<?php
/**
 * SN Description Page
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Harsha Halgaswatta(harsha.halgaswatta@gmail.com)
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage s
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


include_once $global['approot'] . '/inc/handler_form.inc';
include_once $global['approot'] . '/inc/lib_uuid.inc';
//include_once $global['approot'] . '/inc/lib_form.inc';
include_once $global['approot'] . '/mod/sn/lib_sn.inc';



?>
<div align="center">
<h3> Share Info </h3>




</div>


<?php

shn_form_fopen('sh_info','sn',array('req'=> false));

//shn_form_select('test','select file to upload', 'select','dfdfddfd,fd,fdfd');

shn_form_upload('File to Upload','file_to_upload');
shn_form_fsclose();
shn_form_fclose();

_shn_sn_add_topic_link();
_shn_sn_show_topics();


function _shn_sn_add_topic_link(){

	?>
    <h2><center><?php print (_t('Latest  topics  added  just  to  discuss')); ?></center></h2>
    <?php


   // shn_form_fopen('sn_forums','sn',array('req'=> false));
    //shn_form_fsopen('adding a topic to discuss');



    ?>


    <?php

   // shn_form_fsclose();
   // shn_form_fclose();


}


function _shn_sn_show_topics() {
    ?>
    <div align="right"><a href="index.php?mod=sn&act=log_out"><b><?php echo  _t('Logout'); ?> </b></a></div>

    <?php
    global $global;
    shn_form_fopen('sn_forums','sn',array('req'=> true));
    shn_form_fsopen('Topics added just to discuss');
    shn_form_hidden(array('seq' => 'page4'));


    $recent = _shn_get_stored_topics();
    $records = $recent->fields['topic_id'];


    if($records){
    ?><a href="index.php?mod=sn&act=sn_forums&seq=page2"><b><?php echo  _t('Add a topic'); ?> </b></a><br><br><br>
     <div align="center">
     <table width="600">
         <tr>
             <td> Forum Topics </td>
             <td> Posts  </td>
         </tr>
       <?php
       while (!$recent->EOF) {
       ?><tr>

    	     <td><?php
                 echo '<br /><a href="index.php?mod='.$global['module'].'&act=sn_forums&seq=page4&topic_id='.$recent->fields['topic_id'].'&topic_title='.$recent->fields['topic_title'].'">'.$recent->fields['topic_title'].'</a><br />'.' Created on '.$recent->fields['fmt_topic_create_time'].' by '.$recent->fields['topic_owner'];
                 $topic_id = $recent->fields['topic_id'];
                 //$_SESSION['topic_id'] = $topic_id;
                 $details = _shn_get_num_posts($topic_id);
                 //print "testing counmt is : ".$details;
           ?></td>
    	     <td><?php
                 print '<br />'.$details.'<br>';
           ?></td>
        </tr><?php
            $recent->MoveNext();
       }
       ?>
    </table>
    </div>

    <?php



    }else {
    	?><p>No topics added yet ....<a href="index.php?mod=sn&act=sn_forums&seq=page2"><b><?php echo  _t('Add a topic'); ?> </b></a></p><br><br><br> <?php

    }


    shn_form_fsclose();
    shn_form_fclose();
}

