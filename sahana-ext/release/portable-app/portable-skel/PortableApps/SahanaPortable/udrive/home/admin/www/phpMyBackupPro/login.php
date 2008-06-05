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

@session_start();

// get password and username
require_once("definitions.php");
// login with http authentification
if ($CONF['login'] && !$_SESSION['multi_user_mode']) {
    if (!isset($_SERVER['PHP_AUTH_USER'])
    || (isset($_GET["login"]) && !($_SERVER['PHP_AUTH_USER']==$CONF['sql_user'] && $_SERVER['PHP_AUTH_PW']==$CONF['sql_passwd']))
    || (isset($_GET["logout"]) && $_SERVER['PHP_AUTH_PW']==$CONF['sql_passwd'])) {
        header("WWW-Authenticate: Basic realm=\"phpMyBackupPro\"");
        header("HTTP/1.0 401 Unauthorized");
        echo LI_NOT_LOGED_OUT;
        echo ": <a href=\"index.php?logout=TRUE\">".F_LOGOUT."</a><br>";
        echo LI_MSG.": <a href=\"index.php?login=TRUE\">".LI_LOGIN."</a>";
        exit;
    } else if ($_SERVER['PHP_AUTH_PW']!=$CONF['sql_passwd']) {
        echo LI_LOGED_OUT."<br>\n".LI_MSG;
        echo ": <a href=\"index.php?login=TRUE\">".LI_LOGIN."</a>";
        unset($_SESSION['LOGGED_IN']);
        unset($_SESSION['sql_host_org']);
        unset($_SESSION['sql_user_org']);
        unset($_SESSION['sql_passwd_org']);
        @session_destroy();
        exit;
    }
    
    // login with html authentification
} else {

    // disable login functions if $CONF['no_login'] is true
    if ($CONF['no_login']!="1") {
        if (!isset($_SESSION['LOGGED_IN'])) $_SESSION['LOGGED_IN']=FALSE;    

        // not logged in
        if (!$_SESSION['LOGGED_IN']) {
            if (!isset($_POST['password'])) $_POST['password']=FALSE;
            if (!isset($_POST['username'])) $_POST['username']=FALSE;            

            // distinguish between multi and single user mode
            if ($_SESSION['multi_user_mode'])
            {
                $con=@mysql_connect($PMBP_MU_CONF['sql_host_admin'],$PMBP_MU_CONF['sql_user_admin'],$PMBP_MU_CONF['sql_passwd_admin']);
                mysql_select_db("mysql");
                $res=mysql_query("select * from user where (User='".$_POST['username']."' or User='') and password=password('".$_POST['password']."')");
                $success=mysql_fetch_array($res);
                @mysql_close($con);
            } else {
                if ($CONF['sql_user']==$_POST['username'] && $CONF['sql_passwd']==$_POST['password']) {
                    $success=TRUE;
                } else {
                    $success=FALSE;
                }
            }
            // was the login successful
            if($success) {
                // login successful - set "LOGGED_IN"-bit
	            $_SESSION['LOGGED_IN']=TRUE;
	            $_GET['login']=TRUE;                

                // just make these settings for the first page after login, because definitions.php was already loaded
                $_SESSION['sql_user']=$_POST['username'];
                $_SESSION['sql_passwd']=$_POST['password'];
                $_SESSION['sql_host']=$PMBP_MU_CONF['sql_host_admin'];
                $CONF['sql_user']=$_SESSION['sql_user'];
                $CONF['sql_passwd']=$_SESSION['sql_passwd'];
                $CONF['sql_host']=$_SESSION['sql_host'];
                $CONF['sql_db']="";                
	        } else {
                // login failed - print login form
                ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
   "http://www.w3.org/TR/html4/loose.dtd">
<html<?php echo ARABIC_HTML;?>>
<head>
<meta http-equiv="Content-Type" content="text/html;charset=<?php echo BD_CHARSET_HTML;?>">
<link rel="stylesheet" href="<?php echo PMBP_STYLESHEET_DIR.$CONF['stylesheet'];?>.css" type="text/css">
<title>phpMyBackupPro</title>
</head>
<body onLoad="document.login.username.focus()">
<form name="login" action="" method="POST">
<table width="400">
  <tr>
    <th colspan="2" class="active">
<?php
echo PMBP_image_tag("logo.png","phpMyBackupPro","http://www.phpMyBackupPro.net","http://www.phpMyBackupPro.net");
?>
    </th>
  </tr>
  <tr>
    <td colspan="2"><?php echo LI_MSG; ?>:</td>
  </tr>
  <tr>
    <td><?php echo LI_USER; ?>:</td>
    <td><input type="text" name="username"></td>
  </tr>
  <tr>
    <td><?php echo LI_PASSWD; ?>:</td>
    <td><input type="password" name="password"></td>
  </tr>
  <tr>
    <td colspan="2"><input type="submit" name="login" value="<?php echo LI_LOGIN; ?>" class="button"></td>
  </tr>
</table>
</form>
</body>
</html>
	            <?php
	            $CONF="";
	            
	            // break loading page if not logged in
	            exit;
	        }
	    }
	
	    // logout
	    if (isset($_GET['logout'])) {
	        @session_start();
	        unset($_SESSION['PMBP_VERSION']);
	        unset($_SESSION['LOGGED_IN']);
	        unset($_SESSION['sql_host_org']);
	        unset($_SESSION['sql_user_org']);
	        unset($_SESSION['sql_passwd_org']);
	        unset($_SESSION['sql_user']);
	        unset($_SESSION['sql_passwd']);
            unset($_SESSION['file_system']);
	        header("Location: index.php");
	        exit;
	    }

    // when login functions is disabled
    } else {
        $_SESSION['LOGGED_IN']="Login deactivated!";
    }
} // end type of auth
?>
