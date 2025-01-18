#!/bin/bash

cd "$(dirname "$0")" || exit 1
PROGNAME=$(basename "$0")

usage() {
	echo "Использование: $PROGNAME file1"
	return
}

if [ $# -ne 1 ] && [ $# -ne 2 ]; then
  usage
  exit 1
fi

cd ../.. || exit 1

read -r args < "$1"

eval set -- "$args"

if [ ! -z "$3" ]; then
  valgrind --leak-check=yes -q "./app.exe" "$1" "$2" "$3"
else
  valgrind --leak-check=yes -q "./app.exe" "$1" "$2"
fi

rc=$?

if [ $rc -ne 0 ]; then
  rm -f "./func_tests/data/out.txt"
  exit 0
fi
rm -f "./func_tests/data/out.txt"
exit 1
