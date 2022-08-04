#ifndef BOMB_H
#define BOMB_H

#include <string>

class Tile {
 public:
  static const std::string EMPTY_TILE_REPRESENTATION;
  static const std::string TILE_WITH_BOMB_REPRESENTATION;
  static const std::string FLAGGED_TILE_REPRESENTATION;
  static const std::string COVERED_TILE_REPRESENTATION;

  int n_adjacent_bombs;
  bool is_bomb;
  bool is_flagged;
  bool is_covered;
  std::string representation;

  Tile();
  void reset();
  void uncover();
  void toggleFlagged();
  void updateTileRepresentation();
  bool isEmpty();
};

#endif
