#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>
#include <cstring>

class S21Matrix {
    private:
        int rows_, cols_; 
        double **matrix_;

    public:
        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other) noexcept;
        ~S21Matrix();

        void setRows(int rows) {
            rows_ = rows;
        }
        void setCols(int cols) {
            cols_ = cols;
        } 
        int getRows() {
            return rows_;
        }
        int getCols() {
            return cols_;
        }

        S21Matrix& operator=(const S21Matrix& other); //    
        double& operator()(int row, int col);                         
        double& operator()(int row, int col) const;
        S21Matrix& operator+=(const S21Matrix& other);                            
        S21Matrix operator+(const S21Matrix& other);
        S21Matrix& operator-=(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);
        S21Matrix operator*(const S21Matrix& other);
        S21Matrix operator*=(const S21Matrix& other);
        S21Matrix operator==(const S21Matrix& other);

        bool EqMatrix(const S21Matrix& other);
        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();
};

#endif // __S21MATRIX_H__