<?php if(count($volunteers) > 0) { ?>
<table align=center>
    <thead>
        <tr>
            <td><?php echo _("Name"); ?></td>


            <?php if($showPictures) { ?>
	            <td><?php echo _("Picture"); ?></td>
			<?php } 
 if($showStatus && $view_auth >= VM_ACCESS_PARTIAL) { ?>
	            <td><?php echo _("Status"); ?></td>
	        <?php } 
 if($showAffiliation && $view_auth >= VM_ACCESS_PARTIAL) { ?>
	            <td><?php echo _("Affiliation"); ?></td>
	        <?php } 
 if($view_auth >= VM_ACCESS_PARTIAL && $showPositions) { ?>
				<td><?php echo _("Project - Position"); ?></td>
			<?php } 
 if($showAvailability && $view_auth >= VM_ACCESS_PARTIAL) { ?>
	            <td><?php echo _("Availability"); ?><br /><?php echo _("Start"); ?></td>
	            <td><?php echo _("Availability"); ?><br /><?php echo _("End"); ?></td>
            <?php } 
 if($view_auth >= VM_ACCESS_PARTIAL && $showHours) { ?>
				  <td><?php echo _("Hours"); ?></td>
			<?php } 
 if($showIDs && $view_auth >= VM_ACCESS_ALL) { ?>
            	<td><?php echo _("Identification"); ?></td>
            <?php } 
 if($showLocation && $view_auth >= VM_ACCESS_PARTIAL) { ?>
            	<td><?php echo _("Location"); ?></td>
           	<?php } 
 if($showSkills && $view_auth >= VM_ACCESS_PARTIAL) { ?>
				<td><?php echo _("Specialties"); ?></td>
			<?php } 
 if($showAssignButton && $view_auth >= VM_ACCESS_PARTIAL) { ?>
				<td><?php echo _("Assign"); ?></td>
			<?php } 
 if($showRemove && $view_auth >= VM_ACCESS_PARTIAL) { ?>
	       		<td><?php echo _("Remove From Project"); ?></td>
			<?php } ?>

        </tr>
    </thead>







    <tbody>
    <?php foreach($volunteers as $vol) { 
 
    		$info = $vol->info;
    	 ?>
        <tr style="text-align: center; background-color: white; height: <?php echo($rowHeight); ?>px;" onMouseOver="this.style.backgroundColor = '#FFA';"	onMouseOut="this.style.backgroundColor = 'white';">
            <td><a href='?mod=vm&act=default&vm_action=display_single&p_uuid=<?php echo $vol->p_uuid; ?>'><?php echo($info['full_name']); ?></a></td>


            <?php if($showPictures) { 
 
            	$pictureID = $vol->getPictureID();
             ?>
			<td style="margin: 0; padding: 0; text-align: center;">
				<?php if(!empty($pictureID)) { ?>
					<img  style="margin: 0; padding: 0;" src="?mod=vm&amp;act=display_image&amp;stream=image&amp;size=thumb&amp;id=<?php echo($pictureID); ?>" />
				<?php } ?>
			</td>
			<?php } 
 if($showStatus && $view_auth >= VM_ACCESS_PARTIAL) { ?>
	            <td>
	            	<?php 
	            		$num_projs = count($vol->proj_id);
	            	 
 if($num_projs > 0) { ?>
	            		<b style="color: green"><?php echo _("Assigned"); ?></b> 
	            	<?php } else { ?>
	            		<b style="color: red"><?php echo _("Unassigned"); ?></b>
	            	<?php } ?>
	            </td>
	        <?php } 
 if($showAffiliation && $view_auth >= VM_ACCESS_PARTIAL) { ?>
	            <td><?php echo($info['affiliation_name']); ?></td>
	        <?php } 
 if($view_auth >= VM_ACCESS_PARTIAL && $showPositions) { ?>
				<td align="center">
				<?php 
					$volPositions = $vol->getVolunteerAssignments();
				 
 if(!empty($volPositions)) { ?>
				<table>
					<?php foreach($volPositions as $position) { ?>
					<tr>
						<td align="right" style="border: none; padding-right: 0;">
					 		<a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id=<?php echo($position['proj_id']); ?>"><?php echo($position['project_name']); ?></a>
					 	</td>
					 	<td align="left" style="border: none;">- <?php echo($position['title']); ?></td>
					</tr>
					<?php } ?>
				</table>
				<?php } ?>
				</td>
			<?php } 
 if($showAvailability && $view_auth >= VM_ACCESS_PARTIAL) { ?>
	            <td><?php echo($info['date_start']); ?></td>
	            <td><?php echo($info['date_end']); ?></td>
            <?php } 
 if($view_auth >= VM_ACCESS_PARTIAL && $showHours) { ?>
  			<td><?php echo $vol->getHoursByProject($modifyProjId); ?></td>

  			<?php } 
 if($showIDs && $view_auth == VM_ACCESS_ALL) { ?>
	            <td>
		            <?php foreach($vol->info['ids'] as $name => $serial) { ?>
		            	<b><?php echo($name); ?></b>: <?php echo($serial); ?><br />
		            <?php } ?>
	            </td>
            <?php } 
 if($showLocation && $view_auth >= VM_ACCESS_PARTIAL) { ?>
	            <td>
	            	<?php foreach($vol->info['location_names'] as $loc) { 
 echo($loc); ?><br />
	            	<?php } ?>
	            </td>
            <?php } 
 if($showSkills && $view_auth >= VM_ACCESS_PARTIAL) { ?>
				<td>
					<select style="width: 100%;">
						<?php foreach($info['skills'] as $opt_value => $desc) { ?>
							<option value="<?php echo($opt_value); ?>">
								<?php echo($desc); ?>
							</option>
						<?php } ?>
					</select>
	        	</td>
        	<?php } 
 if($showAssignButton && $view_auth >= VM_ACCESS_PARTIAL) { ?>
				<td>
				<b><?php echo _("Position:"); ?></b>
				<br />
				<select name="pos_id_<?php echo $vol->p_uuid; ?>">
				<?php foreach($positions as $p) { ?>
					<option value="<?php echo($p['pos_id']); ?>"><?php echo($p['title']); ?></option>
				<?php } ?>
				</select>
				<br />
				<input type="submit" name="assigning_vol_<?php echo $vol->p_uuid; ?>" value="<?php echo _("Assign this Volunteer"); ?>" />
				</td>
        	<?php } 

				global $global;
				$rpp = $global['vm_page_rpp'];
				$page = isset($_REQUEST['page']) ? $_REQUEST['page'] : 1;
			
 if($showRemove && $view_auth >= VM_ACCESS_PARTIAL) { ?>
            	<td onMouseOver="this.style.color='red';"
            	    onMouseOut="this.style.color='black';"
            	    style="color: black; font-size: 30px; font-weight: bold; cursor: pointer; font-family: 'Comic Sans MS'"
            	    onClick="window.location='index.php?mod=vm&amp;act=project&amp;vm_action=process_remove_from_project&amp;p_uuid=<?php echo $vol->p_uuid; ?>&amp;proj_id=<?php echo($modifyProjId); ?>&amp;page=<?php echo($page); ?>&amp;rpp=<?php echo($rpp); ?>';">
            	x</td>
			<?php } ?>

        </tr>
    <?php } ?>
    </tbody>
</table>
<?php } else { 
 if($justAssignedVol) { 
 
		_add_confirmation(_('To assign another volunteer, you must perform another search because no other volunteers match the current search criteria'));
		 
 } else if($searching) { 
 
			add_warning(_('No volunteers were found. Please refine your criteria and try again'));
			if($_REQUEST['vol_name'] != '' && !$advanced)
				add_warning(_('Alternatively, you can try the') . '<a href="index.php?mod=vm&act=volunteer&vm_action=display_search&advanced=true">Advanced Search</a>,' . _('specifying \'Loose Name Matching\''));
		 
 } else { ?>
		<center>_("(none)")</center>
	<?php } 
 } ?>
<br /><br />