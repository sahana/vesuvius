<?php
include_once $global['approot'] . '/mod/cs/lib_cs.inc';
  global $global;
  $db = $global['db'];
  
  switch ($_REQUEST['seq'])
    {
  	case '':
  		_shn_ims_select_kit();
  		break;
  		
  	case 'add_kits':
  		_shn_ims_add_kits();
  		break;
  	case 'add_items_for_kits';
  		_shn_ims_add_items_for_kits();
  		break;
  	case 'add_consolidated_kits':
  		if(_shn_ims_validate())
  		{
  			_shn_ims_add_kits();
  		}
  		else
  		{
  			_shn_ims_add_consolidated_kits();
  		}
  		break;
  		
    }

     //$tables = array('ims_item_records' => 'c' , 'ims_inventory_records' => 'c' , 'ct_catalogue' => 'r');
 
function _shn_ims_select_kit()
{
?>

    <h1 align="center"><?php print _t("Select Consolidated Item"); ?><br></h1>
    
<?php
    $form_opts['name'] = 'subcat';
    shn_form_fopen("consolidated_items",null,$form_opts);
    $depth = get_max_depth();
    shn_form_hidden(array('seq'=>'add_kits'));
    shn_sub_cat($depth,'subcat',$inventory_id);
    shn_form_fclose();
}

function _shn_ims_add_kits()
{
	global $global;
	$db = $global['db'];
	$depth = get_max_depth();
        $parent_id = trim($_POST['0']);
    
        for ($i = 1; $i < $depth; $i++) {
            $parent_id = trim($_POST[$i]);
    
            if ($parent_id == null) {
                $parent_id = trim($_POST[$i - 1]);
                break;
            }
        }
       // print $parent_id;
       if($parent_id!=null || $parent_id!='')
       {
    		$_SESSION['ims']['add']['catalog_id'] = $parent_id;
       }
    //print $_SESSION['ims']['add']['catalog_id'];
	shn_form_fopen('consolidated_items');
	shn_form_fsopen(_t('Consolidated Kit Information'));
	shn_form_text(_t('Consolidated kit name'), 'item_name', 'size="25" readonly=true', array('value'=>$item_name));
	//shn_form_text(_t("Amount : "),'amount','size="25"',array('value'=>$amount,'req'=>true));
	$inv_id = $_POST['inventory'];
	$item_name = $_POST['item_name'];
	$inventory_array = array();
	$q = "SELECT inv_uuid, inventory_name from ims_inventory_records;";
	$res = $db->Execute($q);
	$inventory_array['all'] = _t('=== Select ===');
	while(!$res==NULL && !$res->EOF)
	{
		$inventory_array[$res->fields['inv_uuid']] = $res->fields['inventory_name'];
		$res->MoveNext();
	}
	shn_form_select($inventory_array, _t('Inventory'), 'inventory', 'size="1" onchange=submit(this);', array('value'=>$inv_id));
	shn_form_hidden(array('seq'=>'add_kits'));
    //
    echo $_POST['ct_uuid'];
	shn_form_fsclose();
	shn_form_fclose();
	shn_form_fopen('consolidated_items');
	shn_form_hidden(array('seq'=>'add_items_for_kits'));
	shn_form_hidden(array('inv_id'=>$inv_id));
	shn_form_hidden(array('catalog_id'=>$parent_id));
	shn_form_hidden(array('item_name'=>$item_name));
	shn_form_hidden(array('catalog_id'=>$_SESSION['ims']['add']['catalog_id']));
	shn_form_submit(_t('Create Kit'));
	
	list($category, $catalog_item) = split("->",$item_name);
	//print $category;
	//echo '<br>';
	//print $catalog_item;
	//echo strtolower($catalog_item);
	if(strtolower($catalog_item)=='money')
	{
		$sql = "SELECT i.item_id as item_id, i.catalog_id as catalog_id, i.item_name as item_name, i.amount as amount, i.unit as unit, u.name as unit_name, i.suplier_id as suplier_id FROM ims_item_records i INNER JOIN ct_unit u ON i.unit = u.unit_uuid WHERE i.state = 'available' AND i.inv_id='$inv_id' AND i.amount>0 AND i.item_name LIKE '%{$catalog_item}%'";
		//print $sql;
	}
	else
	{
		$sql = "SELECT i.item_id as item_id, i.catalog_id as catalog_id, i.item_name as item_name, i.amount as amount, i.unit as unit, u.name as unit_name, i.suplier_id as suplier_id FROM ims_item_records i INNER JOIN ct_unit u ON i.unit = u.unit_uuid WHERE i.state = 'available' AND i.inv_id='$inv_id' AND i.amount>0 AND i.item_name NOT LIKE '%Money%' ORDER BY i.item_name";
		//print $sql;
	}
	
	
	//print $sql;
	global $global;
	$db = $global['db'];
	$res = $db->Execute($sql);
	//print $sql;
	echo '<div id="result">';
	?><!-- Item Table -->
	<table>
	<thead>
	<tr>
	<td><?php echo _('Item');?></td>
	<td><?php echo _('Amount');?></td>
	<td><?php echo _('Unit');?></td>
	<td><?php echo _('Supplier');?></td>
	<td><?php 
	if(strtolower($catalog_item)=='money')
	{
		echo _('Amount to be used to Buy');
	}
	else
	{
		echo _('Amount Per kit');
	}?></td>
	</tr>
	</thead>
	<tbody>
	
	<?php
	$i=0;
	while(!$res == NULL && !$res->EOF)
	{
				
	?>
	<tr>
	<td><?php echo $res->fields['item_name'];?></td>
	<td><?php echo $res->fields['amount'];?></td>
	<td><?php echo $res->fields['unit_name'];?>
	<td><?php $suplier_name_array=_shn_or_get_suplier_name($res->fields['suplier_id']);
	$suplier_name=$suplier_name_array[$res->fields['suplier_id']];
	echo $suplier_name;//echo $res->fields['suplier_id'];?></td>
	<td><?php 
		shn_form_text(_t(''), 'amount_per_kit-'.$res->fields['item_id'], 'size="10"',array('value'=>$_POST['amount_per_kit']));
	?></td>	
	</tr>
	<?php 
	$i = $i+1;
	$res->MoveNext();
	}
	?></tbody></table>
	<?php
	echo '</div>';
	shn_form_fclose();
}


function _shn_ims_add_items_for_kits()
{
	$inv_id = $_POST['inv_id'];
	$sql = "SELECT i.item_id as item_id, i.catalog_id as catalog_id, i.item_name as item_name, i.amount as amount, i.unit as unit, u.name as unit_name, i.suplier_id as suplier_id FROM ims_item_records i INNER JOIN ct_unit u ON i.unit = u.unit_uuid WHERE i.state = 'available' AND i.inv_id='$inv_id'";
	global $global;
	$db = $global['db'];
	//print $sql;
	$res = $db->Execute($sql);
	//$item_id = $_POST['item_id'];
	$catalog_id = $_POST['catalog_id'];
	$item_name = $_POST['item_name'];
	$amount_per_kit = array();
	echo '<div id="result">';
	?><!-- Item Table -->
	<table>
	<thead>
	<tr>
	<td><?php echo _('Item');?></td>
	<td><?php echo _('Amount');?></td>
	<td><?php echo _('Unit');?></td>
	<td><?php echo _('Supplier');?></td>
	<td><?php echo _('Amount Per kit');?></td>
	</tr>
	</thead>
	<tbody>
	<?php 	
	$i=0;
	while(!$res==NULL && !$res->EOF)
	{
		//print 
		if($_POST['amount_per_kit-'.$res->fields['item_id']] != 0 && $_POST['amount_per_kit-'.$res->fields['item_id']] != NULL)
		{
			$item_id = $res->fields['item_id'];
			$amount_per_kit[$i/*$res->fields['item_id']*/] = $res->fields['item_id'].'-'.$_POST['amount_per_kit-'.$res->fields['item_id']];
			$q = "SELECT i.item_id as item_id, i.catalog_id as catalog_id, i.item_name as item_name, i.amount as amount, i.unit as unit, u.name as unit_name, i.suplier_id as suplier_id FROM ims_item_records i INNER JOIN ct_unit u ON i.unit = u.unit_uuid WHERE i.state = 'available' AND i.item_id=$item_id";
			
			//print $sql;
			//$temp[$i] = $inventory_array;
			//$i=$i+1;
			$r = $db->Execute($q)
			?>
			<tr>
	<td><?php echo $r->fields['item_name'];?></td>
	<td><?php echo $r->fields['amount'];?></td>
	<td><?php echo $r->fields['unit_name'];?>
	<td><?php $suplier_name_array=_shn_or_get_suplier_name($res->fields['suplier_id']);
	$suplier_name=$suplier_name_array[$res->fields['suplier_id']];
	echo $suplier_name;//echo $r->fields['suplier_id'];?></td>
	<td><?php list($item, $amount_kit) = split("-", $amount_per_kit[$i]);
			  echo $amount_kit; ?></td></tr>
	<?php
			$i = $i+1;
		}
		//echo '<br>';
		$res->MoveNext();
	}
	?>
	</tbody>
	</table>
	<?php 
	echo '</div>';
	//var_dump($amount_per_kit);
	$item_name = trim($_POST['item_name']);
	$catalog_id = trim($_POST['catalog_id']);
	//print $catalog_id;
	shn_form_fopen('consolidated_items');
	shn_form_fsopen(_('Add Consolidated Kit'));
	shn_form_text(_t('Consolidated kit name'), 'item_name', 'size="25" readonly=true', array('value'=>$item_name));
	shn_form_text(_t("Number of Kits "),'amount','size="25"',array('value'=>$amount,'req'=>true));
	shn_form_text(_t('Cost Per Unit'), 'cost_per_unit', 'size="25', null);
	
	//*******************
	global $global;
    $db = $global["db"];
    
    //$cq = "SELECT name FROM ct_unit WHERE unit_uuid='$unit';";
    //$cms = $db->Execute($cq);
    
    //$unit_select_array[$unit] = $cms->fields['name'];
    
    $query = "SELECT * FROM ct_cat_unit WHERE ct_uuid='$catalog_id'";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
    $temp2 = $res->fields['unit_uuid'];
    $query1 = "SELECT name FROM ct_unit WHERE unit_uuid ='$temp2'";
    $res2 = $db->Execute($query1);
    
    $unit_select_array[$res->fields['unit_uuid']] = $res2->fields['name'];
    $res->MoveNext();
    }    

    shn_form_select($unit_select_array,_t("Unit : "),'unit_select','size="1"',array('req'=>true));
	
	
	//*******************
	
	$inventory_array = array();
	$q = "SELECT inv_uuid, inventory_name from ims_inventory_records;";
	$res = $db->Execute($q);
	while(!$res==NULL && !$res->EOF)
	{
		$inventory_array[$res->fields['inv_uuid']] = $res->fields['inventory_name'];
		
		$res->MoveNext();
	}
	shn_form_text(_t('Inventory'), 'inventory_name', 'size="25" readonly=true', array('value'=>$inventory_array[$inv_id]));
	
	//shn_form_select($inventory_array, _t('Inventory'), 'inventory', 'size="1"', array('value'=>$inv_id));
	shn_form_fsclose();
	$_SESSION['ims']['add']['amount_per_kit'] = $amount_per_kit;
	//shn_form_hidden(array('item_name'=>$item_name));
	shn_form_hidden(array('inventory'=>$inv_id));
	shn_form_hidden(array('catalog_id'=>$catalog_id));
	shn_form_hidden(array('seq'=>'add_consolidated_kits'));
	//shn_form_hidden(array('amount_per_kit'=>$amount_per_kit));
	shn_form_submit(_t('Add Consolidated kit'));
	shn_form_fclose();
}

function _shn_ims_add_consolidated_kits()
{
	$number_of_kits = trim($_POST['amount']);
	$amount_per_kit = $_SESSION['ims']['add']['amount_per_kit'];
	global $global;
	$db = $global['db'];
	$insert_array = array();
	$insert_array['catalog_id'] = $_POST['catalog_id'];
	$insert_array['inv_id'] = trim($_POST['inventory']);
	$insert_array['item_name'] = trim($_POST['item_name']);
	$insert_array['amount'] = trim($_POST['amount']);
	$insert_array['unit'] = trim($_POST['unit_select']);
	$insert_array['cost_per_unit'] = trim($_POST['cost_per_unit']);
	$insert_array['state'] = 'available';
	$insert_array['inserted_date'] = date('Y-m-d');
	//var_dump($insert_array);
	$res = $db->AutoExecute('ims_item_records', $insert_array, 'INSERT');
	
	$sql = "SELECT item_id FROM ims_item_records ORDER BY item_id DESC;";
	$r = $db->Execute($sql);
	//print $sql;
	$kit_item_id = $r->fields['item_id']; 
	
	$item_history = array();
	$item_history['item_id'] = $kit_item_id;
	$item_history['first_amount'] = trim($_POST['amount']);
	$item_history['unit'] = trim($_POST['unit_select']);
	$res1 = $db->AutoExecute('ims_item_amount_history', $item_history, 'INSERT');
	//print $res1;
	//print $res;
	//var_dump($insert_array);
	
	
	
	
	$consolidated_array = array();
	
	for($i=0;$i<count($amount_per_kit);$i++)
	{
		list($item_id,$amount_item) = split("-",$amount_per_kit[$i]);
		$sql = "SELECT * FROM ims_item_records WHERE item_id='$item_id';";
		$res = $db->Execute($sql);
		$current_amount = $res->fields['amount'];
		$new_amount = $current_amount-($amount_item*trim($_POST['amount']));
		$sql ="UPDATE ims_item_records SET amount='{$new_amount}' WHERE item_id='$item_id'";
		$db->Execute($sql);
		
		$consolidated_array['kit_item_id'] = $kit_item_id;
		$consolidated_array['item_id'] = $item_id;
		$consolidated_array['amount'] = $amount_item*trim($_POST['amount'] ).'';
		$consolidated_array['unit'] = $res->fields['unit'];
		//var_dump($consolidated_array);
		$sql = "INSERT INTO ims_consolidated_kits VALUES ('{$kit_item_id}', '{$item_id}', '{$consolidated_array['amount']}', '{$consolidated_array['unit']}')";
		//print $sql;
		$db->Execute($sql);
		//$res2 = $db->AutoExecute($consolidated_array, 'ims_consolidated_kits', 'INSERT');
		//print $res2;
	}
	
if($res && $res1)
	{
		add_confirmation(_t('Kit Created Successfully'));
	}
	else
	{
		add_error(_t('Database Error'));
	}
	
	unset($_POST['amount']);
	unset($_POST['catalog_id']);
	
	unset($_SESSION['ims']['add']['amount_per_kit']);
	
	unset($_POST['catalog_id']);
	unset($_POST['inventory']);
	unset($_POST['item_name']);
	unset($_POST['amount']);
	unset($_POST['unit_select']);
	unset($_POST['cost_per_unit']);
	$insert_array['state'] = '';
	$insert_array['inserted_date'] = '';
	//var_dump($insert_array);
	
	//print $sql;
	$kit_item_id = '';
	
	
	$item_history['item_id'] = '';
	$item_history['first_amount'] = '';
	$item_history['unit'] = '';
	
		
		$current_amount = '';
		$new_amount = '';
		
		
		$consolidated_array['kit_item_id'] = '';
		$consolidated_array['item_id'] = '';
		$consolidated_array['amount'] = '';
		$consolidated_array['unit'] = '';
		
	//echo 'test';
	
	
	//var_dump($amount_per_kit);
	
	
		
	//$sql = " INSERT INTO ims_item_records (catalog_id,inv_id,suplier_id,item_name,amount,cost_per_unit,unit,manufactured_date,expire_date,state,inserted_date,total_amount,predict_amount) VALUES ('$parent_id','$inv_id','$suplier_id','$item','$amou','$amou','$cost_per_unit','$unit','$manufactured_date','$expire_date','$state','$date','$total_amount','$predeict_amount');";
        //$ims = $db->Execute($sql);
}


function _shn_ims_validate()
{
	$error_flag = false;
	$number_of_kits = trim($_POST['amount']);
	$amount_per_kit = $_SESSION['ims']['add']['amount_per_kit'];
	
	global $global;
	$db = $global['db'];
	
	if(count($amount_per_kit)==0 || count($amount_per_kit)<0)
	{
		add_error(_t('Please Select any amout of items that have to be included in a kit'));
		$error_flag=true;
	}
	
	for($i=0;$i<count($amount_per_kit);$i++)
	{
		list($item_id,$amount_item) = split("-",$amount_per_kit[$i]);
		$sql = "SELECT * FROM ims_item_records WHERE item_id='$item_id';";
		//print $sql;
		$res = $db->Execute($sql);
		$current_amount = $res->fields['amount'];
		$new_amount = $current_amount-($amount_item*trim($_POST['amount']));
		//print $new_amount;
		if($new_amount<0)
		{
			add_error(_t('Not a valid amount '));
			$error_flag=true;
		}
	}
	if($number_of_kits=='' || $number_of_kits==NULL)
	{
		add_error(_t('Item amount is essential '));
		$error_flag=true;
	}
	
	return $error_flag;
}

?>