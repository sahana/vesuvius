<?php
 # dataclean_top.php - Clean attribute data.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 27/01/2005
 # Updated: 31/01/2005

# Dont allow directcall. Uses mambo variable
#defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

 // Site configuration
require_once("../common/site@config.php");

// Database support
require_once ("$webroot/common/db@connect.php");

require_once ("inc_dataclean.php");

$db=0;$xdb=1; #local debug options


?>
<html>
<head><title>Clean up data</title>
<link rel="stylesheet" href="main.css" type="text/css">
</head>
<body>
<table border="0" class="tableASH1_padding">
<form action="dataclean.php" method="post" target="datarea" name="updatefrm">
<tr><td>Please select an attribute to clean data for : </td>
<td>

<select name="attr" onchange="document.forms[0].submit()">
<option value="">Select one</option>
<?=get_attribute($_REQUEST['attr'])?>  
</select>
</td>
<td>&nbsp;</td>
<td><!-- replace value-->
&nbsp;Replace with : <input type="text" name="replace_value">
</td>
<td>&nbsp;<input type="submit" value="Modify" onClick="parent.frames['datarea'].document.forms['updatefrm'].replace_value.value=document.forms[0].replace_value.value;parent.frames['datarea'].document.forms['updatefrm'].submit();return false;"></td>
</tr>
<tr class="tableASH2_padding blk_12px">
<td colspan="5"><a href="dataclean.php#a" target="datarea">A</a> | <a href="dataclean.php#b" target="datarea">B</a> | <a href="dataclean.php#c" target="datarea">C</a> | <a href="dataclean.php#d" target="datarea">D</a> | <a href="dataclean.php#e" target="datarea">E</a> | <a href="dataclean.php#f" target="datarea">F</a> | <a href="dataclean.php#g" target="datarea">G</a> | <a href="dataclean.php#h" target="datarea">H</a> | <a href="dataclean.php#i" target="datarea">I</a> | <a href="dataclean.php#j" target="datarea">J</a> | <a href="dataclean.php#k" target="datarea">K</a> | <a href="dataclean.php#l" target="datarea">L</a> | <a href="dataclean.php#m" target="datarea">M</a> | <a href="dataclean.php#n" target="datarea">N</a> | <a href="dataclean.php#o" target="datarea">O</a> | <a href="dataclean.php#p" target="datarea">P</a> | <a href="dataclean.php#q" target="datarea">Q</a> | <a href="dataclean.php#r" target="datarea">R</a> | <a href="dataclean.php#s" target="datarea">S</a> | <a href="dataclean.php#t" target="datarea">T</a> | <a href="dataclean.php#u" target="datarea">U</a> | <a href="dataclean.php#w" target="datarea">W</a> | <a href="dataclean.php#x" target="datarea">X,Y,Z</a></td>
</tr>
</form>
</table>
</body>
</html>
