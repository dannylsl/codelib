#!/bin/bash

path=$1
echo $#
if [ $# == 0 ]; then
	cmd='ls'
elif [ $# == 1 ];then
	cmd="ls ${path}"
	echo $cmd
fi

for x in `$cmd`
do
	echo "filename = $x"
	awk '/render_FPS=.*/{print}' $path'/'$x
done




