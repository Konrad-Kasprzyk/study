#include "csapp.h"

int main(int argc, char *argv[]) {
  if (argc < 2)
    app_error("Give me a string!");
  // s to długość stringa, ale bez ostatniego znaku '\0'
  const char *s = argv[1];
  // więc mamy za mało pamięci w p o jeden char
  char *p = malloc(strlen(s));
  strcpy(p, s);
  free(p);
  return 0;
}
