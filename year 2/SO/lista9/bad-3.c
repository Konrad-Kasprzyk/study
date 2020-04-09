#include "csapp.h"

#define M 10
#define N 20

int main(void) {
  // zapełnia zadany obszar x, liczbami 0xf0, gdzie zapełnianiy rozmiar to N * sizeof(int)
  int *x = malloc(N * sizeof(int));
  memset(x, 0xf0, N * sizeof(int));
  free(x);
  int *y = malloc(M * sizeof(int));
  // użyliśmy M w malloc, a tutaj N
  memset(y, 0x0f, N * sizeof(int));
  // free(x) zamiast free(y)
  free(x);
  return 0;
}
