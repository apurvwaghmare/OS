

# #!/bin/bash
# read -p "Enter the num to check palindrome: " no
# original=$no
# reversed_no=0;
# while [ $no -gt 0 ]; do
# 	digit=$(( $no % 10 ))
# 	reversed_no=$(( $reversed_no * 10 + $digit ))
# 	no=$(( $no / 10))
# done
# echo "$reversed_no:"
# if [ $original -eq $reversed_no ]; then
# 	echo "no is palindrome" 
# else
# 	echo "not palindrome"
# fi









#!/bin/bash
# string="Apurv"
# string1=""
# for (( i=${#string} - 1 ;i >= 0 ; i-- )); do
# 	string1+="${string:i:1}"
# done
# echo "${string1}"

# reverse() {
# 	local input="$1"
# 	local ans=""
# 	for (( i=${#input} - 1 ; i >= 0 ; i-- )); do
# 		ans+="${input:i:1}"
# 	done
# 	echo "$ans"
# }
# original="samarth"
# reversed=$(reverse "$original" )

# echo "reversed : $reversed"











#!/bin/bash
# read -p "Enter the numver for fact: " no
# fact=1
# if [[ $no -eq 0 || $no -eq 1 ]]; then
# 	fact=1
# else
# 	for (( i=1 ; i <= $no ; i++ )); do
# 		fact=$(( $fact * $i ))
# 	done
# fi

# echo " $fact "

# factorial() {
# 	local num=$1;
# 	if [[ $num -lt 1 ]]; then
# 		echo 1
# 	else
# 		local ans=$(factorial $(( num-1 )) )
# 		echo $(( num * ans ))
# 	fi


# }
# result=$(factorial $no)
# echo "$result"










#!/bin/bash
# Celsius_to_fahrenheit() {
#     celsius=$1
#     fahrenheit=$((celsius * 9/5 + 32))
#     echo $fahrenheit
# }

# echo "Enter the Temperature in Celsius: "
# read temp
# result=$(Celsius_to_fahrenheit "$temp")
# echo "Temperature in Fahrenheit: $result"











#!/bin/bash
# Simple exponent program

# Function to calculate exponent
# calculate_exponent() {
#     base=$1
#     exponent=$2
#     result=$((base ** exponent))
#     echo $result
# }

# # Taking input from user
# read -p "Enter the base: " base
# read -p "Enter the exponent: " exponent

# # Calling the function and displaying the result
# result=$(calculate_exponent $base $exponent)
# echo "Result: $result"










#!/bin/bash

# count_digits() {
#     local num=$1
#     local count=0
#     while [ $num -ne 0 ]; do
#         num=$(expr $num / 10)
#         count=$(expr $count + 1)
#     done
#     echo $count
# }

# is_armstrong() {
#     local num=$1
#     local C_digits=$2
#     local temp=$num
#     local sum=0
#     while [ $temp -ne 0 ]; do
#         digit=$(expr $temp % 10)
#         sum=$(expr $sum + $digit \* $digit \* $digit)
#         temp=$(expr $temp / 10)
#     done
#     if [ $num -eq $sum ]; then
#         return 0
#     else
#         return 1
#     fi
# }










# echo "Enter number: "
# read num
# C_digits=$(count_digits $num)
# is_armstrong $num $C_digits
# result=$?

# if [ $result -eq 0 ]; then
#     echo "$num is an Armstrong number"
# else
#     echo "$num is not an Armstrong number"
# fi









#!/bin/bash

# if [ "$#" -ne 1 ]; then
#     echo "Usage: $0 <side_length>"
#     exit 1
# fi
# side_length=$1
# volume=$((side_length * side_length * side_length))
# echo "The volume of the cube with side length $side_length is: $volume"





