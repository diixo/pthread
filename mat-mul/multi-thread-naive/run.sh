#!/bin/bash 
set -e
for i in $(seq 2 2 128)
do
    ./mat-mul $i
done
