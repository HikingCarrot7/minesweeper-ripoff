#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <utility>

#include "../utils/matrix_2d.hpp"
#include "coord.hpp"
#include "tile.hpp"

typedef std::vector<std::shared_ptr<Tile>> TileVector;
typedef std::vector<std::pair<std::shared_ptr<Tile>, Coord>> TilesWithCoordVector;

class Board {
 private:
  std::unique_ptr<Matrix2D<std::shared_ptr<Tile>>> board_;
  void initBoard();

 public:
  Board(int, int);
  ~Board();
  std::vector<std::shared_ptr<Tile>> getAdjacentTiles(std::shared_ptr<Tile>);
  Coord getTileCoord(std::shared_ptr<Tile>);
  TilesWithCoordVector getAllTilesWithCoord();
  std::shared_ptr<Tile>& getTile(int, int) const;
  std::shared_ptr<Tile>& getTile(int) const;
  int getRows() const;
  int getCols() const;
  int getTotalTiles() const;
};

#endif
