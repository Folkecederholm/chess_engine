#include "../headers/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/***starting_board() is a kind of Board***/
Board* starting_board() {
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
  Board* heap_board = (Board*)malloc(sizeof(Board));
  memcpy(heap_board->board, board.board, sizeof(Board));
  return heap_board;
}

void set_piece(Board* board, int x, int y, Piece piece) {
  board->board[x + 8*y] = piece;
}

void make_move(Board* board, char* move) {

  if (move == 0) // Null move - don't change the board
    return;
 
  // -48 = ASCII to literal value
  // -96 = letter to literal value
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


   // Check for castling
   int c1 = strcmp(move, "e1g1 ");
   int c2 = strcmp(move, "e1c1 ");
   int c3 = strcmp(move, "e8g8 ");
   int c4 = strcmp(move, "e8c8 ");
   if (moved_piece % 6 == WHITE_KING) {//If black or white king
     if (c1 == 0) {
       set_piece(board, 4, 0, EMPTY_SQUARE);
       set_piece(board, 5, 0, WHITE_ROOK);
       set_piece(board, 6, 0, WHITE_KING);
       set_piece(board, 7, 0, EMPTY_SQUARE);
     }
     if (c2 == 0) {
       set_piece(board, 0, 0, EMPTY_SQUARE);
       set_piece(board, 1, 0, EMPTY_SQUARE);
       set_piece(board, 2, 0, WHITE_KING);
       set_piece(board, 3, 0, WHITE_ROOK);
       set_piece(board, 4, 0, EMPTY_SQUARE);
     }
     if (c3 == 0) {
       set_piece(board, 4, 8, EMPTY_SQUARE);
       set_piece(board, 5, 8, WHITE_ROOK);
       set_piece(board, 6, 8, WHITE_KING);
       set_piece(board, 7, 8, EMPTY_SQUARE);
     }
     if (c4 == 0) {
       set_piece(board, 0, 8, EMPTY_SQUARE);
       set_piece(board, 1, 8, EMPTY_SQUARE);
       set_piece(board, 2, 8, WHITE_KING);
       set_piece(board, 3, 8, WHITE_ROOK);
       set_piece(board, 4, 8, EMPTY_SQUARE);
     }
   } else { //No castling
    set_piece(board, x1, y1, EMPTY_SQUARE);
    set_piece(board, x2, y2, moved_piece);
  }
  


}
