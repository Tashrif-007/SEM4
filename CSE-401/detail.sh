#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

directory=$1

if [ ! -d "$directory" ]; then
    echo "Error: '$directory' is not a directory."
    exit 1
fi

echo "File_Name      LOC      Word      Character"
echo "---------------------------------------"

find "$directory" -type f -name "*.c" -or -name "*.cpp" | while read -r file; do
    loc=$(wc -l < "$file")
    word=$(wc -w < "$file")
    char=$(wc -c < "$file")
    echo "$(basename "$file")      $loc    $word    $char"
done
