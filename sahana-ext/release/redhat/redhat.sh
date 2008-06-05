#!/bin/bash

#############################
# This script can be used to generate rpm package from any sahana branch or release. This will work only in Debian base GNU/Linux systems.
# LICENSE: This source file is subject to LGPL license
# that is available through the world-wide-web at the following URI:
# http://www.gnu.org/copyleft/lesser.html
# @package    Sahana - http://sahana.sourceforge.net
# @author   Ishan Liyanage <ishan@opensource.lk> 
# @copyright  Lanka Software Foundation - http://www.opensource.lk
#
#############################


dep_rpm=`dpkg -l | grep "rpm"`;
if [ "$dep_rpm" == "" ]; then
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
echo "Creating the rpm package...."

mkdir tmp
cd tmp
mkdir sahana-rpm
cd sahana-rpm
mkdir usr var
cd usr
mkdir share
cd ../var
mkdir www
cd www
mkdir html
cd ../../..
echo -e "%define name sahana \n%define version 6.2.2 \n%define release RC1 \nSummary: Sahana - an opensource disaster management system. \nName: %{name} \nVersion: %{version} \nRelease: %{release} \nVendor: Lanka Software Foundation \nURL: http://www.sahana.lk \nLicense: LGPL \nGroup: Software/Disaster Management \nPrefix: %{_prefix}
BuildRoot: `pwd`/sahana-rpm \nrequires: httpd >= 2.0, mysql-server >= 5.0, mysql >= 5.0, php-mysql >= 5.0, php >= 5.0, php-gd >= 5.0, php5-common >= 5.0 \n%description\nSahana is an opensource software for management of disasters. \n%prep \n%build \n%install \n%files \n/usr/share/sahana \n/var/www/html/sahana \n%clean \n%post" > sahana.spec
cd sahana-rpm
mkdir BUILD RPMS SRPMS SOURCES SPECS
cp -r ../../sahana usr/share
chmod a+w usr/share/sahana/conf usr/share/sahana/www/tmp
cd var/www/html
ln -s ../../../usr/share/sahana/www sahana

cd ../../../
echo -e "%packager      Sahana <support@sahana.lk> \n%vendor     Sahana \n%_topdir       `pwd`" > ~/.rpmmacros
rpmbuild -bb ../sahana.spec
cd RPMS
cp `ls`/* ../../../
cd ../../../
rm -r sahana tmp
