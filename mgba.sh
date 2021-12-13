#!/bin/bash

pkill mgba-qt

(
	sleep 2
	echo "started"
)&

#echo $1 $2
mgba-qt -2 $1 $2