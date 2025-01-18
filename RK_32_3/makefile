CC := gcc
CFLAGS := -std=c99 -Wpedantic -Werror -Wall -g -Iinc

app.exe: out out/main.o out/list.o out/node.o
	$(CC) -o $@ out/main.o out/list.o out/node.o

out/main.o: src/main.c inc/list.h inc/node.h
	$(CC) $(CFLAGS) -c $< -o $@

out/list.o: src/list.c inc/list.h inc/node.h
	$(CC) $(CFLAGS) -c $< -o $@

out/node.o: src/node.c inc/node.h inc/node.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf out
	rm -f *.exe

out:
	mkdir -p out
