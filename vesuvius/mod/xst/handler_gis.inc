<?
/**
 * @name         Extensible Streaming
 * @version      1.0
 * @package      xst
 * @author       Ishan Liyanage <ishanul@gmail.com>
 * @author       Richard Smith <s0459387@sms.ed.ac.uk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


/**
* Returns a list of all feature classes in a layer
*
* Used to narrow a drop down box of all feature classes
* when layer options are available.
*
* @global <type> $global
* @global <type> $conf
*/
function _shn_gis_form_select_layer_callback() {
	global $global;
	global $conf;
	if($conf['gis']) {
		require_once $global['approot']."/inc/lib_gis/gis_fns.inc";

		if(isset($_GET["layer"])){
			$layer = mysql_real_escape_string($_GET["layer"]);
			$all   = mysql_real_escape_string($_GET["all"]);
			// Find feature classes in system
			if('all' == $layer){
				$f_classes = shn_gis_get_feature_class_all();
			} else {
				$f_classes = shn_gis_get_feature_classes_layer($layer, 2);
			}
			if($all == 'true'){
				$options_c = array('all' => 'All');
			} else {
				$options_c = array();
			}
			foreach($f_classes as $f_class){
				$options_c[$f_class['c_uuid']] = $f_class['c_name'];
			}
			shn_form_select($options_c, "Feature Class", "c_uuid", $select_opts = "", $extra_opts = null);
		}
	}
}



function _shn_gis_form_gis_popup_new_callback() {
	global $global;
	global $conf;
	require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

	if($conf['gis']){

		$center_lat = mysql_real_escape_string($_GET["center_lat"]);
		$center_lon = mysql_real_escape_string($_GET["center_lon"]);
		$wkt        = mysql_real_escape_string($_GET["wkt"]);
		$coords     = $center_lon . ',' . $center_lat . ',' . '0,wkt{' . $wkt . '}';

		$keys = array(
			'f_class'         => $conf['gis_feature_type_default'],
			'f_type'          => mysql_real_escape_string($_GET["type"]),
			'f_coords'        => $coords,
			'f_name'          => mysql_real_escape_string($_GET["name"]),
			'f_description'   => mysql_real_escape_string($_GET["desc"]),
			'f_author'        => mysql_real_escape_string($_GET["auth"]),
			'f_url'           => mysql_real_escape_string($_GET["url"]),
			'f_address'       => mysql_real_escape_string($_GET["add"]),
			'f_event_date'    => mysql_real_escape_string($_GET["date"]),
		);
		$uuid = shn_gis_create_feature($keys);
		$class = shn_gis_get_feature_class_uuid($keys['f_class']);
		if(!($uuid === false  || $uuid == '')) {
			echo $uuid . '<uuid />' . $class['c_icon'] . '<icon />';
			$_GET["id"] = $uuid;
			_shn_gis_form_gis_popup_refresh_callback();
		} else {
			echo 'fail';
		}
	}
}



/**
*
*
* @global <type> $global
* @global <type> $conf
*/
function _shn_gis_form_gis_popup_edit_position_callback() {
	global $global;
	global $conf;
	require_once $global['approot']."/inc/lib_gis/gis_fns.inc";

	if($conf['gis']){
		if(isset($_GET["id"])){
			$center_lat = mysql_real_escape_string($_GET["center_lat"]);
			$center_lon = mysql_real_escape_string($_GET["center_lon"]);
			$wkt        = mysql_real_escape_string($_GET["wkt"]);
			$coords     = $center_lon . ',' . $center_lat . ',' . '0,wkt{' . $wkt . '}';
			$keys_ = array('f_coords' => $coords, );
			shn_gis_modify_feature(mysql_real_escape_string($_GET["id"]), $keys_);
			_shn_gis_form_gis_popup_refresh_callback();
		}
	}
}



/**
* Used to return hmtml for an edit box popup
*
* @global <type> $global
* @global <type> $conf
*/
function _shn_gis_form_gis_popup_edit_callback() {
	global $global;
	global $conf;
	require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";

	if($conf['gis']){
		if(isset($_GET["id"])){
			$keys_ = array(
			'f_uuid'          => '1',
			'f_class'         => '1',
			'f_type'          => '1',
			'f_projection'    => '1',
			'f_coords'        => '1',
			'f_name'          => '1',
			'f_description'   => '1',
			'f_author'        => '1',
			'f_url'           => '1',
			'f_address'       => '1',
			'f_event_date'    => '1',
			);
			$features = shn_gis_get_features_uuid(mysql_real_escape_string($_GET["id"]), $keys_);
			//$return = $return . '<popuphtml>' . shn_gis_form_popupHTML_edit($features[0]) . '</popuphtml>';
			$return = shn_gis_form_popupHTML_edit($features[0]);
			echo $return;
		}
	}
}



function _shn_gis_form_gis_popup_edit_ok_callback() {
	global $global;
	global $conf;
	require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";
	if($conf['gis']){
		if(isset($_GET["id"])){
			$keys_ = array(
			'f_name'          => mysql_real_escape_string($_GET["name"]),
			'f_description'   => mysql_real_escape_string($_GET["desc"]),
			'f_author'        => mysql_real_escape_string($_GET["auth"]),
			'f_url'           => mysql_real_escape_string($_GET["url"]),
			'f_address'       => mysql_real_escape_string($_GET["add"]),
			'f_event_date'    => mysql_real_escape_string($_GET["date"]),
			);
			shn_gis_modify_feature(mysql_real_escape_string($_GET["id"]), $keys_);
			_shn_gis_form_gis_popup_refresh_callback();
		}
	}
}



function _shn_gis_form_gis_popup_delete_callback() {
	global $global;
	global $conf;
	require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";

	if($conf['gis']){
		if(isset($_GET["id"])){
			$keys_ = array(
			'f_uuid'          => '1',
			'f_class'         => '1',
			'f_type'          => '1',
			'f_projection'    => '1',
			'f_coords'        => '1',
			'f_name'          => '1',
			'f_description'   => '1',
			'f_author'        => '1',
			'f_url'           => '1',
			'f_address'       => '1',
			'f_event_date'    => '1',
			'f_url_view'      => '1',
			'f_url_edit'      => '1'
			);
			$ok =  shn_gis_remove_feature( mysql_real_escape_string($_GET["id"]) );
			if($ok){
				echo '<delete />';
			} else{
				_shn_gis_form_gis_popup_refresh_callback();
			}
		}
	}
}



function _shn_gis_form_gis_popup_refresh_callback() {
	global $global;
	global $conf;
	require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";

	if($conf['gis']){
		if(isset($_GET["id"])){
			$keys_ = array('all'  => '1');
			$features = shn_gis_get_features_uuid( mysql_real_escape_string($_GET["id"]), $keys_);
			$return = shn_gis_form_popupHTML_view($features[0]);
			echo $return;
		}
	}
}

