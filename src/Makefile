CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic
OS = $(shell uname -s)
PROJECT_NAME = matrix_oop

all: clean a21_matrix_oop.a test

s21_matrix_oop.a: s21_matrix_oop.o
	ar rc s21_matrix_oop.a s21_*.c

s21_matrix_oop.o:
	$(CC) -c $(FLAGS) s21_*.cpp

clean:
	@rm -rf build \
	*.o \
	*.out \
	*.gcno \
	*.gcda \
	report

test: clean
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
else 
	$(CC) $(CFLAGS) -lrt -lpthread -lm -lsubunit -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
endif

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind  --leak-check=full ./test.out
endif

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cpp *.h
	rm -rf .clang-format
