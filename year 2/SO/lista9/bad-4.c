#include "csapp.h"

#define M 10
#define N 20

int main(void) {
  int *x = malloc(N * sizeof(int));
  memset(x, 0xf0, N * sizeof(int));
  free(x);
  int *y = malloc(M * sizeof(int));
  // wcześniej zrobiliśmy free(x), a w pętli się do tej pamięci odwołujemy
  for (int i = 0; i < M; i++)
    y[i] = x[i]++;
  return 0;
}
