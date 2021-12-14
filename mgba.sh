#!/bin/bash

pkill mgba-qt

(
	sleep 3
	echo "started"
)&

#echo $1 $2
sleep 1.5
mgba-qt -2 $1 $2