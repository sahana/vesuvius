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

_shn_rms_show_headder(_("New Request"));

function _shn_rms_get_requesterid()
{
?>
If you have a user id please enter it, Or if you are a new requester 
please <a href="index.php?mod=rms&amp;act=req_new&amp;seq=newcon"><strong>Enter Here</strong></a>.
<?php
    shn_form_fopen("req_new",null);
    
    shn_form_hidden(array('seq'=>'newsite'));
    
    shn_form_fsopen('Requester ID');
    shn_form_text('Enter Requester ID','id');
    shn_form_fsclose();
    shn_form_submit('Enter');
    shn_form_fclose();
}

/**
 * Retrive requester data from the database
 */
function _shn_rms_rtv_requesterinfo()
{
    global $global;
    $id = $_POST['id'];
    
    $rs = _shn_rms_get_requesterter($id);
    if ($rs==false)
        return false;   

    $_SESSION['rms_requester'] = $rs;
    return true;
}

/**
 * Get new contact information for a requester
 */ 
function _shn_rms_get_coninfo($error=false)
{
    if($error)
    {
        _shn_rms_showerrors();
    }
        
    shn_form_fopen("req_new",null);
    
    shn_form_hidden(array('seq'=>'addcon'));
    
    shn_form_fsopen('Requester Contact Information');
    
    shn_form_text('Name','name');
    //shn_location_form('1','4');
    shn_form_text('Location','location');    
    shn_form_text('Telephone','telephone');
    shn_form_text('E-Mail','email');
    shn_form_textarea('Address','address');
    shn_form_textarea('Comments','comments');
    shn_form_fsclose();
    shn_form_submit('-- Next -->');
    shn_form_fclose();
}

function _shn_rms_add_coninfo()
{
    $error = false;
    
    if(trim($_POST['name'])=='')
    {
        _shn_rms_adderror("The Name field cannot be empty");
    }
    
    if(trim($_POST['location'])=='')
    {
        _shn_rms_adderror("The Location field cannot be empty");
    }
    
    if (0 < _shn_rms_errorcount())
    {
        _shn_rms_get_coninfo(true);
    }
    else if (!isset($_SESSION['rms_requester']['id']))
    {
        global $global;
        $_SESSION['rms_requester'] = $_POST;
        unset($_SESSION['rms_requester']['seq']);
        $CON = $_SESSION['rms_requester'];
        
        shn_db_insert($CON,"rms_org_psn");
        $_SESSION['rms_requester']['id'] = $global['db']->Insert_ID();
        print_r($_SESSION['rms_requester']);
        
        unset($_POST);  //To prevent the form being populated with contactperson info.
        _shn_rms_get_siteinfo();
    }
    else
    {
        unset($_POST);
        _shn_rms_get_siteinfo();
    }
}

function _shn_rms_get_siteinfo($error=false)
{
    if($error)
    {
        _shn_rms_showerrors();
    }
    
    shn_form_fopen("req_new",null);
    shn_form_hidden(array('seq'=>'addsite'));
    shn_form_fsopen('Site Information');
    shn_form_text('Name','name');
    shn_form_textarea('Address','address');
    //shn_location_form('1','4');
    shn_form_text('Location','location');  
    shn_form_fsclose();
    shn_form_submit('-- Next -->');
    shn_form_fclose();
}


function _shn_rms_add_siteinfo()
{
    $error = false;
    
    if(trim($_POST['name'])=='')
    {
        _shn_rms_adderror("The Name field cannot be empty");
    }
    
    if(trim($_POST['address'])=='')
    {
        _shn_rms_adderror("The Address field cannot be empty");
    }
    
    if(trim($_POST['location'])=='')
    {
        _shn_rms_adderror("The Location field cannot be empty");
    }
    
    if (0 < _shn_rms_errorcount())
    {
        _shn_rms_get_siteinfo(true);
    }
    else if (!isset($_SESSION['rms_site']['id']))
    {
        global $global;
        
        $_SESSION['rms_site'] = $_POST;
        unset($_SESSION['rms_site']['seq']);
        $SIT = $_SESSION['rms_site'];
        
        shn_db_insert($SIT,"rms_req_site");
        
        $_SESSION['rms_site']['id'] = $global['db']->Insert_ID();
        
        unset($_POST);
        
        _shn_rms_get_iteminfo();
    }
    else
    {
        unset($_POST);
        _shn_rms_get_iteminfo();
    }
}

function _shn_rms_get_iteminfo($error=false)
{
    if($error)
    {
        _shn_rms_showerrors();
    }
        
    shn_form_fopen("req_new",null);
    
    shn_form_hidden(array('seq'=>'additem'));
    
    shn_form_fsopen('Item Information');
    shn_form_select(_shn_rms_get_catlist(),"Category","cat_id");
    shn_form_text('Item','item');
    shn_form_text('Unit','unit');
    shn_form_text('Quantity','qty');
    shn_form_select(_shn_rms_get_prylist(),"Priority","pry_id");
    shn_form_fsclose();
    shn_form_submit('Add Item');
    shn_form_fclose();
    
    /**
     * The Finish button
     */
    shn_form_fopen("req_new",null);
    shn_form_hidden(array('seq'=>'finish'));
    shn_form_submit('Finish');
    shn_form_fclose();
}

function _shn_rms_add_iteminfo()
{
    $error = false;
    
    if(trim($_POST['item'])=='')
    {
        _shn_rms_adderror("The Item field cannot be empty");
    }
    
    if(trim($_POST['qty'])=='')
    {
        _shn_rms_adderror("The Please Enter a vlid Quantity");
    }
    
    if (0 < _shn_rms_errorcount())
    {
        _shn_rms_get_iteminfo(true);
    }
    else
    {
        global $global;

        $ITM['name'] = $_POST['item'];
        $ITM['cat_id'] = $_POST['cat_id'];
        $ITM['unit'] = $_POST['unit'];
        $ITM['qty'] = $_POST['qty'];
        
        shn_db_insert($ITM,"rms_item");
        $ITM['id'] = $global['db']->Insert_ID();
        
        if (!isset($_SESSION['rms_request']['id']))
        {
            $REQ['site_id'] = $_SESSION['rms_site']['id'];
            $REQ['status'] = "open";
            $REQ['requester_id'] = $_SESSION['rms_requester']['id'];
            
            shn_db_insert($REQ,"rms_request");
            $_SESSION['rms_request']['id'] = $global['db']->Insert_ID();
        }
        
        $REQ_ITM['req_id'] = $_SESSION['rms_request']['id'];
        $REQ_ITM['item_id'] = $ITM['id'];
        $REQ_ITM['priority_id'] = $_POST['pry_id'];
        
        shn_db_insert($REQ_ITM,"rms_req_item");
        unset($_POST);
        
        _shn_rms_get_iteminfo();
    }
}

function _shn_rms_req_added()
{
    _shn_rms_showerrors();
?>
    <h3>The Request was added successfully</h3>
<?php
    _shn_rms_show_request($_SESSION['rms_request']['id']);
}

switch ($_REQUEST['seq'])
{
    case '':
            _shn_rms_clear_reqsession();
            _shn_rms_get_requesterid();
            break;
    
    case 'newcon':
            _shn_rms_get_coninfo();
            break;
            
    case 'addcon':
            _shn_rms_add_coninfo();
            break;
              
    case 'newsite':
            if(_shn_rms_rtv_requesterinfo())
                _shn_rms_get_siteinfo();
            else
            {
                _shn_rms_showerrors();
                _shn_rms_get_requesterid();
            }
            break;
            
    case 'addsite':
            _shn_rms_add_siteinfo();
            break;
            
    case 'newitem':
            _shn_rms_get_iteminfo();
            break;
            
    case 'additem':
            _shn_rms_add_iteminfo();
            break;
    
    case 'finish':
            _shn_rms_req_added();
            break;
                
}

?>