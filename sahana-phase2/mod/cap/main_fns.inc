<?php
/*
 * Sahana CAP alert aggregator Module
 * PHP version 5
 * LICENSE: This source file is subject to LGPL license 
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 * @author     Shree Kant Bohra <skbohra123@gmail.com> 
 * @package    Sahana - http://sahana.lk/
 * @module     CAP
 * @copyright  Lanka Software Foundation - http://www.opensource.lk 
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 */

global $global;
include_once $global['approot']."/3rd/xajax/xajax.inc.php";
$global['xajax']= new xajax('index.php?mod=cap&act=default');
$global['xajax']->registerFunction('_shn_cap_update_alerts');
$global['xajax']->registerFunction('_shn_cap_restore');
$global['xajax']->registerFunction('_shn_cap_delete');
$global['xajax']->registerFunction('_shn_cap_mark_as_read');
$global['xajax']->processRequests();
 


/*Function to display Alerts Area and select form
 * @param void
 * @return void 
 */
function _shn_cap_show_alerts()
{	
	global $global;
	$db=$global['db'];
	$q="SELECT * FROM cap_agg WHERE deleted=0";
	$q1="SELECT SUM(unread) AS totalunread FROM cap_agg";
	$q2="SELECT DISTINCT category from cap_agg_alerts";
	$result=$db->GetArray($q);
	$totalunread=$db->GetArray($q1);
	$categories=$db->GetArray($q2);
	$step=0;
	 
	
	?>
	<div>
	<?php print "<h2>"._t("CAP Aggregator")."</h2>";?>
	<?php
	$extraopts['br']=''; 
	shn_form_fopen('default','cap',Array());
	
	$subscriptions =array();
	$step=0;
	$subscriptions['']='All';
			 
	while($result[$step]){ //building up the drop down list of subscriptions based on database entries
		$subscriptions[$result[$step]['id']]=$result[$step]['server_name'];
		$step++;
	}
	$category['']='Default';
	$step=0;
	while($categories[$step]){ //building up the drop down list of categories based database entries
		$category[$categories[$step]['category']]=$categories[$step]['category'];
		$step++;
	}
	//set up the filter form 
	shn_form_select($subscriptions,_t('Choose Subscription'),'sub','', $extraopts);
	shn_form_select(array(""=>_t("Sort By Date"),"severity"=>_t("Sort By Severity")),_t("Sort By"),"sort", '',$extraopts); 
	shn_form_select($category,_t('Choose Category'),'category', '',$extraopts);
	shn_form_select(array("1000000"=>_t("All time"),"1"=>_t("Today"),"7"=>_t("Last 7 days"),"7"=>_t("Last 7 days"),"15"=>_t("Last 15 days"),"30"=>_t("Last 30 days")),'','days', '',$extraopts);
	shn_form_hidden(array('id'=>'$result[$step]["id"]'),'', $extraopts );
	shn_form_submit(_t('Go'));
	shn_form_fclose();
	?>
	</div>
		
	<div id="alerts_container"> <!-- the alerts container -->
	<span class="alerts_header_left"><?php print _t("Alerts"); 
	?></span><span class="alerts_header_message"><span class="alerts_header_message_no" id="alerts_no"><?php echo $totalunread[0]["totalunread"]?></span> <?php print _t("New alerts");?><input type="button" value="<?php print _t('Refresh');?>" onclick="xajax__shn_cap_update_alerts();"/></span>	
	<div id="alerts">
	
	<?php show_top_alerts();//call this function to show alerts based on the filter options selected by user
	
	
	$global['xajax']->printJavascript("res/js"); //xajax function
	
}


/*Function to update alerts
 * this function is registered to xajax 
 * @params void
 * @return xajax response 
 */
 


function _shn_cap_update_alerts()
{
	global $global;
	include_once $global['approot']."/mod/cap/lib_cap.inc";
	$db=$global['db'];
	$q="SELECT id,server_name,feed_url,last_updated,total_entries,unread FROM cap_agg WHERE deleted=0";
	$result=$db->GetArray($q);
	$step=0;$totalnew=0;$unread=0;$flag=0;$error=1;
	while($result[$step])
	{
		$capAlert=new fetchCap; //create an object
		$url = $result[$step]['feed_url'];
		$alerts=$capAlert->fetchAlerts($url); //set up the url to be fetched
		if($alerts){ //check if we get something back
			$error=0; // set error flag to zero 
			$unread=$result[$step]['unread']; //get the unread alerts count from database
			if($result[$step][last_updated]!=$alerts['updated']){//check if feed document is updated
				if($result[$step][total_entries]!=$alerts['total']) //if number of entries has changed update the database entry 
				$q="UPDATE cap_agg SET last_updated='$alerts[updated]',total_entries='$alerts[total]' WHERE feed_url='$url'"; //update database entries
				if($db->Execute($q)){
						$flag=1; //set the flag in case query doesn't executed, we will check this later
				}
				$step1=0;
				while($step1<$alerts['total']) //iterate while we have alerts
				{	$db1= $global['db'];
					$feed_id =$alerts[$step1]['feed_id'];
					$q3="SELECT * FROM cap_agg_alerts WHERE feed_id ='$feed_id'"; //check if the alert already exists 
					$res= $db->GetArray($q3);
					if($res){ // in case alert already exists
						if($res[0]['updated']!=$alerts[$step1]['updated']){ //if its updated
						$filename = $capAlert->saveCAP($alerts[$step1]['link']); //get the CAP document and save it on system 
						$q1="UPDATE cap_agg_alerts SET id='$result[$step][id]',title='$alerts[$step1][title]',area='$alerts[$step1][area]',msgtype='$alerts[$step1][msgtype]',severity='$alerts[$step1][severity]',link='$alerts[$step1][link]',status='$alerts[$step1][status']',updated='$alerts[$step1][updated]',category='$alerts[$step1]['category']',urgency='$alerts[$step1][urgency]',certainity='$alerts[$step1][certainity]',longlat='$alerts[$step1][longlat]',filename='$filename' WHERE feed_id ='$alerts[$step1]['feed_id']'"; 
						//$diff= $diff+1;
						if(!$db->Execute($q1)){
						$flag=0; //set the flag in case query does't executed
						}		
						}
						
					}else{//in case its a new alert
						$filename = $capAlert->saveCAP($alerts[$step1]['link']); //get the CAP document and save it on system
						$diff= $diff+1; //its a new alert, so mark it unread
						$q1='INSERT INTO cap_agg_alerts VALUES("'.$result[$step]['id'].'","'.$alerts[$step1]['title'].'","'.$alerts[$step1]['area'].'","'.$alerts[$step1]['msgtype'].'","'.$alerts[$step1]['severity'].'","'.$alerts[$step1]['link'].'","'.$alerts[$step1]['status'].'","'.$alerts[$step1]['updated'].'","'.$alerts[$step1]['category'].'","'.$alerts[$step1]['urgency'].'","'.$alerts[$step1]['certainity'].'","'.$alerts[$step1]['longlat'].'","'.$filename.'","'.$alerts[$step1]['feed_id'].'")'; //insert into database 
						if(!$db->Execute($q1)){
					$flag=0; //set flag in case query doesnt executed
					}
					}
				$step1++;
				}
				
			}
		
		}
		else{ // in case we didnt get anything
			$error=1;//set the error flag, we will check this laters
		}
				$a=$result[$step]['unread']+$diff;
				$q2="UPDATE cap_agg SET unread='$a' WHERE feed_url='$url'"; //update database and put no of unread messages	
				$db->Execute($q2);
				$totalnew=$totalnew+$diff+$unread; //find out total number of new message
		$step++;
	}	
	
	
	if($error==0){//in case there's no error
		if($flag==1){ //check if flag is set, 
			$global['xajax_res']= new xajaxResponse();
	   		$global['xajax_res']->addClear("alerts_no","innerHTML");
			$global['xajax_res']->addAssign("alerts_no","innerHTML", $totalnew); //send the number of new alerts as xajax response
			return $global['xajax_res'];
		}elseif($flag==0){//in case flag is not set
			$global['xajax_res']= new xajaxResponse();
    		$global['xajax_res']->addAssign("alerts_no","innerHTML",$totalnew); //send the number of new alerts as xajax response
    		return $global['xajax_res'];
		}
	}else{ // in case something went wrong, display a message
		$global['xajax_res']= new xajaxResponse();
    	$global['xajax_res']->addAssign("alerts_no","innerHTML",'Error Updating!'); //send error message as xajax response
    	return $global['xajax_res'];
	}
		
	
}


/*Function for deleting subscribed cap servers
 * This function updates 'deleted' field in 'cap_agg' table to 1
 * This function is registered to xajax 
 * @params string url of the subscription to be deleted
 * @return xjax response 
 */

function _shn_cap_delete($url)
{	
	global $global;
	$db=$global['db'];
	$q="UPDATE cap_agg SET deleted=1 WHERE feed_url='$url'"; //just set the delete flag to 1 when user delete a subsriptions, so that user can restore it later
	$global['xajax_res']= new xajaxResponse();
	$db->Execute($q);
	if($db->Execute($q)){
	$global['xajax_res']->addScript('alert("Subscription Deleted");'); //send an alert message as xajax response  	
	}else{
		$global['xajax_res']->addScript('alert("Error Deleting");');//incase something went wrong send a message
	}
	return $global['xajax_res'];	
}

/*Function for restoring deleted cap server subscription
 * This function updates 'deleted' field in cap_agg table to 0
 * This function is registered to xajax
 * @params string url of the subsciption to be restored
 * @return xajax response
 */

function _shn_cap_restore($url)
{	
	global $global;
	$db=$global['db'];
	$q="UPDATE cap_agg SET deleted=0 WHERE feed_url='$url'"; //unset the delete flag in database we check this when look for alerts
	$global['xajax_res']= new xajaxResponse();
	$db->Execute($q);
	if($db->Execute($q)){
		$global['xajax_res']->addScript('alert("Subscription Restored");');	//send an alert message as xajax response
	}else{
		$global['xajax_res']->addScript('alert("Error Restoring");'); //in case something went wrong send a message
	}
	return $global['xajax_res'];	
}

/* Function to display all alerts on a single map
 *@parms void
 *@return void 
 */

function shn_cap_cap_map_all($query=null)
{	global $global;
	global $conf;
	$db=$global['db'];
	$q=$_REQUEST['res'];//get the query statement 
	if(!$_REQUEST['res'])
	$q=$query;
	//$conf['gis_height']='400px'; //setup the height and width of map
	//$conf['gis_width']='370px';
		
	
	$conf['gis_dflt']='openlayers'; //set google maps as default, as yet to implemented in openlayers
	$conf['gis_zoom']='3';
	$res=$db->GetArray($q);//exectue the query 
	$step=0;
	$step1=0;
	include $global['approot']."/inc/lib_gis/gis_fns.inc";
	print "<h2>"._("Alerts on Map")."</h2>";
	while($res[$step]){
		$split=preg_split('/\s/',$res[$step]['longlat'],2); //get the cordiantes from database
		
		$right=preg_split('/,/',$split[0],2); //we need to split them as two points are put together in  field separated by comma
		$left=preg_split('/,/',$split[1],2);
		
		if($right[0] && $right[1]){//check if cordinates found
		
			$time=convert_time($res[$step]['updated']); //lets convert time in more readable form
			$cords[$step1]['left']=$left; //get the left point cordiantes
			$cords[$step1]['right']=$right;//get the right point cordinates
			$title[$step1]['title']=$res[$step]['title'];//send title along with corinates
			if(preg_match("/.cap|.xml/", $res[$step]['alert_file_name']))
			$title[$step1]['link']=$res[$step]['alert_file_name'];//send link	
			else
			$title[$step1]['link']=$res[$step]['link'];//send link
			$title[$step1]['days']=$time['days_passed'];//send days passed
			$title[$step1]['hours']=$time['hours_passed'];//send hours passed
		$step1++;
		}
		$step++;
	}
	if($cords){ //call function to show map only if we have atleast on cordinate
		//shn_gis_show_map();
		$conf['gis_center_x']= $cords[0]['right'][1];
		$conf['gis_center_y']= $cords[0]['right'][0];
		shn_gis_draw_polylines($cords,$title);
	}else{
		print _t("Error! No Map Information Found"); //display an error message in case no cordinates found
	}
}

/*Funtion to display alerts.
 * This function is called in main.inc
 * @parms void
 * @return void
 */

function show_top_alerts()
{
		global $global;
		$conf = $global['conf'];
		
		include_once $global['approot']."/inc/lib_paging.inc";
		include_once $global['approot']."/mod/cap/lib_cap.inc";
		$db= $global['db'];
		$sub=$_REQUEST['sub'];
		$category=$_REQUEST['category'];
		$sort=$_REQUEST['sort'];
		
		switch($_REQUEST['sort']) //various filter cases
		{
			case '': //the default case i.e. sorting by date
			if($sub && $category){ // if both category and subcriptions are choosen 
				$q3="SELECT * FROM cap_agg_alerts WHERE ((id='$sub') AND (category='$category')) ORDER BY updated desc";
				$q4="UPDATE cap_agg SET unread=0 WHERE (id='$sub')"; //in case a subscription is choosen explicitly assume that all alerts are read hence set the unread flag to 0 in database
				$db->Execute($q4);
				
			}elseif($category){
				$q3="SELECT * FROM cap_agg_alerts WHERE (category='$category') ORDER BY updated desc";
				
									
			}elseif($sub){
				$q3="SELECT * FROM cap_agg_alerts WHERE (id='$sub') ORDER BY updated desc";
				$q4="UPDATE cap_agg SET unread=0 WHERE (id='$sub')"; //in case a subscription is choosen explicitly assume that all alerts are read hence set the unread flag to 0 in database
				$db->Execute($q4);
				
			}else{
				$q3="SELECT * FROM cap_agg_alerts ORDER BY updated desc";
			}		  
			break;
			
			case 'severity': //if filter is based on severity 
				if($sub && $category){
					$q3="SELECT * FROM cap_agg_alerts WHERE ((id='$sub') AND (category='$category')) ORDER BY severity asc";
					$q4="UPDATE cap_agg SET unread=0 WHERE (id='$sub')";//in case a subscription is choosen explicitly assume that all alerts are read hence set the unread flag to 0 in database
					$db->Execute($q4);
				
				}elseif($category){
					$q3="SELECT * FROM cap_agg_alerts WHERE (category='$category') ORDER BY severity asc";
					
				}elseif($sub){
					$q3="SELECT * FROM cap_agg_alerts WHERE (id='$sub') ORDER BY severity asc";
					$q4="UPDATE cap_agg SET unread=0 WHERE (id='$sub')"; //in case a subscription is choosen explicitly assume that all alerts are read hence set the unread flag to 0 in database
					$db->Execute($q4);
								
				}else{
					$q3="SELECT * FROM cap_agg_alerts ORDER BY severity asc";
				}		  
				break;
		}
	
		$res=shn_paging_get_report($q3,$rpp=6,$headers=NULL,array("post"=>true,"return"=>false)); //using paging library for pagination of results

		shn_form_fopen('cap_map_all',cap,Array()); //setting up the form to allow user to see alerts on map
		shn_form_hidden(Array('res'=>$q3));//send query statement as form variable
		shn_form_submit(_t("View Alerts on Map"));
		shn_form_fclose();
		
							
		while(!$res->EOF)
		{	
			
			$time=convert_time($res->fields['updated']); //convert the unix timestamp into a readable form
			
			$days = $_REQUEST['days']; //get the days 
			
			if(!$days) //in case days is not set set it to all time
			$days='10000000000';
			
			if($time['days_passed'] <= "$days") //workout for watch window
			{
				$id = $res->fields["id"];
				$q5="SELECT server_name FROM cap_agg WHERE (id='$id')";
				$title = $db->Execute($q5) or die();
			
			if($res->fields['severity']=='1') //convert code into nice names 
				$severity='Extreme';
			elseif($res->fields['severity']=='2')
				$severity='Severe';
			elseif($res->fields['severity']=='3')
				$severity='Moderate';
			elseif($res->fields['severity']=='4')
				$severity='Minor';
			
			else{
				$severity='Unknown';
			}
				$tinyurl = getFile("http://tinyurl.com/api-create.php?url=".$res->fields['link']); //using tinyurl api to get the shorten url
				$tweet='I found this Alert worth sharing! '.$tinyurl.' via(@sahanacap)'; //setting up the tweet text
				$tweet='http://twitter.com/home?status='.$tweet;    //the final tweet url
			
			//$tweet=rawurlencode($tweet);
			//the following code setup the css for alert text
			if(preg_match("/.cap|.xml/", $res->fields['alert_file_name']))
				$alert="<span class='title'><a href='index.php?mod=cap&act=alert&stream=text&url=".$res->fields['alert_file_name']."' >".$res->fields['title']."</a>" ;
			else
			$alert="<span class='title'><a href='".$res->fields['link']."'>".$res->fields['title']."</a>" ;
			if($time["hours_passed"] <=1 && $time["days_passed"]< 1) //work out to format time and days in nice format. in case hours and days are less then or equal to 1 
				$alert=$alert."</span><span class='timesince'>".$time['hours_passed']._t(' hour ago')."</span>"; 
			elseif($time["hours_passed"]>1 && $time["hours_passed"]<=8 && $time["days_passed"] <1) //if less than 8 hours show number of hours
			$alert=$alert."</span><span class='timesince'>".$time['hours_passed']._t(' hours ago')."</span>";
			else
			$alert=$alert."</span><span class='timesince'>".$time['date_time']."</span>"; //hours more than 8 show complete date and time
			$alert=$alert."<br/><b>".$title->fields[0]."</b>";
			if($res->fields['area']) //show only if data available
			$alert=$alert."<br/><b>Location:</b>".$res->fields['area'];
			$alert=$alert."<br/><b>Severity:</b>".$severity;
			if($res->fields['category']) //show only if data available
			$alert=$alert."&nbsp;<b>Category:</b>".$res->fields['category'];
			if($res->fields['certainity']) //show only if data available
			$alert=$alert."&nbsp;<b>Certainty:</b>".$res->fields['certainity'];
			//$alert=$alert."<br/><b>Updated:</b>".$res->fields['updated'];
			$alert=$alert."<br/><form action='index.php?mod=cap&act=cap_map' method='post' class='imagebutton'><input type='hidden' name='title' value='".$res->fields['title']."' class='imagebutton'/><input type='hidden' name='updated' value='".$res->fields['updated']."' class='imagebutton'/><input type='hidden' name='link' value='".$res->fields['link']."' class='imagebutton'/><input type='hidden' name='longlat' value='".$res->fields['longlat']."' /><input class='imagebutton' type='image' src ='res/img/map.png' title='View on map'/></form>"; //set up the form to let user see alerts on map
			$alert=$alert."<form action='index.php?mod=cap&act=cap_msg' method='post' class='imagebutton'><input class='imagebutton' type='hidden' name='title' value='".$res->fields['title']."'/><input type='hidden' name='area' value='".$res->fields['area']."' class='imagebutton'/><input type='hidden' name='updated' value='".$res->fields['updated']."' class='imagebutton'/><input type='hidden' name='link' value='".$res->fields['link']."' class='imagebutton'/><input class='imagebutton' type='image' src='res/img/sms.png' title='SMS this alert' value='Share this'/></form>"; //set up the form to let user send alert as sms
			$alert=$alert."<a href='".$tweet."'><img src='res/img/twitter.png' title='Tweet This'/></a>"; //set up the hyper link to allow user to send alert as tweet
			//$alert=$alert."<span class='markread'><a href='#' onclick='xajax__shn_cap_mark_as_read()'>Mark as read</a></span>";
			if($res->fields['status']=='Actual'){ //set up the color code according to severity
				if(trim($res->fields['severity'])=='1' && trim($res->fields['uregency'])=='Immediate' && trim($res->fields['Certainity'])=='Observed'){
					$html=$html."<div class='alert_rigour'>".$alert."</div>";
				}elseif(trim($res->fields['severity'])=='2' && trim($res->fields['uregency'])=='Expected' && trim($res->fields['Certainity'])=='Observed'){
						$html=$html."<div class='alert_moderate'>".$alert."</div>";
				}elseif(trim($res->fields['severity'])=='3' && trim($res->fields['uregency'])=='Expected' && trim($res->fields['Certainity'])=='Observed'){
						$html=$html."<div class='alert_minor'>".$alert."</div>";
				}else{
						$html=$html."<div class='alert_minor'>".$alert."</div>";
				} 
			}elseif(trim($res->fields['status'])=='Test'){
				$html=$html."<div class='alert_test'><p>".$alert."</p></div>";
			}elseif(trim($res->fields['status'])=='Excercise'){
				$html=$html."<div class='alert_excercise'><p>".$alert."</p></div>";
			}elseif(trim($res->fields['status'])=='System'){
				$html=$html."<div class='alert_system'><p>".$alert."</p></div>";
			}			
			else{
				$html=$html."<div class='alert_moderate'>".$alert."</div>";
			}
			}
			else{ //in case theres no alert in that date
				$html = _t("No alerts in specified critiera");
			}
			$res->Movenext();
		
		}
		print $html; //print the alert now
		?></div></div><div id="map_area"><?php shn_cap_cap_map_all($q3);?><?php //show up the map in right side
}

/*Function used to make sms alert support
 * @params void 
 * @return void
 */
function shn_cap_cap_msg()
{
	global $global;
	include_once "handler_cap_msg.inc"; //work out for send sms thing
}

/*Function to display a single alert on map
 * @params void
 * @return void
 */
function shn_cap_cap_map()
{	
	global $global;
	global $conf;
	include $global['approot']."/inc/lib_gis/gis_fns.inc";
	$conf['gis_dflt']='openlayers';
	$conf['gis_zoom']='3';
	print "<h2>"._t("CAP Aggregator")."</h2>";
	
	$split=preg_split('/\s/',$_REQUEST['longlat'],2); //get the cordinates
	$right=preg_split('/,/',$split[0],2);
	$left=preg_split('/,/',$split[1],2);
	$time=convert_time($_REQUEST['updated']);
	$cords[0]['left']=$left;
	$cords[0]['right']=$right;
	$title[0]['title']=trim($_REQUEST['title']);
	$title[0]['link']=$_REQUEST['link'];
	$title[0]['days']=$time['days_passed'];
	$title[0]['hours']=$time['hours_passed'];
	if($_REQUEST['longlat']){
		$conf['gis_center_x']= $cords[0]['right'][1];
		$conf['gis_center_y']= $cords[0]['right'][0];
		shn_gis_draw_polylines($cords,$title);
	}
	else{
		add_error(_t("Error! No Map Information Found"));
	}
}
function _shn_cap_mark_as_read($url=null){ //not used yet
	global $global;
	$global['xajax_res']= new xajaxResponse();
	$global['xajax_res']->addScript('alert("Cookie Set!");');	
	return $global['xajax_res'];	
	
}


//funtion to convert time in hours, days and local time
//@params time
//@return days, hours and time
function convert_time($updated){ 
	$time=time();
	$timepassed=$time-strtotime($updated); //get the difference from local time		
	$days_passed = gmdate("z",$timepassed); //get only days 
	$hours_passed = gmdate("G",$timepassed);//get only hours 
	$date_time = date("M d Y H:i:s",strtotime($updated));  //get nice date and time
	$converted_time['days_passed']=$days_passed;
	$converted_time['hours_passed']=$hours_passed;
	$converted_time['date_time']=$date_time; 
	return $converted_time;
}
function shn_xajax_printJavaScript(){}
