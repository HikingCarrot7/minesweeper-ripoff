#ifndef DIFFICULTY_H
#define DIFFICULTY_H

struct Difficulty {
  int rows;
  int cols;
  int max_bombs;
  int max_flags;

  Difficulty(int rows, int cols, int max_bombs, int max_flags) {
    this->rows = rows;
    this->cols = cols;
    this->max_bombs = max_bombs;
    this->max_flags = max_flags;
  }
};

#endif
