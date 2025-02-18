#!/bin/bash

# Check if the user has provided a filename as an argument
if [ -z "$1" ]; then
    echo "Please provide a filename or directory as an argument."
    exit 1
fi

# Check if the provided file is a directory
if [ -d "$1" ]; then
    echo "$1 is a directory."
# Check if the provided file is a regular file
elif [ -f "$1" ]; then
    echo "$1 is a regular file."
# If it's neither a directory nor a regular file (could be other types like symbolic link)
else
    echo "$1 is neither a regular file nor a directory."
fi


