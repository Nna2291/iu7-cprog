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

if [ $verbose -eq 1 ]; then
	cmp "$1" "$2"
else
	cmp -s "$1" "$2"
fi

if [ $? -eq 0 ]; then
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
