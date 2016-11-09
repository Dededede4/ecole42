#!/bin/bash

action=$1
schoolGitUrl=$2
name=$3

thisPath=`pwd`
workPath='/Users/mprevot/dev/ecole42'
backupPath='/Users/mprevot/dev/ecole42.github'

rsync -a --exclude='.git/' "${workPath}/" "${backupPath}/"

if [ $action = "new" ]
then
	cd $workPath
	git clone $schoolGitUrl $name
	
	cd $backupPath
	mkdir $name
else
	command=""

	for i in "$@"; do 
		    i="${i//\\/\\\\}"
		    command="$command \"${i//\"/\\\"}\""
	done

	echo $command
	eval $command

	subPath=${thisPath#$workPath}
	cd "$backupPath$subPath"
	eval $command
fi
