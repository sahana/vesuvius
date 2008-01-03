<h2 style="text-align: center;">
{if $pos_id}
	Edit {$title}
{else}
	Add Position
{/if}
</h2>

{php}
shn_form_fopen('project&vm_action=process_add_position');
	shn_form_fsopen("Position Information");
		shn_form_text("Title", "title", '', array('req'=>true, 'value'=>$title));
		shn_form_select($position_types,'Position Type :', 'ptype_id', '', array('req' => true, 'value' => $ptype_id));
		shn_form_text("Hourly Pay Rate", "payrate", 'size=4', array('req'=>true, 'value'=>$payrate));
		shn_form_text("Target Number of Volunteers", "numSlots", 'size=4', array('req'=>true, 'value'=>$numSlots));
		shn_form_textarea("Description", "description", '', array('value'=>$description, 'req' => true));

		$hidden = array("proj_id" => $proj_id);
		if($pos_id != null)
			$hidden['pos_id'] = $pos_id;
		shn_form_hidden($hidden);
	shn_form_fsclose();
	shn_form_submit("Submit");
	shn_form_button("Cancel", "onClick='history.go(-1);'");
shn_form_fclose();
{/php}
