/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

$(document).ready(function(){
    
    $('#db_host').next().next().after('<span id="db_host_err_msg"></span>');
    $('#db_port').next().next().after('<span id="db_port_err_msg"></span>');
    $('#db_name').next().next().after('<span id="db_name_err_msg"></span>');
    $('#db_user').next().next().after('<span id="db_user_err_msg"></span>');
    $('#license_agreement').next().after('<span id="license_agreement_err_msg"></span>');
    
});
