#!/usr/bin/bash
echo "Program;Threads;Test;Temps"

for i in 1 2 4 8 16 32 64;do
    for j in $(seq 1 5);do
        echo "Philosof;$i;$j;$(/usr/bin/time -f %e temp/Philosof $i --quiet 2>&1)"
    done
done
for i in 1 2 4 8 16 32 64;do
    for j in $(seq 1 5);do
        echo "Producer_Consumer;$i;$j;$(/usr/bin/time -f %e temp/Producer_Consumer $i $i --quiet 2>&1)"
    done
done
for i in 1 2 4 8 16 32 64;do
    for j in $(seq 1 5);do
        echo "WriterReader;$i;$j;$(/usr/bin/time -f %e temp/WriterReader $i $i --quiet 2>&1)"
    done
done
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
for i in 1 2 4 8 16 32 64;do
    for j in $(seq 1 5);do
        echo "Producer_Consumer;$i;$j;$(/usr/bin/time -f %e temp/Producer_Consumer_AC $i $i --quiet 2>&1)"
    done
done
for i in 1 2 4 8 16 32 64;do
    for j in $(seq 1 5);do
        echo "Philosof_AC;$i;$j;$(/usr/bin/time -f %e temp/Philosof_AC $i --quiet 2>&1)"
    done
done
