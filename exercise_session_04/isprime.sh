#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

num=$1

if ! [[ "$num" =~ ^-?[0-9]+$ ]]; then
    echo "ERROR: The given input is not a number: $num"
    exit 1
fi

if [ "$num" -lt 1 ]; then
    echo "ERROR: The given input is not a positive integer: $num"
    exit 1
fi


count=$(factor "$num" | wc -w)

if [ "$count" -eq 2 ]; then
    echo "$num is prime"
else
    echo "$num is composite"
fi
