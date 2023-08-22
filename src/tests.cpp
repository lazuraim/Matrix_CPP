#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>
#include <cstring>
#include <cmath>

class S21Matrix {

    public:
        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other) noexcept;
        ~S21Matrix();

        void setRows(int new_rows);
        void setCols(int new_cols);
        int getRows() const;
        int getCols() const;

        S21Matrix& operator=(const S21Matrix& other);
        S21Matrix& operator=(S21Matrix&& other) noexcept;
        double& operator()(int row, int col);                         
        double& operator()(int row, int col) const;
        S21Matrix& operator+=(const S21Matrix& other);                            
        S21Matrix operator+(const S21Matrix& other);
        S21Matrix& operator-=(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);
        S21Matrix operator*(const double num) const;
        friend S21Matrix operator*(const double num, const S21Matrix& other);
        S21Matrix operator*=(const S21Matrix& other);
        bool operator==(const S21Matrix& other);
        bool operator!=(const S21Matrix& other);

        bool EqMatrix(const S21Matrix& other);
        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);
        S21Matrix Transpose() const;
        S21Matrix CalcComplements() const;
        double Determinant() const;
        S21Matrix InverseMatrix() const;

    private:
        int rows_, cols_; 
        double *matrix_;
        const double kEps = 1e-7;
        void CreateMatrix();
        void DestroyMatrix();
        void FillMinorMatrix(int current_row, int current_col, S21Matrix &minor_matrix) const; 
};

#endif // __S21MATRIX_H__
