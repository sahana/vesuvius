<?php
/**
* Regular expressions used by the Whiz template engine
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Antonio Alcorn
* @author       Giovanni Capalbo
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
* @package      sahana
* @subpackage   vm
* @tutorial
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

$find = array(
	"/_\(\s*\"([^\(\)]+)\"\s*\|\s*([^\(\)]+)\s*\)/",	// text with format string
	"/{\s*\\$(\w+)\.(\w+)\s*}/",				// array dot syntax
	"/{\s*\\$(\w+)\.(\w+)\.(\w+)\s*}/",		// array dot syntax (2-level)
	"/{\s*\\$(\w+)\.\\$(\w+)\s*}/",			// array dot syntax w/vars
	"/{\s*\\$(\w+)\.\\$(\w+)\.\\$(\w+)\s*}/",	// array dot syntax (2-level, w/vars)
	"/{\s*\\$(\w+)\s*}/",						// variables
	"/{\s*if\s+(.*)\s*}/",						// if
	"/{\s*else\s*}/",							// else
	"/{\s*else\s+if\s+(.*)\s*}/",				// else if
	"/{\s*\/if\s*}/",							// end if
	"/{\s*while\s+(.*)\s*}/","/{\s*\/while\s*}/",	// while
	"/{foreach\s+(.*)}/","/{\s*\/foreach\s*}/",	// foreach
	"/{php}/","/{\/php}/",					// php tags
	"/{\*.*\*}/",							// comments
	"/_\(\"\s*([^\(\)]+)\s*\"\)/"			// localizable text
);

$replace = array(
	"<?php printf(\"$1\", $2); ?>",
	"<?php echo(\$$1['$2']); ?>",
	"<?php echo(\$$1['$2']['$3']); ?>",
	"<?php echo(\$$1[\$$2]); ?>",
	"<?php echo(\$$1[\$$2][\$$3]); ?>",
	"<?php echo(\$$1); ?>",
	"<?php if($1) { ?>",
	"<?php } else { ?>",
	"<?php } else if($1) { ?>",
	"<?php } ?>",
	"<?php while($1) { ?>","<?php } ?>",
	"<?php foreach(\$1) { ?>","<?php } ?>",
	"<?php "," ?>",
	"",
	"<?php echo _(\"$1\"); ?>"
	
);

$empty_blocks = "/\?\>\s+\<\?php/";

