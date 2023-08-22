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
	rm -rf $(TARGET) *.o *.a test *.gcno *.gcda *.dSYM report gcov_report

test: clean
	$(CC) $(SOURCES) tests.cpp -o test $(TEST_LIBS) $(CFLAGS)
	./test

gcov_report:
	$(CC) $(SOURCES) --coverage tests.cpp -o gcov_report $(TEST_LIBS) $(CFLAGS)
	./gcov_report
	lcov -t report -o gcov_report.info -c -d . --no-external
	genhtml -o report gcov_report.info
	open ./report/index.html
	rm -rf *.gcno *.gcda *.dSYM gcov_report.* gcov_report

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
