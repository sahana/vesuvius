    <div id="header" class="clearfix">
        <?php  ?>
        <h1><?=_("Sahana FOSS Disaster Management System")?></h1>
        <?php 
            global $conf;
            if(file_exists($global['approot'].'conf/sysconf.inc'))
            {
                _shn_lc_lang_list(); 
            }
        ?>
    </div>
    <!-- /header -->


