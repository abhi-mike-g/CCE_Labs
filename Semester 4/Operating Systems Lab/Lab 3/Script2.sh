#!/bin/bash

# Prompt the user for the folder path
read -p "Enter the folder path: " folder_path

# Check if the folder exists
if [ ! -d "$folder_path" ]; then
    echo "The specified folder does not exist."
    exit 1
fi

# Prompt the user for the pattern (string) to search
read -p "Enter the pattern to search for: " pattern

# Use find to search for files containing the pattern
# -type f ensures only regular files are considered
# -exec runs grep to check if the file contains the pattern
# Only the filenames (without path) are displayed
find "$folder_path" -type f -exec grep -l "$pattern" {} \; | while read file; do
    # Extract just the filename from the full path
    echo "$(basename "$file")"
done
