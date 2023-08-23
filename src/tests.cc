#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

namespace s21 {

TEST(Constructors, Default) {
  S21Matrix m0;
  ASSERT_EQ(m0.getRows(), 0);
  ASSERT_EQ(m0.getCols(), 0);
}

TEST(Constructors, Parameterized_1) {
  S21Matrix m1(1, 1);
  ASSERT_EQ(m1.getRows(), 1);
  ASSERT_EQ(m1.getCols(), 1);
}

TEST(Constructors, Parameterized_2) {
  S21Matrix m4x3(4, 3);
  ASSERT_EQ(m4x3.getRows(), 4);
  ASSERT_EQ(m4x3.getCols(), 3);
}

TEST(Constructors, Parameterized_3) { EXPECT_ANY_THROW(S21Matrix m(0, 0);); }

TEST(Constructors, Parameterized_4) { EXPECT_ANY_THROW(S21Matrix m(0, 5);); }

TEST(Constructors, Parameterized_5) { EXPECT_ANY_THROW(S21Matrix m(10, 0);); }

TEST(Constructors, Parameterized_6) { EXPECT_ANY_THROW(S21Matrix m(-1, 0);); }

TEST(Constructors, copy_1) {
  S21Matrix m1(1, 1);
  S21Matrix m2(m1);
  ASSERT_EQ(m2.getRows(), 1);
  ASSERT_EQ(m2.getCols(), 1);
  ASSERT_EQ(m2.getRows(), m1.getRows());
  ASSERT_EQ(m2.getCols(), m1.getCols());
}

TEST(Constructors, copy_2) {
  S21Matrix m1(1, 1);
  S21Matrix m2 = m1;
  ASSERT_EQ(m2.getRows(), 1);
  ASSERT_EQ(m2.getCols(), 1);
  ASSERT_EQ(m2.getRows(), m1.getRows());
  ASSERT_EQ(m2.getCols(), m1.getCols());
}

TEST(Constructors, copy_3) {
  S21Matrix m1;
  EXPECT_ANY_THROW(S21Matrix m2(m1););
}

TEST(Constructors, copy_4) {
  S21Matrix m1;
  EXPECT_ANY_THROW(S21Matrix m2 = m1;);
}

TEST(Constructors, copy_5) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0, m1(0, 1) = 2.0;
  m1(1, 0) = 3.0, m1(1, 1) = 4.0;

  S21Matrix m2(m1);
  ASSERT_DOUBLE_EQ(m2(0, 0), m1(0, 0));
  ASSERT_DOUBLE_EQ(m2(0, 1), m1(0, 1));
  ASSERT_DOUBLE_EQ(m2(1, 0), m1(1, 0));
  ASSERT_DOUBLE_EQ(m2(1, 1), m1(1, 1));

  ASSERT_DOUBLE_EQ(m2(0, 0), 1.0);
  ASSERT_DOUBLE_EQ(m2(0, 1), 2.0);
  ASSERT_DOUBLE_EQ(m2(1, 0), 3.0);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.0);
}

TEST(Constructors, copy_6) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.6, m1(0, 1) = 2.7;
  m1(1, 0) = 3.8, m1(1, 1) = 4.0;

  S21Matrix m2 = m1;
  ASSERT_DOUBLE_EQ(m2(0, 0), m1(0, 0));
  ASSERT_DOUBLE_EQ(m2(0, 1), m1(0, 1));
  ASSERT_DOUBLE_EQ(m2(1, 0), m1(1, 0));
  ASSERT_DOUBLE_EQ(m2(1, 1), m1(1, 1));

  ASSERT_DOUBLE_EQ(m2(0, 0), 1.6);
  ASSERT_DOUBLE_EQ(m2(0, 1), 2.7);
  ASSERT_DOUBLE_EQ(m2(1, 0), 3.8);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.0);
}

TEST(Constructors, copy_7) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.6, m1(0, 1) = 2.7;
  m1(1, 0) = 3.8, m1(1, 1) = 4.0;

  S21Matrix m2;
  m2 = m1;
  ASSERT_DOUBLE_EQ(m2(0, 0), m1(0, 0));
  ASSERT_DOUBLE_EQ(m2(0, 1), m1(0, 1));
  ASSERT_DOUBLE_EQ(m2(1, 0), m1(1, 0));
  ASSERT_DOUBLE_EQ(m2(1, 1), m1(1, 1));

  ASSERT_DOUBLE_EQ(m2(0, 0), 1.6);
  ASSERT_DOUBLE_EQ(m2(0, 1), 2.7);
  ASSERT_DOUBLE_EQ(m2(1, 0), 3.8);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.0);
}

TEST(Constructors, copy_8) {
  S21Matrix m1;
  S21Matrix m2(2, 2);
  m2(0, 0) = 1.6, m2(0, 1) = 2.7;
  m2(1, 0) = 3.8, m2(1, 1) = 4.0;
  m1 = m2;
  ASSERT_DOUBLE_EQ(m1(0, 0), m2(0, 0));
  ASSERT_DOUBLE_EQ(m1(0, 1), m2(0, 1));
  ASSERT_DOUBLE_EQ(m1(1, 0), m2(1, 0));
  ASSERT_DOUBLE_EQ(m1(1, 1), m2(1, 1));

  ASSERT_DOUBLE_EQ(m1(0, 0), 1.6);
  ASSERT_DOUBLE_EQ(m1(0, 1), 2.7);
  ASSERT_DOUBLE_EQ(m1(1, 0), 3.8);
  ASSERT_DOUBLE_EQ(m1(1, 1), 4.0);
}

TEST(Constructors, copy_9) {
  S21Matrix m1;
  S21Matrix m2(1, 1);
  EXPECT_ANY_THROW(m2 = m1;);
}

TEST(Constructors, move_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.6, m1(0, 1) = 2.7;
  m1(1, 0) = 3.8, m1(1, 1) = 4.0;
  S21Matrix m2 = std::move(m1);
  ASSERT_DOUBLE_EQ(m2(0, 0), 1.6);
  ASSERT_DOUBLE_EQ(m2(0, 1), 2.7);
  ASSERT_DOUBLE_EQ(m2(1, 0), 3.8);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.0);

  ASSERT_EQ(m1.getRows(), 0);
  ASSERT_EQ(m1.getCols(), 0);
  EXPECT_ANY_THROW(m1(0, 0););
}

TEST(Constructors, move_2) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.6, m1(0, 1) = 2.7;
  m1(1, 0) = 3.8, m1(1, 1) = 4.0;
  S21Matrix m2(std::move(m1));
  ASSERT_DOUBLE_EQ(m2(0, 0), 1.6);
  ASSERT_DOUBLE_EQ(m2(0, 1), 2.7);
  ASSERT_DOUBLE_EQ(m2(1, 0), 3.8);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.0);

  ASSERT_EQ(m1.getRows(), 0);
  ASSERT_EQ(m1.getCols(), 0);
  EXPECT_ANY_THROW(m1(0, 0););
}

TEST(Constructors, move_3) {
  S21Matrix m1;
  S21Matrix m2(std::move(m1));
  ASSERT_EQ(m2.getRows(), 0);
  ASSERT_EQ(m2.getCols(), 0);
}

TEST(Constructors, move_4) {
  S21Matrix m1(1, 1);
  m1(0, 0) = 5.0;
  S21Matrix m2(std::move(m1));
  ASSERT_EQ(m2.getRows(), 1);
  ASSERT_EQ(m2.getCols(), 1);
  ASSERT_DOUBLE_EQ(m2(0, 0), 5.0);
}

TEST(Setters, set_rows_1) {
  S21Matrix m1;
  m1.setRows(1);
  ASSERT_EQ(m1.getRows(), 1);
  ASSERT_EQ(m1.getCols(), 0);
}

TEST(Setters, set_rows_2) {
  S21Matrix m1(1, 1);
  m1.setRows(5);
  ASSERT_EQ(m1.getRows(), 5);
  ASSERT_EQ(m1.getCols(), 1);
}

TEST(Setters, set_rows_3) {
  S21Matrix m1(3, 3);
  m1.setRows(3);
  ASSERT_EQ(m1.getRows(), 3);
  ASSERT_EQ(m1.getCols(), 3);
}

TEST(Setters, set_rows_4) {
  S21Matrix m1(1, 1);
  EXPECT_ANY_THROW(m1.setRows(0););
}

TEST(Setters, set_rows_5) {
  S21Matrix m1(1, 1);
  EXPECT_ANY_THROW(m1.setRows(-5););
}

TEST(Setters, set_cols_1) {
  S21Matrix m1;
  m1.setCols(1);
  ASSERT_EQ(m1.getRows(), 0);
  ASSERT_EQ(m1.getCols(), 1);
}

TEST(Setters, set_cols_2) {
  S21Matrix m1(1, 1);
  m1.setCols(5);
  ASSERT_EQ(m1.getRows(), 1);
  ASSERT_EQ(m1.getCols(), 5);
}

TEST(Setters, set_cols_3) {
  S21Matrix m1(3, 3);
  m1.setCols(3);
  ASSERT_EQ(m1.getRows(), 3);
  ASSERT_EQ(m1.getCols(), 3);
}

TEST(Setters, set_cols_4) {
  S21Matrix m1(1, 1);
  EXPECT_ANY_THROW(m1.setCols(0););
}

TEST(Setters, set_cols_5) {
  S21Matrix m1(1, 1);
  EXPECT_ANY_THROW(m1.setCols(-5););
}

TEST(Operations, EqMatrix_1) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1, m1(0, 1) = 2, m1(0, 2) = 3;
  m1(1, 0) = 4, m1(1, 1) = 5, m1(1, 2) = 6;
  m1(2, 0) = 7, m1(2, 1) = 8, m1(2, 2) = 9;
  S21Matrix m2(3, 3);
  m2(0, 0) = 1, m2(0, 1) = 2, m2(0, 2) = 3;
  m2(1, 0) = 4, m2(1, 1) = 5, m2(1, 2) = 6;
  m2(2, 0) = 7, m2(2, 1) = 8, m2(2, 2) = 9;
  ASSERT_EQ(m1.EqMatrix(m2), 1);
}

TEST(Operations, EqMatrix_2) {
  S21Matrix m1(4, 3);
  m1(0, 0) = 1, m1(0, 1) = 2, m1(0, 2) = 3;
  m1(1, 0) = 4, m1(1, 1) = 5, m1(1, 2) = 6;
  m1(2, 0) = 7, m1(2, 1) = 8, m1(2, 2) = 9;
  S21Matrix m2(3, 3);
  m2(0, 0) = 1, m2(0, 1) = 2, m2(0, 2) = 3;
  m2(1, 0) = 4, m2(1, 1) = 5, m2(1, 2) = 6;
  m2(2, 0) = 7, m2(2, 1) = 8, m2(2, 2) = 9;
  ASSERT_EQ(m1.EqMatrix(m2), 0);
}

TEST(Operations, EqMatrix_3) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1, m1(0, 1) = 2, m1(0, 2) = 3;
  m1(1, 0) = 4, m1(1, 1) = 5, m1(1, 2) = 6;
  m1(2, 0) = 717, m1(2, 1) = 8, m1(2, 2) = 9;
  S21Matrix m2(3, 3);
  m2(0, 0) = 1, m2(0, 1) = 2, m2(0, 2) = 3;
  m2(1, 0) = 4, m2(1, 1) = 5, m2(1, 2) = 6;
  m2(2, 0) = 7, m2(2, 1) = 8, m2(2, 2) = 9;
  ASSERT_EQ(m1.EqMatrix(m2), 0);
}

TEST(Operations, SumMatrix_1) {
  S21Matrix m1(1, 1);
  S21Matrix m2(2, 2);
  EXPECT_ANY_THROW(m1.SumMatrix(m2););
}

TEST(Operations, SumMatrix_2) {
  S21Matrix m1;
  S21Matrix m2(2, 2);
  EXPECT_ANY_THROW(m2.SumMatrix(m1););
}

TEST(Operations, SumMatrix_3) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 10.0, m1(0, 1) = 100.0;
  m1(1, 0) = 20.0, m1(1, 1) = 200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  m1.SumMatrix(m2);
  ASSERT_DOUBLE_EQ(m1(0, 0), 11.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), 101.0);
  ASSERT_DOUBLE_EQ(m1(1, 0), 22.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), 202.0);
}

TEST(Operations, SumMatrix_4) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = -10.0, m1(0, 1) = -100.0;
  m1(1, 0) = -20.0, m1(1, 1) = -200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  m1.SumMatrix(m2);
  ASSERT_DOUBLE_EQ(m1(0, 0), -9.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), -99.0);
  ASSERT_DOUBLE_EQ(m1(1, 0), -18.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), -198.0);
}

TEST(Operators, Sum_1) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 10.0, m1(0, 1) = 100.0;
  m1(1, 0) = 20.0, m1(1, 1) = 200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  S21Matrix m3 = m1 + m2;
  ASSERT_DOUBLE_EQ(m3(0, 0), 11.0);
  ASSERT_DOUBLE_EQ(m3(0, 1), 101.0);
  ASSERT_DOUBLE_EQ(m3(1, 0), 22.0);
  ASSERT_DOUBLE_EQ(m3(1, 1), 202.0);
}

TEST(Operators, Sum_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 10.0, m1(0, 1) = 100.0;
  m1(1, 0) = 20.0, m1(1, 1) = 200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  S21Matrix m3 = m2 + m1;
  ASSERT_DOUBLE_EQ(m3(0, 0), 11.0);
  ASSERT_DOUBLE_EQ(m3(0, 1), 101.0);
  ASSERT_DOUBLE_EQ(m3(1, 0), 22.0);
  ASSERT_DOUBLE_EQ(m3(1, 1), 202.0);
}

TEST(Operators, Sum_3) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 2);
  EXPECT_ANY_THROW(S21Matrix m3 = m1 + m2;);
}

TEST(Operators, SumEq_1) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 2);
  EXPECT_ANY_THROW(m1 += m2;);
}

TEST(Operators, SumEq_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 10.0, m1(0, 1) = 100.0;
  m1(1, 0) = 20.0, m1(1, 1) = 200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  m1 += m2;
  ASSERT_DOUBLE_EQ(m1(0, 0), 11.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), 101.0);
  ASSERT_DOUBLE_EQ(m1(1, 0), 22.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), 202.0);
}

TEST(Operators, SumEq_3) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 10.0, m1(0, 1) = 100.0;
  m1(1, 0) = 20.0, m1(1, 1) = 200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  m2 += m1;
  ASSERT_DOUBLE_EQ(m2(0, 0), 11.0);
  ASSERT_DOUBLE_EQ(m2(0, 1), 101.0);
  ASSERT_DOUBLE_EQ(m2(1, 0), 22.0);
  ASSERT_DOUBLE_EQ(m2(1, 1), 202.0);
}

TEST(Operations, SubMatrix_1) {
  S21Matrix m1(1, 1);
  S21Matrix m2(2, 2);
  EXPECT_ANY_THROW(m1.SubMatrix(m2););
}

TEST(Operations, SubMatrix_2) {
  S21Matrix m1;
  S21Matrix m2(2, 2);
  EXPECT_ANY_THROW(m2.SubMatrix(m1););
}

TEST(Operations, SubMatrix_3) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = -10.0, m1(0, 1) = -100.0;
  m1(1, 0) = -20.0, m1(1, 1) = -200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  m1.SubMatrix(m2);
  ASSERT_DOUBLE_EQ(m1(0, 0), -11.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), -101.0);
  ASSERT_DOUBLE_EQ(m1(1, 0), -22.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), -202.0);
}

TEST(Operations, SubMatrix_4) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 30.5, m1(0, 1) = 100.4;
  m1(1, 0) = 56.56, m1(1, 1) = 1.111;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.06, m2(1, 1) = 2.0;
  m1.SubMatrix(m2);
  ASSERT_DOUBLE_EQ(m1(0, 0), 29.5);
  ASSERT_DOUBLE_EQ(m1(0, 1), 99.4);
  ASSERT_DOUBLE_EQ(m1(1, 0), 54.50);
  ASSERT_DOUBLE_EQ(m1(1, 1), -0.889);
}

TEST(Operators, Sub_1) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = -10.0, m1(0, 1) = -100.0;
  m1(1, 0) = -20.0, m1(1, 1) = -200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  S21Matrix m3 = m1 - m2;
  ASSERT_DOUBLE_EQ(m3(0, 0), -11.0);
  ASSERT_DOUBLE_EQ(m3(0, 1), -101.0);
  ASSERT_DOUBLE_EQ(m3(1, 0), -22.0);
  ASSERT_DOUBLE_EQ(m3(1, 1), -202.0);
}

TEST(Operators, Sub_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 5);
  EXPECT_ANY_THROW(S21Matrix m3 = m1 - m2;);
}

TEST(Operators, SubEq_1) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 5);
  EXPECT_ANY_THROW(m1 -= m2;);
}

TEST(Operators, SubEq_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = -10.0, m1(0, 1) = -100.0;
  m1(1, 0) = -20.0, m1(1, 1) = -200.0;
  m2(0, 0) = 1.0, m2(0, 1) = 1.0;
  m2(1, 0) = 2.0, m2(1, 1) = 2.0;
  m1 -= m2;
  ASSERT_EQ(m1(0, 0), -11.0);
  ASSERT_EQ(m1(0, 1), -101.0);
  ASSERT_EQ(m1(1, 0), -22.0);
  ASSERT_EQ(m1(1, 1), -202.0);
}

TEST(Operations, MulNumber_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  m1.MulNumber(0.5);
  ASSERT_DOUBLE_EQ(m1(0, 0), 3.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), 3.5);
  ASSERT_DOUBLE_EQ(m1(1, 0), 4.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), 4.5);
}

TEST(Operations, MulNumber_2) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  m1.MulNumber(0);
  ASSERT_DOUBLE_EQ(m1(0, 0), 0.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), 0.0);
  ASSERT_DOUBLE_EQ(m1(1, 0), 0.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), 0.0);
}

TEST(Operators, MulNumber_oper_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2 = m1 * 0;
  ASSERT_DOUBLE_EQ(m2(0, 0), 0.0);
  ASSERT_DOUBLE_EQ(m2(0, 1), 0.0);
  ASSERT_DOUBLE_EQ(m2(1, 0), 0.0);
  ASSERT_DOUBLE_EQ(m2(1, 1), 0.0);
}

TEST(Operators, MulNumber_oper_2) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2 = m1 * 0.5;
  ASSERT_DOUBLE_EQ(m2(0, 0), 3.0);
  ASSERT_DOUBLE_EQ(m2(0, 1), 3.5);
  ASSERT_DOUBLE_EQ(m2(1, 0), 4.0);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.5);
}

TEST(Operators, MulNumber_oper_3) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2 = 0.5 * m1;
  ASSERT_DOUBLE_EQ(m2(0, 0), 3.0);
  ASSERT_DOUBLE_EQ(m2(0, 1), 3.5);
  ASSERT_DOUBLE_EQ(m2(1, 0), 4.0);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.5);
}

TEST(Operators, MulNumber_oper_4) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  m1 *= 0.5;
  ASSERT_DOUBLE_EQ(m1(0, 0), 3.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), 3.5);
  ASSERT_DOUBLE_EQ(m1(1, 0), 4.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), 4.5);
}

TEST(Operators, MulNumber_oper_5) {
  S21Matrix m1;
  EXPECT_ANY_THROW(m1 *= 0.5);
}

TEST(Operations, MulMatrix_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2(m1);
  m1.MulMatrix(m2);
  ASSERT_DOUBLE_EQ(m1(0, 0), 92.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), 105.0);
  ASSERT_DOUBLE_EQ(m1(1, 0), 120.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), 137.0);
}

TEST(Operations, MulMatrix_2) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2(5, 5);
  EXPECT_ANY_THROW(m1.MulMatrix(m2););
}

TEST(Operators, MulMatrix_oper_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2(5, 5);
  EXPECT_ANY_THROW(m1 * m2;);
}

TEST(Operators, MulMatrix_oper_2) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2(m1);
  m1 = m1 * m2;
  ASSERT_DOUBLE_EQ(m1(0, 0), 92.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), 105.0);
  ASSERT_DOUBLE_EQ(m1(1, 0), 120.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), 137.0);
}

TEST(Operators, MulMatrix_oper_3) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2(m1);
  m1 *= m2;
  ASSERT_DOUBLE_EQ(m1(0, 0), 92.0);
  ASSERT_DOUBLE_EQ(m1(0, 1), 105.0);
  ASSERT_DOUBLE_EQ(m1(1, 0), 120.0);
  ASSERT_DOUBLE_EQ(m1(1, 1), 137.0);
}

TEST(Operators, MulMatrix_oper_4) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  S21Matrix m2(m1);
  m2 *= m1;
  ASSERT_DOUBLE_EQ(m2(0, 0), 92.0);
  ASSERT_DOUBLE_EQ(m2(0, 1), 105.0);
  ASSERT_DOUBLE_EQ(m2(1, 0), 120.0);
  ASSERT_DOUBLE_EQ(m2(1, 1), 137.0);
}

TEST(Operations, Transpose_1) {
  S21Matrix m1(3, 2);
  m1(0, 0) = 6.0, m1(0, 1) = 7.0;
  m1(1, 0) = 8.0, m1(1, 1) = 9.0;
  m1(2, 0) = 10.0, m1(2, 1) = 11.0;
  S21Matrix m2 = m1.Transpose();
  ASSERT_EQ(m2.getRows(), m1.getCols());
  ASSERT_EQ(m2.getCols(), m1.getRows());
  ASSERT_DOUBLE_EQ(m2(0, 0), m1(0, 0));
  ASSERT_DOUBLE_EQ(m2(0, 1), m1(1, 0));
  ASSERT_DOUBLE_EQ(m2(1, 0), m1(0, 1));
  ASSERT_DOUBLE_EQ(m2(1, 1), m1(1, 1));
  ASSERT_DOUBLE_EQ(m2(0, 2), m1(2, 0));
  ASSERT_DOUBLE_EQ(m2(1, 2), m1(2, 1));
}

TEST(Operations, Transpose_2) {
  S21Matrix m1;
  EXPECT_ANY_THROW(S21Matrix m2 = m1.Transpose(););
}

TEST(Operations, Determinant_1) {
  S21Matrix m1(3, 4);
  EXPECT_ANY_THROW(m1.Determinant(););
}

TEST(Operations, Determinant_2) {
  S21Matrix m1(1, 1);
  m1(0, 0) = 5;
  ASSERT_DOUBLE_EQ(m1.Determinant(), 5);
}

TEST(Operations, Determinant_3) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 5.0, m1(0, 1) = 6.0;
  m1(1, 0) = 10.0, m1(1, 1) = 4.0;
  ASSERT_DOUBLE_EQ(m1.Determinant(), -40.0);
}

TEST(Operations, Determinant_4) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 5.0, m1(0, 1) = 6.0, m1(0, 2) = 67.0;
  m1(1, 0) = 10.0, m1(1, 1) = 4.0, m1(1, 2) = -9.0;
  m1(2, 0) = 7.0, m1(2, 1) = 90.0, m1(2, 2) = 91.0;
  ASSERT_DOUBLE_EQ(m1.Determinant(), 58456.0);
}

TEST(Operations, CalcComplements_1) {
  S21Matrix m1(3, 7);
  EXPECT_ANY_THROW(m1.CalcComplements(););
}

TEST(Operations, InverseMatrix_1) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1.0, m1(0, 1) = 2.0, m1(0, 2) = 3.0;
  m1(1, 0) = 4.0, m1(1, 1) = 5.0, m1(1, 2) = 6.0;
  m1(2, 0) = 7.0, m1(2, 1) = 8.0, m1(2, 2) = 9.0;
  EXPECT_ANY_THROW(m1.InverseMatrix(););
}

TEST(Operations, InverseMatrix_2) {
  S21Matrix m1(4, 4);
  m1(0, 0) = 2.0, m1(0, 1) = 1.0, m1(0, 2) = 0.0, m1(0, 3) = 0.0;
  m1(1, 0) = 3.0, m1(1, 1) = 2.0, m1(1, 2) = 0.0, m1(1, 3) = 0.0;
  m1(2, 0) = 1.0, m1(2, 1) = 1.0, m1(2, 2) = 3.0, m1(2, 3) = 4.0;
  m1(3, 0) = 2.0, m1(3, 1) = -1.0, m1(3, 2) = 2.0, m1(3, 3) = 3.0;

  S21Matrix m2 = m1.InverseMatrix();
  ASSERT_DOUBLE_EQ(m2(0, 0), 2.0);
  ASSERT_DOUBLE_EQ(m2(0, 1), -1.0);
  ASSERT_DOUBLE_EQ(m2(0, 2), 0.0);
  ASSERT_DOUBLE_EQ(m2(0, 3), 0.0);

  ASSERT_DOUBLE_EQ(m2(1, 0), -3.0);
  ASSERT_DOUBLE_EQ(m2(1, 1), 2.0);
  ASSERT_DOUBLE_EQ(m2(1, 2), 0.0);
  ASSERT_DOUBLE_EQ(m2(1, 3), 0.0);

  ASSERT_DOUBLE_EQ(m2(2, 0), 31.0);
  ASSERT_DOUBLE_EQ(m2(2, 1), -19.0);
  ASSERT_DOUBLE_EQ(m2(2, 2), 3.0);
  ASSERT_DOUBLE_EQ(m2(2, 3), -4.0);

  ASSERT_DOUBLE_EQ(m2(3, 0), -23.0);
  ASSERT_DOUBLE_EQ(m2(3, 1), 14.0);
  ASSERT_DOUBLE_EQ(m2(3, 2), -2.0);
  ASSERT_DOUBLE_EQ(m2(3, 3), 3.0);
}

TEST(Operations, InverseMatrix_3) {
  S21Matrix m1(1, 1);
  m1(0, 0) = 10;
  EXPECT_ANY_THROW(m1.InverseMatrix(););
}

TEST(Operators, Equality_1) {
  S21Matrix m1;
  S21Matrix m2(1, 1);
  ASSERT_EQ(m1 == m2, false);
  ASSERT_EQ(m1 != m2, true);
}

TEST(Operators, Equality_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0.000001, m1(0, 1) = -0.000001;
  m1(1, 0) = 1.0, m1(1, 1) = 2.0;

  m2(0, 0) = 0.000002, m2(0, 1) = -0.000002;
  m2(1, 0) = 1.1, m2(1, 1) = 2.1;
  ASSERT_EQ(m1 == m2, false);
  ASSERT_EQ(m1 != m2, true);
}

TEST(Operators, Equality_3) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0.000001, m1(0, 1) = -0.000001;
  m1(1, 0) = 1.0, m1(1, 1) = 2.0;
  m2(0, 0) = 0.000001, m2(0, 1) = -0.000001;
  m2(1, 0) = 1.0, m2(1, 1) = 2.0;
  ASSERT_EQ(m1 == m2, true);
  ASSERT_EQ(m1 != m2, false);
}

TEST(Operators, Index_3) {
  const S21Matrix m1(2, 2);
  m1(0, 0) = 0.000001, m1(0, 1) = -0.000001;
  m1(1, 0) = 1.0, m1(1, 1) = 2.0;
  EXPECT_ANY_THROW(m1(3, 3););
}

}  // namespace s21

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
