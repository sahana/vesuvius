<?php if(!$assigning) { 
 if($advanced) { ?>
		<h1 style="text-align: center"><?php echo _("Advanced Search Criteria"); ?></h1>
		<a style="font-size: 16px; font-weight:bold;" href="index.php?mod=vm&act=volunteer&vm_action=display_search"><?php echo _("Back to Basic Search"); ?></a><br /><br />
	<?php } else { ?>
		<h1 style="text-align: center"><?php echo _("Basic Search Criteria"); ?></h1>
		<a style="font-size: 16px; font-weight:bold;" href="index.php?mod=vm&act=volunteer&vm_action=display_search&advanced=true"><?php echo _("Advanced Search"); ?></a><br /><br />
	<?php } ?>
	<b style="color: black; font-size: 15px;"><?php echo _("Search results are returned only if they match ALL selected fields."); ?></b><br /><br />
	<b style="color: black; font-size: 15px;"><?php echo _("Please enter at least one field below:"); ?></b><br /><br />
<?php } else { ?>
	<br /><b style="color: black; font-size: 15px;"><?php echo _("Filter volunteer results by any one of the following fields:"); ?></b><br /><br />
<?php } 
 

	global $global;
	include_once($global['approot']."inc/lib_location.inc");

    shn_form_fsopen(_('Personal Information'));
	    shn_form_text(_('Any ID Number:'),'vol_iden','size="30"');
	    shn_form_text(_('Name:'),'vol_name','size="30"');
    shn_form_fsclose();


    if($advanced)
    {
    	shn_form_hidden(array(_('advanced') => 'true'));

    	shn_form_fsopen(_('Options'));
	    	shn_form_checkbox(_('Loose Name Matching') . '<br />' . _('(May return many unrelated results)'), 'loose', ($_POST['loose']=='true')?'checked':'', array('value' => 'true'));
	    	echo '<br /><br /><br />';
	    	shn_form_checkbox(_('Find similar sounding names') . '<br />' . _('(May return many unrelated results)'), 'soundslike', ($_POST['soundslike']=='true')?'checked':'', array('value' => 'true'));
	    	echo '<br /><br /><br />';
	    	shn_form_checkbox(_('Show only unassigned'), 'unassigned', ($_POST['unassigned']=='true')?'checked':'', array('value' => 'true'));
		shn_form_fsclose();

		shn_form_fsopen(_('Location'));
			shn_location(shn_get_range());
		shn_form_fsclose();

		shn_form_fsopen(_('Skills'));
			shn_form_radio(array('and_skills' => _('Require ALL skills below')), '', 'skills_matching', ($_POST['skills_matching']=='and_skills')?'checked':'');
			shn_form_radio(array('or_skills' => _('Require ANY skills below')), '', 'skills_matching', ($_POST['skills_matching']!=_('and_skills'))?'checked':'');
			$skills->display('', 'Node.toggleChildren(0, 0, true); tree_tmp.expandParentsOfChecked(); Tree.checkTree(tree_tmp.root);');
			shn_form_fsclose();


 ?>


<fieldset style="display: none"></fieldset>

<?php 
	    shn_form_fsopen(_('Availability'));
	    	shn_form_radio(array('full_date' => _('Volunteer must be available for the ENTIRE time specified below')), '', 'date_constraint', ($_POST['date_constraint']=='full_date')?'checked':'');
			shn_form_radio(array('partial_date' => _('Volunteer must be available for ANY PORTION of the time specified below')), '', 'date_constraint', ($_POST['date_constraint']!='full_date')?'checked':'');
		    shn_form_date(_('Start date :'), 'start_date');
			shn_form_date(_('End date :'), 'end_date');
	    shn_form_fsclose();
	}

    shn_form_submit(_($assigning?'Filter':'Search'));
    shn_form_fclose();

 ?>
<br />
