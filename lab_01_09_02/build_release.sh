#!/bin/bash

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH" || exit 1


gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c main.c
gcc main.o -o app.exe -lm
