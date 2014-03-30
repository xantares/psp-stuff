#include "search.h"
#include "generator.h"


void searchInit (search_st *search, game_st *game) {
  search->maximumDepth = 2;
  search->side = game->side;
  moveInit (&search->bestMove);
}


void searchRun (search_st *search, game_st *game) {
  int found = 0, parentEvaluation = - InfiniteEvaluation, childEvaluation,i=0;
  generator_st generator;

  search->depth = 0;
  search->numberOfTerminalNode = 0;

  if (!game->isOver) {
/*gameApplyDirection (game, East);
gameApplyDirection (game, North);*/
    generatorInit (&generator);
/*found=generatorFind (&generator, game);  found=generatorFind (&generator, game);moveCopy (&generator.move, &search->bestMove);movePrint (&generator.move);return;*/
    while (generatorFind (&generator, game)) {

      gamePlay (game, &generator.move);
      ++ search->depth;
      childEvaluation = searchComputeMinMax (search, game);
printf ("searchRun ce=%d pe=%d side=%d\n",childEvaluation,parentEvaluation,search->side);
      if((childEvaluation > parentEvaluation) || ((childEvaluation == parentEvaluation) && (generator.move.length < search->bestMove.length))) {
        parentEvaluation = childEvaluation;
        moveCopy (&generator.move, &search->bestMove);
      }
      gameCancel (game, &generator.move);
      -- search->depth;
++i;
    }
    printf ("searchRun found=%d\n",found);
    generatorQuit (&generator);
  }
  printf ("searchRun.exit\n");

++i;
/*gameApplyDirection (game, East);
gameApplyDirection (game, North);
    generatorInit (&generator);
    printf ("game.pos=[%d %d]\n",game->position.x,game->position.y);

    for (i=0;i<1;++i) {
    found = generatorFind (&generator, game);

    if (found) {

      movePrint (&generator.move);
    }
     printf ("game.pos=[%d %d]\n",game->position.x,game->position.y);
    }    gamePlay (game, &generator.move);*/
}


int searchComputeMinMax (search_st *search, game_st *game) {
  int parentEvaluation, childEvaluation, maxNode = 0;
  generator_st generator;

  if ((search->depth >= search->maximumDepth) || game->isOver) {
    ++ search->numberOfTerminalNode;
    parentEvaluation = gameEvaluate(game, search->side);
  }
  else {
    maxNode = (game->side == search->side);
    if (maxNode) {
      parentEvaluation = - InfiniteEvaluation;
    }
    else {
      parentEvaluation = + InfiniteEvaluation;
    }
    generatorInit (&generator);
    while (generatorFind (&generator, game)) {
      gamePlay (game, &generator.move);
      ++ search->depth;
      childEvaluation = searchComputeMinMax (search, game);
      if (maxNode) {
        /* compute max */
        if(childEvaluation > parentEvaluation)
          parentEvaluation = childEvaluation;
      }
      else {
        /* compute min */
        if(childEvaluation < parentEvaluation)
          parentEvaluation = childEvaluation;
      }
      gameCancel (game, &generator.move);
      -- search->depth;
    }
  }
  return parentEvaluation;
}