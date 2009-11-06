<?php if($edit_auth || $delete_auth) { ?>
	<div id="submenu_v">
		<?php if($edit_auth) { ?>
			<a href = '?mod=vm&act=volunteer&vm_action=display_edit&p_uuid=<?php echo($p_uuid); ?>'><?php echo _("Edit"); ?></a>
		<?php } 
 if($delete_auth && $p_uuid != $_SESSION['user_id']) { ?>
			<a href = '?mod=vm&act=volunteer&vm_action=display_confirm_delete&p_uuid=<?php echo($p_uuid); ?>'><?php echo _("Delete"); ?></a>
		<?php } ?>
	</div>
<?php } ?>
<br>
<?php if(!empty($pictureID)) { ?>
<center><img style="padding-bottom: 1em;" src="?mod=vm&amp;act=display_image&amp;stream=image&amp;size=full&amp;id=<?php echo($pictureID); ?>" /></center>
<?php } ?> </br>
<table align="center" border="0">
	<tr>
		<br>
		<td><b><?php echo _("Name:"); ?></b></td>
		<td><?php echo($info['full_name']); ?></td>
	</tr>
	<tr>
		<td><b><?php echo _("Gender:"); ?></b></td>
		<td><?php echo($info['gender']); ?></td>
	</tr> </br>
	<?php if($view_auth == VM_ACCESS_ALL && !empty($ids)) { ?>
	<tr>
		<td><b>ID:</b></td>
		<td>
			<?php foreach($ids as $type => $value) { 
 echo($id_types[$type]); ?>: <?php echo($value); ?><br />
			<?php } ?>
		</td>
	</tr>
	<?php } 
 if(!empty($locations)) { ?>
	<tr>
		<td><b>Location:</b></td>
		<td>
			<?php foreach($locations as $loc) { 
 echo($loc['name']); ?><br />
			<?php } ?>
		</td>
	</tr>
	<?php } 
 if($view_auth == VM_ACCESS_ALL && !empty($dob)) { ?>
	<tr>
		<td><b><?php echo _("Date of Birth:"); ?></b></td>
		<td><?php echo($dob); ?></td>
	</tr>
	<?php } ?>
</table>
<br />
<?php if(!empty($info['contact'])) { ?>
	<h2><?php echo _("Contact Info"); ?></h2>
	<table align="center" border="0">
		<?php foreach($info['contact'] as $type => $value) { 
 if(strlen($value) > 0) { ?>
			<tr>
				<td><b><?php echo($contact_types[$type]); ?>:</b></td>
				<td><?php echo($value); ?></td>
			</tr>
			<?php } 
 } ?>
	</table>
	<br />
<?php } ?>
<h2><?php echo _("Availability"); ?></h2>
<table align="center" border="0">
	<tr>
		<td><b><?php echo _("Work Begin:"); ?></b></td>
		<td><?php echo($date_start); ?></td>
	</tr>
	<tr>
		<td><b><?php echo _("Work End:"); ?></b></td>
		<td><?php echo($date_end); ?></td>
	</tr>
	<?php if(!empty($hour_start)) { ?>
		<tr>
			<td><b><?php echo _("Work Hour Begin:"); ?></b></td>
			<td><?php echo($hour_start); ?></td>
		</tr>
	<?php } 
 if(!empty($hour_end)) { ?>
		<tr>
			<td><b><?php echo _("Work Hour End:"); ?></b></td>
			<td><?php echo($hour_end); ?></td>
		</tr>
	<?php } ?>
</table>
<br />

<h2><?php echo _("Work Details"); ?></h2>
<table align="center" border="0">
	<?php if(!empty($occupation)) { ?>
	<tr>
		<td><b><?php echo _("Occupation:"); ?></b></td>
		<td><?php echo($occupation); ?></td>
	</tr>
	<?php } 
 if(!empty($affiliation)) { ?>
	<tr>
		<td><b><?php echo _("Affiliation:"); ?></b></td>
		<td><?php echo($affiliation); ?></td>
	</tr>
	</table>
	<?php } 
 if(count($projects) > 0) { ?>
	<table align= "center">
		<thead>
			<tr>
				<td> <?php echo _("Project"); ?> </td>
				<td><?php echo _("Position"); ?></td>
				<td><?php echo _("Log Time"); ?></td>
			</tr>
		</thead>
		<tbody>

		<?php foreach($VolPositions as $position) { ?>
			<tr>
				<td><a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id=<?php echo($position['proj_id']); ?>"><?php echo($position['project_name']); ?></a></td>
				<td><?php echo($position['title']); ?></td>
				<td style="text-align: center">
					<?php 
						if($ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_log_time_form', array('pos_id' => $position['pos_id'], 'p_uuid' => $p_uuid))))
						{
					 ?>
						<a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_log_time_form&amp;p_uuid=<?php echo($p_uuid); ?>&amp;pos_id=<?php echo($position['pos_id']); ?>"><?php echo _("Log time"); ?></a>
					<?php } else { ?>
						---
					<?php } ?>
				</td>
			</tr>
		<?php } ?>

		</tbody>
	</table>
			<?php } else { ?>
			(none)
			<?php } ?>


</table>
<br />
<h2><?php echo _("Skills and Work Restrictions"); ?></h2>
<?php
$vol_skills->display();

 if(!empty($special_needs)) { ?>
	<tr>
	<br>
		<td><b><?php echo _("Special Needs:"); ?> </b></td>
		<td><?php echo($special_needs); ?></td>
	</br>
	</tr>
<?php } ?>

