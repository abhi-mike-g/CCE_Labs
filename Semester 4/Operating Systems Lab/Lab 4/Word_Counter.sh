#!/bin/bash

# Check if at least one option is passed
if [ $# -lt 2 ]; then
    echo "Usage: $0 -linecount|-wordcount|-charcount <file>"
    exit 1
fi

# Get the option and file path from the command line arguments
option="$1"
file="$2"

# Check if the provided file exists
if [ ! -f "$file" ]; then
    echo "Error: File '$file' does not exist."
    exit 2
fi

# Process the option using case statement
case "$option" in
    -linecount)
        # Count the number of lines in the file
        line_count=$(wc -l < "$file")
        echo "Line count: $line_count"
        ;;
    -wordcount)
        # Count the number of words in the file
        word_count=$(wc -w < "$file")
        echo "Word count: $word_count"
        ;;
    -charcount)
        # Count the number of characters in the file
        char_count=$(wc -c < "$file")
        echo "Character count: $char_count"
        ;;
    *)
        # Invalid option
        echo "Error: Invalid option '$option'. Use -linecount, -wordcount, or -charcount."
        exit 3
        ;;
esac
