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

// set the timelimit
@set_time_limit($CONF['timelimit']);

// show the requested file
if (isset($_GET['view']) && file_exists($_GET['view'])) {
    if (isset($_GET['download'])) {
        header("Content-Type: application/octet-stream");
        header("Content-Disposition: attachment; filename=".basename($_GET['view']));
        readfile($_GET['view']);
    } else {
        echo "<pre>";
        while($line=PMBP_getln($_GET['view'])) echo htmlentities($line);
        PMBP_getln($_GET['view'],true);
        echo "</pre>";
    }
} else {
	if (isset($_GET['view'])) echo $_GET['view']." ".F_MAIL_3."!";
}
?>
