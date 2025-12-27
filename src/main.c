//   This is the main function. This is where it happens.
//   Through the whole project, these rules for comments apply:
//   /* These comments are important */
//   // These comments are less important
//   // They can also be commented out code
//
//   Also, %: is used as a digraph instead of # sometimes.
//   This is where multiple preprocessor aspects are used and %:
//   helps to differentiate the two procesess
//   E.g. header guards with #ifndef... and
//   includes with %:include...


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "trace_board_state/pub.h"
#include "headers/types.h"
#include "headers/find_moves_rs.h"
#include "best_move/best_move.h"

int main() {
  // printf("Calling greet();...");
  // fflush(stdout);
  // greet();

  Board* board = trace_moves("e2e4 d7d5 e4d5 g8f6 f1b5 c7c6 d5c6 d8b6 c6b7 b6b5 b7c8q ");
  print_board(board, true);
  // describe_board(*board);

  char* moves = find_all_moves(*board);
  printf("\n%s",moves);

  char* best = best_move(board, moves);
  // char* best = "e2e4 ";
  printf("\nbestmove %s",best);

  free(board);
  free_string(moves);
  
  return 0;
}
