#!/bin/bash

PROG_PATH=$(dirname "$0")

cd "$PROG_PATH" || exit 1

if [ ! -f "./build_coverage.sh" ]; then
  echo "Файла для сборки с покрытием не существует"
  exit 1
fi
./build_coverage.sh
./func_tests/scripts/func_tests.sh -v
gcov main.c
exit 0