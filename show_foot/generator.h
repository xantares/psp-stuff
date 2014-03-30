#ifndef _GENERATOR_H
#define _GENERATOR_H

#include "game.h"
#include "move.h"

#define MAX_GEN 256

typedef struct {
  int direction0;
  move_st move;
} generator_st;


#ifdef __cplusplus
extern "C" {
#endif

void generatorInit (generator_st *generator);
int generatorFind (generator_st *generator, game_st *game);
void generatorQuit (generator_st *generator);

#ifdef __cplusplus
}
#endif

#endif