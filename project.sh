#!/bin/bash

action=$1
schoolGitUrl=$2
name=$3

thisPath=`pwd`
thisDir=${PWD##*/}
workPath='/Users/mprevot/dev/ecole42'
backupPath='/Users/mprevot/dev/ecole42.github'

rsync -a --exclude='.git/' "${workPath}/" "${backupPath}/"

if [ $action = "new" ]
then
	cd $workPath
	git clone $schoolGitUrl $name
	
	cd $backupPath
	mkdir $name
elif [ $action = "pull" ]
then
	git stash --include-untracked

	cd $backupPath
	git fetch
	git pull

	rsync -a --exclude='.git/' "${backupPath}/${thisDir}" "${thisPath}/"
	cd $thisPath
	git add .
	git commit -m 'synchronisation from github'
	git push	

	git stash pop
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
