/**
 * @name         Dynamic Portable App
 * @version      0.1
 * @package      dpa
 * @author       Akila Ravihansa Perera <ravihansa3000@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0723
 */

var iframe_id = "#dpa_ifrm_dl";
var dialog_id = "#dpa_dialog";
var form_id = "#dpa_download_form"
var status_tbl_id = "#tbl_dpa_status";
var nonce_str;
var refreshIntervalId;

$(document).ready(function() {
    $(form_id).submit(function(e) {
        e.preventDefault();        
        var form = $(form_id);
        var inputs = form.find("input, select, button, textarea");
        inputs.prop("disabled", true);    
        $(dialog_id).html('<h5>Please wait while we are processing your request. Do not close this window or browse to another page.</h5><div style="padding: 20px 0;"><img src="res/img/ajax-loader.gif" /></div>');
        show_dialog();       
        var url = getUrl();        
        var jqiFrame = $('<iframe id="'+iframe_id+'" src= "'+url+'" style="display: none;" />');        
        $('body').append(jqiFrame);
        
        refreshIntervalId = setInterval(function(){
            var ready = getCookie("FILE_READY");
            if (ready == nonce_str){    
                var checksum = getCookie("FILE_CHECKSUM");
                loadComplete(checksum);                
            }else if (ready == nonce_str + ":ERROR" || ready == ":ERROR"){
                loadError();
            }
        },1000);		
    });
	
    $('#btn_status_bindir_fix').click(function() {
        $(dialog_id).html('<h5 style="text-align: left;">Unable to change directory permissions. Please set write permissions to the \'bin\' directory specified in Portable App module configuration file.</h5><div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
        show_dialog();
    });
	
    $('#btn_status_repo_fix').click(function() {
        $(dialog_id).html('<h5 style="text-align: left;">Repository did not respond as expected. Goto configuration section to update repository URL.</h5><div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
        show_dialog();
    });
        
    $('#btn_status_win_wrapper_fix').click(function() {
        $(status_tbl_id).find("input, select, button, textarea").prop("disabled", true);       
        $(dialog_id).html('<h5 id="dpa_progress">Wrapper file is being downloaded to the server. Please wait...</h5><div style="padding: 0;"><div style="padding: 2px 0;"><img src="res/img/ajax-loader.gif" /></div><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
        show_dialog();        
        var jqxhr = $.ajax({
            type: "GET",
            url: "?dpa&winwrapperfix",
            dataType: "text",
            cache: false,
            success: function(result) {
                var obj = jQuery.parseJSON(result);
                $(dialog_id).html('<h5 id="dpa_progress">'+obj.response+'</h5><div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
            },
            error:function (xhr, ajaxOptions, thrownError){
                $(dialog_id).html('<h5>Error! Unable to send the request. Please try again later.</h5><div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
            },              
            async: true
        });
        jqxhr.always(function() {
            $(status_tbl_id).find("input, select, button, textarea").prop("disabled", false);
        });
    });
    
    $('#btn_status_win_wrapper_progress').click(function() {
        $(status_tbl_id).find("input, select, button, textarea").prop("disabled", true);       
        $(dialog_id).html('<h5 id="dpa_progress">Requesting status. Please wait...</h5><div style="padding: 0;"><div style="padding: 2px 0;"><img src="res/img/ajax-loader.gif" /></div><input type="button" value="Cancel" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
        show_dialog();
        var jqxhr = $.ajax({
            type: "GET",
            url: "?dpa&winwrapperstatus",
            dataType: "text",
            cache: false,
            success: function(result) {                
                var obj = jQuery.parseJSON(result);
                $(dialog_id).html('<h5 id="dpa_progress">'+obj.response+'</h5><div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
            },
            error:function (xhr, ajaxOptions, thrownError){
                $(dialog_id).html('<h5>Error! Unable to send the request. Please try again later.</h5><div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
            },              
            async: true
        });
        jqxhr.always(function() {
            $(status_tbl_id).find("input, select, button, textarea").prop("disabled", false);
        });
    });
	
	$('#dpa_checkall').click(function() {
		$('.modules').attr('checked', 'checked');
	});
	
	$('#dpa_uncheckall').click(function() {
		$('.modules').removeAttr('checked');
	});
	
	$(".dpa_tooltip_icon").hover(
		function () {
			$(this).append('<div class="dpa_tooltip"><p>This shows whether Dynamic Portable App module has all the required resources to perform correctly. Please see whether prerequisites are fully met. In some cases module is able to perform correctly with partial completion of  prerequisites.</p></div>');
		}, 
		function () {
			$(".dpa_tooltip").remove();
		}
	);
	
});
    

function loadError(){
    clearInterval(refreshIntervalId);
    var form = $(form_id);	
    var inputs = form.find("input, select, button, textarea");
    inputs.prop("disabled", false);    
    $(dialog_id).html('<h5>Error! Something went wrong. Please try again later.</h5><div style="padding: 20px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
	

}



function loadComplete(checksum){
    clearInterval(refreshIntervalId);
    var form = $(form_id);	
    var inputs = form.find("input, select, button, textarea");
    inputs.prop("disabled", false);    
    $(dialog_id).html('<h5>OK! Download has started. After the file is downloaded extract the zip archive and launch vesuvius.exe</h5>' +
                        '<div style="padding: 5px 0;">MD5 File Checksum: ' + checksum + '</div>' +
                       '<div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
                   
                   
}

function getUrl(){
    var form = $(form_id);
    var base_url = form.attr('action');
    var params = "";
    var selected_mods = [];
    nonce_str = make_nonce();
	
    $('.modules:checkbox:checked').each(function() {
        selected_mods.push($(this).attr('name'));
    });	
	
    $.each(selected_mods, function(i, val) {
        params += "&" + val;
    });	
	
    var os = $("#os").val();
    params += "&os=" + os;
    params += "&nonce=" + nonce_str;
	
    return base_url + params;	
}

function show_dialog() {    
    //Get the window height and width
    var winH = $(window).height();
    var winW = $(window).width();
              
    //Set the popup window to center
    $(dialog_id).css('top',  winH/2-$(dialog_id).height()/2);
    $(dialog_id).css('left', winW/2-$(dialog_id).width()/2);
	
    //transition effect
    $(dialog_id).fadeIn(200);        
}



function make_nonce(){
    var text = "";
    var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for( var i=0; i < 20; i++ )
        text += possible.charAt(Math.floor(Math.random() * possible.length));

    return text;
}

function getCookie(c_name)
{
    var c_value = document.cookie;
    var c_start = c_value.indexOf(" " + c_name + "=");
    if (c_start == -1)
    {
        c_start = c_value.indexOf(c_name + "=");
    }
    if (c_start == -1)
    {
        c_value = null;
    }
    else
    {
        c_start = c_value.indexOf("=", c_start) + 1;
        var c_end = c_value.indexOf(";", c_start);
        if (c_end == -1)
        {
            c_end = c_value.length;
        }
        c_value = unescape(c_value.substring(c_start,c_end));
    }
    return c_value;
}