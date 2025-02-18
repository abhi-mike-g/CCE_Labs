#!/bin/bash

# Check if at least one file is provided as an argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <file1> <file2> ... <fileN>"
    exit 1
fi

# Loop through all the arguments (file names)
for file in "$@"; do
    # Check if the file exists
    if [ -f "$file" ]; then
        # Ask for user confirmation before deleting the file
        read -p "Are you sure you want to delete '$file'? (y/n): " confirm
        if [[ "$confirm" =~ ^[Yy]$ ]]; then
            rm "$file"  # Delete the file
            echo "File '$file' has been deleted."
        else
            echo "File '$file' was not deleted."
        fi
    else
        echo "Error: '$file' does not exist or is not a regular file."
    fi
done
