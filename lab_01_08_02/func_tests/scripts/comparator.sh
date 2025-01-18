#!/bin/bash

PROGNAME=$(basename "$0")
verbose=0

usage() {
	echo "Использование: $PROGNAME file1 file2 [-v]"
	return
}

if [ $# -ne 2 ] && [ $# -ne 3 ]; then
	usage
	exit 1
fi

if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
	verbose=1
fi

if [ ! -f "$1" ] || [ ! -f "$2" ]; then
	echo "Ошибка: Один или оба файла не существуют."
	exit 1
fi

regular='Result: .*'

numbers1=$(grep -o "$regular" "$1" | sed 's/Result: //')
numbers2=$(grep -o "$regular" "$2" | sed 's/Result: //')
if [ "$numbers1" = "$numbers2" ]; then
	if [ $verbose -eq 1 ]; then
		echo "Числа в файлах $1 и $2 совпадают."
	fi
	exit 0
else
	if [ $verbose -eq 1 ]; then
		echo "Числа в файлах $1 и $2 не совпадают."
	  exit 1
	fi
fi
