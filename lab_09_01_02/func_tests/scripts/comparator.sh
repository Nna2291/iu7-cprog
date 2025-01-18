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


# echo "$1"
# echo "$2"

if [ ! -f "$1" ] || [ ! -f "$2" ]; then
	echo "Ошибка: Один или оба файла не существуют."
	exit 1
fi

PROG_PATH=$(dirname "$0")
cd "$PROG_PATH"/../.. || exit 1

regular='[-+]?[0-9]*\.?[0-9]+'

numbers1=$(grep -oE "$regular" "$1" | grep -vE 'e[+-]?[0-9]+' | tr '\n' ' ')
numbers2=$(grep -oE "$regular" "$2" | grep -vE 'e[+-]?[0-9]+' | tr '\n' ' ')

if [ "$numbers1" = "$numbers2" ]; then
	if [ $verbose -eq 1 ]; then
		echo "Числа в файлах $1 и $2 совпадают."
	fi
	exit 0
else
	if [ $verbose -eq 1 ]; then
		echo "Числа в файлах $1 и $2 не совпадают."
	fi
	exit 1
fi
