#ifndef _BOARD_H
#define _BOARD_H

#include "game.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


typedef struct {
  SDL_Surface *field;
  SDL_Surface *screen;
  SDL_Surface *bar[9];
  SDL_Surface *arrow[10];
  int arrow_orientation;
} board_st;

#ifdef __cplusplus
extern "C" {
#endif

void boardInit (board_st *board);
void boardRefresh (board_st *board, game_st *game);
void boardRefreshArrow (board_st *board, int flip);
void boardQuit (board_st *board);

#ifdef __cplusplus
}
#endif

#endif