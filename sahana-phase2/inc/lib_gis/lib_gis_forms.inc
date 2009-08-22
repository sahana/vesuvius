<?php
/**
* Forms related to the GIS
*
* PHP version 5
*
* @package	Sahana - http://sahana.sourceforge.net
* @author       Richard Smith <s0459387@sms.ed.ac.uk>
* @version
* @library	GIS
* @copyright  	Lanka Software Foundation - http://www.opensource.lk
* @license    	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DISPLAY MAPS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function shn_gis_form_map_add_marker($name_of_map="Area Map",$name=null)
{
    
}

function shn_gis_form_map_add_marker_plus($name_of_map="Area Map",$nameOfPoint="",$button_submit_opts=null,$extra_opts=null)
{
    
}

function shn_gis_form_map_with_feature_uuids($uuids = array())
{
   shn_gis_form_map_with_features_and_uuids($uuids, array());
}

function shn_gis_form_map_with_features($features = array())
{
    shn_gis_form_map_with_features_and_uuids(array(), $features);
}

/**
 * Add map with markers with info
 * 
 * @global <type> $global
 * @global <type> $conf
 * @param <type> $uuids 2d array of info to be added
 * @param <type> $extra_features 2d array of info to be added
 */
function shn_gis_form_map_with_features_and_uuids($uuids = array(), $extra_features = array())
{
    // Includes.
    global $global;
    global $conf;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    require_once $global['approot'].'/inc/lib_gis/plugins/'. $conf['gis_dflt'] .'/handler_'. $conf['gis_dflt'] .'.inc';
    
    if($conf['gis']){ 
        
        // need to add areas first, then lines, then polygons... so that can click on markers!!!!
        $points = array();
        $lines = array();
        $polygons = array();
        
       // set values for db to return.
        $keys_ = array('all' => '1');
        
        // Add db features to extra features if provided.
        foreach($uuids as $uuid){
            $feature = shn_gis_get_features_uuid($uuid, $keys_);
            
            array_push($extra_features, $feature[0]);
        }
        // Show map with features.
        show_map_with_features($extra_features);
    } else{
       shn_gis_print_msg();
    }
}

function shn_gis_form_map_single_geometry($button_set = array('next' => true), $feature_class = null, $types = array('point' => true))
{
    global $global;
    global $conf;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    require_once $global['approot'].'/inc/lib_gis/plugins/openlayers/handler_openlayers.inc';
    
    shn_form_fsopen(_t("GPS Coordinates (Center)"));
    shn_form_text(_t("Northing / Latitude"),"gps_y",'size="60"');
    shn_form_text(_t("Easting / Longitude"),"gps_x",'size="60"');
    shn_form_submit_set($button_set);
    shn_form_fsclose();
    
    if($conf['gis']){ 
        shn_form_fsopen('Locate feature');
        shn_form_hidden(array('loc_type' => ''));
        shn_form_hidden(array('loc_x' => ''));
        shn_form_hidden(array('loc_y' => ''));
        shn_form_hidden(array('loc_wkt' => ''));
        
        if($feature_class != null){
            $class = shn_gis_get_feature_class_uuid($feature_class); 
        } else{
            $class = shn_gis_get_feature_class_uuid($conf['gis_feature_type_default']);
        }
        $icon_path = $class['c_icon'];
        if($class['c_icon'] == ''){
            $icon_path = $conf['gis_marker_folder'] . $conf['gis_marker'];
        }
        echo "<div class='message information'>";
        echo _t("You can move around and enlarge/reduce the size of the area you want using
    the scale on upper left corner of the map. By clicking on a map you can
    mark your location with a pointer..");
        echo "</div>";
        show_map_add_single_geometry($icon_path, $types);
        shn_form_fsclose();
    } else{
        shn_gis_print_msg();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAP POPUPS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Creates the HTML for the standard view in a mapping popup box
 * 
 * @global <type> $id
 * @param <type> $feature
 * @return <type>
 */
function shn_gis_form_popupHTML_view($feature)
{
    global $global;
    global $conf;
    global $shn_tabindex;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        
    // Generate vars for popup HTML content
        
    // Set Feature uuid
    if(isset($feature['f_uuid']) && $feature['f_uuid'] != ''){
        $feature_uuid = $feature['f_uuid'];
    } else{
        $feature_uuid = 'popup_' . $id++; // :(
    }
    // Set Feature Class
    if(isset($feature['f_class']) && $feature['f_class'] != ''){
        $feature_class = shn_gis_get_feature_class_uuid($feature['f_class']);
    } else{
        $feature_class = shn_gis_get_feature_class_uuid($conf['gis_feature_type_default']);
    }
    // Set name.
    if(isset($feature['f_name']) && $feature['f_name'] != ''){
        $name = $feature['f_name'];
    } else{
        $name = $feature_class['c_name'];
    }
    // Set Description
    if(isset($feature['f_description']) && $feature['f_description'] != ''){
        $description = $feature['f_description'];
    } else{
        $description = $feature_class['c_description'];
    }
    // Set Author
    if(isset($feature['f_author']) && $feature['f_author'] != ''){
        $author = $feature['f_author'];
    } else{
        $author = 'Anonymous';
    }
    // Set Address
    if(isset($feature['f_address']) && $feature['f_address'] != ''){
        $address = $feature['f_address'];
    } else{
        $address = false;
    }
    // Set Event Date
    if(isset($feature['f_event_date'])){
        $event_date = $feature['f_event_date'];
    } else{
        $event_date = 'Unknown';
    }
    // Set View URL
    if(isset($feature['f_url']) && $feature['f_url'] != ''){
        $url = $feature['f_url'];
    } else{
        $url = false;
    }
    // Set View URL
    if(isset($feature['f_url_view']) && $feature['f_url_view'] != ''){
        $url_view = $feature['f_url_view'];
    } else{
        $url_view = false;
    }
    // Set Edit URL
    if(isset($feature['f_url_edit']) && $feature['f_url_edit'] != ''){
        // if feature has an edit url
        $url_edit = $feature['f_url_edit'];
    } elseif(isset($feature['f_module_item']) && $feature['f_module_item'] != ''){
        // if is registered to a module but has no edit url, should not be editable.
        $url_edit = false;
        
    } elseif(!isset($feature['f_uuid']) || $feature['f_uuid'] == ''){
        // if there is no uuid to tie feature being edited too...
        $url_edit = false;
    } else{
        // if feature is not module related and has a uuid to tie changes to. (can edit)
        $url_edit = true;
    }
    // Set Delete URL
    if(isset($feature['f_url_delete']) && $feature['f_url_delete'] != ''){
        // if feature has a delete url
        $url_del = $feature['f_url_delete'];
    } elseif(isset($feature['f_module_item']) && $feature['f_module_item'] != ''){
        // if is registered to a module but has no del url, should not be deletable.
        $url_del = false;
    } elseif(!isset($feature['f_uuid']) || $feature['f_uuid'] == ''){
        // if there is no uuid to tie feature being deleted too...
        $url_del = false;
    } else{
        // if feature is not module related and has a uuid to tie changes to. (can del)
        $url_del = true;
    }
    
    // Popup HTML
    $html = '';
    $html = $html . "<div class='gis_openlayers_popupbox' id='$feature_uuid'>";
    // Header (name, link, date, author, address)
    $html = $html . "   <div class='gis_openlayers_popupbox_header'>";
    $html = $html . "     <div class='gis_openlayers_popupbox_header_r'>";
    $html = $html . "       <div class='gis_openlayers_popupbox_author'><label for='gis_popup_author' >" . _t("Author:") . "</label> $author</div>";
    $html = $html . "       <div class='gis_openlayers_popupbox_date'><label for='gis_popup_date' >" . _t("Date:") . "</label> $event_date</div>";;
    $html = $html . "     </div>";
    $html = $html . "     <div class='gis_openlayers_popupbox_header_l'>";
    $html = $html . "       <div class='gis_openlayers_popupbox_name'><span> $name</span> ({$feature_class['c_name']})";
    if(!($url === false)){
        $html = $html . "      <a href='$url' target='_blank'><div class='gis_openlayers_popupbox_link' style='width: 17px; height: 17px;'></div></a>";
    }
    $html = $html . "       </div>";
    $html = $html . "     </div>";
    if(!($address === false)){
        $html = $html . "      <div class='gis_openlayers_popupbox_address'><b>" . _t("Address:") . "</b> $address</div>";
    }
    $html = $html . "   </div>";
    // Body (desc, img, vid)
    $html = $html . "   <div class='gis_openlayers_popupbox_body'>";
    $html = $html . "     <span class='gis_openlayers_popupbox_text'>$description</span>";
    //$html = $html .  "    <span class='gis_openlayers_popupbox_img'><img src=$image width=100 height=100></span>";    
    //$html = $html .  "    <span class='gis_openlayers_popupbox_vid'></span>";    
    $html = $html . "  </div>";
    // Footer (edit, view)
    $html = $html . "  <div class='gis_openlayers_popupbox_footer'>";
    //Options will want to display these based on ACL privileges (also make sure resulting actions are ACLed)
    
    if($url_del === true){
        $html = $html . "      <span><a onclick='shn_gis_popup_delete(&#39$feature_uuid&#39)' alt='" . _t('delete') . "'><div class='gis_openlayers_popupbox_delete' style='width: 17px; height: 17px;'></div><span>" . _t('delete') . "</span></a></span>";   
    } elseif(!($url_del === false)){
        $html = $html . "      <span><a href='$url_del' target='_blank' alt='" . _t('delete') . "'><div class='gis_openlayers_popupbox_delete' style='width: 17px; height: 17px;'></div><span>" . _t('delete') . "</span></a></span>";   
    } else {
        $html = $html . "      <span><a onclick='shn_gis_popup_unable()' alt='" . _t('delete') . "'><div class='gis_openlayers_popupbox_delete' style='width: 17px; height: 17px;'></div><span>" . _t('delete') . "</span></a></span>";   
    }
    
   if($url_edit === true){
        $html = $html . "      <span><a onclick='shn_gis_popup_edit_details(&#39$feature_uuid&#39)' alt='" . _t('edit') . "'><div class='gis_openlayers_popupbox_edit' style='width: 17px; height: 17px;'></div><span>" . _t('edit') . "</span></a></span>";
    } elseif(!($url_edit === false)){
        $html = $html . "      <span><a href='$url_edit' target='_blank' alt='" . _t('edit') . "'><div class='gis_openlayers_popupbox_edit' style='width: 17px; height: 17px;'></div><span>" . _t("edit") . "</span></a></span> ";
    } else {
        $html = $html . "      <span><a onclick='shn_gis_popup_unable()' alt='" . _t('edit') . "'><div class='gis_openlayers_popupbox_edit' style='width: 17px; height: 17px;'></div><span>" . _t("edit") . "</span></a></span> ";   
    }
    
    if(!($url_view === false)){
        $html = $html . "      <span><a href='$url_view' target='_blank' alt='" . _t('view') . "'><div class='gis_openlayers_popupbox_view' style='width: 17px; height: 17px;'></div><span>" . _t("view") . "</span></a></span>";
    }
    
    $html = $html . "      <span class='gis_openlayers_popupbox_refreshs'><a onclick='shn_gis_popup_refresh(&#39$feature_uuid&#39)' alt='" . _t('refresh') . "'><div class='gis_openlayers_popupbox_refresh' style='width: 17px; height: 17px;'></div><span>" . _t("refresh") . "</span></a></span>";
    $html = $html . "  </div>";
    $html = $html . "  <div style='clear: both;'></div>";
    $html = $html . "</div>";
        
    return $html;
}
    
/**
 * Creates the HTML for editing a feature in a mapping popup box
 * (This should only be used if the feature was created in SM and not in
 * another module. In cases when the feature was created in another module
 * the edit option should link to said module).
 * 
 * @global <type> $shn_tabindex
 * @global <type> $id
 * @param <type> $feature
 * @return <type>
 */
function shn_gis_form_popupHTML_edit($feature)
{
    global $global;
    global $conf;
    global $id;
    global $shn_tabindex;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    // Fixes bug
    $shn_tabindex++;
    
    // Generate vars for popup HTML content
        
    // Set Feature uuid
    if(isset($feature['f_uuid'])){
        $feature_uuid = $feature['f_uuid'];
    } else {
        $feature_uuid = 'popup_' . $id++; // :(
    }
        
    // Set Feature Class
    if(isset($feature['f_class'])){
        $feature_class = shn_gis_get_feature_class_uuid($feature['f_class']);
    } else {
        $feature_class = shn_gis_get_feature_class_uuid($conf['gis_feature_type_default']);
    }
    // Set name.
    if(isset($feature['f_name'])){
        $name = $feature['f_name'];
    } else {
        $name = '';
    }
    // Set Description
    if(isset($feature['f_description'])){
        $description = $feature['f_description'];
    } else {
        $description = $feature_class['c_description'];
    }
    // Set Author
    if(isset($feature['f_author'])){
        $author = $feature['f_author'];
    } else {
        $author = 'Anonymous';
    }
    // Set Address
    if(isset($feature['f_address']) && $feature['f_address'] != ''){
        $address = $feature['f_address'];
    } else {
        $address = '';
    }
    // Set Event Date
    if(isset($feature['f_event_date'])){
        $event_date = $feature['f_event_date'];
    } else {
        $event_date = '';
    }
    // Set View URL
    if(isset($feature['f_url']) && $feature['f_url'] != ''){
        $url = $feature['f_url'];
    } else {
        $url = '';
    }
        
    // Popup
    $html = '';
    $html = $html . "<div class='gis_openlayers_popupbox' id='$feature_uuid'>";
    $html = $html . "<form method='post' action='index.php?mod=admin&amp;act=gis_database_classes_edit' id='form0' name='form0'><input name='seq' value='seq_3' type='hidden' />";
        
    // Header (name, link, date, author, address)
    $html = $html . "   <div class='gis_openlayers_popupbox_header'>";
    $html = $html . "     <div class='gis_openlayers_popupbox_header_r'>";
    $html = $html . "       <div class='gis_openlayers_popupbox_author'><label for='gis_popup_author' >" . _t("Author:") . "</label> <input type='text' name='gis_popup_author' id='{$feature_uuid}_popup_auth' value='$author' size='15' maxlength='60' tabindex=" . (($shn_tabindex++) + 2) . " /></div>";
    $html = $html . "       <div class='gis_openlayers_popupbox_date'><label for='gis_popup_date' >" . _t("Date:") . "</label> <input type='text' name='gis_popup_date' id='{$feature_uuid}_popup_edate' value='$event_date' size='15' tabindex=" . (($shn_tabindex++) + 2). " /></div>";
    $html = $html . "     </div>";
    $html = $html . "     <div class='gis_openlayers_popupbox_header_l'>";
    $html = $html . "       <div class='gis_openlayers_popupbox_name'><label for='gis_popup_name'>" . _t("Name:") . "</label> <span><input type='text' name='gis_popup_name' id='{$feature_uuid}_popup_name' value='$name' size='10' maxlength='60' tabindex=" . (($shn_tabindex++) - 2) . " /></span> ({$feature_class['c_name']})</div>";
    $html = $html . "       <div class='gis_openlayers_popupbox_url'><label for='gis_popup_name'>" . _t("Url:") . "</label> <input type='text' name='gis_popup_url' id='{$feature_uuid}_popup_url' value='$url' size='40' maxlength='100' tabindex=" . (($shn_tabindex++) - 2) . " /></div>";
    $html = $html . "     </div>";
    $html = $html . "      <div class='gis_openlayers_popupbox_address'><b>" . _t("Address:") . "</b> <input type='text' name='gis_popup_address' id='{$feature_uuid}_popup_add' value='$address' size='55' maxlength='200' tabindex=" . $shn_tabindex++ . " /></div>";
    $html = $html . "   </div>";  
        
    // Body (desc, img, vid)
    $html = $html . "   <div class='gis_openlayers_popupbox_body'>";
    //$html = $html .  "  Description, Image, Video, Layer???";
    $html = $html . "     <span class='gis_openlayers_popupbox_text'><textarea rows='5' cols='70' name='gis_popup_desc' id='{$feature_uuid}_popup_desc' tabindex=" . $shn_tabindex++ . " >$description</textarea></span>";
    //$html = $html .  "    <span class='gis_openlayers_popupbox_img'><img src=$image width=100 height=100></span>";    
    //$html = $html .  "    <span class='gis_openlayers_popupbox_vid'></span>";    
    $html = $html . "  </div>";
        
    // Footer (cancel, ok)
    $html = $html . "  <div class='gis_openlayers_popupbox_footer'>";
    $html = $html . "      <span><a onclick='shn_gis_popup_refresh(&#39$feature_uuid&#39)' alt='" . _t('cancel') . "'><div class='gis_openlayers_popupbox_edit_cancel' style='width: 17px; height: 17px;'></div><span>" . _t("cancel") . "</span></a></span>";
    $html = $html . "      <span><a onclick='shn_gis_popup_edit_details_ok(&#39$feature_uuid&#39)' alt='" . _t('ok') . "'><div class='gis_openlayers_popupbox_edit_ok' style='width: 17px; height: 17px;'></div><span>" . _t("ok") . "</span></a></span> ";
    $html = $html . "  </div>";
    $html = $html . "  <div style='clear: both;'></div>";
    $html = $html . "</form>";
    $html = $html . "</div>";
        
    return $html;  
}

function shn_gis_form_popupHTML_new()
{
    global $global;
    global $conf;
    global $id;
    global $shn_tabindex;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    // Fixes bug
    $shn_tabindex++;
                
    $feature_uuid = 'popup_' . $id++; // :(
    
    // Set Feature Class
    $feature_class = shn_gis_get_feature_class_uuid($conf['gis_feature_type_default']); 
    
    // Popup
    $html = '';
    $html = $html . "<div class='gis_openlayers_popupbox' id='$feature_uuid'>";
    $html = $html . "<form method='post' action='index.php?mod=admin&amp;act=gis_database_classes_edit' id='form0' name='form0'><input name='seq' value='seq_3' type='hidden' />";
        
    // Header (name, link, date, author, address)
    $html = $html . "   <div class='gis_openlayers_popupbox_header'>";
    $html = $html . "     <div class='gis_openlayers_popupbox_header_r'>";
    $html = $html . "       <div class='gis_openlayers_popupbox_author'><label for='gis_popup_author' >" . _t("Author:") . "</label> <input type='text' name='gis_popup_author' id='{$feature_uuid}_popup_auth' size='15' maxlength='60' tabindex=" . (($shn_tabindex++) + 2) . " /></div>";
    $html = $html . "       <div class='gis_openlayers_popupbox_date'><label for='gis_popup_date' >" . _t("Date:") . "</label> <input type='text' name='gis_popup_date' id='{$feature_uuid}_popup_edate' size='15' tabindex=" . (($shn_tabindex++) + 2). " /></div>";
    $html = $html . "     </div>";
    $html = $html . "     <div class='gis_openlayers_popupbox_header_l'>";
    $html = $html . "       <div class='gis_openlayers_popupbox_name'><label for='gis_popup_name'>" . _t("Name:") . "</label> <span><input type='text' name='gis_popup_name' id='{$feature_uuid}_popup_name' size='10' maxlength='60' tabindex=" . (($shn_tabindex++) - 2) . " /></span> ({$feature_class['c_name']})</div>";
    $html = $html . "       <div class='gis_openlayers_popupbox_url'><label for='gis_popup_name'>" . _t("Url:") . "</label> <input type='text' name='gis_popup_url' id='{$feature_uuid}_popup_url' size='40' maxlength='100' tabindex=" . (($shn_tabindex++) - 2) . " /></div>";
    $html = $html . "     </div>";
    $html = $html . "      <div class='gis_openlayers_popupbox_address'><b>" . _t("Address:") . "</b> <input type='text' name='gis_popup_address' id='{$feature_uuid}_popup_add' size='55' maxlength='200' tabindex=" . $shn_tabindex++ . " /></div>";
    $html = $html . "   </div>";  
        
    // Body (desc, img, vid)
    $html = $html . "   <div class='gis_openlayers_popupbox_body'>";
    //$html = $html .  "  Description, Image, Video, Layer???";
    $html = $html . "     <span class='gis_openlayers_popupbox_text'><textarea rows='5' cols='70' name='gis_popup_desc' id='{$feature_uuid}_popup_desc' tabindex=" . $shn_tabindex++ . " ></textarea></span>";
    //$html = $html .  "    <span class='gis_openlayers_popupbox_img'><img src=$image width=100 height=100></span>";    
    //$html = $html .  "    <span class='gis_openlayers_popupbox_vid'></span>";    
    $html = $html . "  </div>";
        
    // Footer (cancel, ok)
    $html = $html . "  <div class='gis_openlayers_popupbox_footer'>";
    $html = $html . "      <span><a onclick='shn_gis_popup_new_cancel(&#39$feature_uuid&#39)' alt='" . _t('cancel') . "'><div class='gis_openlayers_popupbox_edit_cancel' style='width: 17px; height: 17px;'></div><span>" . _t("cancel") . "</span></a></span>";
    $html = $html . "      <span><a onclick='shn_gis_popup_new_ok(&#39$feature_uuid&#39)' alt='" . _t('ok') . "'><div class='gis_openlayers_popupbox_edit_ok' style='width: 17px; height: 17px;'></div><span>" . _t("ok") . "</span></a></span> ";
    $html = $html . "  </div>";
    $html = $html . "  <div style='clear: both;'></div>";
    $html = $html . "</form>";
    $html = $html . "</div>";
        
    return $html;  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OTHER FORMS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Opens a form and produces a search feature box
 *
 * @global <type> $global
 * @global <type> $conf
 * @param <type> $action
 * @param <type> $form_opts
 */
function shn_gis_form_feature_search($act = '', $button_set, $form_opts = array('seq' => ''))
{
    global $global;
    global $conf;
    if($conf['gis']){
        $seq = $form_opts['seq'];
        
        echo '<h2>' . _t("Feature Search") . '</h2>';
        shn_form_fopen($act, null, null, array('req' => false));
        shn_form_fsopen(_t("Feature Details"));
        shn_gis_form_layer_to_feature_narrow();
        shn_form_text(_t("Name of Author"), "f_author", 'size="20"', array('req' => false));
        shn_form_date(_t("Date of Event (From)"), "f_event_date_from", array('req' => false));
        shn_form_date(_t("Date of Event (To)"), "f_event_date_to", array('req' => false));
        shn_form_text(_t("Name of Feature"), "f_name", 'size="20"', array('req' => false));
        shn_form_hidden(array('seq' => $seq));
        shn_form_fsclose();
        shn_form_submit_set($button_set);
        shn_form_fclose();

    } else {
        add_error(_("GIS Disabled"));
    }
}

/**
 * Displays a layers and feature class selection boxes.
 * The feature class dropdown changes depending on the layer selected.
 * Uses ajax.
 * 
 * @global <type> $global
 * @global <type> $conf
 * @param <type> $all
 */
function shn_gis_form_layer_to_feature_narrow($all = true)
{
    global $global;
    global $conf;
    if($conf['gis']){
        require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        _shn_gis_form_feature_search_ajax();
        // Find all layers in system
        $layers = shn_gis_get_layers_all();
        $options_l = array('all' => 'All');
        foreach($layers as $layer){
            $options_l[$layer['l_uuid']] = $layer['l_name'];
        }
        if($all){
            $allform = 'true';
        } else{
            $allform = 'false';
        }
        $select_opts = 'onchange="shn_gis_narrow_feature_classes(this.value, ' . $allform . ')"';
        shn_form_select($options_l, "Layer", "l_uuid", $select_opts, $extra_opts = null);
        // Find all feature classes in system
        $f_classes = shn_gis_get_feature_class_all();
        if($all){
            $options_c = array('all' => 'All');
        } else{
            $options_c = array();
        }
        foreach($f_classes as $f_class){
            $options_c[$f_class['c_uuid']] = $f_class['c_name'];
        }
        // div used by ajax to reload classes
        echo '<div id="gis_feature_class_select_form">';
        shn_form_select($options_c, "Feature Class", "c_uuid", $select_opts = "", $extra_opts = null);
        echo '</div>';
    } else {
        add_error(_t("Cannot search Layers or Feature Classes: GIS Disabled"));
    }
}

/**
 * fsopen form to display features 
 * $results_ are the results in the form array(array(f_name => camp, f_desc => a big camp)array(etc))
 * $keys_display_ are the fields to display (use f_name => '0' , f_coords => '0' etc)
 * $keys_display_  are the fields to make editable (use f_name => '1', etc) (not implemented yet)
 *
 * Boxes can be checked by setting a feature in results to $result['f_extended_data'] = 'selected_'
 *
 * @global <type> $global
 * @global <type> $conf
 * @param <type> $results_
 * @param <type> $keys_
 */
function shn_gis_form_feature_display($results_, $keys_display_ = array('f_name' => '1', 'f_desc' => '1', 'f_author' => '1', 'f_date' => '1', 'f_class' => '1', 'select' => '1'), $keys_edit_ = array())
{
    global $global;
    global $conf;
    global $shn_tabindex;
    if($conf['gis']){
        require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        shn_form_fsopen(_("Features"));

        echo '<br />';
        echo '<div id ="result">';
        echo '<table>';
        echo '<thead>';
        echo '<tr>';
        
        if(array_key_exists('f_uuid', $keys_display_)){
            echo '<td>' . _t('Feature Unique ID') . '</td>';
        }
        if(array_key_exists('f_module_item', $keys_display_)){
            echo '<td>' . _t('Module Unique ID') . '</td>';
        }
        if(array_key_exists('f_name', $keys_display_)){
            echo '<td>' . _t('Feature Name') . '</td>';
        }
        if(array_key_exists('f_desc', $keys_display_)){
            echo '<td>' . _t('Feature Description') . '</td>';
        }
        if(array_key_exists('f_url', $keys_display_)){
            echo '<td>' . _t('Feature Link') . '</td>';
        }
        if(array_key_exists('f_author', $keys_display_)){
            echo '<td>' . _t('Feature Author') . '</td>';
        }
        if(array_key_exists('f_event_date', $keys_display_)){
            echo '<td>' . _t('Event Date') . '</td>';
        }
        if(array_key_exists('f_address', $keys_display_)){
            echo '<td>' . _t('Feature Address') . '</td>';
        }
        if(array_key_exists('f_coords', $keys_display_)){
            echo '<td>' . _t('Event Coordinates') . '</td>';
        }
        if(array_key_exists('f_projection', $keys_display_)){
            echo '<td>' . _t('Projection Type') . '</td>';
        }
        if(array_key_exists('f_type', $keys_display_)){
            echo '<td>' . _t("Feature Type") . '</td>';
        }
        if(array_key_exists('f_class', $keys_display_)){
            echo '<td>' . _t("Feature Class") . '</td>';
        }
        if(array_key_exists('select', $keys_display_)){
            echo '<td>' . _t("Select") . '</td>';
        }
        echo '</tr>';
        echo '</thead>';
        $count = 0;
        foreach($results_ as $result){
            $count++;
            if(array_key_exists('f_uuid', $result)){
                $id = $result['f_uuid'];
            } else {
                $id = $count;
            } 
            $cls = shn_gis_get_feature_class_uuid($result['f_class']);
            echo '<tr>';
            if(array_key_exists('f_uuid', $keys_display_)){
            echo '<td>' . $result['f_uuid'] . '</td>';
            }
            if(array_key_exists('f_module_item', $keys_display_)){
                echo '<td>' . $result['f_module_item'] . '</td>';
            }
            if(array_key_exists('f_name', $keys_display_)){
                echo '<td>' . $result['f_name'] . '</td>';
            }
            if(array_key_exists('f_desc', $keys_display_)){
                echo '<td>' . $result['f_description'] . '</td>';
            }
            if(array_key_exists('f_url', $keys_display_)){
                echo '<td>' . $result['f_url'] . '</td>';
            }
            if(array_key_exists('f_author', $keys_display_)){
                echo '<td>' . $result['f_author'] . '</td>';
            }
            if(array_key_exists('f_event_date', $keys_display_)){
                echo '<td>' . $result['f_event_date'] . '</td>';
            }
            if(array_key_exists('f_address', $keys_display_)){
            echo '<td>' . $result['f_address'] . '</td>';
            }
            if(array_key_exists('f_coords', $keys_display_)){
                echo '<td>' . $result['f_coords'] . '</td>';
            }
            if(array_key_exists('f_projection', $keys_display_)){
                echo '<td>' . $result['f_projection'] . '</td>';
            }
            if(array_key_exists('f_type', $keys_display_)){
                echo '<td>' . $result['f_type'] . '</td>';
            }
            if(array_key_exists('f_class', $keys_display_)){
                echo '<td>' . $cls['c_name'] . '</td>';
            }
            if(array_key_exists('select', $keys_display_)){
                $checked = '';
                if('checked_' == $result['checked']){
                    $checked = 'checked = "checked"';
                }
                echo '<td><input type="checkbox" name="' . $count . '" id="' . $count . '" value="' . $id . '" ' . $checked . ' tabindex="' . ++$shn_tabindex . '" /></td>';
            }
            echo '</tr>';
        }
        echo '</table>';
        echo '</div>';
        echo '<br />';
        shn_form_hidden(array('count' => $count));
        shn_form_fsclose();
    }
}
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AJAX
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Ajax form for shn_gis_form_feature_search
 */
function _shn_gis_form_feature_search_ajax()
{
    $ajax_error = '"' . _t('Your browser does not support AJAX!') . '"';
?>
<script type="text/javascript">
    var xmlHttp

    function shn_gis_narrow_feature_classes(layer_, all_)
    {
        if(layer_.length == 0 ){
            return;
        }

        xmlHttp = GetXmlHttpObject();
        if (xmlHttp==null){
            alert (<?php echo $ajax_error ?>);
            return;
        }        
    
        var url='index.php?act=gis_search_layer&mod=xst&stream=text&layer=' + layer_ + '&all=' + all_;
        url = url+"&sid="+Math.random();
        xmlHttp.onreadystatechange = stateChanged;
        xmlHttp.open("GET", url, true);
        xmlHttp.send(null);
    }

    function stateChanged()
    {
        if (xmlHttp.readyState==4){
            document.getElementById("gis_feature_class_select_form").innerHTML = xmlHttp.responseText;
        }            
    }


    function GetXmlHttpObject(){
        var xmlHttp=null;
        try{
            // Firefox, Opera 8.0+, Safari
            xmlHttp=new XMLHttpRequest();
        }
        catch (e){
            // Internet Explorer
            try{
                xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
            }
            catch (e){
                xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
            }
        }
        return xmlHttp;
    }
</script>
<?php
}

