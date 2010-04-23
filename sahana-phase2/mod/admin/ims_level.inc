<?php

/**
 * _shn_ims_level1_form 
 * 
 * @param mixed $errors 
 * @param mixed $updated 
 * @access protected
 * @return void
 *
 * Level 1 Form
 */
function _shn_ims_level1_form($errors=false,$type=null) {
	global $global;
	global $conf;

	if ($errors) {
		display_errors();
	}

	$sql = "SELECT * FROM incident WHERE parent_id IS NULL";  
	$arr = $global['db']->GetAll($sql);
	if (!empty($arr)) {
		shn_form_fopen("ims_level1",null);
		if($type=='Updated' || $type=='Deleted') {
			shn_form_fsopen(_t(""));
			?><p align="center"><?php echo $type;?></p><?php
			shn_form_fsclose();
		}
		shn_form_hidden(array('seq'=>'update'));
		shn_form_fsopen(_t('Manage ')._lc($conf['mod_admin_ims_level1']));
		echo "\n<table class=\"smoothtable\">\n<thead>\n";
			echo "<td><strong>"._t('Name')."</strong></td>\n";
			echo "<td><strong>"._t('Short Name')."</strong></td>\n";
			echo "<td><strong>"._t('Date')."</strong></td>\n";
			echo "<td><strong>"._t('Type')."</strong></td>\n";
			echo "<td><strong>"._t('Latitude')."</strong></td>\n";
			echo "<td><strong>"._t('Longitude')."</strong></td>\n";
			echo "<td><strong>"._t('Delete')."</strong></td>\n";
		echo "</thead>\n";
		foreach($arr as $row) {
			echo "<tr>\n";
			echo "<td>";
				echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_name[".$row['incident_id']."]\" id=\"level1_name[".$row['incident_id']."]\" value=\"".$row['name']."\" /><span class=\"req\">*</span>";
			echo "</td>\n";
			echo "<td>";
				echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_shortname[".$row['incident_id']."]\" id=\"level1_shortname[".$row['incident_id']."]\" value=\"".$row['shortname']."\" /><span class=\"req\">*</span>";
			echo "</td>\n";
			echo "<td>";
				echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_date[".$row['incident_id']."]\" id=\"level1_date[".$row['incident_id']."]\" value=\"".$row['date']."\" />";
			echo "</td>\n";
			echo "<td>";
				echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_type[".$row['incident_id']."]\" id=\"level1_type[".$row['incident_id']."]\" value=\"".$row['type']."\" />";
			echo "</td>\n";
			echo "<td>";
				echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_latitude[".$row['incident_id']."]\" id=\"level1_latitude[".$row['incident_id']."]\" value=\"".$row['latitude']."\" />";
			echo "</td>\n";
			echo "<td>";
				echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_longitude[".$row['incident_id']."]\" id=\"level1_longitude[".$row['incident_id']."]\" value=\"".$row['longitude']."\" />";
			echo "</td>\n";
			echo "<td>";
				echo "<input type=\"checkbox\" name=\"level1_delete[".$row['incident_id']."]\" />";
			echo "</td>\n";
			echo "</tr>\n\n";
		}
		?></table><?php
		shn_form_fsclose();
		shn_form_submit(_t('Update'));
		shn_form_fclose(); 
	}

	shn_form_fopen("ims_level1",null,array('req_message'=>false));
	if ($type=='added') {
		shn_form_fsopen(_t(""));
		?><p align="center"><?php echo $type;?></p><?php
		shn_form_fsclose();
	}
	echo "<br /><br /><br />";
	shn_form_hidden(array('seq'=>'addnew'));
	shn_form_fsopen(_t('Add New ')._lc($conf['mod_admin_ims_level1']));
		echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_name_new\"      id=\"level1_name_new\"      value=\"\" /> Name <span class=\"req\">*</span><br>";
		echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_shortname_new\" id=\"level1_shortname_new\" value=\"\" /> Short Name <span class=\"req\">*</span><br>";
		echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_date_new\"      id=\"level1_date_new\"      value=\"\" /> Date<br>";
		echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_type_new\"      id=\"level1_type_new\"      value=\"\" /> Type<br>";
		echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_latitude_new\"  id=\"level1_latitude_new\"  value=\"\" /> Latitude<br>";
		echo "<input class=\"smoothinput\" type=\"text\" name=\"level1_longitude_new\" id=\"level1_longitude_new\" value=\"\" /> Longitude<br>";
	shn_form_fsclose();
	shn_form_submit(_t('Add New'));
	shn_form_fclose(); 
}



/**
 * _shn_ims_config_validate 
 * 
 * @access protected
 * @return void
 * Level1 Validation
 */
function _shn_ims_level1_validate() {
	global $conf;
	global $global;
	$error_flag=false;

	//clean the post
	shn_tools_clean_post(&$local_post);
	
	//anything entered?
	if(empty($local_post)) {
		add_error(_t("You have not completed the form"));
		return false;
	}

	if (($local_post['seq']) == 'addnew') {
		if (!isset($local_post['level1_name_new'])) {
			add_error(sprintf(_t("Please enter a name for the %s"),strtolower($conf['mod_admin_ims_level1'])));
			add_warning(sprintf(_t('If there are no %1$ss please add a new %2$s'),strtolower($conf['mod_admin_ims_level1']),strtolower($conf['mod_admin_ims_level1'])));
			$error_flag=true;
		}
		if (!isset($local_post['level1_shortname_new'])) {
			add_error(sprintf(_t("Please enter a Short Name for the %s"),strtolower($conf['mod_admin_ims_level1'])));
			add_warning(sprintf(_t('If there are no %1$ss please add a new %2$s'),strtolower($conf['mod_admin_ims_level1']),strtolower($conf['mod_admin_ims_level1'])));
			$error_flag=true;
		}
	} else {
		$local_post['level1_name'] = null;
		foreach($_POST['level1_name'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level1_name'][$k] = $v;
			}
		}
		foreach($_POST['level1_shortname'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level1_shortname'][$k] = $v;
			}
		}
		foreach($_POST['level1_date'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level1_date'][$k] = $v;
			}
		}
		foreach($_POST['level1_type'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level1_type'][$k] = $v;
			}
		}
		foreach($_POST['level1_latitude'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level1_latitude'][$k] = $v;
			}
		}
		foreach($_POST['level1_longitude'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level1_longitude'][$k] = $v;
			}
		}
		if(isset($_POST['level1_delete'])) {
			$local_post['level1_delete'] = null;
			foreach($_POST['level1_delete'] as $k => $v) {
				$v = trim($v);
				$k = trim($k);
				if($v != '') {
					$local_post['level1_delete'][$k] = $v;
				}
			}
		}
	}
	if ($error_flag) {
		return false;
	} else{
		if (($local_post['seq']) == 'addnew') {
			$sql = "INSERT INTO incident (name, shortname, date, type, latitude, longitude) 
				VALUES 
				('{$local_post['level1_name_new']}', 
				'{$local_post['level1_shortname_new']}', 
				'{$local_post['level1_date_new']}', 
				'{$local_post['level1_type_new']}', 
				'{$local_post['level1_latitude_new']}', 
				'{$local_post['level1_longitude_new']}')";
			$global['db']->Execute($sql);
			$message = $local_post['level1_name_new']._t(" ").$conf['mod_admin_ims_level1']._t(" successfully added.");
		} else {
			//Update
			foreach($local_post['level1_name'] as $k => $v) {
				$sql = "UPDATE incident 
					SET name = '$v' WHERE incident_id = '$k'";
				$global['db']->Execute($sql);
				$message = $conf['mod_admin_ims_level1']._t(" successfully updated as ".$v);
			}
			foreach($local_post['level1_shortname'] as $k => $v) {
				$sql = "UPDATE incident 
					SET shortname = '$v' WHERE incident_id = '$k'";
				$global['db']->Execute($sql);
				$message = $conf['mod_admin_ims_level1']._t(" successfully updated as ".$v);
			}
			foreach($local_post['level1_date'] as $k => $v) {
				$sql = "UPDATE incident 
					SET date = '$v' WHERE incident_id = '$k'";
				$global['db']->Execute($sql);
				$message = $conf['mod_admin_ims_level1']._t(" successfully updated as ".$v);
			}
			foreach($local_post['level1_type'] as $k => $v) {
				$sql = "UPDATE incident 
					SET type = '$v' WHERE incident_id = '$k'";
				$global['db']->Execute($sql);
				$message = $conf['mod_admin_ims_level1']._t(" successfully updated as ".$v);
			}
			foreach($local_post['level1_latitude'] as $k => $v) {
				$sql = "UPDATE incident 
					SET latitude = '$v' WHERE incident_id = '$k'";
				$global['db']->Execute($sql);
				$message = $conf['mod_admin_ims_level1']._t(" successfully updated as ".$v);
			}
			foreach($local_post['level1_longitude'] as $k => $v) {
				$sql = "UPDATE incident 
					SET longitude = '$v' WHERE incident_id = '$k'";
				$global['db']->Execute($sql);
				$message = $conf['mod_admin_ims_level1']._t(" successfully updated as ".$v);
			}
			//Delete
			if(isset($_POST['level1_delete'])) {
				foreach($local_post['level1_delete'] as $k => $v) {
					$sql = "DELETE FROM incident WHERE incident_id='$k'";
					$global['db']->Execute($sql);
					$message = $conf['mod_admin_ims_level1']._t(" successfully deleted.");
				}
			}
		}
		add_confirmation($message);
	}
}



/**
 * _shn_ims_level2_form 
 * 
 * @param mixed $errors 
 * @param mixed $updated 
 * @access protected
 * @return void
 *
 * Level 2 Form
 */
function _shn_ims_level2_form($errors=false,$type=null) {
	global $global;
	global $conf;

	if ($errors) {
		display_errors();
	}

	$sql = "SELECT incident_id, name FROM incident WHERE parent_id IS NULL";
	$arr = $global['db']->GetAll($sql);
	foreach($arr as $row) {
		$parent_ids[$row['incident_id']] = $row['name'];
	}
	
	$sql = "SELECT  a.incident_id as parent_id, b.name, b.incident_id FROM incident a INNER JOIN incident b ON a.incident_id = b.parent_id AND a.parent_id IS NULL";
	$arr = $global['db']->GetAll($sql);
	if(! empty($arr)) {
		shn_form_fopen("ims_level2",null);
		if($type=='Updated' || $type=='Deleted') {
			shn_form_fsopen(_t(""));
			?><p align="center"><?php echo $type;?></p><?php
			shn_form_fsclose();
		}

		shn_form_hidden(array('seq'=>'update'));
		shn_form_fsopen(_t('Manage ')._t($conf['mod_admin_ims_level2']));
		?><table class="smoothtable" width="100%"><thead>
			<td><strong><?php echo _t('Name');?></strong></td>
			<td><strong><?php echo _lc($conf['mod_admin_ims_level1']);?></strong></td>
			<td><strong><?php echo _t('Delete');?></strong></td>
		</thead><?php
		foreach($arr as $row) {
			?><tr><td><?php
			shn_form_text('', 'level2_name['.$row['incident_id'].']', 'class="smoothinput"', array('value'=>$row['name'], 'no_label'=>true,'req'=>true));
			?></td><td><select name="level2_parent_id[<?php echo $row['incident_id'];?>]"><?php
			foreach($parent_ids as $parent_id => $name) {
				?><option value="<?php echo $parent_id;?>" <?php echo ($parent_id==$row['parent_id']?'selected':'');?> ><?php echo $name;?></option><?php
			}
			?></select></td><td><input type="checkbox" name="level2_delete[<?php echo $row['incident_id'];?>]" /></td></tr><?php
		}
		?></table><?php
		shn_form_fsclose();
		shn_form_submit(_t('Update'));
		shn_form_fclose(); 
	}

	shn_form_fopen("ims_level2",null,array('req_message'=>false));
	if($type=='added') {
		shn_form_fsopen(_t(""));
		?><p align="center"><?php echo $type;?></p><?php
		shn_form_fsclose();
	}
	
	echo "<br /><br /><br />";
	shn_form_hidden(array('seq'=>'addnew'));
	shn_form_fsopen(_t('Add New ')._lc($conf['mod_admin_ims_level2']));
	shn_form_select($parent_ids,_lc($conf['mod_admin_ims_level1']),"level2_new_parent_id",null,array('req'=>true));
	shn_form_text(_t("Name"), 'level2_name_new', 'class="smoothinput"', array('req'=>true));
	shn_form_fsclose();
	shn_form_submit(_t('Add New'));
	shn_form_fclose(); 
}



/**
 * _shn_ims_config_validate 
 * 
 * @access protected
 * @return void
 *
 * level 2 Validation
 */
function _shn_ims_level2_validate() {
	global $conf;
	global $global;
	$error_flag=false;

	//clean the post
	shn_tools_clean_post(&$local_post);
	
	//anything entered?
	if(empty($local_post)) {
		add_error(_t("You have not completed the form"));
		return false;
	}

	if(($local_post['seq']) == 'addnew') {
		if(! isset($local_post['level2_name_new'])) {
			add_error(sprintf(_t("Please enter a name for the %s"),strtolower($conf['mod_admin_ims_level2'])));
			$error_flag=true;
		}
		if(! isset($local_post['level2_new_parent_id'])) {
			add_error(sprintf(_t("Please select a %s"),strtolower($conf['mod_admin_ims_level1'])));
			$error_flag=true;
		}
	} else {
		$local_post['level2_name'] = null;
		foreach($_POST['level2_name'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level2_name'][$k] = $v;
			}
		}
		$local_post['level2_parent_id'] = null;
		foreach($_POST['level2_parent_id'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level2_parent_id'][$k] = $v;
			}
		}

		if(isset($_POST['level2_delete'])) {
			$local_post['level2_delete'] = null;
			foreach($_POST['level2_delete'] as $k => $v) {
				$v = trim($v);
				$k = trim($k);
				if($v != '') {
					$local_post['level2_delete'][$k] = $v;
				}
			}
		}
	}

	if($error_flag) {
		return false;
	} else {
		if (($local_post['seq']) == 'addnew') {
			$sql = "INSERT INTO incident (name,parent_id) VALUES ('{$local_post['level2_name_new']}','{$local_post['level2_new_parent_id']}')";
			$global['db']->Execute($sql);
			$message = $local_post['level2_name_new']._t(" successfully added under ").$conf['mod_admin_ims_level2'];
		}else{
			//Update
			foreach($local_post['level2_name'] as $k => $v) {
				$sql = "UPDATE incident SET name='$v' WHERE incident_id='$k'";
				$global['db']->Execute($sql);
				$message = $conf['mod_admin_ims_level2']._t(" successfully updated as ").$v;
				#echo $sql."<br >";
			}
			foreach($local_post['level2_parent_id'] as $k => $v) {
				$sql = "UPDATE incident SET parent_id='$v' WHERE incident_id='$k'";
				$global['db']->Execute($sql);
				$message = _t("Changes were applied successfully.");
				#echo $sql."<br >";
			}

			//Delete
			if(isset($_POST['level2_delete'])) {
				foreach($local_post['level2_delete'] as $k => $v) {
					$sql = "DELETE FROM incident WHERE incident_id='$k'";
					$global['db']->Execute($sql);
					$message = $conf['mod_admin_ims_level2']._t(" deleted successfully.");
					#echo $sql."<br >";
				}
			}
		}
		add_confirmation($message);
	}
}



/**
 * _shn_ims_level3_form 
 * 
 * @param mixed $errors 
 * @param mixed $updated 
 * @access protected
 * @return void
 */
function _shn_ims_level3_form($errors=false,$type=null) {
	global $global;
	global $conf;

	if($errors) {
		display_errors();
	}

	$sql = "SELECT a.incident_id, a.name FROM incident a INNER JOIN incident b ON a.parent_id = b.incident_id and b.parent_id IS NULL";
	$arr = $global['db']->GetAll($sql);
	foreach($arr as $row) {
		$parent_ids[$row['incident_id']] = $row['name'];
	}
	
	$sql = "SELECT a.incident_id, a.name, b.incident_id as parent_id FROM incident a INNER JOIN incident b  ON a.parent_id = b.incident_id INNER JOIN incident c ON b.parent_id = c.incident_id AND c.parent_id IS NULL";
	$arr = $global['db']->GetAll($sql);
	if(! empty($arr)) {
		shn_form_fopen("ims_level3",null);
		if($type=='Updated' || $type=='Deleted') {
			shn_form_fsopen(_t(""));
			?><p align="center"><?php echo $type;?></p><?php
			shn_form_fsclose();
		}
		shn_form_hidden(array('seq'=>'update'));
		shn_form_fsopen(_t('Manage ')._t($conf['mod_admin_ims_level3']));
		?><table class="smoothtable" width="100%"><thead>
			<td><strong><?php echo _t('Name');?></strong></td>
			<td><strong><?php echo _t($conf['mod_admin_ims_level2']);?></strong></td>
			<td><strong><?php echo _t('Delete');?></strong></td>
		</thead><?php
		foreach($arr as $row) {
			?><tr><td><?php
			shn_form_text('', 'level3_name['.$row['incident_id'].']', 'class="smoothinput"', array('value'=>$row['name'],'no_label'=>true,'req'=>true));
			?></td><td><select name="level3_parent_id[<?php echo $row['incident_id'];?>]"><?php
			foreach($parent_ids as $parent_id => $name) {
				?><option value="<?php echo $parent_id;?>" <?php echo ($parent_id==$row['parent_id']?'selected':'');?> ><?php echo $name;?></option><?php
			}
			?></select></td><td><input type="checkbox" name="level3_delete[<?php echo $row['incident_id'];?>]" /></td></tr><?php
		}
		?></table><?php
		shn_form_fsclose();
		shn_form_submit(_t('Update'));
		shn_form_fclose(); 
	}

	shn_form_fopen("ims_level3",null,array('req_message'=>false));
	if($type=='added') {
		shn_form_fsopen(_t(""));
		?><p align="center"><?php echo $type;?></p><?php
		shn_form_fsclose();
	}
	
	echo "<br /><br /><br />";
	shn_form_hidden(array('seq'=>'addnew'));
	shn_form_fsopen(_t('Add New ')._t($conf['mod_admin_ims_level3']));
	shn_form_select($parent_ids,_t($conf['mod_admin_ims_level2']),"level3_new_parent_id",null,array('req'=>true));
	shn_form_text(_t("Name"), 'level3_name_new', 'class="smoothinput"', array('req'=>true));
	shn_form_fsclose();
	shn_form_submit(_t('Add New'));
	shn_form_fclose(); 
}



/**
 * _shn_ims_config_validate 
 * 
 * @access protected
 * @return void
 * 
 * Level 3 Validation
 */
function _shn_ims_level3_validate() {
	global $conf;
	global $global;
	$error_flag=false;

	//clean the post
	shn_tools_clean_post(&$local_post);
	
	//anything entered?
	if(empty($local_post)) {
		add_error(_t("You have not completed the form"));
		return false;
	}

	if(($local_post['seq']) == 'addnew') {
		if(! isset($local_post['level3_name_new'])) {
			add_error(sprintf(_t("Please enter a name for the %s"),strtolower($conf['mod_admin_ims_level3'])));
			$error_flag=true;
		}
		if(! isset($local_post['level3_new_parent_id'])) {
			add_error(sprintf(_t("Please select a %s"),strtolower($conf['mod_admin_ims_level2'])));
			add_warning(sprintf(_t('If there are no %1$s. Please add a new %2$s'),strtolower($conf['mod_admin_ims_level2']),strtolower($conf['mod_admin_ims_level2'])));
			$error_flag=true;
		}
	}else{
		$local_post['level3_name'] = null;
		foreach($_POST['level3_name'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level3_name'][$k] = $v;
			}
		}
		$local_post['level3_parent_id'] = null;
		foreach($_POST['level3_parent_id'] as $k => $v) {
			$v = trim($v);
			$k = trim($k);
			if($v != '') {
				$local_post['level3_parent_id'][$k] = $v;
			}
		}

		if(isset($_POST['level3_delete'])) {
			$local_post['level3_delete'] = null;
			foreach($_POST['level3_delete'] as $k => $v) {
				$v = trim($v);
				$k = trim($k);
				if($v != '') {
					$local_post['level3_delete'][$k] = $v;
				}
			}
		}
		
	}
	if($error_flag) {
		return false;
	} else {
		if(($local_post['seq']) == 'addnew') {
			$sql = "INSERT INTO incident (name,parent_id) VALUES ('{$local_post['level3_name_new']}','{$local_post['level3_new_parent_id']}')";
			$global['db']->Execute($sql);
			$message = $local_post['level3_name_new']._t(" successfully added under ").$conf['mod_admin_ims_level3'];
		} else {
			//Update
			foreach($local_post['level3_name'] as $k => $v) {
				$sql = "UPDATE incident SET name='$v' WHERE incident_id='$k'";
				$global['db']->Execute($sql);
				$message = $conf['mod_admin_ims_level3']._t(" successfully updated as ").$v;
				#echo $sql."<br >";
			}
			foreach($local_post['level3_parent_id'] as $k => $v) {
				$sql = "UPDATE incident SET parent_id='$v' WHERE incident_id='$k'";
				$global['db']->Execute($sql);
				$message = _t("Changes were applied successfully.");
				#echo $sql."<br >";
			}

			//Delete
			if(isset($_POST['level3_delete'])) {
				foreach($local_post['level3_delete'] as $k => $v) {
					$sql = "DELETE FROM incident WHERE incident_id='$k'";
					$global['db']->Execute($sql);
					$message = $conf['mod_admin_ims_level3']._t(" deleted successfully.");
					#echo $sql."<br >";
				}
			}
		}
		add_confirmation($message);
	}
}
