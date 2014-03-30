#ifndef _GAME_H
#define _GAME_H

#define MAX_CELL_X 9
#define MAX_CELL_Y 7

#include "move.h"

typedef enum {
  WhiteSide = 0,
  BlackSide,
  NoneSide
} side_e;

typedef enum {
  East = 0,
  NorthEast,
  North,
  NorthWest,
  SouthEast,
  South,
  SouthWest,
  West,
  NoneOrientation,
  Stop
} link_type_e;

typedef struct {
  unsigned int link[MAX_CELL_X][MAX_CELL_Y];
  coord_st position;
  int side;
  int isOver;
  int winner;
} game_st;


#ifdef __cplusplus
extern "C" {
#endif

void gameInit (game_st *game);
void gamePlay (game_st *game, move_st *move);
void gameCancel (game_st *game, move_st *move);
void gameCheckOver (game_st *game);
void gameApplyDirection (game_st *game, unsigned int direction);
void gameChangeSide (game_st *game);
int gameNumberOfLink (game_st *game);
int gameHasLink (game_st *game, int direction);
int gameEvaluate (game_st *game, int side);
int getOrientation (coord_st *coord);

#ifdef __cplusplus
}
#endif

#endif