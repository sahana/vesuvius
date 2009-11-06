<?php ?> 
       <h2 class="title">Module Test</h2>

        <p> The module requested : <?php print $global['module'] ?></p>
        <p> The action requested : <?php print $global['action'] ?></p>
        <p> The $conf['dvr_name'] :<?php print $conf['dvr_name'] ?></p>
        <p> Application root     : <?php print $approot ?></p>
        <p> <a href="index.php?act=view&mod=dvr">Mod DVR with view action</a></p>
        <p> Theme is             : <?php print $conf['theme'] ?> </p>
          

