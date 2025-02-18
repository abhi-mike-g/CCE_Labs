#!/bin/bash

# Prompt the user for the file extension and the target folder
read -p "Enter the file extension (e.g., .txt, .text): " extension
read -p "Enter the name of the target folder (e.g., TEXT): " target_folder

# Check if the target folder exists, if not, create it
if [ ! -d "$target_folder" ]; then
    echo "Target folder does not exist. Creating it now."
    mkdir "$target_folder"
fi

# Loop through all files in the current directory with the given extension
for file in *"$extension"; do
    # Check if the item is a regular file and not a directory
    if [ -f "$file" ]; then
        # Copy the file to the target folder
        cp "$file" "$target_folder/"
        echo "Copied $file to $target_folder/"
    fi
done

echo "File copy operation complete."
