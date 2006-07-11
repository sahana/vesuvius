<?php
/**Processing functions(add ,edit,delete,ect) for Organizations of the Organization Registry 
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
function _shn_or_reg_org_cr()
{
    global $global;
    include_once "reg_org.inc";
    include_once $global['approot']."/inc/lib_security/authenticate.inc"; 
    include_once($global['approot']."/inc/lib_uuid.inc");

    		$db=$global['db'];
    		$org_id	=shn_create_uuid('org');
      //  $org_id = $db->GenID('org_seq',1);
        if (empty($org_id)){
            $error=true;
            //("add_org(): ORG_ID generation failed!");
            return false;
        }
        $q="select o_uuid from org_main where o_uuid='{$org_id}'";
        $res=$db->Execute($q);
        if(!$res->EOF){
            $error=true;
            add_error(SHN_ERR_OR_ORG_EXISTS);
            return false;
        }
        if($error!=true){
            //no validation done on other fields as they are not unique
            $privacy=0;
            $q="insert into org_main(o_uuid,name,opt_org_type,reg_no,man_power,equipment,resources,privacy)values('{$org_id}','{$_SESSION['org']['name']}','{$_SESSION['org']['type']}','{$_SESSION['org']['reg_no']}','{$_SESSION['org']['man_power']}','{$_SESSION['org']['equipment']}','{$_SESSION['org']['resources']}',$privacy)";
            $res=$db->Execute($q);
            
            $q="insert into resource_to_incident(incident_id,x_uuid) values('{$_SESSION['user_pref_ims_incident_id']}','{$org_id}')";
            $res=$db->Execute($q);
        		$i=0;
            while($i<count($_SESSION['org']['sector'])){
                $q="insert into sector(pgoc_uuid,opt_sector) values('{$org_id}','{$_SESSION['org']['sector'][$i]}')";
                $res=$db->Execute($q);
                $i=$i+1;
            }
            $q="insert into location_details(poc_uuid,location_id,address) values('{$org_id}','{$_SESSION['org']['loc']}','{$_SESSION['org']['contact_address']}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','curr','{$_SESSION['org']['contact_phone']}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','pmob','{$_SESSION['org']['contact_mobile']}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','name','{$_SESSION['org']['contact_name']}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','fax','{$_SESSION['org']['contact_fax']}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','email','{$_SESSION['org']['contact_mail']}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','web','{$_SESSION['org']['contact_web']}')";
            $res=$db->Execute($q);

    }
	
     if($error!=true){
?>
    <div id="result_msg">
       <?php echo $_SESSION['org']['name']?> Organization was succesfully registered
    <br /><br />
   
    Now you can add a Branch/Department Under  <?php echo $_SESSION['org']['name']?>
    e.g. Health Department,Relief Operations Department.
    <br />
    If you need to register a Branch/Department ,click the link below
    <br />
     <a href="index.php?&mod=or&act=reg_operation&org=<?php echo $org_id;?>">Register a Department/Branch</a>
    <br />
    Of course you can add Branches/Departments later on through the
    Register a Department/Branch link.
    <br /> <br />

    Instead if you wish to add another organization click the link below
    <br />
    <a href="index.php?&mod=or&act=reg_org">Register an Organization</a>
    </div>
    <br />
<?php
	 
    }
}


function _shn_or_reg_operation_cr()
{
    include_once "reg_org.inc";
    include_once "errors.inc";
    global $global;
    include_once $global['approot']."/inc/lib_validate.inc";
    include_once($global['approot']."/inc/lib_uuid.inc");
      $error=false;
    $VARCHAR=100;
    $parent_id=$_POST["parent"];
    list($error,$org_name)=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);
    list($error,$opt_org_sub_type)=(shn_validate_opt_field('opt_org_sub_type',$_POST{"opt_org_sub_type"},"Relationship to the parent organization",$VARCHAR,false))?array($error,$_POST{"opt_org_sub_type"}):array(true,NULL);
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
   
   	
    $loc=shn_location_get_form_submit_loc();
    if($loc==-1){
    		add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
        $error=true;
    }
  
    $contact_name=$_POST{"contact_name"};
    $contact_address=$_POST{"contact_add"};
    $contact_phone=$_POST{"contact_phone"};
    $contact_mobile=$_POST{"contact_mobile"};
    $contact_fax=$_POST{"contact_fax"};
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_POST{"contact_mail"};
        if(!shn_valid_email($contact_mail)){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }
    }
    $contact_web=$_POST{"contact_web"};
    $man_power=$_POST{"man_power"};
    $equipment=$_POST{"equipment"};
    $resources=$_POST{"resources"};
    $chk_branch=(isset ($_POST{"chk_branch"}))?1:0;
    $db=$global['db'];
    $org_id	=shn_create_uuid('org');;
    if (empty($org_id)){
        return false;
    }
    $q="select o_uuid from org_main where o_uuid='{$org_id}'";
    $res=$db->Execute($q);
    if(!$res->EOF){
        $error=true;
        add_error(SHN_ERR_OR_ORG_EXISTS);
    }
    if(!$error){
        
    //no validation done on other fields as they are not unique
        $q="insert into org_main(o_uuid,parent_id,name,opt_org_type,man_power,equipment,resources)values('{$org_id}','{$parent_id}','{$org_name}','{$opt_org_sub_type}','{$man_power}','{$equipment}','{$resources}')";
        $res=$db->Execute($q);
        $q="insert into resource_to_incident(incident_id,x_uuid) values('{$_SESSION['user_pref_ims_incident_id']}','{$org_id}')";
        $res=$db->Execute($q);
        $i=0;
        while($i<count($sector)){
            $q="insert into sector(pgoc_uuid,opt_sector) values('{$org_id}','{$sector[$i]}')";
            $res=$db->Execute($q);
            $i=$i+1;
        }
    }
    $q="insert into location_details(poc_uuid,location_id,address) values('{$org_id}','{$loc}','{$contact_address}')";
    $res=$db->Execute($q);
  
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','name','{$contact_name}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','curr','{$contact_phone}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','pmob','{$contact_mobile}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','fax','{$contact_fax}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','email','{$contact_mail}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','web','{$contact_web}')";
    $res=$db->Execute($q);
    if(!$error){
     ?>
    <div id="result_msg">
       <?php echo $org_name?> Operation was succesfully registered
    </div>
    <br />
<?php
    }
        _shn_or_regform_operation($error);
        
    
    

}

function _shn_or_del_org()
{
    global $global;
    $db=$global['db'];
    $org_id=$_POST{"org_id"};
    $q="select name from org_main where o_uuid='{$org_id}'";
    $res=$db->Execute($q);
    $org_name=$res->fields["name"];
    $q="delete from org_main where o_uuid='{$org_id}'";
    $res=$db->Execute($q);
    $q="delete from sector where pgoc_uuid='{$org_id}'";
    $res=$db->Execute($q);
    $q="delete from location_details where poc_uuid='{$org_id}'";
    $res=$db->Execute($q);
    $q="delete from contact where pgoc_uuid='{$org_id}'";
    $res=$db->Execute($q);
/*
  if($error==true){
		_shn_or_viewform_org($org_id,$error);
        	return false;
	    }
*/
  ?>
    <div id="result_msg">
       <?php echo $org_name?> Organization was succesfully Deleted
    </div>
    <br />
<h2> Organization Registry</h2>
<?php
        _shn_or_viewform_allorg();    
}

function _shn_or_edit_org()
{
    global $global;
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    $incidents=$_POST["incidents"];
    $error=false;
    $VARCHAR=100;
    $org_id=$_POST{"org_id"};
    $parent=_shn_or_is_root($org_id);
	if($parent){
        		$type="opt_org_type";	
    }else{
        		$type="opt_org_sub_type";	
    }
    list($error,$org_name)=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);
    list($error,$org_type)=(shn_validate_opt_field($type,$_POST{$type},"Organization Type",$VARCHAR,false))?array($error,$_POST{$type}):array(true,NULL);
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
   	$loc=shn_location_get_form_submit_loc();
    if($loc==-1){
    		add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
        $error=true;
    }
	
    if (trim(strlen($_POST{"reg_no"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $reg_no=$_POST{"reg_no"};
    }
    if (trim(strlen($_POST{"contact_name"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_name=$_POST{"contact_name"};
    }
/*
    if (trim(strlen($_POST{"contact_add"})) > $CONTACT_ADDRESS){
        add_error(SHN_ERR_OR_REG_MAX);
    }else {
       $contact_address=$_POST{"contact_add"};
    }
*/
    $contact_address=$_POST{"contact_add"};
    if (trim(strlen($_POST{"contact_phone"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_phone=$_POST{"contact_phone"};
    }
    if (trim(strlen($_POST{"contact_mobile"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_mobile=$_POST{"contact_mobile"};
    }
    if (trim(strlen($_POST{"contact_fax"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
         $contact_fax=$_POST{"contact_fax"};
    }
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_POST{"contact_mail"};
        if(!shn_valid_email($contact_mail)){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }
    }
    if (trim(strlen($_POST{"contact_web"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_web=$_POST{"contact_web"};
    }
    if (trim(strlen($_POST{"man_power"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $man_power=$_POST{"man_power"};
    }
    if (trim(strlen($_POST{"equipment"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $equipment=$_POST{"equipment"};
    }
    $resources=$_POST{"resources"};
    if(!$error){
    $db=$global['db'];
           //no validation done on other fields as they are not unique
            $q="update org_main set name='{$org_name}',opt_org_type='{$org_type}',reg_no='{$reg_no}',man_power='{$man_power}',equipment='{$equipment}',resources='{$resources}' where o_uuid='{$org_id}'";
            $res=$db->Execute($q);
            $q="delete from sector where pgoc_uuid='{$org_id}'";
            $res=$db->Execute($q);
            $i=0;
            while($i<count($sector)){
                $q="insert into sector(pgoc_uuid,opt_sector) values('{$org_id}','{$sector[$i]}')";
                $res=$db->Execute($q);
                $i=$i+1;
            }
            $q="delete from resource_to_incident where x_uuid='{$org_id}'";
            $res=$db->Execute($q);
            $i=0;
            
            while($i<count($incidents)){
                $q="insert into resource_to_incident(incident_id,x_uuid) values($incidents[$i],'{$org_id}')";
                $res=$db->Execute($q);
                $i=$i+1;
            }
            
            $q="update location_details set location_id='{$loc}',address='{$contact_address}' where poc_uuid='{$org_id}'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_name}' where pgoc_uuid='{$org_id}' and opt_contact_type='name'";
            $res=$db->Execute($q);
    		$q="update contact set contact_value='{$contact_phone}' where pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_mobile}' where pgoc_uuid='{$org_id}' and opt_contact_type='pmob'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_fax}' where pgoc_uuid='{$org_id}' and opt_contact_type='fax'";
            $res=$db->Execute($q);
           	$q="update contact set contact_value='{$contact_mail}' where pgoc_uuid='{$org_id}' and opt_contact_type='email'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_web}' where pgoc_uuid='{$org_id}' and opt_contact_type='web'";
            $res=$db->Execute($q);
           
  ?>
    <div id="result_msg">
       <?php echo $org_name?> Organization was succesfully Updated
    </div>
    <br />
<h2> Organization Registry</h2>
<?php
    }
     if($error==true){
		_shn_or_viewform_org($org_id,$error);
        	return false;
	 }
        _shn_or_viewform_allorg();    
}
?>
