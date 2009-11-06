<h2 style="text-align: center;">_("Create Custom Report")</h2>
<br />

{php}
	shn_form_fopen('volunteer&amp;vm_action=display_custom_report&amp;rpp='.VM_DEFAULT_REPORTS_RPP, null, array('enctype' => 'enctype="multipart/form-data"'));

		shn_form_fsopen(_('Filter by Project, Organization, or Both'));
			shn_form_select($projects, _('By Project:'), 'proj_id');
			shn_form_select($orgs, _('By Organization:'), 'org_id');
		shn_form_fsclose();

		shn_form_submit(_('Create Project or Organization Report'));

	shn_form_fclose();
{/php}

<br />
<br />

{php}
	shn_form_fopen('volunteer&vm_action=display_custom_report', null, array('enctype' => 'enctype="multipart/form-data"'));
		shn_form_fsopen(_('Report by Specific Volunteers'));
		shn_form_extra_opts(array('br' => true, 'help' => _('To add a volunteer to the list, select one in the \'List of Volunteers\' below and click on \'Add\'.') . "<br /><br />" . _('To remove a volunteer from the list, click on the remove link next to his name.')));
{/php}
<br />
<div style="border: 1px solid black; margin-left: 150px; padding: 10px 10px 10px 10px; width: 300px; height: 150px; overflow: auto;">
	<p id="no_people_selected" style="text-align: center">(none)</p>
	<div id="vol_list_div"></div>
</div>
<br />
<br />
{php}

		shn_form_select($vols, _('List of Volunteers :'), 'vol_list', '', array('br' => false));

		//Add the 'Add' button and make it update the to list

		shn_form_button('Add', "onClick=\"
			var list = document.getElementById('vol_list');
			var value = list.options[list.selectedIndex].getAttribute('value');
			var text = list.options[list.selectedIndex].text;
			addToList(value, text);
		\"", array('br' => false));

	shn_form_fsclose();

	shn_form_submit(_('Create Custom Report for these Volunteers'), "onClick=\"
		var vols_tmp = document.getElementById('vol_list_div');
		if(vols_tmp.childNodes.length == 0)
		{
			alert('_('You must select at least one volunteer if reporting by volunteer.')');
			return false;
		}
	\"");
shn_form_fclose();
{/php}

<script type="text/javascript">
/*
 * Set up a function to add a person to the volunteer list
 *
 * @param value		-	the p_uuid of the person to add
 * @param text		-	the name of the person to add
 * @return void
 */

function addToList(value, text)
{
	//get a reference to the volunteer list
	var vol_list = document.getElementById('vol_list_div');

	//check to see if the person is already in the to list and return if so
	for(var i = 0; i < vol_list.childNodes.length; i++)
	{
		var child = vol_list.childNodes[i];
		if(child.tagName == 'DIV'  && child.getAttribute('name') == value)
			return;
	}


	var row = document.createElement('div');
	row.setAttribute('name', value);

	var input = document.createElement('input');
	input.setAttribute('type', 'checkbox');
	input.setAttribute('name', 'vols[]');
	input.setAttribute('value', value);
	input.style.display = 'none';		//do not display the input, we only want to have it record the entry in the to list, not be able to change its value

	var remove_text = document.createElement('span');
	remove_text.style.color = 'red';
	remove_text.style.border = '0pt none';
	remove_text.style.cursor = 'pointer';
	remove_text.style.display = 'inline';
	remove_text.appendChild(document.createTextNode('(click to remove) '));

	var name_text = document.createElement('span');
	name_text.style.border = '0pt none';
	name_text.style.display = 'inline';
	name_text.appendChild(document.createTextNode(text));

	try
	{
		remove_text.addEventListener('click',
		function(e)
		{
			var num_rows = 0;
			var parent_div = e.target.parentNode.parentNode;
			for(var i = 0; i < parent_div.childNodes.length; i++)
			{
				if(parent_div.childNodes[i].tagName == 'DIV')
					num_rows++;
			}

			e.target.parentNode.parentNode.removeChild(e.target.parentNode);

			if((num_rows - 1) == 0)
			{
				var none = document.getElementById('no_people_selected');
				none.style.display = 'block';
				none.style.textAlign = 'center';
			}
		}, false);
	}
	catch(err)
	{
		remove_text.attachEvent('onclick',
		function(e)
		{
			var num_rows = 0;
			var parent_div = e.srcElement.parentNode.parentNode;
			for(var i = 0; i < parent_div.childNodes.length; i++)
			{
				if(parent_div.childNodes[i].tagName == 'DIV')
					num_rows++;
			}

			e.srcElement.parentNode.parentNode.removeChild(e.srcElement.parentNode);

			if((num_rows - 1) == 0)
			{
				var none = document.getElementById('no_people_selected');
				none.style.display = 'block';
				none.style.paddingLeft = '150px';
			}
		});
	}

	try
	{
		remove_text.addEventListener('mouseover',
		function(e)
		{
			e.target.style.backgroundColor = '#FFA';
		}, false);
	}
	catch(err)
	{
		remove_text.attachEvent('onmouseover',
		function(e)
		{
			e.srcElement.style.backgroundColor = '#FFA';
		});
	}

	try
	{
		remove_text.addEventListener('mouseout',
		function(e)
		{
			e.target.style.backgroundColor = '#FFF';
		}, false);
	}
	catch(err)
	{
		remove_text.attachEvent('onmouseout',
		function(e)
		{
			e.srcElement.style.backgroundColor = '#FFF';
		});
	}

	row.appendChild(input);
	row.appendChild(remove_text);
	row.appendChild(name_text);
	vol_list.appendChild(row);
	input.checked = true;		//do this here for IE
	document.getElementById('no_people_selected').style.display = 'none';
}

</script>