<h3><?=$US['title']?> <? include('.version') ?></h3>
<a target="content" onClick="h(this);" href="start.php"><?=$US['nav-home']?></a>
<a target="content" onclick="h(this);" href="security.php"><?=$US['nav-secure']?></a>
<a target="content" onclick="h(this);" href="phpinfo.php"><?=$US['nav-phpinfo']?></a>
<a target="content" onclick="h(this);" href="<?=$apanel?>/cgi-bin/includes/lang/<?=file_get_contents("includes/.lang");?>/cgienv.cgi"><?=$US['nav-cgienv']?></a>
<a target="_status" onclick="h(this);" href="/server-status"><?=$US['nav-status']?></a>
<a target="_info" onclick="h(this);" href="/server-info"><?=$US['nav-info']?></a>
<a target="content" onclick="h(this);" href="update.php"><?=$US['nav-update']?></a>