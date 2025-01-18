COMPILER_NAME := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic -g -O0 -Iinc

FLAGS_CHECK := -lcheck -lm
# FLAGS_CHECK := -lcheck -lsubunit -lrt -lm
# FLAGS_LINK := 
FLAGS_COV := -fprofile-arcs -ftest-coverage -fPIC

app.exe: out out/main.o out/sorting.o out/array_io.o out/array_loc.o
	$(COMPILER_NAME) $(FLAGS_LINK) -o $@ out/main.o out/sorting.o out/array_io.o out/array_loc.o

unit_tests.exe: out out/check_main.o out/sorting.o out/array_io.o out/array_loc.o out/check_mysort.o out/check_key.o out/compare.o 
	$(COMPILER_NAME) -o $@ out/check_main.o out/sorting.o out/array_io.o out/array_loc.o out/check_mysort.o out/check_key.o out/compare.o $(FLAGS_CHECK)

out/check_main.o: unit_tests/check_main.c inc/check_mysort.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/check_mysort.o: unit_tests/check_mysort.c inc/check_mysort.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/check_key.o: unit_tests/check_key.c inc/check_key.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/compare.o: unit_tests/compare.c inc/constants.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/main.o: src/main.c inc/sorting.h inc/array_io.h inc/sorting.h inc/errors.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/sorting.o: src/sorting.c inc/sorting.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/array_io.o: src/array_io.c inc/array_io.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/array_loc.o: src/array_loc.c inc/array_loc.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out:
	mkdir -p out

.PHONY: clean
clean:
	rm -rf out
	rm -f *.exe
	rm -f *.gcov

.PHONY: coverage_units
coverage_units: FLAGS += $(FLAGS_COV)
coverage_units: FLAGS_LINK += $(FLAGS_COV)
coverage_units: FLAGS_CHECK += $(FLAGS_COV)
coverage_units: unit_tests.exe out/check_main.o out/sorting.o out/array_io.o out/array_loc.o out/check_mysort.o out/check_key.o out/compare.o
	./unit_tests.exe
	gcov -t -o ./out out/sorting.c > ./out/sorting.c.gcov

.PHONY: coverage_func
coverage_func: FLAGS += $(FLAGS_COV)
coverage_func: FLAGS_LINK += $(FLAGS_COV)
coverage_func: FLAGS_CHECK += $(FLAGS_COV)
coverage_func: app.exe out/main.o out/sorting.o out/array_io.o out/array_loc.o
	./func_tests/scripts/func_tests.sh
	gcov -t -o ./out out/sorting.c > ./out/sorting.c.gcov
	gcov -t -o ./out out/main.c > ./out/main.c.gcov
	gcov -t -o ./out out/array_io.c > ./out/array_io.c.gcov
	gcov -t -o ./out out/array_loc.c > ./out/array_loc.c.gcov