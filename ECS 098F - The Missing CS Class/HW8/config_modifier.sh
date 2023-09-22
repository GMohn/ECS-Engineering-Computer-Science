#!/usr/bin/bash

taget_dir=$1
mode=$2
shift 2
sed_command=""
appendMode() {
    # Appends a new field to a given section with a field name and value
    # 
    # Args
    # $1: Section name
    # $2: New field name
    # $3: New field value
    sed_command="/^\[$1\]/a\\$2\ = $3"
    #echo "app mode"
}

deleteMode() {
    # Removes a field from the config file
    #
    # Args
    # $1: field_name
    sed_command="/$1/d"
    #echo "del mode"
}

subMode() {
    # Replaces the value of a particular field with a new one
    #
    # Args
    # $1: field name
    # $2: new_value
    sed_command="/$1 =/ s/= .*/= $2/"
    #echo "sub mode"
}

case $mode in
    '-a')
        appendMode "$@"
        ;;
    '-d')
        deleteMode "$@"
        ;;
    '-s')
        subMode "$@"
        ;;
    *)
        echo 'Unrecongized flag for first argument'
        exit 2
        ;;
esac

# What command can we use to recursively find all files with an ini extenstion?
#echo "finding"
echo "$sed_command"
find "$taget_dir" -name "*.ini" -exec sed -i -e "$sed_command" {} +

# Furthermore, how can we make that command call sed for each file it finds?
