<?php
# inc_dataclean.php - Clean attribute data [include file].
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 27/01/2005
 # Updated: 31/01/2005

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
 
 $sql="select distinct value_string,soundex(value_string) as soundex_string from $attrvaltable where attribute_id=$attrid order by soundex_string, value_string"; #echo "<br>sql=$sql";
 $rs=mysql_query($sql,$conn);
 
 if(mysql_num_rows($rs)==0){
   print "<tr><td colspan=2>No results found!</td></tr>";
 }
 
 $rowaltcolor='#EBEBEB';  # Used to alternate colors between rows
 
 for ($i=0;$i<mysql_num_rows($rs);$i++){
   $row=mysql_fetch_array($rs);
   
   if($lastsoundex_string!=$row['soundex_string']){$rowaltcolor=($rowaltcolor=='#D8D8D8')?'#FFFFFF':'#D8D8D8';}
   
   $name_value=$row['value_string'];
   $curstartswith=strtolower(substr($row['value_string'],0,1));
   if($startswith!=$curstartswith){$name_value="<a name=\"$curstartswith\">$name_value</a>";}
   print "<tr class=\"blk_14px \" bgcolor=\"$rowaltcolor\"><td><input type=\"checkbox\" name=\"value_string[]\" value=\"$row[value_string]\"></td><td>$name_value &nbsp;&nbsp;<a href=\"\" onclick=\"parent.frames['topbar'].document.forms['updatefrm'].replace_value.value='$row[value_string]';return false;\" class=\"blk_11px\">copy</a></td></tr>\n";
   $startswith=strtolower(substr($row['value_string'],0,1));  # Keep track of when start letter changes to generate index
   $lastsoundex_string=$row['soundex_string'];
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

?>