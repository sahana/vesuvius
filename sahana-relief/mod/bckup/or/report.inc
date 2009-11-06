<?php
/**Reports of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_paging.inc";
include_once("lib_or.inc");


function shn_or_rpt_default()
{
	shn_or_service_coverage_chart();
	shn_or_service_coverage_pdf();
	shn_or_all_orgs_pdf();
}

function shn_or_service_coverage_chart()
{	
	global $global;
    $db=$global['db'];
	$q = "SELECT option_code,option_description FROM field_options WHERE field_name='opt_sector_type' ORDER BY option_description";
    $res_sector=$db->Execute($q);
    
    while(!$res_sector==NULL && !$res_sector->EOF){
    		$option_code=$res_sector->fields["option_code"];
    		$option_desc=$res_sector->fields["option_description"];
		$q = "SELECT DISTINCT COUNT(o_uuid) as count FROM org_main,sector WHERE sector.opt_sector='{$option_code}' AND sector.pgoc_uuid=org_main.o_uuid";
    		$res_org=$db->Execute($q);
	    if((!$res_org->EOF) && ($res_org->fields["count"]!=0)){
	    		add_data($option_desc,$res_org->fields["count"]);
	    }else{
	    		add_data($option_desc,0);
	    }
	    $res_sector->MoveNext();
    }

	$keyword_arr = array('chart'=>'pie chart','mod'=>'or');
	generate_piechart("Piechart","","","",$keyword_arr);

}

function shn_or_service_coverage_pdf()
{
    global $global;
    include_once("view_org.inc");
    $db=$global["db"];
 //   $table_header=array('Service' =>'Service', 'name' => 'Organization Name','Service' =>'Service',
   // 'Incidents' =>'Incidents','Services_Offered' =>'Services Offered','Organization_Type' =>'Organization Type','Location' =>'Location', 'Address' =>'Address', 'Contact_Number' =>'Contact Number');
    $table_header=array('Service' =>'Service', 'name' => 'Organization Name','Organization_Type' =>'Organization Type','Location' =>'Location', 'Address' =>'Address', 'Contact_Number' =>'Contact Number');
    $table_data = array();
    $row_count = 0;
    
    $q = "SELECT option_code,option_description FROM field_options WHERE field_name='opt_sector_type' order by option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
        $option_code=$res_sector->fields[0];
        $q = "SELECT o_uuid,parent_id,name,man_power,equipment,resources FROM org_main,sector WHERE sector.opt_sector='{$option_code}' and sector.pgoc_uuid=org_main.o_uuid ORDER BY name";
        $res_org=$db->Execute($q);
	    if(!$res_org->EOF){
	       // $table_row = "row".$row_count++;
    			$table_row = array();
    			$table_row ["Service"]= $res_sector->fields[1];
    			// added teh following to be blank
    			$table_row ['name'] = "                ";
    			$table_row ['Organization_Type'] = "                ";
    			$table_row ['Location'] = "                ";
    			$table_row ['Address'] = "                ";
    			$table_row ['Contact_Number'] = "                ";
    			array_push($table_data, $table_row);
        }

        while(!$res_org==NULL && !$res_org->EOF){
            $org_id=$res_org->fields["o_uuid"];
            $org_data=_shn_get_org_data($org_id,false);
            $table_row ["Service"]="";
            $table_row ["name"]=$res_org->fields["name"];
          //  $table_row ["Incidents"]=$org_data["incidents"];
       //     $table_row ["Services_Offered"]=$org_data["services"];
            $table_row ["Organization_Type"]=$org_data["type"];
            $table_row ["Location"]=(isset($org_data["location"])?$org_data["location"]:" - ");
            $table_row ["Address"]=(isset($org_data["address"])?$org_data["address"]:" - ");
            $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='curr'";
        	$res_contact=$db->Execute($q);
            if(!$res_contact==NULL && !$res_contact->EOF){
            	$contact_value = $res_contact->fields["contact_value"];
            	$table_row ["Contact_Number"]=isset($contact_value)?$contact_value:" - ";
        	}else{
        		$table_row ["Contact_Number"]=" - ";
        	}

            array_push($table_data, $table_row);
            $res_org->MoveNext();
        }
        $res_sector->MoveNext();
    }
   
   
    $title='Organization Report by Service';
    $txt = 'This a listing of Organizations Grouped by service';
    $or_report1_keyword_arr = array('mod'=>'or','report'=>'by service','report1'=>'orgs','users'=>'all');


    shn_report_fopen('pdf',"orgs_by_service",$or_report1_keyword_arr);
    shn_report_add_title($title);
    #shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();
}


function shn_or_all_orgs_pdf()
{
    global $global;
    include_once("view_org.inc");
    $db=$global["db"];
 //   $table_header=array('Service' =>'Service', 'name' => 'Organization Name','Service' =>'Service',
   // 'Incidents' =>'Incidents','Services_Offered' =>'Services Offered','Organization_Type' =>'Organization Type','Location' =>'Location', 'Address' =>'Address', 'Contact_Number' =>'Contact Number');
    //$table_header=array('name' => 'Name','Organization_Type' =>'Type','services'=>'Services','Location' =>'Location', 'Address' =>'Address', 'Contact_Number' =>'Contact Number');
    $table_header=array('name' => 'Organization Name','Organization_Type' =>'Organization Type','Service' =>'Service','Location' =>'Location', 'Address' =>'Address', 'Contact_Number' =>'Contact Number');
    $table_data = array();
   // $row_count = 0;

        $q = "SELECT o_uuid,parent_id,name,man_power,equipment,resources FROM org_main ORDER BY name";
        $res_org=$db->Execute($q);

        while(!$res_org==NULL && !$res_org->EOF){
            $org_id=$res_org->fields["o_uuid"];
            $org_data=_shn_get_org_data($org_id,false);
           
            $table_row ["name"]=$res_org->fields["name"];
          //  $table_row ["Incidents"]=$org_data["incidents"];
       //     $table_row ["Services_Offered"]=$org_data["services"];
            $table_row ["Organization_Type"]=$org_data["type"];
            $table_row ["Service"]=$org_data["sector"];;
            $table_row ["Location"]=$org_data["location"];
            $table_row ["Address"]=$org_data["address"];
            $table_row ["Contact_Number"]=$org_data["phone"];

      
            array_push($table_data, $table_row);
           $res_org->MoveNext();
        }
       


    $title='Organization Report';
    $txt = 'This a listing of Organizations of all incidents';
    $or_report1_keyword_arr = array('mod'=>'or','report'=>'all orgs','report1'=>'orgs','users'=>'all');

    
    shn_report_fopen('pdf',"orgs",$or_report1_keyword_arr);
    shn_report_add_title($title);
    #shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();
}


function _shn_or_drill_org($parent=null)
{
    global $global;
    $db=$global['db'];
    if(($parent==null)){
    		$parent="NULL";
    		$lvl_child=1;
    }else{
    		$lvl_child=shn_get_level($parent);
    		$lvl_child=$lvl_child+1;
    }
    $q="SELECT option_description FROM field_options WHERE field_options.option_code ='{$lvl_child}' AND field_name='opt_location_type'";
    
    $res=$db->Execute($q);
    $level=$res->fields["option_description"];
    ?>
	<h2><?php echo _t("Organization Report By "). $level ?></h2>
    <p>
    
    <?php 
    /*
    echo	 _t("Each Row is a ")."<strong>".$level."</strong>"._t(" ,Columns are")."<strong>"._t(" Services")."</strong>"._t(" provided by organizations.")."<br />";
	echo _t("Intersection shows the number of organizations providing the service in the location and its sub locations.")."<br />";
    */
    echo _t("This table covers the number of organizations that provide a particular service in a area as a geographical drill down. You may view  a sub-location by clicking on a parent-location and the organization details by clicking on the appropriate number. Please give attention to all services Not covered.");
    ?>
    </p>
    <br />
    <div>
    
    </div>
  
<!--</div>-->
<div id ="result">
    <table>
        <thead>
        <td><?php echo  $level ?></td>
        
<?php
    $q = "SELECT option_code,option_description FROM field_options WHERE field_name='opt_sector_type' ORDER BY option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
       echo "<td>".$res_sector->fields["option_description"]."</td>";
       $res_sector->MoveNext();
    }
       $res_sector->MoveFirst();
?>       
        </thead>
    <tbody>
<?php
	$q = "SELECT loc_uuid,name FROM location WHERE parent_id='{$parent}' ORDER BY name";
	//$res_loc=$db->Execute($q);
	$res_loc=shn_paging_get_report($q,5,$headers,array('post'=>false,'return'=>true));
	
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
<?php if(shn_location_is_leaf($res_loc->fields["loc_uuid"])){
        echo $res_loc->fields["name"];
      }else {
        echo "<a href='index.php?mod=or&act=drill_report_org_next&parent=".$res_loc->fields["loc_uuid"]."'>".$res_loc->fields["name"]."</a>";
      }
?>
        </td>
<?php
        while(!$res_sector==NULL && !$res_sector->EOF){
        		$count=0;
        		_shn_is_covered_org($res_loc->fields["loc_uuid"],$res_sector->fields[0],$count);
        		if($count==0){
        			//echo "<td><b><font color=#FF0000>".$count."</font></b></td>";
        			echo "<td><b><font color=#FF0000>Not Covered</font></b></td>";
        		}else{
        			//echo "<td><b><font color=#FF0000>".$count."</font></b></a></td>";
        			echo "<td><a href='index.php?mod=or&act=drill_report_org_show_orgs&loc=".$res_loc->fields["loc_uuid"]."&sec=".$res_sector->fields[0]."'><b><font color=#2E8B57>".$count."</font></b></a></td>";
        		}
        		
        
            $res_sector->MoveNext();
        }
        $res_sector->MoveFirst();
        $res_loc->MoveNext();
?>
    </tr>
<?php
    }
?>    
       </tbody>
  </table>
</div>

<?php
}

function _shn_or_drill_loc($parent=null)
{
    global $global;
    $db=$global['db'];
    if((null==$parent)){
    		$parent="NULL";
    		$lvl_child=1;
    }else{
    		$lvl_child=shn_get_level($parent);
    		$lvl_child=$lvl_child+1;
    }
    $q="SELECT option_description FROM field_options WHERE field_options.option_code ='{$lvl_child}' AND field_name='opt_location_type'";
    $res=$db->Execute($q);
    $level1=$res->fields["option_description"];
    $lvl_child=$lvl_child+1;
    $q="SELECT option_description FROM field_options WHERE field_options.option_code ='{$lvl_child}' AND field_name='opt_location_type'";
    $res=$db->Execute($q);
    $child_type=$res->fields["option_description"];
    if($parent<0){
    	$parent=NULL;
    }
    $parent_type=$level1;
    
  /*
    $child=$child+1;
    $q="select option_description from field_options where field_options.option_code=$child and field_name='opt_location_type'"; 
    $res_label=$db->Execute($q);
    $grand_child_type=$res_label->fields[0];
    */
?>
	
 <?php 
 	$tmp=shn_get_last_level();
 	if($tmp[0]==$lvl_child-1){
 	?>
 	<h2><?php echo _t("Organization Report for ").$parent_type; ?></h2>
    <div class="note">
    <?php 
    	$tmp=shn_get_last_level();
 	$child_type=$tmp[1];
 	//echo	_t("Each Row is a ".$child_type." ,Column is a  Service.");
 	?>
 	</div><?php
 	 }else{
 	?>
 	<h2><?php echo _t("Organization Report By ").$child_type._t(" for ").$parent_type; ?></h2>
    <p>
 
<?php
 	   	/*
 	   	echo "<strong>". _t("This report provides the coverage of services Regional wise ")."</strong><br />";
 	   	echo	 _t("Each Row is a ")."<strong>".$parent_type."</strong>"._t(" ,Columns are")."<strong>"._t(" Services")."</strong>"._t(" provided by organizations.")."<br />";
        //echo _t("This report provides the coverage of services Regional wise ")."<strong>".$child_type."</strong>"._t(" for each " )."<strong>"."$parent_type"."</strong><br />"; 
        
        echo _t("A Region is considered covered for a service if there is at least one organization providing the service")."<br />";
       // echo _t("Intersection shows the precentage of ".$child_type." Covered per each service.")."<br />";
       // echo _t("e.g. For a country how many districts have at least one organization providing the service. <br /> ");
        echo _t("If the country ")."<strong><em>C</em></strong>"._t(" has ")."<strong><em>X</em></strong>"._t(" no of districts and for the service ")."<strong><em>S</em></strong>"._t(" only ")."<strong><em>Y</em></strong>"._t(" no of districts have the presence of an organization then ")."<strong><em>C/S</em></strong>". _t(" intersection shows ")."<strong><em>Y/X</em></strong><br />";
 		echo _t("Percentage of ")."<strong><em>Y/X</em></strong>"." is also given for emphasis"."<br />";
 		echo _t("Please provide attention to locations with the note ")."<strong>Not covered</strong>"._t(" in Red as that means there is not a single organization " .
 				"providing that particular service in its sub locations");
 		*/
 		echo _t("This table covers the services provided by organizations in a geographical drill down. Thus you may view a sub-location by clicking on a parent-location. Percentage is based on sub-location coverage of that particular service. Please give attention to all locations not covered.");
 ?></p><br /><?php 
 }     
    
?>

<div id ="result">
    <table>
        <thead>
        <td>
        <?php echo  $parent_type ?>
        </td>
<?php
    $q = "SELECT option_code,option_description FROM field_options WHERE field_name='opt_sector_type' ORDER BY option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
       echo "<td>"._lc($res_sector->fields[1])."</td>";
       $res_sector->MoveNext();
    }
       $res_sector->MoveFirst();
?>       
        </thead>
    <tbody>
<?php
	$q = "SELECT loc_uuid,name FROM location WHERE parent_id='{$parent}' ORDER BY name";
	$res_loc=shn_paging_get_report($q,5,$headers,array('post'=>false,'return'=>true));
	//print_r($locs);	
    //$res_loc=$db->Execute($q);
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
<?php if(shn_location_is_leaf($res_loc->fields["loc_uuid"])){
        echo $res_loc->fields["name"];
      }else {
        echo "<a href='index.php?mod=or&act=drill_report_loc_next&parent=".$res_loc->fields["loc_uuid"]."'>".$res_loc->fields["name"]."</a>";
      }
?>
        </td>
<?php
        while(!$res_sector==NULL && !$res_sector->EOF){
            if(shn_location_is_leaf($res_loc->fields["loc_uuid"])){
//                echo ($res["active"]);
			   $count=0;
			   _shn_is_covered_org($res_loc->fields["loc_uuid"],$res_sector->fields[0],$count);
               //if(_shn_is_covered($res_loc->fields[0],$res_sector->fields[0])){
               if($count>0){
                    $active=_t("Covered");
		            //echo "<td><b><font color=#2E8B57>".$active."</font></b></td>";
                		echo "<td><a href='index.php?mod=or&act=drill_report_loc_show_orgs&loc=".$res_loc->fields["loc_uuid"]."&sec=".$res_sector->fields[0]."'><b><font color=#2E8B57>".$active."</font></b></a></td>";
                }else {
                    $active=_t("Not Covered");
		            echo "<td><b><font color=#FF0000>".$active."</font></b></td>";
                }
            }else {
                $res=_shn_coverage_loc($res_loc->fields["loc_uuid"],$res_sector->fields[0]);
                $precent=0;
                if($res["total"]>0){
                    $precent=round($res["active"]/$res["total"] *100,2);
                    if($res["active"]>0){
                    		echo "<td><a href='index.php?mod=or&act=drill_report_loc_show_orgs&loc=".$res_loc->fields["loc_uuid"]."&sec=".$res_sector->fields[0]."'><b><font color=#2E8B57>".$res["active"]."/".$res["total"]."</font> (<font color=#FF0000>".$precent."%</font>)</b></a></td>";
                    }else{
                    		$active=_t("Not Covered");
		            		echo "<td><b><font color=#FF0000>".$active."</font></b></td>";	
                    }
                }
                
                //echo "<td><b><font color=#2E8B57>".$res["active"]."/".$res["total"]."</font> (<font color=#FF0000>".$precent."%</font>)</b></td>";
            }
            $res_sector->MoveNext();
        }
        $res_sector->MoveFirst();
        $res_loc->MoveNext();
?>
    </tr>
<?php
    }
?>    
       </tbody>
  </table>
</div>

<?php
}

function _shn_coverage_loc($loc,$sector)
{
    global $global;
    $db=$global["db"];
    $result=array();
    $result["total"]=0;
    $result["active"]=0;
    /*
    if(_shn_is_covered($loc,$sector)){    
            $result["active"]=$result["active"]+1;
    }*/
    $q="SELECT loc_uuid,name FROM location WHERE parent_id='{$loc}'";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $result["total"]=$result["total"]+1;
        $next_lvl=$res_tmp->fields[0];
        $count=0;
        _shn_is_covered_org($res_tmp->fields["loc_uuid"],$sector,$count);
        if($count>0){
        //if(_shn_is_covered($res_tmp->fields["loc_uuid"],$sector)){    
            $result["active"]=$result["active"]+1;
        }
        $res_tmp->MoveNext();
    }
   return $result; 
}

function _shn_is_covered($loc,$sector)
{
    global $global;
    $db=$global["db"];
    $q="SELECT location_id FROM location_details,sector WHERE location_details.location_id='{$loc}' and location_details.poc_uuid=sector.pgoc_uuid AND sector.opt_sector='{$sector}'";
    $res_village=$db->Execute($q);
     if(!$res_village==NULL && !$res_village->EOF){
            return true;
    }
    $q="SELECT loc_uuid,name FROM location WHERE parent_id='{$loc}'";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $next_lvl=$res_tmp->fields[0];
        if(_shn_is_covered($next_lvl,$sector)){
            return true;
        }
        $res_tmp->MoveNext();
    }
   return false; 
}

function _shn_is_covered_org($loc,$sector,&$count)
{
    global $global;
    $db=$global["db"];
  //  $q="select location_id from location_details,sector,org_main,incident where location_details.location_id='{$loc}' and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector}' and sector.pgoc_uuid=org_main.o_uuid";
    $incident_arr=array($_SESSION['user_pref_ims_incident_id']);
	shn_get_incident_descendants($_SESSION['user_pref_ims_incident_id'],$incident_arr);
	$loc_arr=array($loc);
	shn_location_get_descendants($loc,&$loc_arr);
	$org_list=shn_or_org_loc_sector_incident_list($loc_arr,$sector,$incident_arr);
    $count=count($org_list);
}

function _shn_or_report_org_sector($sector)
{
    include_once("view_org.inc");
    global $global;
    $db=$global['db'];
    
?>
<h2><?php echo _t("Organization Report by Sector")?></h2>
<?php 
	shn_report_download("shn_or_service_coverage_pdf","Download as PDF");
    $q = "SELECT option_code,option_description FROM field_options WHERE field_name='opt_sector_type' ORDER BY option_description";
    $res_sector=$db->Execute($q);
    $sectors=array();
    while(!$res_sector==NULL && !$res_sector->EOF){
    	if(NULL==$sector){
            $sector=$res_sector->fields[0];
    	}
	$sectors[$res_sector->fields[0]]=$res_sector->fields[1];
	$res_sector->MoveNext();
    }
    shn_form_fopen('org_sector','or',array('req_message'=>false));
    
    shn_form_select($sectors,'Sector', 'opt_sector',"onchange=submit(this)", array('br'=>false));    
    
    shn_form_submit(_t("Filter"));
    
    shn_form_fclose();
    ?>
    <br>
    <?php
    $option_code=$sector;
    $q = "SELECT o_uuid,parent_id,name,man_power,equipment,resources FROM org_main,sector WHERE sector.opt_sector='{$option_code}' AND sector.pgoc_uuid=org_main.o_uuid ORDER BY name";
    $res_org=shn_paging_get_report($q,5,$headers,array('post'=>true,'return'=>true));
?>
<br>
<div id ="result">
    <table>
        <thead>
        	<td></td>
            <td><?php echo _t("Organization Name")?></td>
            <td><?php echo _t("Incidents")?></td>
            <td><?php echo _t("Services Offered")?></td>
            <td><?php echo _t("Organization Type")?></td>
            <td><?php echo _t("Location")?></td>
            <td><?php echo _t("Address")?></td>
            <td><?php echo _t("Contact Number")?></td>
        </thead>
        <tbody>
<?php    
   
        
        //$res_org=$db->Execute($q);
	    if(!$res_org->EOF){
	    ?>
	    <!--<tr>
		    <td>
	            <b><?php echo _t($res_sector->fields[1])?></b>
		    </td>
	    </tr>-->
	    <?php
        }
        while(!$res_org==NULL && !$res_org->EOF){
            $org_id=$res_org->fields['o_uuid'];
            _shn_display_org($org_id,false);
            $res_org->MoveNext();
        }
        
?>
   </tbody>
  </table>
</div>

<?php
}
