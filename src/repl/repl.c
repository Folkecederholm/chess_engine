#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void repl() {
  while (true) {
  char *input = NULL;
  size_t len = 0;
  if (getline(&input, &len, stdin) != -1) {
    if (strcmp(input, "isready\n") == 0)
      printf("readyok\n");
    if (strcmp(input, "exit\n") == 0)
      break;
  }


  free(input);
  }
}
