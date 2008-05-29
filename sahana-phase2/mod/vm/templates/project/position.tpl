<h2 style="text-align: center;">
{if $pos_id}
	_("Edit") {$title}
{else}
	_("Add Position")
{/if}
</h2>

{php}
shn_form_fopen('project&vm_action=process_add_position');
	shn_form_fsopen(_('Position Information'));
		shn_form_text(_('Title'), "title", '', array('req'=>true, 'value'=>$title));
		shn_form_select($position_types,_('Position Type :'), 'ptype_id', '', array('req' => true, 'value' => $ptype_id));
		shn_form_text(_('Hourly Pay Rate'), "payrate", 'size=4', array('req'=>true, 'value'=>$payrate));
		shn_form_text(_('Target Number of Volunteers'), "numSlots", 'size=4', array('req'=>true, 'value'=>$numSlots));
		shn_form_textarea(_('Description'), "description", '', array('value'=>$description, 'req' => true));

		$hidden = array("proj_id" => $proj_id);
		if($pos_id != null)
			$hidden['pos_id'] = $pos_id;
		shn_form_hidden($hidden);
	shn_form_fsclose();
	shn_form_submit(_('Submit'));
	shn_form_button(_('Cancel'), "onClick='history.go(-1);'");
shn_form_fclose();
{/php}
