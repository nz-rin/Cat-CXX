#!/usr/bin/env bash
echo "Compiling Cat Clone"
g++ cat.cxx -o cat -Wall -Wextra -g

if [[ $? != 0 ]]; then
	echo "FAILED"
else
	echo "DONE"
fi
