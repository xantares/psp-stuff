#include "generator.h"


void generatorInit (generator_st *generator) {
  generator->direction0 = 0;
  moveInit (&generator->move);
}


int generatorFind (generator_st *generator, game_st *game) {
  int limit=0,end = 0, found = 0, direction = 0, i;

  for (i = 0; i < generator->move.length; ++ i) {
    direction = generator->move.sequence[i];
    gameApplyDirection (game, direction);
  }
  while (!end) {
    while ((direction < 8) && gameHasLink (game, direction)) {
      ++ direction;
    }
    /*printf ("generatorFind.begin dir=%d\n", direction);*/
    if ((direction < 8) && ((gameNumberOfLink (game) > 1) || moveEmpty(&generator->move))) {
      /* down */
      /*printf ("generatorFind.down dir=%d\n", direction);*/
      gameApplyDirection (game, direction);
      moveAddDirection (&generator->move, direction);
      direction = 0;
    }
    else if (generator->move.length > 0) {
      /* up */
      /*printf ("generatorFind.up dir=%d\n", 7-moveLastDirection(&generator->move));*/
      direction = moveLastDirection(&generator->move) + 1;
      gameApplyDirection (game, 7-moveLastDirection(&generator->move));
      moveRemoveDirection (&generator->move);
    }
    found = (gameNumberOfLink (game) < 2) && !moveEmpty(&generator->move);
    end = found || (limit > 32) || ((direction >= 8) && moveEmpty(&generator->move));
    ++ limit;
  }
  /*printf ("generatorFind.end dir=%d found=%d end=%d limit=%d empty=%d\n", direction, found, end, limit, moveEmpty(&generator->move));*/
  for (i = generator->move.length-1; i >= 0; -- i) {
    gameApplyDirection (game, 7-generator->move.sequence[i]);
  }
  return found;
}


void generatorQuit (generator_st *generator) {
  moveQuit (&generator->move);
}
