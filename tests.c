#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix;
  ck_assert_int_eq(OK, s21_create_matrix(rows, columns, &matrix));
  ck_assert_int_eq(matrix.columns, columns);
  ck_assert_int_eq(matrix.rows, rows);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix2) {
  int rows = 4367;
  int columns = 4;
  matrix_t matrix;
  ck_assert_int_eq(OK, s21_create_matrix(rows, columns, &matrix));
  ck_assert_int_eq(matrix.columns, columns);
  ck_assert_int_eq(matrix.rows, rows);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix3) {
  int rows = 2;
  int columns = 8420;
  matrix_t matrix;
  ck_assert_int_eq(OK, s21_create_matrix(rows, columns, &matrix));
  ck_assert_int_eq(matrix.columns, columns);
  ck_assert_int_eq(matrix.rows, rows);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix4) {
  int rows = -9;
  int columns = -6;
  matrix_t matrix;
  ck_assert_int_eq(INCORRECT_MATRIX, s21_create_matrix(rows, columns, &matrix));
}
END_TEST

START_TEST(s21_create_matrix5) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t matrix;
  ck_assert_int_eq(INCORRECT_MATRIX, s21_create_matrix(rows, columns, &matrix));
}
END_TEST

START_TEST(s21_create_matrix6) {
  int rows = rand() % 100 + 1;
  int columns = 0;
  matrix_t matrix;
  ck_assert_int_eq(INCORRECT_MATRIX, s21_create_matrix(rows, columns, &matrix));
}
END_TEST

START_TEST(s21_eq_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1, matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double random_num = (double)rand() / ((double)rand() + 0.1);
      matrix1.matrix[i][j] = random_num;
      matrix2.matrix[i][j] = random_num;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix2) {
  int rows = 5;
  int columns = 10;
  matrix_t matrix1, matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  matrix1.matrix[0][1] = 3.243321;
  matrix2.matrix[0][1] = 3.243321;
  matrix1.matrix[4][9] = 563478290;
  matrix2.matrix[4][9] = 563478290;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix3) {
  int rows = 57;
  int columns = 12;
  matrix_t matrix1, matrix2;
  double random_num = 0;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  matrix1.matrix[0][1] = 3.243321;
  matrix2.matrix[0][1] = 3.243321;
  matrix1.matrix[4][9] = 563478290;
  matrix2.matrix[4][9] = 563478290;
  random_num = (double)rand() / ((double)rand() + 0.1);
  matrix1.matrix[32][2] = random_num;
  matrix2.matrix[32][2] = random_num;
  random_num = (double)rand() / ((double)rand() + 0.1);
  matrix1.matrix[50][7] = random_num;
  matrix2.matrix[50][7] = random_num;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix4) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1, matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);
      matrix2.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix5) {
  int rows = 57;
  int columns = 12;
  matrix_t matrix1, matrix2;
  double random_num = 0;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  matrix1.matrix[0][1] = 3.243321;
  matrix2.matrix[0][1] = 3.321;
  matrix1.matrix[4][9] = 478290;
  matrix2.matrix[4][9] = 563478290;
  random_num = (double)rand() / ((double)rand() + 0.1);
  matrix1.matrix[32][2] = random_num;
  matrix2.matrix[32][2] = -(random_num);
  random_num = (double)rand() / ((double)rand() + 0.1);
  matrix1.matrix[50][7] = random_num;
  matrix2.matrix[50][7] = 0;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_sum_matrix1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t matrix1, matrix2, check;
  s21_create_matrix(rows, cols, &matrix1);
  s21_create_matrix(rows, cols, &matrix2);
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);
      matrix2.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);
      check.matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
    }
  }
  matrix_t result;

  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_sum_matrix2) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 1, &matrix2);
  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result),
                   CALCULATION_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_sum_matrix3) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 0, &matrix1);
  s21_create_matrix(-1, 1, &matrix2);
  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_sub_matrix1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t matrix1, matrix2, check;
  s21_create_matrix(rows, cols, &matrix1);
  s21_create_matrix(rows, cols, &matrix2);
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);
      matrix2.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);
      check.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
    }
  }
  matrix_t result;

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_sub_matrix2) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 1, &matrix2);
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result),
                   CALCULATION_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_sub_matrix3) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 0, &matrix1);
  s21_create_matrix(-1, 1, &matrix2);
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_mult_number1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t matrix1, check, result;
  s21_create_matrix(rows, cols, &matrix1);
  s21_create_matrix(rows, cols, &check);
  double number = (double)rand() / ((double)rand() + 0.1);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);
      check.matrix[i][j] = matrix1.matrix[i][j] * number;
    }
  }

  ck_assert_int_eq(s21_mult_number(&matrix1, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_mult_number2) {
  matrix_t matrix1, result;
  double number = (double)rand() / ((double)rand() + 0.1);
  s21_create_matrix(2, 0, &matrix1);
  ck_assert_int_eq(s21_mult_number(&matrix1, number, &result),
                   INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_mult_matrix1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t matrix1, matrix2, result, check;
  s21_create_matrix(rows, cols, &matrix1);
  s21_create_matrix(cols, rows, &matrix2);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      matrix1.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++)
      matrix2.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);

  s21_create_matrix(matrix1.rows, matrix2.columns, &check);

  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < matrix1.columns; k++)
        check.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_mult_matrix2) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 1, &matrix2);
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result),
                   CALCULATION_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_mult_matrix3) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 0, &matrix1);
  s21_create_matrix(-1, 1, &matrix2);
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_transpose1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t matrix1, check, result;
  s21_create_matrix(rows, cols, &matrix1);
  s21_create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = (double)rand() / ((double)rand() + 0.1);
      matrix1.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }

  ck_assert_int_eq(s21_transpose(&matrix1, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_transpose2) {
  matrix_t matrix1, result;
  s21_create_matrix(0, 3, &matrix1);
  ck_assert_int_eq(s21_transpose(&matrix1, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_determinant1) {
  int size = 1;
  double result = 0;
  matrix_t matrix;
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 673.23;
  ck_assert_int_eq(OK, s21_determinant(&matrix, &result));
  ck_assert_double_eq(673.23, result);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant2) {
  double result = 0;
  matrix_t matrix;
  s21_create_matrix(0, 4, &matrix);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_determinant(&matrix, &result));
}
END_TEST

START_TEST(s21_determinant3) {
  double result = 0;
  matrix_t matrix;
  s21_create_matrix(5, 4, &matrix);
  ck_assert_int_eq(CALCULATION_ERROR, s21_determinant(&matrix, &result));
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant4) {
  int size = 2;
  double result = 0, check = 0;
  matrix_t matrix;
  s21_create_matrix(size, size, &matrix);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix.matrix[i][j] = (double)rand() / ((double)rand() + 0.1);
    }
  }
  check = matrix.matrix[0][0] * matrix.matrix[1][1] -
          matrix.matrix[1][0] * matrix.matrix[0][1];
  ck_assert_int_eq(OK, s21_determinant(&matrix, &result));
  ck_assert_double_eq(check, result);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant5) {
  int size = 5;
  double result = 0;
  matrix_t matrix;
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 43.3;
  matrix.matrix[0][1] = 1;
  matrix.matrix[0][2] = 23;
  matrix.matrix[0][3] = 0;
  matrix.matrix[0][4] = 0.22;
  matrix.matrix[1][0] = 54.2;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 43;
  matrix.matrix[1][3] = 5.45;
  matrix.matrix[1][4] = 0.11;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 0.3;
  matrix.matrix[2][2] = 5;
  matrix.matrix[2][3] = 654;
  matrix.matrix[2][4] = 4.34;
  matrix.matrix[3][0] = 2;
  matrix.matrix[3][1] = 0.54;
  matrix.matrix[3][2] = 6;
  matrix.matrix[3][3] = 0;
  matrix.matrix[3][4] = 55.3;
  matrix.matrix[4][0] = 4;
  matrix.matrix[4][1] = 0.434;
  matrix.matrix[4][2] = 8;
  matrix.matrix[4][3] = 65.33;
  matrix.matrix[4][4] = 2;

  ck_assert_int_eq(OK, s21_determinant(&matrix, &result));
  ck_assert_double_eq_tol(8182890.618145, result, 1e-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant6) {
  int size = 3;
  double result = 0;
  matrix_t matrix;
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 43.3;
  matrix.matrix[0][1] = 1;
  matrix.matrix[0][2] = 23;
  matrix.matrix[1][0] = 54.2;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 43;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 0.3;
  matrix.matrix[2][2] = 5;
  ck_assert_int_eq(OK, s21_determinant(&matrix, &result));
  ck_assert_double_eq_tol(63.91, result, 1e-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant7) {
  int size = 3;
  double result = 0;
  matrix_t matrix;
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 55;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 54;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 89;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 3;
  matrix.matrix[2][1] = 4;
  matrix.matrix[2][2] = 6;
  ck_assert_int_eq(OK, s21_determinant(&matrix, &result));
  ck_assert_double_eq_tol(15136, result, 1e-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant8) {
  int size = 4;
  double result = 0;
  matrix_t matrix;
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 3;
  matrix.matrix[0][1] = 76;
  matrix.matrix[0][2] = 2;
  matrix.matrix[0][3] = 256;
  matrix.matrix[1][0] = 2;
  matrix.matrix[1][1] = 76;
  matrix.matrix[1][2] = 2;
  matrix.matrix[1][3] = 3;
  matrix.matrix[2][0] = 45;
  matrix.matrix[2][1] = 5;
  matrix.matrix[2][2] = 8;
  matrix.matrix[2][3] = 0;
  matrix.matrix[3][0] = 11;
  matrix.matrix[3][1] = 9;
  matrix.matrix[3][2] = 8;
  matrix.matrix[3][3] = 7;
  ck_assert_int_eq(OK, s21_determinant(&matrix, &result));
  ck_assert_double_eq_tol(5073198, result, 1e-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_calc_complements1) {
  matrix_t matrix, result;
  s21_create_matrix(0, -2, &matrix);
  ck_assert_int_eq(s21_calc_complements(&matrix, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_calc_complements2) {
  matrix_t matrix1, matrix2;
  s21_create_matrix(1, 11, &matrix1);
  ck_assert_int_eq(s21_calc_complements(&matrix1, &matrix2), CALCULATION_ERROR);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(s21_calc_complements3) {
  matrix_t matrix1, matrix2;
  s21_create_matrix(1, 1, &matrix1);
  ck_assert_int_eq(s21_calc_complements(&matrix1, &matrix2), OK);
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_calc_complements4) {
  matrix_t matrix, result;
  s21_create_matrix(5, 5, &matrix);

  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 0.3;
  matrix.matrix[0][2] = 2.3;
  matrix.matrix[0][3] = -1;
  matrix.matrix[0][4] = -0.4;
  matrix.matrix[1][0] = 0.2;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[1][3] = 6;
  matrix.matrix[1][4] = 8;
  matrix.matrix[2][0] = 9;
  matrix.matrix[2][1] = -5;
  matrix.matrix[2][2] = -0.5;
  matrix.matrix[2][3] = 0.4;
  matrix.matrix[2][4] = 0.6;
  matrix.matrix[3][0] = 7;
  matrix.matrix[3][1] = 2;
  matrix.matrix[3][2] = 7;
  matrix.matrix[3][3] = 2;
  matrix.matrix[3][4] = 9;
  matrix.matrix[4][0] = -3;
  matrix.matrix[4][1] = -5;
  matrix.matrix[4][2] = -1;
  matrix.matrix[4][3] = 2;
  matrix.matrix[4][4] = -2;

  matrix_t check;
  s21_create_matrix(5, 5, &check);
  check.matrix[0][0] = 756.6;
  check.matrix[0][1] = 1070.48;
  check.matrix[0][2] = 1569.6;
  check.matrix[0][3] = 2085.34;
  check.matrix[0][4] = -2510.56;
  check.matrix[1][0] = 317.04;
  check.matrix[1][1] = 578.9;
  check.matrix[1][2] = 69.48;
  check.matrix[1][3] = 1250.41;
  check.matrix[1][4] = -707.14;
  check.matrix[2][0] = 476.4;
  check.matrix[2][1] = 16.6;
  check.matrix[2][2] = -291.96;
  check.matrix[2][3] = 378.8;
  check.matrix[2][4] = -231.32;
  check.matrix[3][0] = -350.52;
  check.matrix[3][1] = -602.048;
  check.matrix[3][2] = 137.88;
  check.matrix[3][3] = -963.796;
  check.matrix[3][4] = 998.164;
  check.matrix[4][0] = -317.58;
  check.matrix[4][1] = -602.732;
  check.matrix[4][2] = 496.872;
  check.matrix[4][3] = 361.13;
  check.matrix[4][4] = -85.76;

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements5) {
  matrix_t matrix, result;
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  matrix_t check;
  s21_create_matrix(3, 3, &check);

  check.matrix[0][1] = 10;
  check.matrix[0][2] = -20;
  check.matrix[1][0] = 4;
  check.matrix[1][1] = -14;
  check.matrix[1][2] = 8;
  check.matrix[2][0] = -8;
  check.matrix[2][1] = -2;
  check.matrix[2][2] = 4;

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix1) {
  matrix_t matrix1, matrix2;
  s21_create_matrix(1, 0, &matrix1);
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &matrix2), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_matrix2) {
  matrix_t matrix1, matrix2;
  s21_create_matrix(1, 11, &matrix1);
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &matrix2), CALCULATION_ERROR);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(s21_inverse_matrix3) {
  matrix_t matrix1, matrix2;
  s21_create_matrix(1, 1, &matrix1);
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &matrix2), CALCULATION_ERROR);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(s21_inverse_matrix4) {
  matrix_t matrix, result, check;
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 4;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 2;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -3;

  s21_create_matrix(3, 3, &check);
  check.matrix[0][0] = 1;
  check.matrix[0][1] = -0.5;
  check.matrix[0][2] = 0;
  check.matrix[1][0] = -9.5;
  check.matrix[1][1] = 5.5;
  check.matrix[1][2] = 1;
  check.matrix[2][0] = 8;
  check.matrix[2][1] = -4.5;
  check.matrix[2][2] = -1;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix5) {
  matrix_t matrix, result, check;
  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 2;
  matrix.matrix[0][3] = 2;
  matrix.matrix[1][0] = 2;
  matrix.matrix[1][1] = 2;
  matrix.matrix[1][2] = -2;
  matrix.matrix[1][3] = -1;
  matrix.matrix[2][0] = 4;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 2;
  matrix.matrix[2][3] = 2;
  matrix.matrix[3][0] = 2;
  matrix.matrix[3][1] = 2;
  matrix.matrix[3][2] = 3;
  matrix.matrix[3][3] = 4;

  s21_create_matrix(4, 4, &check);
  check.matrix[0][0] = -0.5;
  check.matrix[0][1] = 0;
  check.matrix[0][2] = 0.5;
  check.matrix[0][3] = 0;
  check.matrix[1][0] = 1;
  check.matrix[1][1] = 0.2;
  check.matrix[1][2] = -0.5;
  check.matrix[1][3] = -0.2;
  check.matrix[2][0] = 1;
  check.matrix[2][1] = -0.4;
  check.matrix[2][2] = 0;
  check.matrix[2][3] = -0.6;
  check.matrix[3][0] = -1;
  check.matrix[3][1] = 0.2;
  check.matrix[3][2] = 0;
  check.matrix[3][3] = 0.8;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix6) {
  matrix_t matrix, result, check;
  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 4;
  matrix.matrix[0][1] = 6;
  matrix.matrix[0][2] = 4;
  matrix.matrix[0][3] = 2;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 4;
  matrix.matrix[1][3] = 6;
  matrix.matrix[2][0] = 2;
  matrix.matrix[2][1] = -4;
  matrix.matrix[2][2] = 2;
  matrix.matrix[2][3] = 4;
  matrix.matrix[3][0] = -4;
  matrix.matrix[3][1] = -2;
  matrix.matrix[3][2] = -4;
  matrix.matrix[3][3] = -4;

  s21_create_matrix(4, 4, &check);
  check.matrix[0][0] = -7;
  check.matrix[0][1] = -1;
  check.matrix[0][2] = -6;
  check.matrix[0][3] = -11;
  check.matrix[1][0] = -1;
  check.matrix[1][1] = 0;
  check.matrix[1][2] = -1;
  check.matrix[1][3] = -1.5;
  check.matrix[2][0] = 10;
  check.matrix[2][1] = 1;
  check.matrix[2][2] = 8.5;
  check.matrix[2][3] = 15;
  check.matrix[3][0] = -2.5;
  check.matrix[3][1] = 0;
  check.matrix[3][2] = -2;
  check.matrix[3][3] = -3.5;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_all_tests() {
  Suite *s = suite_create("TESTS");

  TCase *tc_create = tcase_create("s21_create_matrix");
  tcase_add_loop_test(tc_create, s21_create_matrix1, 0, 100);
  tcase_add_test(tc_create, s21_create_matrix2);
  tcase_add_test(tc_create, s21_create_matrix3);
  tcase_add_test(tc_create, s21_create_matrix4);
  tcase_add_test(tc_create, s21_create_matrix5);
  tcase_add_test(tc_create, s21_create_matrix6);
  suite_add_tcase(s, tc_create);

  TCase *tc_eq = tcase_create("s21_eq_matrix");
  tcase_add_loop_test(tc_eq, s21_eq_matrix1, 0, 100);
  tcase_add_test(tc_eq, s21_eq_matrix2);
  tcase_add_test(tc_eq, s21_eq_matrix3);
  tcase_add_loop_test(tc_eq, s21_eq_matrix4, 0, 100);
  tcase_add_test(tc_eq, s21_eq_matrix5);
  suite_add_tcase(s, tc_eq);

  TCase *tc_sum = tcase_create("s21_sum_matrix");
  tcase_add_loop_test(tc_sum, s21_sum_matrix1, 0, 100);
  tcase_add_test(tc_sum, s21_sum_matrix2);
  tcase_add_test(tc_sum, s21_sum_matrix3);
  suite_add_tcase(s, tc_sum);

  TCase *tc_sub = tcase_create("s21_sub_matrix");
  tcase_add_loop_test(tc_sub, s21_sub_matrix1, 0, 100);
  tcase_add_test(tc_sub, s21_sub_matrix2);
  tcase_add_test(tc_sub, s21_sub_matrix3);
  suite_add_tcase(s, tc_sub);

  TCase *tc_mult_num = tcase_create("s21_mult_number");
  tcase_add_loop_test(tc_mult_num, s21_mult_number1, 0, 100);
  tcase_add_test(tc_mult_num, s21_mult_number2);
  suite_add_tcase(s, tc_mult_num);

  TCase *tc_mult_mt = tcase_create("s21_mult_matrix");
  tcase_add_loop_test(tc_mult_mt, s21_mult_matrix1, 0, 100);
  tcase_add_test(tc_mult_mt, s21_mult_matrix2);
  tcase_add_test(tc_mult_mt, s21_mult_matrix3);
  suite_add_tcase(s, tc_mult_mt);

  TCase *tc_transpose = tcase_create("s21_transpose");
  tcase_add_loop_test(tc_transpose, s21_transpose1, 0, 100);
  tcase_add_test(tc_transpose, s21_transpose2);
  suite_add_tcase(s, tc_transpose);

  TCase *tc_det = tcase_create("s21_determinant");
  tcase_add_test(tc_det, s21_determinant1);
  tcase_add_test(tc_det, s21_determinant2);
  tcase_add_test(tc_det, s21_determinant3);
  tcase_add_test(tc_det, s21_determinant4);
  tcase_add_test(tc_det, s21_determinant5);
  tcase_add_test(tc_det, s21_determinant6);
  tcase_add_test(tc_det, s21_determinant7);
  tcase_add_test(tc_det, s21_determinant8);
  suite_add_tcase(s, tc_det);

  TCase *tc_compl = tcase_create("s21_calc_complements");
  tcase_add_test(tc_compl, s21_calc_complements1);
  tcase_add_test(tc_compl, s21_calc_complements2);
  tcase_add_test(tc_compl, s21_calc_complements3);
  tcase_add_test(tc_compl, s21_calc_complements4);
  tcase_add_test(tc_compl, s21_calc_complements5);
  suite_add_tcase(s, tc_compl);

  TCase *tc_inverse = tcase_create("s21_inverse_matrix");
  tcase_add_test(tc_inverse, s21_inverse_matrix1);
  tcase_add_test(tc_inverse, s21_inverse_matrix2);
  tcase_add_test(tc_inverse, s21_inverse_matrix3);
  tcase_add_test(tc_inverse, s21_inverse_matrix4);
  tcase_add_test(tc_inverse, s21_inverse_matrix5);
  tcase_add_test(tc_inverse, s21_inverse_matrix6);
  suite_add_tcase(s, tc_inverse);

  return s;
}

int main() {
  int count;
  Suite *s = suite_all_tests();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  count = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}