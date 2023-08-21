#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

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

TEST(Constructors, Parameterized_3) {
  EXPECT_ANY_THROW (
     S21Matrix m(0, 0);
  );
}

TEST(Constructors, Parameterized_4) {
  EXPECT_ANY_THROW (
     S21Matrix m(0, 5);
  );
}

TEST(Constructors, Parameterized_5) {
  EXPECT_ANY_THROW (
     S21Matrix m(10, 0);
  );
}

TEST(Constructors, Parameterized_6) {
  EXPECT_ANY_THROW (
     S21Matrix m(-1, 0);
  );
}

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
  EXPECT_ANY_THROW (
    S21Matrix m2(m1);
  );
}

TEST(Constructors, copy_4) {
  S21Matrix m1;
  EXPECT_ANY_THROW (
    S21Matrix m2 = m1;
  );
}

TEST(Constructors, copy_5) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  
  S21Matrix m2(m1);
  ASSERT_DOUBLE_EQ(m2(0, 0), m1(0, 0));
  ASSERT_DOUBLE_EQ(m2(0, 1), m1(0, 1));
  ASSERT_DOUBLE_EQ(m2(1, 0), m1(1, 0));
  ASSERT_DOUBLE_EQ(m2(1, 1), m1(1, 1));
  
  ASSERT_DOUBLE_EQ(m2(0, 0), 1);
  ASSERT_DOUBLE_EQ(m2(0, 1), 2);
  ASSERT_DOUBLE_EQ(m2(1, 0), 3);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4);
}

TEST(Constructors, copy_6) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.6;
  m1(0, 1) = 2.7;
  m1(1, 0) = 3.8;
  m1(1, 1) = 4.0;
  
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

TEST(Constructors, move_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.6;
  m1(0, 1) = 2.7;
  m1(1, 0) = 3.8;
  m1(1, 1) = 4.0;
  
  S21Matrix m2 = std::move(m1);
  
  ASSERT_DOUBLE_EQ(m2(0, 0), 1.6);
  ASSERT_DOUBLE_EQ(m2(0, 1), 2.7);
  ASSERT_DOUBLE_EQ(m2(1, 0), 3.8);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.0);
  
  ASSERT_EQ(m1.getRows(), 0);
  ASSERT_EQ(m1.getCols(), 0);
  EXPECT_ANY_THROW (
  	m1(0, 0);
  );
}

TEST(Constructors, move_2) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.6;
  m1(0, 1) = 2.7;
  m1(1, 0) = 3.8;
  m1(1, 1) = 4.0;
  
  S21Matrix m2(std::move(m1));
  
  ASSERT_DOUBLE_EQ(m2(0, 0), 1.6);
  ASSERT_DOUBLE_EQ(m2(0, 1), 2.7);
  ASSERT_DOUBLE_EQ(m2(1, 0), 3.8);
  ASSERT_DOUBLE_EQ(m2(1, 1), 4.0);
  
  ASSERT_EQ(m1.getRows(), 0);
  ASSERT_EQ(m1.getCols(), 0);
  EXPECT_ANY_THROW (
  	m1(0, 0);
  );
}

TEST(Constructors, move_3) {
  S21Matrix m1;
  S21Matrix m2(std::move(m1));
  ASSERT_EQ(m2.getRows(), 0);
  ASSERT_EQ(m2.getCols(), 0);
}

// set rows for default
TEST(Setters, set_rows_1) {
  S21Matrix m1;
  m1.setRows(1);
  ASSERT_EQ(m1.getRows(), 1);
  ASSERT_EQ(m1.getCols(), 0);
}

// general case
TEST(Setters, set_rows_2) {
  S21Matrix m1(1, 1);
  m1.setRows(5);
  ASSERT_EQ(m1.getRows(), 5);
  ASSERT_EQ(m1.getCols(), 1);
}

// new rows == rows_
TEST(Setters, set_rows_3) {
  S21Matrix m1(3, 3);
  m1.setRows(3);
  ASSERT_EQ(m1.getRows(), 3);
  ASSERT_EQ(m1.getCols(), 3);
}

// zero
TEST(Setters, set_rows_4) {
  S21Matrix m1(1, 1);
  EXPECT_ANY_THROW (
    m1.setRows(0);
  );
}

// less than zero
TEST(Setters, set_rows_5) {
  S21Matrix m1(1, 1);
  EXPECT_ANY_THROW (
    m1.setRows(-5);
  );
}

// set cols for default
TEST(Setters, set_cols_1) {
  S21Matrix m1;
  m1.setCols(1);
  ASSERT_EQ(m1.getRows(), 0);
  ASSERT_EQ(m1.getCols(), 1);
}

// general case
TEST(Setters, set_cols_2) {
  S21Matrix m1(1, 1);
  m1.setCols(5);
  ASSERT_EQ(m1.getRows(), 1);
  ASSERT_EQ(m1.getCols(), 5);
}

// new rows == rows_
TEST(Setters, set_cols_3) {
  S21Matrix m1(3, 3);
  m1.setCols(3);
  ASSERT_EQ(m1.getRows(), 3);
  ASSERT_EQ(m1.getCols(), 3);
}

// zero
TEST(Setters, set_cols_4) {
  S21Matrix m1(1, 1);
  EXPECT_ANY_THROW (
    m1.setCols(0);
  );
}

// less than zero
TEST(Setters, set_cols_5) {
  S21Matrix m1(1, 1);
  EXPECT_ANY_THROW (
    m1.setCols(-5);
  );
}

// general case
TEST(Operations, EqMatrix_1) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  
  S21Matrix m2(3, 3);
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(0, 2) = 3;
  m2(1, 0) = 4;
  m2(1, 1) = 5;
  m2(1, 2) = 6;
  m2(2, 0) = 7;
  m2(2, 1) = 8;
  m2(2, 2) = 9;
  
  ASSERT_EQ(m1.EqMatrix(m2), 1);
}

// general not equal
TEST(Operations, EqMatrix_2) {
  S21Matrix m1(4, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  
  S21Matrix m2(3, 3);
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(0, 2) = 3;
  m2(1, 0) = 4;
  m2(1, 1) = 5;
  m2(1, 2) = 6;
  m2(2, 0) = 7;
  m2(2, 1) = 8;
  m2(2, 2) = 9;
  
  ASSERT_EQ(m1.EqMatrix(m2), 0);
}

// general not equal
TEST(Operations, EqMatrix_3) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 717;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  
  S21Matrix m2(3, 3);
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(0, 2) = 3;
  m2(1, 0) = 4;
  m2(1, 1) = 5;
  m2(1, 2) = 6;
  m2(2, 0) = 7;
  m2(2, 1) = 8;
  m2(2, 2) = 9;
  
  ASSERT_EQ(m1.EqMatrix(m2), 0);
}

TEST(Operations, SumMatrix_1) {
  S21Matrix m1(1, 1);
  S21Matrix m2(2, 2);
  EXPECT_ANY_THROW(
    m1.SumMatrix(m2);
  );
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
