#!/bin/bash

out="out.txt"
> "$out"
sum=0
count=0

for file in measurements{1..5}.txt; do
    grep -E '^Temperature:' "$file" >> "$out"

    temps=$(grep -Eo 'Temperature: *[0-9]+(\.[0-9]+)?' "$file" | grep -Eo '[0-9]+(\.[0-9]+)?')
    for t in $temps; do
        sum=$(echo "$sum + $t" | bc)
        count=$((count + 1))
    done
done

if [ $count -gt 0 ]; then
    avg=$(echo "scale=2; $sum / $count" | bc)
    echo "Average temperature: $avg"
else
    echo "No data."
fi
