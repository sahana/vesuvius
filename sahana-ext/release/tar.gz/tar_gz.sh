#!/bin/bash
dep_dpkg=`dpkg -l | grep "dpkg-dev"`;
dep_rpm=`dpkg -l | grep "rpm"`;
if [ "$dep_dpkg" == "" ]; then
sudo apt-get install dpkg-dev
elif [ "$dep_rpm" == "" ]; then
sudo apt-get install rpm	
fi

directory=`pwd`
echo "Please, Enter the sourceforge sahana user name"
read user
echo "Please Enter the branch name"
read rel
cvs -z3 -d:ext:`echo $user`@sahana.cvs.sourceforge.net:/cvsroot/sahana export -r `echo $rel`  sahana-phase2

echo "downloaded sahana....."
mv sahana-phase2 sahana
echo "Please enter the release name"
read rel
echo "Creating tar.gz package..."
tar -czf `echo $rel`.tar.gz sahana
echo "Successfully Created tar.gz package...."
rm -r sahana
