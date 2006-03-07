<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package
* @subpackage
* @tutorial
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


_shn_rms_show_headder(_("Search for a Request"));

function _shn_rms_get_kword()
{
    __shn_rms_schkword();
    __req_id_form();
}

function __shn_rms_schkword()
{
	shn_form_fopen("sc_req",null,array('req_message'=>false));

    shn_form_hidden(array('seq'=>'req_sch'));

    shn_form_fsopen(_("Search For Requests"));
    shn_form_text(_("Enter Search Keyword"),'kword',null,array('br'=>false));
    shn_form_submit(_("Search"));
    shn_form_fsclose();
    shn_form_fclose();
}

function __req_id_form()
{
	shn_form_fopen("v_req",null,array('req_message'=>false));
    shn_form_fsopen(_("View Request by ID"));
    shn_form_hidden(array('seq'=>'view'));
    shn_form_text(_("Enter Request ID"),'req_id',null,array('br'=>false));
    shn_form_submit(_("View Request"));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_rms_get_res($word)
{
    global $global;

    $sql = "SELECT * FROM rms_request " .
            "WHERE LOWER(name) LIKE LOWER('%$word%') " .
            "OR LOWER(site_name) LIKE LOWER('%$word%') " .
            "OR LOWER(site_address) LIKE LOWER('%$word%')";

    $rs = $global['db']->Execute($sql);

    if ($global['db']->ErrorMsg())
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
    }

    if (1>$rs->RecordCount())
    {
        return false;
    }

    return $rs->GetArray();
}

function _shn_rms_show_res()
{
    $kword = $_POST['kword'];
    $_SESSION['rms_src_kword'] = $kword;
    $words = preg_split("/\s+/",$kword);
    $thead = false;
    $error = true;

    $body = array();
    $row  = array();

    __shn_rms_schkword();

    foreach($words as $word)
    {
        $reqs = _shn_rms_get_res($word);

//        if (!$thead && $reqs)
//        {
//        	__show_table_head();
//        	$thead = true;
//        }

        if($reqs)
        {
        	$error = false;

	        foreach ($reqs as $req)
	        {
                array_push($row, $req['req_id']);
                array_push($row, $req['req_date']);
                array_push($row, $req['name']);
                array_push($row, $req['site_name']);
                array_push($row, nl2br($req['site_address']));
                array_push($row, '<a href="index.php?mod=rms&amp;act=vw_req&amp;seq=detail&amp;req_id=' . $req['req_id'] . '#list">View</a>');
	        }
            array_push($body, $row);
        }
    }

    if (!empty($body))
    {
        $top_row = array(
                    _("ID"),
                    _("Date"),
                    _("Requester"),
                    _("Site Name"),
                    _("Site Address"),
                    _("More Details")
                    );
        $head = array ($top_row);

        shn_html_table($body, $head);
    }
?>
</tbody>
</table>
</div>
<?php

	if ($error)
	{
		_shn_rms_plgsc_back();
	}
}

function __show_table_head()
{
?>
	<br/>
<div>
<table id="result" width="100%">
<?php

?>
    <tbody>
<?php
}

function _shn_rms_plgsc_back()
{
	print _("<h3>No results found for the keyword : "). $_SESSION['rms_src_kword'] ."</h3>";
    print _("<br/><h4>Click the back button to go back</h4>");

    #back button
    shn_form_fopen("sc_req",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>''));
    shn_form_submit(_("Back"),"short");
    shn_form_fclose();
}

function _shn_rms_show_reqdetails()
{
    _shn_rms_show_request($_POST['id']);

    #back button
    shn_form_fopen("req_srch",null);

    shn_form_hidden(array('seq'=>'req_sch'));
    shn_form_hidden(array('kword'=>$_SESSION['rms_src_kword']));
    shn_form_submit(_("Back"),"short");
    shn_form_fclose();

}

switch ($_REQUEST['seq'])
{
    case '':
            _shn_rms_get_kword();
            break;

    case 'req_sch':
            _shn_rms_show_res();
            break;

    case 'req_vw' :
            _shn_rms_show_reqdetails();
            break;
}
?>