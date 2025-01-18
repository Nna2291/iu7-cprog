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

"../../app.exe" < "$1" > "out.txt"

if [ $verbose -eq 1 ]; then
  "./comparator.sh" "out.txt" "$2" "-v"
else
  "./comparator.sh" "out.txt" "$2"
fi
rc=$?
rm "out.txt"
if [ $rc -ne 0 ]; then
  exit 1
fi
exit 0
