<h2 style="text-align: center;">
{if $pos_id}
	Edit {$title}
{else}
	Add a position
{/if}
</h2>

<form name="position" action="?mod=vm&act=project&vm_action=process_add_position&pos_id={$pos_id}" method="post">

<input type="hidden" name="proj_id" value="{$proj_id}" />

Title:
<input type="text" name="title" value="{$title}"><br />
<br />

Position Type:
<select name="ptype_id">
{foreach $position_types as $this_ptype_id => $ptype_title}
	{if $this_ptype_id == $ptype_id}
	<option value="{$this_ptype_id}" selected="selected">{$ptype_title}</option>
	{else}
	<option value="{$this_ptype_id}">{$ptype_title}</option>
	{/if}
{/foreach}
</select><br />
<br />

Pay Rate :
<input type="text" name="payrate" value="{$payrate}" size="4" />
<br />
<br />

Target number of volunteers:
<input type="text" name="numSlots" value="{$numSlots}" size="4" /><br />
<br />
Description:<br />
<textarea name="description" rows="10" cols="95">{$description}</textarea>
<br />
<br />

<input type="submit" value="Save" />

<br />
	{if $edit_auth}
	<a href="?mod=vm&act=project&vm_action=display_edit&pos_id={$pos_id}">Edit</a>
	{/if}

	{if $delete_auth}
	<a href="?mod=vm&amp;act=project&vm_action=display_confirm_delete&pos_id={$pos_id}">Delete</a>
	{/if}
	<br />

</form>