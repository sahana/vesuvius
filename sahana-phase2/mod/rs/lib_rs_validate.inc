<?php
/**
 * rs lib validate
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

function shn_rs_validate_sample_report()
{
$error_flag=false;
clean_errors();

    //this checks whether name entered in the add unit form
    if(trim($_POST['rep_file_name'])==null)
    {
    add_error(_("Enter the File Name"));
    $error_flag=true;
    }

 if(trim($_POST['report_type'])==null || trim($_POST['report_type'])=='none')
    {
    add_error(_("Select the report type to continue"));
    $error_flag=true;
    }

  if(trim($_POST['file_type'])==null || trim($_POST['file_type'])=='none')
    {
    add_error(_("Select the file type to continue"));
    $error_flag=true;
    }

    return $error_flag;
}


function shn_rs_validate_search_reports()
{
$error_flag=false;
clean_errors();

    if(trim($_POST['search_type'])==null || trim($_POST['search_type'])=='none')
    {
    add_error(_("Select the Search type"));
    $error_flag=true;
    }

    return $error_flag;
}
?>