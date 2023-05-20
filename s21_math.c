#include <stdio.h>
#include <stdlib.h>
#include "s21_math.h"

int s21_isinf(long double x) {
    int res = 0;
    if (x == S21_MINUS_INF || x == S21_PLUS_INF) res = 1;
    return res;
}

int s21_isnan(long double x) {
    int res = 0;
    if (x != x) res = 1;
    return res;
}

int s21_abs(int x) {
    return (x > 0) ? x : -x;
}

long double s21_fabs(double x) {
    x = (x > 0) ? x : -x;
    return x;
}

long double s21_floor(double x) {
    long double xInt = (long long int)x;
    if (s21_isinf(x) || s21_isnan(x) || x == 0.0) {
        xInt = x;
    } else {
        long double ostatok = (long double)(x - xInt);
        if (x < 0.0 && ostatok != 0) xInt -= 1.0;
    }
    return xInt;
}

long double s21_ceil(double x) {
    long double res = x;

    res = (long long)x;
    if (x - res >= 1.0 || x - res <= -1.0) {
        res = x;
    } else {
        if (res < x) res += 1.0;
    }
    return (is_nan(x) || is_inf(x)) ? x : res;
}

long double s21_sin(double x) {
    double sum = 0;
    if (x == S21_PLUS_INF || x == S21_MINUS_INF || x == S21_NAN) {
        sum = S21_NAN;
    } else {
        while (x > 2 * S21_PI || x < -2 * S21_PI) {
            if (x > 2 * S21_PI) {
                x -= 2 * S21_PI;
            } else {
                x += 2 * S21_PI;
            }
        }
        double tmp = x;
        sum = x;
        for (int n = 3; s21_fabs(tmp) > EPS; n += 2) {
            tmp *= -x * x / n / (n - 1);
            sum += tmp;
        }
    }
    return sum;
}

long double s21_cos(double x) {
    double sum = 0;
    if (x == S21_PLUS_INF || x == S21_MINUS_INF || x == S21_NAN) {
        sum = S21_NAN;
    } else {
        while (x > 2 * S21_PI || x < -2 * S21_PI) {
            if (x > 2 * S21_PI) {
                x -= 2 * S21_PI;
            } else {
                x += 2 * S21_PI;
            }
        }
        double tmp = 1.0;
        sum = 1.0;
        for (int n = 1; s21_fabs(tmp) > EPS; n++) {
            tmp *= -x * x / (2*n - 1) / (2*n);
            sum += tmp;
        }
    }
    return sum;
}

long double s21_tan(double x) {
    double sum = 0;
    if (x == S21_PLUS_INF || x == S21_MINUS_INF || x == S21_NAN) {
        sum = S21_NAN;
    } else {
        sum = s21_sin(x)/ s21_cos(x);
    }
    return sum;
}

long double s21_sqrt(double x) {
    if (__builtin_signbit(x)) {
        return S21_NAN;
    }
    if (is_inf(x)) {
        return S21_HUGE_VAL;
    }
    return s21_pow(x, 0.5);
}

long double s21_pow(double base, double exp) {
    if (base == 1 || exp == 0 || (base == -1 && (exp == S21_MINUS_INF || exp == S21_PLUS_INF))) {
        return 1;
    } else if ((s21_fabs(base) < 1 && exp == S21_MINUS_INF) || (s21_fabs(base) > 1 && exp == S21_PLUS_INF) ||
               (base == S21_MINUS_INF && ((exp > 0 && (int)exp % 2 == 0) || exp == S21_PLUS_INF)) ||
               (base == S21_PLUS_INF && exp > 0)) {
        return S21_PLUS_INF;
    } else if ((base < 0 && (int)exp - exp != 0) || (base != base && exp != exp)) {
        return S21_NAN;
    } else if ((base == 0 && exp > 0) || (s21_fabs(base) > 1 && exp == S21_MINUS_INF) ||
               (s21_fabs(base) < 1 && exp == S21_PLUS_INF) ||
               (base == s21_NEGZERO && (exp > 0 && (int)exp % 2 == 0)) ||
               (base == S21_MINUS_INF && (exp < 0 && (int)exp % 2 == 0)) ||
               (base == S21_PLUS_INF && exp < 0)) {
        return 0;
    } else if ((base == s21_NEGZERO && (exp > 0 && (int)exp % 2 != 0)) ||
               (base == S21_MINUS_INF && (exp < 0 && (int)exp % 2 != 0))) {
        return s21_NEGZERO;
    } else if (base == S21_MINUS_INF && (exp > 0 && (int)exp % 2 != 0)) {
        return S21_MINUS_INF;
    }
    int flag = 0;
    if (base < 0) {
        if ((int)exp % 2 != 0) {
            flag = 1;
        }
        base = s21_fabs(base);
    }
    return flag ? -s21_exp(exp * s21_log(base)) : s21_exp(exp * s21_log(base));
}

long double s21_fmod(double x, double y) {
    if (is_nan(x) || is_nan(y) || is_inf(x) || s21_fabs(y) < EPS || (is_inf(x) && is_inf(y))) {
        return S21_NAN;
    }
    if (s21_fabs(x) < EPS) return 0;
    if (is_inf(y)) return x;
    double a, b, result;
    a = x/y;
    if (x < 0 && y < 0) {
        b = s21_abs(a);
    } else if (x < 0 || y < 0) {
        b = (-1) * s21_abs(a);
    } else {
        b = s21_abs(a);
    }
    result = x - b * y;
    if (y == 0) {
        result = 0 / 0.0;
    }
    return result;
}

long double s21_log(double x) {
    long double res = 0;
    int ex_pow = 0;
    long double y = 0;
    long double yNext = 0;
    if (x == 0) {
        res = S21_MINUS_INF;
    } else if (x < 0.0 || x == S21_NAN || x == S21_MINUS_INF) {
        res = S21_NAN;
    } else if (x == S21_PLUS_INF) {
        res = S21_PLUS_INF;
    } else {
        for (; x >= S21_EXP; x /= S21_EXP, ex_pow++) {}
        for (int i = 0; i < 100; i++) {
            y = yNext;
            yNext = y + (2 * (x - s21_exp(y)) / (x + s21_exp(y)));
        }
        res = yNext + ex_pow;
    }
    return res;
}


long double s21_exp(double x) {
    long double r = 1, y = 1;
    long double i = 1;
    int z = 0;
    if (x < 0) {
        x *= -1;
        z = 1;
    }
    while (s21_fabs(r) > 1e-17) {
    r *= x / i;
        i++;
        y += r;
        if (y > 1.7976931348623157e308) {
            y = 1.0 / 0.0;
            break;
        }
    }
    if (z == 1) {
        if (y > 1.7976931348623157e308)
            y = 0;
        else
            y = 1. / y;
    }
    if (y > 1.7976931348623157e308)
        y = 1.0 / 0.0;
    return y;
}

long double s21_atan(double x) {
    long double result = 0.0;

    if (s21_fabs(x) == S21_HUGE_VAL) {
        result = S21_PI / 2;
        if (x < 0) {
            result = -result;
        }
    } else if (s21_fabs(x) == 1) {
        result = 0.7853981634;
        if (x < 0) {
            result = -result;
        }
    } else if (s21_fabs(x) < 1) {
        for (int i = 0; i < 500; i++) {
            result += s21_pow(-1, i) * s21_pow(x, (1 + (2 * i))) / (1 + (2 * i));
        }
    } else {
        for (int i = 0; i < 500; i++) {
            result += s21_pow(-1, i) * s21_pow(x, (-1 - (2 * i))) / (1 + (2 * i));
        }
        result = (S21_PI * s21_fabs(x)) / (2 * x) - result;
    }

    return result;
}

long double s21_acos(double x) {
    long double res = 0;
    if (x == 1) return 0;
    if (x == 0) return S21_PI / 2;
    if (x == -1) return S21_PI;
    if (x > 0 && x < 1) {
        res = s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x);
    } else if (x > -1 && x < 0) {
        res = S21_PI + s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x);
    } else {
        res = S21_NAN;
    }
  return res;
}

long double s21_asin(double x) {
    long double res = 0;
    if (x == 1)
        res = S21_PI / 2;
    if (x == 0)
        res = 0;
    if (x == -1)
        res = S21_PI / 2;
    if (s21_abs(x) < 1)
        res = s21_atan(x / (s21_sqrt(1 - s21_pow(x, 2))));
    else
        res = S21_NAN;
    return res;
}
