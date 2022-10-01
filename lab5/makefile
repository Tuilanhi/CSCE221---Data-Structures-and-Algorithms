CC = g++
CFLAGS = -std=c++17 -Wall -g

all: rbt

rbt: clean red_black_tree.h red_black_tree_tests.cpp
	$(CC) $(CFLAGS) --coverage red_black_tree_tests.cpp && ./a.out && gcov -mr red_black_tree_tests.cpp

rbt_memory_errors: clean red_black_tree.h red_black_tree_tests.cpp
	$(CC) $(CFLAGS) red_black_tree_tests.cpp && valgrind --leak-check=full ./a.out

compile_test: clean red_black_tree.h compile_test.cpp
	$(CC) $(CFLAGS) compile_test.cpp

build_a_tree: clean red_black_tree.h build_a_tree.cpp
	$(CC) $(CFLAGS) build_a_tree.cpp && ./a.out

clean:
	rm -f *.gcov *.gcda *.gcno a.out
