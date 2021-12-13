#!/bin/bash

# Filename: ex21.sh
#
# Problem: Count the number of quotes each person had in the top 100 quote
# list. Then output the list of names in alphabetical order with the number of quotes each.
cat ex21.input | gawk -F " - " 'BEGIN{
		quoteCount[$1] = 0
	}
	{
		if (match($0,"-")) {
			if($1 in quoteCount) {quoteCount[$1]++}
			else {quoteCount[$1] = 1}
		}
	}
	END {
		asorti(quoteCount, sorted)
		for (i in sorted) {
			if(quoteCount[sorted[i]] != 0) {
				print sorted[i] " had " quoteCount[sorted[i]] " quotes."
			} 
		}
	}'
