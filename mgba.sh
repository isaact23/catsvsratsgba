#!/bin/bash
(
    sleep 2
    echo "started"
)&
sleep 1
echo $1
mgba-qt $1 -g
