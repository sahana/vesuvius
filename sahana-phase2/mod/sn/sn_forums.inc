<?php

/**
 * Discussion Page
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
include_once $global['approot'] . '/mod/sn/lib_sn.inc';

if(isset($_REQUEST['seq'])) {
	switch($_REQUEST['seq']){
		case 'page2':
            {
             _shn_sn_show_add_topic_form();
            break;

            }

         case 'page3' :
         {
         	if(_shn_sn_validate()){
         		_shn_sn_show_add_topic_form(true);
         	}
		    else{

		    	_shn_sn_add_topic_to_db();
		    	_shn_sn_show_topics();
		    }
		    break;

         }
         case 'page4' :
         {
         	_shn_sn_show_posts();
            break;

         }
         case 'page5' :
         {
         	_shn_sn_add_post_form();
            break;

         }
         case 'page6' :
         {
         	_shn_sn_do_add_post();
         	_shn_sn_show_posts();
         	 //unset($_SESSION['topic_id']);

            break;

         }
         case 'page7' :
         {
         	_shn_sn_add_topic_link();
         }

	}


}
else{

	_shn_sn_add_topic_link();

}
/**
 * this function would display the initial
 * link to add a topic to discuss
 *
 */
function _shn_sn_add_topic_link(){
	?>
    <h2><center><?php print (('Latest  topics  added  just  to  discuss')); ?></center></h2>
    <?php

    global $global;
    shn_form_fopen('sn_forums','sn',array('req'=> false));
    shn_form_fsopen('adding a topic to discuss');



    ?>
       <a href="index.php?mod=sn&act=sn_forums&seq=page2"><b><?= ('Add a topic'); ?> </b></a>

    <?php
    $chk_topics = _shn_sn_count_topic();

    if($chk_topics){

    	$recent = _shn_get_stored_topics();
        $records = $recent->fields['topic_id'];
    	    ?>
        <br><br><br>
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


    }
    else {
    	?><p>No topics added yet ...</p><br><br><br> <?php

    }


    shn_form_fsclose();
    shn_form_fclose();


}

/**
 * this will display a form to add a new topic to discuss
 *
 */
 function  _shn_sn_show_add_topic_form($errors = false){
 	if($errors){
 		display_errors();
 	}

    ?>

    <h2><center><?php print (('Adding a topic')); ?></center></h2>
    <?php


    shn_form_fopen('sn_forums','sn',array('req'=> true));
    shn_form_fsopen('adding a topic to discuss');
    shn_form_hidden(array('seq' => 'page3'));


    //shn_form_label('email',$_SESSION[sn][mem_email]);
    //shn_form_text('E-Mail Address','topic_owner');
    shn_form_text('Topic Title','topic_title');

    $extra_options = array();
    $array_options['cols'] = '70';
    $array_options['rows'] = '5';
    shn_form_textarea('Post Text','post_text','',$array_options);

    shn_form_submit('Add a topic');

    shn_form_fsclose();
    shn_form_fclose();


}
/**
 * This function will validate required fields.
 */
function  _shn_sn_validate(){

    clean_errors();
	$error_flag= false;

	$topic_owner = $_SESSION[sn][mem_username];
	$topic_title = $_POST['topic_title'];
	$post_text = $_POST['post_text'];

/*	if ($topic_owner == null) {
		//$errors[0] = 'Please enter a username';
		add_error('please enter a email address');
        $error_flag = true;
	}*/
	if($topic_title  == null){
		add_error('please enter a topic title');
		$error_flag = true;
	}
	if($post_text== null){
		//add_error('no text to post');
		//$error_flag = true;
	}

	return $error_flag ;

}
/**
 * this function would add topic to db.
 */
function _shn_sn_add_topic_to_db(){

	$topic_id = shn_create_uuid('topic'); //create id for topics
	global $global;
	$db = $global['db'];
	$sql = "INSERT INTO sn_forum_topics VALUES ('$topic_id','{$_POST['topic_title']}',now(),'{$_SESSION[sn][mem_username]}')";
	$sql_ok1 = _shn_sn_execute($sql);

	$id = mysql_insert_id();

	print "$topic_id";
	$sql = "INSERT INTO sn_forum_posts VALUES('','$topic_id','{$_POST['post_text']}',now(),'{$_SESSION[sn][mem_username]}')";
	$sql_ok2 = _shn_sn_execute($sql);

	if ($sql_ok1) {
	    add_confirmation(($_POST['topic_title']. ' is successfully added.'));
	}

	if ($sql_ok2) {
	  // add_confirmation(($_POST['post_text']. ' is successfully added.'));
	}
}
/**
 * This function would illustrate the topics posted and no of
 * posts for the topics
 *
 */
function _shn_sn_show_topics(){

    global $global;
    shn_form_fopen('sn_forums','sn',array('req'=> true));
    shn_form_fsopen('Topics added just to discuss');
    shn_form_hidden(array('seq' => 'page4'));


    $recent = _shn_get_stored_topics();

  ?>
<div align="center">
<table  border="1">
    <tr>
        <th> Forum Topics </th>
        <th> Posts  </th>
    </tr>

  <?php
    while (!$recent->EOF) {
  ?><tr>

    	<td>
   <?php
        //print $recent->fields['dis_uuid'] . '...........' . $recent->fields['dis_name'];
        echo '<br /><a href="index.php?mod='.$global['module'].'&act=sn_forums&seq=page4&topic_id='.$recent->fields['topic_id'].'&topic_title='.$recent->fields['topic_title'].'">'.$recent->fields['topic_title'].'</a><br />'.' Created on '.$recent->fields['fmt_topic_create_time'].' by '.$recent->fields['topic_owner'];


        $topic_id = $recent->fields['topic_id'];
        //$_SESSION['topic_id'] = $topic_id;

        $details = _shn_get_num_posts($topic_id);

    ?>  </td>
    	<td>
    <?php
        print '<br />'.$details.'<br>';
    ?>  </td>
        </tr>
    <?php
        $recent->MoveNext();
    }
    ?>
</table>
</div>

<?php
    shn_form_fsclose();
    shn_form_fclose();
}





function _shn_sn_show_posts(){

    global $global;
    shn_form_fopen('sn_forums','sn',array('req'=> true));
    shn_form_fsopen('posts to the particular topic');
    shn_form_hidden(array('seq' => '5'));
    ?>
    <div align="right"><?php

    shn_form_fopen('sn_forums','sn',array('req'=> true));
    shn_form_hidden(array('seq' => 'page7'));
    shn_form_submit('<< Back',"name='button'");
    shn_form_fclose();

    ?></div><?php

/*    $t_id = $_SESSION['topic_id'];
    if($t_id){
    	$topic_id=$t_id;
    }else{*/
    	$topic_id =$_REQUEST['topic_id'];
    $topic_title =$_REQUEST['topic_title'];

    $chk_posts = _shn_sn_count_posts($topic_id);

    $recent1 = _shn_sn_get_posts($topic_id);?>



    <br>
    <h3 align="center"> <b> <font color="green" size="2"> feel free to add posts to the following discussion, they are based on <?=$topic_title ?> </font></b><br></h3><br><br>
    <div align="center">
    <table width="800">
    <tr>
        <td> Image </td>
        <td> Author </td>
        <td width="200pt"> Posts  </td>
    </tr>

    <?php
    while (!$recent1->EOF) {
         $post_owner = $recent1->fields['post_owner'];

         $sql_img = "select p_uuid from users where user_name='$post_owner'";
         $result =   _shn_sn_execute($sql_img)->fields['p_uuid'];

    // echo  'user id is :'.$result;
       ?><tr><td><?php

       shn_show_thumb_url($result,'database','sn','mem_img',false);

       ?></td><td><?php
        //print the authors names of a particular posts.
        echo '<br />'.' Post by  '.$recent1->fields['post_owner'].' on '.$recent1->fields['fmt_post_create_time'];

       ?>  </td><td><?php

       $p = $recent1->fields['post_text'];
       if($chk_posts){
       	    echo $recent1->fields['post_text'].'<br><br>'.'<a href="index.php?mod='.$global['module'].'&act=sn_forums&seq=page5&topic_id='.$topic_id.'">'.'Reply to the post'.'</a><br />';

       }
       else{
	       echo 'No posts for the topic'.'<br><br>'.'<a href="index.php?mod='.$global['module'].'&act=sn_forums&seq=page5&topic_id='.$topic_id.'">'.'Be the first one in posting'.'</a><br />';
       }//print the post owner.



       ?>  </td></tr><?php


       $recent1->MoveNext();
       }
       ?>
           </table>
           </div>
       <?php

       shn_form_fsclose();
       shn_form_fclose();

}

function _shn_sn_add_post_form(){
	?>
	<div align="right"><a href="index.php?mod=sn&act=log_out"><b><?= ('Logout'); ?> </b></a></div>
    <h2><center><?php print (('Adding a posts')); ?></center></h2><br><br>
    <?php
    $topic = $_GET['topic_id'];
    //$_SESSION['topic_id']= $topic;
    //echo $topic;
	shn_form_fopen('sn_forums','sn',array('req'=> true));
    shn_form_fsopen('Add posts for the topic');
    shn_form_hidden(array('seq'=>'page6','topic_id'=>$topic));

	//shn_form_text('E-Mail Address','post_owner');
    $extra_options = array();
    $array_options['cols'] = '70';
    $array_options['rows'] = '5';
    shn_form_textarea('Post Text','post_text','',$array_options);


    shn_form_submit('Add Post');



    shn_form_fsclose();
    shn_form_fclose();

}
function _shn_sn_do_add_post(){
    $post_text= null;
	$topic_id =  $_REQUEST['topic_id'];
	$email = $_POST['post_owner'];
	$post_text = $_POST['post_text'];

    if($topic_id){
    	$sql = "INSERT INTO sn_forum_posts VALUES('','$topic_id','{$_POST['post_text']}',now(),'{$_SESSION[sn][mem_username]}')";
	    $sql_ok = _shn_sn_execute($sql);
	    //shn_form_hidden(array('topic_id'=>$topic_id));


	    if ($sql_ok) {
	        add_confirmation(('Post is successfully added.'));
	    }
    }
 }


?>




