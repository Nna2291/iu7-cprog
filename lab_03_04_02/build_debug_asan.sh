#!/bin/bash

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH" || exit 1


clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -g -fsanitize=address -fno-omit-frame-pointer -Wvla -c ./*.c
clang -fsanitize=address -fno-omit-frame-pointer ./*.o -o app.exe
