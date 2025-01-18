#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fPIE -fno-omit-frame-pointer -c main.c -o main.o
clang -fsanitize=leak -fsanitize=address -fsanitize=undefined -fPIE -fno-omit-frame-pointer main.o -o app.exe
