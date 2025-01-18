#!/bin/bash

cd "$(dirname "$0")" || exit 1
PROGNAME=$(basename "$0")
verbose=0

usage() {
	echo "Использование: $PROGNAME file1 file2"
	return
}

if [ $# -ne 2 ]; then
  usage
  exit 1
fi

valgrind -q "../../app.exe" < "$1" > "../data/out.txt"
rc=$?
if [ $verbose -eq 1 ] && [ $rc -eq 0 ]; then
  "./comparator.sh" "../data/out.txt" "$2" "-v"
else
  "./comparator.sh" "../data/out.txt" "$2"
fi
rc=$?
rm "../data/out.txt"
if [ $rc -ne 0 ]; then
  exit 1
fi
exit 0
