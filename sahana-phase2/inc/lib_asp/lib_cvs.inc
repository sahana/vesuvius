/**
* Description for file
* http://sahana.sourceforge.net
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana ASP
* @subpackage CVS 
* @author     Pradeeper <pradeeper@opensource.lk>
*/
<?php
require_once "config.inc";


function cvs_checkout($release, $working_dir)
{
	echo "getting CVS from the release $release \n";
	$release="-r $release";
	echo "This might take a while......";
	exec("cd $working_dir && cvs -z3 -d:pserver:anonymous@sahana.cvs.sourceforge.net:/cvsroot/sahana co $release -P sahana-phase2 2>&1", $cvsout, $error);
	if ($error==0){
		echo "cvs checkout is successfull.\n";
	} else {
		echo "cvs checkout is failed.";
	}
}// end of cvs_checkout function


function cvs_update($release, $working_dir)
{
	echo "Updating CVS from the release $release \n";
	$release="-r $release";
	exec("cd $working_dir && cvs -z3 -d:pserver:anonymous@sahana.cvs.sourceforge.net:/cvsroot/sahana up $release -dP sahana-phase2", $cvsout, $error);
	if ($error==0){
		echo "cvs update is successfull.\n";
	} else {
		echo "cvs update is failed.";
	}
}// end of cvs_update function


