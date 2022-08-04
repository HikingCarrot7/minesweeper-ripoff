#include "board.hpp"

#include <algorithm>

Board::Board(int rows, int cols) {
  board_ = std::make_unique<Matrix2D<std::shared_ptr<Tile>>>(rows, cols);
  initBoard();
}

Board::~Board() {}

void Board::initBoard() {
  for (int row = 0; row < getRows(); row++) {
    for (int col = 0; col < getCols(); col++) {
      board_->put(std::make_shared<Tile>(), row, col);
    }
  }
}

std::vector<std::shared_ptr<Tile>> Board::getAdjacentTiles(std::shared_ptr<Tile> tile) {
  Coord tile_coord = getTileCoord(tile);
  std::vector<std::shared_ptr<Tile>> adjacent_tiles;
  for (int row = std::max(0, tile_coord.row - 1); row < std::min(getRows(), tile_coord.row + 2); row++) {
    for (int col = std::max(0, tile_coord.col - 1); col < std::min(getCols(), tile_coord.col + 2); col++) {
      std::shared_ptr<Tile>& adjacent_tile = getTile(row, col);
      if (adjacent_tile != tile) {
        adjacent_tiles.push_back(adjacent_tile);
      }
    }
  }
  return adjacent_tiles;
}

Coord Board::getTileCoord(std::shared_ptr<Tile> tile) {
  TilesWithCoordVector all_tiles = getAllTilesWithCoord();
  for (const auto& pair : all_tiles) {
    if (pair.first == tile) {
      return pair.second;
    }
  }
  throw "Tile not found!";
}

TilesWithCoordVector Board::getAllTilesWithCoord() {
  TilesWithCoordVector all_tiles;
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getCols(); j++) {
      all_tiles.push_back(std::pair<std::shared_ptr<Tile>, Coord>(getTile(i, j), Coord(i, j)));
    }
  }
  return all_tiles;
}

std::shared_ptr<Tile>& Board::getTile(int row, int col) const {
  return board_->at(row, col);
}

std::shared_ptr<Tile>& Board::getTile(int pos) const {
  return board_->at(pos);
}

int Board::getRows() const {
  return board_->getRows();
}

int Board::getCols() const {
  return board_->getCols();
}

int Board::getTotalTiles() const {
  return getRows() * getCols();
}
