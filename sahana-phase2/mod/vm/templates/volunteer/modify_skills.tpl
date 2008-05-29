<h3>_("Skills Modifications")</h3>
{php}
shn_form_fopen('volunteer&amp;vm_action=process_add_skill');
shn_form_fsopen(_('Add a new skill'));

$req = array('req' => true);

shn_form_text(_('Skill Description :'),'skill_desc','size="50"', $req);
shn_form_text(_('Code [4-5 letter unique abbreviation] : '),'skill_code','size="5"', $req);

shn_form_fsclose();
shn_form_submit(_('Add'));
shn_form_fclose();
{/php}
<br /><br />
{php}
shn_form_fopen('volunteer&amp;vm_action=process_remove_skill', null, array('req_message' => false));
shn_form_fsopen('Remove skills');
{/php}
{if empty($skills)}
	_("No skills defined.")
{else}
	<select name="skills[]" multiple="true">
	{foreach $skills as $code => $skill}
		<option value="{$code}">{$skill}</option>
	{/foreach}
	</select>
{/if}

{php}
shn_form_fsclose();
shn_form_submit(_('Remove'));
shn_form_fclose();
{/php}
