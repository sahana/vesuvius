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

// items which are checkboxes and the config page basic(1) or ext(2)
$checkbox=array("ftp_use"=>1,"ftp_pasv"=>1,"email_use"=>1,"import_error"=>2,"no_login"=>2,"ftp_del"=>1,"dir_backup"=>2,"dir_rec"=>2,"login"=>2);

// check if all configuration settings are available
// login, stylesheet and lang are checked before
if (!isset($CONF['sitename'])) $CONF['sitename']='';
if (!isset($CONF['ftp_use'])) $CONF['ftp_use']='';
if (!isset($CONF['ftp_server'])) $CONF['ftp_server']='';
if (!isset($CONF['ftp_user'])) $CONF['ftp_user']='';
if (!isset($CONF['sql_passwd'])) $CONF['sql_passwd']='';
if (!isset($CONF['sql_host'])) $CONF['sql_host']='';
if (!isset($CONF['sql_user'])) $CONF['sql_user']='';
if (!isset($CONF['sql_db'])) $CONF['sql_db']='';
if (!isset($CONF['ftp_passwd'])) $CONF['ftp_passwd']='';
if (!isset($CONF['ftp_path'])) $CONF['ftp_path']='';
if (!isset($CONF['ftp_pasv'])) $CONF['ftp_pasv']='';
if (!isset($CONF['ftp_port'])) $CONF['ftp_port']='';
if (!isset($CONF['ftp_del'])) $CONF['ftp_del']='';
if (!isset($CONF['email_use'])) $CONF['email_use']='';
if (!isset($CONF['email'])) $CONF['email']='';
if (!isset($CONF['date'])) $CONF['date']='';
if (!isset($CONF['del_time'])) $CONF['del_time']='';
if (!isset($CONF['del_number'])) $CONF['del_number']='';
if (!isset($CONF['timelimit'])) $CONF['timelimit']='';
if (!isset($CONF['confirm'])) $CONF['confirm']='';
if (!isset($CONF['import_error'])) $CONF['import_error']='';
if (!isset($CONF['no_login'])) $CONF['no_loginxxxx']='';
if (!isset($CONF['dir_backup'])) $CONF['dir_backup']='';
if (!isset($CONF['dir_rec'])) $CONF['dir_rec']='';
    
// if save button was clicked
if (isset($_POST['submit'])) {

    // configurations
    if (isset($_POST['sql_host']) || isset($_POST['del_time'])) {
    
        // first set all check boxes of the selected configuration tab to "0"
        foreach ($checkbox as $item=>$page) {
            // checkboxes on extended configurations
            if ($page=="2" && isset($_GET['ext'])) $CONF[$item]="0";
                // checkboxes on basic configurations
                elseif($page=="1" && !isset($_GET['ext'])) $CONF[$item]="0";
        }
        
        // update $CONF
        foreach($CONF as $item=>$value) {
            // don't save settings for several servers in conf.php
            if ($item=="sql_host_s" || $item=="sql_user_s" || $item=="sql_passwd_s" || $item=="sql_db_s") continue;
            
            // don't save data of settings the user isn't allowed to change
            if ($_SESSION['multi_user_mode']) {
                if ($item=="sitename" && $PMBP_MU_CONF['sitename']) continue;
                if (($item=="email_use"|$item=="email") && !$PMBP_MU_CONF['allow_email']) continue;
                
                if (!$PMBP_MU_CONF['allow_ftp'] && !$PMBP_MU_CONF['allow_dir_backup']) {
                    if ($item=="ftp_server") continue;
                    if ($item=="ftp_user") continue;
                    if ($item=="ftp_passwd") continue;
                    if ($item=="ftp_path") continue;
                    if ($item=="ftp_pasv") continue;
                    if ($item=="ftp_port") continue;
                    if ($item=="ftp_use") continue;
                    if ($item=="dir_backup") continue;
                    if ($item=="dir_rec") continue;
                }
                if ($PMBP_MU_CONF['allow_dir_backup']) {
                    if ($item=="dir_backup") continue;
                    if ($item=="dir_rec") continue;
                }
                if ($PMBP_MU_CONF['allow_ftp']) {
                    if ($item=="ftp_use") continue;
                }                
            }
            
            // check if the value was posted
            if (isset($_POST[$item])) {
                if (isset($checkbox[$item])) {
                    $CONF[$item]=1;
                } else {
                    $CONF[$item]=$_POST[$item];
                }
            }
        }       
           
    // system variables
    } else {
        foreach($_POST as $key=>$value) {
            if ($key!="submit") $PMBP_SYS_VAR[$key]=$value;
        }
    }
    
    // save $CONF to global_conf.php
    if (PMBP_save_global_conf()) {
        $out="<div class=\"green\">".C_SAVED."!</div>\n";
    } else {
        $out="<div class=\"red\">".PMBP_GLOBAL_CONF." ".C_WRITEABLE."!</div>\n";
    }
}


PMBP_print_header(ereg_replace(".*/","",$_SERVER['SCRIPT_NAME']));
if (isset($out)) echo $out;

// validation type of some variables
$validate=array('timelimit'=>"int",'del_time'=>"float",'email'=>"email",'ftp_port'=>"int");
$conf=array(C_TIMELIMIT=>"timelimit",C_FTP_PORT=>"ftp_port",C_DEL_TIME=>"del_time",C_EMAIL=>"email");

// validate
foreach($CONF as $key=>$value) {
    if (array_key_exists($key,$validate)) {
        switch($validate[$key]) {
            case "int": if (!eregi("^[0-9]*$",$value)) echo "<div class=\"red\">'".array_search($key,$conf)."' ".C_WRONG_TYPE."</div>\n";
                break;
            case "float": if (!eregi("^[0-9]*\.?[0-9]*$",$value)) echo "<div class=\"red\">'".array_search($key,$conf)."' ".C_WRONG_TYPE."</div>\n";
                break;
            case "email": if ($value||$CONF['email_use']) {
                    foreach(explode(",",$value) as $value2) {
                        if (!eregi("^\ *[‰ˆ¸ƒ÷‹a-zA-Z0-9_-]+(\.[‰ˆ¸ƒ÷‹a-zA-Z0-9\._-]+)*@([‰ˆ¸ƒ÷‹a-zA-Z0-9-]+\.)+([a-z]{2,4})$",$value2)) {
                            echo "<div class=\"red\">'".array_search($key,$conf)."' ".C_WRONG_TYPE."</div>\n";
                            break;
                        }
                    }
                }
                break;
        }
    }
}

// if no db connection possible
if (isset($_SESSION['sql_host_org'])) {
    if (!@mysql_connect($_SESSION['sql_host_org'],$_SESSION['sql_user_org'],$_SESSION['sql_passwd_org'])) echo "<div class=\"red\">".C_WRONG_SQL."</div>";     
    if ($_SESSION['sql_db_org']) if (!@mysql_select_db($_SESSION['sql_db_org'])) echo "<div class=\"red\">".C_WRONG_DB."</div>";    
} else {
    if (!@mysql_connect($CONF['sql_host'],$CONF['sql_user'],$CONF['sql_passwd'])) echo "<div class=\"red\">".C_WRONG_SQL."</div>";
    if ($CONF['sql_db']) if (!@mysql_select_db($CONF['sql_db'])) echo "<div class=\"red\">".C_WRONG_DB."</div>";
}

// only if 'good internet connection' and if no ftp connection possible
if ($CONF['ftp_use'] || $CONF['dir_backup']) {
	
    if (!$CONF['ftp_server']) {
        echo "<div class=\"red\">".C_WRONG_FTP."</div>";
    // check only if internet connection seems to be good
    } elseif(!$_SESSION['PMBP_VERSION']) {
        if (!$conn_id=@ftp_connect($CONF['ftp_server'],$CONF['ftp_port'],$PMBP_SYS_VAR['ftp_timeout']))
            echo "<div class=\"red\">".C_WRONG_FTP."</div>";
    }
}

// print configuration selection
if (!$_SESSION['multi_user_mode']) {
    if (isset($_GET['ext'])) echo "<div class=\"bold\"><a href=\"config.php\">".C_BASIC_VAL."</a> | ".C_EXT_VAL." | <a href=\"config.php?sys=TRUE\">".PMBP_C_SYSTEM_VAL."</a></div>";
        elseif(isset($_GET['sys'])) echo "<div class=\"bold\"><a href=\"config.php\">".C_BASIC_VAL."</a> | <a href=\"config.php?ext=TRUE\">".C_EXT_VAL."</a> | ".PMBP_C_SYSTEM_VAL."</div>\n";
            else echo "<div class=\"bold\">".C_BASIC_VAL." | <a href=\"config.php?ext=TRUE\">".C_EXT_VAL."</a> | <a href=\"config.php?sys=TRUE\">".PMBP_C_SYSTEM_VAL."</a></div>\n";
}

// print html code
if (isset($_GET['ext'])) echo "<br><form action=\"config.php?ext=TRUE\" method=\"post\">\n";
    elseif(isset($_GET['sys'])) echo "<br><form action=\"config.php?sys=TRUE\" method=\"post\">\n";
        else echo "<br><form action=\"config.php\" method=\"post\">\n";
echo "<table border=\"0\" cellspacing=\"2\" cellpadding=\"1\" width=\"100%\">\n";

if ($_SESSION['multi_user_mode']) {
    // configurations in mu user mode
    echo "<tr>";
    echo "<td colspan=\"8\">&nbsp;</td></tr><tr>";
    echo "<td>".C_LANG."*:</td><td>".PMBP_config_print("lang")."</td>\n";
    echo "<td>".C_DATE."*:</td><td>".PMBP_config_print("date")."</td>\n";      
    echo "<td>".C_STYLESHEET."*:</td><td>".PMBP_config_print("stylesheet")."</td>\n";      
    if (!$PMBP_MU_CONF['sitename']) {
        echo "<td>".C_SITENAME."*:</td><td>".PMBP_config_print("sitename")."</td>\n";
    } else {
        echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    }    
    echo "</tr><tr>";  
    if ($PMBP_MU_CONF['allow_email']) {
        echo "<td><br><div class=\"bold_left\">".C_TITLE_DELETE."</div></td><td colspan=\"3\"><br><hr></td>\n";    
        echo "<td><br><div class=\"bold_left\">".C_TITLE_EMAIL."</div></td><td colspan=\"3\"><br><hr></td>\n";        
    } else {
        echo "<td><br><div class=\"bold_left\">".C_TITLE_DELETE."</div></td><td colspan=\"7\"><br><hr></td>\n";
    }
    echo "</tr><tr>";
    echo "<td>".C_DEL_TIME.":</td><td>".PMBP_config_print("del_time")."</td>\n";
    echo "<td>".C_DEL_NUMBER.":</td><td>".PMBP_config_print("del_number")."</td>\n";
    if ($PMBP_MU_CONF['allow_email']) {    
        echo "<td>".C_EMAIL_USE.":</td><td>".PMBP_config_print("email_use")."</td>\n";
        echo "<td>".C_EMAIL.":</td><td>".PMBP_config_print("email")."</td>\n";
    } else {
        echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
        echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    }
    echo "</tr><tr>";
    if ($PMBP_MU_CONF['allow_ftp'] || $PMBP_MU_CONF['allow_dir_backup']) {
        echo "<td><br><div class=\"bold_left\">".C_TITLE_FTP."</div></td><td colspan=\"7\"><br><hr></td>\n";
        echo "</tr><tr>";
        if ($PMBP_MU_CONF['allow_ftp']) {
            echo "<td>".C_FTP_USE.":</td><td>".PMBP_config_print("ftp_use")."</td>\n";
        } else {
            echo "<td>&nbsp;</td><td>&nbsp;</td>\n";    
        }
        echo "<td>".C_FTP_SERVER.":</td><td>".PMBP_config_print("ftp_server")."</td>\n";
        echo "<td>".C_FTP_USER.":</td><td>".PMBP_config_print("ftp_user")."</td>\n";
        echo "<td>".C_FTP_PASSWD.":</td><td>".PMBP_config_print("ftp_passwd")."</td>\n";
        echo "</tr><tr>";
        echo "<td>".C_FTP_PATH.":</td><td>".PMBP_config_print("ftp_path")."</td>\n";
        echo "<td>".C_FTP_PASV.":</td><td>".PMBP_config_print("ftp_pasv")."</td>\n";
        echo "<td>".C_FTP_PORT.":</td><td>".PMBP_config_print("ftp_port")."</td>\n";
        echo "<td>".C_FTP_DEL.":</td><td>".PMBP_config_print("ftp_del")."</td>\n";
        echo "</tr><tr>";
    }
    echo "<td><br><div class=\"bold_left\">".C_TITLE_CONFIG."</div></td><td colspan=\"7\"><br><hr></td>\n";
    echo "</tr><tr>";
    echo "<td>".C_TIMELIMIT." (".F_SECONDS.")*:</td><td>".PMBP_config_print("timelimit")."</td>\n";
    echo "<td>".C_CONFIRM."*:</td><td>".PMBP_config_print("confirm")."</td>\n";
    if ($PMBP_MU_CONF['allow_dir_backup']) {    
    echo "<td>".C_DIR_BACKUP.":</td><td>".PMBP_config_print("dir_backup")."</td>\n";
    echo "<td>".C_DIR_REC.":</td><td>".PMBP_config_print("dir_rec")."</td>\n";
    } else {
        echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
        echo "<td>&nbsp;</td><td>&nbsp;</td>\n";    
    }
    echo "</tr>";
} elseif (isset($_GET['ext'])) {
    echo "<tr>";
    echo "<td><br><div class=\"bold_left\">".C_TITLE_STYLE."</div></td><td colspan=\"7\"><br><hr></td>\n";
    echo "</tr><tr>";
    echo "<td>".C_STYLESHEET."*:</td><td>".PMBP_config_print("stylesheet")."</td>\n";
    echo "<td>".C_DATE."*:</td><td>".PMBP_config_print("date")."</td>\n";
    echo "<td>".C_LOGIN."*:</td><td>".PMBP_config_print("login")."</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "</tr><tr>";
    echo "<td><br><div class=\"bold_left\">".C_TITLE_DELETE."</div></td><td colspan=\"7\"><br><hr></td>\n";
    echo "</tr><tr>";
    echo "<td>".C_DEL_TIME.":</td><td>".PMBP_config_print("del_time")."</td>\n";
    echo "<td>".C_DEL_NUMBER.":</td><td>".PMBP_config_print("del_number")."</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "</tr><tr>";
    echo "<td><br><div class=\"bold_left\">".C_TITLE_CONFIG."</div></td><td colspan=\"7\"><br><hr></td>\n";
    echo "</tr><tr>";
    echo "<td>".C_TIMELIMIT." (".F_SECONDS.")*:</td><td>".PMBP_config_print("timelimit")."</td>\n";
    echo "<td>".C_CONFIRM."*:</td><td>".PMBP_config_print("confirm")."</td>\n";
    echo "<td>".C_IMPORT_ERROR.":</td><td>".PMBP_config_print("import_error")."</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "</tr><tr>";
    echo "<td>".C_DIR_BACKUP.":</td><td>".PMBP_config_print("dir_backup")."</td>\n";
    echo "<td>".C_DIR_REC.":</td><td>".PMBP_config_print("dir_rec")."</td>\n";
    echo "<td>[".C_NO_LOGIN.":</td><td>".PMBP_config_print("no_login")."]</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "</tr>";
} elseif(isset($_GET['sys'])) {
    echo "<div class=\"red\">".PMBP_C_SYS_WARNING."</div><br>";
    $i=0;
    foreach($PMBP_SYS_VAR as $key=>$value) {            
        if ($i%2==0) echo "<tr>\n";
        echo "<td colspan=\"2\">".$key.":</td><td colspan=\"2\"><input type=\"text\" size=\"20\" name=\"".$key."\" value=\"".$value."\"></td>\n";
        if ($i%2==1) echo "</tr>";
        $i++;
    }
    if ($i%2) echo "</tr>\n";
} else {
    echo "<tr>";
    echo "<td colspan=\"8\">&nbsp;</td></tr>";
    echo "<tr><td>".C_SITENAME."*:</td><td>".PMBP_config_print("sitename")."</td>\n";
    echo "<td>".C_LANG."*:</td><td>".PMBP_config_print("lang")."</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "</tr><tr>";
    echo "<td><br><div class=\"bold_left\">".C_TITLE_SQL."</div></td><td colspan=\"7\"><br><hr></td>\n";
    echo "</tr><tr>";
    echo "<td>".C_SQL_HOST."*:</td><td>".PMBP_config_print("sql_host")."</td>\n";
    echo "<td>".C_SQL_USER."*:</td><td>".PMBP_config_print("sql_user")."</td>\n";
    echo "<td>".C_SQL_PASSWD."*:</td><td>".PMBP_config_print("sql_passwd")."</td>\n";
    echo "<td>".C_SQL_DB.":</td><td>".PMBP_config_print("sql_db")."</td>\n";
    echo "</tr><tr>";
    echo "<td><br><div class=\"bold_left\">".C_TITLE_FTP."</div></td><td colspan=\"7\"><br><hr></td>\n";
    echo "</tr><tr>";
    echo "<td>".C_FTP_USE.":</td><td>".PMBP_config_print("ftp_use")."</td>\n";
    echo "<td>".C_FTP_SERVER.":</td><td>".PMBP_config_print("ftp_server")."</td>\n";
    echo "<td>".C_FTP_USER.":</td><td>".PMBP_config_print("ftp_user")."</td>\n";
    echo "<td>".C_FTP_PASSWD.":</td><td>".PMBP_config_print("ftp_passwd")."</td>\n";
    echo "</tr><tr>";
    echo "<td>".C_FTP_PATH.":</td><td>".PMBP_config_print("ftp_path")."</td>\n";
    echo "<td>".C_FTP_PASV.":</td><td>".PMBP_config_print("ftp_pasv")."</td>\n";
    echo "<td>".C_FTP_PORT.":</td><td>".PMBP_config_print("ftp_port")."</td>\n";
    echo "<td>".C_FTP_DEL.":</td><td>".PMBP_config_print("ftp_del")."</td>\n";
    echo "</tr><tr>";
    echo "<td><br><div class=\"bold_left\">".C_TITLE_EMAIL."</div></td><td colspan=\"7\"><br><hr></td>\n";
    echo "</tr><tr>";
    echo "<td>".C_EMAIL_USE.":</td><td>".PMBP_config_print("email_use")."</td>\n";
    echo "<td>".C_EMAIL.":</td><td>".PMBP_config_print("email")."</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "<td>&nbsp;</td><td>&nbsp;</td>\n";
    echo "</tr>";
}

echo "<tr><td colspan=\"8\">\n<input name=\"submit\" type=\"submit\" value=\"".C_SAVE."\" class=\"button\"></td></tr>\n</table>\n</form>";
PMBP_print_footer();


// two functions only used in config.php

// returns the html code for the different configuration items and controls
function PMBP_config_print($item) {
    global $CONF;
    
    // vars whos type is checkbox, password, select or a filelist
    global $checkbox;
    $password=array("sql_passwd","ftp_passwd");
    $select['confirm']=array(C_CONFIRM_1,C_CONFIRM_2,C_CONFIRM_3,C_CONFIRM_4);
    $time=time();
    $select['date']=array(BD_DATE_FORMAT=>strftime(BD_DATE_FORMAT,$time),
        "%x %X"=>strftime("%x %X",$time),"%x %H:%M"=>strftime("%x %H:%M",$time),
        "%m/%d/%y %X"=>strftime("%m/%d/%y %X",$time),"%m/%d/%y %H:%M"=>strftime("%m/%d/%y %H:%M",$time),
        "%b %d %Y %X"=>strftime("%b %d %Y %X",$time),"%b %d %Y %H:%M"=>strftime("%b %d %Y %H:%M",$time),
        "%Y/%m/%d %X"=>strftime("%Y/%m/%d %X",$time),"%Y/%m/%d %H:%M"=>strftime("%Y/%m/%d %H:%M",$time));
    $filelist['lang']=array(PMBP_LANGUAGE_DIR,".inc.php");
    $filelist['stylesheet']=array(PMBP_STYLESHEET_DIR,".css");

    // create the html code
    if (isset($checkbox[$item])) {
        if ($CONF[$item]) $status=" checked"; else $status=" ";        
        $out="<input type=\"checkbox\" name=\"".$item."\" value=\"".$CONF[$item]."\"".$status.PMBP_config_disable($item).">";
    } elseif (in_array($item,$password)) {
        $out="<input type=\"password\" size=\"10\" name=\"".$item."\" value=\"".$CONF[$item]."\"".PMBP_config_disable($item).">";
    } elseif (isset($select[$item])) {
        $out="<select name=\"".$item."\"".PMBP_config_disable($item).">\n";
        foreach($select[$item] as $opt_no=>$print_value)
            if ($opt_no==$CONF[$item]) $out.="<option value=\"".$opt_no."\" selected>".$print_value."</option>\n";
                else $out.="<option value=\"".$opt_no."\">".$print_value."</option>\n";
        $out.="</select>";
    } elseif(isset($filelist[$item])) {
        $files=FALSE;
        $handle=opendir("./".$filelist[$item][0]);
        while ($file=readdir($handle))
            if (substr($file,-(strlen($filelist[$item][1])),strlen($filelist[$item][1]))==$filelist[$item][1])
                $files[]=substr($file,0,strlen($file)-strlen($filelist[$item][1]));
        $out="<select name=\"".$item."\">\n";
        foreach($files as $file)
            if ($file==$CONF[$item]) $out.="<option value=\"".$file."\" selected>".$file."</option>\n"; else $out.="<option value=\"".$file."\">".$file."</option>\n";
        $out.="</select>";
    } else {
        $out="<input type=\"text\" size=\"10\" name=\"".$item."\" value=\"".$CONF[$item]."\"".PMBP_config_disable($item)."><br>";
    }
    return $out;
}

// checks if a item should be disabled and returns the code to disable it
function PMBP_config_disable($item) {
    global $CONF;
    global $PMBP_SYS_VAR;
    global $PMBP_MU_CONF;
    
    // availability check for some functions
    $disable=array('ftp_use'=>"!function_exists(\"ftp_connect\")",'ftp_server'=>"!function_exists(\"ftp_connect\")",
        'ftp_user'=>"!function_exists(\"ftp_connect\")",'ftp_passwd'=>"!function_exists(\"ftp_connect\")",
        'ftp_path'=>"!function_exists(\"ftp_connect\")",'ftp_pasv'=>"!function_exists(\"ftp_connect\")",
        'ftp_port'=>"!function_exists(\"ftp_connect\")",'email_use'=>"!function_exists(\"mail\")",'email'=>"!function_exists(\"mail\")",
        'no_login'=>($_SESSION['multi_user_mode'] || $CONF['login'])?1:0,
        'timelimit'=>"ini_get(\"safe_mode\")");

    // disable selected items due to system restrictions
    $out="";
    if (isset($disable[$item])) {
        if (eval("return(".$disable[$item].");")) $out=" disabled";
        // special case 'timelimit'
        if ($item=="timelimit" && $out) {
            $timelimit=ini_get("max_execution_time");
            if ($CONF['timelimit']!=$timelimit) {
                $CONF['timelimit']=$timelimit;
                PMBP_save_global_conf();
            }
        }
    }
    return $out;
}
?>
