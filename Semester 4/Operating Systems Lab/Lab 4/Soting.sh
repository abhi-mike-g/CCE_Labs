#!/bin/bash

# User-defined sort function
custom_sort() {
    # Sort the input strings using a simple sorting algorithm (Bubble sort)
    arr=("$@")  # Store the arguments in an array
    n=${#arr[@]} # Get the number of arguments (strings)

    # Bubble sort logic to sort the array
    for ((i = 0; i < n; i++)); do
        for ((j = 0; j < n-i-1; j++)); do
            if [[ "${arr[j]}" > "${arr[j+1]}" ]]; then
                # Swap the elements
                temp="${arr[j]}"
                arr[j]="${arr[j+1]}"
                arr[j+1]="$temp"
            fi
        done
    done

    # Print the sorted strings
    echo "${arr[@]}"
}

# Check if at least one argument is passed
if [ $# -eq 0 ]; then
    echo "Usage: $0 <string1> <string2> ... <stringN>"
    exit 1
fi

# Call the custom_sort function with all the command-line arguments
sorted_strings=$(custom_sort "$@")

# Output the sorted strings
echo "$sorted_strings"
