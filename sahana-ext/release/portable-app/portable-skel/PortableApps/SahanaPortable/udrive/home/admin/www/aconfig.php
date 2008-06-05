<?
/*
####################################################
# Name: The Uniform Server Admin Panel 2.0
# Developed By: The Uniform Server Development Team
# Modified Last By: Olajide Olaolorun (empirex)
# Web: http://www.uniformserver.com
# MPG V0.1 24-6-07 added function mpgUpdateRedirectFile()
# When a user changes Apache port redirection html also updated
####################################################
*/

// Includes
include "includes/config.inc.php";
include "$apanel_path/includes/lang/".file_get_contents("includes/.lang").".php";
include "includes/header.php";
include "includes/secure.php";
?>

<div id="main">
<h2>» <?=$US['aconfig-head']?></h2>
<h3><?=$US['aconfig-conf']?></h3>
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

$apache = new Config ("/usr/local/apache2/conf/httpd.conf","#");
$apache->Var_Name =array ("ServerName","ServerAdmin","DirectoryIndex","AddHandler server-parsed","ServerSignature","Listen");
$apache->Var_Text =array (
"".$US['aconfig-sname']."","".$US['aconfig-wemail']."","".$US['aconfig-difiles']."",
"".$US['aconfig-ssi']."","".$US['aconfig-ssig']."","".$US['aconfig-listen']."");
$apache->Var_Help =array (
"http://httpd.apache.org/docs/mod/core.html#servername",
"http://httpd.apache.org/docs/mod/core.html#serveradmin",
"http://httpd.apache.org/docs/mod/mod_dir.html#directoryindex",
"http://httpd.apache.org/docs/mod/mod_include.html",
"http://httpd.apache.org/docs/mod/core.html#serversignature",
"http://httpd.apache.org/docs/2.0/bind.html");


// import_request_variables("gP", "st");
$step=$HTTP_POST_VARS['Submit'];
if ($step == "next") {
        echo "<p>".$US['aconfig-text-0']."</p>";
}

else {
        if ($step == "Save") {
mpgUpdateRedirectFile();
                $apache->replace_values ($HTTP_POST_VARS);

                echo "<p><font color=\"red\">".$US['aconfig-text-1']."</font><p>";
        }
?>

        <form action="
<?
        echo $_SERVER["PHP_SELF"]."\" name=\"f\" method=\"post\">";
        $apache->echo_values ();
?>
        <br />
        <input type="submit" value="<?=$US['aconfig-save']?>" name="Submit" />
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
//Update file redirect.html to new port number

function mpgUpdateRedirectFile(){
$portnum = $_POST['C1i5'];    // get new port number
if($portnum == 80){           // browser defaults to 80
$portnum="";                 // hence a blank string
}
else{                         // not 80
$portnum= ":".$portnum;      // hence create string with colon and port
}                        

$file = './redirect.html';    // Path to file

$search = '/localhost\/|localhost:[0-9]*\//';    // Search and
$replace = 'localhost'.$portnum.'/'; // Replace strings

$lines = file($file);               // Open file and read content into array
if($lines){                         // file was opened and content read continue
  $fh = fopen($file,'w');           // open file for writing and delete content

  foreach($lines as $line_num => $line) {           // Read through array
    $line = preg_replace($search, $replace, $line); // and update port number
    $line2 = trim($line);                           // clean line and
    fwrite($fh,$line2."\n");                        // write into file add new line
//    echo "$line2";
  }
  fclose($fh);                                     // finished with file so close it
}
else{
echo "failed to open file";
}

}//end function

//---------------------------------------------------------------------
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
                <td width=\"150\"><p>$Var_Text:</p></td>
                <td>
                <p><input type=\"text\" name=\"$Var_ID\" size=\"31\" maxlength=\"2048\" value='$tag[1]' /> ";
            if ($Var_Help != "") {echo "<a href=\"$Var_Help\" target=\"_help\">".$US['aconfig-help']."</a>";};
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