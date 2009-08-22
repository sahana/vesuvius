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


class Msg_CapResource
{
	private $resourceDesc;
    private $mimeType;
    private $size;
    private $uri;
    private $derefUri;
    private $digest;
    
    function isValid()
    {
    	    //add validation code
        return true;
    }
    
    /**
     * Set methods
     */
    function setResourceDesc($resourceDesc)
    {
        if(isset($resourceDesc) && $resourceDesc != '')
        {
            $this->resourceDesc = $resourceDesc;
        }
        else
        {
        	    add_error(_t("resourceDesc is a required value"));
        }
    }
    
    function setMimeType($mimeType)
    {
        $this->mimeType = $mimeType;
    }
    
    function setSize($size)
    {
        if(is_numeric($size))
        {
            $this->size = $size;
        }
        else
        {
            add_error(_t("The Size has to be a numeric value"));
        }
    }
    
  
    function setUri($uri)
    {
        $this->uri = $uri;
    }
    
    function setDerefUri($derefUri)
    {
        $this->derefUri = $derefUri;
    }
    
    function setDigest($digest = null)
    {
        if(isset($digest) && $digest != null)
        {
            $this->digest = $digest;
        }
        elseif (isset($this->derefUri) && $this->derefUri != '')
        {
        	    $this->digest = sha1($this->derefUri);
        }
        elseif (isset($this->uri) && $this->uri != '')
        {
        	    //$this->digest = sha1_file($this->uri);
        }
    }
    
    /**
     * Get methods
     */
    function getResourceDesc()
    {
        return $this->resourceDesc;
    }
    
    function getMimeType()
    {
        return $this->mimeType;
    }
    
    function getSize()
    {
        return $this->size;
    }
    
    function getUri()
    {
        return $this->uri;
    }
    
    function getDerefUri()
    {
        return $this->derefUri;
    }
    
    function getDigest()
    {
        return $this->digest;
    }
    
}


