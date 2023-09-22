#!/usr/bin/bash

# The only command line argument is a file name
file_name=$1
passed=true
# Iterate over each line of the input file
while IFS= read -r line; do
    # Here's where you can use regex capture groups to extract the info from each line
    # You'll need to capture two pieces of data: the field name and the value of the field.
    # Put your regex with capture groups to the right of the =~ operator
    #echo "$line"
    if [[ "$line" =~ [[:space:]]+(.*):[[:space:]]+(.*) ]]; then
        # Recall how to access text from regex capture groups
        # See slide 15 from the lecture
        field="${BASH_REMATCH[1]}"
        value="${BASH_REMATCH[2]}"
        #echo "$field"
    else
        # If nothing could be extraced, then skip the line
        continue
    fi

    case $field in
        # You can follow this pattern for all other fields
        first_name | last_name)
            pattern='[[:alpha:]]'
            ;;
        phone_number)
            pattern='^([0-9]{3})-([0-9]{3})-([0-9]{4})$'
            ;;
        email) # Case where the field name is literally the string "email"
            # Same regex for email that we used in lecture
            pattern='^[[:alnum:]_#-]+@[[:alnum:]-]+\.[[:alnum:]]{2,4}$'
            ;;
        street_number)
            pattern='^([0-9]{1,5})$'
            ;;
        street_name | city)
            pattern='^[A-Za-z\s]'
            ;;
        apartment_number)
            pattern='^([0-9]{1,4})$|.*'
            ;;
        state)
            pattern='^[A-Z]{2}$'
            ;;
        zip)
            pattern='^[0-9]{5}'
            ;;
        card_number)
            pattern='^([0-9]{4})-([0-9]{4})-([0-9]{4})-([0-9]{4})$'
            ;;
        expiration_month)
            pattern='0[1-9]|1[0-2]'
            ;;
        expiration_year)
            pattern='^20[2][1-9]$'
            ;;
        ccv)
            pattern='[0-9]{3}'
            ;;
        *) # Case where there the field name didn't match anything
            continue
            ;;
    esac


    if ! [[ $value =~ $pattern ]]; then
        # We need to print out a message if the field isn't valid
        echo "field $field with value $value is not valid"
        passed=false
    fi
        
done < "$file_name"

# We need to print something if all fields were valid
# Remember, booleans are useful for this assignment
if [[ $passed = true ]]; then
    echo "purchase is valid"
    exit 0
fi
