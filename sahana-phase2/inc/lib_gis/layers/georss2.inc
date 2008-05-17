<?php

/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright  	Lanka Software Foundation - http://www.opensource.lk
* @package    	Sahana - http://sahana.lk/
* @library      GIS
* @version     	$Id: georss2.inc,v 1.11 2008-05-17 16:03:23 mifanc Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
* 
* @todo: handle delete and enable coming from table chkbxs
* @todo: add a conf value for feed enabling
* @todo:too cluttered: shove the add section somewher else!!
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class georss2 implements layer{

	
    function print_form()
    {
        global $conf;
        shn_form_fsopen(_t('GeoRSS2'));
        $this->georss_enable();
        $this->show_georss_feeds();
        $this->add_georss_feed();
    	shn_form_fsclose();
    	
    }
    function georss_enable()
    {
    	global $conf;
    	shn_form_fsopen(_t('INFO'));
        echo _t("<p>Sahana can make use of Feeds from servers using the <a href='http://en.wikipedia.org/wiki/GeoRSS' target=_blank>GeoRSS</a> standard </p>");
        echo _t("<p>Enable GeoRSS Layers by selecting the checkbox option below.</p>");
        echo _t("<p><b>NB This version is UNDER DEVELOPMENT. Use GeoRSS instead.</b></p>");
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_georss_enable']){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable GeoRSS layers'),'georss_enable',$checked,array('value'=>1));
        shn_form_fsclose();
    }
    
    function add_georss_feed()
    {
    	global $conf;
        
  
        if ($conf['gis_ol_georss_enable']){
            if($_POST['gis_ol_georss'] && is_numeric($_POST['gis_ol_georss']))
            	$georss_layers = $_POST['gis_ol_georss'];
            else
            	$georss_layers = 0;
            	
            //Hack to stop number of layers automagically appearing in below text box for layer numbers, regardless of value set
            //I guess this is part of how the form-handler works - setting POST back to original in next few lines
            $_POST['gis_ol_georss']=0;
            
            shn_form_fsopen(_t('Add New Feed'));
            shn_form_fsopen(_t('NUMBER'));
            shn_form_text(_t('Number of GeoRSS layers to add'),'gis_ol_georss','size=2 maxlength=2');
            
            //Part of the plot - this should retain the layer value for commiting
            //Should theoretically only have a value on the 2nd post
            //qed: No layers committed in frst pass where number of layers are set
            //Layer values only committed in 2nd pass where the below post is set -- saavy?
            shn_form_hidden(array('georss_layers'=>$georss_layers));
            shn_form_fsclose();
            
            //And here: setting things right... Using POST with original value hereafter
            $_POST['gis_ol_georss']=$georss_layers;
            
            $description_help=_t("Only displayed in GIS Catalogue (optional)");
            $name_help=_t("Name displayed in Layer-Switcher (mandatory)");
            $url_help=_t("Address of the GeoRSS service (mandatory)");
            $projection_help=_t("Coordinate system used to display the data, as defined by <a href=\"http://www.epsg.org\" target=_blank>European Petroleum Survey Group</a> (mandatory). If left blank, then EPSG:4326 is assumed as this is the default WGS84.");
            $visibility_help=_t("Whether the layer is visible by default");
            $enabled_help=_t("Whether the layer is selectable from the Map or not");
            
            //@todo: set layer number to display actual layer count in the system
            for ($i=0; $i<$georss_layers; $i++) {
                //Set counter to one after the current layer count
                $j=$i+1;
                shn_form_fsopen(_t('LAYER '.$j));
                shn_form_text(_t('Description'),'gis_ol_georss_'.$j.'_description','size=60',array("help"=>$description_help));
                shn_form_text(_t('Name'),'gis_ol_georss_'.$j.'_name',null,array('req'=>true,"help"=>$name_help));
                shn_form_text(_t('URL'),'gis_ol_georss_'.$j.'_url','size=60',array('req'=>true,"help"=>$url_help));
                $projection = "EPSG:4326";
                if (!null == $conf['gis_ol_georss_'.$j.'_projection']) {
                    $projection = $conf['gis_ol_georss_'.$j.'_projection'];
                }
                shn_form_text(_t('Projection'),'gis_ol_georss_'.$j.'_projection',null,array('req'=>true,'value'=>$projection,"help"=>$projection_help));
                $visibilities = array(_t('false'),_t('true'));
                $visibility_select = '0';
                if ('1'==$conf['gis_ol_georss_'.$j.'_visibility']) {
                    $visibility_select = '1';
                }
                shn_form_select($visibilities,_t('Visible'),'gis_ol_georss_'.$j.'_visibility',null,array('value'=>$visibility_select,"help"=>$visibility_help));
                $enableds = array(_t('false'),_t('true'));
                $enabled_select = '1';
                if ('0'==$conf['gis_ol_georss_'.$j.'_enabled']) {
                    $enabled_select = '0';
                }
                shn_form_select($enableds,_t('Enabled'),'gis_ol_georss_'.$j.'_enabled',null,array('value'=>$enabled_select,"help"=>$enabled_help));
                shn_form_fsclose();
            }
            shn_form_fsclose();
        }
        
    }

	/**
	 * Handle addition of new feeds only
	 * Set counter to last feed counter in DB
	 * Do not commit empty name OR URL feeds
	 */
    function commit_values()
    {
        $DEBUG = false;
        
        global $global;
        global $conf;
        $db = $global['db'];
        
        $this->commit_georss_feed_table(true);
        
        if($DEBUG)
        	print_r ($_POST); 
        	
        //Handle new feeds only
        //Retrieving this value from hidden value
        //Thus created on 2nd pass only
       	$layers_to_add = $_POST['georss_layers'];
       	//echo "layers:".$layers_to_add;

                         
        for ($i=1; $i<=$layers_to_add; $i++) {
            $j=$conf['gis_ol_georss'] + $i;
            
            $description = 'gis_ol_georss_'.$i.'_description';
            $description_db = 'gis_ol_georss_'.$j.'_description';
            $name = 'gis_ol_georss_'.$i.'_name';
            $name_db = 'gis_ol_georss_'.$j.'_name';
            $url = 'gis_ol_georss_'.$i.'_url';
            $url_db = 'gis_ol_georss_'.$j.'_url';
            $visibility = 'gis_ol_georss_'.$i.'_visibility';
            $visibility_db = 'gis_ol_georss_'.$j.'_visibility';
            $enabled = 'gis_ol_georss_'.$i.'_enabled';
            $enabled_db = 'gis_ol_georss_'.$j.'_enabled';
          
          if($_POST[$name] && $_POST[$url]){
            //description
            $query = "SELECT * FROM config WHERE confkey='$description_db' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST[$description]}' WHERE module_id = 'admin' AND confkey = '$description_db'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$description_db','{$_POST[$description]}')";
                $db->Execute($insert);
            }
            
            //name            
            if(!null==$_POST[$name]){
                $query = "SELECT * FROM config WHERE confkey='$name_db' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$name]}' WHERE module_id = 'admin' AND confkey = '$name_db'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$name_db','{$_POST[$name]}')";
                    $db->Execute($insert);
                }
            }
            
            //url           
            if(!null==$_POST[$url]){
                $query = "SELECT * FROM config WHERE confkey='$url_db' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$url]}' WHERE module_id = 'admin' AND confkey = '$url_db'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$url_db','{$_POST[$url]}')";
                    $db->Execute($insert);
                }
            }
            
            //visibility
            //In PHP 0 == NULL!            
            $query = "SELECT * FROM config WHERE confkey='$visibility_db' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST[$visibility]}' WHERE module_id = 'admin' AND confkey = '$visibility_db'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$visibility_db','{$_POST[$visibility]}')";
                $db->Execute($insert);
            }
            
            //enabled            
            $query = "SELECT * FROM config WHERE confkey='$enabled_db' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST[$enabled]}' WHERE module_id = 'admin' AND confkey = '$enabled_db'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$enabled_db','{$_POST[$enabled]}')";
                $db->Execute($insert);
            }
            
            
          }//Empty check of name & url
        }//End of loop
        
        
		

            // Checkboxes return nothing if unticked!
        // Overall GeoRSS enable
        
        if (null == $_POST['georss_enable']){
            $gis_georss_enable=0;
        } 
        else {
      		$gis_georss_enable=1;
        }
        if (!$gis_georss_enable == $conf['gis_ol_georss_enable']) {
            $query = "SELECT * FROM config WHERE confkey='gis_ol_georss' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$gis_georss_enable' WHERE module_id = 'admin' AND confkey = 'gis_ol_georss_enable'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_georss_enable','$gis_georss_enable')";
                $db->Execute($insert);
            }
        }
        
        //Add updated layers value - handle deleted layers too
        $total_layers = $conf['gis_ol_georss']+$layers_to_add;
		 $query = "SELECT * FROM config WHERE confkey='gis_ol_georss' AND module_id='admin'";
		    $res = $db->Execute($query);
		    if(!$res->EOF){
		        $q = "UPDATE config SET value = '{$total_layers}' WHERE module_id = 'admin' AND confkey = 'gis_ol_georss'";
		        $db->Execute($q);
		    }
		    else{
		        $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_georss','{$total_layers}')";
		        $db->Execute($insert);
		    }
    }
    
    /**
     * Commit options made in feeds table
     * @todo: call this BEFORE commiting new layers - things could screw up if not!
     */
    function commit_georss_feed_table($debug=false)
    {

    	
    	global $global;
        global $conf;
        $db = $global['db'];
        $layers_in_db = $conf['gis_ol_georss'];
        if($debug)
        	print_r ($_POST);
       	
       	//loop the loop
       	for($i=1;$i<=$layers_in_db;$i++){
       		
       		//Check delete first
       		if(!(null==$_POST['georss_delete_'.$i])){
       			//Delete this layer
       			//Store georss conf value endings
       			$value_array = array('description','name','url','visibility','enabled');
       			$value='gis_ol_georss_'.$i.'_description';
       			$delete = "delete from config where confkey='{$value}'";
       			
       			foreach ($value_array as $values){
       				$value = 'gis_ol_georss_'.$i.'_'.$values;
       				$delete = "delete from config where confkey='{$value}'";
       				$db->Execute($delete);
       				//@todo: Handle the number of layers in the system
       			}
       			
       			
       			//No point in further checks
       			continue;
       			
       		}
       	
       		
       		if(null==$_POST['georss_enable_'.$i])
       			$georss_enable_layer = 0;
       		else
       			$georss_enable_layer = 1;
       			
       		if(null==$_POST['georss_visible_'.$i])
       			$georss_visible_layer = 0;
       		else
       			$georss_visible_layer = 1;
       			

       		
       		
       	}
        
    }
    
    function show_georss_feeds()
    {
    	global $conf;
    	if ($conf['gis_ol_georss_enable']){
    	shn_form_fsopen(_t('Available GeoRSS Feeds'));
    	
    	if($conf['gis_ol_georss']){
?>
		<div id="result">
			
		  <table>
			<thead>
				<td><?php echo _t('Layer')?></td>
				<td><?php echo _t('Layer Name')?></td>
				<td><?php echo _t('Description')?></td>
				<td><?php echo _t('Enabled (for selection)')?></td>
				<td><?php echo _t('Visible (by default)')?></td>
				<td><?php echo _t('Delete')?></td>
			</thead>
			<tbody>
<?php

				$georss_layers_count = $conf['gis_ol_georss'];
				
				for($i=0;$i<$georss_layers_count;$i++){
					$check_enable =''; 
					$check_visible='';
					$j=$i+1;
					//Skip empty buggers
					/*
					if($conf['gis_ol_georss_'.$j.'_name']=='')
						continue;
					*/
					if($conf['gis_ol_georss_'.$j.'_enabled']=='1')
						$check_enable = 'checked';

					if($conf['gis_ol_georss_'.$j.'_visibility']=='1')
						$check_visible = 'checked';
?>
				<tr>
					<td><?php echo $j?></td>
					<td><?php echo $conf['gis_ol_georss_'.$j.'_name']; ?></td>
					<td><?php echo $conf['gis_ol_georss_'.$j.'_description']; ?></td>
					<td><?php shn_form_checkbox($conf['gis_ol_georss_'.$j.'_enabled'],'georss_enable_'.$j,$check_enable); ?></td>
					<td><?php shn_form_checkbox($conf['gis_ol_georss_'.$j.'_visibility'],'georss_visible_'.$j,$check_visible); ?></td>
					<td><?php shn_form_checkbox(null,'georss_delete_'.$j,null,array('value'=>0)); ?> </td>
				</tr>
<?php
				}
?>
			</tbody>
		  </table>
  
  
		</div>
<?php
    	}
    	else{
    		//No feeds to display
    		echo _t('No GeoRSS feeds to display in catalog');
    	}
    	shn_form_fsclose();
    	}
    }
    
}
 
?>
