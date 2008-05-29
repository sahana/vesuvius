{if $action!='Save'}
<h2>_("Volunteer Registry - Thank you for your help!")</h2>
<b style="color: #369; font-size: 16px">_("To register, fill in as many of the below fields as possible. When you are finished, click \"Submit\".
Your registration will be confirmed via phone or email.")</b>
<br /><br />
{else}
<h2>_("Edit details")</h2><br />
{/if}

{php}

shn_form_fopen('default&vm_action=process_add', null, array('enctype' => 'enctype="multipart/form-data"'));

	shn_form_fsopen(_('Personal Details'));
		shn_form_text(_('Name in Full :'), 'full_name', '', array('req' => true, 'value' => $full_name));
		shn_form_date(_('Date of Birth :'), 'dob', array('value' => $dob));
		shn_form_select(array('M' => _('Male'), 'F' => _('Female')), _('Gender :'), 'gender', '', array('value' => $gender));
		shn_form_select($id_types, _('Type of Identification :'), 'id_type', '', array('value' => $id_type));
		shn_form_text(_('Identification Number :'), 'serial', '', array('value' => $serial));
	shn_form_fsclose();

	if($reg_account)
	{
		shn_form_fsopen(_('Create a Sahana account'));
		{/php}
		<b style="color: red">_("Remember this information, because you will use it to log into Sahana.")</b><br /><br />
		{php}
			shn_form_text(_('Username :'), 'user_name', '', array('req' => true));
			shn_form_password(_('Password :'), 'pass1', '', array('req' => true));
			shn_form_password(_('Re-Type Password :'), 'pass2', '', array('req' => true));
			shn_form_hidden(array('reg_account' => 'true'));
		shn_form_fsclose();
	}

	shn_form_fsopen(_('Work Details'));
		shn_form_select($orgs, _('Affiliation :'), 'affiliation', '', array('value' => $affiliation ,'help' => _('Organizations are populated through the Organization Registry module. Contact an administrator if you do not see your organization.')));
		shn_form_text(_('Occupation :'), 'occupation', '', array('value' => $occupation));
	shn_form_fsclose();

	shn_form_fsopen(_('Skills'));
		echo "<b>" . _('Please select your skills and limitations below.') . "</b>";
		shn_form_extra_opts(array('req' => true));
		echo "<b>" . _('NOTE: Selecting a category will select all options below it.') . "</b>";
		shn_form_extra_opts(array("help" => _('When you select a checkbox that has a ')."<img src='".TREE_IMAGE_PATH."plus' />". _(' next to it, you are selecting all options that fall under that category. For this reason, make sure that you review the options you select by expanding until you see a '). "<img src='".TREE_IMAGE_PATH."minus' />"));

		$select_skills_tree->display('', 'Node.toggleChildren(0, 0, true); tree_tmp.expandParentsOfChecked(); Tree.checkTree(tree_tmp.root);');

		echo '<p>' . _('Optionally, you may enter any special needs. Please use commas to separate multiple needs:') . '</p>';
		shn_form_textarea(_('Special needs:'), 'special_needs', '', array('value' => $special_needs));
		shn_form_fsclose();
{/php}

{* This line is included as a temporary fix for a bug that made elements (in the fieldset under the fieldset containing the tree) float around when expanding and collapsing tree nodes *}
<fieldset style="display: none"></fieldset>

{php}
	shn_form_fsopen(_('Availability'));
		shn_form_date(_('Start Date :'), 'start_date', array('value' => $date_start, 'req' => true));
		shn_form_date(_('End Date :'), 'end_date', array('value' => $date_end, 'req' => true));
		shn_form_text(_('Start Hours (e.g. 08:00) :'), 'hrs_avail_start', '', array('value' => $hour_start));
		shn_form_text(_('End Hours (e.g. 17:00) :'), 'hrs_avail_end', '', array('value' => $hour_end));

	shn_form_fsclose();

	shn_form_fsopen(_('Base Location'));
		shn_location(shn_get_range(), $location);
	shn_form_fsclose();

	shn_form_fsopen(_('Contact Information'));
		foreach($contact_types as $code => $name)
		{
			shn_form_text($name.' :', 'contact_'.$code, '', array('value' => $info['contact'][$code]));
		}
	shn_form_fsclose();

	shn_form_fsopen(_('Picture'));
	echo '<p>' . _('Optionally, you may upload a picture to identify yourself.') . '</p>';
	shn_form_upload(_('Image file:'),"picture");
	{/php}
	{if !empty($pictureID)}
		<p>_('Current picture') [<a href="?mod=vm&amp;act=volunteer&amp;vm_action=process_remove_picture&amp;id={$p_uuid}&amp;p_uuid={$p_uuid}">remove</a>]</p>
		<img src="?mod=vm&amp;act=display_image&amp;stream=image&amp;id={$pictureID}" />
	{/if}
	{php}
	shn_form_fsclose();

	shn_form_hidden($hidden);

	shn_form_submit($action);

shn_form_fclose();
{/php}
<br />
