#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>
#include <cstring>

class S21Matrix {
    private:
        int rows_, cols_; 
        double **matrix_;
        void CreateMatrix();
        void DestroyMatrix(); 

    public:
        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other) noexcept;
        ~S21Matrix();

        void setRows(int rows);
        void setCols(int new_cols);
        int getRows();
        int getCols();


        S21Matrix& operator=(const S21Matrix& other); // оператор копирования
        S21Matrix& operator=(S21Matrix&& other) noexcept; // оператор перемещения 
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
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();
};



#endif // __S21MATRIX_H__