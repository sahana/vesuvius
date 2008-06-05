<?
/*
####################################################
# Name: The Uniform Server Admin Panel 2.0
# Developed By: The Uniform Server Development Team
# Modified Last By: Olajide Olaolorun (empirex) 
# Web: http://www.uniformserver.com
####################################################
*/

// Includes
include "includes/config.inc.php";
include "$apanel_path/includes/lang/".file_get_contents("includes/.lang").".php"; 
include "includes/secure.php";

// Path to httpd.conf
$httpd_conf_sti = "/usr/local/apache2/conf/httpd.conf";

// Path to hosts file
$hosts_sti = $_ENV["windir"]."/system32/drivers/etc/hosts";

// path to all hosts
$default_path = "/www/";

if(isset($_POST["host_navn"])) {

if(!is_dir($_POST["host_path"])) {
mkdir($_POST["host_path"]);
}

$conf_str = "\n##########VIRTUAL HOST SETUP##########";
$conf_str .= "\n# ". strtoupper($_POST["host_navn"]) ."\n";
$conf_str .= "<VirtualHost *>\n";
$conf_str .= "ServerName ". $_POST["host_navn"] ."\n";
$conf_str .= "DocumentRoot ". $_POST["host_path"] ."\n";

    if(!empty($_POST["host_param"])) {
    $conf_str .= $_POST["host_param"] ."\n";
    }

$conf_str .= "</VirtualHost>\n";

$conf = fopen($httpd_conf_sti, "at");
if ($conf) {
fputs($conf, $conf_str);
fclose($conf);
}

// Write to hosts file
$host_str = "\n127.0.0.1    ". $_POST["host_navn"];

$to_hostsfil = fopen($hosts_sti, "at");
if ($to_hostsfil) {
fputs($to_hostsfil, $host_str);
fclose($to_hostsfil);
}

// Restarts apache. Only works if safe_mode is Off in php.ini
//$exe_sti = explode("/usr/local/apache2/conf/httpd.conf", $httpd_conf_sti);
//$true_exesti = str_replace("/", "\\", $exe_sti[0]);
//exec($true_exesti ."Apache.exe -k restart");

//header("Location:". $_SERVER["PHP_SELF"] ."");
header('Location: http://localhost/apanel/cgi-bin/includes/lang/en/rs.cgi');
exit();
}
include "includes/header.php"; 
?>
<body leftmargin="0" topmargin="0">

<div id="main">
<h2>&#187; <?=$US['vhost-head']?></h2>
<?
if(is_file($httpd_conf_sti)) { // findes httpd.conf?
    if(is_file($hosts_sti)) {  // findes filen hosts?

$all_hosts = array();
$fil = file($httpd_conf_sti);

// Finds hosts in httpd.conf
    for($i = 0; $i < count($fil); $i++) {
        $fil[$i] = trim($fil[$i]);

        if(substr($fil[$i], 0, 10) == "ServerName") {
            $all_hosts[] = trim(strtolower(substr($fil[$i], 10)));
        }
    }

// Remove "duplicates"
$hosts = array_unique($all_hosts);

sort($hosts);

// If there was "duplicates", giv'em a correct "key" again ( 0=>host1, 1=>host2 )
$b = 0;
foreach($hosts as $value) {
$host_name[$b] = $value;
$b++;
}

$ialt = count($host_name);

// Checks if hostnames in $host_name also exist in hosts file.........

$ok_name = array();
$nyfile = file_get_contents($hosts_sti);

    foreach($host_name as $tjek_hostfil_name) {
    $pos = strpos(strtolower($nyfile), $tjek_hostfil_name);
        if($pos !== false) {
        $ok_name[] = $tjek_hostfil_name;
        }
    }

// Contains names present in httdp.conf but not in file hosts
$name_result = array_diff($host_name, $ok_name);

echo"<h3>". $US['vhost-settings'] ."</h3>";
echo"<p>". $US['vhost-text-0'] ." ". $ialt ." ". $US['vhost-text-1'] ." <br />";

if($ialt > 0) {
for($c = 0; $c < $ialt; $c++) {
echo"<a target=\"_new\" href=\"http://". $host_name[$c] ."/\">". $host_name[$c] ."</a><br />";
}
echo"<br />";
}

if(count($name_result) !=0) {
echo"<b>". $US['vhost-text-2'] ."</b> ";
    foreach($name_result as $navn) {
    echo $navn ." ". $US['vhost-dne'] ."";
    }
}
else{
echo"". $US['vhost-text-3'] ."";
}

echo"<h3>". $US['vhost-setup'] ."</h3>";
echo"<p>". $US['vhost-new'] ."";

echo"	
<form action=\"". $_SERVER["PHP_SELF"] ."\" method=\"post\">
<p>". $US['vhost-name'] ." <small>". $US['vhost-new-ex'] ."</small></p>
<input type=\"text\" name=\"host_navn\" class=\"input\" size=\"24\" />
<p>". $US['vhost-path'] ." <small>". $US['vhost-path-ex'] ."</small></p>
<input type=\"text\" name=\"host_path\" class=\"input\" size=\"40\" value=\"". $default_path ."\" />
<p>". $US['vhost-opt'] ." <small>". $US['vhost-opt-ex'] ."</small></p>
<textarea name=\"host_param\" class=\"input\" cols=\"48\" rows=\"8\"></textarea><br />
<input type=\"submit\" value=\"". $US['vhost-make'] ."\" />
\n\n";

echo"</form>\n";

}
else{
echo"<br />\n<span class=\"error\">". $US['vhost-error-1'] ."</span><br />\n";
}

}
else{
echo"<br />\n<span class=\"error\">". $US['vhost-error-2'] ."</span><br />\n";
}

$safe = ini_get('safe_mode');
if(!empty($safe)) {
echo"". $US['vhost-text-4'] ."";
}
?>
</p>
</div>
<p class="copyright"><span class="name"><?=$US['apanel']?> <?=$version?></span> 
| © 2007 <?=$US['dev-team']?> | <a href="http://www.eksperten.dk/artikler/218"><?=$US['vhost-credit']?></a> <? include "includes/code.php"; ?></div>
</body>
</html>
