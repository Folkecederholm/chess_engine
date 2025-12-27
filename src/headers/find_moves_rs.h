/* This file is for importing Rust functions for the find_moves module.
 * These functions work independently of being defined as extern.
 * I have to figure that out sometime.
 */


#ifndef FIND_MOVES_RS_H
#define FIND_MOVES_RS_H

%:include "types.h"
extern void describe_board(Board board);
extern char* find_all_moves(Board board);
extern void free_string(char* string);
extern void test_rust();


#endif
