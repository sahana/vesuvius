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
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/mod/cap/lib_cap.inc";
include_once $global['approot']."/3rd/xajax/xajax.inc.php";
$global['xajax']= new xajax('index.php?mod=cap&act=cap_subscribe');
$global['xajax']->registerFunction('_shn_cap_restore');
$global['xajax']->registerFunction('_shn_cap_delete');
$global['xajax']->processRequests();
 

switch ($_REQUEST['seq'])
{
    case '' :
            _shn_cap_addsource(); //the defualt case, show the form
            _shn_cap_subscribed_list();
            
            break;
	case 'addsrc':
			_shn_cap_addsrc_success(); //the form is filled, call the function to store in database
			break;

}
/*Function used to display add cap server form
 *@params void
 *@return void
 */

function _shn_cap_addsource()
{
	print "<h2>" . _t("Add New Cap Source") . "</h2>";
	//the form used to display the form to subscribe for a new cap source
	shn_form_fopen("cap_subscribe",null,array());
	shn_form_fsopen();
	shn_form_hidden(array('seq'=>'addsrc'));
	shn_form_text(_t('Source Url'),'srcurl','size="50"');
	//shn_form_text(_('Category  '),'category','size="50"');
	shn_form_select(array("1"=>('1'),"2"=>('2'),"3"=>('3')), _t('Priority'),  "priority" );
	shn_form_submit(_t('Add'));
	shn_form_fsclose();
	shn_form_fclose();
}

/*Function called by form 'cap_subscribe' to add cap servers
 *@params void
 *@return void
 */

function _shn_cap_addsrc_success()
{
	global $global;
	global $conf;
	$db=$global['db'];
	$src=$_POST['srcurl'];
	$check=shn_is_null($src);
	//various checks to see if everything is filled and filled correctly
	if(!$check)	{
	//check if source already exists
	$query="SELECT * FROM cap_agg WHERE feed_url='$src'";
	$result=$db->Execute($query);
		if($result->EOF){
			//get the name of user currently logged in 
			$user = $_SESSION["user"];
 			$priority=$_POST["priority"];
 			$date =getdate();
			$avg_update='5';
			//in case the url submitted by user is not an atom feed document, call this function to get the 
			// feed documents available in that url, called as feed discovery
			$feedurl=discover_feed($src); 
			if($feedurl){
				$step=0;
				while($feedurl[$step]){
					//create an instance of ParseFeedIndex class defined in lib_cap.inc
					$feedDocument = new ParseFeedIndex;
					$feedDocument->mUrl=$feedurl[$step]; //set the url to be fetched
					$feedDocument->setDocument(); //call the function that fetches the url and parsed the xml document
					//the insert query to put available data in database
					$q="INSERT INTO cap_agg VALUES('$feedDocument->mId','$feedurl[$step]','$feedDocument->mTitle','0','0','$feedDocument->mTitle','$feedDocument->mAuthor','$avg_update','$date','$user','$priority','0','0','0')";
					$results=$db->Execute($q);
					if($results){
						add_confirmation(_t("The Source succefully added!")); 
					}else{
						add_error(_t("Couldn't Connect to Database!")); //if something goes fishy with database
					}	
				$step++;
				}
			}else{
				add_error(_t("Error! Not a valid url")); //in case the url submitted in not valid, displays an error
			}	
		}else{ 
			add_error(_t("Error! Source already added")); // in case source already exists, displays an error
		}
	}else{
		add_error(_t("The Field can't be blank")); // in case user try to submit blank form
	}

}

/*Function to display the list of subscribed servers 
 * @params void
 * @return void
*/

function _shn_cap_subscribed_list()
{
	global $global;
    include_once $global['approot']."/inc/lib_form.inc";
?>
	<h2><?php print _t("Subscribed CAP Servers");?></h2>
	<?php
	$q= 'SELECT * FROM cap_agg';
	//using the paging functions
	$result_set = shn_paging_get_report($q,$rpp=20,$headers=NULL);?>
	<div id="result">
	<table>
	<thead><td><?php print _t("Server Name");?></id><td><?php print _t("Feed Location");?></td><td><?php print _t("Verified");?></td><td><?php print _t("Deleted");?></td><td><?php print _t("Total Entries");?></td><td><?php print _t("Action");?></td></thead>
	<?php
	foreach($result_set as $results)
	{
		?>
		<tbody>
		<tr>
		<td><?php echo $results['server_name'];?></td>
		<td><?php echo $results['feed_url'];?></td>
		<td><?php echo $results['verified'];?></td>
		<td><?php echo $results['deleted'];?></td>
		<td><?php echo $results['total_entries'];?></td>
		<?php 
			if($results['deleted']==0){?>
				<td style="cursor:pointer; text-decoration:underline; text-color:blue" onclick="xajax__shn_cap_delete('<?php echo $results['feed_url']?>')"><?php print _t("Delete");?></td>
				<?php
			}
		 	else{?>
				<td style="cursor:pointer; text-decoration:underline; text-color:blue" onclick="xajax__shn_cap_restore('<?php echo $results['feed_url']?>')"><?php print _t("Restore");?></td>
				<?php
			}?>
		</tr>
		<?php
	
				
	}?>
	</tbody>
	</table>
	</div></div>
	<?php
		$global['xajax']->printJavascript("res/js");
}





