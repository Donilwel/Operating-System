#!/usr/bin/bash

#линейный поиск строки в массиве

linear_search() {
	local targ=$1
	array=("pen" "pineapple" "apple" "not_pen")
	for el in "${array[@]}"; do
		if [[ "$el" == "$targ" ]]; then
			echo "\"$targ\" catch!"
			return 
		fi
	done
	echo "no \"$targ\" catch("
}

linear_search $1
