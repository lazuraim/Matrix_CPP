CC = g++
CFLAGS = -ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
SOURCES = $(wildcard s21*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
TARGET = s21_matrix_oop
TEST_LIBS = -lgtest -lgmock -pthread

all: $(TARGET).a

main:
	$(CC) $(FLAGS) $(SOURCES) -o $(TARGET)

$(TARGET).a: $(OBJECTS)
	ar rc $(TARGET).a $(OBJECTS)

%.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -rf $(TARGET) *.o *.a

test:
	$(CC) $(SOURCES) tests.cpp -o test $(TEST_LIBS) $(CFLAGS)
	./test

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
else
	valgrind  --leak-check=full ./test
endif

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cpp *.h
	rm -rf .clang-format
