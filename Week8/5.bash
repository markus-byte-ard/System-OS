#!/bin/bash
if [  $# -le 0 ]; then 
	echo "Usage: command"
	exit 1
fi
filelocation="/usr/share/man"
list=$(find $filelocation -name "$1*")
for i in $list; do
	echo $i
done
