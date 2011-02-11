#!/bin/bash
curdir=$(pwd)
echo "This program will remove all trailing ?> at the end of the files in directory '$curdir'."
echo ""
echo "Press y to continue or n to terminate"
read -p "Proceed ? [y/n] " ans
echo ""
if [ $ans == 'y' ];then
	lst=$(find . -type f)
	for f in $lst; do
		has_tag=$(tail -n1 $f | grep \?\>)
		if [ ! -z "$has_tag"  ];then
			sed -i '$s/\?>//' $f | tail -n5
			echo "====================="
		fi
	done
	echo "Complete !"
else
	echo "Aborted !"
fi
