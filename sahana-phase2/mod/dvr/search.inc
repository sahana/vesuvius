<?php
/**Search page of the DVR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author	  Mifan Careem <mifan@opensource.lk>
* @author	  Janaka Wickramasinghe <janaka@opensource.lk> 
* @author	  Saumya Gunawardana <saumya@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

function _shn_dvr_search_default()
{
?>
    <h3> Advanced Search </h3>
<?php    
    $header = array (array('method'=>"POST",'action'=>'')); // end of header
    shn_show_form($header);

    $body = array (
    	array('type'=>'text','desc'=>'Name','size'=>'30','name'=>'name'),
    	array('type'=>'password','desc'=>'Name','size'=>'30','name'=>'name55'),
    	array ( 'type'=>'dropdown','desc' => 'Option', 'name'=>'opt_name','options'=>
    		array(
    			array('drop_desc'=>'Exactly'),
    			array('drop_desc'=>'Like'),
    			array('drop_desc'=>'Starting From')
    		)
    	),
    	array ( 'type'=>'dropdown','desc' => '', 'name'=>'or_name','options'=>
    		array(
    			array('drop_desc'=>'Or'),
    			array('drop_desc'=>'And')
    		)	
    	),
    	array('type'=>'text','desc'=>'Age','size'=>'5','name'=>'age'),
    	array ( 'type'=>'dropdown','desc' => 'Option', 'name'=>'opt_age','options'=>
    		array(
    			array('drop_desc'=>'Exactly')
    		)
    	),
    	array ( 'type'=>'dropdown','desc' => '', 'name'=>'or_age','options'=>
    		array(
    			array('drop_desc'=>'Or'),
    			array('drop_desc'=>'And')
    		)	
    	),
    	array('type'=>'text','desc'=>'Address','size'=>'50','name'=>'address'),
    	array ( 'type'=>'dropdown','desc' => 'Option', 'name'=>'opt_addr','options'=>
    		array(
    			array('drop_desc'=>'Exactly'),
    			array('drop_desc'=>'Like'),
    			array('drop_desc'=>'Starting From')
    		)
    	)	
    );//end of body
    shn_show_form($body);
    
    $tail = array (
        array('type'=>"submit",'value'=>"Search")
    ); // end of tail
?>
    <input type="hidden" name="search_seq" value="result" />
<?php 
    shn_show_form($tail);
}

function _shn_dvr_search_result()
{
	global $global;
?>
    <h3> Search Results </h3>   
<?php  
		
	$arr_name=NULL;
	$arr_age=NULL;
	$arr_addr=NULL;
    $args=NULL;
    $opt=NULL;
    $result=NULL;
    
    $args[0]  = ($_POST['name']!=NULL)?$_POST['name']:NULL;
    $args[1]  = ($_POST['age']!=NULL)?$_POST['age']:NULL;
	$args[2]  = ($_POST['address']!=NULL)?$_POST['address']:NULL;
    $opt[0] = ($_POST['opt_name']!=NULL)?$_POST['opt_name']:NULL;
    $opt[1] = ($_POST['opt_age']!=NULL)?$_POST['opt_age']:NULL;
	$opt[2] = ($_POST['opt_addr']!=NULL)?$_POST['opt_addr']:NULL;
    $or[0] = ($_POST['or_name']!=NULL)?$_POST['or_name']:NULL;
	$or[1] = ($_POST['or_age']!=NULL)?$_POST['or_age']:NULL;
	
	if($args!=NULL){
		for($i=0;$i<=2;$i++){
			if($args[$i]!=NULL){
			    switch ($i){
    				case 0:
        				$table="metadata_text";
						$field=$args[0];
						$option=$opt[0];
        			break;
        			case 1:
        				$table="metadata_int";
						$field=$args[1];
						$option=$opt[1];
        			break;
					case 2:
        				$table="metadata_text";
						$field=$args[2];
						$option=$opt[2];
        			break;
    			}
   			
    			$where=NULL;
    			switch ($option){
    				case "Exactly":
        				$where=" ='".$field."'";
        			break;
        			case "Like":
        				$where=" LIKE '%".$field."%'";
        			break;
					case "Starting From":
        				$where=" LIKE '".$field."%'";
        			break;
    			}		
    			
    			$sql="SELECT rec_id FROM ".$table." WHERE value".$where.""; 
				$conn=$global['db'];
				$rs = $conn->SelectLimit($sql);
				if ($rs === false) {
        			print 'Error Fetching: '.$conn->ErrorMsg().'<br />';
    			} 
    			else{
    				$i=0;
    				while ($arr = $rs->FetchRow()) {
    					//$rec_name[$i]=$arr['rec_id'];
    					$sql="SELECT form_id FROM people_reg WHERE rec_id='".$arr['rec_id']."' AND active=1"; 
            			$res = $conn->SelectLimit($sql);
						if ($res === false) {
        					print 'Error Fetching: '.$conn->ErrorMsg().'<br />';
    					} 
    					else{
    						while ($arr2 = $res->FetchRow()) {
    							$arr_name[$i]=$arr2['form_id'];
    						}
    					}
    					$i++;
    				}
    			}
    		}	
		}
    }

 	if($arr_name!=NULL){
 		if($arr_age!=NULL){
 			if($arr_addr!=NULL){
 				if($opt[0]=="Or"){
    				$result=array_merge($arr_name,$arr_age);
    				if($opt[1]=="Or"){
    					$result=array_merge($result,$arr_addr);
    				}elseif($opt[1]=="And"){
    					$result=array_intersect($result,$arr_addr);
    				}else{
    					$result=$result;
    				}
    			}elseif($opt[0]=="And"){
    				$result=array_intersect($arr_name,$arr_age);
    				if($opt[1]=="Or"){
    					$result=array_merge($result,$arr_addr);
    				}elseif($opt[1]=="And"){
    					$result=array_intersect($result,$arr_addr);
    				}else{
    					$result=$result;
    				}
    			}
    		}else{
    			if($opt[0]=="Or"){
    				$result=array_merge($arr_name,$arr_age);
    			}elseif($opt[0]=="And"){
    				$result=array_intersect($arr_name,$arr_age);
    			}else{
    				$result=$result;
    			}
    		}
    	}else{
    		if($arr_addr!=NULL){
    			if($opt[1]=="Or"){
    				$result=array_merge($arr_name,$arr_addr);
    			}elseif($opt[1]=="And"){
    				$result=array_intersect($arr_name,$arr_addr);
    			}else{
    				$result=$result;
    			}
    		}else{
    			$result=$arr_name;
    		}
    	}
    }else{
    	if($arr_age!=NULL){
 			if($arr_addr!=NULL){
 				if($opt[1]=="Or"){
    				$result=array_merge($arr_age,$arr_addr);
    			}elseif($opt['1']=="And"){
    				$result=array_intersect($arr_age,$arr_addr);
    			}else{
    				$result=$result;
    			}
    		}else{
    			$result=$arr_age;
    		}
    	}else{
    		if($arr_addr!=NULL){
    			$result=$arr_addr;
    		}else{
    			$result=NULL;
    		}
    	}
    }
    if($result!=NULL){
    	$result=array_unique($result);
    }
    if($result!=NULL){
?>
		<table>
		<tr>
		<td>Name</td>
		<td>Age</td>
		<td>Address</td>
		</tr>
<?php
    	foreach($result as $value){
?>
			<tr><td>
<?php
    		$sql="SELECT metadata_text.value FROM people_reg,metadata_text WHERE people_reg.form_id='".$value."' AND people_reg.active=1 AND people_reg.meta_id=1 AND people_reg.rec_id=metadata_text.rec_id"; 
    		//print($sql);
    		$res = $conn->SelectLimit($sql);
			if ($res === false) {
    			print 'Error Fetching: '.$conn->ErrorMsg().'<br />';
    		} 
    		else{
    			while ($arr = $res->FetchRow()) {
    				print($arr['value']);
					print"<br />";
    			}
    		}
?>
			</td><td>
<?php
    		$sql="SELECT metadata_int.value FROM people_reg,metadata_int WHERE people_reg.form_id='".$value."' AND people_reg.active=1 AND people_reg.meta_id=2 AND people_reg.rec_id=metadata_int.rec_id"; 
    		//print($sql);
    		$res1 = $conn->SelectLimit($sql);
			if ($res1 === false) {
    			print 'Error Fetching: '.$conn->ErrorMsg().'<br />';
    		} 
    		else{
    			while ($arr1 = $res1->FetchRow()) {
    				print($arr1['value']);
					print"<br />";
    			}
    		}
?>
			</td><td>
<?php
    		$sql="SELECT metadata_text.value FROM people_reg,metadata_text WHERE people_reg.form_id='".$value."' AND people_reg.active=1 AND people_reg.meta_id=3 AND people_reg.rec_id=metadata_text.rec_id"; 
    		//print($sql);
    		$res2 = $conn->SelectLimit($sql);
			if ($res2 === false) {
    			print 'Error Fetching: '.$conn->ErrorMsg().'<br />';
    		} 
    		else{
    			while ($arr2 = $res2->FetchRow()) {
    				print($arr2['value']);
					print"<br />";
    			}
    		}
?>
			</td></tr>
<?php
    	}
?>
		</table>
<?php
    }
    else{
    	print"No matching entries found for the input";
    }
}
?>
