<h3><?=$US['nav-tools']?></h3>
<a target="_phpmyadmin" onclick="h(this);" href="<?=$apanel?>/phpMyAdmin/"><?=$US['nav-pma']?></a>
<a target="_phpmyadmin" onclick="h(this);" href="<?=$apanel?>/phpMyBackupPro/"><?=$US['nav-pmbp']?></a>
<a target="content" onclick="h(this);" href="downloads.php"><?=$US['nav-down']?></a>
<a target="content" onclick="h(this);" href="<?=$apanel?>/cgi-bin/includes/lang/<?=file_get_contents("includes/.lang");?>/elog.cgi"><?=$US['nav-elog']?></a>
<a target="content" onclick="h(this);" href="<?=$apanel?>/cgi-bin/includes/lang/<?=file_get_contents("includes/.lang");?>/u2w.cgi"><?=$US['nav-u2w']?></a>
<a target="content" onclick="h(this);" href="<?=$apanel?>/cgi-bin/includes/lang/<?=file_get_contents("includes/.lang");?>/dserver.cgi"><?=$US['nav-del']?></a>
<a target="content" onclick="h(this);" href="migrate.php"><?=$US['nav-smig']?></a>
