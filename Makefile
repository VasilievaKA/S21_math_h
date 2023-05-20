CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
LFLAGS = -fprofile-arcs -ftest-coverage


all: s21_math.a test gcov_report

clean:
	rm -rf *.o *.a test test1 *.html *.css *.out *.gcda *.gcno *.a_check

check:
	checkmk clean_mode=1 test.check > s21_tests.c

test: s21_math.a_check s21_tests.c
	$(CC) $(CFLAGS) -lcheck $? -coverage -o $@ -lm
	./test

s21_math.a_check: s21_math.c
	$(CC) -c $(CFLAGS) -coverage -std=c11 -pedantic $?
	ar -rcs $@ *.o
	rm -f *.o

rebuild: clean all

gcov_report: test
	./$?
	gcovr -r . --html --html-details -o coverage-report.html
	rm -f s21_tests.gcda s21_tests.gcno
	open coverage-report.html

s21_math.a: s21_math.c
	gcc -Wall -Wextra -Werror s21_math.c -c -o s21_math.o
	ar rc libs21_math.a s21_math.o
	ranlib libs21_math.a
	cp libs21_math.a ./s21_math.a
	rm s21_math.o

style_check:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py ./s21_*.c ./s21_*.h
