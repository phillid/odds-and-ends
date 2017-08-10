#!/bin/bash

if [ -x $1 ]; then
	echo Syntax: $0 [letters]
	exit
fi

< /usr/share/dict/words ./match_pool $1 | \
	grep 'matches$' | \
	awk '{print length($1)" "$1}' | \
	sort -n
