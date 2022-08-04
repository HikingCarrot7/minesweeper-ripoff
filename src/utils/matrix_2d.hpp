#ifndef MATRIX_2D_H
#define MATRIX_2D_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Matrix2D {
 private:
  int rows_;
  int cols_;
  std::unique_ptr<std::vector<T>> items_;

 public:
  Matrix2D(int rows = 1, int cols = 1) {
    rows_ = rows;
    cols_ = cols;
    items_ = std::make_unique<std::vector<T>>();
    items_->reserve(rows * cols);
  }

  Matrix2D(int rows, int cols, T& default_value) : Matrix2D(rows, cols) {
    for (int i = 0; i < rows_ * cols_; i++) {
      items_->push_back(default_value);
    }
  }

  Matrix2D(int rows, int cols, T&& default_value) : Matrix2D(rows, cols, default_value) {}

  ~Matrix2D() {
    items_->clear();
  }

  void put(T& value, int row, int col) {
    checkBounds(row, col);
    items_->insert(items_->begin() + getIndex(row, col), value);
  }

  void put(T&& value, int row, int col) {
    checkBounds(row, col);
    items_->insert(items_->begin() + getIndex(row, col), std::move(value));
  }

  T& at(int row, int col) {
    checkBounds(row, col);
    return items_->at(getIndex(row, col));
  }

  T& at(int pos) {
    if (pos < 0 || pos >= rows_ * cols_) {
      throw "Index out of bounds!";
    }
    return items_->at(pos);
  }

  int getIndex(int row, int col) {
    return row * cols_ + col;
  }

  void checkBounds(int row, int col) {
    if (row < 0 || row >= rows_) {
      throw "Row is out of bounds!";
    }
    if (col < 0 || col >= cols_) {
      throw "Col is out of bounds!";
    }
  }

  int getRows() {
    return rows_;
  }

  int getCols() {
    return cols_;
  }

  std::vector<T>& getItems() {
    return items_;
  }

  void print() {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        std::cout << "[" << at(i, j) << "] ";
      }
      std::cout << std::endl;
    }
  }
};

#endif
