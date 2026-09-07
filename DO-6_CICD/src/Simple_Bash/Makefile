CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror

all: s21_cat s21_grep

build: s21_cat s21_grep

s21_cat: cat/s21_cat.c
	$(CC) $(FLAGS) cat/s21_cat.c -o cat/s21_cat

s21_grep: grep/s21_grep.c
	$(CC) $(FLAGS) grep/s21_grep.c -o grep/s21_grep

cf:
	cp ../../materials/linters/.clang-format .
	clang-format -i cat/*.c cat/*.h
	clang-format -i grep/*.c grep/*.c
	rm .clang-format

clang:
	cp ../../materials/linters/.clang-format .
	clang-format -n -Werror cat/*.c cat/*.h
	clang-format -n -Werror grep/*.c grep/*.h
	rm .clang-format

rebuild: clean s21_cat s21_grep

clean:
	rm cat/s21_cat
	rm grep/s21_grep
	rm cat/s21_cat_errors.txt
	rm grep/s21_grep_errors.txt
	
test: s21_cat s21_grep
	cd cat && bash s21_cat_test.sh
	cd grep && bash s21_grep_test.sh
