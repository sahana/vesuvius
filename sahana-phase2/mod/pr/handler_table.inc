<?php

	/**
	 *
	 * PHP version 5
	 *
	 * LICENSE: This source file is subject to LGPL license
	 * that is available through the world-wide-web at the following URI:
	 * http://www.gnu.org/copyleft/lesser.html
	 *
	 * @package    Sahana - http://sahana.sourceforge.net
	 * @author     Kethees <sdkethees@gmail.com>
	 * @copyright  Lanka Software Foundation - http://www.opensource.lk
	 */

	function shn_table_result($res,$headers=null,$actions = array('edit'=>true, 'del'=>true, 'view'=>true,'sel'=>true),$submit_options = array('del'=>true), $escape = true){
	    global $global;

	    $chk_name = 'record_no';
	    
	    $url="index.php?mod={$global['module']}&amp;act={$global['action']}";
	    
	    //create the nessary links
	    $url_form=(is_array($submit_options) && array_key_exists('action',$submit_options))?$submit_options['action']:$url;
	    $url_edit=(is_array($actions) && array_key_exists('edit',$actions))?$actions['edit']:$url;
	    $url_del =(is_array($actions) && array_key_exists('del',$actions))?$actions['del']:$url;
	    $url_view=(is_array($actions) && array_key_exists('view',$actions))?$actions['view']:$url;
		$url_sel=(is_array($actions) && array_key_exists('sel',$actions))?$actions['sel']:$url;
	    
	    //if headers are not specify use array keys
	    if(!is_array($res[0]))
	    	return;
	    $keys=array_keys($res[0]);
	    $headers=(isset($headers))?$headers:$keys;
	
	    $field_count=count($headers);
	    
	?>
	<div>
	<form action="<?php echo $url_form ?>" method="post" id="ctr">	
	<table width="100%">
	    <thead>
	        <tr>
	            <?php if(count($submit_options) != 0){ ?>
	            <td><input type="checkbox" onClick="select_all('<?php echo $chk_name?>', this.checked,'ctr');" /></td>
	            <?php $field_count++; } ?>
	            <?php if(isset($actions)){ $field_count++; ?>
	            <td width="60"><?php echo _t('Action')?></td>
	            <?php 
				}			
				?>
	<?php
	    foreach($headers as $column)
	        echo "<td>$column</td>";
	                 $id=$keys[0];			 
	?>
	        </tr>
	    </thead>
	    <tbody>
	<?php
	        //print the table
	        $zebra = 1;
	        foreach($res as $row){
	            $class = ($zebra++%2 == 1)?'odd':'even';
	            ?><tr class=<?php echo $class?>><?php
	            echo "\n";
	            if(count($submit_options) != 0){ 
	                echo "<td width='20px'><input type='checkbox' name='".$chk_name."[]' value ='$row[$id]' /></td>";
	            }			
	            if(isset($actions)){
	?>
	                <td width="60">
	                    <?php if(isset($actions['edit'])){ ?>
	                    <a href="<?php echo  "$url_edit&amp;$id={$row[$id]}" ?>" title="Edit" >
	                    <img src="theme/default/img/tbl_edit.png" alt="edit" /></a>
	                    <?php ;} if(isset($actions['view'])){ ?>
	                    <a href="<?php echo  "$url_view&amp;$id={$row[$id]}" ?>" target="_blank" title="View" >
	                    <img src="theme/default/img/tbl_view.png" alt="view" /></a>
	                    <?php ;} if(isset($actions['del'])){ ?>
	                    <a href="<?php echo  "$url_del&amp;$id={$row[$id]}" ?>" title="Delete"  onclick="return confirmation('delete');">
	                    <img src="theme/default/img/tbl_delete.png" alt="delete" /></a>
						<?php ;} if(isset($actions['sel'])){ ?>
	                    <a href="<?php echo "$url_sel&amp;$id={$row[$id]}" ?>">Select</a>
	                    <?php ;} ?>
	                </td>
	<?php
	            }
	        $i = 1;       
	        foreach($row as $field){
	            if($i != 1){
	                echo "\t<td>";
	                echo htmlspecialchars($field);
	                echo "</td>\n";
	            }	  
	            $i++;          
	        }
	        ?></tr><?php
	        echo "\n";
	    }
	?>
	        <!-- last row of table -->
	        <tr>
	            <td colspan="<?php echo $field_count ?>" class='total'>
	                <?php if($submit_options['del']){ ?>
	                <input type="submit" name="delete" value="<?php echo _t('Delete')?>" title="<?php echo _t('Delete')?>" onclick="return confirmation('delete');" />
	                <?php } ?>
	                <?php if($submit_options['next']){ ?>
	                <input type="submit" name="next" value="<?php echo _t('Next')?>" title="<?php echo _t('Next')?>"  />
	                <?php } ?>
	                <?php if($submit_options['assign']){ ?>
	                <input type="submit" name="assign" value="<?php echo _t('Assign')?>" title="<?php echo _t('Assign')?>"  />
	                <?php } ?>
					 <?php if($submit_options['add']){ ?>
	                <input type="submit" name="add" value="<?php echo _t('Add New Entity')?>" title="<?php echo _t('Add New Entity')?>"  />
					<?php } ?>
	            </td>
	        </tr>
	    </tbody>
	</table>
	</form>
	</div>
	<?php
	}
	
		
