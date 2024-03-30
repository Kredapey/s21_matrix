#include "s21_test_matrix.h"

int main() {
  srand(time(0));
  Suite* s;
  SRunner* sr;
  s = s21_matrix_tests();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
  return 0;
}

START_TEST(create_matrix) {
  int res = 0;
  matrix_t new_matrix = {0};
  res = s21_create_matrix(3, 3, &new_matrix);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&new_matrix);

  res = s21_create_matrix(0, 2, &new_matrix);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&new_matrix);

  res = s21_create_matrix(2, 0, &new_matrix);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&new_matrix);
}
END_TEST

START_TEST(eq_matrix) {
  int res = 0;
  matrix_t matrix_1 = {0}, matrix_2 = {0};
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  double arr_1_0[3][3] = {{1.00000001, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_2_0[3][3] = {{1.00000002, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  init_matrix(&matrix_2, 3, 3, arr_2_0);
  res = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  double arr_1_1[3][3] = {{2.00000001, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_2_1[3][3] = {{1.00000002, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_1, 3, 3, arr_1_1);
  init_matrix(&matrix_2, 3, 3, arr_2_1);
  res = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(2, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  double arr_1_2[2][3] = {{1.00000001, 1, 1}, {2, 2, 2}};
  double arr_2_2[3][3] = {{1.00000002, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_1, 2, 3, arr_1_2);
  init_matrix(&matrix_2, 3, 3, arr_2_2);
  res = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 2, &matrix_2);
  double arr_1_3[3][3] = {{1.00000001, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_2_3[3][2] = {{1.00000002, 1}, {2, 2}, {3, 3}};
  init_matrix(&matrix_1, 3, 3, arr_1_3);
  init_matrix(&matrix_2, 3, 2, arr_2_3);
  res = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  double arr_2_4[3][3] = {{1.00000002, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_2, 3, 3, arr_2_4);
  res = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(sum_matrix) {
  int res = 0;
  matrix_t matrix_1 = {0}, matrix_2 = {0}, matrix_myres = {0}, matrix_res = {0};
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  s21_create_matrix(3, 3, &matrix_res);
  double arr_1_0[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_2_0[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_res_0[3][3] = {{2, 2, 2}, {4, 4, 4}, {6, 6, 6}};
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  init_matrix(&matrix_2, 3, 3, arr_2_0);
  init_matrix(&matrix_res, 3, 3, arr_res_0);
  res = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&matrix_myres, &matrix_res), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_myres);
  s21_remove_matrix(&matrix_res);

  s21_create_matrix(3, 3, &matrix_2);
  double arr_2_1[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_2, 3, 3, arr_2_1);
  res = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  double arr_1_2[3][2] = {{1, 1}, {2, 2}, {3, 3}};
  double arr_2_2[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_1, 3, 2, arr_1_2);
  init_matrix(&matrix_2, 3, 3, arr_2_2);
  res = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(sub_matrix) {
  int res = 0;
  matrix_t matrix_1 = {0}, matrix_2 = {0}, matrix_myres = {0}, matrix_res = {0};
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  s21_create_matrix(3, 3, &matrix_res);
  double arr_1_0[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_2_0[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_res_0[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  init_matrix(&matrix_2, 3, 3, arr_2_0);
  init_matrix(&matrix_res, 3, 3, arr_res_0);
  res = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&matrix_myres, &matrix_res), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_myres);
  s21_remove_matrix(&matrix_res);

  s21_create_matrix(3, 3, &matrix_2);
  double arr_2_1[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_2, 3, 3, arr_2_1);
  res = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  double arr_1_2[3][2] = {{1, 1}, {2, 2}, {3, 3}};
  double arr_2_2[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_1, 3, 2, arr_1_2);
  init_matrix(&matrix_2, 3, 3, arr_2_2);
  res = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(mult_matrix) {
  int res = 0;
  matrix_t matrix_1 = {0}, matrix_2 = {0}, matrix_myres = {0}, matrix_res = {0};
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  s21_create_matrix(3, 3, &matrix_res);
  double arr_1_0[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_2_0[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_res_0[3][3] = {{6, 6, 6}, {12, 12, 12}, {18, 18, 18}};
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  init_matrix(&matrix_2, 3, 3, arr_2_0);
  init_matrix(&matrix_res, 3, 3, arr_res_0);
  res = s21_mult_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&matrix_myres, &matrix_res), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_myres);
  s21_remove_matrix(&matrix_res);

  s21_create_matrix(3, 3, &matrix_2);
  double arr_2_1[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_2, 3, 3, arr_2_1);
  res = s21_mult_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  double arr_1_2[3][2] = {{1, 1}, {2, 2}, {3, 3}};
  double arr_2_2[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  init_matrix(&matrix_1, 3, 2, arr_1_2);
  init_matrix(&matrix_2, 3, 3, arr_2_2);
  res = s21_mult_matrix(&matrix_1, &matrix_2, &matrix_myres);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(mult_number) {
  int res = 0;
  matrix_t matrix_1 = {0}, matrix_myres = {0}, matrix_res = {0};
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_res);
  double arr_1_0[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double i = 3.0;
  double arr_res_0[3][3] = {{3, 3, 3}, {6, 6, 6}, {9, 9, 9}};
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  init_matrix(&matrix_res, 3, 3, arr_res_0);
  res = s21_mult_number(&matrix_1, i, &matrix_myres);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&matrix_myres, &matrix_res), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_myres);
  s21_remove_matrix(&matrix_res);

  res = s21_mult_number(&matrix_1, i, &matrix_myres);
  ck_assert_int_eq(res, MATRIX_ERROR);
}
END_TEST

START_TEST(transpose) {
  int res = 0;
  matrix_t matrix_1 = {0}, matrix_myres = {0}, matrix_res = {0};
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_res);
  double arr_1_0[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  double arr_res_0[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  init_matrix(&matrix_res, 3, 3, arr_res_0);
  res = s21_transpose(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&matrix_myres, &matrix_res), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_myres);
  s21_remove_matrix(&matrix_res);

  res = s21_transpose(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, MATRIX_ERROR);
}
END_TEST

START_TEST(calc_complements) {
  int res = 0;
  matrix_t matrix_1 = {0}, matrix_myres = {0}, matrix_res = {0};
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_res);
  double arr_1_0[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double arr_res_0[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  init_matrix(&matrix_res, 3, 3, arr_res_0);
  res = s21_calc_complements(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&matrix_myres, &matrix_res), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_myres);
  s21_remove_matrix(&matrix_res);

  res = s21_calc_complements(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, MATRIX_ERROR);

  s21_create_matrix(3, 2, &matrix_1);
  double arr_1_2[3][2] = {{1, 2}, {4, 7}, {1, 1}};
  init_matrix(&matrix_1, 3, 2, arr_1_2);
  res = s21_calc_complements(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(determinant) {
  int res = 0;
  matrix_t matrix_1 = {0};
  s21_create_matrix(3, 3, &matrix_1);
  double arr_1_0[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double my_res = 0.0, res_dbl = -40.0;
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  res = s21_determinant(&matrix_1, &my_res);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(res_dbl, my_res);
  s21_remove_matrix(&matrix_1);

  res = s21_determinant(&matrix_1, &my_res);
  ck_assert_int_eq(res, MATRIX_ERROR);

  s21_create_matrix(3, 2, &matrix_1);
  double arr_1_2[3][2] = {{1, 2}, {4, 7}, {1, 1}};
  init_matrix(&matrix_1, 3, 2, arr_1_2);
  res = s21_determinant(&matrix_1, &my_res);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(inverse_matrix) {
  int res = 0;
  matrix_t matrix_1 = {0}, matrix_myres = {0}, matrix_res = {0};
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_res);
  double arr_1_0[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double arr_res_0[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  init_matrix(&matrix_1, 3, 3, arr_1_0);
  init_matrix(&matrix_res, 3, 3, arr_res_0);
  res = s21_inverse_matrix(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&matrix_myres, &matrix_res), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_myres);
  s21_remove_matrix(&matrix_res);

  res = s21_inverse_matrix(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, MATRIX_ERROR);

  s21_create_matrix(3, 2, &matrix_1);
  double arr_1_2[3][2] = {{1, 2}, {4, 7}, {1, 1}};
  init_matrix(&matrix_1, 3, 2, arr_1_2);
  res = s21_inverse_matrix(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&matrix_1);

  s21_create_matrix(3, 3, &matrix_1);
  double arr_1_1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  init_matrix(&matrix_1, 3, 3, arr_1_1);
  res = s21_inverse_matrix(&matrix_1, &matrix_myres);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&matrix_1);
}
END_TEST

Suite* s21_matrix_tests(void) {
  Suite* s = suite_create("TEST STARTED");

  TCase* tc_create_matrix = tcase_create("create_matrix");
  suite_add_tcase(s, tc_create_matrix);
  tcase_add_test(tc_create_matrix, create_matrix);

  TCase* tc_eq_matrix = tcase_create("eq_matrix");
  suite_add_tcase(s, tc_eq_matrix);
  tcase_add_test(tc_eq_matrix, eq_matrix);

  TCase* tc_sum_matrix = tcase_create("sum_matrix");
  suite_add_tcase(s, tc_sum_matrix);
  tcase_add_test(tc_sum_matrix, sum_matrix);

  TCase* tc_sub_matrix = tcase_create("sub_matrix");
  suite_add_tcase(s, tc_sub_matrix);
  tcase_add_test(tc_sub_matrix, sub_matrix);

  TCase* tc_mult_matrix = tcase_create("mult_matrix");
  suite_add_tcase(s, tc_mult_matrix);
  tcase_add_test(tc_mult_matrix, mult_matrix);

  TCase* tc_mult_number = tcase_create("mult_number");
  suite_add_tcase(s, tc_mult_number);
  tcase_add_test(tc_mult_number, mult_number);

  TCase* tc_transpose = tcase_create("transpose");
  suite_add_tcase(s, tc_transpose);
  tcase_add_test(tc_transpose, transpose);

  TCase* tc_calc_complements = tcase_create("calc_complements");
  suite_add_tcase(s, tc_calc_complements);
  tcase_add_test(tc_calc_complements, calc_complements);

  TCase* tc_determinant = tcase_create("determinant");
  suite_add_tcase(s, tc_determinant);
  tcase_add_test(tc_determinant, determinant);

  TCase* tc_inverse_matrix = tcase_create("inverse_matrix");
  suite_add_tcase(s, tc_inverse_matrix);
  tcase_add_test(tc_inverse_matrix, inverse_matrix);

  return s;
}
