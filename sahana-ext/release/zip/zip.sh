#!/bin/bash

#############################
# This script can be used to generate zip package from any sahana branch or release. This will work only in Debian base GNU/Linux systems.
# LICENSE: This source file is subject to LGPL license
# that is available through the world-wide-web at the following URI:
# http://www.gnu.org/copyleft/lesser.html
# @package    Sahana - http://sahana.sourceforge.net
# @author   Ishan Liyanage <ishan@opensource.lk> 
# @copyright  Lanka Software Foundation - http://www.opensource.lk
#
#############################
zip=`dpkg -l | grep "zip"`;

if [ "$zip" == "" ]; then
sudo apt-get install zip

fi

directory=`pwd`
echo "Please, Enter the sourceforge sahana user name"
read user
echo "Please Enter the branch name"
read rel
cvs -z3 -d:ext:`echo $user`@sahana.cvs.sourceforge.net:/cvsroot/sahana export -r `echo $rel`  sahana-phase2

echo "downloaded sahana....."
echo "Creating the zip package...."
mv sahana-phase2 sahana
zip -r `echo $rel`.zip sahana
rm -r sahana
echo "Created zip package successfully"
