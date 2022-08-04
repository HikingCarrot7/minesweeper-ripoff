#ifndef COORD_H
#define COORD_H

#include <ostream>

struct Coord {
  int row;
  int col;

  Coord(int r, int c) : row(r), col(c) {}

  friend std::ostream& operator<<(std::ostream& output, const Coord& coord) {
    output << "[" << coord.row << ", " << coord.col << "] ";
    return output;
  }
};

#endif
