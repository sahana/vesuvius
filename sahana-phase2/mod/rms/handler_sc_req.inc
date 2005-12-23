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
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 


_shn_rms_show_headder(_("Search for a Request"));

function _shn_rms_get_kword()
{
    shn_form_fopen("sc_req",null,array('req_message'=>false));
    
    shn_form_hidden(array('seq'=>'req_sch'));
    
    shn_form_fsopen('Search Keyword');
    shn_form_text('Enter Search Keyword','kword');
    shn_form_fsclose();
    shn_form_submit('Search');
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
        print "<h3>No results found for the keyword : ". $_SESSION['rms_src_kword'] ."</h3>";
        print "<br/><h4>Click the back button to go back</h4>";
        
        #back button
        shn_form_fopen("sc_req",null,array('req_message'=>false));
        shn_form_hidden(array('seq'=>''));
        shn_form_submit('Back',"short");
        shn_form_fclose();
    }
    
    return $rs->GetArray();
}

function _shn_rms_show_res()
{
    $kword = $_POST['kword'];
    $_SESSION['rms_src_kword'] = $kword;
    $words = preg_split("/\s+/",$kword);
    
    _shn_rms_get_kword();
?>
<br/>
<div>
<table id="result" width="100%">
    <thead>
        <td width="30"><?php print _("ID") ?></td>
        <td width="120"><?php print _("Date") ?></td>
        <td width="100"><?php print _("Requester") ?></td>
        <td width="100"><?php print _("Site Name") ?></td>
        <td width=""><?php print _("Site Address") ?></td>
        <td width="80"><?php print _("More Details") ?></td>
    </thead>
    <tbody>
<?php
    foreach($words as $word)
    {
        $reqs = _shn_rms_get_res($word);
        
        
        foreach ($reqs as $req)
        {
            print "<tr>";
            print "<td>" . $req['req_id'] . "</td>";
            print "<td>" . $req['req_date'] . "</td>";
            print "<td>" . $req['name'] . "</td>";
            print "<td>" . $req['site_name'] . "</td>";
            print "<td>" . nl2br($req['site_address']) . "</td>";
            print '<td><a href="index.php?mod=rms&amp;act=vw_req&amp;seq=detail&amp;req_id=' . $req['req_id'] . '#list">View</a></td>';
            print "</tr>";
        }        
    }
?>
</tbody>
</table>
</div>
<?php
}

function _shn_rms_show_reqdetails()
{
    _shn_rms_show_request($_POST['id']);
    
    #back button
    shn_form_fopen("req_srch",null);
    
    shn_form_hidden(array('seq'=>'req_sch'));
    shn_form_hidden(array('kword'=>$_SESSION['rms_src_kword']));            
    shn_form_submit('Back',"short");
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