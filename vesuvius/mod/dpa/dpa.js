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
var wizard_id = "#dpa_wizard_box";
var monthNames = ["January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"];
var nonce_str;
var refreshIntervalId;

$(document).ready(function() {
    $('#dpa_btn_download').click(function(e) {
        e.preventDefault();
        if ($(this).val() === "Download and Publish" && $('#dpa_publish_desc').val() === "") {
            $(dialog_id).hide();
            alert('Please enter a description for the instance that will be published.');
            return;
        }
        var inputs = $('#dpa_download_form').find("input, select, button, textarea");
        inputs.prop("disabled", true);
        $(dialog_id).html('<h5>Please wait while we are processing your request. Do not close this window or browse to another page.</h5><div style="padding: 20px 0;"><img src="res/img/ajax-loader.gif" /></div>');
        show_dialog();
        var url = getUrl() + '&enable_download';
        var jqiFrame = $('<iframe id="' + iframe_id + '" src= "' + url + '" style="display: none;" />');
        $('body').append(jqiFrame);
        refreshIntervalId = setInterval(function() {
            var ready = getCookie("FILE_READY");
            if (ready === nonce_str) {
                var checksum = getCookie("FILE_CHECKSUM");
                if ($('#dpa_btn_download').val() === "Download and Publish") {
                    var publish_status = getCookie("FILE_PUBLISH");
                    if (publish_status === "success") {
                        load_publish_Complete(checksum, true);
                    } else {
                        load_publish_Complete(checksum, false);
                    }
                } else {
                    loadComplete(checksum);
                }
            } else if (ready === nonce_str + ":ERROR" || ready === ":ERROR") {
                loadError();
            }
        }, 1000);
    });


    $('#dpa_btn_publish').click(function(e) {
        e.preventDefault();
        if ($(this).val() === "Publish only" && $('#dpa_publish_desc').val() === "") {
            $(dialog_id).hide();
            alert('Please enter a description for the instance that will be published.');
            return;
        }
        var inputs = $('#dpa_download_form').find("input, select, button, textarea");
        inputs.prop("disabled", true);
        $(dialog_id).html('<h5>Please wait while we are processing your request. Do not close this window or browse to another page.</h5><div style="padding: 20px 0;"><img src="res/img/ajax-loader.gif" /></div>');
        show_dialog();
        var url = getUrl();
        var jqxhr = $.ajax({
            type: "GET",
            url: url,
            dataType: "text",
            cache: false,
            success: function(result) {
                try {
                    var obj = jQuery.parseJSON(result);
                    $(dialog_id).html('<h5 id="dpa_result">' + obj.response + '</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
                } catch (ex) {
                    $(dialog_id).html('<h5 id="dpa_progress">Error! Invalid response from the server.</h5><h5>' + result + '</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
                }
            },
            error: function(xhr, ajaxOptions, thrownError) {
                $(dialog_id).html('<h5>Error! Unable to send the request. Please try again later.</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
            },
            async: true
        });
        jqxhr.always(function() {
            $('#dpa_download_form').find("input, select, button, textarea").prop("disabled", false);
            update_download_form_inputs();
        });

    });

    $('#btn_status_bindir_fix').click(function() {
        $(dialog_id).html('<h5 style="text-align: left;">Unable to change directory permissions. Please set write permissions to the \'bin\' directory specified in Portable App module configuration file.</h5><div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
        show_dialog();
    });

    $('#btn_status_repo_fix').click(function() {
        $(dialog_id).html('<h5>Repository did not respond as expected. Goto configuration section to update repository URL.</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
        show_dialog();
    });

    $('#btn_status_win_wrapper_fix').click(function() {
        $('#tbl_dpa_status').find("input, select, button, textarea").prop("disabled", true);
        $(dialog_id).html('<h5 id="dpa_progress">Portable wrapper file is being downloaded to the server.<br/>You may close this window. The download process will continue in the background.</h5><div style="padding: 0;"><div style="padding: 5px 0 10px 0;"><img src="res/img/ajax-loader.gif" /></div><input type="button" value="OK" class="styleTehButton" onclick="close_dialog();" /></div>');
        show_dialog();
        var jqxhr = $.ajax({
            type: "GET",
            url: "?dpa&winwrapperfix",
            dataType: "text",
            cache: false,
            success: function(result) {
                try {
                    var obj = jQuery.parseJSON(result);
                    $(dialog_id).html('<h5 id="dpa_progress">' + obj.response + '</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
                } catch (ex) {
                    $(dialog_id).html('<h5 id="dpa_progress">Error! Invalid response from the server.</h5><h5>' + result + '</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
                }
            },
            error: function(xhr, ajaxOptions, thrownError) {
                $(dialog_id).html('<h5>Error! Unable to send the request. Please try again later.</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
            },
            async: true
        });
        jqxhr.always(function() {
            $('#tbl_dpa_status').find("input, select, button, textarea").prop("disabled", false);
        });
    });

    $('#btn_status_win_wrapper_progress').click(function() {
        $('#tbl_dpa_status').find("input, select, button, textarea").prop("disabled", true);
        $(dialog_id).html('<h5 id="dpa_progress">Requesting status. Please wait...</h5><div style="padding: 0;"><div style="padding: 15px 0 10px 0;"><img src="res/img/ajax-loader.gif" /></div><input type="button" value="Cancel" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
        show_dialog();
        var jqxhr = $.ajax({
            type: "GET",
            url: "?dpa&winwrapperstatus",
            dataType: "text",
            cache: false,
            success: function(result) {
                try {
                    var obj = jQuery.parseJSON(result);
                    $(dialog_id).html('<h5 id="dpa_progress">' + obj.response + '</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
                } catch (ex) {
                    $(dialog_id).html('<h5 id="dpa_progress">Error! Invalid response from the server.</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
                }
            },
            error: function(xhr, ajaxOptions, thrownError) {
                $(dialog_id).html('<h5>Error! Unable to send the request. Please try again later.</h5><div style="padding: 25px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
            },
            async: true
        });
        jqxhr.always(function() {
            $('#tbl_dpa_status').find("input, select, button, textarea").prop("disabled", false);
        });
    });

    $('#dpa_checkall').click(function() {
        $('#dpa_download_form .modules').attr('checked', 'checked');
    });

    $('#dpa_uncheckall').click(function() {
        $('#dpa_download_form .modules').removeAttr('checked');
    });

    $('#dpa_wizard').click(function() {
        show_wizard();
    });

    $('#dpa_wizard_ok').click(function() {
        $('#dpa_download_form .modules').removeAttr('checked');
        var matches = [];
        $(".dpa_wizard_feature:checked").each(function() {
            matches = matches.concat(this.value.split(","));
        });
        for (var i = 0; i < matches.length; i++) {
            module = matches[i].trim();
            $("#dpa_download_form input[name='" + module + "']").prop('checked', true);
        }
        $(wizard_id).hide();
    });

    $('#dpa_wizard_cancel').click(function() {
        $(wizard_id).hide();
    });

    $(".dpa_tooltip_icon").hover(
            function() {
                $(this).append('<div class="dpa_tooltip"><p>This shows whether Dynamic Portable App module has all the required resources to perform correctly. Please see whether prerequisites are fully met. In some cases module is able to perform correctly with partial completion of  prerequisites.</p></div>');
            },
            function() {
                $(".dpa_tooltip").remove();
            }
    );

    $("#dpa_event_filter").change(update_event_filter);
    $("#dpa_selected_disaster").change(update_incident_list);
    $("#dpa_selected_incident").change(update_event_list);

    $('#dpa_enable_publish').click(function() {
        update_publish();
    });

    $('.dpa_manage_datetime, .dpa_log_datetime, .dpa_download_datetime').each(function() {
        var date = new Date($(this).attr("utc_date") + 'T' + $(this).attr("utc_time") + '+00:00');
        console.log(date.toString());
        var localDate = date.getFullYear() + ' ' + monthNames[date.getMonth()] + ' ' + date.getDate();
        var localTime = date.getHours() + ':' + date.getMinutes() + ':' + date.getSeconds();
        $(this).html(localDate + ' ' + localTime);
    });

    update_download_form_inputs();
});

function update_download_form_inputs() {
    $('.required_modules').attr('disabled', 'disabled');
    update_event_filter();
    update_publish();
}

function update_publish() {
    if ($("#dpa_enable_publish").is(":checked")) {
        $('#dpa_publish_desc').removeAttr('disabled');
        $('#dpa_btn_publish').removeAttr('disabled');
        $("#dpa_btn_download").val("Download and Publish");
    } else {
        $("#dpa_publish_desc").prop('disabled', 'disabled');
        $("#dpa_btn_publish").prop('disabled', 'disabled');
        $("#dpa_btn_download").val("Download");
    }
}

function update_event_filter() {
    if ($("#dpa_event_filter").is(":checked")) {
        $("#dpa_selected_disaster").removeAttr('disabled');
        $("#dpa_selected_incident").removeAttr('disabled');
        $("#dpa_selected_event").removeAttr('disabled');
        update_incident_list();
    } else {
        $("#dpa_selected_disaster").prop("disabled", "disabled");
        $("#dpa_selected_incident").prop("disabled", "disabled");
        $("#dpa_selected_event").prop("disabled", "disabled");
    }
}

function update_incident_list() {
    var disaster_id = $("#dpa_selected_disaster").val();
    $('#dpa_selected_incident').children().remove().end().append('<option selected value="-1">N/A</option>');
    $('#dpa_selected_event').children().remove().end().append('<option selected value="-1">N/A</option>');

    for (var key in event_list) {
        if (event_list.hasOwnProperty(key)) {
            //alert(key + " -> " + event_list[key][1]);
            if (disaster_id === event_list[key][1]) {
                $('#dpa_selected_incident').append($('<option>', {
                    value: key,
                    text: event_list[key][0]
                }));
            }
        }
    }
}

function update_event_list() {
    var disaster_id = $("#dpa_selected_incident").val();
    $('#dpa_selected_event').children().remove().end().append('<option selected value="-1">N/A</option>');

    for (var key in event_list) {
        if (event_list.hasOwnProperty(key)) {
            //alert(key + " -> " + event_list[key][1]);
            if (disaster_id === event_list[key][1]) {
                $('#dpa_selected_event').append($('<option>', {
                    value: key,
                    text: event_list[key][0]
                }));
            }
        }
    }
}

function close_dialog() {
    $(dialog_id).hide();
    $('#tbl_dpa_status').find("input, select, button, textarea").prop("disabled", false);
}

function loadError() {
    clearInterval(refreshIntervalId);
    $('#dpa_download_form').find("input, select, button, textarea").prop("disabled", false);
    update_download_form_inputs();
    $('.required_modules').attr('disabled', 'disabled');
    $(dialog_id).html('<h5>Error! Something went wrong. Please try again later.</h5><div style="padding: 20px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
}

function loadComplete(checksum) {
    clearInterval(refreshIntervalId);
    $('#dpa_download_form').find("input, select, button, textarea").prop("disabled", false);
    update_download_form_inputs();
    $('.required_modules').attr('disabled', 'disabled');
    $(dialog_id).html('<h5>OK! Download has started. After the file is downloaded extract the zip archive and launch vesuvius.exe</h5>' +
            '<div style="padding: 5px 0;">MD5 File Checksum: ' + checksum + '</div>' +
            '<div style="padding: 10px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
}

function load_publish_Complete(checksum, publish_status) {
    clearInterval(refreshIntervalId);
    $('#dpa_download_form').find("input, select, button, textarea").prop("disabled", false);
    update_download_form_inputs();
    $('.required_modules').attr('disabled', 'disabled');

    if (publish_status === true) {
        $(dialog_id).html('<h5>OK! Download has started. After the file is downloaded extract the zip archive and launch vesuvius.exe</h5>' +
                '<div style="padding: 0;">MD5 File Checksum: ' + checksum + '</div>' +
                '<hr><div style="padding: 0;">File successfully published.</div>' +
                '<div style="padding: 8px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
    } else {
        $(dialog_id).html('<h5>OK! Download has started. After the file is downloaded extract the zip archive and launch vesuvius.exe</h5>' +
                '<div style="padding: 0;">MD5 File Checksum: ' + checksum + '</div>' +
                '<div style="padding: 0;">Error! Failed to publish the file.</div>' +
                '<div style="padding: 8px 0;"><input type="button" value="OK" class="styleTehButton" onclick="$(dialog_id).hide();" /></div>');
    }

}

function getUrl() {
    var form = $('#dpa_download_form');
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

    var os = $("#dpa_target_os").val();
    params += "&dpa_target_os=" + os;

    if ($("#dpa_event_filter").is(":checked")) {
        params += "&dpa_event_filter";
        params += "&disaster=" + $("#dpa_selected_disaster").val();
        params += "&incident=" + $("#dpa_selected_incident").val();
        params += "&event=" + $("#dpa_selected_event").val();
    }
    if ($("#dpa_image_filter").is(":checked")) {
        params += "&dpa_image_filter";
    }
    if ($("#dpa_enable_publish").is(":checked")) {
        params += "&enable_publish";
        params += "&dpa_publish_desc=" + $("#dpa_publish_desc").val();
    }
    params += "&nonce=" + nonce_str;
    return base_url + params;
}

function show_dialog() {
    //Get the window height and width
    var winH = $(window).height();
    var winW = $(window).width();

    //Set the popup window to center
    $(dialog_id).css('top', winH / 2 - $(dialog_id).height() / 2);
    $(dialog_id).css('left', winW / 2 - $(dialog_id).width() / 2);

    //transition effect
    $(dialog_id).fadeIn(200);
}

function show_wizard() {
    //Get the window height and width
    var winH = $(window).height();
    var winW = $(window).width();

    //Set the popup window to center
    $(wizard_id).css('top', winH / 2 - $(wizard_id).height() / 2);
    $(wizard_id).css('left', winW / 2 - $(wizard_id).width() / 2);

    //transition effect
    $(wizard_id).fadeIn(200);
}



function make_nonce() {
    var text = "";
    var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (var i = 0; i < 20; i++)
        text += possible.charAt(Math.floor(Math.random() * possible.length));

    return text;
}

function getCookie(c_name)
{
    var c_value = document.cookie;
    var c_start = c_value.indexOf(" " + c_name + "=");
    if (c_start === -1)
    {
        c_start = c_value.indexOf(c_name + "=");
    }
    if (c_start === -1)
    {
        c_value = null;
    }
    else
    {
        c_start = c_value.indexOf("=", c_start) + 1;
        var c_end = c_value.indexOf(";", c_start);
        if (c_end === -1)
        {
            c_end = c_value.length;
        }
        c_value = unescape(c_value.substring(c_start, c_end));
    }
    return c_value;
}