#include "s21_matrix_oop.h"

// int main() {
//   S21Matrix m1(5, 5);
//   //double count = 1;
//   std::cout << m1.getRows() << "\n";
//   std::cout << m1.getCols() << "\n";
//   for (int i = 0; i < m1.getRows(); i++) {
//     for (int j = 0; j < m1.getCols(); j++) {
//       m1(i, j) = rand() % 10;
//     }
//   }

//   for (int i = 0; i < m1.getRows(); i++) {
//     for (int j = 0; j < m1.getCols(); j++) {
//       std::cout << "m1(" << i << ", " << j << ") = " << m1(i, j) << " | " << " ";
//     }
//     std::cout << "\n";
//   }
//   S21Matrix inversed = m1.InverseMatrix();

//   for (int i = 0; i < inversed.getRows(); i++) {
//     for (int j = 0; j < inversed.getCols(); j++) {
//       std::cout << "m1(" << i << ", " << j << ") = " << inversed(i, j) << " | " << " ";
//     }
//     std::cout << "\n";
//   }
// }

// написать почему матрица нулевая

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other) 
        : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  std::memcpy(matrix_, other.matrix_,
              rows_ * cols_ * sizeof(double));
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
  return *this;
}

// конструктор перемещения
S21Matrix::S21Matrix(S21Matrix&& other) noexcept : 
        rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
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
  return *this;
}

S21Matrix::~S21Matrix() {
  DestroyMatrix();
}

int S21Matrix::getRows() const {
  return rows_;
}

int S21Matrix::getCols() const {
  return cols_;
}

void S21Matrix::setRows(int new_rows) {
  if (new_rows < 1) {
    throw std::out_of_range(
      "Incorrect input, rows should not be less than 0");
  }
  if (new_rows != rows_) {
    if (rows_ == 0 || cols_ == 0) {
    	rows_ = new_rows;
    } else {
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
}

void S21Matrix::setCols(int new_cols) {
  if (new_cols < 1) {
    throw std::out_of_range(
      "Incorrect input, cols should not be less than 0");
  }
  if (new_cols != cols_) {
	if (rows_ == 0 || cols_ == 0) {
		cols_ = new_cols;
        } else {
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
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = 1;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = 0;
  } else {
    for (auto i = 0; i < rows_ && result; ++i) {
      for (auto j = 0; j < cols_ && result; ++j) {
        if (((*this)(i, j) - other(i, j)) > 1e-7) {
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

double S21Matrix::Determinant() {
  double result = 0;
  if (rows_ != cols_) {
      throw std::out_of_range(
          "Incorrect input, matrix should be square");
  }
  if (rows_ == 1) {
    result = (*this)(0, 0);
  } else if (rows_ == 2) {
    result =
        (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  } else if (rows_ > 2) {
    S21Matrix algebraic_compl = (*this).CalcComplements();
    for (int i = 0; i < rows_; i++) {
      result += (*this)(i, 0) * algebraic_compl(i, 0);
    }
    }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
      throw std::out_of_range(
          "Incorrect input, matrix should be square");
  }
  double minor = 0;
  S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
  S21Matrix algebraic_compl(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      FillMinorMatrix(i, j, minor_matrix);
      minor = minor_matrix.Determinant();
      algebraic_compl(i, j) = minor * pow(-1, (i + j));
    }
  }
  return algebraic_compl;
}

void S21Matrix::FillMinorMatrix(int current_row, int current_col, S21Matrix &minor_matrix) {
  int minor_rows = 0;
  for (int k = 0; k < rows_; k++) {
    int minor_cols = 0;
    for (int l = 0; l < cols_; l++) {
      if (k != current_row && l != current_col) {
        minor_matrix(minor_rows, minor_cols) = (*this)(k, l);
        minor_cols++;
      }
    }
    if (k != current_row) {
      minor_rows++;
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (fabs(determinant) < 1e-6) {
    throw std::invalid_argument("Matrix deteminant is 0");
  }
  S21Matrix inversed = CalcComplements();
  inversed.Transpose();
  for (int i = 0; i < inversed.rows_; i++) {
    for (int j = 0; j < inversed.cols_; j++) {
      inversed(i, j) /= determinant;
    }
  }
  return inversed;
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
