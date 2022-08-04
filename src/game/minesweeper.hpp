#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <memory>

#include "../core/board.hpp"
#include "../core/difficulty.hpp"

class Minesweeper {
 private:
  bool game_over_;
  int max_bombs_;
  int max_flags_;
  int placed_flags_;
  std::shared_ptr<Board> board_;

  void placeBombs();
  void shuffleBombs();
  void updateAdjacentBombsPerTile();
  void uncoverTile(std::shared_ptr<Tile>);

 public:
  struct GameOverStatus {
    bool player_win;
    bool player_lose;

    GameOverStatus(bool p_w, bool p_l) : player_win(p_w), player_lose(p_l) {}
  };

  static const Difficulty BEGGINER;
  static const Difficulty INTERMEDIATE;
  static const Difficulty EXPERT;

  Minesweeper();
  Minesweeper(Difficulty);
  void createGame(Difficulty difficulty);
  void resetGame();
  void uncoverTile(int, int);
  void toggleFlagged(int, int);
  TileVector getAdjacentBombs(std::shared_ptr<Tile>);
  TilesWithCoordVector getRemainingUncoveredBombs();
  bool allBombsLocated();
  bool isGameOver();
  std::shared_ptr<const Board> getBoard();
  int getPlacedFlags() const;
  int getMaxFlags() const;
  GameOverStatus getGameOverStatus();
};

#endif
