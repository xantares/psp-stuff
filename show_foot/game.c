#include "game.h"


void gameInit (game_st *game) {
  int i, j;

  game->side = WhiteSide;
  game->isOver = 0;
  game->winner = NoneSide;
  game->position.x = MAX_CELL_X / 2;
  game->position.y = MAX_CELL_Y / 2;

  for (i = 0; i < MAX_CELL_X; ++ i) {
    for (j = 0; j < MAX_CELL_Y; ++ j) {
      game->link[i][j] = 0;
      if (i == 0) {
        game->link[i][j] |= (1<<West) | (1<<NorthWest) | (1<<SouthWest) | (1<<North) | (1<<South);
      }
      if (i == MAX_CELL_X-1) {
        game->link[i][j] |= (1<<East)| (1<<NorthEast) | (1<<SouthEast) | (1<<North) | (1<<South);
      }
      if (j == 0) {
        game->link[i][j] |= (1<<North) | (1<<NorthWest) | (1<<NorthEast) | (1<<West) | (1<<East);
      }
      if (j == MAX_CELL_Y-1) {
        game->link[i][j] |= (1<<South) | (1<<SouthEast) | (1<<SouthWest) | (1<<West) | (1<<East);
      }
    }
  }
  game->link[0][MAX_CELL_Y/2] = 0;
  game->link[MAX_CELL_X-1][MAX_CELL_Y/2] = 0;
}


void gameApplyDirection (game_st *game, unsigned int direction) {
  int offsetX[8];
  int offsetY[8];
  coord_st destination;

  offsetX[East] = 1;
  offsetX[NorthEast] = 1;
  offsetX[North] = 0;
  offsetX[NorthWest] = -1;
  offsetX[West] = -1;
  offsetX[SouthWest] = -1;
  offsetX[South] = 0;
  offsetX[SouthEast] = 1;

  offsetY[East] = 0;
  offsetY[NorthEast] = -1;
  offsetY[North] = -1;
  offsetY[NorthWest] = -1;
  offsetY[West] = 0;
  offsetY[SouthWest] = 1;
  offsetY[South] = 1;
  offsetY[SouthEast] = 1;

  if (game != NULL) {
    destination.x = game->position.x;
    destination.y = game->position.y;
    if (direction < 8) {
      /*printf ("gameApplyDirection.before game.pos=[%d %d]\n",game->position.x,game->position.y);*/
      destination.x += offsetX [direction];
      destination.y += offsetY [direction];
      game->link[game->position.x][game->position.y] ^= 1<<direction;
      game->link[destination.x][destination.y] ^= 1<<(7-direction);
      game->position = destination;
      /*printf ("gameApplyDirection.after %d game.pos=[%d %d]\n",direction, game->position.x,game->position.y);*/
    }
    else {
      printf ("error - gameApplyDirection direction=%d\n", direction); exit(4);
    }
  }
  else {
    printf ("error - gameApplyDirection game=NULL\n"); exit(4);
  }
}


void gameChangeSide (game_st *game) {
  game->side = (game->side == WhiteSide) ? BlackSide : WhiteSide;
}


void gamePlay (game_st *game, move_st *move) {
  int i;
  for (i = 0; i < move->length; ++ i) {
    gameApplyDirection (game, move->sequence[i]);
  }
  gameChangeSide (game);
}


void gameCancel (game_st *game, move_st *move) {
  int i;
  for (i = move->length-1; i >= 0; -- i) {
    gameApplyDirection (game, 7-move->sequence[i]);
  }
  gameChangeSide (game);
}


void gameCheckOver (game_st *game) {
  if (((game->position.x == 0) || (game->position.x == MAX_CELL_X-1)) && (game->position.y == MAX_CELL_Y/2)) {
    game->isOver = 1;
    if (game->position.x == 0) {
      game->winner = WhiteSide;
    }
    else {
      game->winner = BlackSide;
    }
    printf ("winner=%d\n", game->winner);
  }
  else {
    game->isOver = 0;
  }
}


int gameEvaluate (game_st *game, int side) {
  int deltaX, deltaY;
/*printf ("gameEvaluate side=%d\n", side);*/
  if (side == BlackSide) {
    deltaX = (game->position.x);
  }
  else {
    deltaX = (MAX_CELL_X-1-game->position.x);
  }
  deltaY = MAX_CELL_Y/2-game->position.y;
  return -(deltaX*deltaX+deltaY*deltaY);
}



int gameNumberOfLink (game_st *game) {
  int count = 0, direction;

  for (direction = 0; direction < 8; ++ direction) {
    if (gameHasLink (game, direction)) {
      ++ count;
    }
  }

  return count;
}


int gameHasLink (game_st *game, int direction) {
  int hasLink = 0;

  if (direction < 8) {
    if (game->link[game->position.x][game->position.y] & (1<<direction)) {
      hasLink = 1;
    }
  }
  else {
    printf ("error - gameHasLink direction=%d\n", direction); exit(4);
  }

  return hasLink;
}


int getOrientation (coord_st *coord) {
  const int ref[3][3] = {{NorthWest,  West,  SouthWest}, {North,  NoneOrientation,  South}, {NorthEast,  East, SouthEast}};
  return ref[1+coord->x][1+coord->y];
}
