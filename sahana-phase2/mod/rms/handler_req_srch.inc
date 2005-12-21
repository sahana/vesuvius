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
    shn_form_fopen("req_srch",null);
    
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
    
    $sql = "SELECT * FROM (SELECT r.id AS id,r.status AS status," .
                "r.date AS date,s.name AS name,p.name AS pname " .
                "FROM rms_request r, rms_org_psn p, rms_req_site s " .
                "WHERE r.requester_id = p.id AND r.site_id = s.id) AS tb " .
            "WHERE LOWER(name) LIKE LOWER('%$word%') " .
            "OR LOWER(status) = LOWER('$word') " .
            "OR LOWER(pname) LIKE LOWER('%$word%') " .
            "OR LOWER(date) LIKE LOWER('%$word%')";
            
    $rs = $global['db']->Execute($sql);
    
    if ($global['db']->ErrorMsg())
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
    }
    
    if (1>$rs->RecordCount())
    {
        print "<h3>No results found for the keyword : ". $_SESSION['rms_src_kword'] ."</h3>";
        print "<h3>Click the back button to go back</h3>";
        
        #back button
        shn_form_fopen("req_srch",null);
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
<table id="result">
<?php
    foreach($words as $word)
    {
        $reqs = _shn_rms_get_res($word);
        
        foreach ($reqs as $req)
        {
            print "<tr>";
            print "<td>" . $req['id'] . "</td>";
            print "<td>" . $req['date'] . "</td>";
            print "<td>" . $req['status'] . "</td>";
            print "<td>" . $req['name'] . "</td>";
            print "<td>" . $req[3] . "</td>";
            print "<td>";

            #more details button
            shn_form_fopen("req_srch",null);
            shn_form_hidden(array('seq'=>'req_vw'));            
            shn_form_hidden(array('id'=>$req['id']));
            shn_form_submit('Details',"short");
            shn_form_fclose();
        
            print "</td>";
            print "</tr>";
        }        
    }
?>
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