<?php
 # cleandata.php - Clean attribute data.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 27/01/2005
 # Updated: 27/01/2005

# Dont allow directcall. Uses mambo variable
#defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

 // Site configuration
require_once("../common/site@config.php");

// Database support
require_once ("$webroot/common/db@connect.php");


$db=0;$xdb=1; #local debug options


function get_attribute($value){ # Get a list of attributes
 global $conn,$attrtable,$attrtable_fields,$attrvaltable,$attrvaltable_fields;
 global $attroptiontable,$attroptiontable_fields;
 
 $cont='';
 
 $crit="name IN('city','country','race','religion','division','gs_division','village','occupation')";
 $sql="select $attrtable_fields from $attrtable where data_type=1 AND $crit order by name";
 $rs=mysql_query($sql,$conn);
 
 for ($i=0;$i<mysql_num_rows($rs);$i++){
   $row=mysql_fetch_array($rs);
   if($value==$row['id']){
     $cont.="<option value=\"$row[id]\" selected>$row[caption]</option>\n";
   }else{
     $cont.="<option value=\"$row[id]\">$row[caption]</option>\n";
   }
 }
 return $cont; 
}

function list_attr_values($attrid){
 global $conn,$attrtable,$attrtable_fields,$attrvaltable,$attrvaltable_fields;
 global $attroptiontable,$attroptiontable_fields;
 
 $sql="select distinct value_string from $attrvaltable where attribute_id=$attrid order by value_string";
 $rs=mysql_query($sql,$conn);
 
 if(mysql_num_rows($rs)==0){
   print "<tr><td colspan=2>No results found!</td></tr>";
 }
 
 for ($i=0;$i<mysql_num_rows($rs);$i++){
   $row=mysql_fetch_array($rs);
   print "<tr><td><input type=\"checkbox\" name=\"value_string[]\" value=\"$row[value_string]\"></td><td>$row[value_string]</td></tr>\n";
 }
 
}

function update_data($attrid){
 global $conn,$attrtable,$attrtable_fields,$attrvaltable,$attrvaltable_fields;
 global $attroptiontable,$attroptiontable_fields;

 foreach ($_REQUEST['value_string'] as $value_string){
   $sql="update $attrvaltable set value_string='$_REQUEST[replace_value]' where value_string='$value_string' and attribute_id=$attrid"; #print "<br>sql=$sql";
   mysql_query($sql);
 }
 
}

if(count($_REQUEST['value_string'])>0){ # Call update_data if data is passed
 update_data($_REQUEST['attr']);
}

?>
<html>
<head><title>Clean up data</title></head>
<body>
<table border="0">
<form action="<?=$_SERVER[PHP_SELF]?>" method="post">
<tr><td>Please select an attribute to clean data for : </td>
<td>

<select name="attr" onchange="document.forms[0].submit()">
<?=get_attribute($_REQUEST['attr'])?>  
</select>
</td>
</tr>
</form>
</table>

<table>
<form action="<?=$_SERVER[PHP_SELF]?>" method="post">
<tr><td>
<!-- attribute value data -->
<table border=1>

<tr><th>seq #</th><th>Attribute value</th></tr>
<?=list_attr_values($_REQUEST['attr'])?>
</table>

</td>
<td valign="top">
<!-- replace value-->
&nbsp;Replace with : <input type="text" name="replace_value"><br>
<input type="hidden" name="attr" value="<?=$_REQUEST['attr']?>">
<input type="submit" value="Modify">
</td>
</tr>
</form>
</table>
</body>
</html>
