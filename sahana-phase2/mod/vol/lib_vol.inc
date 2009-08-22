<?php
/**Internal Library of the Organization Registry 
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
include_once $global['approot']."/inc/lib_form.inc";

function _shn_vol_get_start_loc()
{
    global $global;
    global $conf;
    $db=$global['db'];
    $q="select value from config where module_id='vol' and confkey='loc_start'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	return $conf['mod_vol_start_loc'];
    }else {
    	return $res->fields[0];
    }
}

function shn_vol_get_loc_range()
{
    global $global;
    global $conf;
    $db=$global['db'];
    $loc=array();
    $q="select value from config where module_id='vol' and confkey='loc_range_start'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	$loc["start"]=$conf['mod_vol_loc_level_start'];
    }else {
    	$loc["start"]=$res->fields[0];
    }
    $q="select value from config where module_id='vol' and confkey='loc_range_end'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	$loc["end"]=$conf['mod_vol_loc_level_end'];
    }else {
    	$loc["end"]=$res->fields[0];
    }
    return $loc;
}

function _shn_vol_action_change_javascript($form,$change)
{
?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName("<?php echo $change?>");
         x[0].value=action;
         document.<?php echo $form?>.submit();
         return;
    }
</script>
<?php
}

function _shn_vol_location_string($loc)
{
	global $global;
	$db=$global["db"];
	$loc_arr=array();
   	shn_get_parents($loc,&$loc_arr);
   	if($loc_arr[0]=='unknown'){
   		shn_form_label(_t("Organization Location"),"Unknown");
   	}else{
   		
   		$max=count($loc_arr)-1;
   		array_pop($loc_arr);
   		for($count=0;$count<$max;$count++){
   			$x=array_pop($loc_arr);
   			$q="select name from location where loc_uuid='{$x}'";
    			$res=$db->Execute($q);
    			if($count==0 ){
    				$location=$location.$res->Fields("name");
    			}else{
   				$location=$location." -->".$res->Fields("name");
    			}
    			
   		}
   	}
   	return $location;
}
/*
function _shn_vol_action_change_javascript($change)
{
?>
<script type="text/javascript">
    function change_action(action){

        var x=document.getElementsByName("<?php echo $change?>");
         x[0].value=action;
         document.view.submit();
         return;
    }
</script>
<?php
}*/

function _shn_vol_admin_javascript($name)
{
?>
<script type="text/javascript">

 // sort function - ascending (case-insensitive)
        function sortFuncAsc(record1, record2) {
            var value1 = record1.optText.toLowerCase();
            var value2 = record2.optText.toLowerCase();
            if (value1 > value2) return(1);
            if (value1 < value2) return(-1);
            return(0);
        }

        // sort function - descending (case-insensitive)
        function sortFuncDesc(record1, record2) {
            var value1 = record1.optText.toLowerCase();
            var value2 = record2.optText.toLowerCase();
            if (value1 > value2) return(-1);
            if (value1 < value2) return(1);
            return(0);
        }

        function sortSelect(selectToSort, ascendingOrder) {
            if (arguments.length == 1) ascendingOrder = true;    // default to ascending sort

            // copy options into an array
            var myOptions = [];
            for (var loop=0; loop<selectToSort.options.length; loop++) {
                myOptions[loop] = { optText:selectToSort.options[loop].text, optValue:selectToSort.options[loop].value };
            }

            // sort array
            if (ascendingOrder) {
                myOptions.sort(sortFuncAsc);
            } else {
                myOptions.sort(sortFuncDesc);
            }

            // copy sorted options from array back to select box
            selectToSort.options.length = 0;
            for (var loop=0; loop<myOptions.length; loop++) {
                var optObj = document.createElement('option');
                optObj.text = myOptions[loop].optText;
                optObj.value = myOptions[loop].optValue;
                selectToSort.options.add(optObj);
            }
        }

        function add_types(){
            var y=document.getElementsByName("type");
            var z=document.getElementsByName("type_abbr");
            var add=document.getElementsByName("added");
            var remove=document.getElementsByName("removed");
            var exist=search(add[0].value,z[0].value,true,y[0].value);
            if(exist){
                alert("The Type Exists,you just added it");
                return;
            }
            var x=document.getElementsByName("<?php echo $name?>");
            exist=search_select_box(x[0],z[0].value,true,y[0].value);
            if(exist){
                alert("The Type Exists in the DataBase");
                return;
            }
            exist=search(remove[0].value,z[0].value,true,y[0].value);
            if(exist){
                remove[0]=del(remove[0].value,z[0].value);
                return;
            }
            opt = document.createElement("option") ;
            opt.text = y[0].value ;
            opt.value = z[0].value ;
            var k=x[0].options.length;
            x[0].options[k]=opt;
            sortSelect(x[0], true) ;
            add[0].value= add[0].value+":"+z[0].value+"|"+y[0].value;
            y[0].value=null;
            z[0].value=null
        }

        function remove_types(){
            var x=document.getElementsByName("<?php echo $name?>");
            removeSelectedOptions(x[0]);
            sortSelect(x[0], true) ;
        }

        function hasOptions(obj) {
    	    if (obj!=null && obj.options!=null) { return true; }
	            return false;
	    }
	
        function removeSelectedOptions(from) { 
	        if (!hasOptions(from)) { return; }
	        if (from.type=="select-one") {
		        from.options[from.selectedIndex] = null;
		    }
	        else {
		        var add=document.getElementsByName("added");
                var remove=document.getElementsByName("removed");
                for (var i=(from.options.length-1); i>=0; i--) { 
        			var o=from.options[i]; 
			        if (o.selected) { 
					    var exist=search(add[0].value,o.value,false);
            			if(exist){
					        add[0].value=del(add[0].value,o.value);
                        }else{
                         	remove[0].value= remove[0].value+":"+o.value+"|"+o.text;
					    }
				        from.options[i] = null; 
				    }
            	}
            }
             	from.selectedIndex = -1; 
	    } 

        function search(arr,value,both,desc){
            if (window.RegExp) {
                var re = new RegExp(value);
                var temp = new Array(); 
                temp = arr.split(':');
                if (temp.length==1){
                    return false;
                }
                for (var i=0; i<temp.length; i++) {
                    var options = new Array(); 
                    options= temp[i].split('|');
                    var re = new RegExp(value);
                    if (re.test(options[0])) {
                        return true;
                    }
				    if(both){
		                re = new RegExp(desc);
                        if (re.test(options[1])) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        function search_select_box(obj,value,both,desc) {
	        if (window.RegExp) {
        		if (!hasOptions(obj)) { return false; }
		        for (var i=0; i<obj.options.length; i++) {
		            var re = new RegExp(value);
                    if (re.test(obj.options[i].value)) {
                        return true;
                    }
				    if(both){
		                re = new RegExp(desc);
                        if (re.test(obj.options[i].text)) {
                            return true;
                        }
		            }
                }
	        }
            return false;
        }
        function del(from,what){
            var temp = new Array();
            temp = from.split(':');
            from=null;
            if (temp.length==1){
                return false;
            }
            for (var i=1; i<temp.length; i++) {
                var options = new Array(); 
                options= temp[i].split('|');
                if(options[0]!=what){
                    
                    from= from+":"+options[0]+"|"+options[1];
                }
            }
            
            return from;
        }
	
</script>
<?php
}
function _shn_vol_get_loc_parents($child)
{
    global $global;
    $db=$global['db'];
    $q="select search_id,name,location.location_id from location_details,location where poc_uuid='{$child}' and location_details.location_id=location.location_id";
    $res_temp=$db->Execute($q);
    $final=array();
    $final[0]=$res_temp->fields[0];
    $final[1]=$res_temp->fields[1];
    $final[2]=$res_temp->fields[2];

    $bsd_village=$res_temp->fields[0];
    $loc=split("\.", $bsd_village);
    $loc_return=array();
    for($k=0;$k<count($loc)-1;$k++){
        $cur=$cur.$loc[$k];
        $temp=array();
        $temp[0]=$cur;     
        $q="select name,location_id from location where search_id='$cur'";
        $res_loc=$db->Execute($q);
        $temp[1]=$res_loc->fields[0];
        $temp[2]=$res_loc->fields[1];
        array_push(
            $loc_return,
            $temp
            );
        if($k!=count($loc)-1){
            $cur=$cur.".";
        }
	}
    array_push(
        $loc_return,
        $final
    );
     return $loc_return;
}


function _shn_vol_display_skills($error=false,$value=NULL,$label=NULL)
{
    if($value!=NULL && is_array($value)){
	    $extra_opts['value']=$value;
	    //$extra_opts['req']=false;
    }else{
	    //$extra_opts['req']=true;
    }
    if($error==true){
    		$extra_opts['value']=$_SESSION['vol']['skill'];
    }
   ?><div class="info"><?php echo _t("Select the skills you have");?></div><br /><?php
    shn_form_opt_multi_select('opt_skill_type','','multiple="true"',$extra_opts);

}

function _shn_vol_display_gender($error=false,$value=NULL,$label=NULL)
{
    if($value!=NULL){
	    $extra_opts['value']=$value;
	    //$extra_opts['req']=false;
    }else{
	    //$extra_opts['req']=true;
    }
    if($error==true){
    		$extra_opts['value']=$_SESSION['vol']['gender'];
    }
    $label=($label==NULL)?_t("Gender:"):$label;
    shn_form_opt_select('opt_gender',$label,$select_opts,$extra_opts);
}


function _shn_vol_display_sector($error=false,$value=NULL)
{
    if($value!=NULL){
        $extra_opts['value']=$value;
       // $extra_opts['req']=false;
    }else{
       // $extra_opts['req']=true;
    }
    ?><div class="info"><?php echo _t("Select the sector you are in ,e.g. if you are a medical practitioner then you are in the medical sector");?></div><br /><?php
    $extra_opts['req']=true;
    shn_form_opt_multi_select('opt_sector_type','','multiple="true"',$extra_opts);
}
/*
function _shn_vol_display_contact_person($error=false,$org=true,$po_uuid=null)
{
    ?><div class="info"><?php echo  _t("Please provide contact details that can be used to contact your in a disaster");?> </div><br /><?php
    if(!shn_is_null($po_uuid)){
        global $global;
        $db=$global['db'];
        $q = "select address from location_details where poc_uuid={$po_uuid}";
        $res_addr=$db->Execute($q); 
        $contact_address=$res_addr->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='curr'";
        $res_phone=$db->Execute($q);
        $contact_phone=$res_phone->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='pmob'";
        $res_mobile=$db->Execute($q);
        $contact_mobile=$res_mobile->fields[0];
        if($org){
            $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='name'";
            $res_name=$db->Execute($q);
            $contact_name=$res_name->fields[0];
        }
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='fax'";
        $res_fax=$db->Execute($q);
        $contact_fax=$res_fax->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='email'";
        $res_email=$db->Execute($q);
        $contact_email=$res_email->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='web'";
        $res_web=$db->Execute($q);
        $contact_web=$res_web->fields[0];
    }
    $extra_opts['value']=$contact_address;
    shn_form_text(_t("Address : "),'contact_add','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_phone;
    shn_form_text(_t("Phone : "),'contact_phone','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_mobile;
    shn_form_text(_t("Mobile No : "),'contact_mobile','size="50"',$extra_opts);
    $extra_opts['value']=$contact_fax;
    shn_form_text(_t("Fax : "),'contact_fax','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_email;
    shn_form_text(_t("Email : "),'contact_mail','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_web;
    shn_form_text(_t("Website : "),'contact_web','size="50"',$extra_opts);
}*/

function _shn_vol_display_contact_person($error=false,$confirm=false,$po_uuid=null)
{
        
    if($confirm==true){
    		
    		shn_form_label(_t("Address"),$_SESSION['vol']['contact_address']);
    		shn_form_label(_t("Phone"),$_SESSION['vol']['contact_phone']);
    		shn_form_label(_t("Mobile"),$_SESSION['vol']['contact_mobile']);
    		shn_form_label(_t("Fax"),$_SESSION['vol']['contact_fax']);
    		shn_form_label(_t("Website"),$_SESSION['vol']['contact_web']);
    		return;
    }
    ?><div class="info"><?php echo  _t("Please provide contact details that can be used to contact your organization in a disaster");?> </div><br /><?php
   if($error==true){
   		$contact_address=$_SESSION['vol']['contact_address'];
        $contact_phone=$_SESSION['vol']['contact_phone'];
        $contact_mobile=$_SESSION['vol']['contact_mobile'];
        $contact_name=$_SESSION['vol']['contact_name'];
        $contact_fax=$_SESSION['vol']['contact_fax'];
        $contact_email=$_SESSION['vol']['contact_mail'];
        $contact_web=$_SESSION['vol']['contact_web'];
    }
    if(!shn_is_null($po_uuid)){
        global $global;
        $db=$global['db'];
        $q = "select address from location_details where poc_uuid='{$po_uuid}'";
        $res_addr=$db->Execute($q); 
        $contact_address=$res_addr->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='curr'";
        $res_phone=$db->Execute($q);
        $contact_phone=$res_phone->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='pmob'";
        $res_mobile=$db->Execute($q);
        $contact_mobile=$res_mobile->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='fax'";
        $res_fax=$db->Execute($q);
        $contact_fax=$res_fax->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='email'";
        $res_email=$db->Execute($q);
        $contact_email=$res_email->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='web'";
        $res_web=$db->Execute($q);
        $contact_web=$res_web->fields[0];
    }
 
    $extra_opts['value']=$contact_address;
      $extra_opts['help']=_t("Address to be contacted in a disaster");
    shn_form_text(_t("Address : "),'contact_add','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_phone;
      $extra_opts['help']=_t("Land line number to be contacted in a disaster");
    shn_form_text(_t("Phone : "),'contact_phone','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_mobile;
      $extra_opts['help']=_t("Mobile Phone number to be contacted in a disaster");
    shn_form_text(_t("Mobile No : "),'contact_mobile','size="50"',$extra_opts);
    $extra_opts['value']=$contact_fax;
      $extra_opts['help']=_t("Fax number to be contacted in a disaster");
    shn_form_text(_t("Fax : "),'contact_fax','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_email;
      $extra_opts['help']=_t("Email address to be contacted in a disaster");
    shn_form_text(_t("Email : "),'contact_mail','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_web;
      $extra_opts['help']=_t("Website of the Organization");
    shn_form_text(_t("Website : "),'contact_web','size="50"',$extra_opts);
}


function _shn_vol_display_logininfo($error=false)
{
// for get login info
    $login_info = array(
    		       	array('desc'=>_t("Account Name : "),'type'=>"text",'size'=>20,'name'=>'account_name','br'=>1),
                    array('desc'=>_t("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
                    array('desc'=>_t("* Password for Login: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_t("* Confirm Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    return $login_info;
}

function _shn_vol_display_avaliability($error=false,$po_uuid=null)
{
    if($value!=NULL){
	    $extra_opts['value']=$value;
	    //$extra_opts['req']=false;
    }else{
	    //$extra_opts['req']=true;
    }
    $label=($label==NULL)?_t("Gender:"):$label;
    shn_form_opt_select('opt_gender',$label,$select_opts,$extra_opts);
}

function _shn_vol_display_extra($error=false)
{
    shn_form_checkbox(_t("Upload Your Picture"),'chk_image',null,$chkbox_opts);
    shn_form_checkbox(_t("Create an Account for Login"),'chk_login',null,$chkbox_opts);
}

/**
 * This is the image upload form
 * @param mixed $errors 
 * @access public
 * @return void
 */
function _shn_vol_image_upload($errors=false) 
{
    if($errors)
        display_errors();

    shn_form_fopen("add_image",null,array('enctype'=>'enctype="multipart/form-data"'));

    shn_form_hidden(array('seq'=>'upload_pic'));
    shn_form_fsopen(_t('Upload Picture'));
    shn_form_upload(_t('Upload Picture'),"picture");
    shn_form_fsclose();
    shn_form_submit(_t('Next'));
    shn_form_fclose();
}


/**
 *
 * This function can resize a given image and save it to the given
 * location. 
 *
 * @todo Need to move this out to a library, e.g. image library
 * @param mixed $src_path 
 * @param mixed $desc_path 
 * @param mixed $width 
 * @param mixed $height 
 * @access public
 * @return void
 */
function shn_image_resize($src_path,$desc_path,$width,$height)
{
    $info = getimagesize($src_path);
    if(! $info)
        return false;

    $width_orig = $info[0];
    $height_orig = $info[1];

    if ($width && ($width_orig < $height_orig)) {
       $width = ($height / $height_orig) * $width_orig;
    } else {
       $height = ($width / $width_orig) * $height_orig;
    }
    
    $image_p = imagecreatetruecolor($width, $height);

    list($ignore,$mime) = split("\/",$info['mime']);
    $func = 'imagecreatefrom'.$mime;
    $image = $func($src_path);

    imagecopyresampled($image_p, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);
    $func2 = 'image'.$mime;
    $func2($image_p,$desc_path,100);
}
/* }}} */

/* {{{ Image Resize DB */
/**
 *
 * This function can resize a given image and save it to the given
 * location. 
 *
 * @todo Need to move this out to a library, e.g. image library
 * @param mixed $src_path 
 * @param mixed $desc_path 
 * @param mixed $width 
 * @param mixed $height 
 * @access public
 * @return void
 */
function shn_image_resize_from_string($img,$width,$height)
{
    
    $width_orig = $img['image_width'];
    $height_orig = $img['image_height'];

    if ($width && ($width_orig < $height_orig)) {
       $width = ($height / $height_orig) * $width_orig;
    } else {
       $height = ($width / $width_orig) * $height_orig;
    }
    
    $image_p = imagecreatetruecolor($width, $height);

    $mime = $img['image_type'];
    $image = imagecreatefromstring($img['image']);

    imagecopyresampled($image_p, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);
    $func2 = 'image'.$mime;
    $func2($image_p);
}
/* }}} */

/* {{{ Image To Database */

function _shn_vol_image_to_db($p_uuid,$pic,$type,$height,$width,$replace_id=null)
{    
    global $global;
    
    $pic = addslashes($pic);
    
    if($replace_id){
        $sql = "UPDATE person_image SET 
                    image = '$pic',
                    image_type = '$type',
                    image_height = '$height',
                    image_width = '$width',
                WHERE image_id = '$replace_id'";
    }else{
        $sql = "INSERT INTO person_image (p_uuid, image, image_type, image_height, image_width) 
                VALUES ('$p_uuid','$pic','$type','$height','$width')";
    }
    
    $global['db']->Execute($sql);
    
}


/**
 *
 * This is function show the tumbnail if available and say "Image not
 * available" otherwise
 *
 * @todo Need to move to a different file, possibly to a library.
 * @param mixed $p_uuid 
 * @access public
 * @return void
 */
function shn_show_thumb($p_uuid,$session=false)
{
    global $global;
    global $conf;

    if($conf['mod_mpr_upload_picture_savehandler'] == 'database'){
        if($session && $_SESSION['mpr']['entry']['image']){
	        $src_ori = "index.php?stream=image&mod=mpr&act=addmp_img&session=true";
            $src_tmp = "index.php?stream=image&mod=mpr&act=addmp_img&session=true&thumbnail=true";
        }else{
            //need to get the type
            $sql = "SELECT image_type,image_height, image_width FROM person_image WHERE p_uuid = '$p_uuid'";
            $arr = $global['db']->GetAll($sql);
            if(isset($arr[0]['image_type'])){
                $type='&imagetype='.$arr[0]['image_type'];
                $height = $arr[0]['image_height']+20;
                $width = $arr[0]['image_width']+20;
            } 
	        $src_ori = "index.php?stream=image&mod=mpr&act=addmp_img&p_uuid=".$p_uuid.$type;
            $src_tmp = "index.php?stream=image&mod=mpr&act=addmp_img&thumbnail=true&p_uuid=".$p_uuid.$type;
        }
    }else{
        //Since we don't know the extension
        $dir = $global['approot'].'www/tmp/';
 
        //Need a better way
        $d = dir($dir);
        while (false !== ($f = $d->read())){
            if(preg_match('/thumb_'.$p_uuid.'(.*)/',$f,&$matches)){
                $filename = $dir.trim($f);
                $ext = $matches[1];
                break; 
            }
        }
        $filename = trim($filename);
    
	    //if image is not available 
	    if(! file_exists($global['approot']."www/tmp/ori_$p_uuid"."$ext") ){
	        echo _t("Image Not Available");
	        return false;
	    }
	        
	
	    $info = getimagesize($global['approot']."www/tmp/ori_$p_uuid"."$ext");
	    $height = $info[1]+20;
	    $width = $info[0]+20;
	 
	    $url = $_SERVER["SERVER_NAME"].$_SERVER["PHP_SELF"];
	    //remove the index.php
	    $url = substr($url,0,strlen($url)-9);
	    //add http://
	    $src_ori = 'http://'.$url."/tmp/ori_$p_uuid"."$ext";
        $src_tmp = "tmp/thumb_$p_uuid"."$ext";
    }
?>
    <a title="<?php echo  _t('Click to see the original size'); ?>" href="#" onclick="window.open('<?php echo $src_ori;?>','hello','width=<?php echo $width?>,height=<?php echo $height?>,scrollbars=no,status=no');return false;" >
    <img border="0" src="<?php echo $src_tmp;?>" />
    </a>
<?php
    return true;
}

function _shn_vol_display_incident_form($error=false,$act)
{
    global $global;
    global $conf;
    $db=$global['db'];
?>
<h2><?php echo _t("Select the Disaster/event/incident")?> </h2>
<div id="note">
<?php echo _t("Since there are multiple incidents you required to select relevant incidents ");?>
</div>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
    shn_form_fopen($act);
    shn_form_fsopen('Choose related incidents');
    _shn_vol_display_incident(false,true);
    shn_form_fsclose();
    shn_form_hidden(array('incident'=>"true"));
    ?>
<br />
<center>
<?php
//create the submit button
   shn_form_submit(_t("Next"));
?>
</center>
<br />
<?php
        //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
} 

function _shn_vol_display_incident($error=false,$multi=false,$value=NULL)
{
    global $global;
    $db=$global["db"];
    if($value!=NULL){
        $extra_opts['value']=$value;
       // $extra_opts['req']=false;
    }else{
      //  $extra_opts['req']=true;
    }
    $extra_opts['req']=true;
    if($multi){
        $select_opts="multiple='true'";
    }else{
        //$select_opts="multiple='false'";;
    }
    $q = "select incident_id,name from incident";
    
    $res_options=$db->Execute($q) ; 
    //$options['-1']="ALL incidents";
    while(!$res_options->EOF){
    		$options[$res_options->fields["incident_id"]]=$res_options->fields["name"];
         //add all the locations e.g $options['sl'=>'sri lanka']
        $res_options->MoveNext();
    }
    if(!empty($value)){
    		$extra_opts['value']=$value;	
    }
    $extra_opts['help']=_t("select related incidents");
    shn_form_multi_select('incidents',$options,'',$select_opts,$extra_opts);
}

function _shn_vol_check_vol_reg_info_complete()
{

    include_once "errors.inc";
    global $global;
	include_once $global['approot']."/inc/lib_validate.inc";
	$error=false;
    $VARCHAR=100; 
	list($error,$_SESSION['vol']['name'])=(shn_validate_field($_POST{"name"},"Volunteer Name",$VARCHAR,true))?array($error,$_POST{"name"}):array(true,NULL);
    if (!shn_valid_date($_POST{"dob"})){
        $error=true;
    }else {    
        $_SESSION['vol']['dob']=$_POST{"dob"};	
    }
    $_SESSION['vol']['job']=$_POST{"job"};
    $_SESSION['vol']['nic']=trim($_POST{"nic"});
    $_SESSION['vol']['pas']=trim($_POST{"pas"});
    $_SESSION['vol']['dln']=trim($_POST{"dln"});
    
    list($error,$_SESSION['vol']['gender'])=(shn_validate_opt_field('opt_gender',$_POST{"opt_gender"},"Gender",$VARCHAR,false))?array($error,$_POST{"opt_gender"}):array(true,NULL);
    list($error,$_SESSION['vol']['skills'])=(shn_validate_opt_field('opt_skill_type',$_POST{"opt_skill_type"},"Skills",$VARCHAR,true))?array($error,$_POST{"opt_skill_type"}):array(true,NULL);
    list($error,$_SESSION['vol']['sector'])=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    $loc=shn_location_get_form_submit_loc();
    if ($loc==-1){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else{
    		$_SESSION['vol']['loc']=$loc;
    }
    $_SESSION['vol']['contact_address']=$_POST{"contact_add"};
    if (trim(strlen($_POST{"contact_phone"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['vol']['contact_phone']=$_POST{"contact_phone"};
    }
     if (trim(strlen($_POST{"contact_mobile"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['vol']['contact_mobile']=$_POST{"contact_mobile"};
    }
    if (trim(strlen($_POST{"contact_fax"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
         $_SESSION['vol']['contact_fax']=$_POST{"contact_fax"};
    }
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        
        if(!shn_valid_email($_POST{"contact_mail"})){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }else{
        		$_SESSION['vol']['contact_mail']=$_POST{"contact_mail"};
        }
    }
    if (trim(strlen($_POST{"contact_web"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['vol']['contact_web']=$_POST{"contact_web"};
    }
 
    return $error;
}


