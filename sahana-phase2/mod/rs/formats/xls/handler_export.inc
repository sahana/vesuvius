<?php
global $global;

//featch data
$global['db']->SetFetchMode(ADODB_FETCH_NUM);
$recordSet = $global['db']->Execute($_SESSION['export_sql']);//check weather the sql is empty
if (!$recordSet){
    add_error($global['db']->ErrorMsg());
    return;
}
else{

header("Content-type: application/x-msdownload");
header("Content-Disposition: attachment; filename=sahana_".date('Y-m-d').".xls");
header("Pragma: no-cache");
header("Expires: 0");


echo "<?xml version=\"1.0\"?>\n";
echo "<?mso-application progid=\"Excel.Sheet\"?>\n";
?>
<Workbook xmlns="urn:schemas-microsoft-com:office:spreadsheet"
 xmlns:o="urn:schemas-microsoft-com:office:office"
 xmlns:x="urn:schemas-microsoft-com:office:excel"
 xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"
 xmlns:html="http://www.w3.org/TR/REC-html40">
 <DocumentProperties xmlns="urn:schemas-microsoft-com:office:office">
  <Author> Sahana</Author>
  <LastAuthor>Sahana</LastAuthor>
  <Created><?php echo date('Y-m-d');?>T<?php echo date('H:i:s');?>Z</Created>
  <Version>11.5606</Version>
 </DocumentProperties>
 <ExcelWorkbook xmlns="urn:schemas-microsoft-com:office:excel">
  <WindowHeight>8700</WindowHeight>
  <WindowWidth>11355</WindowWidth>
  <WindowTopX>240</WindowTopX>
  <WindowTopY>30</WindowTopY>
  <ProtectStructure>False</ProtectStructure>
  <ProtectWindows>False</ProtectWindows>
 </ExcelWorkbook>

<Styles>
  <Style ss:ID="Default" ss:Name="Normal">
   <Alignment ss:Vertical="Bottom"/>
   <Borders/>
   <Font/>
   <Interior/>
   <NumberFormat/>
   <Protection/>
  </Style>
  <Style ss:ID="s21">
   <NumberFormat ss:Format="&quot;$&quot;#,##0;[Red]\-&quot;$&quot;#,##0"/>
  </Style>
  <Style ss:ID="s22">
   <Interior ss:Color="#CC99FF" ss:Pattern="Solid"/>
  </Style>
 </Styles>
<Worksheet ss:Name="Sheet1">
<?php
    $ECC=$recordSet->FieldCount();//handel 0 count
    $ERC=$recordSet->RecordCount();//handel 0 count

    if(isset($_SESSION['export_title']))
        $ERC=$ERC+1;
echo "<Table ss:ExpandedColumnCount=\"$ECC\" ss:ExpandedRowCount=\"$ERC\" 
        x:FullColumns=\"1\"  x:FullRows=\"1\">\n";

    if(isset($_SESSION['export_title'])){
        echo "<Row>\n";
        foreach($_SESSION['export_title'] as $value) {
            echo "<Cell ss:StyleID=\"s22\"><Data ss:Type=\"String\"><![CDATA[";
            echo $value;
            echo  "]]></Data></Cell>\n";
        }
        echo "</Row>\n";
    }

    foreach($recordSet as $row){
        $line = '';
        $data = '';
        echo "<Row>\n";
        foreach($row as $value) {
            echo "<Cell><Data ss:Type=\"String\"><![CDATA[";
            echo $value;
            echo  "]]></Data></Cell>\n";
        }
        echo "</Row>\n";
    }
?>
  </Table>
  <WorksheetOptions xmlns="urn:schemas-microsoft-com:office:excel">
   <Print>
    <ValidPrinterInfo/>
    <VerticalResolution>0</VerticalResolution>
   </Print>
   <Selected/>
   <Panes>
    <Pane>
     <Number>3</Number>
     <ActiveRow><?php echo $ERC; ?></ActiveRow>
    </Pane>
   </Panes>
   <ProtectObjects>False</ProtectObjects>
   <ProtectScenarios>False</ProtectScenarios>
  </WorksheetOptions>
 </Worksheet>
</Workbook>
<?php
}
