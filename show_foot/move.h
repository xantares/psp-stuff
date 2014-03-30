#ifndef _MOVE_H
#define _MOVE_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_MOVE 64

typedef struct {
  int x;
  int y;
} coord_st;

typedef struct {
  int length;
  int max_length;
  int *sequence;
} move_st;


#ifdef __cplusplus
extern "C" {
#endif

void moveInit (move_st *move);
void moveAddDirection (move_st *move, int direction);
void moveRemoveDirection (move_st *move);
int moveLastDirection (move_st *move);
void moveCopy (move_st *source, move_st *dest);
int moveEmpty (move_st *move);
void moveQuit (move_st *move);
void movePrint (move_st *move);

#ifdef __cplusplus
}
#endif

#endif