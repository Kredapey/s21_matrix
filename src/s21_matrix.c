#include "s21_matrix.h"

// СОЗДАНИЕ И УДАЛЕНИЕ МАТРИЦ
//___________________________________________________________________

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;
  if (rows <= 0 || columns <= 0) {
    error = MATRIX_ERROR;
  } else {
    result->rows = rows;
    result->columns = columns;
    if (!(result->matrix = (double **)calloc(rows, sizeof(double *)))) {
      result->rows = 0;
      result->columns = 0;
      error = MEM_ERROR;
    } else {
      for (int i = 0; i < rows; i++) {
        if (!(result->matrix[i] = (double *)calloc(columns, sizeof(double)))) {
          error = MEM_ERROR;
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          result->rows = 0;
          result->columns = 0;
        }
      }
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

//___________________________________________________________________

// СРАВНЕНИЕ МАТРИЦ
//___________________________________________________________________

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = FAILURE;
  int match = 0;
  if (A->matrix != NULL && B->matrix != NULL && A->rows > 0 && A->columns > 0 &&
      B->rows > 0 && B->columns > 0) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
            match = 1;
            break;
          }
          if (match == 0) {
            result = SUCCESS;
          }
        }
      }
    }
  }
  return result;
}

//___________________________________________________________________

// АРИФМЕТИКА МАТРИЦ
//___________________________________________________________________

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (A->matrix == NULL || B->matrix == NULL) {
    error = MATRIX_ERROR;
  } else if ((A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) &&
             ((A->rows == B->rows) && (A->columns == B->columns))) {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (error == OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else {
    error = CALC_ERROR;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (A->matrix == NULL || B->matrix == NULL) {
    error = MATRIX_ERROR;
  } else if ((A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) &&
             ((A->rows == B->rows) && (A->columns == B->columns))) {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (error == OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  } else {
    error = CALC_ERROR;
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  if (A->matrix == NULL) {
    error = MATRIX_ERROR;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (A->matrix == NULL || B->matrix == NULL) {
    error = MATRIX_ERROR;
  } else if ((A->rows == B->columns && A->columns == B->rows) &&
             (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0)) {
    error = s21_create_matrix(A->rows, B->columns, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int h = 0; h < B->rows; h++) {
            result->matrix[i][j] += A->matrix[i][h] * B->matrix[h][j];
          }
        }
      }
    }
  } else {
    error = CALC_ERROR;
  }
  return error;
}

//___________________________________________________________________

// ОПЕРАЦИИ С МАТРИЦАМИ
//___________________________________________________________________

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (A->matrix == NULL) {
    error = MATRIX_ERROR;
  } else {
    error = s21_create_matrix(A->columns, A->rows, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  double temp = 0.0;
  matrix_t minor = {0};
  if (A->matrix == NULL) {
    error = MATRIX_ERROR;
  } else if ((A->rows > 0 && A->columns > 0) && (A->rows == A->columns)) {
    if (error == OK) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (error == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            minor_matrix(i, j, A, &minor);
            s21_determinant(&minor, &temp);
            result->matrix[i][j] = temp * pow(-1, i + j);
          }
        }
        s21_remove_matrix(&minor);
      }
    }
  } else {
    error = CALC_ERROR;
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  *result = 0.0;
  int error = OK;
  if (A->matrix == NULL) {
    error = MATRIX_ERROR;
  } else if ((A->rows > 0 && A->columns > 0) && (A->rows == A->columns)) {
    *result = recurs_determinant(A);  // Уходит в рекурсию
  } else {
    error = CALC_ERROR;
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  matrix_t temp_calc = {0}, temp_transpose = {0};
  double det = 0.0;
  if (A->matrix == NULL) {
    error = MATRIX_ERROR;
  } else if ((A->rows > 0 && A->columns > 0) && (A->rows == A->columns)) {
    if (A->rows == 1) {
      if (A->matrix[0][0] != 0) {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = 1.0 / A->matrix[0][0];
      } else {
        error = CALC_ERROR;
      }
    } else {
      s21_determinant(A, &det);
      if (det != 0.0) {
        error = s21_calc_complements(A, &temp_calc);
        if (error == OK) {
          error = s21_transpose(&temp_calc, &temp_transpose);
          if (error == OK) {
            error = s21_mult_number(&temp_transpose, (1 / det), result);
          }
        }
        s21_remove_matrix(&temp_calc);
        s21_remove_matrix(&temp_transpose);
      } else {
        error = CALC_ERROR;
      }
    }
  } else {
    error = CALC_ERROR;
  }
  return error;
}

//___________________________________________________________________

// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
//___________________________________________________________________

int init_matrix(matrix_t *matrix, int rows, int columns,
                double arr[rows][columns]) {
  int error = OK;
  if (matrix->rows != rows || matrix->columns != columns ||
      matrix->matrix == NULL) {
    error = MATRIX_ERROR;
  } else {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        matrix->matrix[i][j] = arr[i][j];
      }
    }
  }
  return error;
}

int minor_matrix(int rm_row, int rm_col, matrix_t *src, matrix_t *dest) {
  int error = OK, rows = 0, columns = 0, dest_rows = 0, dest_columns = 0;
  if (src->matrix != NULL) {
    if ((src->rows > 0 && src->columns > 0) && (src->rows == src->columns)) {
      rows = src->rows - 1;
      columns = src->columns - 1;
      if (dest->matrix == NULL) {
        error = s21_create_matrix(rows, columns, dest);
      } else {
        s21_remove_matrix(dest);
        error = s21_create_matrix(rows, columns, dest);
      }
      if (error == OK) {
        for (int i = 0; i < src->rows; i++) {
          if (i == rm_row) {
            continue;
          }
          dest_columns = 0;
          for (int j = 0; j < src->columns; j++) {
            if (j == rm_col) {
              continue;
            }
            dest->matrix[dest_rows][dest_columns] = src->matrix[i][j];
            dest_columns++;
          }
          dest_rows++;
        }
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = MATRIX_ERROR;
  }
  return error;
}

double recurs_determinant(matrix_t *A) {
  double result = 0.0;
  matrix_t temp = {0};
  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else {
    for (int i = 0; i < A->columns;
         i++) {  // Определитель ищем по первой строке
      minor_matrix(0, i, A, &temp);
      result += (pow(-1, i) * A->matrix[0][i] *
                 recurs_determinant(&temp));  // Будет выполняться пока матрица
                                              // не станет первого порядка
    }
    s21_remove_matrix(&temp);
  }
  return result;
}

//___________________________________________________________________
