# !/bin/bash
set -e
for i in $(seq 2 2 128)
do
    #echo $i $`cat dump-$i` | grep -o '[0-9]\+\.[0-9]\+'
    echo $i $(echo $`cat dump-$i` | grep -o '[0-9]\+\.[0-9]\+') >> xx.txt
done
