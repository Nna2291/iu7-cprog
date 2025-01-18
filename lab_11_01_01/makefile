CC := gcc
CFLAGS := -std=c99 -Wpedantic -Werror -Wall -g -Iinc
FLAGS_CHECK := -lcheck -lm
# FLAGS_CHECK := -lcheck -lsubunit -lrt -lm
COVER_FLAGS := -fprofile-arcs -ftest-coverage

all: unit_tests.exe
	./unit_tests.exe
	gcov -o out/ src/my_realization.c -t > out/report.txt

unit_tests.exe: out out/check_main.o out/my_realization.o out/check_snprintf.o
	$(CC) -g -o $@ out/check_main.o out/my_realization.o out/check_snprintf.o $(FLAGS_CHECK) $(COVER_FLAGS)

out/my_realization.o: src/my_realization.c inc/my_realization.h
	$(CC) $(CFLAGS) $(COVER_FLAGS) -c $< -o $@

out/check_main.o: unit_tests/check_main.c
	$(CC) $(CFLAGS) $(COVER_FLAGS) -c $< -o $@

out/check_snprintf.o: unit_tests/check_snprintf.c inc/check_snprintf.h
	$(CC) $(CFLAGS) $(COVER_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf out
	rm -rf .cache
	rm -f *.exe

out:
	mkdir -p out
