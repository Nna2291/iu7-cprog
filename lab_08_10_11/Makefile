CC := gcc
CFLAGS := -std=c99 -Werror -Wall -pedantic -Iinc -g -O0
FLAGS_LINK := 
FLAGS_CHECK := -lcheck -lm
# FLAGS_CHECK := -lcheck -lsubunit -lrt -lm
FLAGS_COV := -fprofile-arcs -ftest-coverage -fPIC

app.exe: out out/main.o out/mtr_alloc.o out/mtr_io.o out/mtr_op.o out/mtr_slau.o
	$(CC) $(CFLAGS) $(FLAGS_LINK) -o $@ out/main.o out/mtr_alloc.o out/mtr_io.o out/mtr_op.o out/mtr_slau.o

unit_tests.exe: out out/check_main.o out/compare.o out/check_solve.o out/check_sum.o out/check_multi.o out/mtr_alloc.o out/mtr_io.o out/mtr_op.o out/mtr_slau.o
	$(CC) $(CFLAGS) -o $@ out/check_main.o out/check_solve.o out/check_sum.o out/check_multi.o out/mtr_alloc.o out/mtr_io.o out/mtr_op.o out/compare.o out/mtr_slau.o $(FLAGS_CHECK)

out/check_multi.o: unit_tests/check_multi.c inc/check_multi.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_main.o: unit_tests/check_main.c inc/check_solve.h
	$(CC) $(CFLAGS) -c $< -o $@

out/mtr_slau.o: src/mtr_slau.c inc/mtr_slau.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_solve.o: unit_tests/check_solve.c inc/check_solve.h inc/mtr_op.h inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_sum.o: unit_tests/check_sum.c inc/check_sum.h inc/mtr_op.h inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

out/main.o: src/main.c inc/mtr_alloc.h inc/mtr_io.h inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

out/mtr_alloc.o: src/mtr_alloc.c inc/mtr_alloc.h
	$(CC) $(CFLAGS) -c $< -o $@

out/mtr_io.o: src/mtr_io.c inc/mtr_alloc.h inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

out/mtr_op.o: src/mtr_op.c inc/mtr_alloc.h inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

out/compare.o: unit_tests/compare.c inc/compare.h
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
