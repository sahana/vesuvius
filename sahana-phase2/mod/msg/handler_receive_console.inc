<?php
/**
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @author   	J P Fonseka <jo@respere.com>
* @copyright  	Respere - http://respere.com/
* @version 		$Id: handler_receive_console.inc,v 1.3 2008-06-01 07:08:52 priyanga Exp $
* @package 		Sahana - http://sahana.lk/
* @subpackage 	messaging   
* @license   	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once ('lib_receive_console.inc');

echo "<h2>"._t('Receive Console')."</h2>";
    shn_form_fopen('','',array('req_message'=>false,'id'=>'search'));
    //shn_form_fsopen("Search Messages");
    shn_form_text('Sender or Message','search','',array('br'=>false,'size'=>20));
    //shn_form_text('Number','number');
    //shn_form_date('Date','date');
    //shn_form_text('Message','message');
    //shn_form_fsclose();
    shn_form_submit('Search',' onclick="msg_click_search();return false;"');
    shn_form_fclose();

?>
<br />
<a onclick="msg_popout_rconsole(this)" style="background:#D6EDFF;padding:2px 10px 2px 10px;cursor:pointer;-moz-border-radius: 5px 5px 0px 0px; text-decoration:none;
" id="pop_but">Pop out</a>&nbsp;
<div>
<?php _shn_msg_popup_div() ?>
</div>
<br />

