#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum other_res { OK = 0, MATRIX_ERROR = 1, CALC_ERROR = 2, MEM_ERROR = 3 };

enum comparison_res { FAILURE = 0, SUCCESS = 1 };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание и удаление матриц
int s21_create_matrix(int rows, int columns, matrix_t *result);  // +
void s21_remove_matrix(matrix_t *A);                             // +
// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);  // +
// Арифметика
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);     // +
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);     // +
int s21_mult_number(matrix_t *A, double number, matrix_t *result);  // +
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    // +
// Операции с матрицами
int s21_transpose(matrix_t *A, matrix_t *result);         // +
int s21_calc_complements(matrix_t *A, matrix_t *result);  // +
int s21_determinant(matrix_t *A, double *result);         // +
int s21_inverse_matrix(matrix_t *A, matrix_t *result);    // +
// Вспомогательные функции
int init_matrix(matrix_t *matrix, int rows, int columns,
                double arr[rows][columns]);
int minor_matrix(int rm_row, int rm_col, matrix_t *src, matrix_t *dest);
double recurs_determinant(matrix_t *A);

#endif  // S21_MATRIX_H