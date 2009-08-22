<?php
//include_once $global['approot'] . '/mod/dsm/lib_dsm.inc';
?>

<div id="home">

<h2><?php print (_t('Disease Surviellance Module')); ?></h2>

<p>
<?php
    print (_('The Disease Surviellance Module contains data mining and surviellance informations on spreading of diseases. Graphs, maps and charts are being used to represent those information. The simple disease diagnosis system can be used in rulal areas and also as a primary disease diagnosis. This module also consists of data collecting and storing system for data analyzing and mining purposes.'));
?>
</p>
<strong><?php echo _t("Features include:")?></strong>
<ul>
    <li>
    <?php print _t("Capture Information on Diseases.")?>
    </li>
    <li>
    <?php print _t("Graphical representation of surviellance data.")?>
    </li>
    <li>
    <?php print _t("Simple diagnosis system.")?>
    </li>
    
    </ul>
    
    <strong><?php echo _t("Description of Actions:")?></strong><br/>
    <ul>
        <li><a href="index.php?mod=dsm&act=add_dis"><b><?php echo  _t('Add Disease'); ?> </b></a><br/><?php echo  _t('Adding details of a disease into the system'); ?></li>
        <li><a href="index.php?mod=dsm&act=rep_dis"><b><?php echo  _t('Reports patient/disease'); ?> </b></a><br/><?php echo  _t('Reporting a patient or adisease'); ?></li>
        <li><a href="index.php?mod=dsm&act=sur_rep"><b><?php echo  _t('Surviellance Reports'); ?> </b></a><br/><?php echo  _t('Statistic details, Graphical representation'); ?></li>
        </ul>
        <br/>
</div>

<div id="home_recent">



<h1><?php echo  _t('Latest Epidemic Diseases'); ?></h1>
<div id="result">
<table>

<?php

    $recent = _shn_dsm_get_resent();//print $recent->fields['dis_uuid'];
    //$rec_id = array();
   // $rec_id = $recent->fields['dis_uuid'];print $rec_id;
   if ($recent) {
       while (!$recent -> EOF) {
    	    ?><tr><td><?php
            //print $recent->fields['dis_uuid'] . '...........' . $recent->fields['dis_name'];
            echo '<br /><a href="index.php?mod='.$global['module'].'&act=sur_rep&dis_uuid='.$recent->fields['dis_id'].'">'.$recent->fields['dis_name'].' Surviellance Report</a><br />';
            ?></td></tr><?php
            $recent->MoveNext();
        
        }
    }
?>
</table>
</div>
</div>

<?php

