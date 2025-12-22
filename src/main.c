extern void greet();
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "trace_board_state/pub.h"
#include "headers/types.h"

int main() {
  // printf("Calling greet();...");
  // fflush(stdout);
  // greet();

  Board* board = trace_moves("e2e4 d7d5 e4d5 g8f6 f1b5 c7c6 d5c6 d8b6 c6b7 b6b5 b7c8q ");
  //print_board(board, true);
  free(board);
  Board* board2 = trace_moves("e1g1 ");
  print_board(board2, true);
  free(board2);
  
  return 0;
}
