#include "s21_matrix_oop.h"

int main() {
  // S21Matrix m(8, 6);
  // std::cout << "rows m = " << m.getRows() << "\ncols m = " << m.getCols() << std::endl;
  // S21Matrix m2;
  // std::cout << "rows m2 = " << m2.getRows() << "\ncols m2 = " << m2.getCols() << std::endl;
  // m2 = std::move(m);

  // std::cout << "______________" << std::endl;
  // std::cout << "rows m = " << m.getRows() << "\ncols m = " << m.getCols() << std::endl;
  // std::cout << "rows m2 = " << m2.getRows() << "\ncols m2 = " << m2.getCols() << std::endl;

  S21Matrix m1(1, 1);
  std::cout << "rows m1 = " << m1.getRows() << "\ncols m1 = " << m1.getCols() << std::endl;
  m1.setRows(3);
  m1.setCols(3);
  std::cout << "rows m1 = " << m1.getRows() << "\ncols m1 = " << m1.getCols() << std::endl;

}

S21Matrix::S21Matrix() : S21Matrix(3, 3) {
  std::cout << "default ctor " << this << std::endl;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
  std::cout << "parameter ctor " << this << std::endl;
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other) 
        : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  std::memcpy(matrix_, other.matrix_,
              rows_ * cols_ * sizeof(double));
              std::cout << "copy ctor" << this << std::endl;
}

// копирующий оператор присваивания
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    DestroyMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
    std::memcpy(matrix_, other.matrix_,
                rows_ * cols_ * sizeof(double));
  }
  std::cout << "copy assign = " << this << std::endl;
  return *this;
}

// конструктор перемещения
S21Matrix::S21Matrix(S21Matrix&& other) noexcept : 
        rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
  std::cout << "move ctor " << this << std::endl;
}

// перемещающий оператор присваивания
S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    DestroyMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  std::cout << "move assign = " << this << std::endl;
  return *this;
}

S21Matrix::~S21Matrix() {
  std::cout << "Destructor 1  " << this << std::endl;
  DestroyMatrix();
  std::cout << "Destructor 2 " << this << std::endl;
}

void S21Matrix::setRows(int new_rows) {
  if (new_rows < 0) {
    throw std::out_of_range(
      "Incorrect input, rows should not be negative");
  }
  if (new_rows != rows_) {
    S21Matrix tmp(new_rows, cols_);
    int rows_to_copy = std::min(new_rows, rows_);
    for (int i = 0; i < rows_to_copy; i++) {
        for (int j = 0; j < cols_; j++) {
            tmp(i, j) = (*this)(i, j);
        }
    }
    *this = std::move(tmp);
  }
}

void S21Matrix::setCols(int new_cols) {
  if (new_cols < 0) {
    throw std::out_of_range(
      "Incorrect input, cols should not be negative");
  }
  if (new_cols != cols_) {
    S21Matrix tmp(rows_, new_cols);
    int cols_to_copy = std::min(cols_, new_cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_to_copy; j++) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

int S21Matrix::getRows() {
  return rows_;
}
int S21Matrix::getCols() {
  return cols_;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = 1;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = 0;
  } else {
    for (auto i = 0; i < rows_ && result; i++) {
      for (auto j = 0; j < cols_ && result; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          result = 0;
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
      matrix_[i][j] += other.matrix_[i][j];
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
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix& other) {
  return !EqMatrix(other);
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix tmp = other * num;
  return tmp;
}

/*
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

void S21Matrix::CreateMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::DestroyMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
    }
    delete [] matrix_;
  }
}