#include "tile.hpp"

#include <sstream>

const std::string Tile::EMPTY_TILE_REPRESENTATION = " ";
const std::string Tile::TILE_WITH_BOMB_REPRESENTATION = "O";
const std::string Tile::FLAGGED_TILE_REPRESENTATION = "F";
const std::string Tile::COVERED_TILE_REPRESENTATION = ".";

Tile::Tile() {
  reset();
}

void Tile::reset() {
  n_adjacent_bombs = 0;
  is_bomb = false;
  is_flagged = false;
  is_covered = true;
  representation = COVERED_TILE_REPRESENTATION;
}

void Tile::uncover() {
  is_covered = false;
  updateTileRepresentation();
}

void Tile::toggleFlagged() {
  if (!is_covered) {
    return;
  }
  is_flagged = !is_flagged;
  representation = is_flagged ? FLAGGED_TILE_REPRESENTATION : COVERED_TILE_REPRESENTATION;
}

void Tile::updateTileRepresentation() {
  representation = std::to_string(n_adjacent_bombs);
  if (is_bomb) {
    representation = TILE_WITH_BOMB_REPRESENTATION;
  }
  if (isEmpty()) {
    representation = EMPTY_TILE_REPRESENTATION;
  }
}

bool Tile::isEmpty() {
  return !is_bomb && !is_flagged && n_adjacent_bombs == 0;
}
