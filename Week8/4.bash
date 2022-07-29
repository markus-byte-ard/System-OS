#!/bin/bash
echo "$USER"
arvo="Tämä on arvo"
echo $arvo
for i in $*; do
	echo $i
done
echo -n "Anna jokin argumentti: "
read argumentti
echo $argumentti
env
