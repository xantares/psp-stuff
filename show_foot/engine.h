#ifndef _ENGINE_H
#define _ENGINE_H


#include "board.h"

typedef struct {
  game_st game;
  board_st board;
} engine_st;


#ifdef __cplusplus
extern "C" {
#endif

void engineInit (engine_st *engine);
void engineRun (engine_st *engine);
void engineHumanTurn (engine_st *engine);
void engineIaTurn (engine_st *engine);
void engineQuit (engine_st *engine);

#ifdef __cplusplus
}
#endif

#endif