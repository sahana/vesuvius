<a id="vmToggleDisplayLink" name="graphical" onClick="vmToggleDisplay();" style="cursor: pointer;">View Printer Friendly Version</a>
<br />
<br />

{php}
	$report_total_hours = 0;
	$report_total_payment = 0;
	$javascript = "";
	$next_row = 0;
{/php}

<center>
<div id="vmReportTitle">
	<b>Viewing Report For</b><br />
	{if $reportingSpecificVolunteers}
		<b>Specific Volunteers</b>
	{else}
		{if !is_null($reportProjName) && !is_null($reportOrgName)}
			<b>All Volunteers Part of Organization: </b>
			<b style="color: #C00;">{$reportOrgName}</b><br />
			<b>Restricting Results by Project:</b>
			<b style="color: #C00;">{$reportProjName}</b>
		{else if !is_null($reportProjName)}
			<b>Project: </b>
			<b style="color: #C00;">{$reportProjName}</b>
		{else if !is_null($reportOrgName)}
			<b>Organization: </b>
			<b style="color: #C00;">{$reportOrgName}</b>
		{else}
			<b>All Volunteers that Ever Worked on any Projects</b>
		{/if}
	{/if}
</div>
</center>
<br />

{if count($volunteers) > 0}
	<table align=center>
	    <thead>
	        <tr id="vmReportHeadings">
	            <td>Name</td>
		        <td>Status</td>
		        <td>Affiliation</td>
				<td>Total Positions Held</td>
				<td>Total Hours</td>
				<td>Total Monetary Value</td>
	        </tr>
	    </thead>
	    <tbody id="vmReportInfo">
	    {foreach $volunteers as $p_uuid => $vol}
	        <tr style="text-align: center; background-color: white; height: 20px;" id="volRow{$next_row}"
	        	{php}$next_row++;{/php}
	        	onMouseOver="this.style.backgroundColor = '#FFA';"
	        	onMouseOut="this.style.backgroundColor = 'white';">

	{* Volunteer's name *}
	            <td><a href='?mod=vm&act=default&vm_action=display_single&p_uuid={$p_uuid}'>{$vol.full_name}</a></td>

	{* Volunteer's status *}
	            <td>
	            	{if $vol['status'] == 'active'}
	            		<b style="color: green">Active</b>
	            	{else}
	            		<b style="color: #D00">Retired</b>
	            	{/if}
	            </td>

	{* Volunteer's affiliation *}
	            <td>{$vol.affiliation}</td>

	{* Reporting information *}
					{php}
						$vol_total_hours = 0;
						$vol_total_payment = 0;
						$vol_positions = 0;
						$this_row_num = $next_row - 1;

						$javascript .= "
								var temp_window = document.createElement('td');
								temp_window.style.border = '2px solid black';
								temp_window.style.backgroundColor = '#AFCAE4';
								temp_window.style.position = 'absolute';
								temp_window.style.display = 'none';
								temp_window.style.zIndex = '10';
								temp_window.style.padding = '5px 5px 5px 5px';
								temp_window.style.textAlign = 'left';
								temp_window.name = 'infoBubble';
								temp_window.innerHTML += '<br /><b name=\"vmBubbleFullName\" style=\"text-decoration: underline; color: white\">".str_replace("'", "\'", $vol['full_name'])."</b><br />';
							";

						if(!empty($vol['pay_info']))
						{
							foreach($vol['pay_info'] as $proj_id => $positions)
							{
								foreach($positions as $pos_id => $pos_info)
								{
									if($pos_id != 'project_name')
									{
										$vol_total_hours += $pos_info['hours'];
										$vol_total_payment += $pos_info['hours'] * $pos_info['payrate'];
										$vol_positions++;
										$javascript .= "
											temp_window.innerHTML += '<b style=\"margin-left: 40px; color: #008;\">Position: 		</b>".str_replace("'", "\'", $pos_info['title'])."<br />';
											temp_window.innerHTML += '<b style=\"margin-left: 80px; color: #800;\">Position Status: 	</b>".str_replace("'", "\'", $pos_info['status'])."<br />';
											temp_window.innerHTML += '<b style=\"margin-left: 80px; color: #800;\">Hours: 			</b>".number_format(round($pos_info['hours'], 1), 1)."<br />';
											temp_window.innerHTML += '<b style=\"margin-left: 80px; color: #800;\">Hourly Rate: 		</b>$".number_format(round($pos_info['payrate'], 2), 2)."<br />';
											temp_window.innerHTML += '<b style=\"margin-left: 80px; color: #080;\">Monetary Value: 	</b>$".number_format(round($pos_info['payrate'] * $pos_info['hours'], 2), 2)."<br /><br />';
										";
									}
									else
									{
										$javascript .= " temp_window.innerHTML += '<br /><b style=\"color: #D70;\">Project: </b>".str_replace("'", "\'", $pos_info)."<br />'; ";
									}
								}
							}
						}
						else
						{
							$javascript .= "
								temp_window.innerHTML += '<br /><b>(no positions held)</b><br /><br />';
							";
						}

						$report_total_hours += $vol_total_hours;
						$report_total_payment += $vol_total_payment;

						$vol_total_hours = number_format(round($vol_total_hours, 1), 1);
						$vol_total_payment = number_format(round($vol_total_payment, 2), 2);

						$javascript .= "
							var temp_row = document.getElementById('volRow".$this_row_num."');
							temp_row.appendChild(temp_window);
							try
							{
								temp_row.addEventListener('mouseover', vmMoveInfoBubble, false);
								temp_row.addEventListener('mouseout', vmHideInfoBubble, false);
								temp_row.addEventListener('mousemove', vmMoveInfoBubble, false);
							}
							catch(e)
							{
								temp_row.attachEvent('onmouseover', vmMoveInfoBubble);
								temp_row.attachEvent('onmouseout', vmHideInfoBubble);
								temp_row.attachEvent('onmousemove', vmMoveInfoBubble);
							}
						";
					{/php}
					<td>{$vol_positions}</td>
					<td>{$vol_total_hours}</td>
					<td>${$vol_total_payment}</td>
	        </tr>
	    {/foreach}
	    </tbody>
	</table>
{else}
	<center>(none)</center>
{/if}

<br />
<br />

<script type="text/javascript">

	/**
	 * Moves the info bubble
	 *
	 * @param e 		- the event that was fired to get here
	 * @return void
	 */

	function vmMoveInfoBubble(e)
	{
		var target;
		if(e.target != null)
			target = e.target;
		else
			target = e.srcElement;

		if(target.name == 'infoBubble')
		{
			//if we're here, then the event is happening on the info bubble itself, and not the row,
			//so we have to position it accordingly

			if(e.layerX != null)
			{
				target.style.left = target.offsetLeft + e.layerX + 5 + 'px';
				target.style.top = target.offsetTop + e.layerY + 5 + 'px';
			}
			else
			{
				target.style.left = target.offsetLeft + e.x + 5 + 'px';
				target.style.top = target.offsetTop + e.y + 5 + 'px';
			}
		}
		else
		{
			//get a reference to the actual row

			var row = target;
			while(row.tagName != 'TR')
				row = row.parentNode;

			for(var i = 0; i < row.childNodes.length; i++)
			{
				if(row.childNodes[i].name == 'infoBubble')
				{
					var node = row.childNodes[i];
					if(e.layerX != null)
					{
						node.style.left = e.layerX + 5 + 'px';
						node.style.top = e.layerY + 5 + 'px';
					}
					else
					{
						var newX = e.offsetX + 5;
						var newY = e.offsetY + 5;

						var tempNode = target;
						while(tempNode != null)
						{
							newX += tempNode.offsetLeft;
							newY += tempNode.offsetTop;
							tempNode = tempNode.offsetParent;
						}

						node.style.left = newX + 'px';
						node.style.top = newY + 'px';
					}
					node.style.display = 'block';
					break;
				}
			}
		}
	}

	/**
	 * Hides the info bubble over a volunteer's row
	 *
	 * @param e 		- the event that was fired to get here
	 * @return void
	 */

	function vmHideInfoBubble(e)
	{
		//get a referenece to the actual row

		var row;
		if(e.target != null)
			row = e.target;
		else
			row = e.srcElement;

		while(row.tagName != 'TR')
			row = row.parentNode;

		for(var i = 0; i < row.childNodes.length; i++)
		{
			if(row.childNodes[i].name == 'infoBubble')
			{
				row.childNodes[i].style.display = 'none';
				break;
			}
		}
	}

	/**
	 * A function to set up all of the info bubbles
	 *
	 * @param e 		- the event that was fired to get here
	 * @return void
	 */

	var vmGraphicalHead;
	var vmGraphicalBody;
	var vmPrinterBody;

	function vmSetupInfoBubbles(e)
	{
		//create and attach all of the info bubbles

		{$javascript}

		//store a reference to the entire default document

		vmGraphicalHead = document.getElementsByTagName('head')[0];
		vmGraphicalBody = document.getElementsByTagName('body')[0];

		/*
		 * Create a printer-friendly version of the same page
		 */

		//create and start the new 'head' and 'body' elements

		vmPrinterHead = document.createElement('head');
		vmPrinterBody = document.createElement('body');
		vmPrinterBody.innerHTML = '<h1 id="vmToggleDisplayLink" name="printer" onClick="vmToggleDisplay();" style="cursor: pointer; text-decoration: underline; color: #00F;">Back to Sahana</h1><br /><br /><hr />';
		vmPrinterBody.innerHTML += document.getElementById('vmReportTitle').innerHTML.replace(/color:.*?;/g, '') + '<hr/>';

		//get and store the headings from the report table

		var infoHeadings = document.getElementById('vmReportHeadings');
		var headers = new Array();

		for(var i = 0; i < infoHeadings.childNodes.length; i++)
		{
			if(infoHeadings.childNodes[i].tagName == 'TD')
				headers[headers.length] = infoHeadings.childNodes[i].innerHTML;
		}

		//get and store the actual report information from the report table, using the headings

		var infoBody = document.getElementById('vmReportInfo');
		for(var i = 0; i < infoBody.childNodes.length; i++)
		{
			if(infoBody.childNodes[i].tagName == 'TR')
			{
				var cellIndex = 0;
				vmPrinterBody.innerHTML += '<br /><br />';

				for(var j = 0; j < infoBody.childNodes[i].childNodes.length; j++)
				{
					var cell = infoBody.childNodes[i].childNodes[j];
					if(cell.tagName == 'TD' && cellIndex < headers.length)
					{
						vmPrinterBody.innerHTML += '<b>' + headers[cellIndex] + ': </b>' + cell.innerHTML.replace(/<.*?>/g, '') + '<br />';
						cellIndex++;
					}
					else if(cell.name == 'infoBubble')
					{
						var cellCode = cell.innerHTML;
						cellCode = cellCode.replace(/color.*?\w\w\w/gi, '');
						cellCode = cellCode.replace(/<b.*?name="vmBubbleFullName".*?>.*?<\/b>/gim, '');
						vmPrinterBody.innerHTML += cellCode;
					}
				}

				vmPrinterBody.innerHTML += '<hr />';
			}
		}

		var totalHours = document.getElementById('vmTotalHours').innerHTML;
		var totalPayment = document.getElementById('vmTotalPayment').innerHTML;

		vmPrinterBody.innerHTML += '<b>Total Hours Worked: </b>' + totalHours + '<br />';
		vmPrinterBody.innerHTML += '<b>Total Monetary Value: </b>' + totalPayment + '<br />';
	}

	/**
	 * Toggle between the printer friendly and graphical representation of the data
	 */

	function vmToggleDisplay()
	{
		var toggleLink = document.getElementById('vmToggleDisplayLink');

		if(toggleLink.name == 'graphical')
		{
			vmGraphicalHead.parentNode.replaceChild(vmPrinterHead, vmGraphicalHead);
			vmGraphicalBody.parentNode.replaceChild(vmPrinterBody, vmGraphicalBody);
		}
		else
		{
			vmPrinterHead.parentNode.replaceChild(vmGraphicalHead, vmPrinterHead);
			vmPrinterBody.parentNode.replaceChild(vmGraphicalBody, vmPrinterBody);
		}

	}

	//set up the info bubbles once the page has loaded

	try
	{
		window.addEventListener('load', vmSetupInfoBubbles, false);
	}
	catch(e)
	{
		window.attachEvent('onload', vmSetupInfoBubbles);
	}
</script>

<p>
	{php}
		$report_total_hours = number_format(round($report_total_hours, 1), 1);
		$report_total_payment = number_format(round($report_total_payment, 2), 2);
	{/php}

	<h3>Total Hours</h3>
	<b id="vmTotalHours">{$report_total_hours}</b>

	<br />
	<br />

	<h3>Total Monetary Value</h3>
	<b id="vmTotalPayment">${$report_total_payment}</b>
</p>
