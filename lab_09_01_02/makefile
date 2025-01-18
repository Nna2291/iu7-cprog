COMPILER_NAME := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic -g -O0 -Iinc

FLAGS_CHECK := -lcheck -lm
# FLAGS_CHECK := -lcheck -lsubunit -lrt -lm
# FLAGS_LINK := 
FLAGS_COV := -fprofile-arcs -ftest-coverage -fPIC

app.exe: out out/main.o out/item.o out/item_array.o out/utils.o
	$(COMPILER_NAME) $(FLAGS_LINK) -o $@ out/main.o out/item.o out/item_array.o out/utils.o

unit_tests.exe: out out/check_main.o out/item.o out/item_array.o out/check_sort.o out/check_substr.o out/check_read.o out/utils.o
	$(COMPILER_NAME) -g -o $@ out/check_main.o out/item.o out/item_array.o out/check_sort.o out/check_substr.o out/check_read.o out/utils.o $(FLAGS_CHECK)

out/utils.o: src/utils.c inc/utils.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/check_main.o: unit_tests/check_main.c inc/check_sort.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/check_read.o: unit_tests/check_read.c inc/check_read.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/check_sort.o: unit_tests/check_sort.c inc/check_sort.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/check_substr.o: unit_tests/check_substr.c inc/check_substr.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/main.o: src/main.c inc/item.h inc/item_array.h inc/errors.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/item.o: src/item.c inc/item.h inc/errors.h
	$(COMPILER_NAME) $(FLAGS) -c $< -o $@

out/item_array.o: src/item_array.c inc/item_array.h inc/item.h inc/errors.h
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