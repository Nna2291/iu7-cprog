#!/bin/bash

cd "$(dirname "$0")" || exit 1
PROGNAME=$(basename "$0")
verbose=0

usage() {
	echo "Использование: $PROGNAME file1 file2"
	return
}
out_file="$2"
if [ $# -ne 2 ]; then
  usage
  exit 1
fi

PROG_PATH=$(dirname "$0")
#cd "$PROG_PATH"|| exit 1

cd ../.. || exit 1

read -r args < "$1"

eval set -- "$args"

"./app.exe" "$@" > "out.txt"

rc=$?

if [ $verbose -eq 1 ] && [ $rc -eq 0 ]; then
  "./func_tests/scripts/comparator.sh" "out.txt" "$out_file" "-v"
else
  "./func_tests/scripts/comparator.sh" "out.txt" "$out_file"
fi
rc=$?
rm "out.txt"
if [ $rc -ne 0 ]; then
  exit 1
fi
exit 0
