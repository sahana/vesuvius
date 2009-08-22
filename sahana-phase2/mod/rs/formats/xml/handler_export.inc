<?php
global $global;

//featch data
$global['db']->SetFetchMode(ADODB_FETCH_NUM);
$rs = $global['db']->Execute($_SESSION['export_sql']);//check weather the sql is empty
if (!$rs){
    add_error($global['db']->ErrorMsg());
    return;
}
else{
        header("Expires: 0");
        header("Content-type: text/xml");
        header("Content-Disposition: attachment; filename=sahana_".date('Y-m-d').".xml");
        header("Cache-Control: no-cache, must-revalidate");

echo "<?xml version=\"1.0\"?>\n";

    $ECC=$rs->FieldCount();//handel 0 count
    $ERC=$rs->RecordCount();//handel 0 count

    if(isset($_SESSION['export_title']))
        $ERC=$ERC+1;
echo "<table>\n";
        $fc=$rs->FieldCount();
        for($x=0;$x<$fc;$x++)
        $fields[$x]=$rs->FetchField($x)->name;
        foreach($rs as $row){
            echo "\t\t<record>\n";
            foreach($fields as $k=>$field){
                $row[$k]=(isset($row[$k]))?$row[$k]:'null';
                echo "\t\t\t<".$field."><![CDATA[".$row[$k]."]]></".$field.">\n";
            }
            echo "\t\t</record>\n";
        }
?>
  </table>
<?php
}
