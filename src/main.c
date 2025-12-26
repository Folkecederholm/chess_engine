#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "trace_board_state/pub.h"
#include "headers/types.h"

extern void describe_board(Board board);
extern char* make_string(Board board);
extern void free_string(char* string);
extern void test_rust();

int main() {
  // printf("Calling greet();...");
  // fflush(stdout);
  // greet();

  Board* board = trace_moves("e2e4 d7d5 e4d5 g8f6 f1b5 c7c6 d5c6 d8b6 c6b7 b6b5 b7c8q f6h5 0000 ");
  print_board(board, true);
  // describe_board(*board);

  char* string = make_string(*board);
  free(board);
  printf("\n%s",string);
  free_string(string);
  
  return 0;
}
