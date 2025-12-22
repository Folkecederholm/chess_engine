%:ifndef BOIL_H
%:define BOIL_H

#include <stdbool.h>


#include "../headers/types.h"
Board* starting_board();
void set_piece(Board* board, int x, int y, Piece piece);
void make_move(Board* board, char* move);


%:endif
