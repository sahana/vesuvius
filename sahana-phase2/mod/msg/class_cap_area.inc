<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

class Msg_CapArea
{
    private $areaDesc;
    private $polygon;
    private $circle;
    private $geocode;
    private $altitude;
    private $ceiling;
    
    function isValid()
    {
        //add validation code
        return true;
    }
    
    function addGeocode($valueName, $value)
    {
        $gc['valueName'] = $valueName;
        $gc['value'] = $value;
        
        $this->geocode[] = $gc;
    }
    
    function addCircle($x, $y, $radius)
    {
        $circle = "$x,$y $radius";
        $this->circle[] = $circle;
    }
    
    function addPolygon($coord_arr)
    {
    	   
       $fc = split(',', $coord_arr[0]);
       $lc = split(',', $coord_arr[count($coord_arr)-1]);
       if($fc[0] == $lc[0] && $fc[1] == $lc[1])
       {
           foreach ($coord_arr as $coord)
           {
               $polygon .= $coord . ' ';
           }
           
           $this->polygon[] = $polygon;
       }
       else
       {
           add_error(_t("The first and last pairs of coordinates MUST be the " .
                "same."));
       }
    }
        
    /**
     * Set methods
     */
    function setAreaDesc($areaDesc)
    {
        if(isset($areaDesc) && $areaDesc != '')
        {
            $this->areaDesc = $areaDesc;
        }
        else
        {
        	    add_error(_t("areaDesc is a required value"));
        }
    }
    
    function setPolygon($polygon)
    {
        $this->polygon = $polygon;
    }
    
    function setCircle($circle)
    {
        $this->circle = $circle;
    }
    
    function setGeocode($geocode)
    {
        $this->geocode = $geocode;
    }
    
    function setAltitude($altitude)
    {
        $this->altitude = $altitude;
    }
    
    function setCeiling($ceiling)
    {
        if(isset($this->altitude))
        {
            $this->ceiling = $ceiling;
        }
        else
        {
        	   add_error(_t("Altitude has to be set before setting Ceiling"));
        }
    }
    
    /**
     * Get methods
     */
    function getAreaDesc()
    {
        return $this->areaDesc;
    }
    
    function getPolygon()
    {
        return $this->polygon;
    }
    
    function getCircle()
    {
        return $this->circle;
    }
    
    function getGeocode()
    {
        return $this->geocode;
    }
    
    function getAltitude()
    {
        return $this->altitude;
    }
    
    function getCeiling()
    {
        return $this->ceiling;
    }
    
}
