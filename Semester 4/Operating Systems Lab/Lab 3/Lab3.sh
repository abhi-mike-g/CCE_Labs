#!/bin/bash

# Prompt the user to enter the directory path
read -p "Enter the directory path: " directory

# Check if the directory exists
if [ ! -d "$directory" ]; then
    echo "The specified directory does not exist."
    exit 1
fi

# Find the 5 largest files in the directory and its subdirectories
echo "Displaying the 5 largest files in $directory and its subdirectories:"

# Find all files, sort them by size, and display the top 5 largest files
find "$directory" -type f -exec du -h {} + | sort -rh | head -n 5

