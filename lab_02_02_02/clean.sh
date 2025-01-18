#!/bin/bash

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH" || exit 1


rm -f ./*.exe ./*.o ./*.gcda ./*.c.gcov ./*.gcov ./*.gcno ./*.out
rm -rf ./*.dSYM