#ifndef MS_VIEW_H
#define MS_VIEW_H

#include "../game/minesweeper.hpp"
#include "ncurses.h"

#define TILE_WIDTH 3
#define BOMB_COLOR_PAIR_ID 10
#define CURSOR_COLOR_PAIR_ID 20
#define UNCOVER_TILE_COLOR_PAIR_ID 30
#define FLAGGED_TILE_COLOR_PAIR_ID 40

struct CursorPos {
  int x = 0;
  int y = 0;
};

class MsView {
 private:
  const static int VK_ENTER = 10;
  int max_x_;
  int max_y_;
  CursorPos cursor_pos_;
  Minesweeper* ms_;

  void initScreen();
  void initColors();
  WINDOW* createWindow();
  bool menu(WINDOW*);
  void drawBoard(WINDOW*);
  void drawTile(WINDOW*, std::shared_ptr<Tile>&, int, int, bool dye);
  bool handleInput(WINDOW*);
  bool showGameOver(WINDOW*, Minesweeper::GameOverStatus);
  void updateCursorPos(int, int, int);
  void resetCursorPos();

 public:
  MsView(Minesweeper&);
  void renderGame();
};

#endif
