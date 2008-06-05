#!/bin/bash

#############################
# This script can be used to generate deb package from any sahana branch or release. This will work only in Debian base GNU/Linux systems.
# LICENSE: This source file is subject to LGPL license
# that is available through the world-wide-web at the following URI:
# http://www.gnu.org/copyleft/lesser.html
# @package    Sahana - http://sahana.sourceforge.net
# @author   Ishan Liyanage <ishan@opensource.lk> 
# @copyright  Lanka Software Foundation - http://www.opensource.lk
#
#############################
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
echo "Creating the deb package...."
mv sahana-phase2 sahana
mkdir debian
cd debian
mkdir DEBIAN usr var
cd usr
mkdir share
cd share
cp -r ../../../sahana ./
cd ../../var
mkdir www
cd www
ln -s /usr/share/sahana/www
cd ../../DEBIAN
echo -e "Package: sahana \nVersion: 0.6.2.2-rc1 \nSection: web \nPriority: optional \nArchitecture: all \nDepends: php5 | php5-mysql | mysql-server-5.0 , apache2 | httpd | apache | php5-gd \nMaintainer: Sahana <support@sahana.lk> \nDescription: Sahana is a free and open source Disaster Management System.It mainly facilitates management of Missing people, disaster victims, Managing and administrating various organizations, managing camps and managing requests and assistance in the proper distribution of resources. Visit http://www.sahana.lk/"> control

cd ../..
dpkg-deb --build debian
echo "Please enter the release name"
read rel
mv debian.deb `echo $rel`.deb
echo "Successfully Created deb package.."
rm -r debian sahana
