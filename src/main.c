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
#include <string.h> // strncmp
#include <pthread.h>
#include "trace_board_state/pub.h"
#include "headers/types.h"
#include "headers/find_moves_rs.h"
#include "best_move/best_move.h"

void* from_startpos(void *string);
void* bestmove(void* board_void);

int main() { // This function is a REPL

  /*
  Board* board = trace_moves("e2e4 d7d5 e4d5 g8f6 f1b5 c7c6 d5c6 d8b6 c6b7 b6b5 b7c8q ");
  print_board(board, true);

  char* moves = find_all_moves(*board);
  printf("\n%s",moves);

  char* best = best_move(board, moves);
  printf("\nbestmove %s",best);

  free(board);
  free_string(moves);
  
  return 0;
  */
  while (true) {
    char *input = NULL;
    size_t len = 0;
    if (getline(&input, &len, stdin) != -1) {
      if (strncmp(input, "uci", 3) == 0) {
        printf("id name Chess Engine\n");
        printf("id author Folke Cederholm\n");
        printf("uciok\n");
        fflush(stdout);
        break;
      }
    }
  }
  Board* board = NULL;
  while (true) {
    char* input = NULL;
    size_t len = 0;
    pthread_t thread;
    if (getline(&input, &len, stdin) != -1) {
      if (strcmp(input, "isready\n") == 0)
        printf("readyok\n");
        fflush(stdout);
      if (strcmp(input, "exit\n") == 0) {
        printf("ok\n");
        fflush(stdout);
        break;
      }
      if (strncmp(input, "position startpos ", 17) == 0) { /* If input starts with "go" */
        // pthread_t thread;
        char* moves_string = input + 17;
        if (pthread_create(&thread, NULL, from_startpos, moves_string) != 0) {
          printf("Couldn't create a new thread");
          fflush(stdout);
          return 1;
        }
      }
      if (strncmp(input, "go", 2) == 0) {
        pthread_join(thread, (void**)&board);
        pthread_create(&thread, NULL, bestmove, board);
      }
      if (strncmp(input, "board", 5) == 0) {
        print_board(board, true);
        fflush(stdout);
      }
    }


    free(input);
  }

  return 0;
}

void* from_startpos(void *string) {
  fflush(stdout);
  char* moves_string = (char*)string;
  Board* board = trace_moves(moves_string);
  void* to_return = (void*)board;
  fflush(stdout);
  return to_return;
}

void* bestmove(void* board_void) {
  Board* board = (Board*)board_void;
  char* moves = find_all_moves(*board);
  char* best = best_move(board, moves);
  free_string(moves);
  printf("bestmove %s\n",best);
  fflush(stdout);
  return NULL;
}
