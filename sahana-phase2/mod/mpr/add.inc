<?php
//validation
switch ($_POST['seq']) {

    case 'search':
        shn_mpr_addmp_form2();            
        break;

    default:
        shn_mpr_addmp_form1();            

}


function shn_mpr_addmp_form1() 
{
    shn_form_fopen("addmp");
    
    shn_form_hidden(array('seq'=>'search'));

    shn_form_fsopen('Identity');
    shn_form_text('Identity Card Number','idcard','size="30"');
    shn_form_text('Passport Number','passport','size="30"');
    shn_form_fsclose();

    shn_form_fsopen("Basic Details");
?>
<p>Please enter any of the following details on the person:</p> 
<?php

    shn_form_text('Full Name','full_name','size="40"');
    shn_form_text('Family Name','family_name','size="40"');
    shn_form_text('Date of Birth','dob','size=8');
    shn_form_opt_select("opt_age_group","Age Group","" ,array('req'=>true));

    shn_form_fsclose();
    shn_form_submit('Next');
    shn_form_fclose();
}

function shn_mpr_addmp_form2() 
{
?>

<?php

    shn_form_fopen("addmp");
    
    shn_form_hidden(array('seq'=>'search'));

    shn_form_fsopen('Identity');
    shn_form_text('Identity Card Number','idcard','size="30"');
} 
?>
