#!/usr/bin/bash
echo "Program;Threads;Test;Temps"

for i in 1 2 4 8 16 32 64;do
    for j in $(seq 1 5);do
        echo "Test-and-set;$i;$j;$(/usr/bin/time -f %e temp/Perftest $i --quiet 2>&1)"
    done
done
for i in 1 2 4 8 16 32 64;do
    for j in $(seq 1 5);do
        echo "Test-and-test-and-set;$i;$j;$(/usr/bin/time -f %e temp/Perftest2 $i --quiet 2>&1)"
    done
done
