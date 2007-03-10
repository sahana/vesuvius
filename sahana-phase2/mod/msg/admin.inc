<?php
/**
* Sahana Messaging Module
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana
* @subpackage   Messaging
* @tutorial
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_msg_adm_default()
{
    include_once ('admin_settings.inc');
    _shn_kannel_config_setfile();
}

function shn_msg_adm_set()
{
   include_once ('admin_settings.inc');
   if(shn_msg_validate_settings())
   {
      _shn_kannel_config_setfile();
   }
   else
   {
       _shn_kannel_config_savefile();
   }
}

?>
