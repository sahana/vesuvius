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
	global $global; 
	$filename = $global['approot']."/mod/dvr/test.txt"; // File which holds fields 
	$arr_fields = file($filename); // Open the file as an array
	$numLines = count($arr_fields); // Count the elements in the array

    $header = array (array('method'=>"POST",'action'=>'')); // end of header
    shn_show_form($header);
	
	/*$body = array (
		array('fieldset'=>' '),
    	array ('legend'=>'Advanced Search')
    );//end of body
     */   
     $body = array();
	foreach($arr_fields as $value){
		$temp = preg_split("/#/", $value);
		
		$field=NULL;
		$caption=NULL;
		$size=NULL;
		
		$field=$temp[0];
		$caption=$temp[1];
		$size=$temp[2];
		$or_name="or_".$field;
		array_push($body, array('type'=>'text','desc'=>$caption,'size'=>$size,'name'=>$field));
		array_push($body, array ('type'=>'dropdown','desc' => '', 'name'=>$or_name,'options'=>
    			array(
    				array('drop_desc'=>'Or'),
    				array('drop_desc'=>'And')
   		 		)	
   		 	)
   		 );
	}
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
    <h3> Search Results </h3>   ')
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
    				$j=1;
    				while ($arr = $rs->FetchRow()) {
    					$sql="SELECT form_id FROM people_reg WHERE rec_id='".$arr['rec_id']."' AND active=1"; 
            			$res = $conn->SelectLimit($sql);
						if ($res === false) {
        					print 'Error Fetching: '.$conn->ErrorMsg().'<br />';
    					} 
    					else{
    						while ($arr2 = $res->FetchRow()) {
    							if($i==0){
    								$arr_name[$j]=$arr2['form_id'];
    							}elseif($i==1){
    								$arr_age[$j]=$arr2['form_id'];
    							}else{
    								$arr_addr[$j]=$arr2['form_id'];
    							}
    							$j++;
    						}
    					}
    				}
    			}
    		}	
		}
    }

 	if($arr_name!=NULL){
 		if($arr_age!=NULL){
 			if($arr_addr!=NULL){
 				if($or[0]=="Or"){
    				$result=array_merge($arr_name,$arr_age);
    				if($or[1]=="Or"){
    					$result=array_merge($result,$arr_addr);
    				}elseif($or[1]=="And"){
    					$result=array_intersect($result,$arr_addr);
    				}else{
    					$result=$result;
    				}
    			}elseif($or[0]=="And"){
    				$result=array_intersect($arr_name,$arr_age);
    				if($or[1]=="Or"){
    					$result=array_merge($result,$arr_addr);
    				}elseif($or[1]=="And"){
    					$result=array_intersect($result,$arr_addr);
    				}else{
    					$result=$result;
    				}
    			}
    		}else{
    			if($or[0]=="Or"){
    				$result=array_merge($arr_name,$arr_age);
    			}elseif($or[0]=="And"){
    				$result=array_intersect($arr_name,$arr_age);
    			}else{
    				$result=$result;
    			}
    		}
    	}else{
    		if($arr_addr!=NULL){
    			if($or[1]=="Or"){
    				$result=array_merge($arr_name,$arr_addr);
    			}elseif($or[1]=="And"){
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
 				if($or[1]=="Or"){
    				$result=array_merge($arr_age,$arr_addr);
    			}elseif($or['1']=="And"){
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
			<tr><td><a href="index.php?mod=<?=$module?>&act=view&form_id=<?=$value?>">
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
			</a></td><td><a href="index.php?mod=<?=$module?>&act=view&form_id=<?=$value?>">
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
			</a></td><td><a href="index.php?mod=<?=$module?>&act=view&form_id=<?=$value?>">
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
			</a></td></a></tr>
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
