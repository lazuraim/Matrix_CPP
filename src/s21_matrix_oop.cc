#include "s21_matrix_oop.h"

namespace s21 {

S21Matrix::S21Matrix() { Nulling(); }

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range("Incorrect input, rows should not be less than 1");
  }
  rows_ = rows;
  cols_ = cols;
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    DestroyMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
    std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
  }
  return *this;
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.Nulling();
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    DestroyMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.Nulling();
  }
  return *this;
}

S21Matrix::~S21Matrix() { DestroyMatrix(); }

int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int new_rows) {
  if (new_rows < 1) {
    throw std::out_of_range("Incorrect input, rows should not be less than 1");
  }
  if (new_rows != rows_) {
    if (rows_ == 0 || cols_ == 0) {
      rows_ = new_rows;
    } else {
      S21Matrix tmp(new_rows, cols_);
      int rows_to_copy = std::min(new_rows, rows_);
      for (int i = 0; i < rows_to_copy; ++i) {
        for (int j = 0; j < cols_; ++j) {
          tmp(i, j) = (*this)(i, j);
        }
      }
      *this = std::move(tmp);
    }
  }
}

void S21Matrix::setCols(int new_cols) {
  if (new_cols < 1) {
    throw std::out_of_range("Incorrect input, cols should not be less than 1");
  }
  if (new_cols != cols_) {
    if (rows_ == 0 || cols_ == 0) {
      cols_ = new_cols;
    } else {
      S21Matrix tmp(rows_, new_cols);
      int cols_to_copy = std::min(cols_, new_cols);
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_to_copy; ++j) {
          tmp(i, j) = (*this)(i, j);
        }
      }
      *this = std::move(tmp);
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  const double kEpsilon = 1e-7;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return 0;
  } else {
    for (auto i = 0; i < rows_; ++i) {
      for (auto j = 0; j < cols_; ++j) {
        if (((*this)(i, j) - other(i, j)) > kEpsilon) {
          return 0;
        }
      }
    }
  }
  return 1;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "The number of cols of the 1st matrix is not equal to the number of "
        "rows of the 2nd matrix");
  }
  int dimension = cols_;
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      tmp.matrix_[i * other.cols_ + j] = 0;
      for (int z = 0; z < dimension; ++z) {
        tmp.matrix_[i * other.cols_ + j] +=
            matrix_[i * dimension + z] * other.matrix_[z * other.cols_ + j];
      }
    }
  }
  *this = std::move(tmp);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      tmp.matrix_[j * rows_ + i] = matrix_[i * cols_ + j];
    }
  }
  return tmp;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect input, matrix should be square");
  }
  double result = 0.0;
  if (rows_ == 1) {
    return (*this)(0, 0);
  } else if (rows_ == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  } else if (rows_ > 2) {
    S21Matrix algebraic_compl = (*this).CalcComplements();
    for (int i = 0; i < rows_; ++i) {
      result += (*this)(i, 0) * algebraic_compl(i, 0);
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect input, matrix should be square");
  }
  double minor = 0.0;
  S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
  S21Matrix algebraic_compl(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      FillMinorMatrix(i, j, minor_matrix);
      minor = minor_matrix.Determinant();
      algebraic_compl(i, j) = minor * pow(-1, (i + j));
    }
  }
  return algebraic_compl;
}

void S21Matrix::FillMinorMatrix(int current_row, int current_col,
                                S21Matrix &minor_matrix) const {
  int minor_rows = 0;
  for (int i = 0; i < rows_; ++i) {
    int minor_cols = 0;
    for (int j = 0; j < cols_; ++j) {
      if (i != current_row && j != current_col) {
        minor_matrix(minor_rows, minor_cols) = (*this)(i, j);
        ++minor_cols;
      }
    }
    if (i != current_row) {
      ++minor_rows;
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() const {
  const double kEpsilon = 1e-7;
  double determinant = Determinant();
  if (fabs(determinant) < kEpsilon) {
    throw std::logic_error("Matrix determinant is 0");
  }
  S21Matrix transposed = Transpose().CalcComplements();
  return (1.0 / determinant) * transposed;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix &other) const {
  return !EqMatrix(other);
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix operator*(const double num, const S21Matrix &other) {
  S21Matrix tmp = other * num;
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return (*this);
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

void S21Matrix::CreateMatrix() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range(
        "Incorrect input, rows and cols cannot be less than 1");
  }
  matrix_ = new double[rows_ * cols_]();
}

void S21Matrix::DestroyMatrix() {
  if (matrix_) {
    delete[] matrix_;
  }
  Nulling();
}

void S21Matrix::Nulling() {
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

}  // namespace s21