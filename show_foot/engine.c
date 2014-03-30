#include "engine.h"
#include "search.h"

#ifdef _PSP_FW_VERSION
  #include <pspkernel.h>
  #include <pspdebug.h>
  #include <pspctrl.h>
#endif


void engineInit (engine_st *engine) {
  gameInit (&engine->game);
  boardInit (&engine->board);
}


void engineRun (engine_st *engine) {
  while (!engine->game.isOver) {
    engineIaTurn (engine);
    gameCheckOver (&engine->game);
    if (!engine->game.isOver) {
      engineHumanTurn (engine);
      gameCheckOver (&engine->game);
    }
  }
}


void engineHumanTurn (engine_st *engine) {
  int i, played = 0, direction;
  coord_st orientation;
  move_st move;
#ifdef _PSP_FW_VERSION
  SceCtrlData pad;
#else
  SDL_Event event;
#endif

  moveInit (&move);
  orientation.x = 0;
  orientation.y = 0;
  engine->board.arrow_orientation = getOrientation (&orientation);
  boardRefresh (&engine->board, &engine->game);
  while (!played) {
#ifdef _PSP_FW_VERSION
    sceCtrlReadBufferPositive (&pad, 1);
#else
    SDL_Delay(75);
    SDL_PollEvent(&event);
    if (event.type !=  SDL_KEYDOWN) continue;
#endif

#ifdef _PSP_FW_VERSION
    if (pad.Buttons & PSP_CTRL_DOWN) {
#else
    if (event.key.keysym.sym == SDLK_DOWN) {
#endif
      if (orientation.y < 1) ++ orientation.y; else orientation.x = 0;
      engine->board.arrow_orientation = getOrientation (&orientation);
      boardRefreshArrow (&engine->board, 1);
    }
#ifdef _PSP_FW_VERSION
    else if (pad.Buttons & PSP_CTRL_UP) {
#else
    if (event.key.keysym.sym == SDLK_UP) {
#endif
      if (orientation.y >= 0) -- orientation.y; else orientation.x = 0;
      engine->board.arrow_orientation = getOrientation (&orientation);
      boardRefreshArrow (&engine->board, 1);
    }
#ifdef _PSP_FW_VERSION
    if (pad.Buttons & PSP_CTRL_RIGHT) {
#else
    if (event.key.keysym.sym == SDLK_RIGHT) {
#endif
      if (orientation.x < 1) ++ orientation.x; else orientation.y = 0;
      engine->board.arrow_orientation = getOrientation (&orientation);
      boardRefreshArrow (&engine->board, 1);
    }
#ifdef _PSP_FW_VERSION
    else if (pad.Buttons & PSP_CTRL_LEFT) {
#else
    if (event.key.keysym.sym == SDLK_LEFT) {
#endif
     if (orientation.x >= 0) -- orientation.x; else orientation.y = 0;
      engine->board.arrow_orientation = getOrientation (&orientation);
      boardRefreshArrow (&engine->board, 1);
    }
#ifdef _PSP_FW_VERSION
    if ((pad.Buttons & PSP_CTRL_CROSS)) {
#else
    if (event.key.keysym.sym == SDLK_x) {
#endif
      direction = getOrientation (&orientation);
      if (gameHasLink (&engine->game, direction)) {
        engine->board.arrow_orientation = Stop;
        boardRefreshArrow (&engine->board, 1);
      }
      else {
        moveAddDirection (&move, direction);
        gameApplyDirection (&engine->game, direction);
        boardRefresh (&engine->board, &engine->game);
        if (gameNumberOfLink (&engine->game) < 2) {
          played = 1;
        }
      }
    }
#ifdef _PSP_FW_VERSION
    if ((pad.Buttons & PSP_CTRL_SQUARE)) {
#else
    if (event.key.keysym.sym == SDLK_s) {
#endif
      played = 1;
      engine->game.isOver = 1;
    }
#ifdef _PSP_FW_VERSION
    if (pad.Buttons & PSP_CTRL_TRIANGLE) {
#else
    if (event.key.keysym.sym == SDLK_e) {
#endif
    }

#ifdef _PSP_FW_VERSION
    if (pad.Buttons & PSP_CTRL_CIRCLE) {
#else
    if (event.key.keysym.sym == SDLK_d) {
#endif
      if (move.length > 0) {
        direction = moveLastDirection (&move);
        moveRemoveDirection (&move);
        gameApplyDirection (&engine->game, 7-direction);
        orientation.x = 0;
        orientation.y = 0;
        engine->board.arrow_orientation = getOrientation (&orientation);
        boardRefresh (&engine->board, &engine->game);
      }
    }

#ifdef _PSP_FW_VERSION
    if (pad.Buttons & PSP_CTRL_TRIANGLE) {
#else
    if (event.key.keysym.sym == SDLK_e) {
#endif
      if (move.length > 0) {
        for (i = move.length-1; i >= 0; -- i) {
          moveRemoveDirection (&move);
          gameApplyDirection (&engine->game, 7-move.sequence[i]);
        }
        orientation.x = 0;
        orientation.y = 0;
        engine->board.arrow_orientation = getOrientation (&orientation);
        boardRefresh (&engine->board, &engine->game);
      }
    }
    boardRefresh (&engine->board, &engine->game);
  }
  gameChangeSide (&engine->game);
  moveQuit (&move);
}


void engineIaTurn (engine_st *engine) {
  search_st search;

  searchInit (&search, &engine->game);
  searchRun (&search, &engine->game);
printf ("engineIaTurn serch done side=%d\n", search.side);
  movePrint (&(search.bestMove));
  gamePlay (&engine->game, &(search.bestMove));
    boardRefresh (&engine->board, &engine->game);
}


void engineQuit (engine_st *engine) {
  boardQuit (&engine->board);
}
