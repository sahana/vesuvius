<?php
include_once $global['approot'] . '/inc/reporting/lib_chart.inc';
//require_once $global['approot'] . '/mod/dsm/home.inc';


if ($_SESSION['disease_id']) {
	//_shn_dsm_show_general();
    switch ($_REQUEST['sub']) {
	    case 'location' :
		    {
		    	_shn_dsm_tab_menu();
		    	_shn_dsm_show_locations();
			    break;
		    }
	    case 'symptoms' :
	    	{
	    		_shn_dsm_tab_menu();
	    		_shn_dsm_show_disease_symptoms();
	    	    break;
	    	}
        case 'risk' :
	    	{
	    		_shn_dsm_tab_menu();
	    		_shn_dsm_show_risk();
	    	    break;
	    	}
        case 'cost' :
	    	{
	    		_shn_dsm_tab_menu();
	    		_shn_dsm_show_cost();
	    	    break;
	    	}
	    case 'statistics' :
	    	{
	    		_shn_dsm_tab_menu();
	    	    _shn_dsm_show_statistics();
	    	    break;
	    	}
	    default :
	    	{
	    		//$details = _shn_general_data_from_table($disease_id);
	    		_shn_dsm_tab_menu();
	    		_shn_dsm_show_general();
	    	}
    }
	
} else {
    $recent = _shn_dsm_get_resent();//print $recent->fields['dis_uuid'];
    //$rec_id = array();
   // $rec_id = $recent->fields['dis_uuid'];print $rec_id;
   shn_form_fopen('sur_rep','dsm',array('req'=>false));
   shn_form_fsopen(_('Diseases'));
   ?>
    <div><?php
	shn_chart_display("shn_dsm_patients_diseases_chart");
	?></div>
<div id="result">
<table>

<?php
    while (!$recent -> EOF) {
    	?><tr><td><?php
        //print $recent->fields['dis_uuid'] . '...........' . $recent->fields['dis_name'];
        echo '<a href="index.php?mod='.$global['module'].'&act=sur_rep&dis_uuid='.$recent->fields['dis_id'].'">'.$recent->fields['dis_name'].'</a><br />';
        ?></td></tr><?php
        $recent->MoveNext();
        
    }
    ?>
</table>
</div>

<?php
    shn_form_fsclose();
    shn_form_fclose();
}



function _shn_dsm_show_general()
{
	$details = _shn_general_data_from_table($_SESSION['disease_id']);
	shn_form_fopen('sur_rep','dsm',array('req'=>false));
	//shn_form_hidden(array ('seq' => 'page3'));
	
	shn_form_fsopen(_('General Details'));
	print "Disease Name : ".$details['dis_name']."<br><br>";
	print "Medical Name : ".$details['med_name']."<br><br>";
	print "Age Group : ".$details['age_group']."<br><br>";
	print "Carrier : ".$details['carrier']."<br><br>";
	print "Cause : ".$details['cause'];
	shn_form_fsclose();
	
	shn_form_fclose();
}

function _shn_dsm_tab_menu()
{
	shn_adm_menuopen(_t("Disease Surviellance Module"));
 
	shn_adm_menuitem("sur_rep", _t("General Details"));
	shn_adm_menuitem("sur_rep&sub=location", _t("Location"));
	shn_adm_menuitem("sur_rep&sub=symptoms", _t("Symptoms"));
	shn_adm_menuitem("sur_rep&sub=statistics", _t("Statistics"));
	shn_adm_menuitem("sur_rep&sub=risk", _t("Risk Analysis"));
	shn_adm_menuitem("sur_rep&sub=cost", _t("Cost Estimation"));
	
	shn_adm_menuclose();
}

function _shn_dsm_show_locations(){
	global $global;
    $db = $global['db'];
    $module = $global['module'];
    //$db->debug=true;
    $dis_id = $_SESSION['disease_id'];
    
    include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	shn_chart_display("shn_dsm_disease_vs_location_chart");
	
    include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
   
    $query_dis_name = "SELECT dis_name,med_name FROM dsm_diseases WHERE dis_id =?";
    $res_name = $db->Execute($query_dis_name,array($dis_id));
    $dis_name=$res_name->fields["dis_name"];
    $med_name=$res_name->fields["med_name"];
    
    shn_form_fopen("rep_dis",null,array('req'=>false));
    echo "<br></br>";
    echo "<strong> Effeted area of ".$dis_name."&nbsp;(".$med_name.")</strong>";
    echo "<br><br>";
	//shn_form_hidden(array('seq'=>'img'));
    
	shn_gis_add_marker_map_form("Area Map","",null,array('marker'=>'single'));
	shn_form_multi_select('symptoms', array('ertet','ertet','dgdhgdh','dghedghd','gereyeyh'), _t('Symptoms'));
    
	shn_form_fclose();
	
}

//modyed function for show diseas symptoms
function _shn_dsm_show_disease_symptoms(){
	global $global;
    $db = $global['db'];
    $module = $global['module'];
    //$db->debug=true;
    $dis_id = $_SESSION['disease_id'];
   
    $query_dis_name = "SELECT dis_name,med_name FROM dsm_diseases WHERE dis_id =?";
    $res_name = $db->Execute($query_dis_name,array($dis_id));
    $dis_name=$res_name->fields["dis_name"];
    $med_name=$res_name->fields["med_name"];
    
    shn_form_fopen('','',array('req_massege'=>false));
    shn_form_fsopen(_t("Symptoms of Disease &nbsp;".$dis_name."&nbsp;(".$med_name.")"));
    
	$query = "SELECT ds.description FROM dsm_disease_symptoms dds JOIN dsm_symptoms ds ON ds.sym_id=dds.sym_id AND dds.dis_id=?";
    $res = $db->Execute($query,array($dis_id));
    echo "<ul>";
    while($row=$res->FetchRow()){
    	//$discription = $row["description"];
        echo "<li><div>".$row["description"]."</div></li>";
        echo "<br>";
    }
    echo "</ul>";

    shn_form_fsclose();
    shn_form_fclose();
}
//............................................

function _shn_dsm_show_symptoms()
{
	$stored_symptoms = _shn_dsm_get_stored_sym();
	shn_form_fopen('sur_rep','dsm',array('req'=>false));
	//shn_form_hidden(array ('seq' => 'page3'));
	echo '<br></br>';
	echo '<p>' . 'Symptoms of ' . $_SESSION['disease_id'] . '.</p>';
	echo '<br></br>';
	
	shn_form_fsopen(_('Symptoms'));
	foreach ($stored_symptoms as $sym) {
		shn_form_label('',$sym);
	}
	shn_form_fsclose();
	
	shn_form_fclose();
}

function _shn_dsm_show_statistics()
{
	shn_form_fopen('sur_rep','dsm',array('req'=>false));
	shn_form_fsopen(_t('Statistics'));

    shn_form_select(array('year'=>'Last 10 years','month'=>'Within this year'));
    
	shn_form_fsclose();
	
	shn_form_fclose();
}

function _shn_dsm_show_risk()
{
	shn_form_fopen('sur_rep','dsm',array('req'=>false));
	
	shn_form_fsopen(_('Risk Analysis'));
	print 'Risk';
	shn_form_fsclose();
	
	shn_form_fclose();
}

function _shn_dsm_show_cost()
{
	shn_form_fopen('sur_rep','dsm',array('req'=>false));
	
	shn_form_fsopen(_('Cost Estimation'));
	print 'Cost';
	shn_form_fsclose();
	
	shn_form_fclose();
}
?>
