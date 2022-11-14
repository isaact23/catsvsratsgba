#!/bin/bash
(
    sleep 1
    echo "started"
)&
sleep 0.5
echo $1
mgba-qt $1 -g4
