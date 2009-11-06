<h3><?php echo _("Access Control"); ?></h3><br />
	<center>
		<b><?php echo _("Please select a situation below to modify access to:"); ?></b>
	</center>
<br /><br />
<form action="?mod=vm&amp;act=adm_default&amp;vm_action=display_acl_modify" method="post">
	<table style="border: 0" align="center">
		<?php foreach($requests as $desc => $info) { 
 
				$matches = array();
				preg_match("/\s*(\w+)(.*)/", $info['partial_desc'], $matches);
			 ?>
			<tr style="border: 0; height: 30px; border-bottom: 1px solid #CCC; background-color: white;" onMouseOver="this.style.backgroundColor='#FFA';" onMouseOut="this.style.backgroundColor='white';">
				<td style="border: 0"><input type="radio" name="request" value="<?php echo($info['act']); ?>&<?php echo($info['vm_action']); ?>" /></td>
				<td style="border: 0">
					<b style="color: #0"><?php echo($info['display_action']); ?></b>
				</td>
				<td style="border: 0">
					<?php if(strcasecmp($matches[1], 'volunteer') == 0) { ?>
						<b style="color: #090;">
					<?php } else if(strcasecmp($matches[1], 'project') == 0) { ?>
						<b style="color: #900;">
					<?php } else if(strcasecmp($matches[1], 'admin') == 0) { ?>
						<b style="color: #990;">
					<?php } else { ?>
						<b style="color: #00C;">
					<?php } 
 echo($matches['1']); ?></b>
				</td>
				<td style="border: 0">
					<b style="color: #0"><?php echo($matches['2']); ?></b>
				</td>
			</tr>
		<?php } ?>
	</table>
	<br /><br />
	<center>
		<input type="submit" value="<?php echo _("Continue"); ?>" />
	</center>
</form>