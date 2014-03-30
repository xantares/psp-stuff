#ifndef _SEARCH_H
#define _SEARCH_H

#include "game.h"

typedef struct {
  int side;
  int depth;
  int maximumDepth;
  int numberOfTerminalNode;
  move_st bestMove;
} search_st;

static const int InfiniteEvaluation = 1000000;
static const int MaximumEvaluation = 1000;


#ifdef __cplusplus
extern "C" {
#endif


void searchInit (search_st *search, game_st *game);
void searchRun (search_st *search, game_st *game);
int searchComputeMinMax (search_st *search, game_st *game);


#ifdef __cplusplus
}
#endif

#endif