CC := gcc
CFLAGS := -std=c99 -Wpedantic -Werror -Wall -g -Iinc -lm
FLAGS_CHECK := -lcheck -lm
# FLAGS_CHECK := -lcheck -lsubunit -lrt -lm

TESTDIR := ../lab_10_03_common

all: unit

unit: out unit_tests.exe
	./unit_tests.exe

unit_tests.exe: out out/check_main.o out/check_insert.o out/check_remove.o out/check_find.o out/check_min.o out/check_max.o out/check_each.o out/check_clear.o out/associative_array_impl_1.o
	$(CC) -o $@ out/check_main.o out/check_insert.o out/check_remove.o out/check_find.o out/check_min.o out/check_max.o out/check_each.o out/check_clear.o out/associative_array_impl_1.o $(FLAGS_CHECK)

out/associative_array_impl_1.o: associative_array_impl_1.c associative_array.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_main.o: $(TESTDIR)/check_main.c
	$(CC) $(CFLAGS) -c $< -o $@

out/check_insert.o: $(TESTDIR)/check_insert.c $(TESTDIR)/check_insert.h associative_array.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_clear.o: $(TESTDIR)/check_clear.c $(TESTDIR)/check_clear.h associative_array.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_remove.o: $(TESTDIR)/check_remove.c $(TESTDIR)/check_remove.h associative_array.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_find.o: $(TESTDIR)/check_find.c $(TESTDIR)/check_find.h associative_array.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_min.o: $(TESTDIR)/check_min.c $(TESTDIR)/check_min.h associative_array.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_max.o: $(TESTDIR)/check_max.c $(TESTDIR)/check_max.h associative_array.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_each.o: $(TESTDIR)/check_each.c $(TESTDIR)/check_each.h associative_array.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf out *.exe

out:
	mkdir -p out
