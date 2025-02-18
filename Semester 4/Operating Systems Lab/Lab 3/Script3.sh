#!/bin/bash

# Use find to locate all .txt files and rename them to .text
find . -type f -name "*.txt" | while read file; do
    # Construct the new file name by replacing .txt with .text
    new_file="${file%.txt}.text"
    
    # Rename the file using mv
    mv "$file" "$new_file"
    
    # Output the renamed file
    echo "Renamed: $file -> $new_file"
done
