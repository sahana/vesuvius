<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Chathra <chathra@opensource.lk>
* @author     M <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/handler_form.inc";

function shn_cms_reg_victim(){
echo "<h2><center>" . _("Victim Registration") . "</center></h2>";
    // Start Victim registration form
    $header = array (
                        array('method'=>"POST",'action'=>"index.php?mod=cms&act=reg_org_cr")
                    );
                    
    shn_show_form($header);
    
   // Victim Registration on an individual basis
   
    $cms_vct_reg = array(
                        array('legend'=>'Individual Victim Information'),
                        array('desc'=>_("Victim name : "),'type'=>"text",'size'=>50,'name'=>'vct_name','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                        array('desc'=>_("Age category:"),'type'=>"dropdown",'name'=>'age','options'=>$opt_age_group
                        ),
                         array('desc'=>_("Passport/ NID :"),'type'=>"text",'size'=>15,'name'=>'nid','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'
                        ),
                         array('desc'=>_("Person Status :"),'type'=>"dropdown",'name'=>'status','options'=>$opt_status
                        ),
                         array('desc'=>_("Race:"),'type'=>"dropdown",'name'=>'race','options'=>$opt_race
                        ),
                         array('desc'=>_("Religion :"),'type'=>"dropdown",'name'=>'religion','options'=>$opt_religion
                        ),
                          array('desc'=>_("Marital Status :"),'type'=>"dropdown",'name'=>'mar_status','options'=>$opt_maritial_status
                        ),
                          array('desc'=>_("Previous Contact Type :"),'type'=>"dropdown",'name'=>'con_type','options'=>$opt_contact_type 
                        ),
                        array('desc'=>_("Previous Permanant Address : "),'type'=>"txtarea",'rows'=>10,'cols'=>60,'name'=>'pre_add','br'=>1),
                   );
    shn_show_form($cms_vct_reg);

	// Victim Registration on a Group Basis
	
	$cms_grp_reg = array(
                        array('legend'=>'Group Information'),
                        array('desc'=>_("Group Name (preferrably by surname) : "),'type'=>"text",'size'=>50,'name'=>'grp_name','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                        array('desc'=>_("No: of members : "),'type'=>"text",'size'=>50,'number'=>'grp_no','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                       );
    shn_show_form($cms_grp_reg);

     
    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Next"))
                   );

    shn_show_form($tail);
}                                             
?>
<?php
function shn_cms_edit_victim(){
echo "<h2><center>" . _("Edit Victim Information") . "</center></h2>";
    // Start Victim registration form
    $header = array (
                        array('method'=>"POST",'action'=>"index.php?mod=cms&act=reg_org_cr")
                    );
                    
    shn_show_form($header);
    
   // Victim Registration on an individual basis
   
    $cms_vct_reg = array(
                        array('legend'=>'Individual Victim Information'),
                        array('desc'=>_("Victim name : "),'type'=>"text",'size'=>50,'name'=>'vct_name','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                        array('desc'=>_("Age category:"),'type'=>"dropdown",'name'=>'age','options'=>$opt_age_group
                        ),
                         array('desc'=>_("Passport/ NID :"),'type'=>"text",'size'=>15,'name'=>'nid','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'
                        ),
                         array('desc'=>_("Person Status :"),'type'=>"dropdown",'name'=>'status','options'=>$opt_status
                        ),
                         array('desc'=>_("Race:"),'type'=>"dropdown",'name'=>'race','options'=>$opt_race
                        ),
                         array('desc'=>_("Religion :"),'type'=>"dropdown",'name'=>'religion','options'=>$opt_religion
                        ),
                          array('desc'=>_("Marital Status :"),'type'=>"dropdown",'name'=>'mar_status','options'=>$opt_maritial_status
                        ),
                        array('desc'=>_("Previous Contact Type :"),'type'=>"dropdown",'name'=>'con_type','options'=>$opt_contact_type 
                        ),
                        array('desc'=>_("Permanant Address : "),'type'=>"txtarea",'rows'=>10,'cols'=>60,'name'=>'pre_add','br'=>1),
                   );
    shn_show_form($cms_vct_reg);

	// Victim Registration on a Group Basis
	
	$cms_grp_reg = array(
                        array('legend'=>'Group Information'),
                        array('desc'=>_("Group Name (preferrably by surname) : "),'type'=>"text",'size'=>50,'name'=>'grp_name','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                        array('desc'=>_("No: of members : "),'type'=>"text",'size'=>50,'number'=>'grp_no','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                       );
    shn_show_form($cms_grp_reg);

    // CMS infomation
    
    $contact01 = array (
    					array('legend'=>_("Contact Person Information :")),          
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>50,'name'=>'contact_name','br'=>1),
                        array('desc'=>_("Address : "),'type'=>"txtarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1),

                        ); // end of contact 01
    shn_show_form($contact01);
    
     
    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Next"))
                   );

    shn_show_form($tail);
}                                             
?>
