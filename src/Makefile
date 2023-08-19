CC = g++
CFLAGS = -ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
OS = $(shell uname -s)
TARGET = s21_matrix_oop
TEST_LIBS = -lgtest -lgmock -pthread

all: clean $(TARGET).a

main:
	$(CC) $(FLAGS) $(SOURCES) -o $(TARGET)

$(TARGET).a: $(OBJECTS)
	ar rc $(TARGET).a $(OBJECTS)

%.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@

clean:
	@rm -rf $(TARGET) *.o *.a

test: clean
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
else 
	$(CC) $(OBJECTS) main.cpp -o s21_test $(TST_LIBS) $(CFLAGS)
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
