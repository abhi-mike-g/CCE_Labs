#!/bin/bash

# Prompt user for the file to duplicate
echo "Enter the path to the file you want to duplicate:"
read source_file

# Check if the input file is empty
if [ -z "$source_file" ]; then
    echo "Error: No file provided."
    exit 1
fi

# Check if the source file exists
if [ ! -f "$source_file" ]; then
    echo "Error: File '$source_file' does not exist."
    exit 2
fi

# Get the destination file name (appending _copy to the original filename)
destination_file="${source_file%.*}_copy.${source_file##*.}"

# Duplicate the file using cp command
cp "$source_file" "$destination_file"

# Check if the copy was successful
if [ $? -eq 0 ]; then
    echo "File duplicated successfully as '$destination_file'"
else
    echo "Error: Failed to duplicate the file."
    exit 3
fi


