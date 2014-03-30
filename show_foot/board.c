#include "board.h"


void boardInit (board_st *board) {
  board->screen = NULL;
  board->field = NULL;

  board->screen = SDL_SetVideoMode(480, 272, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  board->field = IMG_Load ("data/field.png");

  board->bar[East] = IMG_Load ("data/e_bar.png");
  board->bar[NorthEast] = IMG_Load ("data/ne_bar.png");
  board->bar[North] = IMG_Load ("data/n_bar.png");
  board->bar[NorthWest] = IMG_Load ("data/nw_bar.png");
  board->bar[West] = IMG_Load ("data/w_bar.png");
  board->bar[SouthWest] = IMG_Load ("data/sw_bar.png");
  board->bar[South] = IMG_Load ("data/s_bar.png");
  board->bar[SouthEast] = IMG_Load ("data/se_bar.png");
  board->bar[NoneOrientation] = IMG_Load ("data/null_bar.png");

  board->arrow_orientation = NoneOrientation;
  board->arrow[East] = IMG_Load ("data/arrow_e.png");
  board->arrow[NorthEast] = IMG_Load ("data/arrow_ne.png");
  board->arrow[North] = IMG_Load ("data/arrow_n.png");
  board->arrow[NorthWest] = IMG_Load ("data/arrow_nw.png");
  board->arrow[West] = IMG_Load ("data/arrow_w.png");
  board->arrow[SouthWest] = IMG_Load ("data/arrow_sw.png");
  board->arrow[South] = IMG_Load ("data/arrow_s.png");
  board->arrow[SouthEast] = IMG_Load ("data/arrow_se.png");
  board->arrow[NoneOrientation] = IMG_Load ("data/circle.png");
  board->arrow[Stop] = IMG_Load ("data/stop.png");
}


void boardRefresh (board_st *board, game_st *game) {
  int i,j,orientation;
  SDL_Rect coordinate;
  coordinate.x = 0;
  coordinate.y = 0;
  SDL_FillRect (board->screen, NULL, SDL_MapRGB(board->screen->format, 0, 0, 0));
  SDL_BlitSurface(board->field, NULL, board->screen, &coordinate);

  for (i = 0;i < MAX_CELL_X; i ++) {
    for (j = 0;j < MAX_CELL_Y; j ++) {
      coordinate.x = 30*i+86;
      coordinate.y = 30*j+12;

      /* draw points */
      if ((i>0) && (i<MAX_CELL_X-1) && (j>0) && (j<MAX_CELL_Y-1)) {
        SDL_BlitSurface(board->bar[NoneOrientation], NULL, board->screen, &coordinate);
      }

      /* draw lines */
      for (orientation = 0; orientation < 9; orientation ++) {
        if ( ((i==0) && ((orientation==West) || (orientation==NorthWest) || (orientation==SouthWest)|| (orientation==South)|| (orientation==North))) ||
             ((i==MAX_CELL_X-1) && ((orientation==East) || (orientation==NorthEast) || (orientation==SouthEast)|| (orientation==South)|| (orientation==North))) ||
             ((j==0) && ((orientation==North) || (orientation==NorthEast) || (orientation==NorthWest)|| (orientation==East)|| (orientation==West))) ||
             ((j==MAX_CELL_Y-1) && ((orientation==South) || (orientation==SouthEast) || (orientation==SouthWest)|| (orientation==East)|| (orientation==West))) )
            continue;

        if (game->link[i][j] & (1<<orientation)) {
          SDL_BlitSurface(board->bar[orientation], NULL, board->screen, &coordinate);
        }
      }
    }
  }

  boardRefreshArrow (board, 0);
  SDL_Flip (board->screen);
}


void boardRefreshArrow (board_st *board, int flip) {
  SDL_Rect coordinate;
  coordinate.x = 30;
  coordinate.y = 10;
  SDL_BlitSurface (board->arrow[board->arrow_orientation], NULL, board->screen, &coordinate);
  if (flip) {
    SDL_Flip (board->screen);
  }
}


void boardQuit (board_st *board) {
  int i;

  SDL_FreeSurface (board->screen);
  SDL_FreeSurface (board->field);

  for (i = 0 ; i < 9; i ++) {
    SDL_FreeSurface (board->bar[i]);
    SDL_FreeSurface (board->arrow[i]);
  }
  SDL_FreeSurface (board->arrow[Stop]);
}

/*void oslDrawLine(int x0, int y0, int x1, int y1, OSL_COLOR color)   {
    OSL_LINE_VERTEX* vertices;

    vertices = (OSL_LINE_VERTEX*)sceGuGetMemory(2 * sizeof(OSL_LINE_VERTEX));
    color = oslBlendColor(color);

    vertices[0].color = color;
    vertices[0].x = x0;
    vertices[0].y = y0;
    vertices[0].z = 0;

    vertices[1].color = color;
    vertices[1].x = x1;
    vertices[1].y = y1;
    vertices[1].z = 0;

    oslDisableTexturing();
    sceGuDrawArray(GU_LINES, GU_COLOR_8888|GU_VERTEX_16BIT|GU_TRANSFORM_2D, 2, 0, vertices);
}*/
