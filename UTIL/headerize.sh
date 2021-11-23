#!/bin/bash
#update header information about files and license
#at the beginning of every source file (.cpp,.h,.R)

#usage:
#./headerize.sh component sourceFolder language
#('language' argument is either R or C)

component=$1
sourceFolder=$2
language=$3
temp=/tmp/mixmodFile
boundaryDelimiter="****************************************************************************************"
middleDelimiter="========================================================================================"

if [ "$language" = "C" ]; then
	files=`find $sourceFolder -regex '.*\.h' && find $sourceFolder -regex '.*\.cpp'`
	commentMark='//'
elif [ "$language" = "R" ]; then
	files=`find $sourceFolder -regex '.*\.R'`
	commentMark='#'
fi

for file in $files; do

	#find size of current header (if any)
	lCount=0
	cmCount=0
	while read -r line
	do
		if [ "$line" = "$commentMark$boundaryDelimiter" ]; then
			cmCount=$(($cmCount+1))
		fi
		lCount=$(($lCount+1))
		if [ "$cmCount" -eq 2 ]; then
			break
		fi
	done < $file
	
	if [ "$cmCount" -lt 2 ]; then
		#no header
		lCount=0
	fi

	printf "%s$boundaryDelimiter\n" "$commentMark" > $temp
	
	#informations  
	printf "%s\tfile      : %s / %s\n" "$commentMark" "$component" "$file" >> $temp
	printf "%s\tcopyright : (C) MIXMOD Team - 2001-%i\n" "$commentMark" `date '+%Y'` >> $temp
	printf "%s\temail     : contact@mixmod.org\n" "$commentMark" >> $temp
	
	printf "%s$middleDelimiter\n" "$commentMark" >> $temp
	
	#license
	printf "%s\tThis file is part of MIXMOD (see <http://www.mixmod.org>)\n" "$commentMark" >> $temp
	printf "%s\n" "$commentMark" >> $temp
	printf "%s\tMIXMOD is free software: you can redistribute it and/or modify it under the terms of\n" "$commentMark" >> $temp
	printf "%s\tthe GNU General Public License as published by the Free Software Foundation,\n" "$commentMark" >> $temp
	printf "%s\teither version 3 of the License, or (at your option) any later version.\n" "$commentMark" >> $temp
	printf "%s\n" "$commentMark" >> $temp
	printf "%s\tMIXMOD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;\n" "$commentMark" >> $temp
	printf "%s\twithout even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n" "$commentMark" >> $temp
	printf "%s\tSee the GNU General Public License for more details.\n" "$commentMark" >> $temp
	printf "%s\n" "$commentMark" >> $temp
	printf "%s\tYou should have received a copy of the GNU General Public License along with MIXMOD.\n" "$commentMark" >> $temp
	printf "%s\tIf not, see <http://www.gnu.org/licenses/>.\n" "$commentMark" >> $temp
	
	printf "%s$boundaryDelimiter\n" "$commentMark" >> $temp

	#if lCount==0, add a blank line after header
	if [ $lCount -eq 0 ]; then
		printf "\n" >> $temp
	fi

	#cut first lCount lines (size of old header)
	tail -n +$(($lCount+1)) $file >> $temp

	#now overwrite current file
	mv $temp $file

done
