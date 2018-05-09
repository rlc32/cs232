#!/bin/bash
LANG=C

removespaces() {
    echo "$1" | sed -e "s/ //g"
}

set -e #will exit on command failure.

inputfile="$@"
verbose=0

#checking for at least one command line argument
if [ $# == 0 ];then
	echo "no command line arguments. now exiting"
	exit
fi

#If stattement source code adapted from here http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-6.html
if [ "$1" == "-v" ];then
	verbose=1
	shift
fi
if [ "$1" == "--verbose" ];then
	verbose=1
	shift
fi
inputfile="$@"
#makes sure that if only verbose flag is given that it will exit because no file argument was given.
if [ $# == 0 ];then
	echo "No file argument provided. now exiting"
	exit
fi

#unzipping zipped file
if [ $verbose == 1 ];then
	echo "Creating the folder to unzip into"
	echo "Unzipping the original zip file"
fi
parent="${inputfile%.*}" #getting filename without type extension
mkdir "$parent" #making that file
unzip -qq "${inputfile%.*}" -d "$parent" #unziping the file into parent

#renaming directory
if [ $verbose == 1 ];then
	echo "Renaming the parent directory to not have spaces in the name"
fi
nospaces=$(removespaces "$parent") #removing spaces from parent name. storing in var nospaces
mv "$parent" $nospaces #rename parent directory to no spaces. 

#moving all students submissions into one folder perperson and renaming their name no spaces
parent=$nospaces
OIFS=$IFS
IFS='_'

if [ $verbose == 1 ];then
	echo "Moving all student submissions into one directory"
	echo "Renaming student directorys to not have spaces or numbers in directory names"
fi
cd $parent
for d in *;do
	studentdir=$(removespaces $d)
	mkdir -p $studentdir
	mv "$d"/* $studentdir
	rmdir "$d"
done
#remove spaces in individual filenames
if [ $verbose == 1 ];then
	echo "Removing spaces in individual file names inside of student directorys"
fi
for d in *;do
	cd $d
	for file in *;do
		nospaces=$(removespaces "$file")
		mv "$file" $nospaces
	done
	cd ..
done



