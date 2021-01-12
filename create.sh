#!/bin/bash

if [ $# -lt 1 ]; then
	echo USAGE: $0 programname
	echo -e "\n"
	echo Crates a new directory including all the neccessary mkmake scripts
	echo in order to create a new user mode program called \"programname\".
else
	# Copy the template contents
	rsync -aC template/ $1
	
	# and adjust them
	mv $1/demo.cpp $1/$1.cpp
	echo $1>$1/module.name
	
	# Update all user mode program names
	echo $1>>alluserprogs
fi