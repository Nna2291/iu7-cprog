#!/bin/bash

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH" || exit 1


clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fPIE -fno-omit-frame-pointer -Wvla -c ./*.c
clang -fsanitize=leak -fsanitize=address -fsanitize=undefined -fPIE -fno-omit-frame-pointer ./*.o -o app.exe
