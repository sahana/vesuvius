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
include "includes/header.php";
include "includes/secure.php";
?>

<div id="main">
<h2>&#187; <?=$US['pconfig-head']?></h2>
<h3><?=$US['pconfig-conf']?></h3>
<?
# -- Determines Apache version.
if (preg_match("/Apache\/2/i", $_SERVER["SERVER_SOFTWARE"])) {
        $Apache2 = True;
}
else {
        $Apache2 = False;
}
# --
 
# -- Determines PHP mode
if (!preg_match("/^cgi/",php_sapi_name())) {
        $PHPmod = True;
}
else {
        $PHPmod = False;
}
# --

$PHP = new Config ("/usr/local/PHP/php.ini",";");
$PHP->Var_Name =array ("safe_mode =","expose_php =", "register_globals =", "max_execution_time =",
"memory_limit =", "display_errors =", "post_max_size =", "upload_max_filesize =");
$PHP->Var_Text =array (
"".$US['pconfig-smode']."","".$US['pconfig-ssig']."", "".$US['pconfig-rg']."",
"".$US['pconfig-mtexec']."","".$US['pconfig-mmexec']."","".$US['pconfig-perror']."",
"".$US['pconfig-mpsize']."","".$US['pconfig-musize']."");
$PHP->Var_Help =array (
"http://php.benscom.com/manual/en/features.safe-mode.php",
"http://www.php.net/manual/en/security.hiding.php#security.hiding",
"http://www.php.net/release_4_1_0.php",
"http://www.php.net/manual/en/configuration.php#ini.max-execution-time",
"http://www.php.net/manual/en/configuration.php#ini.memory-limit",
"http://www.php.net/manual/en/configuration.php#ini.display-errors",
"http://www.php.net/manual/en/features.file-upload.php#features.file-upload.post-method",
"http://www.php.net/manual/en/configuration.php#ini.upload-max-filesize");

//--------------------------------------------------------------------

// import_request_variables("gP", "st");
$step=$HTTP_POST_VARS['Submit'];
if ($step == "next") {
        echo "<p>".$US['pconfig-text-0']."</p>";
}

else {
        if ($step == "Save") {
                $PHP->replace_values ($HTTP_POST_VARS);
                echo "<p><font color=\"red\">".$US['pconfig-text-1']."</font></p>";
        }
?>

        <form action="
<?
        echo $_SERVER["PHP_SELF"]."\" name=\"f\" method=\"post\">";
        $PHP->echo_values ();
?>
        <br />
        <input type="submit" value="<?=$US['pconfig-save']?>" name="Submit" />
        </form>
        <br />
<?
        if ($PHPmod==True) {
                echo "<p><font color=\"red\">".$US['aconfig-module']."</font></p>";
        }

        else {
                echo "<p><font color=\"red\">".$US['aconfig-cgi']."</font></p>";
        }
}

//--------------------------------------------------------------------
class Config
{
var $contents;
var $name;
var $comments;
var $Var_Name;
var $Var_Text;
var $Var_Help;
var $classnum;

function Config ($file_name, $comments)
{
      $this->comments=$comments;
      $this->name=$file_name;
      $fd = fopen ($this->name, "r");
      $this->contents = fread ($fd, filesize ($file_name));
      fclose ($fd);
      $this->classnumber=$GLOBALS["$Configclassnumber"]=$GLOBALS["$Configclassnumber"]+1;
}

function f_write ()
{
      $fd = fopen ($this->name, "w");
      $ok = fwrite ($fd, $this->contents);
      fclose ($fd);
}

function echo_values ()
{
      include "includes/lang/".file_get_contents("includes/.lang").".php";
      echo "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">";
      $item=0;

      foreach ($this->Var_Name as $loop){
            $Var_ID="C".$this->classnumber."i".$item;
            $Var_Name=$this->Var_Name[$item];
            $Var_Text=$this->Var_Text[$item];
            $Var_Help=$this->Var_Help[$item];
            $comments=$this->comments;
            preg_match("/\n\s*$Var_Name\s+([^$comments^\n]+)/i", $this->contents, $tag);
            echo "
                <tr>
                <td width=\"250\"><p>$Var_Text:</p></td>
                <td>
                <p><input type=\"text\" name=\"$Var_ID\" size=\"31\" maxlength=\"2048\" value='$tag[1]' /> ";
            if ($Var_Help != "") {echo "<a href=\"$Var_Help\" target=\"_help\">".$US['pconfig-help']."</a>";};
                echo "</p>";
            echo "</td>";
                echo "</tr>";
            $item=$item+1;
        }

      echo "</table>";
}

function replace_values ($HTTP_POST_VARS)
{
      $item=0;

      foreach ($this->Var_Name as $loop){
            $Var_ID="C".$this->classnumber."i".$item;
            $data=$HTTP_POST_VARS[$Var_ID];
            $comments=$this->comments;
            $this->contents=preg_replace("/\n(\s*$loop)\s+([^$comments]+)/i", "\n\\1 $data\n\n", $this->contents, 1);
            $item=$item+1;
      }

      $this->f_write ();
}
}
?>
</div>

<?
// Footer
include "includes/footer.php";
?>