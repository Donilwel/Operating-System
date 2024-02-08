#!/usr/bin/bash

# digit > 0 < 0 == 0 ? mess

var=$1

if [ $var -lt 0 ]; then
	echo "Digit < 0"
elif [ $var -eq 0 ]; then
	echo "Digit == 0"
elif [ $var -gt 0 ]; then
	echo "Digit > 0"
fi
