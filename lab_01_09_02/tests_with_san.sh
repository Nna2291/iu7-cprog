#!/bin/bash

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH" || exit 1

./build_debug_all.sh
./func_tests/scripts/func_tests.sh -v