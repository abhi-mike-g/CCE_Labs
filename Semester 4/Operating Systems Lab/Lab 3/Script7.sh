#!/bin/bash

# Prompt user for the input file
read -p "Enter the filename: " filename

# Check if the file exists
if [ ! -f "$filename" ]; then
    echo "File does not exist."
    exit 1
fi

# Use sed to delete even-numbered lines and save the result back to the same file
sed -i 'n;d' "$filename"

echo "Even-numbered lines have been deleted from $filename."
