CC = gcc
CC_FLAGS = -Wall -Werror -Wextra --std=c11
NAME = s21_matrix.a test
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
else
	TEST_LIBS = -lcheck -lm -lpthread
endif
OBJECTS = s21_matrix.o
SOURCES = s21_matrix.c

.PHONY: all clean test s21_matrix.a gcov_report

all: $(NAME)

test: s21_test_matrix.o s21_matrix.a $(OBJECTS)
	$(CC) $(OBJECTS) s21_test_matrix.o -o test s21_matrix.a $(TEST_LIBS)
	./test

s21_matrix.o: s21_matrix.c
	$(CC) $(CC_FLAGS) -c s21_matrix.c -g $(TEST_LIBS)

s21_test_matrix.o: s21_test_matrix.c
	$(CC) $(CC_FLAGS) -c s21_test_matrix.c

gcov_report: s21_matrix.a
	$(CC) $(CC_FLAGS) --coverage s21_test_matrix.c s21_matrix.c -o gcov_test s21_matrix.a $(TEST_LIBS)
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

style: s21_matrix.a
	clang-format -n *.c *.h

s21_matrix.a: s21_matrix.o
	$(CC) -c $(SOURCES) $(TEST_LIBS)
	ar rcs s21_matrix.a $(OBJECTS)

valgrind: s21_matrix.a test
	CK_FORK=no valgrind --track-origins=yes --leak-check=full --leak-resolution=med --show-leak-kinds=all -s ./test

lik: s21_matrix.a test
	CK_FORK=no leaks -atExit -- ./test

cppcheck: 
	cppcheck *.h *.c

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf gcov_test
	rm -rf test
	rm -rf *.txt
	rm -rf *.info
	rm -rf *.out
	rm -rf *.dSYM
	rm -R report
