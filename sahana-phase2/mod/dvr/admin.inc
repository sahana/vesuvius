<?php
function _shn_dvr_adm_sub_menu()
{
?>
<div id="submenu_v">
<a href="index.php?mod=dvr&act=adm_default">Common Configuration</a>
<a href="index.php?mod=dvr&act=adm_forms">Configure Forms</a>
<a href="index.php?mod=dvr&act=adm_forms">Access Control</a>
</div>
<br>
<?php
}
function shn_dvr_adm_default()
{
    _shn_dvr_adm_sub_menu();
?>
    <p><b> Welcome to the DVR admin page </b></p>
    <p> This can only be seen through the admin module</p>

    <form>
     <input type="text"/>

    </form>
    


<?php
}
function shn_dvr_adm_forms()
{
    _shn_dvr_adm_sub_menu();
    _shn_dvr_adm_show_form();
}

function _shn_dvr_adm_show_form()
{
?>
<form method="POST">
Select The Form : 
<select name="form_type" onchange="submit()">
    <option value="1" <?= ($_POST['form_type']=='1'?'selected':''); ?>>Common</option>
    <option value="2" <?= ($_POST['form_type']=='2'?'selected':''); ?>>Missing Form </option>
    <option value="3" <?= ($_POST['form_type']=='3'?'selected':''); ?>>Displaced Form</option>
    <option value="4" <?= ($_POST['form_type']=='4'?'selected':''); ?>>Affected Form</option>
</select>
</form>
<?php
    global $global;
    $rs = $global['db_cache']->Execute("select a.meta_id, a.caption, a.type, b.section, b.element_order FROM metadata a, module_metadata b WHERE a.meta_id=b.meta_id AND b.module_id=1 AND b.forms=1 ORDER BY b.section, b.element_order");
    echo '<div id="ahref_list">';
    while($result = $rs->FetchRow()){
?>
    <a href="index.php?mod=dvr&act=adm_forms&meta_id=<?= $result['a.meta_id']; ?>">
    <ul>
        <li><?= $result['a.caption']; ?></li>
        <li><?= $result['a.type']; ?></li>
        <li><?= $result['b.section']; ?></li>
        <li><input type="text" size="1" name="element_order[<?= $result['a.meta_id']; ?>]" value="<?= $result['b.element_order']; ?>" /></li>
</a>
        <li><input type="button" name="delete[<?= $result['a.meta_id']; ?>" value="remove" /></li>
    </ul>
<?php
    }
    echo '</div>';
?>
    <a href="index.php?mod=dvr&act=adm_forms&sub_act=assign&form_type=<?= $_POST['form_type']; ?>">Assign More Fields</a>
<?php
}  

function _shn_adm_show_meta_types($default,$index)
{
    $types = array('text','hidden','dropdown','location');
    if($index)
        $return = '<select name="table_name['.$index.']" >';
    else
        $return = '<select name="table_name" >';

    foreach ($types as $type){
        $return .= '<option value="'.$type.'" '.(($type==$default)?'selected':'').'>'.$type.'</option>';
    }

    $return .= '</select>';
    return $return;
}

function _shn_adm_show_tablenames($default,$index)
{
    $names = array('metadata_int', 'metadata_date', 'metadata_text');
    if($index)
        $return = '<select name="types['.$index.']" >';
    else
        $return = '<select name="types" >';

    foreach ($names as $name){
        $return .= '<option value="'.$name.'" '.(($name==$default)?'selected':'').'>'.$name.'</option>';
    }

    $return .= '</select>';
    return $return;
}

?>

