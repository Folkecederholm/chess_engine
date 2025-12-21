%:ifndef TYPES_H
%:define TYPES_H


typedef char Piece;
#define EMPTY_SQUARE 0
#define WHITE_KING 1
#define WHITE_QUEEN 2
#define WHITE_ROOK 3
#define WHITE_BISHOP 4
#define WHITE_KNIGHT 5
#define WHITE_PAWN 6
#define BLACK_KING 7
#define BLACK_QUEEN 8
#define BLACK_ROOK 9
#define BLACK_BISHOP 10
#define BLACK_KNIGHT 11
#define BLACK_PAWN 12

typedef struct {
  Piece board[64];
} Board;

%:endif
