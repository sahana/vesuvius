<?php
//validation
switch ($_POST['seq']) {

    default:
        shn_mpr_search_default();
    break;

}

function shn_mpr_search_default()
{
    global $global;
    
    $arr = $global['db']->GetAll(
}

function shn_mpr_search_show_result($details)
{
?>
<TABLE>
<TR>
    <TD>Picture</TD><TD>Name</TD><TD>Appearance</TD><TD>Missing Details</TD>
</TR>
<?php
    foreach($details as $detail){
?>
    <TR>
        <TD>
<?php
    shn_show_thumb($detail['p_uuid']); 
?>
        </TD>
        <TD>
<?php
    echo $detail['full_name'].'<br>'.$detail['family_name'].'<br>'.$details['l10n_name'];
?>
        </TD>
        <TD>
<?php
    echo ($details['height']?'Height : '.$details['height'].'<br>':'').
        ($details['weight']?'Weight : '.$details['weight'].'<br>':'').
        ($details['opt_eye_color']?'Eye Colour : '.shn_get_field_opt($details['opt_eye_color'],'opt_eye_color').'<br>':'').
        ($details['opt_skin_color']?'Skin Colour : '.shn_get_field_opt($details['opt_skin_color'],'opt_skin_color').'<br>':'').
        ($details['opt_hair_color']?'Hair Colour : '.shn_get_field_opt($details['opt_hair_color'],'opt_hair_color').'<br>':'');
?>
        </TD>
        <TD>
<?php
    echo ($details['last_seen']?'Last Seen : '.$details['last_seen'].'<br>':'').
            ($details['last_clothing']?'Last Clothing : '.$details['last_clothing'].'<br>':'').
            ($details['comments']?'Comments : '.$details['comments']:'');    
?>
        </TD>
    </TR>
<?php
    }
}
?>
