<h2 style="text-align: center;"><?php echo($info['name']); ?></h2>

<?php if($showVolunteersAssigned && ($edit_auth || $delete_auth || $assign_auth)) { ?>
	<div id="submenu_v">
	<?php if($edit_auth) { ?>
		<a href='?mod=vm&act=project&vm_action=display_edit&proj_id=<?php echo($proj_id); ?>'><?php echo _("Edit"); ?></a>
	<?php } 
 if($delete_auth) { ?>
		<a href="?mod=vm&amp;act=project&vm_action=display_confirm_delete&proj_id=<?php echo($proj_id); ?>"><?php echo _("Delete"); ?></a>
	<?php } 
 if($assign_auth) { ?>
		<a href="?mod=vm&amp;act=project&vm_action=display_assign&proj_id=<?php echo($proj_id); ?>"><?php echo _("Assign Volunteers"); ?></a>
	<?php } ?>
		<a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id=<?php echo($proj_id); ?>"><?php echo _("Refresh"); ?></a>
	</div>
<?php } ?>

<table align=center>
    <tbody>
        <tr>
        	<td><b><?php echo _("Project Name :"); ?></b></td>
        	<?php if(!$showVolunteersAssigned) { ?>
        	<td><a href='index.php?mod=vm&act=project&vm_action=display_single&proj_id=<?php echo($proj_id); ?>'><?php echo($info['name']); ?></a></td>
        	<?php } else { ?>
        	<td><?php echo($info['name']); ?></td>
        	<?php } ?>
        </tr>
        <tr>
        	<td><b><?php echo _("Start Date :"); ?></b></td>
        	<td><?php echo($start_date); ?></td>
        </tr>
        <tr>
        	<td><b><?php echo _("End Date :"); ?></b></td>
        	<td><?php echo($end_date); ?></td>
        </tr>
        <tr>
        	<td><b><?php echo _("Location :"); ?></b></td>
        	<td><?php echo($location); ?></td>
        </tr>
        <tr>
        	<td><b><?php echo _("Volunteers assigned :"); ?></b></td>
        	<td><?php echo($numVolunteers); ?></td>
        </tr>
    </tbody>
 </table>
<br />
<br />

<?php if(count($positions) > 0) { ?>
<table align=center>
    <h3 style="text-align: center;"><?php echo _("Positions"); ?></h3>
    <tbody>
    	<tr>
			<th colspan="3"></th>
			<th colspan="2"><?php echo _("# Volunteers"); ?></th>
			<th></th>
    	</tr>
		<tr>
        	<th><?php echo _("Title"); ?></th>
        	<th><?php echo _("Description"); ?></th>
        	<?php if($assign_auth) { ?>
        		<th><?php echo _("Pay Rate"); ?></th>
        	<?php } ?>
        	<th style="padding-right: 1em; text-align: center;"><?php echo _("Target"); ?></th>
        	<th><?php echo _("Assigned"); ?></th>
        	<?php if($add_pos_auth || $delete_pos_auth) { ?>
            <th><?php echo _("Actions"); ?></th>
        	<?php } ?>
        </tr>
		<?php foreach($positions as $p) { ?>
        <tr>
        	<td><?php echo($p['title']); ?></td>
        	<td><?php echo($p['description']); ?></td>

			<?php if($assign_auth) { ?>
        		<td align="center">
        		<?php if(!empty($p['payrate'])) { ?>
        			$<?php echo($p['payrate']); 
 } else { ?>-<?php } ?>
        		</td>
        	<?php } ?>
        	<td align="center">
        		<b>
	        	<?php if($p['numSlots'] > 0) { 
 echo($p['numSlots']); 
 } else { ?>-<?php } ?>
        		</b>
        	</td>

   			<td align="center">
   			<b>

   			<?php if($p['numVolunteers'] <= 0) { ?>
   				<span style="color: red"><?php echo($p['numVolunteers']); ?></span>
   			<?php } else if($p['numVolunteers'] >= $p['numSlots'] ) { ?>
   				<span style="color: green"><?php echo($p['numVolunteers']); ?></span>
   			<?php } else { ?>
   				<span style="color: orange"><?php echo($p['numVolunteers']); ?></span>
   			<?php } ?>
   			</b>
   			</td>
        	<?php if($add_pos_auth || $delete_pos_auth) { ?>
        	<td>
	        	<?php if($add_pos_auth) { ?>
					[<a href="?mod=vm&amp;act=project&amp;vm_action=add_position&amp;proj_id=<?php echo($proj_id); ?>&amp;pos_id=<?php echo($p['pos_id']); ?>"><?php echo _("edit"); ?></a>]
				<?php } 
 if($delete_pos_auth) { ?>
					[<a href="#" onClick="if(confirm('Are you sure you want to remove this position?')) window.location = 'index.php?mod=vm&amp;act=project&amp;vm_action=remove_position&amp;proj_id=<?php echo($proj_id); ?>&amp;pos_id=<?php echo($p['pos_id']); ?>';"><?php echo _("remove"); ?></a>]
				<?php } ?>
			</td>
			<?php } ?>
		</tr>
		<?php } ?>
    </tbody>

 </table>

<?php if($add_pos_auth) { ?>
	<center>
		[<a href="?mod=vm&act=project&vm_action=add_position&proj_id=<?php echo($proj_id); ?>"><?php echo _("Add a position"); ?></a>]
	</center>
<?php } 
 } else { ?>

<center>
	<h3 style="text-align: center;"><?php echo _("Positions"); ?></h3>
		<?php echo _("There are no positions assigned to"); 
 echo($info['name']); ?>.
		<?php if($add_pos_auth ) { ?>
			[<a href="?mod=vm&act=project&vm_action=add_position&proj_id=<?php echo($proj_id); ?>"><?php echo _("Add a position"); ?></a>]
		<?php } ?>
	</center>

<?php } ?>
<br />

<?php if($showVolunteersAssigned) { ?>
<h3><?php echo _("Description"); ?></h3>
<?php echo($info['description']); ?>
<br /><br />

<!--
Projects now have positions
<h3><?php echo _("Specialties needed"); ?></h3>
<br />
<?php
//$skills->display();
?>

<br />
<br />
-->

<div align="center">
	<?php if($numVolunteers > 0) { 
 echo _("Volunteers working on"); 
 echo($info['name']); ?>:
	<?php } else { 
 echo _("No volunteers are currently assigned to"); 
 echo($info['name']); ?>.
	<?php } ?>
</div>
<?php } ?>
<br />
