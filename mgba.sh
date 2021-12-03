#!/bin/bash

(
	sleep 2
	echo "started"
)&

echo "YES!";
echo $1 $2
echo "NO!";
mgba-qt $1 $2