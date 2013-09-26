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

#Function add_all_filepath() add all filepath in a folder to log file
#Usage: add_all_filepath folder more.log [base_dir_for_change]
function add_all_filepath()
{
	dir=$1
	log=$2
	basedir=$3
	echo "[START] add_all_filepath $dir $log" 
	echo "$dir">>$log
	for x in $(ls $dir)	
	do 
		filetype=$(fileType "$dir/$x")
		echo "[file] $dir/$x is a $filetype"
		if [ $filetype == "file" ]; then
			echo "$dir/$x">>$log
		elif [ $filetype == "dir" ]; then
			#THERE IS A SHELL-SCRIPT BUG BELOW, AFTER Traversal,
			#The dir value changed to a value equals to dir value in the Traversal
			echo "$dir/$x/">>$log
			#echo "[BEFORE CALL] $dir"
			cur_dir=$dir
			add_all_filepath "$dir/$x" $log 
			#echo "[AFTER CALL] $dir"
			dir=$cur_dir
			#echo "[AFTER CALL] $dir"
		fi
	done
	echo "[DONE] add_all_filepath $dir $log "
}


#Function compare() output log file
#Usage: compare dir1 dir2 more.log
#		compare dir2 dir1 less.log
function compare()
{
	dir1=$1
	dir2=$2
	log=$3
	echo "compare $dir1 $dir2 $log"
	for x in $(ls $dir1)	
	do
		filetype=$(fileType "$dir1/$x")
		if [ $filetype == "file" ]; then
			#check if [FILE]$x exist in [DIR]$dir2											
			is_file_x_in_dir2=$(isFileExist "$dir2/$x")
			if [ $is_file_x_in_dir2 == "notexist" ]; then			
				echo "$dir1/$x">>$log 	
			fi
		elif [ $filetype == "dir" ]; then
			#check if [DIR]$x exist in [DIR]$dir2	
			is_dir_x_in_dir2=$(isFileExist "$dir2/$x")
			if [ $is_dir_x_in_dir2 == "notexist" ]; then
				#Traversal [DIR]$x and add all filepath to log file		
				echo "[DIR]$x notexist in [DIR]$dir2"
				add_all_filepath $dir1/$x $log 
			elif [ $is_dir_x_in_dir2 == "exist" ]; then
				#THE SAME BUG FOUNDED IN FUNCTION add_all_filepath
				#echo "[BEFORE RECURSION]$dir1  $dir2"
				cur_dir1=$dir1
				cur_dir2=$dir2
				compare "$dir1/$x" "$dir2/$x" $log				
				dir1=$cur_dir1
				dir2=$cur_dir2
				#echo "[AFTER RECURSION]$dir1  $dir2"
				
			fi
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

#fileType $benchmark_dir
#add_all_filepath $benchmark_dir "more2.log"
rm more.log less.log
compare $benchmark_dir $test_dir more.log
compare $test_dir $benchmark_dir less.log
echo "########## more.log ###########"
cat more.log
echo "########## less.log ###########"
cat less.log
