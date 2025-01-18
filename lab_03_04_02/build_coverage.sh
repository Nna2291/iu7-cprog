#!/bin/bash

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH" || exit 1

gcc -std=c99 -Wall -Werror -O0 -fprofile-arcs -ftest-coverage -Wvla -c ./*.c
gcc ./*.o -fprofile-arcs -ftest-coverage -o app.exe -lm
