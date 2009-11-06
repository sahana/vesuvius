<?php if($reportProjName != null) { ?>
	<a href="?mod=vm&amp;stream=text&amp;act=printer_friendly_report&amp;proj_id=<?php echo $_REQUEST['proj_id']; ?>"><?php echo _("View Printer Friendly Version"); ?></a>
<?php } else { ?>
	<a href="?mod=vm&amp;stream=text&amp;act=printer_friendly_report"><?php echo _("View Printer Friendly Version"); ?></a>
<?php } ?>
<br />
<br />

<?php 
	shn_form_fopen("Report", null, array('req_message' => false));//open form to use help bubbles
	$report_total_hours = 0;
	$report_total_payment = 0;
	$printer_friendly = "";
 ?>

<center>
<div id="vmReportTitle">
	<b><?php echo _("Viewing Report For"); ?></b><br />
	<?php if($reportingSpecificVolunteers) { ?>
		<b><?php echo _("Specific Volunteers"); ?></b>
	<?php } else { 
 if(!is_null($reportProjName) && !is_null($reportOrgName)) { ?>
			<b><?php echo _("All Volunteers Part of Organization:"); ?> </b>
			<b style="color: #C00;"><?php echo($reportOrgName); ?></b><br />
			<b><?php echo _("Restricting Results by Project:"); ?></b>
			<b style="color: #C00;"><?php echo($reportProjName); ?></b>
		<?php } else if(!is_null($reportProjName)) { ?>
			<b><?php echo _("Project:"); ?> </b>
			<b style="color: #C00;"><?php echo($reportProjName); ?></b>
		<?php } else if(!is_null($reportOrgName)) { ?>
			<b><?php echo _("Organization:"); ?> </b>
			<b style="color: #C00;"><?php echo($reportOrgName); ?></b>
		<?php } else { ?>
			<b><?php echo _("All Volunteers that Ever Worked on any Projects"); ?></b>
		<?php } 
 } ?>
</div>
</center>
<br />

<?php if(count($volunteers) > 0) { ?>
	<table align=center>
	    <thead>
	        <tr id="vmReportHeadings">
	            <td><?php echo _("Name"); ?></td>
		        <td><?php echo _("Status"); ?></td>
		        <td><?php echo _("Affiliation"); ?></td>
				<td><?php echo _("Total Positions Held"); ?></td>
				<td><?php echo _("Total Hours"); ?></td>
				<td><?php echo _("Total Monetary Value"); ?></td>
				<td><?php echo _("Details"); ?></td>
	        </tr>
	    </thead>
	    <tbody id="vmReportInfo">
	    <?php foreach($volunteers as $p_uuid => $vol) { ?>
	        <tr style="text-align: center; background-color: white; height: 20px;"
	        	onMouseOver="this.style.backgroundColor = '#FFA';"
	        	onMouseOut="this.style.backgroundColor = 'white';">

	
	            <td><a href='?mod=vm&act=default&vm_action=display_single&p_uuid=<?php echo($p_uuid); ?>'><?php echo($vol['full_name']); ?></a></td>

	
	            <td>
	            	<?php if($vol['status'] == 'active') { ?>
	            		<b style="color: green"><?php echo _("Active"); ?></b>
	            	<?php } else { ?>
	            		<b style="color: #D00"><?php echo _("Retired"); ?></b>
	            	<?php } ?>
	            </td>

	
	            <td><?php echo($vol['affiliation']); ?></td>

	
					<?php 
						//format all of the information to go into a Sahana Help information bubble
						$vol_total_hours = 0;
						$vol_total_payment = 0;
						$vol_positions = 0;
						$bubble_info = "<u>{$vol['full_name']}</u><br />";
						if(!empty($vol['pay_info'])) {
							foreach($vol['pay_info'] as $proj_id => $positions) {
								foreach($positions as $pos_id => $pos_info) {
									if($pos_id != 'project_name') {
										$vol_total_hours += $pos_info['hours'];
										$vol_total_payment += $pos_info['hours'] * $pos_info['payrate'];
										$vol_positions++;
										$bubble_info .= "
											<b style=\"margin-left: 10px;\">"._('Position:') 		."</b>{$pos_info['title']}<br />
											<b style=\"margin-left: 20px;\">"._('Position Status:') 	."</b>{$pos_info['status']}<br />
											<b style=\"margin-left: 20px;\">"._('Hours:') 			."</b>".number_format(round($pos_info['hours'], 1), 1)."<br />
											<b style=\"margin-left: 20px;\">"._('Hourly Rate:') 		."</b>$".number_format(round($pos_info['payrate'], 2), 2)."<br />
											<b style=\"margin-left: 20px;\">"._('Monetary Value:') 	."</b>$".number_format(round($pos_info['payrate'] * $pos_info['hours'], 2), 2)."<br /><br />
										";
									} else {
										$bubble_info .= "<br /><b>"._('Project:')." </b>$pos_info<br />";
									}
								}
							}
						} else {
							$bubble_info .= "<br /><b>( "._('no positions held')." )</b><br /><br />";
						}

						$report_total_hours += $vol_total_hours;
						$report_total_payment += $vol_total_payment;

						$vol_total_hours = number_format(round($vol_total_hours, 1), 1);
						$vol_total_payment = number_format(round($vol_total_payment, 2), 2);

						$printer_friendly .= $bubble_info;
						$printer_friendly .= "<table><tr><td><b>"._('Status')."</b></td><td>" . (($vol['status'] == 'active') ? _('Active') : _('Retired')) . "</td></tr>";
						$printer_friendly .= "<tr><td><b>"._('Affiliation')."</b></td><td>" . $vol['affiliation'] . "</td></tr>";
						$printer_friendly .= "<tr><td><b>"._('Positions')."</b></td><td>$vol_positions</td></tr>";
						$printer_friendly .= "<tr><td><b>"._('Total Hours')."</b></td><td>$vol_total_hours</td></tr>";
						$printer_friendly .= "<tr><td><b>"._('Total Payment')."</b></td><td>\$$vol_total_payment</td></tr></table>";
						$printer_friendly .= "<br /><br />";
					 ?>
					<td><?php echo($vol_positions); ?></td>
					<td><?php echo($vol_total_hours); ?></td>
					<td>$<?php echo($vol_total_payment); ?></td>
					<td><?php shn_form_extra_opts(array('help' => $bubble_info)); ?></td>
	        </tr>
	    <?php } ?>
	    </tbody>
	</table>
<?php } else { ?>
	<center>( <?php echo _("none"); ?> )</center>
<?php } ?>

<br />
<br />

<p>
	<?php 
		$report_total_hours = number_format(round($report_total_hours, 1), 1);
		$report_total_payment = number_format(round($report_total_payment, 2), 2);
	 ?>

	<h3><?php echo _("Total Hours"); ?></h3>
	<b id="vmTotalHours"><?php echo($report_total_hours); ?></b>

	<br />
	<br />

	<h3><?php echo _("Total Monetary Value"); ?></h3>
	<b id="vmTotalPayment">$<?php echo($report_total_payment); ?></b>
</p>

<?php 
shn_form_fclose();
//store printer friendly version to session data
$_SESSION['vm_last_printer_friendly_report'] = $printer_friendly;
 
 if($reportProjName != null || $reportOrgName != null) { ?>
	<form action="index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_custom_report" method="post">
		<input type="hidden" name="proj_id" value="<?php echo isset($_REQUEST['proj_id']) ? $_REQUEST['proj_id'] : 'ALL_PROJECTS'; ?>" />
		<input type="hidden" name="org_id" value="<?php echo isset($_REQUEST['org_id']) ? $_REQUEST['org_id'] : 'ALL_ORGS'; ?>" />
		<?php 
			$baseView = new View();
			$baseView->showPagingNavigation(null, true);
		 ?>
	</form>
<?php } else if($reportingSpecificVolunteers) { ?>
	<form action="index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_custom_report" method="post">
		<?php foreach($_REQUEST['vols'] as $p_uuid) { ?>
			<input type="hidden" name="vols[]" value="<?php echo($p_uuid); ?>" />
		<?php } 
 
			$baseView = new View();
			$baseView->showPagingNavigation(null, true);
		 ?>
	</form>
<?php } else { 
 
		$baseView = new View();
		$baseView->showPagingNavigation("index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_report_all");
	 
 } ?>
