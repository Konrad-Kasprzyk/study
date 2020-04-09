#include "shell.h"

typedef int (*func_t)(char **argv);

typedef struct {
  const char *name;
  func_t func;
} command_t;

static int do_quit(char **argv) {
  exit(EXIT_SUCCESS);
}

/*
 * 'cd' - change directory to $HOME
 * 'cd path' - change directory to path
 */
static int do_chdir(char **argv) {
  char *path = argv[0];
  if (path == NULL)
    path = getenv("HOME");
  int rc = chdir(path);
  if (rc < 0) {
    msg("cd: %s: %s\n", strerror(errno), path);
    return 1;
  }
  return 0;
}

static command_t builtins[] = {
  {"quit", do_quit},
  {"cd", do_chdir},
  {NULL, NULL},
};

int builtin_command(char **argv) {
  for (command_t *cmd = builtins; cmd->name; cmd++) {
    if (strcmp(argv[0], cmd->name))
      continue;
    return cmd->func(&argv[1]);
  }

  errno = ENOENT;
  return -1;
}

noreturn void external_command(char **argv) {
  // gdy nie znalazło to zwraca NULL
  const char *path = getenv("PATH");

  // funckja index zwraca wskaźnik na pierwsze wystąpienie '/' w argv[0], czyli gdy nie ma '/' to zwróci 0
  if (!index(argv[0], '/') && path) {
    /* TODO: For all paths in PATH construct an absolute path and execve it. */
    while (true) {
      // strcspn zwraca ile jest znaków w stringu path przed znakiem ":"
      size_t len = strcspn(path, ":");

      if (!len)
        break;
      
      // strndup kopiuje 'len' znaków ze stringa 'path' do 'full'
      char* full = strndup(path, len);
      // funkcja zdefiniowana w pliku "shell", dopisuje string do stringa
      strapp(&full, "/");
      strapp(&full, argv[0]);

      // jak podaliśmy nie tą ścieżkę z PATH, to nie wykona się, zwróci -1 i dalej obieg pętli while
      (void)execve(full, argv, environ);
      // przechodzimy za następny ":" we wszystkich ścieżkach w PATH
      path += len + 1;
      free(full);
    }
  } else {
    // użytkownik podał ścieżkę względną, więc wg polecenia odpalamy execve od razu
    (void)execve(argv[0], argv, environ);
  }

  msg("%s: %s\n", argv[0], strerror(errno));
  exit(EXIT_FAILURE);
}
