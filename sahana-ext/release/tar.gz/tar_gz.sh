#!/bin/bash

#############################
# This script can be used to generate tar.gz package from any sahana branch or release. This will work only in Debian base GNU/Linux systems.
# LICENSE: This source file is subject to LGPL license
# that is available through the world-wide-web at the following URI:
# http://www.gnu.org/copyleft/lesser.html
# @package    Sahana - http://sahana.sourceforge.net
# @author   Ishan Liyanage <ishan@opensource.lk> 
# @copyright  Lanka Software Foundation - http://www.opensource.lk
#
#############################


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
