#include "../headers/types.h"
#include <stdlib.h> // rand()
#include <string.h> // strcpy()
#include <stdio.h>


char* best_move(Board* board, char* moves) {
  /* Find length of moves */
  int len;
  int num_moves = 0;
  char *moves_ptr = moves;
  while (*moves) {
    moves++;
    if (*moves == ' ')
      num_moves++;
  }
  len = moves - moves_ptr;
  moves = moves_ptr;

  /* Choose a random move */
  srand(20);
  int chosen = rand() % num_moves;
  // move must be on the heap since it's returned from the function
  char* move = malloc(5); // A move can maximally take up 5 chars
  for (int i = 0; i < chosen; i++) {
    do moves++; while (*moves != ' ');
  }

  /* Copy the move to the move variable */
  // The above sentence is a proof of the adequacy of the name of the move variable
  memcpy(move, moves, 5);
  
  return move;

}
