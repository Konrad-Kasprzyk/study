/* Konrad Kasprzyk 299243
 *
 *
 * Struktura zajętego bloku:
 *  uint32_t size - rozmiar bloku, reszta wolna dla użytkownika
 * 
 * Struktura wolnego bloku:
 *  uint32_t size - rozmiar bloku, uint32_t prev - pierwsze 32 bity wskaźnika, uint32_t next - pierwsze 32 bity wskaźnika, 
 *  reszta wolna bez ostatnich 4 bajtów, uint32_t - rozmiar bloku
 * 
 * Wyjaśnienie wskaźników:
 *  Wskaźnik next wolnego bloku (po dodaniu 0x800000000) może wskazywać na prawe poddrzewo,
 *  początek listy wolnych bloków tego samego rozmiaru lub następnik w liście wolnych bloków tego samego rozmiaru.
 * 
 *  Wskaźnik prev wolnego bloku (po dodaniu 0x800000000) może wskazywać na lewe poddrzewo,
 *  prawe poddrzewo (gdy jest pierwszy na liście wolnych bloków) lub poprzednik w liście wolnych bloków tego samego rozmiaru.
 * 
 * Wyjaśnienie bitów:
 *  Zarówno w rozmiarze i wskaźniku mamy wolne 2 pierwsze bity.
 *  W rozmiarze bloku jest informacja, czy blok jest wolny i czy poprzedni blok jest wolny.
 *  We wskaźniku prev jest informacja, czy blok jest na liście wolnych bloków o tym samym rozmiarze i czy jest pierwszy na tej liście.
 *  We wskaźniku next jest informacja, czy blok wskaźnik wskazuje na początek listy bloków tego samego rozmiaru.
 * 
 * Wolne bloki są przechowywane na drzewie BST. Każdy wierzchołek drzewa jest innego rozmiaru.
 * Jeśli do drzewa dodajemy blok, gdzie istnieje już wierzchołek o tym samym rozmiarze, to blok jest
 * dodawany do listy bloków tego samego rozmiaru. Wierzchołek może wskazywać wskaźnikiem next na prawe poddrzewo lub
 * na początek listy bloków tego samego rozmiaru. Lista wolnych bloków jest dwukierunkowa, gdzie ostatni blok wskazuje
 * na NULL, a pierwszy ma za poprzednika prawe poddrzewo.
 * 
 * Malloc przeszukuje drzewo by znaleźć najlepiej pasujący blok. Gdy blok jest większy niż potrzeba,
 * to dzieli blok i pozostałą część z powrotem wstawia do drzewa.
 * 
 * Free gorliwie złącza bloki. Usuwa sąsiednie bloki ze sterty z drzewa i wstawia jeden powiększony.
 * Usuwanie bloku, który jest na liście wolnych tego samego rozmiaru i nie jest pierwszym blokiem tej listy,
 * odbywa się w czasie stałym, bo lista jest dwukierunkowa. 
 * 
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
#define DEBUG
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

static void *root;
typedef uint32_t word_t; 
static bool last_free;  /* Jeśli ostatni blok na stercie jest wolny to last_free == true */

typedef enum
{
  // Bity w rozmiarze bloku
  FREE = 1,     /* Block is free */
  USED = 0,     /* Block is used */
  PREVFREE = 2, /* Previous block is free (optimized boundary tags) */
  // Bity we wskaźniku next w wolnym bloku
  POINTS_AT_LIST = 1,
  // Bity we wskaźniku prev w wolnym bloku
  ON_LIST = 1,
  FIRST_ON_LIST = 2,
} bt_flags;

typedef struct
{
  word_t size;
  word_t prev;
  word_t next;
} free_block;

static word_t round_up(word_t size)
{
  return (size + ALIGNMENT - 1) & -ALIGNMENT;
}

static void clear_bit(word_t *word, word_t bit)
{
  *word &= ~bit;
}

static void set_bit(word_t *word, word_t bit)
{
  *word |= bit;
}

static void clear_bits(word_t *word)
{
  *word &= ~3;
}

// Zwraca wskaźnik na blok zapisany we wskaźniku next. Przyjmuje wskaźnik na wolny blok.
static void *get_next_block(void *ptr)
{
  word_t *next = ptr + 8;
  if (*next < 4)
    return NULL;
  return (void *)((*next & ~3) + 0x800000000);
}

// Zwraca wskaźnik na blok zapisany we wskaźniku prev. Przyjmuje wskaźnik na wolny blok.
static void *get_prev_block(void *ptr)
{
  word_t *prev = ptr + 4;
  if (*prev < 4)
    return NULL;
  return (void *)((*prev & ~3) + 0x800000000);
}

// Zwraca wskaźnik na następny blok na stercie
static free_block *get_next_heap_block(free_block *block)
{
  return (free_block *)((void *)block + (block->size & ~3));
}

// Zwraca wskaźnik na poprzedni blok na stercie
static free_block *get_prev_heap_block(free_block *block)
{
  word_t *prev_size = (void *)block - sizeof(word_t);
  return (free_block *)((void *)block - (*prev_size & ~3));
}

// Ustawia w bloku pod adresem (ptr) wskaźnik na następny blok (val)
static void set_next_pointer(void *ptr, word_t val)
{
  word_t *next = ptr + 8;
  *next = val;
}

// Ustawia w bloku pod adresem (ptr) wskaźnik na poprzedni blok (val)
static void set_prev_pointer(void *ptr, word_t val)
{
  word_t *prev = ptr + 4;
  *prev = val;
}

// Zwraca ostatni uint32_t w bloku
static word_t *get_last_word(free_block *block)
{
  return (word_t *)((void *)block + (block->size & ~3) - sizeof(word_t));
}

// Zwraca wskaźnik na prawe poddrzewo
static free_block *get_right_node(free_block *node)
{
  // gdy wskaźnik == 0, to znaczy, że wskazuje na NULL.
  if (node->next == 0)
    return NULL;
  if (node->next & POINTS_AT_LIST)
  {
    void *firts_block_on_list = get_next_block(node);
    return (free_block *)get_prev_block(firts_block_on_list);
  }
  return (free_block *)get_next_block(node);
}

// Zwraca wskaźnik na lewe poddrzewo
static free_block *get_left_node(free_block *node)
{
  if (node->prev == 0)
    return NULL;
  return (free_block *)get_prev_block(node);
}

// wraca wskaźnik na prawe poddrzewo typu uint32_t
static word_t *get_right_pointer(free_block *node)
{
  if (node->next & POINTS_AT_LIST)
  {
    free_block *first_block = get_next_block(node);
    return &first_block->prev;
  }
  else
    return &node->next;
}

// Ustawia wskaźnik na prawe poddrzewo w wierzchołku node
static void set_right_pointer(free_block *node, word_t ptr)
{
  if (node->next & POINTS_AT_LIST)
  {
    free_block *first_block = get_next_block(node);
    first_block->prev = ptr;
    clear_bits(&first_block->prev);
    set_bit(&first_block->prev, ON_LIST);
    set_bit(&first_block->prev, FIRST_ON_LIST);
  }
  else
  {
    node->next = ptr;
    clear_bits(&node->next);
  }
}

// Wstawia blok block do listy bloków tego samego rozmiaru w wierzchołku node.
// Gdy wierzchołek node nie ma listy to tworzy ją.
static void insert_to_same_size_list(free_block *node, free_block *block)
{
  // Co najmniej jeden blok na liście
  if (node->next & POINTS_AT_LIST)
  {
    void *first_block = get_next_block(node);
    free_block *second_block = (free_block *)get_next_block(first_block);
    if (second_block != NULL)
    {
      set_prev_pointer(second_block, (uintptr_t)block);
      set_bit(&second_block->prev, ON_LIST);
    }
    set_next_pointer(block, (uintptr_t)second_block);
    set_prev_pointer(block, (uintptr_t)first_block);
    set_next_pointer(first_block, (uintptr_t)block);
    set_bit(&block->prev, ON_LIST);
  }
  else
  {
    // Wstawiamy pierwszy wierzhołek na listę
    set_prev_pointer(block, node->next);
    set_next_pointer(block, 0);
    set_next_pointer(node, (uintptr_t)block);
    clear_bits(&block->prev);
    set_bit(&block->prev, ON_LIST);
    set_bit(&block->prev, FIRST_ON_LIST);
    set_bit(&node->next, POINTS_AT_LIST);
  }
}

// Wstawia wolny blok do drzewa. Może wstawić jako nowy wierzchołek
// lub dodać do listy bloków tego samego rozmiaru
static void insert_to_tree(free_block *block)
{
  set_next_pointer(block, 0);
  set_prev_pointer(block, 0);
  if (root == NULL)
  {
    root = block;
    return;
  }
  free_block *node = root;
  word_t *prev_node_ptr;
  word_t block_size = block->size;
  clear_bits(&block_size);
  word_t node_size;
  while (node != NULL)
  {
    node_size = node->size;
    clear_bits(&node_size);
    if (node_size < block_size)
    {
      prev_node_ptr = get_right_pointer(node);
      node = get_right_node(node);
    }
    else if (node_size > block_size)
    {
      prev_node_ptr = &node->prev;
      node = get_left_node(node);
    }
    else
    {
      insert_to_same_size_list(node, block);
      return;
    }
  }
  *prev_node_ptr = (*prev_node_ptr & 3) + (uintptr_t)block;
}

// Usuwa pierwszy blok z listy bloków tego samego rozmiaru, na którą wskazuje wierzchołek node
static void delete_first_block_on_list(free_block *node)
{
  free_block *first_block = get_next_block(node);
  // Jedyny blok na liście wolnych bloków
  if (first_block->next == 0)
  {
    node->next = first_block->prev;
    clear_bits(&node->next);
  }
  else
  {
    free_block *second_block = get_next_block(first_block);
    node->next = first_block->next;
    clear_bits(&node->next);
    set_bit(&node->next, POINTS_AT_LIST);
    second_block->prev = first_block->prev;
  }
}

// Gdy malloc chce wziąć wolny blok danego rozmiaru, a istnieje lista wolnych bloków z jego rozmiarem,
// to ta funkcja zwraca blok z tej listy i usuwa go. Na listę wskazuje wierzchołek node.
static free_block *get_and_delete_block_on_list(free_block *node)
{
  free_block *first_block = get_next_block(node);
  if (first_block->next == 0)
  {
    node->next = first_block->prev;
    clear_bits(&node->next);
    return first_block;
  }
  free_block *second_block = get_next_block(first_block);
  if (second_block->next == 0)
  {
    first_block->next = 0;
    return second_block;
  }
  else
  {
    free_block *third_block = get_next_block(second_block);
    first_block->next = second_block->next;
    third_block->prev = second_block->prev;
    return second_block;
  }
}

// Usuwa dany wolny blok z drzewa, gdy jest wierzchołkiem lub pierwszym blokiem na liście wolnych bloków.
// W przeciwnym wypadku funkcja nie zadziała. Wierzchołek musi być w drzewie.
static void delete_node_or_first_block(free_block *to_delete)
{
  free_block *node = root;
  word_t *prev_node_ptr = NULL;
  word_t to_delete_size = to_delete->size;
  clear_bits(&to_delete_size);
  word_t node_size = node->size;
  clear_bits(&node_size);
  // Szukamy wierzchołka o takim samym rozmiarze
  while (node_size != to_delete_size)
  {
    if (node_size < to_delete_size)
    {
      prev_node_ptr = get_right_pointer(node);
      node = get_right_node(node);
    }
    else
    {
      prev_node_ptr = &node->prev;
      node = get_left_node(node);
    }
    node_size = node->size;
    clear_bits(&node_size);
  }

  // Gdy to inny blok tego samego rozmiaru, to musi być pierwszy na liście w tej funkcji
  if (node != to_delete)
  {
    delete_first_block_on_list(node);
    return;
  }

  // Gdy wierzchołek ma listę bloków, to usuń wierzchołek, wstawiając na jego miejsce któryś blok z listy
  if (node->next & POINTS_AT_LIST)
  {
    free_block *first_block = get_next_block(node);
    // Tylko jeden blok na liście bloków tego samego rozmiaru
    if (first_block->next == 0)
    {
      if (prev_node_ptr != NULL)
        *prev_node_ptr = (*prev_node_ptr & 3) + (uintptr_t)first_block;
      else
        root = first_block;
      first_block->next = first_block->prev;
      clear_bits(&first_block->next);
      first_block->prev = node->prev;
      return;
    }
    else
    {
      if (prev_node_ptr != NULL)
        *prev_node_ptr = (*prev_node_ptr & 3) + (uintptr_t)first_block;
      else
        root = first_block;
      free_block *second_block = get_next_block(first_block);
      second_block->prev = first_block->prev;
      first_block->prev = node->prev;
      set_bit(&first_block->next, POINTS_AT_LIST);
      return;
    }
  }

  // Wierzchołek nie ma listy bloków i jest liściem.
  if (node->next == 0 && node->prev == 0)
  {
    if (prev_node_ptr == NULL)
      root = NULL;
    else
      *prev_node_ptr = (*prev_node_ptr & 3);
    return;
  }

  if (node->next == 0)
  {
    if (prev_node_ptr != NULL)
    {
      clear_bits(&node->prev);
      *prev_node_ptr = (*prev_node_ptr & 3) + node->prev;
    }
    else
      root = get_left_node(node);
    return;
  }

  if (node->prev == 0)
  {
    if (prev_node_ptr != NULL)
    {
      clear_bits(&node->next);
      *prev_node_ptr = (*prev_node_ptr & 3) + node->next;
    }
    else
      root = get_right_node(node);
    return;
  }

  // Wierzchołek nie ma listy wolnych bloków i ma dwa poddrzewa. Szukamy bloku o najmniejszym rozmiarze w prawym poddrzewie
  free_block *change_node = get_right_node(node);

  // Prawy wierzchołek usuwanego wierzchołka jest najmniejszy w poddrzewie, czyli nie ma lewego poddrzewa
  if (change_node->prev == 0)
  {
    change_node->prev = node->prev;
    if (prev_node_ptr != NULL)
    {
      clear_bits(&node->next);
      *prev_node_ptr = (*prev_node_ptr & 3) + node->next;
    }
    else
      root = get_right_node(node);
    return;
  }

  word_t *prev_change_node_ptr = &node->next;
  while (change_node->prev != 0)
  {
    prev_change_node_ptr = &change_node->prev;
    change_node = get_left_node(change_node);
  }
  free_block *right_change_node = get_right_node(change_node);
  *prev_change_node_ptr = (uintptr_t)right_change_node;
  set_right_pointer(change_node, 0);

  // Zamieniamy wierzchołki. node to usuwany, change_node ma go zastąpić,
  // change_node to najmniejszy wierzchołek prawego poddrzewa usuwanego wierzchołka
  change_node->prev = node->prev;
  set_right_pointer(change_node, *get_right_pointer(node));

  if (prev_node_ptr == NULL)
    root = change_node;
  else
    *prev_node_ptr = (*prev_node_ptr & 3) + (uintptr_t)change_node;  
}

// Usuwa wolny blok z drzewa. Wywołuje odpowiednie funkcje w zależności czy to wierzchołek,
// czy blok jest na liście wolnych bloków tego samego rozmiaru
static void delete_from_tree(free_block *block)
{
  if (block->prev & ON_LIST)
  {
    if (block->prev & FIRST_ON_LIST)
    {
      delete_node_or_first_block(block);
    }
    else
    {
      free_block *prev_block = get_prev_block(block);
      free_block *next_block = get_next_block(block);
      if (next_block != NULL)
        set_prev_pointer(next_block, block->prev);
      set_next_pointer(prev_block, block->next);
    }
  }
  else
  {
    delete_node_or_first_block(block);
  }
}

/*
 * mm_init - Called when a new trace starts.
 */
int mm_init(void)
{
  last_free = false;
  root = NULL;
  mem_sbrk(ALIGNMENT - sizeof(word_t));
  return 0;
}

// Szuka dostatecznie dużego wolnego bloku. Jeśli znalazł to zajmuje go i jak może to dzieli blok.
// Jak nie znalazł to powiększa stertę.
void *malloc(size_t size)
{
  // Rozmiar nagłówka zaalokowanego bloku
  size += sizeof(word_t);
  size = round_up(size);

  // Nie mamy żadnego bloku na liście wolnych bloków
  if (root == NULL)
  {
    word_t *block_size = mem_sbrk(size);
    if (block_size < 0)
      return NULL;
    *block_size = size;
    if (last_free)
      set_bit(block_size, PREVFREE);
    last_free = false;
    return (void *)block_size + sizeof(word_t);
  }

  // Szukamy najlepiej pasującego wolnego bloku w drzewie
  free_block *node = root;
  free_block *prev_node = NULL;
  free_block *next_node = NULL;
  free_block *bigger_node = NULL;
  free_block *bigger_prev_node = NULL;
  word_t node_size = node->size;
  clear_bits(&node_size);
  while ((node->prev != 0) || (node->next != 0))
  {
    if (node_size < size)
    {
      next_node = get_right_node(node);
      if (next_node == NULL)
        break;
      else{
        prev_node = node;
        node = next_node;
        node_size = node->size;
        clear_bits(&node_size);
      }
    }
    else if (node_size > size)
    {
      next_node = get_left_node(node);
      if (next_node == NULL)
        break;
      else{
        bigger_prev_node = prev_node;
        bigger_node = node;
        prev_node = node;
        node = next_node;
        node_size = node->size;
        clear_bits(&node_size);
      }
    }
    else
    {
      break;
    }
  }
  // Próbowaliśmy znaleźć najlepiej pasujący blok, ale się nie udało. Weź poprzedni blok, który był dostatecznie duży
  if (bigger_node != NULL){
    if(node_size < size){
      prev_node = bigger_prev_node;
      node = bigger_node;
      node_size = node -> size;
      clear_bits(&node_size);
    }
  }
  // Znaleziono dostatecznie duży blok
  if (node_size >= size)
  {
    if (node->next & POINTS_AT_LIST)
    {
      node = get_and_delete_block_on_list(node);
    }
    else
    {
      if (prev_node == NULL)
        delete_node_or_first_block(node);
      else
      {
        void *old_root = root;
        root = prev_node;
        delete_node_or_first_block(node);
        root = old_root;
      }
    }
    // Blok został już usunięty z drzewa
    if (node_size > size)
    {
      // Podziel wolny blok, by reszta wolnego miejsca była w drzewie jako inny wolny blok
      node->size -= size;
      word_t *last_word_free_block = get_last_word(node);
      *last_word_free_block = node->size;
      insert_to_tree(node);
      node = get_next_heap_block(node);
      node->size = size;
      set_bit(&node->size, PREVFREE);
      clear_bit(&node->size, FREE);
      free_block *next_heap_block = get_next_heap_block(node);
      if ((void *)next_heap_block < mem_sbrk(0))
        clear_bit(&next_heap_block->size, PREVFREE);
      else
        last_free = false;
      return (void *)node + sizeof(word_t);
    }
    else
    {
      // Zajmujemy cały wolny blok
      free_block *next_heap_block = get_next_heap_block(node);
      if ((void *)next_heap_block < mem_sbrk(0))
        clear_bit(&next_heap_block->size, PREVFREE);
      else
        last_free = false;
      clear_bit(&node->size, FREE);
      return (void *)node + sizeof(word_t);
    }
  }

  // Żaden blok na liście wolnych bloków nie jest dostatecznie duży, powiększamy stertę
  word_t *block_size = mem_sbrk(size);
  if (block_size < 0)
    return NULL;
  *block_size = size;
  if (last_free)
    set_bit(block_size, PREVFREE);
  last_free = false;
  return (void *)block_size + sizeof(word_t);
}

// Zwalnia blok i gorliwie złącza z sąsiednimi wolnymi blokami na stercie.
void free(void *ptr)
{
  // Zwracamy użytkownikowi blok zaczynający się za rozmiarem bloku,
  // ale my operujemy na bloku wraz z jego rozmiarem
  ptr -= sizeof(word_t);
  free_block *block = ptr;
  free_block *next_block = get_next_heap_block(block);
  // Poprzedni blok wolny
  if (block->size & PREVFREE)
  {
    free_block *prev_block = get_prev_heap_block(block);
    // Nie wyjdziemy poza stertę i następny blok wolny. Usuń otaczające bloki i wstaw jeden powiększony
    if (((void *)next_block < mem_sbrk(0)) && (next_block->size & FREE))
    {
      delete_from_tree(prev_block);
      delete_from_tree(next_block);
      clear_bits(&block->size);
      clear_bits(&next_block->size);
      word_t new_size = prev_block->size + block->size + next_block->size;
      prev_block->size = new_size;
      word_t *last_word = get_last_word(next_block);
      *last_word = new_size;
      insert_to_tree(prev_block);
    }
    else
    {
      // Poprzedni blok jest tylko wolny, usuń go, powiększ i wstaw
      delete_from_tree(prev_block);
      clear_bits(&block->size);
      prev_block->size += block->size;
      word_t *last_word = get_last_word(block);
      *last_word = prev_block->size;
      if ((void *)next_block < mem_sbrk(0))
        set_bit(&next_block->size, PREVFREE);
      else
        last_free = true;

      insert_to_tree(prev_block);
    }
  }
  else if (((void *)next_block < mem_sbrk(0)) && (next_block->size & FREE))
  {
    // Nie wyjdziemy poza stertę i tylko następny blok wolny. Usuń go, i wstaw powiększony zwalniany blok
    next_block->size &= ~3;
    block->size += next_block->size;
    set_bit(&block->size, FREE);
    word_t *last_word = get_last_word(next_block);
    *last_word = block->size;
    delete_from_tree(next_block);
    insert_to_tree(block);
  }
  else
  {
    // Sąsiednie bloki są zajęte. Wstaw zwalniany blok do drzewa
    set_bit(&block->size, FREE);
    if ((void *)next_block < mem_sbrk(0))
      set_bit(&next_block->size, PREVFREE);
    else
      last_free = true;
    word_t *last_word = get_last_word(block);
    *last_word = block->size;
    insert_to_tree(block);
  }
}

/*
 * realloc - Change the size of the block by mallocing a new block,
 *      copying its data, and freeing the old block.
 **/
void *realloc(void *old_ptr, size_t size)
{
  /* If size == 0 then this is just free, and we return NULL. */
  if (size == 0)
  {
    free(old_ptr);
    return NULL;
  }

  /* If old_ptr is NULL, then this is just malloc. */
  if (!old_ptr)
    return malloc(size);

  void *new_ptr = malloc(size);

  /* If malloc() fails, the original block is left untouched. */
  if (!new_ptr)
    return NULL;

  /* Copy the old data. */
  memcpy(new_ptr, old_ptr, size);

  /* Free the old block. */
  free(old_ptr);

  return new_ptr;
}

/*
 * calloc - Allocate the block and set it to zero.
 */
void *calloc(size_t nmemb, size_t size)
{
  size_t bytes = nmemb * size;
  void *new_ptr = malloc(bytes);
  if (new_ptr)
    memset(new_ptr, 0, bytes);
  return new_ptr;
}

// Sprawdza bity bloku i bity bloków na liście wolnych bloków, gdy sprawdzany blok jest wierzchołkiem z listą.
// Wykonuje się na każdym bloku na stercie.
static bool check_block(free_block *block, int verbose)
{
  if (block->size & PREVFREE)
  {
    free_block *prev_heap_block = get_prev_heap_block(block);
    if (!(prev_heap_block->size & FREE))
    {
      if (verbose > 0)
        printf("block %p has set PREVFREE bit, but prevoius block is not free\n", block);
      return true;
    }
  }

  if(!(block->size & FREE)){
    free_block *next_heap_block = get_next_heap_block(block);
    if ((void *)next_heap_block < mem_sbrk(0))
    {
      if (next_heap_block->size & PREVFREE)
      {
        if (verbose > 0)
          printf("block %p has set PREVFREE bit, but prevoius block is not free\n", next_heap_block);
        return true;
      }
    }
    else
    {
      if (last_free == true)
      {
        if (verbose > 0)
          printf("block %p is last used block, but last_free bool is set to true\n", block);
        return true;
      }
    }
  }


  if(block->size & FREE){
    free_block *next_heap_block = get_next_heap_block(block);
    if ((void *)next_heap_block < mem_sbrk(0))
    {
      if (!(next_heap_block->size & PREVFREE))
      {
        if (verbose > 0)
          printf("block %p has not set PREVFREE bit, but prevoius block is free\n", next_heap_block);
        return true;
      }
    }
    else
    {
      if (last_free == false)
      {
        if (verbose > 0)
          printf("block %p is last free block, but last_free bool is set to false\n", block);
        return true;
      }
    }
  }
 
  if (block -> size & FREE && block->next & POINTS_AT_LIST){
    free_block *first_block = get_next_block(block);
    if (!(first_block->prev & FIRST_ON_LIST)){
      if (verbose > 0)
        printf("block %p has set POINTS_AT_LIST bit, but first block on list doesn't have set FIRST_ON_LIST bit\n", block);
      return true;
    }
    if (!(first_block->prev & ON_LIST)){
      if (verbose > 0)
        printf("block %p has set POINTS_AT_LIST bit, but first block on list doesn't have set ON_LIST bit\n", block);
      return true;
    }
    if (block->prev & ON_LIST){
      if (verbose > 0)
        printf("block %p has set POINTS_AT_LIST bit, but has set ON_LIST bit in prev ptr\n", block);
      return true;
    }
    if (block->prev & FIRST_ON_LIST){
      if (verbose > 0)
        printf("block %p has set POINTS_AT_LIST bit, but has set FIRST_ON_LIST bit in prev ptr\n", block);
      return true;
    }

    free_block *list_block = first_block;
    while (list_block != NULL)
    {
      if (list_block->prev & FIRST_ON_LIST){
        if (!(list_block->prev & ON_LIST))
        {
          if (verbose > 0)
            printf("block %p has set FIRST_ON_LIST bit, but doesn't have set ON_LIST bit\n", list_block);
          return true;
        }

        if (list_block->next & POINTS_AT_LIST)
        {
          if (verbose > 0)
            printf("block %p has set FIRST_ON_LIST bit, but next pointer have set POINTS_AT_LIST bit\n", list_block);
          return true;
        }
      }

      if (list_block->prev & ON_LIST){
        if (list_block->next & POINTS_AT_LIST)
        {
          if (verbose > 0)
            printf("block %p has set ON_LIST bit, but next pointer have set POINTS_AT_LIST bit\n", list_block);
          return true;
        }
      }

      list_block = get_next_block(list_block);
    }
  }
  block = get_next_heap_block(block);
  if((void*)block >= mem_sbrk(0))
    return false;
  return check_block(block, verbose);
}

// Wypisuje rozmiar i wskaźniki wierzchołków na drzewie
static void print_node(free_block *node)
{
  if(node == NULL)
    return;
  printf("size= %d, left_ptr= %d, right_ptr= %d, ptr = %p\n", node->size & ~3, node->prev & ~3, node->next & ~3, node);
  print_node(get_left_node(node));
  print_node(get_right_node(node));
}

// Sprawdza bity każdemu blokowi na stercie. Gdy wykryje niezgodność to wypisuje co się nie zgadza
// i wyświetla wszystkie wolne wierzchołki na stercie, gdy verbose > 0. Kończy działanie programu w razie wykrycia niezgodności.
void mm_checkheap(int verbose)
{
  bool print = false;
  free_block *first_heap_block = (void*)0x80000000c;
  if (mem_sbrk(0) > (void*)0x80000000c)
    print = check_block(first_heap_block, verbose);
  if(print && verbose > 0)
     print_node(root);
  if(print)
    exit(0);
}
