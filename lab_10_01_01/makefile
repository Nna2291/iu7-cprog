CC := gcc
CFLAGS := -std=c99 -Werror -Wall -pedantic -Iinc -g -O0
FLAGS_LINK := 
FLAGS_CHECK := -lcheck -lm
# FLAGS_CHECK := -lcheck -lsubunit -lrt -lm
FLAGS_COV := -fprofile-arcs -ftest-coverage -fPIC

all: app.exe unit_tests.exe

app.exe: out out/main.o out/list.o out/node.o out/dino.o out/utils.o
	$(CC) $(CFLAGS) $(FLAGS_LINK) -o $@ out/main.o out/list.o out/node.o out/dino.o out/utils.o

unit_tests.exe: out out/check_main.o out/check_read.o out/check_pop.o out/list.o out/node.o out/dino.o out/utils.o out/check_sort.o out/check_find.o out/check_append.o
	$(CC) -g -o $@ out/check_main.o out/check_read.o out/check_pop.o out/list.o out/node.o out/dino.o out/utils.o out/check_sort.o out/check_find.o out/check_append.o $(FLAGS_CHECK)

out/check_main.o: unit_tests/check_main.c
	$(CC) $(CFLAGS) -c $< -o $@

out/check_read.o: unit_tests/check_read.c inc/check_read.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_pop.o: unit_tests/check_pop.c inc/check_pop.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_sort.o: unit_tests/check_sort.c inc/check_sort.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_find.o: unit_tests/check_find.c inc/check_find.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_append.o: unit_tests/check_append.c inc/check_append.h
	$(CC) $(CFLAGS) -c $< -o $@

out/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

out/utils.o: src/utils.c
	$(CC) $(CFLAGS) -c $< -o $@

out/list.o: src/list.c
	$(CC) $(CFLAGS) -c $< -o $@

out/node.o: src/node.c
	$(CC) $(CFLAGS) -c $< -o $@

out/dino.o: src/dino.c
	$(CC) $(CFLAGS) -c $< -o $@

func: app.exe
	./func_tests/scripts/func_tests.sh

.PHONY: coverage_func
coverage_func: CFLAGS += $(FLAGS_COV)
coverage_func: FLAGS_LINK += $(FLAGS_COV)
coverage_func: FLAGS_CHECK += $(FLAGS_COV)
coverage_func: app.exe out/main.o out/mtr_alloc.o out/mtr_io.o out/mtr_op.o
	./func_tests/scripts/func_tests.sh
	gcov -t -o ./out out/mtr_alloc.c > ./out/mtr_alloc.c.gcov
	gcov -t -o ./out out/main.c > ./out/main.c.gcov
	gcov -t -o ./out out/mtr_io.c > ./out/mtr_io.c.gcov
	gcov -t -o ./out out/mtr_op.c > ./out/mtr_op.c.gcov


# .PHONY: out
out:
	mkdir -p out

.PHONY: clean
clean:
	rm -rf *.exe
	rm -rf out
	rm -rf .cache
