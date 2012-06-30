<?php
/**
 * @name         Event Manager
 * @version      16
 * @package      em
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0119
 */

// xajax.inc
require '../mod/lpf/facebook/src/facebook.php';
include '../mod/lpf/twitter/EpiCurl.php';
include '../mod/lpf/twitter/EpiOAuth.php';
include '../mod/lpf/twitter/EpiTwitter.php';

require '../mod/lpf/googlevoice/class.googlevoice.php';

global $global;

// create an array as it does not exist previosuly and will make warnings
$global['xajax_functions'] = array();

// publicly register accessible xajax funtions
array_push($global['xajax_functions'],'em_append_log');
array_push($global['xajax_functions'],'em_prepend_log');
array_push($global['xajax_functions'],'em_show_message');
array_push($global['xajax_functions'],'em_show_events');
array_push($global['xajax_functions'],'em_perform_edit');
array_push($global['xajax_functions'],'em_perform_delete');
array_push($global['xajax_functions'],'em_perform_purge');
array_push($global['xajax_functions'],'em_perform_insert');
array_push($global['xajax_functions'],'em_perform_save');
array_push($global['xajax_functions'],'em_perform_help');
array_push($global['xajax_functions'],'em_send_post');
array_push($global['xajax_functions'],'em_notify_event');
array_push($global['xajax_functions'],'em_get_prev_msg');
array_push($global['xajax_functions'],'em_get_short_url');
array_push($global['xajax_functions'],'em_save_new_post');
array_push($global['xajax_functions'],'em_save_post_error');
/*
array_push($global['xajax_functions'],'em_format_title');
array_push($global['xajax_functions'],'em_insert_node');
array_push($global['xajax_functions'],'em_edit_node');
array_push($global['xajax_functions'],'em_append_node');
array_push($global['xajax_functions'],'em_delete_node');
*/	
//$prevMsg = '';

// insert new node to dynatree
/*
function em_insert_node($id, $user, $msg) {
	global $conf;
	global $global;
	require_once($global['approot']."/inc/lib_uuid.inc");
        require_once($global['approot']."/inc/lib_image.inc");
        require_once($global['approot']."/inc/lib_locale/gettext.inc");
	if ($_SESSION['logged_in'] != true ) return;

	$s = "insert into ntfy_messages(configid, user_name, message, sent) values('$id', '$user', '$msg', now())";
	$r = $global['db']->Execute($s);
	if($r === false) {
$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>error insert ntfy_messages: '.$global['db']->ErrorMsg());
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "send post");  return($log."error!<br>");
	}

	return $global['xajax_res']->getXML();
}
*/

function em_format_title($s, $isnew=0) {

//	$s = str_replace("\r\n", " ", $s);
	$num = 0;
	$prefix = '';
	if ($isnew==1) {
		$num = 63;
		$prefix = 'New: ';
	}
	else {
		$num = 58;
		$prefix = 'Last sent: ';
	}
	$r = substr($s,0,$num);
	$r .= (strlen($s)>$num?'...':'');

	return $prefix.$r;
}

// save new Message to ntfy_messages
function em_save_new_post($id, $user, $msg) {
	global $conf;
	global $global;
	require_once($global['approot']."/inc/lib_uuid.inc");
        require_once($global['approot']."/inc/lib_image.inc");
        require_once($global['approot']."/inc/lib_locale/gettext.inc");
	if ($_SESSION['logged_in'] != true ) return;

	$s = "insert into ntfy_messages(configid, user_name, message, sent) values('".mysql_real_escape_string($id)."', '".mysql_real_escape_string($user)."', '".str_replace("\r\n", " ", mysql_real_escape_string($msg))."', now())";
	$r = $global['db']->Execute($s);
	if($r === false) {
$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>error insert ntfy_messages: '.$global['db']->ErrorMsg());
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "send post");  return($log."error!<br>");
	}

	return $global['xajax_res']->getXML();
}

// save post error to ntfy_error
function em_save_post_error($id, $user, $msg) {
	global $conf;
	global $global;
	require_once($global['approot']."/inc/lib_uuid.inc");
        require_once($global['approot']."/inc/lib_image.inc");
        require_once($global['approot']."/inc/lib_locale/gettext.inc");
	if ($_SESSION['logged_in'] != true ) return;

	$s = "insert into ntfy_error(configid, username, error) values('$id', '$user', '$msg')";
	$r = $global['db']->Execute($s);
	if($r === false) {
$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>error insert ntfy_error: '.$global['db']->ErrorMsg());
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "send post");  return($log."error!<br>");
	}

	return $global['xajax_res']->getXML();
}

function splitText($s, $delimiter, $limit) {
	$p = '';
	$i = 0;
	$j = 0;
	$len = 0;
	$r = array();
	if (strlen($s)<=$limit)
		$r[0] = $s;
	else {
		$arr = explode($delimiter, $s);
		$len = 0;
		$prefix = '';
		while ($i<count($arr)) {
			$prefix = "#".($j+1).".";
			if ($p=='')
				$p = $prefix . $arr[$i];
			else
				$p .= ' ' . $arr[$i];
			$p = trim($p);
			$len = strlen($p);
			if ($len > $limit) {
				$p = substr($p, 0, $len-strlen($arr[$i])-1);
				$r[$j++] = $p;
				$p = '';
			}
			else if ($len == $limit) {
				$r[$j++] = $p;
				$p = '';
				$i++;
			}
			else {
				$i++;
			}
		}
		if (strlen($p)>0)
			$r[count($r)] = $p;
	}
	//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>count:'.count($r));
	return $r;
}

// send post
function em_send_post($msg=null) {
	global $conf;
	global $global;
	require_once($global['approot']."/inc/lib_uuid.inc");
        require_once($global['approot']."/inc/lib_image.inc");
        require_once($global['approot']."/inc/lib_locale/gettext.inc");
	if ($_SESSION['logged_in'] != true ) return;
/*
$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>m:'.$msg[0]);
	preg_match('/<([0-9]+)>/', $msg[0], $matches);
	$s_match = $matches[0];
	$id = $matches[1];
	$z = 0;
	$foundit = 0;
	$arr = null;
	$m = substr($msg[0], strlen($s_match));
	$arr = splitText($m, ' ', 140);
$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>m:'.$m);
$c = count($arr);
$i = 0;
while ($i < $c) {
$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>'.$arr[$i]);
$i++;
}
return $global['xajax_res']->getXML();
*/

//foreach ($msg as $ma) {
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>');
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', $ma.data.tooltip); //var_dump($a.data.tooltip));
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>');
//}
//return $global['xajax_res']->getXML();

	$s = "
		select id, outType, nckey, value from ntfy_config;
	";
	$r = $global['db']->Execute($s);
	if($r === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "send post");  return($log."error!<br>"); }

	$config = array();
	$count = 0;
	while($row = $r->FetchRow()) {
		$config[$count] = $row;
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>value:'.$config[$count]['value']);
		$count++;
	}

$i = 0;
foreach ($msg as $msgi) {
	preg_match('/<([0-9]+)>/', $msgi, $matches);
	$s_match = $matches[0];
	$id = $matches[1];
	$z = 0;
	$foundit = 0;
	$arr = null;
	while ($z < $count) {
		if ($id == $config[$z]['id']) {
			$m = substr($msgi, strlen($s_match));
			$a = explode("|", $config[$z]['value']);

			switch ( $config[$z]['nckey'] ) {
				case "Facebook":
					try {
						$facebook = new Facebook(array(
							'appId'  => $a[0],
							'secret' => $a[1],
							'cookie' => true,
						));
						$token = $facebook->getAccessToken();
						$post =  array(
							'access_token' => $token,
							'message' => $m
						);
						$res = $facebook->api('/'.$a[2].'/feed', 'POST', $post);
						$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>New post was sent to Facebook');
					}
					catch (Exception $e) {
						em_save_post_error($id, $_SESSION['user'], $e->getMessage());
						$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>Facebook error:'.$e->getMessage());
					}
					break;
				case "Twitter":
					try {
						$twitterObj = new EpiTwitter($a[0], $a[1], $a[2], $a[3]); // //$consumer_key, $consumer_secret, $token, $secret);
						$arr = splitText($m, ' ', 140);
						$i=count($arr)-1;
						while ($i >= 0) {
							$status = $twitterObj->post('/statuses/update.json', array('status' => $arr[$i]));
							$i--;
						}
						$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>New post was sent to Twitter');
					}
					catch (Exception $e) {
						em_save_post_error($id, $_SESSION['user'], $e->getMessage());
						$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>Twitter error:'.$e->getMessage());
					}
					break;
				case "Email":
					try {
						$subject = "notification from event manager";
						$bodyHTML = $m;
						$bodyAlt = $m;
						if (strpos($m, "|")>0) {
							$arr = explode("|", $m);
							$subject = $arr[0];
							$bodyHTML = $arr[1];
							$bodyAlt = $arr[1];
						}
						$pop = new pop();
						$pop->sendMessage($a[1], null, $subject, $bodyHTML, $bodyAlt);
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>Message sent to: '.$a[1].','.$subject.','.$bodyHTML);
						$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>New email was sent to '. $a[0] . ', status: '.$pop->messages);
						unset($pop);
					}
					catch (Exception $e) {
						em_save_post_error($id, $_SESSION['user'], $e->getMessage());
						$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>Email error:'. $e->getMessage());
					}
					break;
				case "SMS":
					try {
						$gv = new GoogleVoice($a[2], $a[3]);
						$arr = splitText($m, ' ', 140);
						$i=count($arr)-1;
						while ($i >= 0) {
							$gv->sms($a[1], $arr[$i]);
							$i--;
						}
						$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>New SMS message was sent to '. $a[0]. ', status: '.$gv->status);
					}
					catch (Exception $e) {
						em_save_post_error($id, $_SESSION['user'], $e->getMessage());
						$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>SMS error:'. $e->getMessage());
					}
			}

			em_save_new_post($id, $_SESSION['user'], mysql_real_escape_string($m));
			break;
		}
		$z++;
	}
	$i++;
}

/*
0,DynaTreeNode: 'Social Media'
1,DynaTreeNode<9>: 'Facebook'
2,DynaTreeNode<9>: 'New: A new event BIG has occurred tweet test'
3,DynaTreeNode<10>: 'Twitter'
4,DynaTreeNode<10>: 'New: A new event BIG has occurred tweet test'

*/

//$_SESSION['user'].' | '.$_SESSION['full_name']);

// need to decide if saving messages to ntfy_messages first, then send them
// or send them first, then save them to tables

	return $global['xajax_res']->getXML();
}

function urlOK($url)
{

    $url_data = parse_url ($url);
    if (!$url_data) return FALSE;

   $errno="";
   $errstr="";
   $fp=0;

   $fp=fsockopen($url_data['host'],80,$errno,$errstr,30);

   if($fp===0) return FALSE;
   $path ='';
   if  (isset( $url_data['path'])) $path .=  $url_data['path'];
   if  (isset( $url_data['query'])) $path .=  '?' .$url_data['query'];

   $out="GET /$path HTTP/1.1\r\n";
   $out.="Host: {$url_data['host']}\r\n";
   $out.="Connection: Close\r\n\r\n";

   fwrite($fp,$out);
   $content=fgets($fp);
   $code=trim(substr($content,9,4)); //get http code
   fclose($fp);
   // if http code is 2xx or 3xx url should work
   return  ($code[0] == 2 || $code[0] == 3) ? TRUE : FALSE;
}

function em_get_short_url($longurl) {
        global $conf;
        global $global;
        require_once($global['approot']."/inc/lib_uuid.inc");
        require_once($global['approot']."/inc/lib_image.inc");
        require_once($global['approot']."/inc/lib_locale/gettext.inc");
        if ($_SESSION['logged_in'] != true ) return;


	$s = "
		SELECT short_url
		FROM ntfy_short_urls
		WHERE long_url = '".$longurl."'
	;";
        $res = $global['db']->Execute($s);
        if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "get short URL"); }

	$shorturl = '';
	if ($row = $res->FetchRow()) {
		$shorturl = $row['short_url'];
	}
	else {

		$apiKey = 'AIzaSyAgpx-svmRIrHnJxzoqA7G1AZaoxKyLMD0';
		//Get API key from : http://code.google.com/apis/console/

		$postData = array('longUrl' => $longurl, 'key' => $apiKey);
		$jsonData = json_encode($postData);

		$curlObj = curl_init();

		curl_setopt($curlObj, CURLOPT_URL, 'https://www.googleapis.com/urlshortener/v1/url');
		curl_setopt($curlObj, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curlObj, CURLOPT_SSL_VERIFYPEER, 0);
		curl_setopt($curlObj, CURLOPT_HEADER, 0);
		curl_setopt($curlObj, CURLOPT_HTTPHEADER, array('Content-type:application/json'));
		curl_setopt($curlObj, CURLOPT_POST, 1);
		curl_setopt($curlObj, CURLOPT_POSTFIELDS, $jsonData);

		$response = curl_exec($curlObj);

		//change the response json string to object
		$json = json_decode($response);

		curl_close($curlObj);

		$shorturl = $json->id;

		if ($shorturl) {

			$s = "INSERT INTO ntfy_short_urls select '$longurl', '$shorturl'
			;";

			$res = $global['db']->Execute($s);
			if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "insert new short URL"); }
		}
	}
	return $shorturl;
}

function extractPart($arr, $delimiter,  $partNum) {
	$a = explode($delimiter, $arr);
	if (count($a)>0)
		return $a[$partNum];
}

// pops up dialog to customize a outgoing message
function em_notify_event ($disaster_id, $longname, $shortname) {
        global $conf;
        global $global;
        require_once($global['approot']."/inc/lib_uuid.inc");
        require_once($global['approot']."/inc/lib_image.inc");
        require_once($global['approot']."/inc/lib_locale/gettext.inc");
        if ($_SESSION['logged_in'] != true ) return;

	// block builds the tree that displays outgoing message types
	$nc1 = "
		SELECT id, trim( outType ) AS outType, trim( nckey ) AS nckey, trim( icon ) AS icon, trim( value ) AS value, (
		SELECT sysgenid
		FROM ntfy_messages
		WHERE configid = c.id
		ORDER BY sent DESC
		LIMIT 1
		) AS sysgenid, (

		SELECT trim( message )
		FROM ntfy_messages
		WHERE configid = c.id
		ORDER BY sent DESC
		LIMIT 1
		) AS message, (

		SELECT sent
		FROM ntfy_messages
		WHERE configid = c.id
		ORDER BY sent DESC
		LIMIT 1
		) AS sent, (

		SELECT trim( user_name )
		FROM ntfy_messages
		WHERE configid = c.id
		ORDER BY sent DESC
		LIMIT 1
		) AS user_name
		FROM ntfy_config c
		ORDER BY seq;
	";
        $ncres1 = $global['db']->Execute($nc1);
        if($ncres1 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "get prev msg"); }
	$nctypes = array();
	$ncvalues = array();
	$ncvcount = 0;
	$z = 0;
	while($ncrow = $ncres1->FetchRow()) {
		$ncvalues[$ncvcount] = $ncrow;
		if ( !in_array($ncvalues[$ncvcount]['outType'], $nctypes))
			array_push($nctypes, $ncvalues[$ncvcount]['outType']);
		$ncvcount++;
	}       
	$i = 0;
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>in em_notify_event<br>');


//<input type=\"text\" size=45 value = \"" + prevTitle + "\"/>
//<input type=\"text\" size=45 value = \"" + prevTitle + "\"/>

	// create the Notification tree
	// provides editing on new messages only
	$s = '
	function format_title(s, isnew) {
		var num = 0;
		var prefix = "";
		if (isnew==1) {
			num = 63;
			prefix = "New: ";
		}
		else {
			num = 58;
			prefix = "Last sent: ";
		}
		r = s.substring(0,num);
		r += (s.length>num?"...":"");
		return prefix+r.replace(/(\r\n)/g, " ");
	}

	function editNode(node){
		var prevTitle = node.data.href, tree = node.tree;
		if (node.data.title.toLowerCase().substring(0,5) != "new: ") return;
		// Disable dynatree mouse- and key handling
		tree.$widget.unbind();

		// Replace node with <input>
		// Focus <input> and bind keyboard handler
		if (node.getParent().getParent().data.title.toLowerCase() == "email") {
			$("#editEmail").dialog("open");
			$("#editEmail").dialog("option", "title", "Edit Email to "+node.getParent().data.title);
			if (prevTitle.indexOf("|")>0) {
				var a = prevTitle.split("|");
				$("#subject").val(a[0]);
				$("#body").val(a[1]);
			}
			else {
				$("#subject").val(prevTitle);
				$("#body").val(prevTitle);
			}
			tree.$widget.bind();
			node.focus();
		}
		else if (node.getParent().data.title.toLowerCase() == "twitter") {
			//$("#editTwitter").dialog("option", "title", "Edit Twitter");
			if (prevTitle.indexOf("...")>0) {
				$("#tweet").val(node.data.tooltip.substring(4));
			}
			else {
				$("#tweet").val(prevTitle.substring(4));
			}
			$("#editTwitter").dialog("open");
			tree.$widget.bind();
			node.focus();
		}
		else {
			$(".dynatree-title", node.span).html("<input id=\"editNode\" type=\"text\" size=45 value = \"" + prevTitle.substring(4) + "\" />");
			$("input#editNode")
			.focus()
			.keydown(function(event){
				switch( event.which ) {
					case 27: // [esc]
						// discard changes on [esc]
						$("input#editNode").val(prevTitle);
						$(this).blur();
						break;
					case 13: // [enter]
						// simulate blur to accept new value
						$(this).blur();
						break;
				}
			})
			.blur(function(event){
				// Accept new value, when user leaves <input>
				var title = $("input#editNode").val();
				node.setTitle(format_title(title,1));
				node.data.href = title;
				node.data.tooltip = format_title(title,1);
				var button = $(":button:contains(\'Send Notification\')");
				enableButton(button);
				// Re-enable mouse and keyboard handlling
				tree.$widget.bind();
				node.focus();
			});
		}
	}
	';

//$('#rezLog').append('<br>'+node.getLevel());
	$s .= "
	function enableButton(button) {
		button.attr(\"disabled\", true).removeClass(\"ui-state-disabled\");
		button.attr(\"disabled\", false).addClass(\"ui-state-enabled\");
	}

	function disableButton(button) {
		button.attr(\"disabled\", false).removeClass(\"ui-state-enabled\");
		button.attr(\"disabled\", true).addClass(\"ui-state-disabled\");
	}

	var savedMsgs = new Array();
	function saveInitialMsg() {
		if (savedMsgs.length>0) return;
		var num = 0;
		var i = 0;
		$('#tree').dynatree(\"getRoot\").visit(function(node){
			if (node.getLevel() == 4) {
				savedMsgs[i] = new Array();
				savedMsgs[i][0] = node.data.key;
				savedMsgs[i][1] = node.data.title;
				savedMsgs[i][2] = node.data.tooltip;
				i++;
			}
		});
	}

	function mytrim(s) {  
		return s.replace(/^\s+|\s+$/g,'');  
	};  

	function splitText(s, delimiter, limit) {
		var p = '';
		var i = 0;
		var j = 0;
		var len = 0;
		var r = new Array();
		if (s.length<=limit)
			r[0] = s;
		else {
			var arr = s.split(delimiter);
			i = 0;
			j = 0;
			len = 0;
			var prefix = '';
			while (i<arr.length) {
				prefix = '<'+j+'>';
				if (p=='')
					p = prefix + arr[i];
				else
					p += ' ' + arr[i];
				len = p.length;
				if (len > limit) {
					p = p.substr(0, len-(arr[i].length));
					r[j++] = p;
					p = '';
				}
				else if (len == limit) {
					r[j++] = p;
					p = '';
					i++;
				}
				else {
					i++;
				}
			}
			if (p.length>0)
				r[r.length] = p;
		}
		return r;
	}

	function insertNode(node, el) {
		var curKey = node.data.key;
		
		$( '#insertRecipient' ).dialog({
			icon: \"move.png\",
			autoOpen: false,
			draggable: true,
			closeOnEscape: false, 
			resizable: false,
			height: \"auto\",
			width: \"auto\",
			modal: true,
			buttons: {
				'Save': function() {
					deSelectAll();
					var node = $('#tree').dynatree('getActiveNode');
					if (node) node.deactivate();
					$( this ).dialog( 'close' );
				},
				Cancel: function() {
					deSelectAll();
					var node = $('#tree').dynatree('getActiveNode');
					if (node) node.deactivate();
					$( this ).dialog( 'close' );
				}
			},
			close: function() {
				//allFields.val( \"\" ).removeClass( \"ui-state-error\" );
				//$(\"#tree\").dynatree(\"getTree\").reload();
				var node = $('#tree').dynatree('getActiveNode');
				if (node) node.deactivate();
				deSelectAll();
				//$(this).remove();
				}
		}).bind(\"dialogopen\", function (event, ui) {
			$('#prevMsg').html(\"\");
			$('#newMessage').val(\"\");

			// disable Send Notification button initially
			var notify_button = $(\":button:contains('Send Notification')\");
			disableButton(notify_button);

			var savemsg_button = $(\":button:contains('Save New Message')\");
			disableButton(savemsg_button);

			saveInitialMsg();

			// fix for width:auto in IE
			var contentWidth = $(this).width();
			$(this).parent().find('.ui-dialog-titlebar').each(function () {
				$(this).width(contentWidth-2);
			});
			$(this).parent().find('.ui-dialog-buttonpane').each(function () {
				$(this).width(contentWidth);
			});
		}).bind(\"dialogresize\", function (event, ui) {
			// fix for width:auto in IE
			var contentWidth = $(this).width();
			$(this).parent().find('.ui-dialog-titlebar').each(function () {
				$(this).width(contentWidth-2);
			});
			$(this).parent().find('.ui-dialog-buttonpane').each(function () {
				$(this).width(contentWidth);
			});
		})
		;
		$('#insertRecipient').dialog('open');
		node.getParent().addChild({
			title: \"ABC node\", key:1,
			tooltip: \"This folder and all child nodes were added programmatically.\"
		});
		var cmp = function(a, b) {
			a = a.data.key;
			b = b.data.key;
			return a > b ? 1 : a < b ? -1 : 0;
		};

		node.getParent().sortChildren(null, false);
	}

	function appendNode(node, el) {
		alert('append:' + node.data.title);
	}

	function deleteNode(node, el) {
		node.remove();
	}

	function bindContextMenu(node, span) {
		// disabled at the moment
		return;
		// Add context menu to this node:
		$(span).contextMenu({menu: \"manageRecipients\"}, function(action, el, pos) {
			// The event was bound to the <span> tag, but the node object
			// is stored in the parent <li> tag
//			var node = $.ui.dynatree.getNode(el);
//alert(node.data.title);
			switch( action ) {
				case \"insert\":
					insertNode(node, el);
					break;
				case \"append\":
					appendNode(node, el);
					break;
				case \"delete\":
					deleteNode(node, el);
					break;
				default:
					alert(\"Todo: appply action '\" + action + \"' to node \" + node);
			}

		});
	};

	function undo(node) {
		var k = node.data.key;
/*
		for (var i=0; i<savedMsgs.length; i++) {
			if (savedMsgs[i][0] == k) {
				node.setTitle(savedMsgs[i][1];
				node.data.tooltip = (savedMsgs[i][2];
			}
		}
*/
	}

	var leftPartWidth = 0, leftPartHeight = 0, rightPartWidth = 0, rightPartHeight = 0;
	// create tree-view ui that hosts the post receivers
	$('#tree').dynatree({
		checkbox: true,
		imagePath: \"res/emntfy/base/images/\",
		selectMode: 3,
		expand: true,
		onClick: function(node, event) {
			if(event.which==1 && (node.tree.isUserEvent()) && node.getLevel()<4) {
				$('#prevMsg').html(\"\");
				$('#newMessage').val(\"\");
				if (node.getLevel()==3) {
					node.visit(function(c){
						if (c.getLevel() == 4) {
							$('#newMessage').val(c.data.href);
							if (c.getParent().getParent().data.title == \"Email\") {
								if (c.data.href.indexOf(\"|\")>0) {
									var a = c.data.href.split(\"|\");
									$('#newMessage').val(a[1]);
								}
							}
						}
					});
				}
				if (node.data.title == \"Twitter\" || node.data.title == \"SMS\") {
		//button.attr(\"disabled\", true).removeClass(\"ui-state-disabled\");
		//$('#charLeftDiv').attr(\"disabled\", false).addClass(\"ui-state-enabled\");
					//$('#charLeftDiv').toggle(true);
					$('#charLeftDiv').show();
					$('#charLeft').show();
					$('#charLeft').html( 140 - parseInt($('#newMessage').val().length) );
					$('#newMessage').bind(\"textchange\", function (event, previousText) {
						var limit = 140;
						var text = $('#newMessage').val();
						var len = parseInt(text.length);
						$('#charLeft').html( limit - len );
						if (limit == len)
						  $('#newMessage').val(text.substr(0,limit));
					});
				}
				else {
					$('#charLeftDiv').hide();
					$('#charLeft').hide();
				}
				em_get_prev_msg(node.data.key, $('#filter').val(), $('#showLast').val());
			}
			// return false; // this breaks/stops subsequent processing
		},
		onDblClick: function(node, event) {
			editNode(node);
			return false;
		},

		onSelect: function(flag, node) {
			var foundit=0;
			var selectedNodes = $(\"#tree\").dynatree(\"getSelectedNodes\");
			var button = $(\":button:contains('Send Notification')\");
			if (selectedNodes.length>0) {
				enableButton(button);
			}
			else {
				disableButton(button);
			}
		},

		onCreate: function(node, span){
			if (node.getLevel()==3) {
				bindContextMenu(node, span);
			}
		},
/*
		dnd: {
			preventVoidMoves: true, // Prevent dropping nodes 'before self', etc.
			onDragStart: function(node) {
				return true;
			},
			onDragEnter: function(node, sourceNode) {
				if(node.parent !== sourceNode.parent)
					return false;
				return [\"before\", \"after\"];
			},
			onDrop: function(node, sourceNode, hitMode, ui, draggable) {
				sourceNode.move(node, hitMode);
			}
		},
*/
		children: [
			{title: \"All\", key:\"All\",hideCheckbox:false, expand: true, icon: \"globe.png\", 
				children: [
	";

	while($i < count($nctypes)) {
		$j = 0;
		if ($i>0) $s .= ",";
		$init = 0;
		while ($j < $ncvcount) {
			if ($ncvalues[$j]['outType'] == $nctypes[$i]) {

				if ($init==0) {

					$icon = strtolower(str_replace(' ', '-', $ncvalues[$j]['outType'])). '.png';

					$s .= "{title: \"".$ncvalues[$j]['outType']."\", key: \"".$ncvalues[$j]['outType']."\", expand: true, icon: \"$icon\",
						children: 
							[
					";

				}
				if ($init!=0) $s .= ",";

				$t_title = $ncvalues[$j]['nckey'];
				$arr = explode('|', $ncvalues[$j]['value']);
				if ($ncvalues[$j]['nckey']=='Email' || $ncvalues[$j]['nckey']=='SMS')
					$t_title = $ncvalues[$j]['nckey'] . ' [' . $arr[0]. ']';

				$ttt = em_format_title( $ncvalues[$j]['message']);
								//{title: \"Last sent: ".$ncvalues[$j]['sent']." [". $tmp ."]\", key: \"".$ncvalues[$j]['id']."\", 

				$toRecipient = "";
				if ($ncvalues[$j]['outType']=='Email' || $ncvalues[$j]['outType']=='SMS')
					$toRecipient = 'tooltip:"'.extractPart($ncvalues[$j]['value'],'|',1).'",';
				$s .= "
					{title: \"". $t_title . "\", key: \"". $ncvalues[$j]['id']. "\", expand: true, icon: \"". $ncvalues[$j]['icon']. "\", 
						". $toRecipient . "
						children: 
							[
								{title: \"". $ttt ."\", key: \"".$ncvalues[$j]['id']."\", hideCheckbox: true,
									icon:false, href: \"".$ncvalues[$j]['message']."\", tooltip: \"Last message [". $ncvalues[$j]['message']. "] was sent by ". 
$ncvalues[$j]['user_name'].($ncvalues[$j]['outType']=='Email'?' to '.$ncvalues[$j]['value']:''). " on ". $ncvalues[$j]['sent']. "\"
}
							]
					}";
				$init = 1;
			}
			$j++;
		}
		$s .= ']}';

		$i++;
	}
	$s .= ']
	}]
})';
// debug $global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>'.$s);
	// block retrieves google shortened url
	$longUrl = "https://".$_SERVER['SERVER_NAME']."/".$shortname."/search";
	$shortUrl = em_get_short_url($longUrl);


//$wt_list = "";

/*
$('#twitter').bind('textchange', function (event, previousText) {
  $('#charactersLeft').html( 140 - parseInt($(this).val().length) );
});
			$('#prevMsg').change(function() {
				$('#newMessage').trigger('click');
			});
// debug $('#rezLog').append('<br>'+childNodes[child]);
//$('#rezLog').append('<br>'+c.getLevel());
*/

	$send = "
		function filterStr(s) {
			return s.replace(/\\r/g, \"\").replace(/\\n/g, \"\").replace(/\\t/g, \"\");
		}

		function format_title(s, isnew) {
			var num = 0;
			var prefix = '';
			var r = '';
			if (isnew==1) {
				num = 63;
				prefix = 'New: ';
			}
			else {
				num = 58;
				prefix = 'Last sent: ';
			}
			r = s.substring(0,num);
			r += (s.length>num?'...':'');

			return prefix+r;
		}

		function deSelectAll() {
			var selectedNodes = $(\"#tree\").dynatree(\"getSelectedNodes\");
			var selectedKeys = $.map(selectedNodes, function(node){
				node.deactivate();
				node.select(false);
			});
		}

		function sendMsg() {
			var selectedNodes = $(\"#tree\").dynatree(\"getSelectedNodes\");
			var selectedKeys = $.map(selectedNodes, function(node){
				if (node.getLevel()==4) {
					if (node.data.title.substring(0,5) == \"New: \") {
						return \"<\"+node.data.key+\">\"+node.data.href;
					}
				}
			});
//alert(selectedKeys.join(\", \")); DO NOT USE join when passing into em_send_post
			em_send_post(selectedKeys);

			// hide char count for twitter
			$('#charLeftDiv').hide();
			$('#charLeft').hide();

			$.map(selectedNodes, function(node){
				if (node.getLevel()==4) {
					node.setTitle(format_title(node.data.href,0));
					node.data.tooltip = \"Last message \"+ node.data.href;
				}
			});
		}
	";

	$s2 = "";

	$s2 .= "
		jQuery(document).ready(function() {
		". $send . "

			$( '#notify' ).dialog({
				icon: \"move.png\",
				autoOpen: false,
				draggable: true,
				closeOnEscape: false, 
				resizable: false,
				height: \"auto\",
				width: \"auto\",
				modal: true,
				buttons: {
					'Send Notification': function() {
						sendMsg();
						deSelectAll();
						var node = $('#tree').dynatree('getActiveNode');
						if (node) node.deactivate();
						$( this ).dialog( 'close' );
					},
					Cancel: function() {
						deSelectAll();
						var node = $('#tree').dynatree('getActiveNode');
						if (node) node.deactivate();
						$( this ).dialog( 'close' );
					}
				},
				close: function() {
					//allFields.val( \"\" ).removeClass( \"ui-state-error\" );
					//$(\"#tree\").dynatree(\"getTree\").reload();
					var node = $('#tree').dynatree('getActiveNode');
					if (node) node.deactivate();
					deSelectAll();
					//$(this).remove();
				}
			}).bind(\"dialogopen\", function (event, ui) {
				$('#prevMsg').html(\"\");
				$('#newMessage').val(\"\");

				// disable Send Notification button initially
				var notify_button = $(\":button:contains('Send Notification')\");
				disableButton(notify_button);

				var savemsg_button = $(\":button:contains('Save New Message')\");
				disableButton(savemsg_button);

				saveInitialMsg();
	
                                // fix for width:auto in IE
                                var contentWidth = $(this).width();
                                $(this).parent().find('.ui-dialog-titlebar').each(function () {
                                        $(this).width(contentWidth-2);
                                });
                                $(this).parent().find('.ui-dialog-buttonpane').each(function () {
                                        $(this).width(contentWidth);
                                });
			}).bind(\"dialogresize\", function (event, ui) {
                                // fix for width:auto in IE
                                var contentWidth = $(this).width();
                                $(this).parent().find('.ui-dialog-titlebar').each(function () {
                                        $(this).width(contentWidth-2);
                                });
                                $(this).parent().find('.ui-dialog-buttonpane').each(function () {
                                        $(this).width(contentWidth);
                                });
                        })
			;

			$('#eventName').val('".$longname."/".$shortname."');
//			$('#eventNameShort').val('".$shortname."');
			$('#eventUrl').val('".$longUrl."');
			$('#shortUrl').val('". $shortUrl . "');
			$('#notify').dialog({ title: \"Event Notification for $longname (long), $shortname (short)\" });

			// add script to create tree (dynatree plug-in)
			if ((_canLog) && (typeof $('#tree').attr('name') != 'undefined')) {" 
				. $s ."
			}

			// add text change event
			$('#newMessage').bind('textchange', function (event, previousText) {
				if ($('#tree').dynatree('getActiveNode'))
					$(this).val(filterStr($(this).val()));
				else {
					$(this).val('');
					alert('Please select a recipient first.');
				}

				var button = $(\":button:contains('Save New Message')\");
				if ($(this).val().length==0)
					disableButton(button);
				else
					enableButton(button);
			});


			// monitor previous msg shown input to ensure all numbers are entered
			// saved for future <input id= ... onkeyup=\"this.value=this.value.replace(/\D/g,'')\"/>
			$('#showLast').bind('textchange', function (event, previousText) {
				if ($(this).val()!=\"*\" && isNaN($(this).val()))
					$(this).val(previousText);
			});

			// event handling for button Save New Message
			$('#saveNewMsg').click(function () {
				var node = $('#tree').dynatree('getActiveNode');
				var childNodes = node.getChildren();

				// set New Message to all children nodes
				node.visit(function(c){
                    			if (c.getLevel()==4) { /// && c.data.title.substring(0,10)=='Last sent:') {
						//n = c; //nxt[0];
						var newmsg = $.trim($('#newMessage').val());
						$('#newMessage').val(newmsg);
						c.data.href = newmsg;
						c.data.tooltip = 'New: '+newmsg;
						var newtitle = format_title( newmsg, 1);	
						c.setTitle(newtitle);
						c.select(true);
//						c.data.hideCheckbox = false;
						c.data.addClass = \"myMenu\";
						c.getParent().select(true);
						//n.getParent().data.hideCheckbox = false;
/*
						$.contextMenu({
							selector: '.myMenu', //dynatree-title', //context-menu-one', 
							callback: function(key, options) {
								switch (key) {
									case \"undo\":
										undo(c);
										break;
									case \"edit\":
										if (c.getParent().getParent().data.title == \"Email\") {
											$('#editEmail').dialog(\"open\");
											$('#editEmail').dialog(\"option\", \"title\", \"Edit Email (\"+node.getParent().data.title+\")\");
										}
										break;
								}
							},
							items: {
								\"undo\": {name: \"Undo\", icon: \"undo\"},
								\"edit\": {name: \"Edit\", icon: \"edit\"},

							}
						});
*/ 
						c.render();
						c.getParent().render();
					}
               			 });

				// enable Send Notification button
				var button = $(\":button:contains('Send Notification')\");
				enableButton(button);

				// again disable the Save New Message button until next new message is entered, detected
//				$(this).addClass('disabled').attr('disabled', true);
				var button = $(\":button:contains('Save New Message')\");
				disableButton(button);
			});

			$('#prevMsg').change(function () {
				var str = $(this).find(\":selected\").attr(\"title\");
				var fin = \"\"; 
				if (str) {
					fin = str.substr(str.indexOf(\"[\")+1, str.indexOf(\"]\")-1-str.indexOf(\"[\"));
					$('#newMessage').val(fin);
					$('#newMessage').trigger('textchange');
//					$('#saveNewMsg').change();

				}
			//		$(\"select option:selected\").each(function () {
			//			str += $(this).text() + \" \";
			//		});
			//		$('#newMsg').val(str
			})
//			.trigger('change')
			;

			$( '#tabs' ).tabs().bind(\"tabcreate\", function (event, ui) {
			})
			;
//			$('#saveNewMsg').attr(\"disabled\", \"true\");

			$('#word-template').sortable({ opacity: 0.9, cursor: \"move\"});

			$( '#editTwitter' ).dialog({
				autoOpen: false,
				draggable: true,
				closeOnEscape: false, 
				resizable: false,
				height: \"auto\",
				width: \"auto\",
				modal: true,
				buttons: {
					\"Save and Close\": function() {
						var node = $('#tree').dynatree('getActiveNode');
						var newTitle = \"New: \" + $('#tweet').val();
						var len = newTitle.length;
						node.data.tooltip = newTitle;
						//var finaltitle = newTitle.substring(0, (len>63?63:len)) + (len>63?\"...\":\"\");
						node.setTitle(format_title(newtitle,1));
						var button = $(\":button:contains('Send Notification')\");
						enableButton(button);
						$( this ).dialog( \"close\" );
					},
					Cancel: function() {
						$( this ).dialog( \"close\" );
					}
				},
				close: function() {
					//allFields.val( \"\" ).removeClass( \"ui-state-error\" );
				}
			}).bind(\"dialogopen\", function (event, ui) {
                                var contentWidth = $(this).width();
                                $(this).parent().find(\".ui-dialog-titlebar\").each(function () {
                                        $(this).width(contentWidth-2);
                                });
                                $(this).parent().find(\".ui-dialog-buttonpane\").each(function () {
                                        $(this).width(contentWidth);
                                });

				$('#charCount').html( 140 - parseInt($('#tweet').val().length) );
				$('#tweet').bind(\"textchange\", function (event, previousText) {
					var limit = 140;
					var text = $('#tweet').val();
					var len = parseInt(text.length);
					$('#charCount').html( limit - len );
					if (limit == len)
					  $('#tweet').val(text.substr(0,limit));
				});

			}).bind(\"dialogresize\", function (event, ui) {
                                // fix for width:auto in IE
                                var contentWidth = $(this).width();
                                $(this).parent().find(\".ui-dialog-titlebar\").each(function () {
                                        $(this).width(contentWidth-2);
                                });
                                $(this).parent().find(\".ui-dialog-buttonpane\").each(function () {
                                        $(this).width(contentWidth);
                                });
			})
			;

			$( '#editEmail' ).dialog({
				autoOpen: false,
				draggable: true,
				closeOnEscape: false, 
				resizable: false,
				height: \"auto\",
				width: \"auto\",
				modal: true,
				buttons: {
					\"Save and Close\": function() {
						var node = $('#tree').dynatree('getActiveNode');
						node.data.href = $('#subject').val()+\"|\"+$('#body').val();
						node.data.tooltip = \"New: \"+$('#subject').val()+\"|\"+$('#body').val();
						var newtitle = format_title($('#body').val(),1);
						node.setTitle(newtitle);
						var button = $(\":button:contains('Send Notification')\");
						enableButton(button);
						$( this ).dialog( \"close\" );
					},
					Cancel: function() {
						$( this ).dialog( \"close\" );
					}
				},
				close: function() {
					//allFields.val( \"\" ).removeClass( \"ui-state-error\" );
				}
			}).bind(\"dialogopen\", function (event, ui) {
                                var contentWidth = $(this).width();
                                $(this).parent().find(\".ui-dialog-titlebar\").each(function () {
                                        $(this).width(contentWidth-2);
                                });
                                $(this).parent().find(\".ui-dialog-buttonpane\").each(function () {
                                        $(this).width(contentWidth);
                                });
			}).bind(\"dialogresize\", function (event, ui) {
                                // fix for width:auto in IE
                                var contentWidth = $(this).width();
                                $(this).parent().find(\".ui-dialog-titlebar\").each(function () {
                                        $(this).width(contentWidth-2);
                                });
                                $(this).parent().find(\".ui-dialog-buttonpane\").each(function () {
                                        $(this).width(contentWidth);
                                });
			})
			;

			$('#notify').dialog('open');
			leftPartWidth = $('#leftPart').width();
			leftPartHeight = $('#leftPart').height();
			rightPartWidth = $('#rightPart').width();
			rightPartHeight = $('#rightPart').height();
// 538, 343, 441, 391
//alert(leftPartWidth + ','+leftPartHeight + ',' + rightPartWidth + ',' + rightPartHeight);


		});
	";
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', $s2);
	$global['xajax_res']->addScript($s2);

	
//	$global['xajax_res']->addScript("alert(\"in em_notify_event\");");
	return $global['xajax_res']->getXML();
}



function wildcard($s) {
	$s = trim($s);
	$words = explode(" ", $s);
	if (count($words)==0) return "";
	$r = "%";
	foreach ($words as $w)
		$r .= "%". trim($w);
	$r .= "%";
	$r = "";
	return $r;
}

function em_get_prev_msg($key, $filter="", $last=0) {
        global $conf;
        global $global;
        require_once($global['approot']."/inc/lib_uuid.inc");
        require_once($global['approot']."/inc/lib_image.inc");
        require_once($global['approot']."/inc/lib_locale/gettext.inc");
        if ($_SESSION['logged_in'] != true ) return;

	$newfilter = "";
	if (!empty($filter)) {
	        $words = explode(" ", trim($filter));
		if (count($words)>0) {
			$newfilter = " and message like '";
			foreach ($words as $w)
				$newfilter .= "%". trim($w);
			$newfilter .= "%'";
		}
	}

	$limit = "";
	if (!empty($last) && $last>0) $limit = "limit ".$last;

	$q = "";

	if (is_numeric($key)) {
        	$q = "
		SELECT sysgenid, trim(message) as message, trim(user_name) as user_name, sent
		FROM ntfy_messages
		WHERE configid = $key
		" . $newfilter ."
		ORDER BY sent DESC
		".$limit."
		;
		";
	}
	else {
		if ($key == "All") {
	        	$q = "
			SELECT sysgenid, trim(message) as message, trim(user_name) as user_name, sent
			FROM ntfy_messages
			WHERE configid in ( SELECT id FROM ntfy_config)
			" . $newfilter ."
			ORDER BY sent DESC
			".$limit."
			;
			";
		}
		else { // top level (Social Media, Email, Sms) selected
	        	$q = "
			SELECT sysgenid, trim(message) as message, trim(user_name) as user_name, sent
			FROM ntfy_messages
			WHERE configid in ( SELECT id FROM ntfy_config WHERE outType = '" . $key . "')
			" . $newfilter ."
			ORDER BY sent DESC
			".$limit."
			;
			";
		}
	}

// debug $global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>'.$q);

        $result = $global['db']->Execute($q);
        if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "purge 1");  return($log."error!<br>"); }
	$recCount = $result->RecordCount();
        $count = 0;
	$m = '';
	
	$s = '<select style=\"width:410px;\">';
	if ($recCount == 0) {
		$s .= '<option title=\"none\" value=\"-1\">None retrieved</option>';
		$global['xajax_res']->addAssign('newMessage', 'innerHTML', '');
	}

	else {
		if ($recCount == 1) {
			$s .= '<option title=\"One found\" value=\"0\">Only one was found</option>';
		}
		else {
			$s .= '<option title=\"choose 1 from '.$recCount.'\" value=\"0\">choose 1 from '.$recCount.' messages</option>';
		}
        	while($row = $result->FetchRow()) {
			$t = "[".$row['message']."] from ".$row['user_name']." on ". $row['sent'];
//			if ($row['sysgenid'] ==  $id) $m = $t;
			$s .= "<option title=\"".$t."\" value=\"".$row['sysgenid']."\">".substr($t,0,25). "</option>";
       	        	$count++;
		}
	}
	$s .= '</select>';
	$global['xajax_res']->addAssign('prevMsg', 'innerHTML', $s);
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', $s);
//	$prevMsg = $s;
//	$global['xajax_res']->addAssign('eventMsg', 'innerHTML', '<p>'.$m.'</p>');

//	$temp = "testing";
//	$global['xajax_res']->addAssign('eventUrl', 'text', $temp );

	//$js = '
//	$eventName = $("#eventName").val();
//	$shortUrl = shortenUrl($eventName);
//	$(\"#eventUrl\").val($shortUrl);
//	';
//	$global['xajax_res']->addScript($js);

//	$global['xajax_res']->addAssign('eventUrl', 'innerHTML', $shortUrl);

	return $global['xajax_res']->getXML();
}


// adds a message to the log div @ tail
function em_append_log($message = "no message specified?") {

	global $global;
	$global['xajax_res']->addAppend('rezLog','innerHTML',$message);
	//---- scroll the log to the bottom
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// adds a message to the log div @ head
function em_prepend_log($message = "no message specified?") {

	global $global;
	$global['xajax_res']->addPrepend('rezLog','innerHTML',$message);
	return $global['xajax_res']->getXML();
}


// shows a status message before another ajax function is executed
function em_show_message($message = "no message specified?") {

	global $global;
	$global['xajax_res']->addAssign('rezMain','innerHTML','<div class="loadingMessage"><center><blink>'.$message.'</blink></center></div>');
	return $global['xajax_res']->getXML();
}



// reloads the mainArea div with information of what pages we have
function em_show_events($internal = FALSE) {

	global $conf;
	global $global;
	$htmlLog = "";
	$htmlMain = "<script type=\"text/javascript\">alert('in em_show_events');</script>";
	$total = 0;
	$char = "<span style=\"text-shadow: 1px 1px 1px #000;\">▶</span>";

	$htmlMain .= "
		<table class=\"emTable\">
			<tr>
				<td style=\"font-size: 120%; padding-left: 8px;\" ><b>Event</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;\" ><b>Name</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;\" ><b>Short Name</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Type</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Default</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Visibility</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Open</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Edit</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Notify</b></td>
			</tr>
	";

	// get list of Disasters
	$q = "
		SELECT *
		FROM incident i
		LEFT JOIN sys_user_groups g
		ON i.private_group = g.group_id
		WHERE i.parent_id is NULL
		ORDER BY date desc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "show events 1"); }

	// find out how many disasters we have
	$disasters = array();
	$dcount = 0;
	while($row = $result->FetchRow() ){
		$disasters[$dcount] = $row;
		$dcount++;
	}
	$total = $dcount;

	$i = 1; // we start with the 2nd row of teh table (header?) :)
	$eo = 0; // 2nd row is odd ~ of course u knew that computers start counting at 0 :P
	while($i <= $dcount) {
		$row           = $disasters[$i-1];
		$type          = "<b><span style=\"color: red;\">".$char."</span> Disaster</b>";
		$disaster_id   = $row['incident_id'];
		$type2         = $row['type'];
		$longname      = $row['name'];
		$shortname     = $row['shortname'];
		$default       = $row['default'];
		$private_group = $row['private_group'];
		$closed        = $row['closed'];

		// get text for default event
		if($default == "1") {
			$defaultText = "DEFAULT";
		} else {
			$defaultText = "-";
		}

		// show group name or public if null group
		if($private_group == NULL) {
			$groupText = "PUBLIC";
		} else {
			$groupText = $row['group_name'];
		}

		// generate open close text
		if((int)$closed == 0) {
			$closedText = "OPEN";
		} else if((int)$closed == 1) {
			$closedText = "CLOSED";
		} else if((int)$closed == 2) {
			$closedText = "CLOSED(PF)";
		} else {
			$closedText = "OPEN";
		}

		// find class to color the row...
		if( $eo == 0 ) {
			$evenOddClass = "mainRowEven";
		} else {
			$evenOddClass = "mainRowOdd";
		}

		$htmlMain .= "
			<tr>
				<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$type."</td>
				<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\"><a href=\"#\" onclick=\"em_append_log('Editing Event #<b>".$disaster_id."</b> ...<br>'); em_perform_edit(".$disaster_id.");\" value=\"Edit\">".$longname."</a></td>
				<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$shortname."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$type2."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$defaultText."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$groupText."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$closedText."</td>

<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"em_append_log('Editing Event #<b>".$disaster_id."</b> ...<br>'); em_perform_edit(".$disaster_id.");\" value=\"Edit\"></td>

<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"em_append_log('Notifying Event #<b>".$disaster_id."</b> ...<br>'); em_notify_event(".$disaster_id.",'".$longname."','".$shortname."');\"); \" value=\"Notify\"></td>

			</tr>
		";


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// list all incidents with this disaster as a parent
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// get list of incidents
		$q = "
			SELECT *
			FROM incident i
			LEFT JOIN sys_user_groups g
			ON i.private_group = g.group_id
			WHERE i.parent_id = ".$disaster_id."
			ORDER BY date desc;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "show events 2"); }

		// find out how many incidents we have
		$incidents = array();
		$icount = 0;
		while($row = $result->FetchRow() ){
			$incidents[$icount] = $row;
			$icount++;
		}
		$total += $icount;

		$j = 1;
		while($j <= $icount) {
			$eo++;
			if($eo == 2) {
				$eo = 0;
			}

			$row           = $incidents[$j-1];
			$type          = "<b> &nbsp; &nbsp; <span style=\"color: orange;\">".$char."</span> &nbsp; Incident</b>";
			$incident_id   = $row['incident_id'];
			$type2         = $row['type'];
			$longname      = $row['name'];
			$shortname     = $row['shortname'];
			$default       = $row['default'];
			$closed        = $row['closed'];
			$private_group = $row['private_group'];

			// get text for default event
			if($default == "1") {
				$defaultText = "DEFAULT";
			} else {
				$defaultText = "-";
			}

			// show group name or public if null group
			if($private_group == NULL) {
				$groupText = "PUBLIC";
			} else {
				$groupText = $row['group_name'];
			}

			// generate open close text
			if((int)$closed == 0) {
				$closedText = "OPEN";
			} else if((int)$closed == 1) {
				$closedText = "CLOSED";
			} else if((int)$closed == 2) {
				$closedText = "CLOSED(PF)";
			} else {
				$closedText = "OPEN";
			}

			// find class to color the row...
			if( $eo == 0 ) {
				$evenOddClass = "mainRowEven";
			} else {
				$evenOddClass = "mainRowOdd";
			}

			$htmlMain .= "
				<tr>
					<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$type."</td>
					<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\"><a href=\"#\" onclick=\"em_append_log('Editting Event #<b>".$incident_id."</b> ...<br>'); em_perform_edit(".$incident_id.");\" value=\"Edit\">".$longname."</a></td>
					<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$shortname."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$type2."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$defaultText."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$groupText."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$closedText."</td>
<<<<<<< TREE
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"em_append_log('Editting Event #<b>".$incident_id."</b> ...<br>'); em_perform_edit(".$incident_id.");\" value=\"Edit\"></td>
=======
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: em_append_log('Editing Event #<b>".$incident_id."</b> ...<br>'); em_perform_edit(".$incident_id.");\">Edit</a></td>
>>>>>>> MERGE-SOURCE
				</tr>
			";

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// list all events with this incident as a parent
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// get list of events
			$q = "
				SELECT *
				FROM incident i
				LEFT JOIN sys_user_groups g
				ON i.private_group = g.group_id
				WHERE i.parent_id = ".$incident_id."
				ORDER BY date desc;
			";
			$result = $global['db']->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "show events 3"); }

			// find out how many events we have
			$events = array();
			$ecount = 0;
			while($row = $result->FetchRow() ){
				$events[$ecount] = $row;
				$ecount++;
			}
			$total += $ecount;

			$k = 1;
			while($k <= $ecount) {
				$eo++;
				if($eo == 2) {
					$eo = 0;
				}

				$row           = $events[$k-1];
				$type          = "<b> &nbsp; &nbsp; &nbsp; &nbsp; <span style=\"color: yellow;\">".$char."</span> &nbsp; Event</b>";
				$event_id      = $row['incident_id'];
				$type2         = $row['type'];
				$longname      = $row['name'];
				$shortname     = $row['shortname'];
				$default       = $row['default'];
				$closed        = $row['closed'];
				$private_group = $row['private_group'];

				// get text for default event
				if($default == "1") {
					$defaultText = "DEFAULT";
				} else {
					$defaultText = "-";
				}

				// show group name or public if null group
				if($private_group == NULL) {
					$groupText = "PUBLIC";
				} else {
					$groupText = $row['group_name'];
				}

				// generate open close text
				if((int)$closed == 0) {
					$closedText = "OPEN";
				} else if((int)$closed == 1) {
					$closedText = "CLOSED";
				} else if((int)$closed == 2) {
					$closedText = "CLOSED(PF)";
				} else {
					$closedText = "OPEN";
				}

				// find class to color the row...
				if( $eo == 0 ) {
					$evenOddClass = "mainRowEven";
				} else {
					$evenOddClass = "mainRowOdd";
				}

				$htmlMain .= "
					<tr>
						<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$type."</td>
						<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\"><a href=\"#\" onclick=\"em_append_log('Editting Event #<b>".$event_id."</b> ...<br>'); em_perform_edit(".$event_id.");\" value=\"Edit\">".$longname."</a></td>
						<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$shortname."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$type2."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$defaultText."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$groupText."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$closedText."</td>
<<<<<<< TREE
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"em_append_log('Editting Event #<b>".$event_id."</b> ...<br>'); em_perform_edit(".$event_id.");\" value=\"Edit\"></td>

=======
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: em_append_log('Editing Event #<b>".$event_id."</b> ...<br>'); em_perform_edit(".$event_id.");\">Edit</a></td>
>>>>>>> MERGE-SOURCE
					</tr>
				";
				$k++;
			}
			// end events
			///////////////////////////////////////////////////////////////////////////////////////////////////////................................

			$j++;
		}
		// end incidents
		////////////////////////////////////////////////////////////////////////////////////////////////////....................................

		// spacer row except last row
		if($i != $dcount) {
			$htmlMain .= "<tr><td class=\"emTableSpacer\" colspan=8>&nbsp;</td></tr>";
		}
		$i++;
		$eo = 0; // reset
	}
	// end disasters
	////////////////////////////////////////////////////////////////////////////////////////////////..................................

	if ($dcount == 0) {
		$htmlMain .= "<tr><td colspan=8 class=\"mainRowEven\" style=\"text-align: center;\">No Events have been created thus far.</td></tr>";
	}
	$htmlMain .= "</table>";

	// script for word-template sortable
	$wt_list = "";
	$sq = "
		select list from ntfy_word_template order by last_update desc limit 1;
	";
        $res3 = $global['db']->Execute($sq);
//	$wt_list .= "<div id =\"$w\" class=\"ui-state-default\" style=\"text-align:center; float:left; width:auto; height: 18px; padding: 0.5em; border:1px solid black;\">$w</div>";
//	$wt_list .= "<div id =\"$w\" class=\"ui-state-default\" style=\"text-align:center; float:left; width: 95px; height: 18px; padding: 0.5em; border:1px solid black;\">$w</div>";

        if($res3 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "get ntfy word template"); }

	if ($row = $res3->FetchRow()) {
		$wt = explode(",", $row['list']);
                $wt_list = "";

		foreach ($wt as $w) {
			$t = str_replace(" ", "<br>", $w);
        		$wt_list .= "<div id =\"$w\" class=\"ui-state-default\" style=\"-webkit-transform: rotate(-90deg); -moz-transform: rotate(-90deg); z-index:inherit; width:80px; height:40px; margin:30px 0px 0px 0px; padding: 0px 0px 0px 0px; display: table-cell; float:left; border:1px solid black;\">$t</div>";
		}
	}
//debug $global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>'.$wt_list);

	// this block paints the dialog for Event Notification
	$htmlMain .= "
		<ul id=\"manageRecipients\" class=\"contextMenu\">
			<li id=\"insert\" class=\"insert\"><a href=\"#insert\">Insert a Recipient</a></li>
			<li id=\"append\" class=\"append\"><a href=\"#append\">Append a Recipient</a></li>
			<li id=\"delete\" class=\"delete separator\"><a href=\"#delete\">Delete a Recipient</a></li>
		</ul>

		<div style=\"display:none\" id=\"insertRecipient\" title=\"\">
			<table class=\"emTable\">
				<tr>
					<td class=\"mainRowEven emFirst emLast\" style=\"\">Title</td>
					<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"rcptitle\" type=\"text\" size=15 ></input></td>
				</tr>
				<tr>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\">Icon</td>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\"><input id=\"iconfile\" type=\"text\" size=45 ></input></td>
				</tr>
				<tr>
					<td class=\"mainRowEven emFirst emLast\" style=\"\">Value</td>
					<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"rcpvalue\" type=\"text\" size=15 title=\"\" ></input></td>
				</tr>
			</table>
		</div>

		<div style=\"display:none\" id=\"editTwitter\" title=\"Edit Message to Twitter\">
			<table class=\"emTable\">
				<tr>
					<td class=\"mainRowEven emFirst emLast\" style=\"\">Tweet</td>
					<td class=\"mainRowEven emFirst emLast\" style=\"\"><textarea id=\"tweet\" rows=5 cols=28 style=\"resize:none\"></textarea></td>
				</tr>
				<tr>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\">characters Left</td>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\"><div id=\"charCount\" ></div></td>
				</tr>
			</table>
		</div>

		<div style=\"display:none\" id=\"editEmail\" title=\"Edit Email\">
			<table class=\"emTable\">
				<tr>
					<td class=\"mainRowEven emFirst emLast\" style=\"\">Subject</td>
					<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"subject\" type=\"text\" size=45 /></td>
				</tr>
				<tr>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\">Body</td>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\"><textarea id=\"body\" rows=7 cols=55></textarea></td>
				</tr>
			</table>
		</div>

		<div style=\"display:none\" id=\"notify\" title=\"Event Notification\" style=\"float:none\">
		    <div id=\"leftPart\" style=\"margin:5px 10px 5px 5px; width:574; height:380; float:left\">
			<table class=\"emTable\">
<!--
				<tr>
					<td class=\"mainRowEven emFirst emLast\" style=\"\">Event Name (long/short)</td>
					<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"eventName\" type=\"text\" size=45 readonly /></td>
				</tr>
-->
				<tr>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\">Event URL</td>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\"><input id=\"eventUrl\" type=\"text\" size=55 readonly /></td>
				</tr>

				<tr>
					<td class=\"mainRowEven emFirst emLast\" style=\"\">Short URL</td>
					<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"shortUrl\" type=\"text\" size=25 readonly /></td>
				</tr>
				<tr>
					<td class=\"mainRowOdd emFirst emLast\" style=\"\" colspan=2>
					<div id=\"tree\" name=\"selNodes\">tree</div></td>
				</tr>
			</table>
		    </div>
		    <div id=\"rightPart\" style=\"width:441; height:391; float:left\">
			<table class=\"emTable\">

				<tr>
					<td class=\"mainRowEven emFirst emLast\" style=\"\" colspan=2>
						<div id=\"tabs\" style=\"height:auto\">
							<ul>
								<li><a href=\"#tabs-1\">Use Previous</a></li>
<!--
								<li><a href=\"#tabs-2\">Start Fresh</a></li>
-->
							</ul>
							<div id=\"tabs-1\" style=\"height:auto\" class=\"mainRowEven emFirst emLast\">
								<table class=\"emTable\">
									<tr>
										<td class=\"mainRowEven emFirst emLast\" style=\"\">
										    <div>
											Filter
										    </div>
										    <div>
											<textarea id=\"filter\" type=\"text\" cols=10 style=\"resize:none\"></textarea>
										    </div>
<!--
											<label for=\"filter\">Filter</label>
											<textarea id=\"filter\" type=\"text\" size=10 style=\"resize:none\"></textarea>
-->
										</td>

										<td class=\"mainRowEven emFirst emLast\" style=\"\">
											<label for=\"showLast\">Retrieve Sent Posts</label>
											<input id=\"showLast\" type=\"text\" size=3 maxlength=3 style=\"width:25px\" title=\"Up to 999 can be entered\" value=\"5\" />
										</td>
									</tr>
									<tr>
										<td class=\"mainRowOdd emFirst emLast\" style=\"\">Found Message</td>
										<td class=\"mainRowOdd emFirst emLast\" style=\"\"><div id=\"prevMsg\" style=\"width:50px\"></div></td>
									</tr>
									<tr>
										<td class=\"mainRowEven emFirst emLast\" style=\"\">New Message</td>
										<td class=\"mainRowEven emFirst emLast\" style=\"\">
										  <table class=\"emTable\">
										    <tr><td>
											<textarea id=\"newMessage\" rows=7 cols=20 type=\"text\" style=\"resize:none;width:200px; height:100px;\"></textarea>
										    </td></tr>
										    <tr><td>
											<div id=\"charLeftDiv\" style=\"float:left; display:none; padding-left:5px; \">
												Characters Left:&nbsp;
											</div>
												<div id=\"charLeft\" style=\"float:left; display:none; position:relative;\"></div></div>
										    </td></tr>
										  </table>
										</td>
									</tr>
								</table>
							</div>
<!--
							<div id=\"tabs-2\" style=\"height:auto\" class=\"emLast\">
								<table class=\"\">
									<tr>
										<td class=\"\" style=\"\">Template</td>
										<td>
											<div id=\"word-template\" class=\"ui-state-default\" style=\"margin:0px 0px 0px 0px; padding: 0px 0px 0px 0px; height:100px; display:table;\">".$wt_list."</div>
										</td>
									</tr>
									<tr>
										<td class=\"mainRowOdd emFirst emLast\" style=\"\">New Message</td>
										<td class=\"mainRowOdd emFirst emLast\">
											<textarea id=\"newMessage\" rows=4 cols=30 type=\"text\" style=\"resize:none;\"></textarea>
										</td>
									</tr>
								</table>
							</div>
-->
						</div>
					</td>
				<tr>
					<td class=\"mainRowEven\" colspan=2 style=\"padding-left: 8px; text-align: center;\" class=\"\"><button id=\"saveNewMsg\" class=\"\" value=\"Save New Message\">Save New Message</button></td>
				</tr>
			</table>
		    </div>
		</div>

	";
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Creating a new Event...<br>\'); em_perform_edit(0);" value="Create a new Disaster / Incident / Event">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: em_append_log(\'Opening Help...<br>\'); em_perform_help();" value="Help">
	';

        $htmlMain .= "<script type=\"text/javascript\">alert('at the end of em_show_events');</script>";

	//---- internally, no ajax, just pass back data
	if ( $internal ) {
		return $htmlMain;
	} else {
		$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
		$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);

		$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
		$global['xajax_res']->addAssign('rezMain','innerHTML',$htmlMain);

		$htmlLog .= "Found <b>".$total."</b> event(s).<br>";
		$global['xajax_res']->addAppend('rezLog','innerHTML',$htmlLog);
		$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
		return $global['xajax_res']->getXML();
	}
}



// shows help
function em_perform_help() {

	global $global;

	// help content
	$pageMainHtml = "
		<h2>Adding a New Event</h2>
		<ul>
			<li>Clicking on the new Event button will create a new event with default sample data.</li>
			<li>New events default to being OPEN, TEST, Non-DEFAULT, private to the admin group, and located at NLM.</li>
			<li>Once the new event is created, you are immediately redirected to begin editing it.</li>
		</ul>
		<br>
		<h2>Editing an Existing Event</h2>
		<ul>
			<li>Any changes made to an event are not saved until you click the <b>Save Changes</b> button.</li>
			<li>If you click <b>Cancel Edit / Close</b> any changes are not saved and your edits lost.</li>
			<li><b>Long Name</b> can be up to 60 characters long althought it is recommended to keep it as short as possible.</li>
			<li><b>Short Name</b> can be up to 16 characters long and can only contain lowercase letters and numbers. Any spaces or special characters will be removed and uppercase characters converted to lowercase when saved.</li>
			<li><b>Parent Event</b> is used to associate an event with another event as a parent. ie. creating a new incident or new event, you can choose the disaster or incident to use as their parent. If an event already has children associated with it, this box will be non-editable. So, in order to change the parent of an event of this type, you must first dissociate all children first.</li>
			<li><b>Type</b> can only be changed for <b>Disasters</b> (top level events). If you are editing an <b>incident</b> (level 2) or an <b>event</b> (level 3), then this value is inherited from the disaster parent or grandparent.</li>
			<li><b>Visibility</b> shares the same inheritance rules as <b>Type</b>.</li>
			<li><b>Date</b>: should be entered in the form <b>2010-01-31</b> (YYYY-MM-DD).</li>
			<li><b>Location</b> is used to help identify where an event happened/is occurring. Begin typing a street address into the first box and it will autocomplete allowing you to use the arrow keys to select an address or you may hit enter to search on a fully typed in address. Additionally, you can simply click the <b>Detect My Current Location</b> button to attempt to self-locate yourself using the HTML5 location spec.</li>
		</ul>
		<br>
		<h2>Deleting Events</h2>
		<ul>
			<li>In order to delete an event from the events list page, click on edit for the event you wish to delete.</li>
			<li>Deleting an event will remove the event from the database and remove all relationship data that any other piece of data has with this event.</li>
			<li>Data that is related to an event, ie. person(s) or other sahana entitites attached to this event are not harmed, but may be left dangaling unassociated with any event.</li>
			<li>It is recommended that the other associated data be first removed via some other means (ie. Delete Person Module) prior to deleting an event.</li>
			<li>Events cannot be deleted if they have children. In order to delete these events, the children must be first deleted.</li>
			<li>Events <b>cannot</b> be un-deleted.</li>
			<li>Only administrators can delete events.</li>
		</ul>
		<br>
		<h2>User Interface Definitions</h2>
		<img alt=\"IE6,7,8 dont support inline images, please upgrade to IE9 or Google Chrome, Firefox, Safari\" class=\"inlineHelp\" src=\"data:image/png;base64,".base64_encode(file_get_contents($global['approot'].'/mod/em/help.png'))."\">
		<br>
		<br>
		<ul>
			<li><b>Event</b>: specifies if the event is a <b>Disaster</b>, an <b>Incident</b>, or an <b>Event</b>. The three levels proceed in this order with <b>Disaster</b> being the top level event. This heiarchy exists so that disaster can can sub-incidents and in turn, incidents may have sub-events.</li>
			<li><b>Name</b>: is the full (long) name of the event.</li>
			<li><b>Short Name</b>: is the exact short string that classifies which event the site will begin handling when passed in via this URL.</li>
			<li><b>Type</b>: indicates whether the event is a <b>REAL</b> or a <b>TEST</b> event. This is spcified by per disaster and all incidents and events that are children of the particular disaster inherit this value from the parent.</li>
			<li><b>Default</b>: shows which event is the default event a user see when they come to the site.</li>
			<li><b>Visibility</b>: shows whether an event is visible to the public (enyone may view it) or whether it is only visible to a specific user class.</li>
			<li><b>Open</b>: an event that is <b>CLOSED</b> cannot accept new persons in the RAP (Report A Person), PLUS (Web Services), and MPRES (Missing Person Registry Email Services). <b>OPEN</b> events allow new persons to be accepted via these three avenues. <b>CLOSED(PF)</b> events are the same as <b>CLOSED</b> events except that they allow the reporting of persons via the Google Person Finder.</li>
			<li><b>Edit</b>: is the link you click on to edit this particular event.</li>
		</ul>
		<img alt=\"IE6,7,8 dont support inline images, please upgrade to IE9 or Google Chrome, Firefox, Safari\" class=\"inlineHelp\" src=\"data:image/png;base64,".base64_encode(file_get_contents($global['approot'].'/mod/em/help2.png'))."\">
		<br>
		<br>
		<ul>
			<li><b>Event ID#</b> is the internal event number used by Sahana is is automatically assigned.</li>
			<li><b>Description</b>: is a paragraph of text describing the event in more detail.</li>
			<li><b>Date</b>: the date on which the event occurred.</li>
			<li><b>Street Address</b>: is used to lookup a location when editing or creating a new event.</li>
			<li><b>Latitude / Longitude</b>: non-editable fields which are updated as the map is updated.</li>
		</ul>
		<img alt=\"IE6,7,8 dont support inline images, please upgrade to IE9 or Google Chrome, Firefox, Safari\" class=\"inlineHelp\" src=\"data:image/png;base64,".base64_encode(file_get_contents($global['approot'].'/mod/em/help3.png'))."\">
		<br>
		<br>
		<ul>
			<li><b>Log</b>: the log displays notifications as you are using the Event Manager to let you understand what is going on. Example: when started it shows how many events are presnet or when saving or canceling an edit, the status of this operation appears in the log so that a user can see when this operation is complete.

		</ul>
		<br>
		<br>
	";

	// update log/ui
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Closing Help...<br>\'); setTimeout(\'em_show_events();\', 250);" value="Close Help">
	';

	$global['xajax_res']->addAssign('rezMain', 'innerHTML', $pageMainHtml);
	$global['xajax_res']->addAssign('rezControl', 'innerHTML', $pageControlHtml);
	return $global['xajax_res']->getXML();
}



// find the root parent of the given event...if event is root event, return -1
function em_find_root_parent($eventId) {

	global $global;
	$q = "
		SELECT *
		FROM `incident`
		WHERE incident_id = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "find root parent 1"); }
	$row = $result->FetchRow();
	$parent = $row['parent_id'];

	// event is a root event, return -1
	if($parent == null) {
		return -1;

	// check if parent event is a root event
	} else {
		$q = "
			SELECT *
			FROM `incident`
			WHERE incident_id = '".$parent."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "find root parent 2"); }
		$row = $result->FetchRow();
		$grandParent = $row['parent_id'];

		if($grandParent == null) {
			return $parent;
		} else {
			return $grandParent;
		}
	}
}



// find if the event has any children
function em_event_has_child($eventId) {

	global $global;
	$q = "
		SELECT count(*)
		FROM `incident`
		WHERE parent_id = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "has child 1"); }
	$row = $result->FetchRow();
	if($row['count(*)'] > 0) {
		return true;
	} else {
		return false;
	}
}




// save all children visibilities and types
function em_save_children($eventId, $group, $type) {

	global $global;

	// update all children
	$q = "
		UPDATE incident
		SET
			type          = '".$type."',
			private_group = ".$group."
		WHERE parent_id       = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save children 1"); }


	// get list of all children, recurse
	$q = "
		SELECT *
		FROM incident
		WHERE parent_id = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save children 2"); }
	while($row = $result->FetchRow()) {
		em_save_children($row['incident_id'], $group, $type);
	}
}



// saves the event attributes to the database
<<<<<<< TREE
function em_perform_save($page_id, $rj) {

=======
function em_perform_save($page_id, $rj, $isNew) {
>>>>>>> MERGE-SOURCE
	global $global;
	global $conf;

	$useDerived = false;
	$passOnGenes = false;
	$r = json_decode($rj, true);
	$log = "";
	$suggest = false;

	$eventId     = mysql_real_escape_string((int)$r['eventId']);
	$name        = mysql_real_escape_string($r['longName']);

	$shortName   = $r['shortName'];
	$shortName   = trim($shortName);
	$shortName   = preg_replace("/[^a-zA-Z0-9\s]/", "", $shortName);
	$shortName   = strtolower($shortName);
	$shortName   = mysql_real_escape_string($shortName);
//	$msgSocial = mysql_real_escape_string($r['msgSocial']);

//$msgSocial = $name." (Event ID# ".$row['incident_id'].") has been created";
	if($r['shortName'] != $shortName) {
		$log .= "<span style=\"color: red;\"><b>Short Name field revised to match rules: 1) lowercase letters and numbers only 2) max 16 characters in length.</span></b><br>";
		$suggest = true;
	}
	if(strlen($shortName) < 1) {

		$log .= "<span style=\"color: red;\"><b>Since the Short Name field was too short, a new one has been auto-generated for you.</span></b><br>";
		$suggest = true;
		$shortName = "event".date("mdGis");
	}
	if($suggest) {
		$log .= "<span style=\"color: red;\"><b>You may wish to <a onclick=\"javascript: em_append_log('Editing Event #<b>".$eventId."</b> ...<br>'); em_perform_edit(".$eventId.");\">edit</a> this event again to make corrections to the new Short Name: </span>".$shortName."</b><br>";
	}


	$description = mysql_real_escape_string($r['eventDescription']);
	$externalReport = mysql_real_escape_string($r['externalReport']);
	$date        = mysql_real_escape_string($r['eventDate']);
        $pfifUrl     = mysql_real_escape_string($r['pfifUrl']);
        $pfifSync    = $r['pfifSync'];
	$street      = mysql_real_escape_string($r['street']);
	$latitude    = (double)$r['latitude'];
	$longitude   = (double)$r['longitude'];

	// Check for inherited properties ---
	// this is server side validation, we check even if derived parameters are passed

	// check if event its a child of other events
	$parentId = em_find_root_parent($eventId);
	if($parentId >= 0) {
		// user derived values
		$useDerived = true;

	// so, we are a root event, should we pass on teh traits? check if we have children
	} else if(em_event_has_child($eventId)) {
		// update children when the time comes
		$passOnGenes = true;
	}


	// if we are using derived values, find them
	if($useDerived) {
		$q = "
			SELECT *
			FROM `incident`
			WHERE incident_id = '".$parentId."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save event 1"); }
		$row = $result->FetchRow();
		$visibilityDerived = $row['private_group'];
		$typeDerived       = $row['type'];

	}


	// if we are on initial save and there is a parent, find the derived values
	if (!$useDerived && $r['eventParent'] > 0) {
        	$q = "
                	SELECT *
                	FROM `incident`
                	WHERE incident_id = '".$r['eventParent']."';
        	";
        	$res = $global['db']->Execute($q);
        	$row = $res->FetchRow();
        	$visibilityDerived = $row['private_group'];
        	$typeDerived       = $row['type'];
        	$useDerived = true;
	}


	// formulate parent
	$parent = (int)$r['eventParent'];
	if($parent == -1) {
		$parent = "NULL";
	} else {
		$parent = "'".$parent."'";
	}


	// formulate type
	if($useDerived || $r['eventType'] == "DERIVE") {
		$type = $typeDerived;
	} else {
		$type = $r['eventType'];
		if(($type != "REAL") && ($type != "TEST")) {
			$type = "TEST";
		}
	}


	// formulate default
	$default = (int)$r['eventDefault'];
	if($default == 1) {
		// return to non-default the current default
		$q = "
			UPDATE incident
			SET `default` = NULL
			WHERE `default` = '1';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save event 2"); }
		$row = $result->FetchRow();
		$default = "'1'";
	} else {
		$default = "NULL";
	}

	// check for bad values
	$closed = (int)$r['eventClosed'];
	if(($closed < 0) || ($closed > 2)) {
		$closed = 0;
	}

	// formulate group
	$group = (int)$r['eventVisibility'];
	if($useDerived || ($group == -2)) {
		if($visibilityDerived == null) {
			$group = "NULL";
		} else {
			$group = "'".$visibilityDerived."'";
		}
	} else {
		if( $group == -1) {
			$group = "NULL";
		} else {
			$group = "'".$group."'";
		}
	}

	// save the revision
	$q = "
		UPDATE incident
		SET
			name            = '".$name."',
			shortname       = '".$shortName."',
			description     = '".$description."',
			date            = '".$date."',
			latitude        = '".$latitude."',
			longitude       = '".$longitude."',
			type            = '".$type."',
			private_group   = ".$group.",
			closed          = ".$closed.",
			`default`       = ".$default.",
			parent_id       = ".$parent.",
			street          = '".$street."',
			external_report = '".$externalReport."'
		WHERE incident_id       = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save event 3"); }

        $pfifName = 'google'.$shortName;  // repository name = "google"+shortname
        $q = "
                UPDATE pfif_repository
                SET
                        name            = '".$pfifName."',
                        base_url        = '".$pfifUrl."',
                        sched_interval_minutes = '".$pfifSync."'
                WHERE incident_id       = '".$eventId."' AND name LIKE 'google%';
        ";
        $result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save event 4"); }

	// update visibility and type of children events.......
	if($passOnGenes) {
		em_save_children($eventId, $group, $type);
	}

	//$msgSocial = $name." (Event ID# ".$eventId.") has been created";
	//em_send_post($msgSocial);

	if ($isNew) {
		// email audit...
		$p = new pop();
		$subject = "{ ".$conf['site_name']." Event Manager Audit - new event ($eventId) $name / $shortName }";
		$bodyHTML = "
			<br>
			<b>A new event ($eventId) $name / $shortName has been instantiated on ".$conf['site_name'].".</b><br>
			<br>
			This is simply an audit email to keep the team aware of such changes.<br>
			<br>
			The event creation was initiated by: <b>".$_SESSION['user']." | ".$_SESSION['full_name']."</b><br><br>
		";
		$bodyAlt = "
			\n
			A new event ($eventId) $name / $shortName has been instantiated on ".$conf['site_name'].".\n\n
			\n
			This is simply an audit email to keep the team aware of such changes.\n
			\n
			The event creation was initiated by: ".$_SESSION['user']." | ".$_SESSION['full_name']."\n\n
		";
		
		$p->sendMessage($conf['audit_email'], null, $subject, $bodyHTML, $bodyAlt);
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>email new event '.$name.'/'.$shortName. ' to '. $conf['audit_email'] .'<br>');
	}

	$log .= "Event #<b>".$page_id."</b> <span style=\"color: green;\">Saved</span>.<b><br>";

	// update log/ui
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Creating a new Event...<br>\'); em_perform_edit(0);" value="Create a new Disaster / Incident / Event">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: em_append_log(\'Opening Help...<br>\'); em_perform_help();" value="Help">
	';
	$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);
	$global['xajax_res']->addAssign('rezMain', 'innerHTML', em_show_events(TRUE));
	$global['xajax_res']->addAppend('rezLog', 'innerHTML', $log);
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}



// delete an event
function em_perform_delete($incident_id, $confirm) {

	global $global;
	global $conf;

	if ($confirm == "true") {

		// email audit...
		$q = "
			SELECT *
			FROM `incident`
			WHERE incident_id = '".$incident_id."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "delete event 2"); }
		$row = $result->FetchRow();
		$name = $row['name'];
		$shortname = $row['shortname'];

		$p = new pop();
		$subject = "{ ".$conf['site_name']." Event Manager Audit }";
		$bodyHTML = "
			<br>
			<b>The event: ($incident_id) $name / $shortname has been deleted on ".$conf['site_name'].".</b><br>
			<br>
			This is simply an audit email to keep the team aware of such changes.<br>
			<br>
			The event deletion was initiated by: <b>".$_SESSION['user']." | ".$_SESSION['full_name']."</b><br><br>
		";
		$bodyAlt = "
			\n
			The event: ($incident_id) $name / $shortname has been deleted on ".$conf['site_name'].".\n
			\n
			This is simply an audit email to keep the team aware of such changes.\n
			\n
			The event deletion was initiated by: ".$_SESSION['user']." | ".$_SESSION['full_name']."\n\n
		";
		$p->sendMessage($conf['audit_email'], null, $subject, $bodyHTML, $bodyAlt);

		// purge the incident of persons and related image data
		$response = em_perform_purge_do($incident_id);

		// master audit log the action
		shn_acl_log_msg("Deleted the event named <b>".$name."</b> using Event Manager", $_SESSION['user_p_uuid'], $_SESSION['user_name'], "EVENT DELETE");

		// delete the incident from the db
		$q = "
			DELETE from incident
			WHERE incident_id = '".$incident_id."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "delete 1"); }

		$global['xajax_res']->addAppend('rezLog', 'innerHTML', $response.'Event <b>#'.$incident_id.'</b> <span style="color: red;">Deleted</span>.<br>');

	} else {
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', "Delete operation aborted.<br>");
	}

	//---- update UI
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Creating a new Event...<br>\'); em_perform_edit(0);" value="Create a new Disaster / Incident / Event">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: em_append_log(\'Opening Help...<br>\'); em_perform_help();" value="Help">
	';
	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);

	$global['xajax_res']->addAssign('rezMain', 'innerHTML', em_show_events(TRUE));
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}



// purge event
function em_perform_purge($incident_id, $confirm) {
	global $global;
	global $conf;

	if ($confirm == "true") {

		// email audit...
		$q = "
			SELECT *
			FROM `incident`
			WHERE incident_id = '".$incident_id."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "delete event 2"); }
		$row = $result->FetchRow();
		$name = $row['name'];
		$shortname = $row['shortname'];

		$p = new pop();
		$subject = "{ ".$conf['site_name']." Event Manager Audit }";
		$bodyHTML = "
			<br>
			<b>The event: ($incident_id) $name / $shortname has been purged on ".$conf['site_name'].".</b><br>
			<br>
			This is simply an audit email to keep the team aware of such changes.<br>
			<br>
			The event purge was initiated by: <b>".$_SESSION['user']." | ".$_SESSION['full_name']."</b><br><br>
		";
		$bodyAlt = "
			\n
			The event: ($incident_id) $name / $shortname has been purged on ".$conf['site_name'].".\n
			\n
			This is simply an audit email to keep the team aware of such changes.\n
			\n
			The event purge was initiated by: ".$_SESSION['user']." | ".$_SESSION['full_name']."\n\n
		";
		$p->sendMessage($conf['audit_email'], null, $subject, $bodyHTML, $bodyAlt);

		// master audit log the action
		shn_acl_log_msg("Purged the event named <b>".$name."</b> using Event Manager", $_SESSION['user_p_uuid'], $_SESSION['user_name'], "EVENT PURGE");

		// purge the incident of persons and related image data
		$response = em_perform_purge_do($incident_id);

		$global['xajax_res']->addAppend('rezLog', 'innerHTML', $response.'Event <b>#'.$incident_id.'</b> <span style="color: red;">Purged</span>.<br>');

	} else {
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', "Purge operation aborted.<br>");
	}

	//---- update UI
	$global['xajax_res']->addAssign('purgeButton','style.opacity','0.2');
	$global['xajax_res']->addAssign('purgeButton','disabled','true');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}



// purge all persons from an event
function em_perform_purge_do($incident_id) {

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");
	require_once($global['approot']."/inc/lib_uuid.inc");
	require_once($global['approot']."/inc/lib_image.inc");
	require_once($global['approot']."/inc/lib_locale/gettext.inc");

	$log = "";
	$webroot = $global['approot']."www/";
	$delPersons = 0;

	// Reset last_count for last export log  record. (Otherwise, the first
	// 'last_count' new records won't get exported.)
	$q = "
		UPDATE pfif_export_log pe, pfif_repository pr SET pe.last_count=0
		WHERE pr.incident_id = ".$incident_id."
		AND pe.repository_id = pr.id
		AND pe.status = 'paused';
	";
	$st = $global['db']->Execute($q);
	if($st === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "purge 0 ((".$q."))");
		$errchk = $global['db']->ErrorMsg();
		$log .= "Error updating last_count for export log for this incident: <b>".$errchk."</b><br>";
	}

	// Get all persons for this incident
	$q = "
		SELECT *
		FROM person_uuid
		WHERE incident_id = '".$incident_id."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "purge 1");  return($log."error!<br>"); }

	$people = array();
	$count = 0;
	while($row = $result->FetchRow()) {
		$people[$count] = $row['p_uuid'];
		$count++;
	}

	foreach($people as $p_uuid) {

		$p = new person();
		$p->p_uuid = $p_uuid;
		$p->load();
		$p->delete();
		$delPersons++;
		$log .= "Deleted <b>".$p_uuid."</b><br>";
	}
	$log .= "<b>".$delPersons." person(s)</b> purged.<br>";

        // Have SOLR do a full update of indexes.
	$handle = fopen("http://pl:8983/solr/dataimport?command=full-import", "r");
	if(!$handle) {
		$log .= "Error doing full reload of indexes after purge.<br>";
	}

	return($log);
}



// create a new page with default content and return its new page_id
function em_perform_new() {

	global $global;
	global $conf;

	$isNew = 1;

	$group = $_SESSION['group_id'];

	// generate the new event index
	require_once($global['approot']."/inc/lib_uuid.inc");
	$newId = shn_create_uuid("incident");

	// insert the new incident
	$random = mt_rand();

	$q = "
		INSERT INTO incident
			(incident_id, parent_id, search_id, name, shortname, date, type, latitude, longitude, private_group, closed)
		VALUES
			(".$newId.", null, null, 'new event ".$random."', 'x".$random."', '".date("Y-m-d")."', 'TEST', '39', '-77.101', '".$group."', '0');
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new 4"); }


        // insert new Google repositories for import/export
	$q = "
		INSERT INTO pfif_repository (name,role,resource_type,incident_id)
		VALUES ('googlexxx','source','person',".$newId.");
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new 5"); }
	$q = "
		INSERT INTO pfif_repository (name,role,resource_type,incident_id)
		VALUES ('googlexxx','source','note',".$newId.");
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new 6"); }
	$q = "
		INSERT INTO pfif_repository (name,role,resource_type,incident_id)
		VALUES ('googlexxx','sink','both',".$newId.");
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new 7"); }

	// email audit...
/*
	$p = new pop();
	$subject = "{ ".$conf['site_name']." Event Manager Audit }";
	$bodyHTML = "
		<br>
		<b>A new event has been instantiated on ".$conf['site_name'].".</b><br>
		<br>
		This is simply an audit email to keep the team aware of such changes.<br>
		<br>
		The event creation was initiated by: <b>".$_SESSION['user']." | ".$_SESSION['full_name']."</b><br><br>
	";
	$bodyAlt = "
		\n
		A new event has been instantiated on ".$conf['site_name'].".\n\n
		\n
		This is simply an audit email to keep the team aware of such changes.\n
		\n
		The event creation was initiated by: ".$_SESSION['user']." | ".$_SESSION['full_name']."\n\n
	";

<<<<<<< TREE
	shn_acl_log_msg("Created a new event using Event Manager", $_SESSION['user_p_uuid'], $_SESSION['user_name'], "EVENT CREATE");

=======
//	$p->sendMessage($conf['audit_email'], null, $subject, $bodyHTML, $bodyAlt);
*/
>>>>>>> MERGE-SOURCE
	return $newId;
}



// presents a gui to edit a page and its corresponding fields
function em_perform_edit($incident_id) {

	global $global;
	global $conf;

	$new = false;
	//$global['xajax_res']->setFlag('debug', true);

	// if incident_id = 0, must create a new incident then continue to edit it
	if ($incident_id == 0) {
		$incident_id = em_perform_new();
		$new = true;
	} else {
		$new = false;
	}

	// get incident info
	$q = "
		SELECT *
		FROM incident i
		LEFT JOIN sys_user_groups g
		ON i.private_group = g.group_id
		WHERE i.incident_id = ".$incident_id."
		ORDER BY date desc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 1"); }
	$row = $result->FetchRow();

	// get Google repository info for this incident
	$q = "
		SELECT base_url,sched_interval_minutes
		FROM pfif_repository
		WHERE incident_id = ".$incident_id." AND name LIKE 'google%' LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 2"); }
	$rowpfif = $result->FetchRow();

	// generate some html for special inputs //////// onchange=\"changeEvent(this.value);\"

	// generate parent event select box

		// check if event has children (if so, we don't allow changing of parent then)
		$qp = "
			SELECT COUNT(*)
			FROM incident
			WHERE parent_id = '".$row['incident_id']."';
		";
		$resp = $global['db']->Execute($qp);
		if($resp === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 3"); }
		$rowp = $resp->FetchRow();
		$hasChildren = $rowp['COUNT(*)'] > 0 ? true : false;

		if(!$hasChildren) {

			$options = "<option value=\"-1\">NONE</option>";

			// get list of Disasters
			$qd = "
				SELECT *
				FROM incident
				WHERE parent_id is null
				ORDER BY date desc;
			";
			$resd = $global['db']->Execute($qd);
			if($resd === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 4"); }
			$disasters = array();
			$dcount = 0;
			$disasters = array();
			while($rowd = $resd->FetchRow()) {
				$disasters[$dcount] = $rowd;
				$dcount++;
			}
			$i = 0; // we start with the 2nd row of teh table (header?) :)
			while($i < $dcount) {
				$selected = $row['parent_id'] == $disasters[$i]['incident_id'] ? "SELECTED" : "";

				// dont show self in teh dropdown :)
				if($disasters[$i]['incident_id'] != $row['incident_id']) {
					$options .= "<option value=\"".$disasters[$i]['incident_id']."\" ".$selected." >".$disasters[$i]['name']."</option>";
				}

					// get list of Incidents for this disaster
					$qi = "
						SELECT *
						FROM incident
						WHERE parent_id = '".$disasters[$i]['incident_id']."'
						ORDER BY date desc;
					";
					$resi = $global['db']->Execute($qi);
					if($resi === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 5"); }
					while($rowi = $resi->FetchRow()) {
						$selected = $row['parent_id'] == $rowi['incident_id'] ? "SELECTED" : "";

						// dont show self in teh dropdown :)
						if($rowi['incident_id'] != $row['incident_id']) {
							$options .= "<option value=\"".$rowi['incident_id']."\" ".$selected." >&nbsp;- ".$rowi['name']."</option>";
						}
					}
				$i++;
			}
			$parent = "
				<select id=\"eventParent\">
				".$options."
				</select>
			";

		} else {
			if($row['parent_id'] == null) {
				$pvalue = "-1";
			} else {
				$pvalue = $row['parent_id'];
			}
			$options = "<option value=\"".$pvalue."\" SELECTED >Event Has Children --- Not Editable</option>";
			$parent = "
				<select id=\"eventParent\" DISABLED>
				".$options."
				</select>
			";
		}

	// end parent select box



	// generate event type
		// if no parent, then you can change these settings...
		if($row['parent_id'] == null) {

			$real = $row['type'] == "REAL" ? "SELECTED" : "";
			$test = $row['type'] == "TEST" ? "SELECTED" : "";
			$type = "
				<select id=\"eventType\">
				<option value=\"REAL\" ".$real.">REAL</option>
				<option value=\"TEST\" ".$test.">TEST</option>
				</select>
			";

		// else they are derived from the parent event
		} else {
			$type = "
				<select id=\"eventType\" DISABLED>
				<option value=\"DERIVE\" SELECTED>Value Dervied From Parent Event</option>
				</select>
			";
		}
	// end type



	// generate default checkbox
		$checked = $row['default'] == "1" ? "CHECKED" : "";
		$default = "<input type=\"checkbox\" id=\"eventDefault\" name=\"eventDefault\" value=\"default\" ".$checked." >";
	// end default


	// generate closed checkboxtextarea
		$checkedZero = $row['closed'] == "0" ? "CHECKED" : "";
		$checkedOne  = $row['closed'] == "1" ? "CHECKED" : "";
		$checkedTwo  = $row['closed'] == "2" ? "CHECKED" : "";
		$closed = "
			<input type=\"radio\" id=\"eventClosed\" name=\"eventClosed\" value=\"0\" ".$checkedZero." > <b>REPORTING OPEN</b> for RAP/MPRES/PLUS/PFIF<br>
			<input type=\"radio\" id=\"eventClosed\" name=\"eventClosed\" value=\"1\" ".$checkedOne." > <b>REPORTING CLOSED</b> for RAP/MPRES/PLUS/PFIF<br>
			<input type=\"radio\" id=\"eventClosed\" name=\"eventClosed\" value=\"2\" ".$checkedTwo." > <b>REPORTING CLOSED</b> for RAP/MPRES/PLUS + <b>REPORTING OPEN</b> for PFIF. Enter reporting widget code below:<br>
			<textarea id=\"externalReport\" rows=4 cols=60 />".$row['external_report']."</textarea>
		";
	// end closed

        // generate options for PFIF data sync with Google
                $checkedSync = $rowpfif['sched_interval_minutes'] == "0" ? "" : "CHECKED";
		$pfif = "
			PF repository: <input type=\"text\" id=\"pfifUrl\" name=\"pfifUrl\" size=\"48\" value=\"".htmlspecialchars($rowpfif['base_url'])."\">
                        &nbsp;&nbsp;Keep ".$conf['site_name']." and Google PF synchronized? <input type=\"checkbox\" id=\"pfifSync\" name=\"pfifSync\" value=\"1\" ".$checkedSync."><br>
                        (e.g. https://www.google.org/personfinder/sendong)
		";
        // end PFIF options

	// generate visibility select box
		// if no parent, then you can change these settings...
		if($row['parent_id'] == null) {

			$options = "<option value=\"-1\">PUBLIC</option>";

			// get list of GROUPS
			$qg = "
				SELECT *
				FROM  `sys_user_groups`;
			";
			$resg = $global['db']->Execute($qg);
			if($resg === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 6"); }
			while($rowg = $resg->FetchRow()) {
				if($row['private_group'] == $rowg['group_id']) {
					$selected = "SELECTED";
				} else {
					$selected = "";
				}
				$options .= "<option value=\"".$rowg['group_id']."\" ".$selected." >".$rowg['group_name']."</option>";
			}
			$visibility = "
				<select id=\"eventVisibility\">
				".$options."
				</select>
			";

		// else setting is derived from parent ......
		} else {
			$visibility = "
				<select id=\"eventVisibility\" DISABLED>
				<option value=\"-2\" SELECTED>Value Dervied From Parent Event</option>
				</select>
			";
		}
	// end visibility select box

	$editMainHtml = "
<div id=\"topBlock\" >
<div id=\"formBlock\" >

<table class=\"emTable\">

	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Event ID#</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"eventId\" type=\"text\" value=\"".$row['incident_id']."\" size=8 readonly /></td>
	<tr>


	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Long Name</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><input id=\"longName\" type=\"text\" size=60 maxlength=60 value=\"".$row['name']."\" /></td>
	<tr>


	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Short Name</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"shortName\" type=\"text\" size=16 maxlength=16 value=\"".$row['shortname']."\" /> ( lowercase letters and numbers only )</td>
	</tr>


	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Title portion 2 (appears next to '".$conf['site_name']."')<br>ie. <b>for the Joplin Tornado</b></td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><textarea id=\"eventDescription\" rows=1 cols=60 />".$row['description']."</textarea></td>
	<tr>

	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Parent Event</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$parent."</td>
	<tr>

	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Type</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\">".$type."</td>
	<tr>

	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Visibility</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$visibility."</td>
	<tr>

	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Date</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><input id=\"eventDate\" type=\"text\" value=\"".$row['date']."\" /></td>
	<tr>


	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Default Event In Web Services</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$default."</td>
	<tr>

	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Event Status</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\">".$closed."</td>
	<tr>

        <tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">PFIF Settings for Google PF</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$pfif."</td>
        <tr>
</table>
</div>
<!--
<div id=\"topNotify\">
 <div id=\"notifyBlock\" class=\"form-container\" >

   <form>
     <fieldset>
       <legend>Event Notification</legend>
        <table class=\"emTable\">
	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Message</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\"><div id=\"eventMsg\" rows=7 col=35 readonly style=\"resize:none;\"></div></td>
	<tr>

	<tr>
		<td class=\"mainRowOdd emFirst emLast\" style=\"\" colspan=2>
        	<div id=\"tree\" name=\"selNodes\">tree</div>
		</td>
	<tr>
	</table>


        <p><input id=\"sendNoficication\" type=\"button\" value=\"Send Notification\"></p>

     </fieldset>

   </form>
 </div>
</div>
</div>
-->
<br>
<table class=\"emTable\">
	<tr>
		<td class=\"mainRowEven\" style=\" border-bottom: none;\" colspan=2>
			<label>Enter a Street Address: </label>
			<input id=\"address\" type=\"text\" /> &nbsp; -OR- &nbsp; <input type=\"button\" style=\"position: relative; top: -2px;\" class=\"styleTehButton\" onclick=\"detect_load();\" value=\"Detect My Current Location\" />
		</td>
	</tr>


	<tr>
		<td class=\"mainRowOdd emFirst emLast\" style=\"border-top: none; border-bottom: none;  padding: 0px;\" colspan=2>
			<div id=\"mapCanvas\" style=\"width: 100%; height: 500px;\"></div>
		</td>
	</tr>

	<tr>
		<td class=\"mainRowEven\" style=\" border-top: none;\" colspan=2>
			<label>latitude: </label>
				<input id=\"latitude\" type=\"text\"/ value=\"".$row['latitude']."\" readonly>
			<label> &nbsp; longitude: </label>
				<input id=\"longitude\" type=\"text\"/ value=\"".$row['longitude']."\" readonly>
		</td>
	</tr>
</table>
<div id=\"dialog\" title=\"\">

<table class=\"emTable\">

	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Event Name</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"eventName\" type=\"text\" value=\"".$row['name']."\" size=25 readonly /></td>
	<tr>
	<tr>
		<td class=\"mainRowOdd emFirst emLast\" style=\"\">Event URL(short)</td>
		<td class=\"mainRowOdd emFirst emLast\" style=\"\"><div id=\"eventUrl\" ></div></td>
	<tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Previous Message</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\"><div id=\"prevMsg\" style=\"width:50px\"></div></td>
	<tr>
	<tr>
		<td class=\"mainRowOdd emFirst emLast\" style=\"\">Message</td>
		<td class=\"mainRowOdd emFirst emLast\" style=\"\"><textarea id=\"newMsg\" rows=7 col=35 style=\"resize:none;\"></textarea></td>
	<tr>
</table>
</div>
	";

	// control HTML
	$editControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Saving Changes...<br>\'); setTimeout(\'em_perform_save('.$incident_id.', em_get_data(), '.(($new)?1:0).');\', 250);" value="Save Changes and Close">
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Canceling Changes...<br>\'); setTimeout(\'em_show_events();\', 250);" value="Cancel Editing and Close">
	';

	// if Admin... show delete/purge buttons
	if($_SESSION['group_id'] == "1") {

		$deleteButtonTitle = "Delete Event";

		if($hasChildren) {
			$disabled = "DISABLED style=\"opacity: 0.2;\"";
			$deleteButtonTitle = "Cannot Delete Event ~ Has Children";
		} else {
			$disabled = "";
		}
		$editControlHtml .= '
			&nbsp; &nbsp; &nbsp; &nbsp;
			<input class="styleTehButton red" type="button" id="deleteButton" onclick="javascript: em_delete('.$incident_id.');" value="'.$deleteButtonTitle.'" '.$disabled.' >
		';
		$editControlHtml .= '
			&nbsp; &nbsp;
			<input class="styleTehButton red" type="button" id="purgeButton" onclick="javascript: em_purge('.$incident_id.');" value="Purge Event">
		';
	}

	$global['xajax_res']->addAssign('rezMain', 'innerHTML', $editMainHtml);
	$global['xajax_res']->addAssign('rezControl', 'innerHTML', $editControlHtml);

	if($new) {
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', 'Event <b>#'.$incident_id.'</b> <span style="color: green;">Created</span>.<br>');
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', 'Editing event <b>#'.$incident_id.'</b>...<br>');
		$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	}
/*
	$nc1 = "
		SELECT id, trim( outType ) AS outType, trim( nckey ) AS nckey, trim( icon ) AS icon, trim( value ) AS value, (
		SELECT sysgenid
		FROM ntfy_messages
		WHERE configid = c.id
		ORDER BY sent DESC
		LIMIT 1
		) AS genid, (

		SELECT trim( message )
		FROM ntfy_messages
		WHERE configid = c.id
		ORDER BY sent DESC
		LIMIT 1
		) AS message, (

		SELECT sent
		FROM ntfy_messages
		WHERE configid = c.id
		ORDER BY sent DESC
		LIMIT 1
		) AS sent, (

		SELECT trim( user_name )
		FROM ntfy_messages
		WHERE configid = c.id
		ORDER BY sent DESC
		LIMIT 1
		) AS user_name
		FROM ntfy_config c
		ORDER BY seq;
	";
        $ncres1 = $global['db']->Execute($nc1);
        if($ncres1 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new nc1"); }
	$nctypes = array();
	$ncvalues = array();
	$ncvcount = 0;
	$z = 0;
	while($ncrow = $ncres1->FetchRow()) {
		$ncvalues[$ncvcount] = $ncrow;
		if ( !in_array($ncvalues[$ncvcount]['outType'], $nctypes))
			array_push($nctypes, $ncvalues[$ncvcount]['outType']);
		$ncvcount++;
	}       
	$i = 0;
	// create the tree-view Notification
	$s = '$("#tree").dynatree({
		checkbox: true,
		imagePath: "theme/lpf3/ntfy/",
		selectMode: 3,
		expand: true,
		onClick: function(node, event) {

			if(node.tree.isUserEvent()){

				if (!isNaN(node.data.key) && !isNaN(parseInt(node.data.key))) {
					$( "#dialog" ).dialog({dialogClass: "ui-dialog-titlebar"});
					$( "#dialog" ).dialog({title: "to " + node.parent.data.title});

					em_get_prev_msg(node.data.key);
					$( "#dialog" ).dialog( "open" );
				}
			}
		},
		children: [
		';

	while($i < count($nctypes)) {
		$j = 0;
		if ($i>0) $s .= ",";
		$init = 0;
		while ($j < $ncvcount) {
			if ($ncvalues[$j]['outType'] == $nctypes[$i]) {

				if ($init==0) {

					$icon = strtolower(str_replace(' ', '-', $ncvalues[$j]['outType'])). '.png';

					$s .= "{title: \"". $ncvalues[$j]['outType']. "\",key: \"". $ncvalues[$j]['outType']. "\", hideCheckbox:true, expand: true, icon: \"$icon\",
						children: 
							[
					";

				}
				if ($init!=0) $s .= ",";
				$s .= "
					{title: \"". ($ncvalues[$j]['outType']=='Email'?$ncvalues[$j]['value']:$ncvalues[$j]['nckey']) . "\", key: \"". $ncvalues[$j]['sysgenid']. "\", hideCheckbox:true, expand: true, icon: \"". $ncvalues[$j]['icon']. "\", 
						children: 
							[
								{title: \"Last sent: ".$ncvalues[$j]['sent']."\", key: \"".$ncvalues[$j]['genid']."\", 
									icon:false,hideCheckbox:true, tooltip: \"Last message [". $ncvalues[$j]['message']. "] was sent by ". 
$ncvalues[$j]['user_name'].($ncvalues[$j]['outType']=='Email'?' to '.$ncvalues[$j]['value']:''). " on ". $ncvalues[$j]['sent']. "\",
}
							]
					}";
				$init = 1;
			}
			$j++;
		}
		$s .= ']}';

		$i++;
	}
	$s .= ']});';
*/
//$global['xajax_res']->addAppend('rezLog', 'innerHTML', $s);
				/* need to either change last sent to "new" or add
				 a new node before last sent and enable the checkbox with checked
				*/
/*
	$global['xajax_res']->addScript("
var mtop = 0;


$(function () {

	$(window).scroll(function () {
		if (typeof $('#notifyBlock').css('position') == 'undefined') return;

		//var isfixed = ($('#notifyBlock').css('position') == 'fixed'? 0 : 1);
		if (mtop == 0) {
			mtop = $('#notifyBlock').offset().top - parseFloat($('#notifyBlock').css('margin-top').replace(/auto/, 0));
		}
		var y = $(this).scrollTop();

		if (y >= mtop) {
			$('#notifyBlock').css('position', 'fixed');
		} else if (y < mtop) {
			$('#notifyBlock').css('position', 'absolute');
		}

	});

	if ((_canLog) && (typeof $('#tree').attr('name') != 'undefined')) {" 
		. $s ."
	}

//var shortUrl = shortenUrl($('#eventName').val());
//alert(shortUrl);
        $( '#dialog' ).dialog({
		autoOpen: false,
		draggable: true,
		height: 400,
		width: 450,
		modal: true,
		buttons: {
			'Save': function() {
				$('#eventMsg').html('<p>'+$('#newMsg').val()+'</p>');

				var title = $( \"#dialog\" ).dialog( \"option\", \"title\" );
				title = title.replace('to ', '');
				var node = $('#tree').dynatree('getActiveNode');
				//var newtitle = 'New: ' + $('#newMsg').val();
				node.setTitle(format_title($('#newMsg').val(),1));
				node.data.tooltip = newtitle;
				node.select(true);
				node.data.hideCheckbox = false;
				node.getParent().select(true);
				node.getParent().data.hideCheckbox = false;
				node.render();
				node.getParent().render();
				$( this ).dialog( 'close' );
			},
			Cancel: function() {
				$( this ).dialog( 'close' );
			}
		},
		close: function() {
			//allFields.val( \"\" ).removeClass( \"ui-state-error\" );
		}
	});

	$('#prevMsg').change(function () {
		var str = $(this).find(\":selected\").attr(\"title\");
		var fin = \"\"; 
		if (str) {
			fin = str.substr(str.indexOf(\"[\")+1, str.indexOf(\"]\")-1-str.indexOf(\"[\"));
			$('#newMsg').val(fin);
		}
//		$(\"select option:selected\").each(function () {
//			str += $(this).text() + \" \";
//		});
//		$('#newMsg').val(str);
        })
        .trigger('change');

  }); // end function
"); // end addScript
*/
	$global['xajax_res']->addScript("load_map(".$row['latitude'].", ".$row['longitude'].", '".$row['street']."');");
	$global['xajax_res']->addScript("initDate();");
	return $global['xajax_res']->getXML();
}




