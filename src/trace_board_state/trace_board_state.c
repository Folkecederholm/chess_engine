#include "../headers/types.h"
#include <stdio.h>

/***starting_board() is a kind of Board***/
Board starting_board() {
  Board board = { .board = {
    WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK,
    WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN,
    BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK,
     }};
  return board;
}

void set_piece(Board* board, int x, int y, Piece piece) {
  board->board[x + 8*y] = piece;
}

void make_move(Board* board, char* move) {
  if (move == 0) // Null move - don't change the board
    return;
  // -48 = ASCII to literal value
  // -96 = char to literal value
  // -1 since arrays are 0-indexed
  int x1 = move[0] - 96 - 1;
  int x2 = move[2] - 96 - 1;
  int y1 = move[1] - 48 - 1;
  int y2 = move[3] - 48 - 1;
  /* will be space if no promotion*/
  Piece moved_piece = board->board[x1 + 8 * y1];
  char promote_to = move[4]; 
  switch (promote_to) {
    case 'q':
      moved_piece -= 4;
      break;
    case 'n':
      moved_piece -= 5;
      break;
    case 'b':
      moved_piece -= 2;
      break;
    case 'r':
      moved_piece -= 3;
      break;
  }

  set_piece(board, x1, y1, EMPTY_SQUARE);
  set_piece(board, x2, y2, moved_piece);

  // printf("\nx1:%d\nx2:%d\ny1:%d\ny2:%d\npromote_to:%c\n",x1,x2,y1,y2,promote_to);
}


void print_board(Board* board, _Bool utf8) {
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
      printf(" %02hhu ", board->board[i]);
    }

    if (i % 8 == 7)
      printf("\n");
  }
}


void trace_moves(char* moves_str) {
  Board board = starting_board();
  /*
  make_move(&board, "e2e4");
  make_move(&board, "e7e5");
  */
  while (1) {
    // printf("BEFORE:{%s} ",moves_str);
    // printf("FIRST_CHAR:{%c}",moves_str[0]);
    make_move(&board, moves_str);

    do { moves_str++; } while (*(moves_str-1) != ' ' && *moves_str != '\0');
    // printf("AFTER:{%s} ",moves_str);
    if (*moves_str == '\0') {
      // printf("BREAKING\n");
      break;
      }
  }
  print_board(&board, 1);
}


