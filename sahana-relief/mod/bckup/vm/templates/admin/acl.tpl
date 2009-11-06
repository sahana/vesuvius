<h3>_("Access Control")</h3><br />
	<center>
		<b>_("Please select a situation below to modify access to:")</b>
	</center>
<br /><br />
<form action="?mod=vm&amp;act=adm_default&amp;vm_action=display_acl_modify" method="post">
	<table style="border: 0" align="center">
		{foreach $requests as $desc => $info}
			{php}
				$matches = array();
				preg_match("/\s*(\w+)(.*)/", $info['partial_desc'], $matches);
			{/php}
			<tr style="border: 0; height: 30px; border-bottom: 1px solid #CCC; background-color: white;" onMouseOver="this.style.backgroundColor='#FFA';" onMouseOut="this.style.backgroundColor='white';">
				<td style="border: 0"><input type="radio" name="request" value="{$info.act}&{$info.vm_action}" /></td>
				<td style="border: 0">
					<b style="color: #0">{$info.display_action}</b>
				</td>
				<td style="border: 0">
					{if strcasecmp($matches[1], 'volunteer') == 0}
						<b style="color: #090;">
					{else if strcasecmp($matches[1], 'project') == 0}
						<b style="color: #900;">
					{else if strcasecmp($matches[1], 'admin') == 0}
						<b style="color: #990;">
					{else}
						<b style="color: #00C;">
					{/if}
					{$matches.1}</b>
				</td>
				<td style="border: 0">
					<b style="color: #0">{$matches.2}</b>
				</td>
			</tr>
		{/foreach}
	</table>
	<br /><br />
	<center>
		<input type="submit" value="_("Continue")" />
	</center>
</form>