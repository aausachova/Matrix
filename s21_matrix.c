#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int result_code = OK;
  if (A->columns <= 0 || A->rows <= 0) {
    result_code = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    result_code = CALCULATION_ERROR;
  } else {
    double determinant = 0;
    s21_determinant(A, &determinant);
    if (determinant == 0 || fabs(determinant) < 1e-6) {
      result_code = CALCULATION_ERROR;
    } else {
      matrix_t tmp1, tmp2;
      s21_calc_complements(A, &tmp1);
      s21_transpose(&tmp1, &tmp2);
      s21_mult_number(&tmp2, (1.0 / determinant), result);
      s21_remove_matrix(&tmp1);
      s21_remove_matrix(&tmp2);
    }
  }
  return result_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int result_code = OK;
  if (A->columns <= 0 || A->rows <= 0) {
    result_code = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    result_code = CALCULATION_ERROR;
  } else if (A->columns == 1) {
    s21_create_matrix(A->rows, A->columns, result);
    result->matrix[0][0] = A->matrix[0][0];
  } else {
    int sign = 0;
    matrix_t tmp;
    s21_create_matrix(A->rows, A->columns, result);
    s21_create_matrix(A->rows, A->columns, &tmp);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        find_minor(A, &tmp, i, j, A->rows);
        sign = ((i + j) % 2 == 0) ? 1 : (-1);
        result->matrix[i][j] = sign * find_determinant(&tmp, A->rows - 1);
      }
    }
    s21_remove_matrix(&tmp);
  }
  return result_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int result_code = OK;
  if (A->columns <= 0 || A->rows <= 0) {
    result_code = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    result_code = CALCULATION_ERROR;
  } else {
    *result = find_determinant(A, A->rows);
  }
  return result_code;
}

double find_determinant(matrix_t *A, int size) {
  double determinant = 0;
  if (size == 1)
    determinant = A->matrix[0][0];
  else if (size == 2)
    determinant =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  else {
    matrix_t tmp;
    int sign = 1;
    s21_create_matrix(size, size, &tmp);
    for (int i = 0; i < size; i++) {
      find_minor(A, &tmp, 0, i, size);
      determinant += sign * A->matrix[0][i] * find_determinant(&tmp, size - 1);
      sign = -sign;
    }
    s21_remove_matrix(&tmp);
  }
  return determinant;
}

void find_minor(matrix_t *A, matrix_t *tmp, int row_skip, int col_skip,
                int size) {
  int i = 0, j = 0;
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if (row != row_skip && col != col_skip) {
        tmp->matrix[i][j] = A->matrix[row][col];
        j++;
        if (j == size - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_code = 0;

  if (A->columns <= 0 || A->rows <= 0 || B->columns <= 0 || B->rows <= 0) {
    result_code = INCORRECT_MATRIX;
  } else if ((A->columns != B->rows) || (A->rows != B->columns)) {
    result_code = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return result_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int result_code = OK;
  if (A->columns <= 0 || A->rows <= 0) {
    result_code = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return result_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int result_code = OK;
  if (A->columns <= 0 || A->rows <= 0) {
    result_code = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return result_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_code = OK;
  if (A->rows <= 0 || B->rows <= 0 || A->columns <= 0 || B->columns <= 0) {
    result_code = INCORRECT_MATRIX;
  } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else {
    result_code = CALCULATION_ERROR;
  }
  return result_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_code = OK;
  if (A->rows <= 0 || B->rows <= 0 || A->columns <= 0 || B->columns <= 0) {
    result_code = INCORRECT_MATRIX;
  } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else {
    result_code = CALCULATION_ERROR;
  }
  return result_code;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if ((A->rows == B->rows) && (A->columns == B->columns)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) {
          result = FAILURE;
          break;
        }
      }
      if (result == FAILURE) {
        break;
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->columns = 0;
  A->rows = 0;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  result->rows = rows;
  result->columns = columns;
  int result_code = OK;
  if (rows <= 0 || columns <= 0) {
    result_code = INCORRECT_MATRIX;
  } else {
    result->matrix = malloc(sizeof(double *) * rows);
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = malloc(sizeof(double *) * columns);
      for (int f = 0; f < columns; f++) {
        result->matrix[i][f] = 0.0;
      }
    }
  }

  return result_code;
}