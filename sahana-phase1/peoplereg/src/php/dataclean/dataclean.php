<?php
 # dataclean.php - Clean attribute data.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 27/01/2005
 # Updated: 01/02/2005

# Dont allow directcall. Uses mambo variable
#defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

 // Site configuration
require_once("../common/site@config.php");

// Database support
require_once ("$webroot/common/db@connect.php");

require_once ("inc_dataclean.php");

$db=0;$xdb=1; #local debug options


if(count($_REQUEST['value_string'])>0){ # Call update_data if data is passed
 update_data($_REQUEST['attr']);
}

?>
<html>
<head><title>Clean up data</title>
<link rel="stylesheet" href="main.css" type="text/css">
</head>
<body>

<?php if($_REQUEST['attr']): ?>
<table border=0 width="100%">
<form action="<?=$_SERVER[PHP_SELF]?>" name="updatefrm" method="post">
<tr><td>
<!-- attribute value data -->
<table border=0 class="bordertext" width="50%">

<tr><th></th><th>Attribute values</th></tr>
<?=list_attr_values($_REQUEST['attr'])?>
</table>

</td>

</tr>
<!-- replace value-->
<input type="hidden" name="replace_value"><br>
<input type="hidden" name="attr" value="<?=$_REQUEST['attr']?>">
</form>
</table>
<?php else:?>
<table border="0" width="450" height="100" class="bordertext" align="center"><tr><td>&nbsp;</td><td>Please select an attribute from the above drop down to get a complete listing. </td><td>&nbsp;</td></tr></table> 
<?php endif?>

</body>
</html>
