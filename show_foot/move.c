#include "move.h"


void moveInit (move_st *move) {
  move->length = 0;
  move->max_length = 1;
  move->sequence = NULL;
  move->sequence = (int*) malloc (move->max_length * sizeof(int));
}


void moveAddDirection (move_st *move, int direction) {
  ++ move->length;
  if (move->length > move->max_length) {
    move->max_length *= 2;
    printf ("moveAddDirection %d len=%d\n", direction, move->max_length);
    move->sequence = (int*)realloc (move->sequence, move->max_length * sizeof(int));
  }
  move->sequence [move->length-1] = direction;
}


void moveRemoveDirection (move_st *move) {
  if (move->length > 0) {
    -- move->length;
  }
  else {
    printf ("error - moveRemoveDirection length=%d\n", move->length); exit(4);
  }
}


int moveLastDirection (move_st *move) {
  int direction = 0;
  if (move->length > 0) {
    direction = move->sequence [move->length-1];
  }
  else {
    printf ("error - moveLastDirection len=%d\n", move->length); exit(4);
  }
  return direction;
}


void moveCopy (move_st *source, move_st *dest) {
  int i;

  if (dest->max_length < source->length) {
    dest->max_length = source->max_length;
    dest->sequence = (int*) realloc (dest->sequence, dest->max_length * sizeof(int));
  }

  dest->length = source->length;
  for (i = 0; i < source->length; ++ i) {
    dest->sequence[i] = source->sequence[i];
  }
}


int moveEmpty (move_st *move) {
  int empty = 0;
  if (move->length < 1) {
    empty = 1;
  }
  return empty;
}


void moveQuit (move_st *move) {
  free (move->sequence); move->sequence = NULL;
}


void movePrint (move_st *move) {
  int i;

  printf ("movePrint [");
  for (i = 0; i < move->length; ++ i) {
    printf ("%d ", move->sequence[i]);
  }
  printf ("]\n");
}

