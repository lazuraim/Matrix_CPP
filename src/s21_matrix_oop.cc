#include "s21_matrix_oop.h"

int main() {
  S21Matrix matr(4, 4);
  S21Matrix matr2(4, 4);
  matr(0, 0) = 1;
  matr(0, 1) = 2;
  matr(0, 2) = 3;
  matr2(0, 0) = 1;
  matr2(0, 1) = 2;
  matr2(0, 2) = 3;
  S21Matrix matr3 = matr.SumMatrix(matr2);
  printf("%i\n", matr3(0, 2));
}

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.cols_ * sizeof(double));
}

/* S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
    if (rows_ * cols_ == other.rows_ * other.cols_) {
        std::memcpy(matrix_, other.matrix_, other.cols_ * other.rows_ *
sizeof(double)); } else { delete[] matrix_; matrix_ = new double[other.rows_ *
other.cols_](); std::memcpy(matrix_, other.matrix_, other.cols_ * other.rows_ *
sizeof(double));
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    delete other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
} */

S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = 0;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = 1;
  } else {
    for (auto i = 0; i < rows_ && result == 0 ; i++) {
      for (auto j = 0; j < cols_ && result == 0; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          result = 1;
        }
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(rows_, cols_);
  res.SumMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(rows_, cols_);
  res.SubMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

/*
// добавить другой порядок
S21Matrix S21Matrix::operator*(const S21Matrix& other) {


}



S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
     std::swap(matrix_, other.matrix_); // изучить метод
     return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix&& other) {
     std::move(matrix_, other.matrix_); // изучить метод
     return *this;
}

S21Matrix S21Matrix::operator==(const S21Matrix& other) {

}



int& S21Matrix::operator()(int row, int col) const {

}

void S21Matrix::MulMatrix(const S21Matrix& other) {

}


S21Matrix S21Matrix::Transpose() {


}


S21Matrix S21Matrix::CalcComplements() {

if (rows_ != cols_) {
        throw std::out_of_range(
            "Incorrect input, matrix should be square");
    }
}

double S21Matrix::Determinant() {

if (rows_ != cols_) {
        throw std::out_of_range(
            "Incorrect input, matrix should be square");
    }
}

S21Matrix S21Matrix::InverseMatrix() {

} */