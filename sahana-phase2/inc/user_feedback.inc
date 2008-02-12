<?php
include_once( $global['approot']."inc/lib_validate.inc");

if(isset($conf['user_help_server'])==false || $conf['user_help_server']==null || strlen(trim($conf['user_help_server']))==0){
	   $conf['user_help_server'] = $conf['base_url'];
}else{
	if(strripos($conf['user_help_server'],"/")<(strlen($conf['user_help_server'])-1)){
		// append a / to the end.
		$conf['user_help_server'] = $conf['user_help_server']."/";
	}
}
/**
 * Search for an answer for the user question in the sahana faq.
 *
 * @param unknown_type $question
 */
function _shn_search_answer($question,$module=null,$action=null){
//	$response_txt = _shn_search_answer_db($question,$module,$action);
	$response_txt = _shn_search_remote_server_answer_db($question,$module,$action);
	$response = new xajaxResponse();
	$response->addAssign("feedback_content_error","className","feedback_content_error hide");
	$response->addAssign("feedback_content","innerHTML",$response_txt);
	return $response;
}

/**
 * Record a feedback sent by the user and register it in sahana.lk
 *
 * @param unknown_type $feedback
 * @param unknown_type $email
 * @return unknown
 */
function _shn_send_feedback($feedback,$email){
	$feedback = trim($feedback);
	$email = trim($email);

	$response = new xajaxResponse();
	if($feedback == null || strlen($feedback) == 0){
		$response->addAssign("user_email","value",$email);
		$response->addAssign("user_fb","value",$feedback);
		$response->addAssign("feedback_content_error","innerHTML",_t("Please enter a feedback comment"));
		$response->addAssign("feedback_content_error","className","feedback_content_error show");
	}else if($email == null || strlen($email) == 0 || shn_valid_email($email) == false){
		$response->addAssign("user_email","value",$email);
		$response->addAssign("user_fb","value",$feedback);
		$response->addAssign("feedback_content_error","innerHTML",_t("Please enter a valid email address"));
		$response->addAssign("feedback_content_error","className","feedback_content_error show");
	}else{
		global $global,$conf;
		$db = $global['db'];
		$query = "INSERT INTO `user_feedback` (`mod`,`act`,`comment`,`date`,`email`) VALUES ('".$global['module']."','".$global['action']."','$feedback','".date("Y-m-d H:i:s")."','$email')";
		$db->Execute($query);
		if($db->ErrorNo()>0){
			$response->addAssign("feedback_content_error","innerHTML",_t("Failiure occured in recording your feedback comment."));
			$response->addAssign("feedback_content_error","className","feedback_content_error show");
		}else{
			$response->addAssign("feedback_content_error","className","feedback_content_error hide");
			$response->addAssign("feedback_content","innerHTML",_t("Thankyou for your feedback comment. We will contact you as soon as possible. <br/><br/> If you wish to provide more information about yourself/ your organization, where are you from, for what are you using sahana for, etc, please feel free to register an account with <a href=\"http://www.sahana.lk/register.php\">www.sahana.lk</a><br/>"));
		}
	}

	return $response;
}

/**
 * Disable the feedback form.
 *
 */
function _shn_dont_show_fbform(){
	shn_config_database_update('shn_user_feedback_enabled',false);
	$response = new xajaxResponse();
	return $response;
}

function _shn_search_answer_db($question,$module,$action){
	global $global,$conf;
	include_once( $global['approot']."mos/ws/main.inc");
	$wsdl_url="http://localhost/trunk/index.php?wsdl&stream=soap&wbsmod=home&mod=ws&act=reg";
	$method="shn_search_answer_db";
//	file_put_contents("/tmp/a.txt","inside user feedback");
//	$x=shn_ws_sahana_client_call($wsdl_url,$method);
//	return;
	$strip_words = array("is","are","in","be","an","a","the","as","how","who","why","what");

	// strip the words from the search string

	$search_str = $question;
	foreach($strip_words as $word){
		$search_str = str_ireplace(" ".$word." "," ",$search_str);
	}

	$keyword_arr = explode(" ",$search_str);

	for($i=0;$i<count($keyword_arr);$i++){
		$kw = $keyword_arr[$i];
		// if there is only one word or it is the last word
		if($i==(count($keyword_arr)-1)){
			$like_list .= " `question` LIKE '%".$kw."%' " ;
		}else{
			if(count($keyword_arr)==1){
				$like_list .= " `question` LIKE '%".$kw."%' " ;
			}else{
			     $like_list .= " `question` LIKE '%".$kw."%' OR ";	
			}			
		}
	}

	// filter by module and action if available.
	$module_search = "";
	if($module && strlen($module)>0){
		$module_search = "`mod`='$module' AND ";
	}
	$action_search = "";
	if($action && strlen($action)>0){
		$action_search = "`act`='$action' AND ";
	}

	$query = "SELECT `qa_id`,`question`,`answer` FROM `faq` WHERE ".$module_search.$action_search." (".$like_list.")";
	$db = $global['db'];
	$rs = $db->Execute($query);
    
	ob_start();

	if($rs){
		echo "<h4> Results </h4>";
		$assoc = $rs->GetAssoc();
		if(count($assoc)==0){
		    echo "<p>"._t("<h4>Sorry !</h4><p>No matching help item was found in our database.</p><br/><p> We suggest contacting us through support@sahana.lk or by adding your problem as a comment along with your email address, for us to contact you.</p>")	; 
		}else{
			echo "<ol>";

			foreach ($assoc as $key=>$vals){
				echo "<li> <a href='".$conf['user_help_server']."?mod=home&act=faq#".$key."'>"._shn_crop_string($vals[0])."</a></li>";
			}
			echo "</ol>";
		}
	}else{
		 echo "<p>"._t("<h4>Sorry !</h4><p>There was an error in searching the help database.</p><br/><p> We suggest contacting us through support@sahana.lk or by adding your problem as a comment along with your email address, for us to contact you. If you think this is a bug, please be kind to <a href='?mod=home&act=bug_report'>report it.</a></p>")    ;
	}

	$contents =  ob_get_contents();
	
	ob_clean();
	return $contents;
}

function _shn_home_faq(){
	global $global,$conf;
	$query = "SELECT `qa_id`,`question`,`answer` FROM `faq`";
	$db = $global['db'];

	echo "<h4>"._t("Frequently Asked Questions (FAQs)")."</h4>";

	$rs = $db->Execute($query);

	if($rs){
		$assoc = $rs->GetAssoc();

		// first print the questions.
		echo "<ol>";
		foreach($assoc as $key=>$vals){
			echo "<li><a href='#$key'>".$vals[0]."</a></li>";
		}
		// then print both questions and answers
		echo "<br/><hr/><ol>";
		foreach($assoc as $key=>$vals){
			echo "<li><b><a id='$key' href='#$key'>".$vals[0]."</a></b><br/>&nbsp;&nbsp;&nbsp;&nbsp;".$vals[1]."<br/></li>";
		}
		echo "</ol>";
	}else{
		add_error(_t("No faq to display. Either faq is not installed or an unknown error occured"));
	}

}

function _shn_crop_string($str){
	$retstr = $str;
	if(strlen($str)>47){
		$retstr = substr($str,0,47);
		$retstr .= "....";
	}
	return $retstr;
}


/*
 * User feedback form
 */

function shn_user_feedback($with_delay = true){
	global $global,$conf;
	if($conf['shn_user_feedback_enabled']==true){
		require_once($global['approot']."/3rd/xajax/xajax.inc.php");
		require_once($global['approot'].'/3rd/xajax/xajaxResponse.inc.php');

		$xajax = new xajax($conf['base_url'].'index.php?mod=xst&act=user_feedback&stream=text');//$conf['base_url'].'index.php?mod=admin&act=conf_list'
		$xajax->registerFunction("_shn_send_feedback");
		$xajax->registerFunction("_shn_search_answer");
		$xajax->registerFunction("_shn_dont_show_fbform");
		$xajax->printJavascript("res/js/");
		?>
<script type="text/javascript">
<!--
        function sendFeedback(feedback,email,button){
            //disable button
            button.disabled = true;
           xajax__shn_send_feedback(feedback,email);
        }
        
        function searchAnswer(question,button){
            // disable button
            button.disabled = true;
            var mod = '<?php echo $global['module']; ?>';
            var act = '<?php echo $global['action']; ?>';
            xajax__shn_search_answer(question,mod,act);
        }
        
        function dontShowAgain(){
            xajax__shn_dont_show_fbform();
            showFeedbackForm(false);
        }
        
        function showFeedbackForm(show){
            if(show){
                document.getElementById("user_fb_form").style.display="block";
            }else{
                document.getElementById("user_fb_form").style.display="none";
            }
        }
        
        // used by the time out function to show the feedback form
        function _showFBInternal(){
            showFeedbackForm(true);
        }
        
        
//-->
</script>
<style>
<!--
    .feedback_error {
    
    }
    
    .feedback_form {
        position: absolute;
        width: 250px;
        right: 10px;
        bottom: 10px;
        padding-left: 30px;
        padding-right: 8px;
        padding-top: 8px;
        padding-bottom: 8px;
        display: none;
    }
    .feedback_close {
        right: 10px;
        top: 10px;
        display: block;
        float: right;
    }
    
    .feedback_dontshow{
        display: block;
        float: left;
        width: 100%;
        position: relative;
    }
    
    .feedback_content {
        display: block;
        float: left;
        padding-left: 5px;
        overflow: auto;
    }
    .feedback_content_error {
        background-color: pink;
        border-color:red;
        color:red;
    }
    .hide{
        display:none;
    }
    .show{
        display:block;
    }
-->
</style>
<!-- The user feedback div -->
<div id="user_fb_form" class="message information feedback_form">

<div class="feedback_close"><a
	href="javascript:void(0)" onmouseup="showFeedbackForm(false)"><?php echo _("Close") ?></a></div>
<div id="feedback_content_error" class="feedback_content_error hide">&nbsp;</div>
<div id="feedback_content" class="feedback_content"><?php
echo _("Need help?");
echo "<br/><hr/>";
?>
<?php
shn_form_text(_("Your email"),"user_email",null,null);
echo "<br/>";
shn_form_label(_("Please type in your question/feedback comment below"),null);
shn_form_textarea("","user_fb");
shn_form_submit(_("Send"),"title=\""._("Send your feedback comments to sahana team")."\" onmouseup=\"sendFeedback(document.getElementById('user_fb').value,document.getElementById('user_email').value,this)\"");
shn_form_submit(_("Search"),"title=\""._("Search for an answer for your question")."\" onmouseup=\"searchAnswer(document.getElementById('user_fb').value,this)\"");
?></div>

<div align="center" class="feedback_dontshow"><hr/><a
	href="javascript:void(0)" onmouseup="dontShowAgain()"><?php echo _("Don't show this again.") ?></a></div>
</div>
<script type="text/javascript">
    window.setTimeout("_showFBInternal()",2000);
</script>
<?php
    }
}

function _shn_search_remote_server_answer_db($question,$module,$action){
	global $global,$conf;
	include_once( $global['approot']."mod/ws/main.inc");
	include_once( $global['approot']."inc/lib_misc.inc");
	$wsdl_url="http://localhost/trunk/index.php?wsdl&stream=soap&wbsmod=home&mod=ws&act=reg";
	$method="shn_search_answer_db";
	$input=array("question"=>"test","module"=>$module,"action"=>$action);
//	file_put_contents("/tmp/a.txt","inside user feedback");
	$response=shn_ws_sahana_client_call($wsdl_url,$method,$input);
	file_put_contents("/tmp/a.txt",$response[0]["question"],FILE_APPEND);
	
	ob_start();

	if($response){
		echo "<h4> Results </h4>";

		if(count($response)==0){
		    echo "<p>"._t("<h4>Sorry !</h4><p>No matching help item was found in our database.</p><br/><p> We suggest contacting us through support@sahana.lk or by adding your problem as a comment along with your email address, for us to contact you.</p>")	; 
		}else{
			echo "<ol>";
			foreach ($response as $faq){
		//	foreach ($assoc as $key=>$vals){
				$key=$faq["id"];
				$question=$faq["question"];
				echo "<li> <a href='".$conf['user_help_server']."?mod=home&act=faq#".$key."'>"._shn_crop_string($question)."</a></li>";
			}
			echo "</ol>";
		}
	}else{
		 echo "<p>"._t("<h4>Sorry !</h4><p>There was an error in searching the help database.</p><br/><p> We suggest contacting us through support@sahana.lk or by adding your problem as a comment along with your email address, for us to contact you. If you think this is a bug, please be kind to <a href='?mod=home&act=bug_report'>report it.</a></p>")    ;
	}

	$contents =  ob_get_contents();
	
	ob_clean();
	
	return $contents;
}

function _shn_search_get_answer_db($question,$module,$action){
	global $global,$conf;

	$strip_words = array("is","are","in","be","an","a","the","as","how","who","why","what");

	// strip the words from the search string

	$search_str = $question;
	foreach($strip_words as $word){
		$search_str = str_ireplace(" ".$word." "," ",$search_str);
	}

	$keyword_arr = explode(" ",$search_str);

	for($i=0;$i<count($keyword_arr);$i++){
		$kw = $keyword_arr[$i];
		// if there is only one word or it is the last word
		if($i==(count($keyword_arr)-1)){
			$like_list .= " `question` LIKE '%".$kw."%' " ;
		}else{
			if(count($keyword_arr)==1){
				$like_list .= " `question` LIKE '%".$kw."%' " ;
			}else{
			     $like_list .= " `question` LIKE '%".$kw."%' OR ";	
			}			
		}
	}

	// filter by module and action if available.
	$module_search = "";
	if($module && strlen($module)>0){
		$module_search = "`mod`='$module' AND ";
	}
	$action_search = "";
	if($action && strlen($action)>0){
		$action_search = "`act`='$action' AND ";
	}

	$query = "SELECT `qa_id`,`question`,`answer` FROM `faq` WHERE ".$module_search.$action_search." (".$like_list.")";
	$db = $global['db'];
	$rs = $db->Execute($query);

	if($rs){

		$assoc = $rs->GetAssoc();
		if(count($assoc)==0){
		   return null;
		 
		}else{
			
			$faq_list=array();
			foreach ($assoc as $key=>$vals){
				$faq_list[] = array('question' => $vals[0], 'id' => $key);
				
			}
			return $faq_list;
			
		}
	}else{
		return null;
		
	}

}

?>