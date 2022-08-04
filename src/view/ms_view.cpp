#include "ms_view.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <sstream>

MsView::MsView(Minesweeper& ms) {
  ms_ = &ms;
}

void MsView::renderGame() {
  initScreen();
  initColors();
  WINDOW* win = createWindow();
  wrefresh(win);
  bool back_to_menu = true;
  while (1) {
    if (back_to_menu) {
      bool quit = menu(win);
      wclear(win);
      resetCursorPos();
      if (quit) break;
    }
    while (!ms_->isGameOver()) {
      drawBoard(win);
      back_to_menu = handleInput(win);
      if (back_to_menu) break;
    }
    if (!back_to_menu) {
      drawBoard(win);
      bool play_again = showGameOver(win, ms_->getGameOverStatus());
      if (play_again) {
        ms_->resetGame();
        resetCursorPos();
      }
      if (!play_again) {
        back_to_menu = true;
      }
    }
  }

  endwin();
}

bool MsView::menu(WINDOW* win) {
  std::vector<std::string> options = {"BEGGINER", "INTERMEDIATE", "EXPERT", "QUIT"};
  wclear(win);
  resetCursorPos();
  box(win, 0, 0);
  mvwprintw(win, 0, 1, "|Select difficulty...|");
  while (1) {
    for (int i = 0; i < options.size(); i++) {
      if (i == cursor_pos_.y) {
        wattron(win, A_REVERSE);
      }
      std::string option = options[i];
      mvwprintw(win, 1 + i, 1, option.c_str());
      wattroff(win, A_REVERSE);
    }
    int input = wgetch(win);
    updateCursorPos(input, options.size() - 1, 0);
    if (input == VK_ENTER) {
      switch (cursor_pos_.y) {
        case 0:
          ms_->createGame(Minesweeper::BEGGINER);
          break;
        case 1:
          ms_->createGame(Minesweeper::INTERMEDIATE);
          break;
        case 2:
          ms_->createGame(Minesweeper::EXPERT);
          break;
        default:
          return true;
          break;
      }
      return false;
    }
  }
}

void MsView::drawBoard(WINDOW* win) {
  std::shared_ptr<const Board> board = ms_->getBoard();
  box(win, 0, 0);
  mvwprintw(win, 0, 1, "|Flags %d/%d|", ms_->getPlacedFlags(), ms_->getMaxFlags());
  for (int y = 0; y < board->getRows(); y++) {
    for (int x = 0; x < board->getCols(); x++) {
      std::shared_ptr<Tile>& tile = board->getTile(y, x);
      bool is_cursor_pos = y == cursor_pos_.y && x == cursor_pos_.x;
      if (is_cursor_pos) {
        wattron(win, COLOR_PAIR(20));
      }
      drawTile(win, tile, y, x, !is_cursor_pos);
      wattroff(win, COLOR_PAIR(20));
    }
  }
}

void MsView::drawTile(WINDOW* win, std::shared_ptr<Tile>& tile, int y, int x, bool dye = true) {
  mvwprintw(win, 1 + y, 1 + x * TILE_WIDTH, "[");
  int color_pair_id = UNCOVER_TILE_COLOR_PAIR_ID;
  if (!tile->is_covered) {
    if (tile->is_bomb) {
      color_pair_id = BOMB_COLOR_PAIR_ID;
    } else if (!tile->isEmpty()) {
      color_pair_id = tile->n_adjacent_bombs;
    }
  }
  if (tile->is_flagged) {
    color_pair_id = FLAGGED_TILE_COLOR_PAIR_ID;
  }
  if (dye) {
    wattron(win, COLOR_PAIR(color_pair_id));
  }
  mvwprintw(win, 1 + y, 2 + x * TILE_WIDTH, tile->representation.c_str());
  if (dye) {
    wattroff(win, COLOR_PAIR(color_pair_id));
  }
  mvwprintw(win, 1 + y, 3 + x * TILE_WIDTH, "]");
}

bool MsView::handleInput(WINDOW* win) {
  std::shared_ptr<const Board> board = ms_->getBoard();
  int input = wgetch(win);
  updateCursorPos(input, board->getRows() - 1, board->getCols() - 1);
  switch (input) {
    case 'f':
      ms_->toggleFlagged(cursor_pos_.y, cursor_pos_.x);
      break;
    case 'r':
      ms_->resetGame();
      resetCursorPos();
      break;
    case 'q':
      return true;
    case ' ':
    case VK_ENTER:
      ms_->uncoverTile(cursor_pos_.y, cursor_pos_.x);
      break;
    default:
      break;
  }
  return false;
}

bool MsView::showGameOver(WINDOW* win, Minesweeper::GameOverStatus go_status) {
  mvwprintw(win, 0, 1, "|%s Play again? (y/n)|", go_status.player_win ? "You win!" : "You hit a bomb :(");
  while (1) {
    int option = wgetch(win);
    switch (option) {
      case 'y':
        return true;
      case 'n':
        return false;
      default:
        break;
    }
  }
}

void MsView::initScreen() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  getmaxyx(stdscr, max_y_, max_x_);
}

void MsView::initColors() {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
  init_pair(6, COLOR_WHITE, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  init_pair(BOMB_COLOR_PAIR_ID, COLOR_RED, COLOR_BLACK);
  init_pair(CURSOR_COLOR_PAIR_ID, COLOR_BLACK, COLOR_WHITE);
  init_pair(UNCOVER_TILE_COLOR_PAIR_ID, COLOR_WHITE, COLOR_BLACK);
  init_pair(FLAGGED_TILE_COLOR_PAIR_ID, COLOR_RED, COLOR_BLACK);
}

WINDOW* MsView::createWindow() {
  return newwin(max_y_, max_x_, 0, 0);
}

void MsView::updateCursorPos(int input, int max_y_pos, int max_x_pos) {
  switch (input) {
    case 'j':
      cursor_pos_.y = std::min(cursor_pos_.y + 1, max_y_pos);
      break;
    case 'k':
      cursor_pos_.y = std::max(cursor_pos_.y - 1, 0);
      break;
    case 'l':
      cursor_pos_.x = std::min(cursor_pos_.x + 1, max_x_pos);
      break;
    case 'h':
      cursor_pos_.x = std::max(cursor_pos_.x - 1, 0);
      break;
  }
}

void MsView::resetCursorPos() {
  cursor_pos_.x = 0;
  cursor_pos_.y = 0;
}
