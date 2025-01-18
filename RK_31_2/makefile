CC := gcc
CFLAGS := -Werror -Wall -pedantic -std=c99 -Iinc

app.exe: out out/main.o out/arr_op.o out/arr_io.o out/arr_loc.o
	$(CC) -o $@ out/main.o out/arr_op.o out/arr_io.o out/arr_loc.o

out/main.o: src/main.c inc/arr_op.h inc/arr_io.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/arr_op.o: src/arr_op.c inc/arr_op.h inc/arr_loc.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/arr_io.o: src/arr_io.c inc/arr_io.h inc/arr_loc.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/arr_loc.o: src/arr_loc.c inc/arr_loc.h
	$(CC) $(CFLAGS) -o $@ -c $<

out:
	mkdir -p out

clean:
	rm -rf out
	rm -f *.exe
