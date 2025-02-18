#!/bin/bash

# Function to display the menu
display_menu() {
    echo "Menu:"
    echo "1. Search patterns in the input file"
    echo "2. Delete all occurrences of patterns in the input file"
    echo "3. Exit"
}

# Function to search patterns in the file
search_patterns() {
    echo "Searching for patterns in file '$file'..."
    for pattern in "${patterns[@]}"; do
        echo "Lines containing the pattern '$pattern':"
        grep -n "$pattern" "$file"
    done
}

# Function to delete occurrences of patterns from the file
delete_patterns() {
    echo "Deleting patterns from the file '$file'..."
    temp_file=$(mktemp)  # Create a temporary file to store the updated content
    cp "$file" "$temp_file"  # Copy the content of the original file to the temp file
    for pattern in "${patterns[@]}"; do
        sed -i "s/$pattern//g" "$temp_file"  # Delete the pattern occurrences
    done
    mv "$temp_file" "$file"  # Replace the original file with the updated content
    echo "Patterns deleted successfully."
}

# Check if the script is passed at least one pattern
if [ $# -lt 1 ]; then
    echo "Usage: $0 <pattern1> <pattern2> ... <patternN>"
    exit 1
fi

# Read the input patterns and the input file
patterns=("$@")  # All command-line arguments except the file name
read -p "Enter the input file name: " file

# Check if the input file exists
if [ ! -f "$file" ]; then
    echo "Error: File '$file' does not exist."
    exit 2
fi

# Main menu loop
while true; do
    display_menu
    read -p "Enter your choice (1/2/3): " choice

    case "$choice" in
        1)
            search_patterns  # Call the search function
            ;;
        2)
            delete_patterns  # Call the delete function
            ;;
        3)
            echo "Exiting the script."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter a valid option."
            ;;
    esac
done
