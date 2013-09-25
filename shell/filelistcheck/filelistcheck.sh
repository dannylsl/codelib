#! /bin/bash
#  a shell script to compare two directories files between $benchmark_dir and $test_dir.
#  The extra file names are listed in file more.log. the missing file names are listed in file less.log
#  the parameter fomat is like:
#    filelistcheck.sh $benchmark_dir $test_dir

function Usage() 
{
	echo "Usage:"	
	echo -e "\t$0 dir1 dir2"
}

#Function isFileExist() check the file exist or not
#Usage: isFileExist filepath
function isFileExist()
{
	filepath=$1
	test -e $filepath && ret="exist"
	test -e $filepath || ret="notexist"
	echo $ret
}

#Function fileType() returns the type of a file [directory of file]
#Usage: fileType filename
function fileType()
{
	file_to_check=$1		
	is_file_exist=$(isFileExist $file_to_check)
	if [ $is_file_exist == "exist"  ]; then
		test -f $file_to_check && ret="file"
		test -d $file_to_check && ret="dir"
	elif [ $is_file_exist == "notexist" ]; then
		ret="notexist"	
	fi
	echo $ret
}

#Function getMore() output more.log
#Usage: getMore dir1 dir2
function getMore()
{
	dir1=$1
	dir2=$2
	for x in $(ls $dir1)	
	do
		filetype=$(fileType $x)
		if [ $filetype == "file" ]; then
			#check if [FILE]$x exist in [DIR]$dir2											
			is_file_x_in_dir2=$(isFileExist "$dir2/$x")
			if [ $is_file_x_in_dir2 == "notexist" ]			
				echo "$dir1/$x">>more.log 	
			fi
		elif [ $filetype == "dir" ]; then
			#check if [DIR]$x exist in [DIR]$dir2	
			is_dir_x_in_dir2=$(isFileExist "$dir2/$x")
			if [ $is_dir_x_in_dir2 == "notexist" ]
				#Traversal [DIR]$x and add all filepath to more.log			
									
			elif [ $is_dir_x_in_dir2 == "exist" ]; then
				#Continue to Traversal [DIR]$x

			fi
		elif [ $filetype == "notexist" ]; then
			#Do nothing
		fi
	done
}

#Syntax check
if [ $# != 2 ]; then
	Usage
	exit
fi

benchmark_dir=$1 
test_dir=$2

#test
fileType $benchmark_dir

#Traversal [DIR]benchmark_dir and compare it with [DIR]test_dir at the same time





