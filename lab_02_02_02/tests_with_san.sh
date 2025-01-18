#!/bin/bash

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH" || exit 1

./build_debug_asan.sh
echo "Tests with address sanitizer"
./func_tests/scripts/func_tests.sh

./build_debug_msan.sh
echo "Tests with memory sanitizer"
./func_tests/scripts/func_tests.sh

./build_debug_ubsan.sh
echo "Tests with undefined behaviour sanitizer"
./func_tests/scripts/func_tests.sh