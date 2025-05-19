#!/bin/bash

update_dictionary() {
	local dictionary="dictionary.txt"
	
	for word in "$@"; do
		if ! grep -iwo "$word" "$dictionary"; then
			echo "$word" >> "$dictionary"
			echo "Pridetas:  $word"
		else
			echo "Jau yra: $word"
		fi
	done
}
