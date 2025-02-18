#!/bin/bash

# Prompt the user to enter the directory
read -p "Enter the directory path (or press Enter for the current directory): " directory

# Use the current directory if no input is given
directory="${directory:-.}"

# Check if the directory exists
if [ ! -d "$directory" ]; then
    echo "The specified directory does not exist."
    exit 1
fi

# Find the largest files in the directory and its subdirectories
echo "Displaying the 5 largest files in $directory and its subdirectories:"

# Find all files, sort them by size, and display the top 5 largest
find "$directory" -type f -exec du -h {} + | sort -rh | head -n 5

