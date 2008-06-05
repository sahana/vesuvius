<?php
/*
 +--------------------------------------------------------------------------+
 | phpMyBackupPro                                                           |
 +--------------------------------------------------------------------------+
 | Copyright (c) 2004-2007 by Dirk Randhahn                                 |                               
 | http://www.phpMyBackupPro.net                                            |
 | version information can be found in definitions.php.                     |
 |                                                                          |
 | This program is free software; you can redistribute it and/or            |
 | modify it under the terms of the GNU General Public License              |
 | as published by the Free Software Foundation; either version 2           |
 | of the License, or (at your option) any later version.                   |
 |                                                                          |
 | This program is distributed in the hope that it will be useful,          |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of           |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            |
 | GNU General Public License for more details.                             |
 |                                                                          |
 | You should have received a copy of the GNU General Public License        |
 | along with this program; if not, write to the Free Software              |
 | Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,USA.|
 +--------------------------------------------------------------------------+
*/

require_once("login.php");

// used variables
if (!isset($_POST['db'])) $_POST['db']=FALSE;
if (!isset($_POST['tables'])) $_POST['tables']=FALSE;
if (!isset($_POST['data'])) $_POST['data']=FALSE;
if (!isset($_POST['zip'])) $_POST['zip']=FALSE;
if (!isset($_POST['drop'])) $_POST['drop']=FALSE;
if (!isset($_POST['man_dirs'])) $_POST['man_dirs']=FALSE;
if (!isset($_POST['comments'])) $_POST['comments']=FALSE;
if (!isset($_POST['packed'])) $_POST['packed']=FALSE;

PMBP_print_header(ereg_replace(".*/","",$_SERVER['SCRIPT_NAME']));

// if first use or no db-connection possible
if (!@mysql_connect($CONF['sql_host'],$CONF['sql_user'],$CONF['sql_passwd'])) echo "<div class=\"red\">".I_SQL_ERROR."</div><br>";

// check if a db or directory was posted
if (isset($_POST['dirs'])) {
    if (is_array($_POST['db']) || is_array($_POST['dirs']) || $_POST['man_dirs']) $selection_ok=TRUE;
        else $selection_ok=FALSE;
} elseif($_POST['man_dirs']) {
    $selection_ok=TRUE;
} elseif(isset($_POST['db'])) {
    if (is_array($_POST['db'])) $selection_ok=TRUE;
        else $selection_ok=FALSE;
} elseif(isset($_POST)) {
    $selection_ok=FALSE;
}

// generate and print php script
if ($selection_ok) {

    // create path to run_scheduled.php
    $path_back="";
    if (strstr($_SERVER['SCRIPT_NAME'],"\\")) $delimiter="\\"; else $delimiter="/";
    $script_path=explode($delimiter,$_SERVER['SCRIPT_NAME']);
    $path_d=count(explode("..",$_POST['path']))-1;
    $path_u=count(explode($delimiter,$_POST['path']))-$path_d-1;
    for ($i=0;$i<$path_u;$i++) $path_back.="../";
    for ($i=count($script_path)-$path_d-1;$i<count($script_path)-1;$i++) $path_back.=$script_path[$i]."/";

    // set sql server in multi server mode
    if (count($CONF['sql_passwd_s'])) {
        if ($CONF['sql_host']==$_SESSION['sql_host_org'] && $CONF['sql_user']==$_SESSION['sql_user_org']) {
            $_POST['mysql_host']=-1;
        } else {
            for($i=0;$i<count($CONF['sql_passwd_s']);$i++) {
                if ($CONF['sql_host']==$CONF['sql_host_s'][$i] && $CONF['sql_user']==$CONF['sql_user_s'][$i]) $_POST['mysql_host']=$i;
            }
        }
    }
    
    // generate the dynamic php script
    $result="<?php\n";
    $result.="// This code was created by phpMyBackupPro ".PMBP_VERSION." \n// ".PMBP_WEBSITE."\n";

    // list dbs
    if (is_array($_POST['db'])) {
        $result.="\$_POST['db']=array(";
        foreach($_POST['db'] as $value) $result.="\"".$value."\", ";
        $result.=");\n";
    }

    // list directories
    if (isset($_POST['dirs'])) {
        $result.="\$_POST['dirs']=array(";
        foreach($_POST['dirs'] as $value) $result.="\"".$value."\", ";
        $result.=");\n";
    }

    // print the backup options
    foreach($_POST as $key=>$value) {
        $value=str_replace("\"","'",$value);
        if ($key!="period" && $key!="path" && $key!="db" && $key!="dirs" && $key!="filename" && $value!='')
            $result.="\$_POST['".$key."']=\"".$value."\";\n";
    }
    
    // print the current working database (but always only once)
    if(isset($_SESSION['wss']) && !isset($_POST['mysql_host'])) $result.="\$_POST['mysql_host']=\"".$_SESSION['wss']."\";\n";    

    // add include(backup.php) to do all the work
    $result.="\$period=(3600*24)".$_POST['period'].";\n";
    $result.="\$security_key=\"".($PMBP_SYS_VAR['security_key'])."\";\n";
    $result.="// This is the relative path to the phpMyBackupPro ".PMBP_VERSION." directory\n";
    if ($path_back) $result.="@chdir(\"".$path_back."\");\n";
    $result.="@include(\"backup.php\");\n";
    $result.="?>";

    // show the generated php script
    printf(PMBP_EXS_INCL,$_POST['path']."???.php");
    echo ":\n<br><textarea name=\"code\" rows=\"16\" cols=\"120\" readOnly>".$result."</textarea>\n<br><br>";
    echo "<form name=\"save\" action=\"scheduled.php\" method=\"post\">\n";    
    
    // list all post variables as hidden fields
    foreach($_POST as $key=>$value) {
        if ($key!="db" && $key!="dirs") echo "<input type=\"hidden\" name=\"".$key."\" value=\"".$value."\">\n";
            elseif(is_array($_POST[$key])) foreach($value as $dbname) echo "<input type=\"hidden\" name=\"".$key."[]\" value=\"".$dbname."\">\n";
    }

    // save file including the backup script
    if (isset($_POST['filename'])) {		
        if (PMBP_save_to_file($_POST['path'].$_POST['filename'],"",$result,"w")) {
            echo "<span class=\"green_left\">".EX_SAVED." ".PMBP_pop_up($_POST['path'].$_POST['filename'],$_POST['path'].$_POST['filename'],"scheduled")."</span><br>\n";
                
            // save specific settings for scheduled backups
            if ($PMBP_SYS_VAR['EXS_scheduled_file']!=$_POST['filename']) {            
                $PMBP_SYS_VAR['EXS_scheduled_file']=$_POST['filename'];        
            }
                        
        } else {
            echo "<span class=\"red_left\">".C_WRITE." ".$_POST['path'].$_POST['filename']."</span><br>\n";
        }
    }
    echo PMBP_EXS_SAVE.":<br>\n";
    echo $_POST['path']."<input type=\"text\" name=\"filename\" value=\"".$PMBP_SYS_VAR['EXS_scheduled_file']."\">&nbsp;";
    echo "<input type=\"submit\" value=\"".C_SAVE."\">";
    if ($PMBP_SYS_VAR['EXS_scheduled_file']!="???.php")
        echo " (<a href=\"\">".PMBP_pop_up("get_file.php?view=".$_POST['path'].$PMBP_SYS_VAR['EXS_scheduled_file'],B_VIEW,"view")."</a>)";
    echo "</form>";
    echo "\n<a href=\"scheduled.php\"> <- ".EXS_BACK."</a>\n";

    // update specific settings for scheduled backups
    if ($_POST['path']!=$PMBP_SYS_VAR['EXS_scheduled_dir'] OR $_POST['period']!=$PMBP_SYS_VAR['EXS_period']) {            
        $PMBP_SYS_VAR['EXS_scheduled_dir']=$_POST['path'];
        $PMBP_SYS_VAR['EXS_period']=$_POST['period'];
    }
    
    // save PMBP_SYS_VARS
    PMBP_save_export_settings();
                
// print instructions and export form
} else {
    if (isset($selection_ok) && isset($_POST['period'])) echo "<div class=\"red\">".EX_NO_DB."!</div>";

    echo "<form name=\"backup\" action=\"scheduled.php\" method=\"post\">\n<div>\n";
    echo EXS_PERIOD.":<br>\n";
    echo "<select name=\"period\">\n";
    if($PMBP_SYS_VAR['EXS_period']=="*0") $selected=" selected"; else $selected="";
    echo "<option value=\"*0\"".$selected.">".PMBP_EXS_ALWAYS."</option>\n";
    echo "<option>---------------------</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="/24") $selected=" selected"; else $selected="";
    echo "<option value=\"/24\"".$selected.">1 ".EXS_HOUR."</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="/4") $selected=" selected"; else $selected="";
    echo "<option value=\"/4\"".$selected.">6 ".EXS_HOURS."</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="/2") $selected=" selected"; else $selected="";
    echo "<option value=\"/2\"".$selected.">12 ".EXS_HOURS."</option>\n";
    echo "<option>---------------------</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*1") $selected=" selected"; else $selected="";
    echo "<option value=\"*1\"".$selected.">1 ".EXS_DAY."</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*2") $selected=" selected"; else $selected="";
    echo "<option value=\"*2\"".$selected.">2 ".EXS_DAYS."</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*3") $selected=" selected"; else $selected="";
    echo "<option value=\"*3\"".$selected.">3 ".EXS_DAYS."</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*5") $selected=" selected"; else $selected="";
    echo "<option value=\"*5\"".$selected.">5 ".EXS_DAYS."</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*10") $selected=" selected"; else $selected="";
    echo "<option value=\"*10\"".$selected.">10 ".EXS_DAYS."</option>\n";
    echo "<option>---------------------</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*7") $selected=" selected"; else $selected="";
    echo "<option value=\"*7\"".$selected.">1 ".EXS_WEEK."</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*14") $selected=" selected"; else $selected="";
    echo "<option value=\"*14\"".$selected.">2 ".EXS_WEEKS."</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*21") $selected=" selected"; else $selected="";
    echo "<option value=\"*21\"".$selected.">3 ".EXS_WEEKS."</option>\n";
    echo "<option>---------------------</option>\n";
    if($PMBP_SYS_VAR['EXS_period']=="*30") $selected=" selected"; else $selected="";
    echo "<option value=\"*30\"".$selected.">1 ".EXS_MONTH." (30 ".EXS_DAYS.")</option>\n";
    echo "</select>\n<br><br>";

    // get content of these directories (I know, it's partly redundant - but I think this is necessary)
    if ($_SESSION['multi_user_mode']) {
        $search_path1=$PMBP_MU_CONF['user_export_dir'];
        $search_path2=$PMBP_MU_CONF['user_scheduled_dir'];
     } else {
        $search_path1="../";
        $search_path2="../../";
    }
    if ($PMBP_SYS_VAR['dir_lists']>=1) {
        $dirs1=PMBP_get_dirs($search_path1);
    }
    if ($PMBP_SYS_VAR['dir_lists']>=2) {
        $dirs2=PMBP_get_dirs($search_path2);
    }    

    echo EXS_PATH.": (<a href=\"scheduled.php?update_dir_list=TRUE\">".PMBP_EXS_UPDATE_DIRS."</a>)<br>\n";
    echo "<select name=\"path\">\n";
    echo "      <option value=\"\" selected>./</option>\n";
    if (isset($dirs1)) {
        foreach($dirs1 as $value) {
            if ($PMBP_SYS_VAR['EXS_scheduled_dir']==$search_path1.$value) {
                echo "<option value=\"".$search_path1.$value."\" selected>".$search_path1.$value."</option>\n";
            } else {
                echo "<option value=\"".$search_path1.$value."\">".$search_path1.$value."</option>\n";
            }
        }
    }
    echo "<option value=\"\">----------------------------</option>\n";
    if (isset($dirs2)) {
        foreach($dirs2 as $value) {
            if ($PMBP_SYS_VAR['EXS_scheduled_dir']==$search_path1.$value) {
                echo "<option value=\"".$search_path2.$value."\" selected>".$search_path2.$value."</option>\n";
            } else {
                echo "<option value=\"".$search_path2.$value."\">".$search_path2.$value."</option>\n";
            }        
        }
    }
    echo "</select>\n<br><br>";

    // include the export form (known from the export page) and submitt the file list
    if (isset($dirs1)) PMBP_print_export_form($dirs1); else PMBP_print_export_form();
    echo "\n<input type=\"submit\" value=\"".EXS_SHOW."\" class=\"button\">\n</div>\n</form>";
}

PMBP_print_footer();
?>
