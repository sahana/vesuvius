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
	"/{ *\\$(\w+)\.(\w+) *}/",				// array dot syntax
	"/{ *\\$(\w+)\.(\w+)\.(\w+) *}/",		// array dot syntax (2-level)
	"/{ *\\$(\w+)\.\\$(\w+) *}/",			// array dot syntax w/vars
	"/{ *\\$(\w+)\.\\$(\w+)\.\\$(\w+) *}/",	// array dot syntax (2-level, w/vars)
	"/{ *\\$(\w+) *}/",						// variables
	"/{ *if +(.*) *}/",						// if
	"/{ *else *}/",							// else
	"/{ *else +if +(.*) *}/",				// else if
	"/{ *\/if *}/",							// end if
	"/{ *while +(.*) *}/","/{\/while}/",	// while
	"/{foreach +(.*)}/","/{\/foreach}/",	// foreach
	"/{php}/","/{\/php}/",					// php tags
	"/{\*.*\*}/"							// comments
);

$replace = array(
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
	""
);

$empty_blocks = "/\?\>\s+\<\?php/";

?>