CC := gcc
CFLAGS := -std=c99 -Wpedantic -Werror -Wall -g -Iinc -lm
FLAGS_CHECK := -lcheck -lm
# FLAGS_CHECK := -lcheck -lsubunit -lrt -lm

all: app.exe unit_tests.exe

app.exe: out out/main.o out/list.o out/node.o out/calculate.o
	$(CC) -o $@ out/main.o out/list.o out/node.o out/calculate.o -lm

unit_tests.exe: out out/check_main.o out/check_derivative.o out/list.o out/node.o out/calculate.o out/check_value.o out/check_div.o out/check_sum.o
	$(CC) -g -o $@ out/check_main.o out/check_derivative.o out/list.o out/node.o out/calculate.o out/check_value.o out/check_div.o out/check_sum.o $(FLAGS_CHECK)

out/main.o: src/main.c inc/list.h inc/node.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_main.o: unit_tests/check_main.c
	$(CC) $(CFLAGS) -c $< -o $@

out/check_derivative.o: unit_tests/check_derivative.c inc/check_derivative.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_value.o: unit_tests/check_value.c inc/check_value.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_sum.o: unit_tests/check_sum.c inc/check_sum.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_div.o: unit_tests/check_div.c inc/check_div.h
	$(CC) $(CFLAGS) -c $< -o $@

out/list.o: src/list.c inc/list.h inc/node.h
	$(CC) $(CFLAGS) -c $< -o $@

out/node.o: src/node.c inc/node.h inc/node.h
	$(CC) $(CFLAGS) -c $< -o $@

out/calculate.o: src/calculate.c inc/calculate.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf out
	rm -rf .cache
	rm -f *.exe

out:
	mkdir -p out
