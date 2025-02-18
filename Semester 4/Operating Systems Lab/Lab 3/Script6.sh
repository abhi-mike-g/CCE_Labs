#!/bin/bash

# Loop through all files in the current directory
for file in *; do
    # Check if it's a regular file (not a directory)
    if [ -f "$file" ]; then
        # Use sed to replace 'ex:' with 'Example:' at the start of the line or after a period.
        sed -i -E 's/(\bex:|\.\s*ex:)/\1Example:/g' "$file"
        echo "Modified file: $file"
    fi
done
