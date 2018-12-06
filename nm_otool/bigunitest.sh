#!/bin/bash
while IFS='' read -r line || [[ -n "$line" ]]; do
    #echo "Text read from file: $line"
    nm $line | grep ' C ' &> /dev/null
	if [ $? == 0 ]; then
	   echo "matched : $line"
	fi
done < "$1"