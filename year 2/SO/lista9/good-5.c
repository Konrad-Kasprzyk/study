#include "csapp.h"
#include "queue.h"

typedef struct node {
  SLIST_ENTRY(node) link;
  long value;
} node_t;

typedef SLIST_HEAD(, node) list_t;

node_t *new_node(long value) {
  node_t *node = malloc(sizeof(node_t));
  node->value = value;
  return node;
}

void free_list(node_t* list) {
  if (list) {
    printf("przed free_list\n");
    free_list(SLIST_NEXT(list, link));
    printf("po free_list\n");
    free(list);
  }
}

#define N 10

int main(void) {
  // bez tego, gdy free_list dojdzie do ostatniego noda, to będzie miał zły wskaźnik -> patrz pierwsza linika w SLIST_INSERT_HEAD
  list_t head = {.slh_first = NULL};
  for (int i = 0; i < N; i++){
    // dzięki temu funkcja free_list nie da błędu idąc do drugiego noda w liście
    node_t* node = new_node(i);
    SLIST_INSERT_HEAD(&head, node, link);
  }
  // zwalniana jest tylko głowa listy, a nie cała lista
  free_list(SLIST_FIRST(&head));
  return 0;
}

// #define SLIST_NEXT(elm, field) ((elm)->field.sle_next)

// #define SLIST_HEAD(name, type)                                                 \
//  struct name {                                                                \
//    struct type *slh_first; /* first element */                                \
//  }

// #define SLIST_INSERT_HEAD(head, elm, field)                                    
//  do {                                                                         
//    (elm)->field.sle_next = (head)->slh_first;                                 
//    (head)->slh_first = (elm);                                                 
//  } while (/*CONSTCOND*/ 0)

  