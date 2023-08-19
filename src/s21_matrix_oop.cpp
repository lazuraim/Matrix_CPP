#include "s21_matrix_oop.h"

int main() {
  S21Matrix m1(5, 3);
  double count = 1;
  std::cout << m1.getRows() << "\n";
  std::cout << m1.getCols() << "\n";
  for (int i = 0; i < m1.getRows(); i++) {
    for (int j = 0; j < m1.getCols(); j++) {
      m1(i, j) = count;
      count++;
    }
  }
  // S21Matrix m2(3, 4);

  // double mnoj = 5;
  // for (int i = 0; i < m2.getRows(); i++) {
  //   for (int j = 0; j < m2.getCols(); j++) {
  //     m2(i, j) = mnoj;
  //     mnoj += 2;
  //   }
  // }

  for (int i = 0; i < m1.getRows(); i++) {
    for (int j = 0; j < m1.getCols(); j++) {
      std::cout << "m1(" << i << ", " << j << ") = " << m1(i, j) << " | " << " ";
    }
    std::cout << "\n";
  }
  // std::cout << "\n";
  // for (int i = 0; i < m2.getRows(); i++) {
  //   for (int j = 0; j < m2.getCols(); j++) {
  //     std::cout << "m2(" << i << ", " << j << ") = " << m2(i, j) << " | " << " ";
  //   }
  //   std::cout << "\n";
  // }

  //m1.MulMatrix(m2);

  m1.Transpose();

  for (int i = 0; i < m1.getRows(); i++) {
    for (int j = 0; j < m1.getCols(); j++) {
      std::cout << "m1(" << i << ", " << j << ") = " << m1(i, j) << " | " << " ";
    }
    std::cout << "\n";
  }

}

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
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
        if ((*this)(i, j) != other(i, j)) {
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
      (*this)(i, j) += other(i, j);
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
      (*this)(i, j) -= other(i, j);
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
  return matrix_[row * cols_ + col];
}

double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
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

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("The number of cols of the 1st matrix is not equal to the number of rows of the 2nd matrix");
  }
  int dimension = cols_;
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      tmp.matrix_[i * other.cols_ + j] = 0;
      for (int z = 0; z < dimension; z++) {
        tmp.matrix_[i * other.cols_ + j] += matrix_[i * dimension + z] * other.matrix_[z * other.cols_ + j];
      }
    }
  }
  *this = std::move(tmp);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[j * rows_ + i] = matrix_[i * cols_ + j];
    }
  }
  *this = std::move(tmp);
  return *this;
}

/*

double S21Matrix::Determinant() {
    if (rows_ != cols_) {
        throw std::out_of_range(
            "Incorrect input, matrix should be square");
    }
}

S21Matrix S21Matrix::CalcComplements() {
    if (rows_ != cols_) {
        throw std::out_of_range(
            "Incorrect input, matrix should be square");
    }
}

S21Matrix S21Matrix::InverseMatrix() {

} */

void S21Matrix::CreateMatrix() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Incorrect input, rows and cols cannot be less than 1");
  }
  matrix_ = new double[rows_ * cols_]();
}

void S21Matrix::DestroyMatrix() {
  if (matrix_) {
    delete [] matrix_;
  }
}