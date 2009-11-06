<h3><?php echo _("Approve Site Managers"); ?> </h3><br />

<div style="text-align: center; font-weight: bold;"><?php echo _("Current or Previous Applicants"); ?></div>
<?php if(count($managers) == 0) { ?>
<br /><center><?php echo _("There are no managers to approve or revoke manager approval from."); ?></center>
<?php } else { ?>
<br />
<br />
<table align="center">
	<thead>
		<tr>
			<td><?php echo _("Current Status"); ?></td>
			<td><?php echo _("Approve"); ?></td>
			<td><?php echo _("Deny / Revoke"); ?></td>
			<td><?php echo _("Volunteer"); ?></td>
		</tr>
	</thead>
	<tbody>
		<?php foreach($managers as $p_uuid => $info) { ?>
			<tr align="center">
				<form action="?mod=vm&amp;act=volunteer&amp;vm_action=process_approval_modifications" method="post">
					<input type="hidden" name="vol_id" value="<?php echo($p_uuid); ?>" />
					<td>
						<?php if($info['status']=='approved') { ?>
							<b style="color: green;"><?php echo _("Approved"); ?></b>
						<?php } else { 
 if($info['status']=='denied') { ?>
								<b style="color: #D00;"><?php echo _("Denied"); ?></b>
							<?php } else { ?>
								<b style="color: #F80;"><?php echo _("Unapproved"); ?></b>
							<?php } 
 } ?>
					</td>
					<?php 
						if($info['status']=='approved')
						{
							$approveButtonShow = 'disabled';
							$denyButtonName = _('Revoke');
						}
						else
						{
							$approveButtonShow = '';
							$denyButtonName = _('Deny');
						}

						if($info['status']=='denied')
						{
							$denyButtonName = _('(Denied)');
							$denyButtonShow = 'disabled';
						}
						else
						{
							$denyButtonShow = '';
						}
					 ?>
					<td><input type="submit" name="approve" value="Approve" <?php echo($approveButtonShow); ?> /></td>
					<td><input type="submit" name="deny" value="<?php echo($denyButtonName); ?>" <?php echo($denyButtonShow); ?> /></td>
					<td><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_single&amp;p_uuid=<?php echo($p_uuid); ?>"><?php echo($info['name']); ?></a></td>
				</form>
			</tr>
		<?php } ?>
	</tbody>
</table>
<?php } ?>
<br />
<br />
<div style="text-align: center; font-weight: bold;">
	<?php echo _("Upgrade Non-Applicants"); ?>
</div>
<br />
<br />
<center>
	<form action="?mod=vm&amp;act=volunteer&amp;vm_action=process_approval_upgrades" method="post">
		<select name="vol_id">
			<?php foreach($volunteers as $p_uuid => $name) { ?>
				<option value="<?php echo($p_uuid); ?>"><?php echo($name); ?></option>
			<?php } ?>
		</select>
		<input type="submit" value="<?php echo _("Upgrade this Volunteer to Site Manager Status"); ?>" />
	</form>
</center>