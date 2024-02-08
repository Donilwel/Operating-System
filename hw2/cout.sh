#!/usr/bin/bash

# Вывод

print() {
	for a in "$@"; do
		echo "$a"
	done
}

print "$@"
