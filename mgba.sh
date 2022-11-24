#!/bin/bash
(
    sleep 5
    echo "started"
)&
sleep 0
echo $1
mgba-qt $1 -g
