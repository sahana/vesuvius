<?php
/**
 * Search Category  
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/**
 * This function shows a form to select the category.Submit the result to shn_cs_search_submit() in main.inc.
 * @access private
 * @return void
 */
function shn_cs_search_cat()
{
    $option_array = array('none' => _t('-----Select Search-----'),'Item' => _t('Item/Catalog'),'Unit' => _t('Unit'),'Unit_type' => _t('Unit Type'));
    $form_opts['name'] = "select_type_form";
    shn_form_fopen('select_type_submit',null,$form_opts);
    shn_form_fsopen(_t('Select Search Type'));
    $select_opts = 'onChange="shn_cs_search_cat_js()"';
    shn_form_select($option_array,'','search_type',$select_opts,null);
    shn_form_fsclose();
    shn_form_fclose();
    shn_cs_search_cat_js();
}

/**
 * This function Displays the Form for selecting catalog.
 * @access private
 * @return void
 */
function _shn_cs_cat_form()
{
    shn_form_fopen('search_item_submit');
    shn_form_fsopen(_t('Search Details'));
    shn_form_text(_t("Name   : "),'cat_item_name','size="50"',array('req' =>'true', 'help'=>_t('Enter the Item/catalog to be searched')));
    $options = array('item' => _t('Item'),'catalogue' => _t('Catalog'));
    shn_form_radio($options,'','item_cat_radio');
    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    shn_form_fclose();
}

/**
 * This function shows the result after processing the POST values from shn_cs_search_cat().
 *This function is called by shn_cs_search_submit() in main.inc
 * @access private
 * @return void
 */
function _shn_cs_search_item_cat_submit_result()
{
    global $global;
    $db = $global["db"];

    $cat_item_name = trim($_POST['cat_item_name']);
    $item_cat_radio = trim($_POST['item_cat_radio']);

    if ($item_cat_radio == 'item') {
        $query = "SELECT * FROM ct_catalogue WHERE name='$cat_item_name' AND final_flag='1'";
        $res = $db->Execute($query);
    
        $name = $res->fields["name"];
        $description = $res->fields["description"];
    } else if ($item_cat_radio == 'catalogue') {
        $query = "SELECT * FROM ct_catalogue WHERE name='$cat_item_name' AND final_flag='0'";
        $res = $db->Execute($query);
    
        $name = $res->fields["name"];
        $description = $res->fields["description"];
    }

    if ($name == null && $description == null) {
        print "<br /><br /><b>" . _t("There is no match found.") . "</b>";
    } else {
        ?>
        <br><br>
        <div id="result">
        <table>
        <THEAD>
            <TD><strong><?php echo _t("Category Name")?></strong></TD>
            <TD><strong><?php echo _t("Description")?></strong></TD>
        </THEAD>
        <TBODY>

        <tr>
            <td><?php print $name; ?></td>
            <td><?php print $description; ?></td>
        </tr>

        </TBODY> 
        </table>
        </div>
        <?php
    }
}

/**
 * This function Displays the Form for selecting Measurement Unit Type.
 * @access private
 * @return void
 */
function _shn_cs_unit_form()
{   
    global $global;
    $db = $global["db"];
    $option_array = array();
    $query = "SELECT unit_type_uuid,name FROM ct_unit_type ";
    $res = $db->Execute($query);
    $option_array['none'] = _t('----Select Unit type----');
    
    while (!$res == NULL && !$res->EOF) {
        $option_array[$res->fields['unit_type_uuid']] = $res->fields['name'];
        $res->MoveNext();
    }
    
    $form_opts['name'] = "unit_type";
    shn_form_fopen("search_unit_submit");
    shn_form_fsopen(_t('Select Measurement Unit Type'));
    shn_form_select($option_array,'','measurement_type',$select_opts,null);
    shn_form_fsclose();
    shn_form_fsopen(_t('Search Details'));
    //$extra_opts['req']=true;
    shn_form_text(_t("Unit Name   : "),'unit_name','size="50"',array('req'=>'true','help'=>_t('Enter the Unit name to be searched.')));
    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    shn_form_fclose();
}

/**
 * This function shows the result after processing the POST values from _shn_cs_unit_form().
 *This function is called by shn_cs_search_unit_submit() in main.inc
 * @access private
 * @return void
 */
function _shn_cs_search_unit_submit_result()
{
    global $global;
    $db = $global["db"];

    $search_name = trim($_POST['unit_name']);
    $unit_type_id = trim($_POST['measurement_type']);

    if ($unit_type_id == 'none' && $search_name == '') {
        $query = "SELECT * FROM ct_unit";
        $res = $db->Execute($query);
    } elseif ($search_name == '') {
        $query = "SELECT * FROM ct_unit WHERE unit_type_uuid='$unit_type_id' ";
        $res = $db->Execute($query);
    } else {
   		$query = "SELECT * FROM ct_unit WHERE name='$search_name' ";
        $res = $db->Execute($query);
    }

	?>
    <br><br>
    <div id="result">
    <table>
    <THEAD>
        <TD><strong><?php echo _t("Unit Type")?></strong></TD>
        <TD><strong><?php echo _t("Unit")?></strong></TD>
        <TD><strong><?php echo _t("Multiplier")?></strong></TD>
    </THEAD>
    <TBODY>
    <?php 
    
    while (!$res == NULL && !$res->EOF) {
        $unit_name = $res->fields["name"];
        $multiplier = $res->fields["multiplier"];

        $temp = $res->fields["unit_type_uuid"];
        
        $query = "SELECT name FROM ct_unit_type WHERE unit_type_uuid='$temp' ";
        $res3 = $db->Execute($query);
        $unit_type_name = $res3->fields["name"];        

    ?>
    <tr>
        <td><?php print $unit_type_name; ?></td>
        <td><?php print $unit_name; ?></td>
        <td><?php print $multiplier; ?></td>
    </tr>
    <?php 
        $res->MoveNext();
    }//end of while loop
    ?>
    </TBODY>
    </table>
    </div>
    <?php
}

/**
 * This function Displays the Form for selecting Unit type
 * @access private
 * @return void
 */
function _shn_cs_unit_type_form()
{
    shn_form_fopen('search_unit_type_submit');
    shn_form_fsopen(_t('Search Details'));
    shn_form_text(_t("Unit type   : "),'unit_type_name','size="50"',array('req' =>'true', 'help'=>_t('Enter the unit type to be searched')));
    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    shn_form_fclose();
}


/**
 * This function shows the result after processing the POST values from shn_cs_search_cat().
 * This function is called by shn_cs_search_unit_type_submit() in main.inc
 * @access private
 * @return void
 */
function _shn_cs_search_unit_type_submit_result()
{
    global $global;
    $db = $global["db"];

    $unit_type_name = trim($_POST['unit_type_name']);
    $query = "SELECT * FROM ct_unit_type WHERE name='$unit_type_name'";
    $res = $db->Execute($query);
    
    $name = $res->fields["name"];
    $description = $res->fields["description"];

	?>
    <br /><br />
    <div id="result">
    <table>
    <THEAD>
        <TD><strong><?php echo _t("Unit Type Name")?></strong></TD>
        <TD><strong><?php echo _t("Description")?></strong></TD>
    </THEAD>
    <TBODY>

    <tr>
        <td><?php print $name; ?></td>
        <td><?php print $description; ?></td>
    </tr>

    </TBODY> 
    </table>
    </div>
	<?php
}

