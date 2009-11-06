<?php
/**
 *
 * This is the location library. A vital component of the framework.
 * locations are used by several modules like organization regsitry,Camp registry 
 * This library has nearly everything you need to do with locations.
 * 
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage location
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @author     Greg Miernicki <g@miernicki.com><miernickig@mail.nih.gov>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */


global $global;
//include_once $global['approot']."/inc/handler_form.inc";
define ("UNKNOWN","unknown");
/**
 * Returns the $_POST location. In the form the user may have entered village
 * some times he may not select a village ,but a district. Therefore
 * this function will start from lowest level and find the first instance
 * with a location set and return that location id.
 * of course if the user has ticked the unknown check box UNKNOWN will be 
 * returned and neither of these cases -1 will be returned to indicate
 * the user has not completed the location section
 *  
 * 
 * @param mixed $child 
 * @access public
 * @return location uuid
 */
function shn_location_get_form_submit_loc() {
	if(isset($_POST["loc_unknown"])){//unknow checkbox is ticked
		return UNKNOWN;
	}
	$n_lvl=$_POST["levels"];//the hidden $_POST variable which indicates the max no of levels
	
	while($n_lvl>0){
		$lvl="loc_select_".$n_lvl;
		if((isset($_POST["$lvl"]))&&($_POST["$lvl"]!="0")){
			return $_POST["$lvl"];//as soon as you find a selected location return
		}
		$n_lvl--;
	}
	return -1;
}



/**
 * Returns the level description having the given level code.
 *
 * @param Integer $level_code
 */
function shn_get_level_description($level_code){
	$range = shn_get_range();
	if($level_code>=0){
		if($level_code>=$range['start'] && $level_code<=$range['end']){
			global $global;
			$db=$global["db"];
			$q = "SELECT option_description FROM field_options WHERE field_name='opt_location_type' AND option_code=".$level_code;
			$res=$db->Execute($q);
			return $res->fields[0];
		}else{
			return "INVALID LEVEL CODE";
		}
	}
}



/**
 * Returns true if the location does not have any children 
 * 
 * @param mixed $loc 
 * @access public
 * @return void
 */
function shn_location_is_leaf($loc) {
	global $global;
	$db=$global["db"];
	$q="select loc_uuid from location where parent_id='{$loc}'";
	
	$res=$db->Execute($q);
	if(!$res==NULL && !$res->EOF){
		return false;
	}else{
		return true;
	}
}



/**
 * return the location name (Sri Lanka -> Western -> Colombo )
 *
 * @param unknown_type $loc_id
 * @return unknown
 */
function shn_location_string($loc) {
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
			$q="SELECT name FROM location WHERE loc_uuid='{$x}'";
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



/**
 * Returns an array of descendants of a location 
 * 
 * @param mixed $loc 
 * @access public
 * @return void
 */
function shn_location_get_descendants($loc,&$loc_arr) {
	global $global;
	$db=$global["db"];
	$q="select loc_uuid from location where parent_id='{$loc}'";
	$res=$db->Execute($q);
	while((!$res==NULL) && (!$res->EOF)){
		array_push($loc_arr,$res->fields["loc_uuid"]);//add this location
		shn_location_get_descendants($res->fields["loc_uuid"],$loc_arr);
		$res->MoveNext();
		//may be this location is not a leaf ,so call the same function again
	}
	return  $loc_arr; //well we reached the leaf ,return with all the parents up to this leaf
}



/**
 * Displays the full range of location levels for the user to select a subrange
 * 
 * @param mixed $loc 
 * @access public
 * @return void
 */
function shn_location_level_range_form($name,$label,$sel) {
	global $global;
	$db=$global["db"];
	$q = "select option_code,option_description from field_options where field_name='opt_location_type' order by option_code";
	$res=$db->Execute($q);
	$options=array();
	while(!$res==NULL && !$res->EOF){
		$options[$res->fields[0]]=$res->fields[0]."---".$res->fields[1];
		$res->MoveNext();
	}
	$extra_opts['value']=$sel;
	$extra_opts['req']=true;
	shn_form_fsopen($label);
	shn_form_select($options,$label, $name,$select_opts = "", $extra_opts);
	shn_form_fsclose();
}



/**
 * ?
 * 
 * @access public
 * @return ?
 */
function shn_location_get_x_uuid_loc_range() {
	global $global;
	global $conf;
	$db=$global['db'];
	$loc=array();
	$q="select value from config where module_id='or' and confkey='loc_range_start'";
	$res=$db->Execute($q);
	if($res->fields[0]==NULL){
		$loc["start"]=$conf['mod_or_loc_level_start'];
	}else {
		$loc["start"]=$res->fields[0];
	}
	$q="select value from config where module_id='or' and confkey='loc_range_end'";
	$res=$db->Execute($q);
	if($res->fields[0]==NULL){
		$loc["end"]=$conf['mod_or_loc_level_end'];
	}else {
		$loc["end"]=$res->fields[0];
	}
	return $loc;
}



/**
 * Returns the list of parents of the location. Starting from the location to
 * the parent,grand parent,ect. For each
 * level the name and location id is returned. 
 * 
 * @param mixed $child 
 * @access public
 * @return array
 */
function shn_get_parents($child,&$loc_arr) {
	global $global;
	include_once $global['approot']."/inc/lib_validate.inc";
		
	if(shn_is_null($child)){
			return $loc_arr;
	}
	
	$db=$global['db'];
		$q="select parent_id from location where loc_uuid='{$child}'";
	$res_temp=$db->Execute($q);
	array_push(
			$loc_arr,
		$child
	);
	shn_get_parents($res_temp->fields['parent_id'],$loc_arr);
		
	
	/*
	$q="select search_id,name,loc_uuid from location where loc_uuid=$child";
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
		$q="select name,loc_uuid from location where search_id='$cur'";
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
	*/
}



/**
 * Returns the level of the location 
 * 
 * @param mixed $loc 
 * @access public
 * @return mixed
 */
function shn_get_level($loc){
	global $global;
	$db=$global['db'];
	$q="select option_code from field_options,location where field_options.option_code =location.opt_location_type and location.loc_uuid='{$loc}' and field_name='opt_location_type'";
	$res=$db->Execute($q);
	return $res->fields[0];
}



/**
 * Returns whether the location is in the last level or not 
 * 
 * @param mixed $loc 
 * @access public
 * @return bool
 */
function shn_is_last_level($loc){
	global $global;
	$db=$global['db'];
	$q="select option_code from field_options where field_name='opt_location_type' order by option_code desc";
	$res=$db->Execute($q);
	$last=$res->fields[0];
	$q="select option_code from field_options,location where field_options.option_code =location.opt_location_type and location.loc_uuid='{$loc}' and field_name='opt_location_type'";
	$res=$db->Execute($q);
	echo $q;
	if($last==$res->fields[0]){
		return true;
	}else {
		return false;
	}
}



/**
 * Returns the last location level avaliable 
 * @param mixed $loc
 * @access public
 * @return void
 */
function shn_get_last_level(){
	global $global;
	$db=$global['db'];
	$q="select option_code,option_description from field_options where field_name='opt_location_type' order by option_code desc";
	$res=$db->Execute($q);
	if(($res==NULL)or($res->EOF==true)){
		$last=0;
	}
	$last=array();
	$last[0]=$res->fields[0];
	$last[1]=$res->fields[1];
	return $last;
}



/**
 * Returns the range of levels avaliable 
 * @param mixed $loc
 * @access public
 * @return void
 */
function shn_get_range(){
	global $global;
	$db=$global['db'];
	$q="select option_code,option_description from field_options where field_name='opt_location_type' order by option_code asc";
	$res=$db->Execute($q);
	$range["start"]=$res->fields[0];
	$q="select option_code,option_description from field_options where field_name='opt_location_type' order by option_code desc";
	$res=$db->Execute($q);
	$range["end"]=$res->fields[0];
	return $range;
}



/**
 * Generates the java script required for AJAX functionality 
 * 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_location_jscript($start,$to,$parent=false){
	global $global;
	$fetch_server="index.php?";
	?>           
	<script type="text/javascript">
	var url = "<?php echo $fetch_server?>"; 
	var curlevel=0;
	var http;
	var to=<?php echo $to ?>;
	var start = <?php echo $start;?>;
	<?php if($parent){
			echo "var parent=true;";    
		}else{
			echo "var parent=false;"; 
		}
		?>
		var previous="nothing";
	function getHTTPObject() {
		var xmlhttp;
		//conditional compliation
		/*@cc_on
		@if (@_jscript_version >= 5)
		try {
			xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
		} catch (e) {
			try {
			xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
			} catch (E) {
			xmlhttp = false;
			}
		}
		@else
		xmlhttp = false;
		@end @*/

		if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
		try {
			xmlhttp = new XMLHttpRequest();
		} catch (e) {
		xmlhttp = false;
		}
		}
	return xmlhttp;
	}

	// The callback funtion
	function handleHttpResponse(){
		if (http.readyState == 4) { // Split the comma delimited response into an array  
			results = http.responseText.split(","); 
				curlevel=curlevel+1;
				var dropdown="loc_select_"+curlevel;
			var x=document.getElementById(dropdown);
			opt = document.createElement("option") ;
				opt.value = "" ;
				opt.text = "";
			if(x.options==null){
				j=0;
			}else{
	
				for (i=0; i<=x.options.length+1; i++){
				x.options[0]=null;
			}
			x.options[0] = opt;
			j=1;
			}
	
		var next=results[1];
		

		for (i=1; i<results.length-1; i=i+2, j++){
				opt = document.createElement("option") ;
				opt.value = results[i] ;
				opt.text = results[i+1].replace(/[^A-Za-z0-9]$/,"");
				x.options[j] = opt;
				
		
		//
		}
		x.selectedIndex=-1;
		if(curlevel<to){
			update_next_level(next,curlevel);
		}
		} 
	}
	
		// The callback funtion for locations related to organizations,camps
		// The callback funtion
	function handleHttpResponseComplex(){
			var selection=0;
		if (http.readyState == 4) { // Split the comma delimited response into an array
	
		var all_arr=http.responseText.split(";"); 
		var header=all_arr[0];
				if(header){
			header_arr = header.split(","); 
			type=header_arr[0];
			next=header_arr[1];
			cur_lvl=header_arr[2];
			selection=header_arr[3]*1+1;//multiplication required to convert to number
		
					//alert(all_arr);
			var data=all_arr[1];
			if(data){
				results = data.split(",");
				
						var dropdown="loc_select_"+cur_lvl;
					var x=document.getElementById(dropdown);

				opt = document.createElement("option") ;
						opt.value = "" ;
						opt.text = "";
				x.options[0] = opt;
				

				for (i=0; i<results.length;i++){
						opt = document.createElement("option") ;

						var option_data=results[i].split(":");
						opt.value = option_data[0] ;
						opt.text = option_data[1].replace(/[^A-Za-z]$/,"");
					x.options[x.options.length] = opt;//i+1
		
				}
				x.selectedIndex=selection;
			
				if(cur_lvl>0){
						update_location(next,type);
				}
			}
			} 
		}
	}

	function update_next_level(selection,level){
		curlevel=level;
		http = getHTTPObject();
		var url2=url + "act=get_loc&mod=xst&stream=text&lvl="+curlevel+"&sel="+selection;
		
		http.open("GET", url2, true); 
	//        http.onreadystatechange = null; 
		http.onreadystatechange = function(){}; 
		http.onreadystatechange = handleHttpResponse; 
		http.send(null);
	}
	
	function update_location(selection,type){
		
		if(type!='loc_dir'){
				for(j=1;j<=to;j++){
					
					var dropdown="loc_select_"+j;
					var x=document.getElementById(dropdown);
					
				for (i=0; i<=x.options.length+1; i++){
					x.options[0]=null;
				}
			}
		}
		http = getHTTPObject();
		var url2=url + "act=get_loc_val&mod=xst&stream=text&type="+type+"&sel="+selection;
		http.open("GET", url2, true); 
		http.onreadystatechange = function(){}; 
		http.onreadystatechange = handleHttpResponseComplex; 
		http.send(null);
	}
	
		
		
		
		function radio_click(div){
			
			if(div=='loc_dir'){
				for(i=start;i<=to;i++){
						var x=document.getElementsByName(i);
						//x[0].selectedIndex=-1;
						var y=document.getElementById(i);
					
						y.style.display='block';
				}


			}else{
				var y=document.getElementById(div);
				
				y.style.display='block';
			}
			
			
			
			if(previous=='loc_dir'){

				for(i=start;i<=to;i++){
						var x=document.getElementsByName(i);
						//x[0].selectedIndex=-1;
						var y=document.getElementById(i);
						
						y.style.display='none';
				}
			}else{
				if(previous!="nothing"){
					var y=document.getElementById(previous);
					
					y.style.display='none';
				}
			}
			previous=div;
			return;
	}
	if(parent==true){
	
				for(i=1;i<=to;i++){
			//	alert("start"+start);
					if(i<=start){
						var x=document.getElementsByName(i);
						//x[0].selectedIndex=-1;
					}
				}
			//var y=document.getElementById(i);
			//y.style.display='none';
			
		}else{
	
		for(i=start;i<=to;i++){
			var x=document.getElementsByName(i);
			//x[0].selectedIndex=-1;
			//var y=document.getElementById(i);
			//y.style.display='none';
			
			}
		}
		var y=document.getElementById("loc_org");
		if(y)
		y.style.display='none';
		
		var y=document.getElementById("loc_camp");
		if(y)
		y.style.display='none';
		
	</script>
	<?php
}



/**
 * ?
 * 
 * @access public
 * @return void
 */
function shn_location_init_jscript($start,$end) {
	?>
	<script type="text/javascript">
	var start = <?php echo $start;?>;
	var end = <?php echo $end;?>;
		for(i=start;i<=end;i++){
			var x=document.getElementsByName(i);
			x[0].selectedIndex=-1;
			var y=document.getElementById(i);
			y.style.visibility='hidden';
		}
		var y=document.getElementById("loc_org");
		y.style.visibility='hidden';
		var y=document.getElementById("loc_camp");
		y.style.visibility='hidden';
	</script>
	<?php
}



/**
 * shn_location 
 * Generates a set of select boxes with locations with in the given levels. Will add to the form. 
 * @param mixed $from 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_location($range,$value=null,$parent=null,$extra_opts=null){
	if($extra_opts['req']==true){
		shn_form_label(null,"Please Select a location", array("req"=>true));
		?> <br /> <?
	}
	// if a location is selected in post values use it, if the value is not given 
	// this will set the location as it is when a submision fails of a form.
	$value=(isset($value))?$value:shn_location_get_form_submit_loc();
			
	if($range == null){
		$range = shn_location_get_loc_range();	
	}
	
	if($parent == null){
		$parent = shn_location_get_start_loc();
	}
	
	$count=0;
	$keepparent=false;
	$info=_t("If you know any of the following, please select only one of them first" .
			" , the selection will populate the set of Location select boxes ")."<br />";
	if($extra_opts["camps"]==true){
		 $info.=_t("* Camp/Shelter ")."<br /> ";
		 $count=$count+1;
	}
	if($extra_opts["inv"]==true){
		 $info.=_t("* an Inventory ")."<br /> ";
		 $count=$count+1;
	}
	if($extra_opts["org"]==true){
		 $info.=_t("* an Organization ")."<br /> ";
		 $count=$count+1;
	}
	if(($extra_opts["camps"]==true)or ($extra_opts["inv"]==true) or ($extra_opts["org"]==true)){
		//$info.=_t("a Location ");
		?><div class="info"><?php echo $info;?></div><br /><?php
	}
	if($extra_opts["camps"]==true){
		if($count>=1){
			$options=array("loc_camp"=>"Select a Camp/Shelter");
			$select_opts='onclick=radio_click("loc_camp")';
			shn_form_radio($options,null, "loc",$select_opts);
		}
		$camps=_shn_location_camp_list();
		$options=array();
		$options[0]="";
		foreach ($camps as $id => $name){
			$options[$id]=$name;
		}
		if($extra_opts["camp_id"]!=null){
			$q="select location_id from camp_general where c_uuid='".$extra_opts["camp_id"]."'";
			global $global;
			$db=$global["db"];
			$res=$db->Execute($q);
				if(($res==NULL) || ($res->EOF)){
					$value=UNKNOWN;
				}else{
					$value=$res->fields["location_id"];
				}
			$extra_opts["value"]=$extra_opts["camp_id"];
		}
		?><div id='loc_camp'><?php
		$select_opts='onChange=update_location(this.options[this.selectedIndex].value,"camp")';
		shn_form_select($options,_t('Shelter/Camp'),'camps',$select_opts,$extra_opts);
		?> </div> <?php
	}
	if($extra_opts["org"]==true){
		global $global;
		include_once $global['approot']."/mod/or/api.inc";
		$orgs=shn_or_organization_list();
		if($count>=1){
			$options=array("loc_org"=>_t("Select an Organization"));
			$select_opts='onChange=radio_click("loc_org")';
			shn_form_radio($options,null, "loc",$select_opts);
//			$options=array("loc_org"=>_t("Select an Organization"));
//			$select_opts='onclick=radio_click("loc_org")';
//			shn_form_radio($options,null,"loc",$select_opts);
		}
		$options=array();
		$options[0]="";
		if($orgs!=null){
			foreach($orgs as $org=>$org_details){
				$options[$org_details["id"]]=$org_details["name"];
			}
		}
		?><div id='loc_org'><?php
		$select_opts='onChange=update_location(this.options[this.selectedIndex].value,"poc")';
		shn_form_select($options,_t('Organizations'),'orgs',$select_opts,$extra_opts);
		?></div><?php
	}
	shn_form_hidden(array('levels'=>$range['end']));
	$start='1';
	if (($value!=NULL) && ($value!=UNKNOWN)){
		_shn_location_form_value($range,$value);
		$start=shn_get_level($value)+1;
	} else {
		if($parent==null){
			_shn_location_form($range);
			//$start='1';	
		} else {
			_shn_location_form_parent($range,$parent);
			$keepparent=true;
		}  
	}
	shn_location_jscript($start,$range["end"],$keepparent);
}



/**
 * shn_location_mpr
 * Generates a set of select boxes with locations for MPR module given POST data.
 * @param mixed $from 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_location_mpr() {
	global $conf;
	$i = $conf['mod_mpr_location_lower_limit'];
	while ((!isset($_POST[$i])) && $i > $conf['mod_mpr_location_upper_limit']) {
		$i--;
	}
	$range['start'] = $conf['mod_mpr_location_upper_limit'];
	$range['end']   = $conf['mod_mpr_location_lower_limit'];
	shn_location($range, $_POST[$i], null, array('sort'=>'display_order, field_name ASC', 'select'=>'true'));
}



/**
 * Retrieves a list of camps 
 * 
 * @access private
 * @return void
 */
function _shn_location_camp_list(){
	global $global;
	$db=$global['db'];
	$q="select c_uuid,name from camp_general";
	$res=$db->Execute($q);
	$camps=array();
	while (!$res==NULL && !$res->EOF) {
		$camps[$res->fields["c_uuid"]]=$res->fields["name"];
		$res->MoveNext();
	}
	return  $camps;
}



/**
 * Adds a location to the database.Retrives the values to insert from the POST variables. 
 * 
 * @access public
 * @return void
 */
function shn_location_add() {
	if($_POST{"loc_name"}==null){
		$msg= " You cant add a NULL(empty) value for location ";
		add_error($msg);
		return;
	}
	global $global;
	include_once($global['approot']."/inc/lib_uuid.inc");
	$db=$global['db'];
	if('yes'!=$_POST['loc_sub_ans']) {
		$q="SELECT name FROM location";
		$res = $global['db']->Execute($q);
		_shn_location_validate_name();
		while(!$res->EOF){
			if($_POST{"loc_name"}==$res->fields['name']){
				add_warning(_("This location name is already in the database. Do you want to add anyway?  &nbsp&nbsp&nbsp<b><a href='#' onclick='_shn_loc_val_name();'>Add anyway</a></b> or else you can change the \"Location Name\" textbox and submit the form again."));
				return;
			}
			$res->MoveNext();
		}
	}
	$insert_array['name']=$_POST{"loc_name"};
	$insert_array['description']=$_POST{"desc"};
	$insert_array['iso_code']=$_POST{"iso"};
	$loc=shn_location_get_form_submit_loc();
	if($loc==-1) {
		$loc=null;
		$lvl=1;
	} else {
		$lvl=shn_get_level($loc)+1;
	}
	$insert_array['opt_location_type']=$lvl;
	$insert_array['loc_uuid']= shn_create_uuid('location');
	$insert_array['parent_id']=$loc;
	shn_db_insert($insert_array,'location', false, 'loc_uuid');
	
	$q="select * from field_options where field_name='opt_location_type' and option_code='$lvl'";
	$res = $global['db']->Execute($q);
	if((!$res==NULL) && (!$res->EOF)) {
		$loc_lvl_name= $res->fields["option_description"];
	}
	$msg= $_POST{"loc_name"}." Location was succesfully added as a ".$loc_lvl_name;
	add_confirmation($msg);
}



/**
 * Batch adds locations to the database. Retrives the values to insert from the POST variables / uploaded .csv file. 
 * 
 * @access public
 * @return void
 */
function shn_location_addb() {
	global $global;
	$db = $global['db'];
	include_once($global['approot']."/inc/lib_uuid.inc");
	$count = 0; // imported record count

	// No file was uploaded ignore
	if($_FILES['batchfile']['error']==UPLOAD_ERR_NO_FILE) {
		add_error("No file was uploaded!");
	} else {
		$row = 1;
		$handle = fopen($_FILES['batchfile']['tmp_name'],"r");
		$parent = $_POST['loc_select_1b'];
		$dupe = $_POST['dupe'];
		$lines = 0;
		while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
			$num = count($data);
			if ( $num == 3 ) {
				$name = $data[0];
				$description = $data[1];
				$iso = $data[2];
				if ( $name == "" || $iso == "" ) {
					add_error("Line #".$lines." has an empty name or iso code, thus was not imported."); 
				} else {
					// determine if there are any duplicates of the current item we are inserting
					// "rename" 	=> Rename imported duplicate Location
					// "overwrite" 	=> Overwrite with imported Location
					// "drop" 	=> Drop duplicate, keep original Location
					$doInsert = true;
					$q = "select * from location where name='".$name."';";
					$res = $global['db']->Execute($q);

					// if duplicate found
					if ($row = $res->FetchRow()){
						// rename = rename new value then insert it
						if ($dupe == "rename") {
							$nameOld = $name;
							$name .= "[".rand(0,99)."]";
							add_warning("Duplicate value: <b>".$nameOld."</b> renamed to <b>".$name."</b> before being imported.");

						// overwrite = delete old then insert new
						} elseif ($dupe == "overwrite") {
							$q2 = "DELETE FROM location WHERE loc_uuid = '".$row['loc_uuid']."';";
							$res2 = $global['db']->Execute($q2);
							add_warning("Duplicate value: <b>".$name."</b> deleted and replaced with new location by the same name.");
							
						// drop = do nothing, forget the insert
						} elseif ($dupe == "drop") {
							// nothing, value is dropped!
							add_warning("Duplicate value: <b>".$name."</b> not added.");
							$doInsert = false;
						}
					}
					if ($doInsert) {
						$uuid = shn_create_uuid('location');
						$q = "INSERT INTO location (name, description, iso_code, opt_location_type, loc_uuid, parent_id) VALUES ( '".$name."', '".$description."', '".$iso."', ";
						if ($parent != '0') {
							$q .= "'2', '".$uuid."', '".$parent."');";
						} else {
							$q .= "'1', '".$uuid."', NULL);";
						}
						$res = $global['db']->Execute($q);
						$count++;
					}
				}
			} else {
				add_error("Line #".$lines." had the incorrect number of fields, thus was not imported."); 
			}
			$lines++;
		}
		fclose($handle);
	}
	if ($count > 0) {
		add_confirmation("<b>".$count."</b> values imported.");
	}
}



/**
 * Deletes a location from the database.
 * 
 * @access public
 * @return void
 */
function shn_location_del($loc) {
	global $global;
	$db=$global['db'];
	$loc_str=array();
	$loc_str=shn_location_get_descendants($loc,$loc_str);
	$loc_arr=split(",",$loc_str);
	$q="delete from location where loc_uuid='{$loc}'";
	$db->Execute($q);
	foreach( $loc_arr as $val){
		$q="delete from location where loc_uuid='{$val}'";
		$db->Execute($q);
	}
	$msg= "Location was succesfully deleted";
	add_confirmation($msg);
}



/**
 * Edits a Location?
 * 
 * @access public
 * @return void
 */
function shn_location_edit($loc) {
	global $global;
	$db=$global['db'];
	$loc_id=$loc{"loc"};
	$name=$loc{"name"};
	$desc=$loc{"desc"};
	$iso=$loc{"iso"};
	$q="update location set name='{$name}',description='{$desc}',iso_code='{$iso}' where loc_uuid='{$loc_id}'";
	$db->Execute($q);
	$msg= $name." Location was succesfully updated ";
	add_confirmation($msg);
	
}



/**
 * ?
 * 
 * @access public
 * @return void
 */
function _shn_location_form_parent($range,$parent){   
	global $global;
	$db=$global['db'];
	$value=$parent;
	// $loc=array();
	$loc_arr=array();
	if($value!=NULL){
		shn_get_parents($value,$loc_arr);
		//parents in the order child,parent,grand parent,..etc
	}
	
	$parent_level=shn_get_level($parent);
	$from=$range["start"];
	$to=$range["end"];
	$cur=$from;
	while($cur<=$parent_level) {
		$q = "select option_code,option_description from field_options where field_name='opt_location_type' and option_code=".$cur;
		$res=$db->Execute($q);
		while(!$res==NULL && !$res->EOF){
			if($cur==$from) {
				$q = "select location.name,location.loc_uuid from location where location.opt_location_type=".$res->fields[0]." order by location.name";
				$extra_opts['help']=_t("Select the location based at.  This is hierarchical. For example think you are based  in the country 'Sri lanka' ,district 'Colombo' ,and village 'dehiwala'.  start by selecting the country ,once you select country all the divisions of that country will populate the next select box.  therefore in this case all the districts in 'Sri lanka' appear . From those select a district which will populate the village list in the next select box. So select 'dehiwala' and you have done it! please note that the levels can be customized, therefore it does not need to be ''->'district'->'village' ,always. Its configurable from the 'administration' section.");//display help icon only once
			} else {
				$q = "select location.name,location.loc_uuid from location where location.opt_location_type=".$res->fields[0]." and parent_id='".$selection."'";
			}
			$res_options=$db->Execute($q);
			$options=array();
			if(!$res_options->EOF){
				$selection=array_pop($loc_arr);
			}
			$options[0]="";
			while(!$res_options->EOF){
				$options[$res_options->fields["loc_uuid"]]=$res_options->fields['name'];
				$res_options->MoveNext();
			}
			$select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')';
			$extra_opts['value']=$selection;
			//   $extra_opts['req']=true;
			shn_form_select($options,_lc($res->fields[1]).":","loc_select_".$res->fields[0],$select_opts,$extra_opts);
			$res->MoveNext();
		}
		$cur=$cur+1;
	}
	$from=$parent_level;
	$cur=$from[0]+1;
	$selection=$parent;
	while($cur<=$to){
		$q = "select option_code,option_description from field_options where field_name='opt_location_type' and option_code=".$cur;
		$res=$db->Execute($q);
		while(!$res==NULL && !$res->EOF){
			$q = "select location.name,location.loc_uuid from location where location.opt_location_type=".$res->fields[0]." and parent_id='".$selection."'";
			$res_options=$db->Execute($q);
			$options=array();
			if(!$res_options->EOF){
				$selection=$res_options->fields[1];
			}
			while(!$res_options->EOF){
				$options[$res_options->fields[1]]=$res_options->fields[0];
				$res_options->MoveNext();
			}
			?><div id='loc_div_<?php echo $res->fields[0];?>'><?php
			$select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')';
			shn_form_select($options,_lc($res->fields[1]).":","loc_select_".$res->fields[0],$select_opts,array('req'=>true));
			?></div><?php
			$res->MoveNext();
		}
		$cur=$cur+1;
	}
}



/**
 * _shn_location_form_value 
 * 
 * @param mixed $range
 * @param mixed $value 
 * @access protected
 * @return void
 */
function _shn_location_form_value($range,$value) {
	/*assume the location is d ,and its parents are
	a,b,c,d.
	first of all we need to obtain the parents  
	for that use shn_get_parents
	then starting from the great ancesstor we display
	the drop down boxes. 
	that is we popluate a drop down box with all the children
	of a and select b.
	like wise we continue unitll we populate all the children
	of c and select d
	*/
	global $global;
	$db=$global['db'];
	$from=$range["start"];//starting level
	$to=$range["end"];//ending level
	$loc_arr=array();
	if($value!=NULL){
		shn_get_parents($value,$loc_arr);
		//parents in the order child,parent,grand parent,..etc
	}
	array_pop($loc_arr);
	$cur=$from;//start from the starting level
	while($cur<=$to){
		$q = "select option_code,option_description from field_options where field_name='opt_location_type' and option_code=".$cur;
		$res=$db->Execute($q);
		while(!$res==NULL && !$res->EOF){
			if($cur==$from){
				//at this instance there is no parent
				$q = "select location.name,location.loc_uuid from location where location.opt_location_type=".$res->fields[0]." order by location.name";
				$extra_opts['help']=_t("Select the location based at.  This is hierarchical. For example think you are based  in the  'Sri lanka' ,district 'Colombo' ,and village 'dehiwala'.  start by selecting the  ,once you select all the divisions of that country will populate the next select box.  therefore in this case all the districts in 'Sri lanka' appear . From those select a district which will populate the village list in the next select box. So select 'dehiwala' and you have done it! please note that the levels can be customized, therefore it does not need to be 'country'->'district'->'village' ,always. Its configurable from the 'administration' section.");//display help icon only once
			} else {
				//now there is a parent, so select all the children
				$q = "select location.name,location.loc_uuid from location where location.opt_location_type=".$res->fields[0]." and parent_id='".$selection."'";
				unset($extra_opts['help']);
			}
			$res_options=$db->Execute($q);
			
			//$res_options contains all the children,but we want to select one of a,b,c
			$options=array();
			if(!$res_options->EOF){
				//returns and removes the last one ,i.e remaining great ancesstor
				$selection=array_pop($loc_arr);
			}
			$options[0]="";
			while(!$res_options->EOF){
				$options[$res_options->fields[1]]=$res_options->fields[0];
				//add all the locations e.g $options['sl'=>'sri lanka']
				$res_options->MoveNext();
			}
			
			$select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')';
			$extra_opts['value']=$selection;
		
			//which one to diplay out of all the locations.
			//should be one of the parents
			// $extra_opts['req']=true;
			?><div id='loc_div_<?php echo $res->fields[0];?>'><?php
			shn_form_select($options,_lc($res->fields[1]).":","loc_select_".$res->fields[0],$select_opts,$extra_opts);
			?></div><?php
			$res->MoveNext();
		}
		$cur=$cur+1;
	}
}



/**
 * _shn_location_form 
 * 
 * @param mixed $from 
 * @param mixed $to 
 * @access protected
 * @return void
 */
function _shn_location_form($range) {   
	global $global;
	$db=$global['db'];
	$loc=array();
	$from=$range["start"];
	$to=$range["end"]; 
	$cur=$from;
	while($cur<=$to) {
		$q = "select option_code,option_description from field_options where field_name='opt_location_type' and option_code=".$cur;
		$res=$db->Execute($q);
		while(!$res==NULL && !$res->EOF) {
			$extra_opts=array();
			//$extra_opts['req']=true;
			if($cur==$from){
				$q = "select location.name,location.loc_uuid from location where location.opt_location_type=".$res->fields[0]." order by location.name";
				$extra_opts['help']=_t("Select the location based at.  This is hierarchical. For example think you are based  in the country 'Sri lanka' ,district 'Colombo' ,and village 'dehiwala'.  start by selecting the country ,once you select country all the divisions of that country will populate the next select box.  therefore in this case all the districts in 'Sri lanka' appear . From those select a district which will populate the village list in the next select box. So select 'dehiwala' and you have done it! please note that the levels can be customized, therefore it does not need to be 'country'->'district'->'village', always. Its configurable from the 'administration' section.");//display help icon only once
			} else {
				$q = "select location.name,location.loc_uuid from location where location.opt_location_type=".$res->fields[0]." and parent_id='".$selection."'";
			}
			$res_options=$db->Execute($q);
			if($res_options==null){ return;}
			$options=array();
			if(!$res_options->EOF){
				$selection=$res_options->fields[1];
			}
			$options[0]="";
			while(!$res_options->EOF){
				$options[$res_options->fields[1]]=$res_options->fields[0];
				$res_options->MoveNext();
			}
			?><div id='loc_div_<?php echo $res->fields[0];?>'><?php
			$select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')';
			shn_form_select($options,_lc($res->fields[1]).":","loc_select_".$res->fields[0],$select_opts,$extra_opts);
			?></div><?php
			$res->MoveNext();
		}
		$cur=$cur+1;
	}
}



/**
 * ?
 * 
 * @access public
 * @return void
 */
function shn_location_get_start_loc() {
	global $global;
	global $conf;
	$db=$global['db'];
	$q="select value from config where module_id='admin' and confkey='loc_start'";
	$res=$db->Execute($q);
	if($res==NULL) {
		return NULL;
	} else {
		return $res->fields["value"];
	}
}



/**
 * ?
 * 
 * @access public
 * @return void
 */
function shn_location_get_loc_range() {
	global $global;
	global $conf;
	$db=$global['db'];
	$loc=array();
	$q="select value from config where module_id='admin' and confkey='loc_range_start'";
	$res=$db->Execute($q);
	if($res->fields[0]==NULL){
		$loc["start"]=$conf['mod_admin_loc_level_start'];
	}else {
		$loc["start"]=$res->fields[0];
	}
	$q="select value from config where module_id='admin' and confkey='loc_range_end'";
	$res=$db->Execute($q);
	if($res->fields[0]==NULL){
		$loc["end"]=$conf['mod_admin_loc_level_end'];
	}else {
		$loc["end"]=$res->fields[0];
	}
	return $loc;
}



/**
 * minor function to validate duplicate location names
 * 
 * @access public
 * @return void
 */
function _shn_location_validate_name(){
	?><script>
	function _shn_loc_val_name(){
		document.getElementById('loc_sub_ans').value='yes';
		document.add_loc_cr_submit.submit();
	}
	</script><?php
}
