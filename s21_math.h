#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#define S21_PI 3.14159265358979323846264338327950288
#define S21_PLUS_INF 1.0 / 0.0
#define S21_MINUS_INF -1.0 / 0.0
#define S21_ME 2.71828182845904523536028747135266250
#define EPS 1e-6
#define S21_EXP 2.7182818284590452353602874713527
#define S21_SQRT2 1.41421356237309504880
#define s21_NEGZERO -1e-20

#define S21_HUGE_VAL (__builtin_inff())
/*
 возвращает значение NaN с плавающей запятой
  */
#define S21_NAN (__builtin_nanf(""))
/*
 проверка на бесконечность: возвращает 1, если бесконечность, -1, если -бесконечность и 0, если конечна
  */
#define is_inf(x) __builtin_isinf_sign(x)
/*
 проверить значение nan: возвращает 1, если NaN и 0, если нет
 */
#define is_nan(x) __builtin_isnan(x)
#define is_finite(x) __builtin_isfinite(x)


int s21_abs(int x);
int s21_isinf(long double x);
int s21_isnan(long double x);
long double s21_fabs(double x);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sqrt(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_fmod(double x, double y);
long double s21_floor(double x);
long double s21_ceil(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_atan(double x);


#endif  //  SRC_S21_MATH_H_
