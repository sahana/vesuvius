{if $reportProjName != null}
	<a href="?mod=vm&amp;stream=text&amp;act=printer_friendly_report&amp;proj_id=<?php echo $_REQUEST['proj_id']; ?>">_("View Printer Friendly Version")</a>
{else}
	<a href="?mod=vm&amp;stream=text&amp;act=printer_friendly_report">_("View Printer Friendly Version")</a>
{/if}
<br />
<br />

{php}
	shn_form_fopen("Report", null, array('req_message' => false));//open form to use help bubbles
	$report_total_hours = 0;
	$report_total_payment = 0;
	$printer_friendly = "";
{/php}

<center>
<div id="vmReportTitle">
	<b>_("Viewing Report For")</b><br />
	{if $reportingSpecificVolunteers}
		<b>_("Specific Volunteers")</b>
	{else}
		{if !is_null($reportProjName) && !is_null($reportOrgName)}
			<b>_("All Volunteers Part of Organization:") </b>
			<b style="color: #C00;">{$reportOrgName}</b><br />
			<b>_("Restricting Results by Project:")</b>
			<b style="color: #C00;">{$reportProjName}</b>
		{else if !is_null($reportProjName)}
			<b>_("Project:") </b>
			<b style="color: #C00;">{$reportProjName}</b>
		{else if !is_null($reportOrgName)}
			<b>_("Organization:") </b>
			<b style="color: #C00;">{$reportOrgName}</b>
		{else}
			<b>_("All Volunteers that Ever Worked on any Projects")</b>
		{/if}
	{/if}
</div>
</center>
<br />

{if count($volunteers) > 0}
	<table align=center>
	    <thead>
	        <tr id="vmReportHeadings">
	            <td>_("Name")</td>
		        <td>_("Status")</td>
		        <td>_("Affiliation")</td>
				<td>_("Total Positions Held")</td>
				<td>_("Total Hours")</td>
				<td>_("Total Monetary Value")</td>
				<td>_("Details")</td>
	        </tr>
	    </thead>
	    <tbody id="vmReportInfo">
	    {foreach $volunteers as $p_uuid => $vol}
	        <tr style="text-align: center; background-color: white; height: 20px;"
	        	onMouseOver="this.style.backgroundColor = '#FFA';"
	        	onMouseOut="this.style.backgroundColor = 'white';">

	{* Volunteer's name *}
	            <td><a href='?mod=vm&act=default&vm_action=display_single&p_uuid={$p_uuid}'>{$vol.full_name}</a></td>

	{* Volunteer's status *}
	            <td>
	            	{if $vol['status'] == 'active'}
	            		<b style="color: green">_("Active")</b>
	            	{else}
	            		<b style="color: #D00">_("Retired")</b>
	            	{/if}
	            </td>

	{* Volunteer's affiliation *}
	            <td>{$vol.affiliation}</td>

	{* Reporting information *}
					{php}
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
					{/php}
					<td>{$vol_positions}</td>
					<td>{$vol_total_hours}</td>
					<td>${$vol_total_payment}</td>
					<td>{php}shn_form_extra_opts(array('help' => $bubble_info));{/php}</td>
	        </tr>
	    {/foreach}
	    </tbody>
	</table>
{else}
	<center>( _("none") )</center>
{/if}

<br />
<br />

<p>
	{php}
		$report_total_hours = number_format(round($report_total_hours, 1), 1);
		$report_total_payment = number_format(round($report_total_payment, 2), 2);
	{/php}

	<h3>_("Total Hours")</h3>
	<b id="vmTotalHours">{$report_total_hours}</b>

	<br />
	<br />

	<h3>_("Total Monetary Value")</h3>
	<b id="vmTotalPayment">${$report_total_payment}</b>
</p>

{php}
shn_form_fclose();
//store printer friendly version to session data
$_SESSION['vm_last_printer_friendly_report'] = $printer_friendly;
{/php}

{* display paging navigation *}

{if $reportProjName != null || $reportOrgName != null}
	<form action="index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_custom_report" method="post">
		<input type="hidden" name="proj_id" value="<?php echo isset($_REQUEST['proj_id']) ? $_REQUEST['proj_id'] : 'ALL_PROJECTS'; ?>" />
		<input type="hidden" name="org_id" value="<?php echo isset($_REQUEST['org_id']) ? $_REQUEST['org_id'] : 'ALL_ORGS'; ?>" />
		{php}
			$baseView = new View();
			$baseView->showPagingNavigation(null, true);
		{/php}
	</form>
{else if $reportingSpecificVolunteers}
	<form action="index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_custom_report" method="post">
		{foreach $_REQUEST['vols'] as $p_uuid}
			<input type="hidden" name="vols[]" value="{$p_uuid}" />
		{/foreach}
		{php}
			$baseView = new View();
			$baseView->showPagingNavigation(null, true);
		{/php}
	</form>
{else}
	{php}
		$baseView = new View();
		$baseView->showPagingNavigation("index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_report_all");
	{/php}
{/if}
