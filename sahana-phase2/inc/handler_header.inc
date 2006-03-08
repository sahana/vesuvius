    <div id="header" class="clearfix">
        <?php  ?>
        <h1><?=_("Sahana FOSS Disaster Management System")?></h1>
        <?php 
            global $conf;
            if($conf['sahana_status'] == 'installed'){
                _shn_lc_lang_list(); 
            }
        ?>
    </div>
    <!-- /header -->


