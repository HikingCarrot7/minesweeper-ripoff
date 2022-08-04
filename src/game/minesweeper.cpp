#include "minesweeper.hpp"

#include <algorithm>
#include <iostream>

#include "../utils/math_helper.hpp"

const Difficulty Minesweeper::BEGGINER = Difficulty(9, 9, 10, 10);
const Difficulty Minesweeper::INTERMEDIATE = Difficulty(16, 16, 40, 40);
const Difficulty Minesweeper::EXPERT = Difficulty(16, 30, 99, 99);

Minesweeper::Minesweeper() {}

Minesweeper::Minesweeper(Difficulty difficulty) {
  createGame(difficulty);
}

void Minesweeper::resetGame() {
  placed_flags_ = 0;
  game_over_ = false;
  for (int i = 0; i < board_->getTotalTiles(); i++) {
    std::shared_ptr<Tile>& tile = board_->getTile(i);
    tile->reset();
  }
  placeBombs();
  shuffleBombs();
  updateAdjacentBombsPerTile();
}

void Minesweeper::createGame(Difficulty difficulty) {
  board_ = std::make_shared<Board>(difficulty.rows, difficulty.cols);
  max_bombs_ = difficulty.max_bombs;
  max_flags_ = difficulty.max_flags;
  placed_flags_ = 0;
  game_over_ = false;
  placeBombs();
  shuffleBombs();
  updateAdjacentBombsPerTile();
}

void Minesweeper::placeBombs() {
  for (int i = 0; i < max_bombs_; i++) {
    std::shared_ptr<Tile>& tile = board_->getTile(i);
    tile->is_bomb = true;
  }
}

void Minesweeper::shuffleBombs() {
  for (int i = 0; i < max_bombs_; i++) {
    int row = MathHelper::randomInt(0, board_->getRows() - 1);
    int col = MathHelper::randomInt(0, board_->getCols() - 1);
    std::shared_ptr<Tile>& tile = board_->getTile(i);
    std::shared_ptr<Tile>& random_tile = board_->getTile(row, col);
    std::swap(tile, random_tile);
  }
}

void Minesweeper::uncoverTile(int row, int col) {
  std::shared_ptr<Tile> tile = board_->getTile(row, col);
  if (tile->is_flagged) {
    toggleFlagged(row, col);
    return;
  }
  uncoverTile(tile);
  if (tile->is_bomb) {
    game_over_ = true;
  }
}

void Minesweeper::uncoverTile(std::shared_ptr<Tile> tile) {
  tile->uncover();
  if (tile->isEmpty()) {
    TileVector adjacent_tiles = board_->getAdjacentTiles(tile);
    TileVector covered_tiles;
    std::copy_if(adjacent_tiles.begin(), adjacent_tiles.end(), std::back_inserter(covered_tiles),
                 [](const auto& tile) { return tile->is_covered; });
    std::for_each(covered_tiles.begin(), covered_tiles.end(), [&](const auto& tile) { uncoverTile(tile); });
  }
}

void Minesweeper::toggleFlagged(int row, int col) {
  std::shared_ptr<Tile>& tile = board_->getTile(row, col);
  if (!tile->is_flagged && placed_flags_ == max_flags_) {
    return;
  }
  tile->toggleFlagged();
  if (tile->is_covered) {
    placed_flags_ += tile->is_flagged ? 1 : -1;
  }
}

void Minesweeper::updateAdjacentBombsPerTile() {
  TilesWithCoordVector all_tiles = board_->getAllTilesWithCoord();
  for (const auto& pair : all_tiles) {
    std::shared_ptr<Tile> tile = pair.first;
    if (tile->is_bomb) {
      continue;
    }
    int n_adjacent_bombs = getAdjacentBombs(tile).size();
    tile->n_adjacent_bombs = n_adjacent_bombs;
  }
}

TileVector Minesweeper::getAdjacentBombs(std::shared_ptr<Tile> tile) {
  TileVector adjacent_tiles = board_->getAdjacentTiles(tile);
  TileVector adjacent_bombs;
  std::copy_if(adjacent_tiles.begin(), adjacent_tiles.end(), std::back_inserter(adjacent_bombs),
               [](const auto& tile) { return tile->is_bomb; });
  return adjacent_bombs;
}

TilesWithCoordVector Minesweeper::getRemainingUncoveredBombs() {
  TilesWithCoordVector all_tiles = board_->getAllTilesWithCoord();
  TilesWithCoordVector uncovered_bombs;
  std::copy_if(all_tiles.begin(), all_tiles.end(), std::back_inserter(uncovered_bombs), [](const auto& pair) {
    std::shared_ptr<Tile> tile = pair.first;
    return tile->is_bomb && !tile->is_flagged;
  });
  return uncovered_bombs;
}

bool Minesweeper::allBombsLocated() {
  return getRemainingUncoveredBombs().empty();
}

bool Minesweeper::isGameOver() {
  if (allBombsLocated()) {
    return true;
  }
  return game_over_;
}

std::shared_ptr<const Board> Minesweeper::getBoard() {
  return board_;
}

int Minesweeper::getPlacedFlags() const {
  return placed_flags_;
}

int Minesweeper::getMaxFlags() const {
  return max_flags_;
}

Minesweeper::GameOverStatus Minesweeper::getGameOverStatus() {
  bool player_win = allBombsLocated();
  return GameOverStatus(player_win, !player_win);
}
