extern void greet();
#include <stdio.h>
#include <stdlib.h>
#include "trace_board_state/trace_board_state.h"

int main() {
  printf("Calling greet();...");
  fflush(stdout);
  //greet();

  trace_moves("e2e4 d7d5 e4d5 g8f6 f1b5 c7c6 d5c6 d8b6 c6b7 b6b5 b7c8q ");
  
  return 0;
}
