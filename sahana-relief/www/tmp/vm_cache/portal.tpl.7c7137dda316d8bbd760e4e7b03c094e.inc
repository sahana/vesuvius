<h1 align=center><?php echo _("Volunteer Management"); ?></h1>
<p><?php echo _("The Volunteer Management module keeps track of projects and volunteers."); ?></p>
<h3><?php echo _("Volunteer Portal"); ?></h3><br/>
<ul style="margin-left: 1em;">
	<li><a href="?mod=vm&amp;act=default&amp;vm_action=display_single&amp;p_uuid=<?php echo($p_uuid); ?>"><b><?php echo _("My information page"); ?></b></a><br/><?php echo _("Personal information and time logging."); ?>  </li>
	<?php if($vol_assign) { ?>
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_select_project"><b><?php echo _("Assign to Project"); ?></b></a><br><?php echo _("Manage volunteer assignments"); ?></li>
	<?php } 
 if($showAssigned) { ?>
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_list_assigned"><b><?php echo _("Show Assigned"); ?></b></a><br/><?php echo _("View all volunteers assigned to projects"); 
 } 
 if($listVolunteers) { ?>
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_list_all"><b><?php echo _("View All Volunteers"); ?></b></a><br/><?php echo _("View all registered volunteers"); 
 } 
 if($search) { ?>
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_search"><b><?php echo _("Search"); ?></b></a><br/><?php echo _("Search for a volunteer"); 
 } 
 if($add_proj) { ?>
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_add"><b><?php echo _("Add New Project"); ?></b></a><br/><?php echo _("Start a new project"); ?></li>
	<?php } 
 if($listMyProjects) { ?>
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_my_list"><b><?php echo _("View My Projects"); ?></b></a><br/><?php echo _("View all projects you are currently assigned to"); 
 } 
 if($listAllProjects) { ?>
		<li><a href="?mod=vm&amp;act=project"><b><?php echo _("View All Projects"); ?></b></a><br/><?php echo _("View all projects being tracked"); ?></li>
	<?php } 
 if($inbox) { ?>
		<li><a href="?mod=vm&amp;act=volunteer&vm_action=display_custom_report_select"><b><?php echo _("Generate report"); ?></b></a><br/><?php echo _("Generate customized report on volunteers and projects"); ?></li>
	<?php } 
 if($outbox) { ?>
		<li><a href="?mod=vm&amp;act=volunteer&vm_action=display_add"><b><?php echo _("Register to VM"); ?></b></a><br /><?php echo _("Register yourself in Volunteer Management module"); ?></li>
	<?php } 
 if($sendMessage) { ?>
		<li>
			<a href="?mod=vm&amp;act=volunteer&vm_action=display_send_message"><b><?php echo _("Send messages"); ?></b></a>
			<br />
			<?php echo _("Send messages to other users"); ?>
		</li>
	<?php } ?>


</ul>
<h3><?php echo _("Current projects"); ?></h3>
<p>
<?php if(empty($projects)) { 
 echo _("You are not assigned to any project."); 
 } else { ?>
<a href="?mod=vm&amp;act=project&amp;vm_action=display_my_list"><?php echo _("Click here"); ?></a> <?php echo _("to view your projects"); ?>.
<?php } ?>
</p>
<h3><?php echo _("Current features include:"); ?></h3>
</p>
<ul style="margin-left: 1em;">
	<li><?php echo _("Manage volunteer assignment"); ?></li>
	<li><?php echo _("Start and view projects"); ?></li>
	<li><?php echo _("Search volunteers"); ?></li>
	<li><?php echo _("Send and receive messages"); ?></li>
</ul>

<SMALL><?php echo _("Version"); ?> 1.4, <?php echo _("Last Modified"); ?> 05/25/2008 01:40 EST </SMALL>
<br /><br />

