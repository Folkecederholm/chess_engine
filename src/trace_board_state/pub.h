%:ifndef TRACE_BOARD_STATE_H
%:define TRACE_BOARD_STATE_H

#include "../headers/types.h"

/* trace_moves:
 -> allocates memory for board, returns Board*
 * long algebraic notation, always ends with a space
 * always lowercase letters, e.g. e2e4
 * nullmove = 0000
 * promotion: b7b8q <!- last letter = what it promotes to
 * castling: says where king goes => one of {e1g1 e1c1 e8g8 e8c8}
**/
Board* trace_moves(char* moves_str);

/* print_board:
 -> prints the specified chess board
 * the second argument specifies whether to print with utf8 chess chars or in ascii
**/
void print_board(Board* board, bool utf8);

%:endif
