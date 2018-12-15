#!/bin/bash

find ./custom_tests -type f  | while read line ;
do
  nm $line | grep --invert-match "is not an object file" > a
  ./ft_nm $line > b
  DIFF=$(diff a b) 
	if [ "$DIFF" != "" ] 
	then
	    echo "Diff : $line"
	    exit
	 else
	 	echo "OK : $line"
	fi
done
