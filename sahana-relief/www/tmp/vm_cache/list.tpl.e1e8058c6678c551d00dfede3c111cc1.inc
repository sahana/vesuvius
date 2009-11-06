<?php if(count($projects) > 0) { ?>
<table align=center>
    <thead>
        <tr>
            <td><?php echo _("Name"); ?></td>
            <td><?php echo _("Description"); ?></td>
        </tr>
    </thead>
    <tbody>
    <?php foreach($projects as $id => $info) { ?>
        <tr>
            <td><a href='?mod=vm&act=project&vm_action=display_single&proj_id=<?php echo($id); ?>'><?php echo($info['name']); ?></a></td>
			<td><?php echo($info['description']); ?></td>
        </tr>
    <?php } ?>
    </tbody>
</table>
<?php } else { ?>
<center>(<?php echo _("no projects"); ?>)</center>
<?php } ?>
<br />