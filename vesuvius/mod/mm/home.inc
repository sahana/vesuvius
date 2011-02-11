<?php

?>

<div id="home">

<h2><?php print (_t('Module Manager')); ?></h2>

<p>
<?php
    print (_('The manager will contain activities to install/uninstall/activate/deactivate modules from Sahana and also include features to use the Sahana App Store and manage the upadate of the current modules'));
?>
</p>
<strong><?php echo _t("Features include:")?></strong>
<ul>
    <li>
    <?php print _t("Install/Uninstall modules")?>
    </li>
    <li>
    <?php print _t("Update current module")?>
    </li>
    <li>
    <?php print _t("App store")?>
    </li>
    
    </ul>
    
    <strong><?php echo _t("Description of Actions:")?></strong><br/>
    <ul>
        <li><a href="index.php?mod=mm&act=module_mgr"><b><?php echo  _t('Install module'); ?> </b></a><br/><?php echo  _t('Install/Uninstall a module'); ?></li>
        <li><a href="index.php?mod=mm&act=update"><b><?php echo  _t('Update module'); ?> </b></a><br/><?php echo  _t('Enable/Disable  a module'); ?></li>
        <li><a href="index.php?mod=mm&act=app_store"><b><?php echo  _t('App store '); ?> </b></a><br/><?php echo  _t('App store related features'); ?></li>
        </ul>
        <br/>
</div>


<?php

