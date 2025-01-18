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

"../../app.exe" < "$1" > /dev/null

rc=$?

if [ $rc -ne 0 ]; then
  exit 0
fi
exit 1
