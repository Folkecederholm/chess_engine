#include "../headers/types.h"
#include <stdio.h>
#include "boil.h"
#include <stdlib.h>
#include <stdbool.h>

// %:include "pub.h" //for debugging with the print_board function

Board* trace_moves(char* moves_str) {
  Board* board = starting_board();
  while (1) {
    // printf("BEFORE:{%s} ",moves_str);
    // printf("FIRST_CHAR:{%c}",moves_str[0]);
    make_move(board, moves_str);

    do { moves_str++; } while (*(moves_str-1) != ' ' && *moves_str != '\0');
    // printf("AFTER:{%s} ",moves_str);
    // print_board(board, true);
    if (*moves_str == '\0') {
      // printf("BREAKING\n");
      break;
      }
  }

  return board;
}


void print_board(Board* board, bool utf8) {
  printf("\n");
  for (int i = 0; i < 64; i++) {

    if (utf8) {
      char piece[4] = {0b11100010, 0b10011001, 0b10010011, '\0'};
      piece[2] += board->board[i];
      if (board->board[i] != EMPTY_SQUARE) {
        printf("%s ", piece);
      } else {
        printf("  ");
      }
    } else {
      printf("%02hhu ", board->board[i]);
    }

    if (i % 8 == 7)
      printf("\n");
  }
}
