<?php 
/**
 * Add Category  
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
 * This function shows a form to add main category and submit values to a function in the main.inc
 * @access public
 * @return void
 */


function shn_cs_addmain_form()
{
    $extra_opts['req']=true;
    shn_form_fopen('addmain_form_submit');
    shn_form_fsopen(_('Details Of the catalogue'));
    shn_form_text(_("Name   : "),'main_cat_name','size="50"',$extra_opts);
    shn_form_text(_("Description   : "),'description','size="50"');
    shn_form_fsclose();
    shn_form_fsopen(_('Keyword'));
    shn_form_text(_(" "),'keyword','size="50"', array('help'=>_('Enter a keyword which will help you to search purticular catalogue/Item easily.')));
    shn_form_fsclose();
    shn_form_submit(_("Add"));
    shn_form_fclose();

}

/**
 * This function shows the result after processing the POST values from shn_cs_addmain_form().
 *This function is called by shn_cs_addmain_form_submit() in main.inc
 * @access private
 * @return void
 */
function _shn_cs_addmain_form_result()
{
    global $global;
    $db=$global["db"];
    $parentid='0';
    $name = trim($_POST['main_cat_name']);
        $description = trim($_POST['description']);
    
    $id = shn_create_uuid("catalogue");

    $q="insert into ct_catalogue (parentid,ct_uuid,name,description) values($parentid,'$id','$name','$description')";
    $res=$db->Execute($q);
?>

    <div id="result_msg">
    <?php echo $name." was succesfully saved.";?>

    </div>

<?php

}


/**
 * This function shows a form to add a sub category. It calls to a function in lib_cs.inc and submit the result to addsub_form1_submit.
 * @access public
 * @return void
 */

function shn_cs_addsub_form1()
{
    require_once("lib_cs.inc");
    $form_opts['name']='subcat';
     
    shn_form_fopen("addsub_form1_submit",null,$form_opts);
    $max_depth=get_max_depth();
    shn_sub_cat($max_depth,'subcat',true);
    shn_form_fclose();
}


/**
 * This function shows a form to add a sub category.Submit the result to addsub_form2_submit() in main.inc.
 * @access private
 * @return void
 */
function _shn_cs_addsub_form1_result()
{
    global $global;
    $db=$global["db"];

    require_once("lib_cs.inc");
    $parent_id=get_itemid();
    
    $extra_opts['req']=true;
    shn_form_fopen("addsub_form2_submit");
    shn_form_fsopen(_('Sub Catalogue Details'));
    shn_form_text(_("Name   : "),'sub_cat_name','size="50"',$extra_opts);
    shn_form_text(_("Description   : "),'sub_description','size="50"',null);
    shn_form_fsclose();
    shn_form_fsopen(_('Keyword'));
    shn_form_text(_(" "),'keyword','size="50"', array('help'=>_('Enter a keyword which will help you to search purticular catalogue/Item easily.')));
    shn_form_fsclose();
    
    //the parent ID is submitted as a hidden variable
    $parent_id_array=array('0' => $parent_id);
    shn_form_hidden($parent_id_array);

    shn_form_submit(_("Add"));
    shn_form_fclose();
}

/**
 * This function shows the result after processing the POST values from _shn_cs_addsub_form1_result().
 *This function is called by shn_cs_addsub_form2_submit() in main.inc
 * @access private
 * @return void
 */

function _shn_cs_addsub_form2_result()
{
    global $global;
    $db=$global["db"];

    require_once("lib_cs.inc");
    $parent_id=get_itemid();


    $sub_cat_name=trim($_POST['sub_cat_name']);
    $sub_description=trim($_POST['sub_description']);
    $id = shn_create_uuid("catalogue");
    $q="insert into ct_catalogue (parentid,ct_uuid,name,description) values('$parent_id','$id','$sub_cat_name','$sub_description')";
    $res=$db->Execute($q);

?>

    <div id="result_msg">
    <?php echo $sub_cat_name." was succesfully saved.";?>

    </div>

<?php

}



/**
 * This function shows a form to add Measurement Unit
 * @access public
 * @return void
 */
function shn_cs_addunit_form()
{
    global $global;
    $db=$global["db"];
    
    $option_array=array();

    $query="select unit_type_uuid,name from ct_unit_type ";
    $res=$db->Execute($query);
    $option_array['none']='----Select Unit type----';
    while(!$res==NULL && !$res->EOF)
    {
    $option_array[$res->fields['unit_type_uuid']]=$res->fields['name'];
    $res->MoveNext();
    }
    
    if($option_array==null)
    {
    shn_form_fopen(null);
    shn_form_fsopen(_("Information"));
    ?>
    <p><?= _('There is no any Measurement Unit category found. '); ?><a href="index.php?mod=cs&act=addunittype">Add Unit category</a><?= _(' First'); ?></p>
    
    <?php
    shn_form_fsclose();
    shn_form_fclose();
    }    
    else
    {
    $extra_opts['req']=true;
    $form_opts['name']="select_unit_type_form";
    shn_form_fopen("addunit_select_utype_submit",null,$form_opts);
    shn_form_fsopen(_("Select Measurement Unit Type"));
    $select_opts='onChange="changeform()"';
    shn_form_select($option_array,'','unit_type',$select_opts,null);
    shn_form_fsclose();
    shn_form_fclose();
    }

}

function _shn_cs_utype_select_submit_result()
{
    global $global;
    $db=$global["db"];
    
    $unit_type_id=trim($_POST['unit_type']);
    

    $query="select name from ct_unit where unit_type_uuid ='$unit_type_id' and base_flag ='1'";
    $res=$db->Execute($query);
    
    $base_unit_name=$res->fields['name'];

    shn_form_fopen("addunit_form_submit");
    shn_form_fsopen(_('Measurement Unit'));
    $extra_opts['req']=true;
    shn_form_text(_("Unit : "),'unit_name','size="50"',$extra_opts);
    $extra_opts['value'] = $base_unit_name;
    $extra_opts['req']=false;
    shn_form_text(_("Base Unit : "),'base_unit','size="5" readonly=true',$extra_opts);

    shn_form_text(_("Multiplier : "),'multiplier','size="50"',array('req'=>'true','help'=>_('Enter the Multiplier of the entered Unit to the base unit of the Unit Type. Eg: Unit = g, Base unit=kg, Multiplier=0.001 (g=kg*0.001)')));
    shn_form_fsclose();

    $unit_id_array=array('unit_type_id' => $unit_type_id);
    shn_form_hidden($unit_id_array);

    shn_form_submit(_("Save"));

    shn_form_fclose();    

}


/**
 * This function shows the result after processing the POST values from shn_cs_addunit_form().
 *This function is called by shn_cs_addunit_form_submit() in main.inc
 * @access private
 * @return void
 */

function _shn_cs_addunit_form_result()
{
    global $global;
    $db=$global["db"];
        
    $unit_name=trim($_POST['unit_name']);
    $multiplier=trim($_POST['multiplier']);
    $unit_type_id=trim($_POST['unit_type_id']);
    
    $unit_id=shn_create_uuid("unit");
    $query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id','$unit_id','$unit_name','0',$multiplier)";
    $res=$db->Execute($query);

    ?>

    <div id="result_msg">
    <?php echo $unit_name." was succesfully saved."; ?>

    </div>

    <?php

}



function shn_cs_additem_form1()
{
    require_once("lib_cs.inc");
    $form_opts['name']='subcat';
 
    shn_form_fopen("additem_form1_submit",null,$form_opts);
    $max_depth=get_max_depth();
    shn_sub_cat($max_depth,'subcat',true);
    shn_form_fclose();
}


function shn_cs_additem_form1_result()
{
    global $global;
    $db=$global["db"];
    require_once("lib_cs.inc");
    $parent_id=get_itemid();
    
    $option_array=array();
    $query="select unit_type_uuid,name from ct_unit_type ";
    $res=$db->Execute($query);
    $option_array['none']='----Select Unit type----';
    while(!$res==NULL && !$res->EOF)
    {
    $option_array[$res->fields['unit_type_uuid']]=$res->fields['name'];
    $res->MoveNext();
    }

    $form_opts['name']="select_unit_type_form1";
    $extra_opts['req']=true;
    shn_form_fopen("additem_form2_submit",null,$form_opts);
    shn_form_fsopen(_('Item Details'));
    shn_form_text(_("Name   : "),'itemname','size="50"',$extra_opts);
    shn_form_text(_("Description   : "),'item_description','size="50"',null);
    shn_form_fsclose();

    shn_form_fsopen(_('Keyword'));
    shn_form_text(_(" "),'keyword','size="50"', array('help'=>_('Enter a keyword which will help you to search purticular catalogue/Item easily.')));
    shn_form_fsclose();
    
    $select_opts='onChange=change_units(this.options[this.selectedIndex].value)';
    shn_form_fsopen(_('Measurement Type'));
    shn_form_select($option_array,_('Measurement Type :'),'measurement_type',$select_opts,null);
    shn_form_fsclose();

    shn_form_fsopen(_('Measurement Unit'));
    shn_form_multi_select('unit_select',$myoptions, _("Unit :"),'size=5 multiple="multiple"' );
    shn_form_fsclose();


    $parent_id_array=array('0' => $parent_id);
    shn_form_hidden($parent_id_array);

    shn_form_submit(_("Add"));
    shn_form_fclose();

    
}

function shn_cs_additem_form2_result()
{

    global $global;
    $db=$global["db"];

    require_once("lib_cs.inc");
    $parent_id=get_itemid();
    
    $item_name=trim($_POST['itemname']);
    $description=trim($_POST['item_description']);

    $id = shn_create_uuid("catalogue");
    $q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag) values('$parent_id','$id','$item_name','$description','1')";
    $res=$db->Execute($q);

    $unit_selected= $_POST["unit_select"];
    $num = sizeof($unit_selected);

    for($i=0;$i<$num;$i++)
    {
    $temp = $unit_selected[$i];
    $q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$id','$temp')";
    $res=$db->Execute($q);
    
    }
    
?>

    <div id="result_msg">
    <?php echo $item_name." was succesfully saved.";?>

    </div>

<?php

    
}


function shn_cs_add_unit_type_form()
{
    $extra_opts['req']=true;
    shn_form_fopen("addunitform_submit");
    shn_form_fsopen(_('Unit Type Details'));
    shn_form_text(_("Name   : "),'unit_type_name','size="50"',$extra_opts);
    shn_form_text(_("Description   : "),'unit_type_description','size="50"',null);
    shn_form_fsclose();

    shn_form_fsopen(_('Base Unit Details'));
    shn_form_text(_("Name   : "),'base_unit_name','size="50"',array('req'=>'true','help'=>_('Specify a base unit here. Eg: Unit Type - Mass, Base Unit- kg')));
    shn_form_fsclose();

    shn_form_submit(_("Add"));
    shn_form_fclose();
}

function _shn_cs_add_unit_type_form_result()
{
    global $global;
    $db=$global["db"];

    $unit_type_name=trim($_POST['unit_type_name']);
    $description=trim($_POST['unit_type_description']);
    $base_unit_name=trim($_POST['base_unit_name']);

    $unit_type_id = shn_create_uuid("unit_type");
    $q="insert into ct_unit_type (unit_type_uuid,name,description) values('$unit_type_id','$unit_type_name','$description')";
    $res=$db->Execute($q);

    $unit_id=shn_create_uuid("unit");
    $query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id','$unit_id','$base_unit_name','1',0)";
    $res=$db->Execute($query);

?>

    <div id="result_msg">
    <?php echo $unit_type_name." was succesfully saved.";?>

    </div>

<?php
}



/**
 * This function validates the values entered in add main form.
 *This function is called by shn_cs_addmain_form_submit() in main.inc
 * @access private
 * @return boolean
 */

function _shn_cs_validate_addmainform()
{
$error_flag=false;
clean_errors();
    
    //this checks whether name entered in the add main form
    if(trim($_POST['main_cat_name'])==null)
    {
    add_error(_("Please Enter the Catalogue Name"));
    $error_flag=true;
    }

    return $error_flag;
}

/**
 * This function validates the values entered in add unit form.
 *This function is called by shn_cs_addunit_form_submit() in main.inc
 * @access private
 * @return boolean
 */

function _shn_cs_validate_unitform()
{
$error_flag=false;
clean_errors();
    
    //this checks whether name entered in the add unit form
    if(trim($_POST['unit_name'])==null)
    {
    add_error(_("Please Enter the Unit Name"));
    $error_flag=true;
    }    

    if(trim($_POST['multiplier'])==null)
    {
    add_error(_("Please Enter the Multiplier"));
    $error_flag=true;
    }



    return $error_flag;
}


function _shn_cs_validate_subcatform()
{
$error_flag=false;
clean_errors();
    
    //this checks whether name entered in the add sub category form
    if(trim($_POST['sub_cat_name'])==null)
    {
    add_error(_("Please Enter the Sub Category Name"));
    $error_flag=true;
    }    

    return $error_flag;
}

function _shn_cs_validate_additem_form()
{
$error_flag=false;
clean_errors();

    //this checks whether name entered in the add Item form
    if(trim($_POST['itemname'])==null)
    {
    add_error(_("Please Enter the Item Name"));
    $error_flag=true;
    }    

    if(trim($_POST['measurement_type'])==null || trim($_POST['measurement_type'])=='none')
    {
    add_error(_("Please Select the Unit Type"));
    $error_flag=true;
    }

    if(trim($_POST['unit_select'])==null)
    {
    add_error(_("Please Select Unit/Units"));
    $error_flag=true;
    }
    

    return $error_flag;
}

function _shn_cs_validate_unit_type_form()
{
$error_flag=false;
clean_errors();

    //this checks whether name entered in the add Item form
    if(trim($_POST['unit_type_name'])==null)
    {
    add_error(_("Please Enter the Unit Type Name"));
    $error_flag=true;
    }    

    if(trim($_POST['base_unit_name'])==null)
    {
    add_error(_("Please Enter the Base Unit Name"));
    $error_flag=true;
    }
    

    return $error_flag;
}


?>
<script type="text/javascript">
    function changeform()
    {
    //document.select_unit_type_form.submit();
    var x=document.select_unit_type_form.unit_type.options[document.select_unit_type_form.unit_type.selectedIndex].value;
    if(x!='none')
        {
        document.select_unit_type_form.submit();
        }
    }
</script>
<?php


?>
<script type="text/javascript">
    var url = "xml.php?"; 
     var http;
        
    function getHTTPObject() 
    {
        var xmlhttp;
        
        //conditional compliation
        /*@cc_on
        @if (@_jscript_version >= 5)
            try {
                xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
            } catch (e) {
                try {
                    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                } catch (E) {
                    xmlhttp = false;
                }
            }
        @else
            xmlhttp = false;
        @end @*/

        if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
            try {
                xmlhttp = new XMLHttpRequest();

            } catch (e) {
            xmlhttp = false;
            }
        }

    return xmlhttp;
    }

function handleHttpResponse(){
        if (http.readyState == 4) 
    { // Split the comma delimited response into an array  
                results = http.responseText.split(",");
                if (results[0]!="null")
            {                
                var x=document.getElementsByName('unit_select[]');

                    for (i=0; i<=x[0].options.length+1; i++)
                    {
                            x[0].options[0]=null;
                            }

                j=0;
                for (i=1; i<results.length-1; i=i+2, j++)
                    {
                    //alert(results[i]);
                         opt = document.createElement("option") ;
                          opt.value = results[i] ;
                          opt.text = results[i+1].replace(/[^A-Za-z]$/,"");
                          x[0].options[j] = opt;
                            }
                    }
        } 
    }

    function change_units(selection){
    
        http = getHTTPObject();

        var url2=url + "act=unit_cat&cat="+selection;
          http.open("GET", url2, true); 
        http.onreadystatechange = function(){}; 
        http.onreadystatechange = handleHttpResponse; 
        http.send(null);
    }


</script>
<?php

?>
