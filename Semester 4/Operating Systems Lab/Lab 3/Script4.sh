#!/bin/bash

# Prompt the user for basic salary and TA (Travel Allowance)
read -p "Enter the Basic Salary: " basics
read -p "Enter the Travel Allowance (TA): " ta

# Calculate 10% of Basics
ten_percent_of_basics=$(echo "$basics * 0.10" | bc)

# Calculate the Gross Salary (GS)
gs=$(echo "$basics + $ta + $ten_percent_of_basics" | bc)

# Display the result
echo "Gross Salary (GS) = Basics + TA + 10% of Basics"
echo "Gross Salary = $gs"
