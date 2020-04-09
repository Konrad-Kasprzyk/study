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

#define N 10

int main(void) {
  list_t head;
  for (int i = 0; i < N; i++)
    // funckja new_node(i) wewnątrz makra wykona się dwa razy, więc nie będzie uporządkowanej listy, tylko losowe wskaźniki
    SLIST_INSERT_HEAD(&head, new_node(i), link);
  // zwalniana jest tylko głowa listy, a nie cała lista
  free(SLIST_FIRST(&head));
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

  