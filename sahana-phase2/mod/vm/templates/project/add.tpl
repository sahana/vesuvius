<h2> {$action} Project</h2>
{php}
shn_form_fopen('project&vm_action=process_add');
	shn_form_fsopen("Project Information");
		shn_form_text("Name", "name", '', array('req'=>true, 'value'=>$info['name']));
		shn_form_date('Start date :', 'start_date', array('value' => $start_date));
		shn_form_date('End date :', 'end_date', array('value' => $end_date));
		shn_form_textarea("Description", "description", '', array('value'=>$info['description']));
	shn_form_fsclose();

	shn_form_fsopen('Details');
		shn_form_select($managers,'Site Manager :', 'manager', '', array('value' => $info['mgr_id'], 'req' => true));

		echo "<b>Please select needed skills below. </b>";
		shn_form_extra_opts(array('req' => true));
		echo "<b>NOTE: Selecting a category will select all skills below it.</b>";
		shn_form_extra_opts(array("help" => "When you select a checkbox that has a <img src='".TREE_IMAGE_PATH."plus' />
		                                     next to it, you are selecting all skills that fall under that category. For this
		                                     reason, make sure that you review the skills you select by expanding until you see a
		                                     <img src='".TREE_IMAGE_PATH."minus' />"));
		$skills->display('', 'Node.toggleChildren(0, 0, true); tree_tmp.expandParentsOfChecked(); Tree.checkTree(tree_tmp.root);');
	shn_form_fsclose();
{/php}

{* This line is included as a temporary fix for a bug that made elements (in the fieldset under the fieldset containing the tree) float around when expanding and collapsing tree nodes *}
<fieldset style="display: none"></fieldset>

{php}
	shn_form_fsopen('Base Location');
		shn_location(shn_get_range(), $info['location_id']);
	shn_form_fsclose();

	shn_form_hidden($hidden);
	shn_form_submit("Submit");
	shn_form_button("Cancel", "onClick='history.go(-1);'");
shn_form_fclose();
{/php}