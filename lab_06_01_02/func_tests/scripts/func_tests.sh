#!/bin/bash

PROG_PATH=$(dirname "$0")
PROGNAME=$(basename "$0")
verbose=0

usage() {
	echo "Использование: $PROGNAME [-v]"
	return
}

if [ $# -ne 0 ] && [ $# -ne 1 ]; then
	usage
	exit 1
fi
if [ "$1" == "-v" ] || [ "$1" == "--verbose" ]; then
	verbose=1
fi

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH"/../.. || exit 1

if [ ! -f "./app.exe" ]; then
  echo "Исполняемого файла не существует"
  exit 1
fi

positive_counter=0
positive_files=0
negative_files=0
negative_counter=0

for file in func_tests/data/pos_**_args.txt
do
  (( positive_files++ ))
  size=${#file}
  out_file=${file:: size-8}out.txt

  "./func_tests/scripts/pos_case.sh" "$file" "$out_file"
  rc=$?
  if [ $rc -eq 0 ]; then
    if [ $verbose -eq 1 ]; then
      echo "POS TEST  $file  PASS"
    fi
    (( positive_counter++ ))
  else
    if [ $verbose -eq 1 ]; then
      echo "POS TEST  $file  FAIL"
    fi
  fi
done

echo "POS TEST PASSED $positive_counter/$positive_files"


for file in ./func_tests/data/neg_**_args.txt
do
  (( negative_files++ ))
  "./func_tests/scripts/neg_case.sh" "$file"
  rc=$?
  if [ $rc -eq 0 ]; then
    if [ $verbose -eq 1 ]; then
      echo "NEG TEST  $file  PASS"
    fi
    (( negative_counter++ ))
  else
    if [ $verbose -eq 1 ]; then
      echo "NEG TEST  $file  FAIL"
    fi
  fi
done

echo "NEG TEST PASSED $negative_counter/$negative_files"

if [ "$positive_counter" -ne  "$positive_files" ] || [ "$negative_counter" -ne  "$negative_files" ]; then
  exit 1
fi
exit 0