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

	
class Msg_CapInfo
{
    private $language;
    private $category;
    private $event;
    private $responseType;
    private $urgency;
    private $severity;
    private $certainty;
    private $audience;
    private $eventCode;
    private $effective;
    private $onset;
    private $expires;
    private $sendername;
    private $headline;
    private $description;
    private $instruction;
    private $web;
    private $contact;
    private $parameter;
    private $resource;
    private $area;
    
    function isValid()
    {
            //add validation code
        return true;
    }
    
    function addCategory($category)
    {
    	    if(isset($category) && $category != '')
        {
        	    $this->category[] = $category;
        }
    }
    
    function addResponseType($responseType)
    {
    	    if(isset($responseType) && $responseType != '')
        {
        	    $this->responseType[] = $responseType;
        }
    }
    
    function addEventCode($valueName, $value)
    {
    	    $ec['valueName'] = $valueName;
        $ec['value'] = $value;
        $this->eventCode[] = $ec;
    }
    
    function addParameter($valueName, $value)
    {
        $param['valueName'] = $valueName;
        $param['value'] = $value;
        $this->parameter[] = $param;
    }

    function addResource($resource)
    {
	    if($resource->isValid())
            $this->resource[] = $resource;
    }
    
    function delResource($resource_index)
    {
        $res = $this->getResource();
        
        for ($i = 0; $i < count ($res); $i++)
        {
            if ($i != $resource_index)
               $tmp_res[] = $res[$i];
        }
        
        $this->setResource($tmp_res);
        
        return true;
    }
    
    function addArea($area)
    {
	    if($area->isValid())
            $this->area[] = $area;
    }
    
    function delArea($area_index)
    {
        $ar = $this->getArea();

        for ($i = 0; $i < count ($ar); $i++)
        {
            if ($i != $area_index)
               $tmp_ar[] = $ar[$i];
        }
        
        $this->setArea($tmp_ar);
        
        return true;
    }
    
    /**
     * Setter functions
     */       
    function setLanguage($language)
    {
        if(isset($language) && $language != '')
        {
            $this->language = $language;
        }
        else
        {
        	    $this->language = 'en-US';
        }
    }
    
    function setCategory($category)
    {
        $this->category = $category;
    }
    
    function setEvent($event)
    {
        if(isset($event) && $event != '')
        {
            $this->event = $event;
        }
        else
        {
        	    add_error(_t("The subject event of the alert message is required"));        	
        }
    }
    
    function setResponseType($responseType)
    {
        $this->responseType = $responseType;
    }
    
    function setUrgency($urgency)
    {
        if(isset($urgency) && $urgency != '')
        {
        	    $this->urgency = $urgency;
        }
        else
        {
        	    add_error(_t("urgency is a required value"));
        }
    }
    
    function setSeverity($severity)
    {
        if(isset($severity) && $severity != '')
        {
            $this->severity = $severity;
        }
        else
        {
            add_error(_t("severity is a required value"));
        }
    }

    function setCertainty($certainty)
    {
        if(isset($certainty) && $certainty != '')
        {
        	    $this->certainty = $certainty;
        }
        else
        {
        	    add_error(_t("certainty is a required value"));
        }
    }
    
    function setAudience($audience)
    {
        $this->audience = $audience;
    }
    
    function setEventCode($eventCode)
    {
        $this->eventCode = $eventCode;
    }
    
    function setEffective($effective = null, $sent = null)
    {
        if (isset($effective) && $effective != '')
        {
            $this->effective = $effective;
        }
        elseif(isset($sent) && $sent != '')
        {
        	    $this->effective = $sent;
        }
    }
    
    function setOnset($onset)
    {
        $this->onset = $onset;
    }
    
    function setExpires($expires)
    {
        $this->expires = $expires;
    }
    
    function setSendername($sendername)
    {
        $this->sendername = $sendername;
    }
    
    function setHeadline($headline)
    {
        $this->headline = $headline;
    }
    
    function setDescription($description)
    {
        $this->description = $description;
    }
    
    function setInstruction($instruction)
    {
        $this->instruction = $instruction;
    }
    
    function setWeb($web)
    {
        $this->web = $web;
    }
    
    function setContact($contact)
    {
        $this->contact = $contact;
    }
    
    function setParameter($parameter)
    {
        $this->parameter = $parameter;
    }
    
    function setResource($resource)
    {
        $this->resource = $resource;
    }
    
    function setArea($area)
    {
        $this->area = $area;
    }
    
    /**
     * Getter functions
     */
    function getLanguage()
    {
        return $this->language;
    }
    
    function getCategory()
    {
        //return $this->category;
        $categories = $this->category;
        if (is_array($categories))
        {
            foreach ($categories as $category)
                $cat_str .= $category . ',';
        }
            
        return $cat_str;
    }
    
    function getEvent()
    {
        return $this->event;
    }
    
    function getResponseType()
    {
        return $this->responseType;
    }
    
    function getUrgency()
    {
        return $this->urgency;
    }
    
    function getSeverity()
    {
        return $this->severity;
    }
    
    function getCertainty()
    {
        return $this->certainty;
    }
    
    function getAudience()
    {
        return $this->audience;
    }
    
    function getEventCode()
    {
        return $this->eventCode;
    }
    
    function getEffective()
    {
        return $this->effective;
    }
    
    function getOnset()
    {
        return $this->onset;
    }
    
    function getExpires()
    {
        return $this->expires;
    }
    
    function getSendername()
    {
        return $this->sendername;
    }
    
    function getHeadline()
    {
        return $this->headline;
    }
    
    function getDescription()
    {
        return $this->description;
    }
    
    function getInstruction()
    {
        return $this->instruction;
    }
    
    function getWeb()
    {
        return $this->web;
    }
    
    function getContact()
    {
        return $this->contact;
    }
    
    function getParameter()
    {
        return $this->parameter;
    }
    
    function getResource()
    {
        return $this->resource;
    }
    
    function getArea()
    {
        return $this->area;
    }

}


