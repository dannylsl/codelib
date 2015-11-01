#!/bin/bash
#Author: danny lee
#Email: dannylsl@hotmail.com
# determine whether a file or path exist or not
#

function Usage()
{	
	echo "Usage: $0 [-fp] [fileName or pathName]"
	echo "Example: $0 -f main.c"
	echo "Example: $0 -p /etc/vim/"
	exit 1
}

function isPathExist()
{
	if [ ! -d "$1" ]; then
		echo "path $1 not exist" 
	else
		echo "path $1 exist"
	fi
	exit 0
}
  
function isFileExist()
{
	if [ ! -f "$1" ]; then
		echo "file $1 not exist" 
	else
		echo "file $1 exist"
	fi
	exit 0
}
  

if [ $# != 2 ]; then
	Usage
fi

if [ "$1" == "-f" ]; then
	fopname=$2 
	isFileExist $fopname
elif [ "$1" == "-p" ]; then
	fopname=$2
	isPathExist $fopname
else
	echo "Parameter error"
	exit 1
fi


