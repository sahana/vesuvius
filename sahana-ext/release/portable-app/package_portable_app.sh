#!/bin/bash

# Sahana front controller, through which all actions are dispatched
#
# PHP version 4 and 5
#
# LICENSE: This source file is subject to LGPL license
# that is available through the world-wide-web at the following URI:
# http://www.gnu.org/copyleft/lesser.html
#
# @package    Sahana - http://sahana.sourceforge.net
# @author     http://www.linux.lk/~chamindra
# @copyright  Lanka Software Foundation - http://www.opensource.lk

echo "Please, Enter the sourceforge sahana user name"
read user
echo "Please Enter the branch name"
read rel
echo "Downloaded Sahana Source....."
cvs -z3 -d:ext:`echo $user`@sahana.cvs.sourceforge.net:/cvsroot/sahana export -r `echo $rel`  sahana-phase2

echo "Creating the portable package...."
mkdir portable-package

echo "Copying skeleton...."
cp -r portable-skel/* portable-package/

echo "Injecting Sahana into Portable...."
mv sahana-phase2 portable-package/PortableApps/SahanaPortable/udrive/www

echo "Zipping Portable App...."
cd portable-package
zip -r ../portable.zip *
cd .. 

echo "Please enter the release name"
read rel

mv portable.zip `echo $rel`-portable-app.zip
echo "Cleaning up...."
rm -rf portable-package

echo "Successfully Created Portable package.."
