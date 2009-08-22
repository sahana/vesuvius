<?php

/*
This script converts template files in the VM to .inc files containing PHP,
which xgettext can parse. Can be run from the command line or browser.

Default paths are set assuming this script resides in [sahana]/vm/tools/.

Antonio Alcorn 5/23/2008
*/

// Path to the VM folder
$vm_dir = "..";

// Path to write .inc files; must exist and requires write permission
$output_dir = "$vm_dir/tpl2inc";

global $tpls;
$tpls = array();

function walk($dir) {
	global $tpls;
	if($dh = opendir($dir)) {
		while(($file = readdir($dh)) !== false) {
			if($file{0} != '.') {
				if(is_file("$dir/$file"))
					$tpls[] = "$dir/$file";
				if(is_dir("$dir/$file"))
					walk("$dir/$file");
			}
		}
	}
}

walk("$vm_dir/templates");

require_once("$vm_dir/whiz/Whiz.php");
$w = new Whiz("$vm_dir/templates/");

foreach($tpls as $t) {
	$w->tpl2php($t, $output_dir);
	echo "Generated $t<br />\n";
}

