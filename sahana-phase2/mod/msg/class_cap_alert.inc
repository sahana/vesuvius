<?php
/**
* Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana
* @subpackage
* @tutorial
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;

include_once $global['approot']."inc/lib_table.inc";

require_once 'class_cap_info.inc';
require_once 'class_cap_resource.inc';
require_once 'class_cap_area.inc';

class Msg_CapAlert
{
    private $identifier;
    private $sender;
    private $sent;
    private $status;
    private $msgType;
    private $source;
    private $scope;
    private $restriction;
    private $address;
    private $code;
    private $note;
    private $references;
    private $incidents;
    private $info;

    function __construct($file=null)
    {
        if($file)
        {
            $this->getFromFile($file);
        }
    }

    function getFromFile($file)
    {
        $dom = new DomDocument();
        $dom->load($file);
        $xpath = new DomXPath($dom);
        //print_r( get_class_methods( $xpath ) );
        $xpath->registerNamespace("foo","urn:oasis:names:tc:emergency:cap:1.1");
        $nodes = $xpath->query("/foo:alert/foo:identifier", $dom->documentElement);
        //var_dump($nodes->item(0));
        $this->identifier = $nodes->item(0)->textContent;
        //var_dump($this->identifier);
        $nodes = $xpath->query("/foo:alert/foo:sender", $dom->documentElement);
        $this->sender = $nodes->item(0)->textContent;
        $nodes = $xpath->query("/foo:alert/foo:sent", $dom->documentElement);
        $this->sent = $nodes->item(0)->textContent;
        $nodes = $xpath->query("/foo:alert/foo:status", $dom->documentElement);
        $this->status = $nodes->item(0)->textContent;
        $nodes = $xpath->query("/foo:alert/foo:msgType", $dom->documentElement);
        $this->msgType = $nodes->item(0)->textContent;
        $nodes = $xpath->query("/foo:alert/foo:source", $dom->documentElement);
        $this->source = $nodes->item(0)->textContent;
        $nodes = $xpath->query("/foo:alert/foo:scope", $dom->documentElement);
        $this->scope = $nodes->item(0)->textContent;

        $nodes = $xpath->query("/foo:alert/foo:restriction", $dom->documentElement);
        $this->restriction = $nodes->item(0)->textContent;
        $nodes = $xpath->query("/foo:alert/foo:address", $dom->documentElement);
        $this->address = $nodes->item(0)->textContent;
        
        $nodes = $xpath->query("/foo:alert/foo:code", $dom->documentElement);
        foreach($nodes as $node)
            $this->addCode($nodes->item(0)->textContent);

        $nodes = $xpath->query("/foo:alert/foo:note", $dom->documentElement);
        $this->note = $nodes->item(0)->textContent;
        $nodes = $xpath->query("/foo:alert/foo:references", $dom->documentElement);
        $this->references = $nodes->item(0)->textContent;
        $nodes = $xpath->query("/foo:alert/foo:incidents", $dom->documentElement);
        $this->incidents = $nodes->item(0)->textContent;

        //Constructing info node
        $inf = new Msg_CapInfo();
        
        $nodes = $xpath->query("/foo:alert/foo:info/foo:language", $dom->documentElement);
        $inf->setLanguage($nodes->item(0)->textContent);

        $nodes = $xpath->query("/foo:alert/foo:info/foo:category", $dom->documentElement);
        foreach($nodes as $node)
            $inf->addCategory($nodes->item(0)->textContent);
            
        $nodes = $xpath->query("/foo:alert/foo:info/foo:event", $dom->documentElement);
        $inf->setEvent($nodes->item(0)->textContent);
        
        $nodes = $xpath->query("/foo:alert/foo:info/foo:responseType", $dom->documentElement);
        foreach($nodes as $node)
            $inf->addResponseType($nodes->item(0)->textContent);
        
        $nodes = $xpath->query("/foo:alert/foo:info/foo:urgency", $dom->documentElement);
        $inf->setUrgency($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:severity", $dom->documentElement);
        $inf->setSeverity($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:certainty", $dom->documentElement);
        $inf->setCertainty($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:audience", $dom->documentElement);
        $inf->setAudience($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:effective", $dom->documentElement);
        $inf->setEffective($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:onset", $dom->documentElement);
        $inf->setOnset($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:expires", $dom->documentElement);
        $inf->setExpires($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:senderName", $dom->documentElement);
        $inf->setSendername($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:headline", $dom->documentElement);
        $inf->setHeadline($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:description", $dom->documentElement);
        $inf->setDescription($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:instruction", $dom->documentElement);
        $inf->setInstruction($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:web", $dom->documentElement);
        $inf->setWeb($nodes->item(0)->textContent);
        $nodes = $xpath->query("/foo:alert/foo:info/foo:contact", $dom->documentElement);
        $inf->setContact($nodes->item(0)->textContent);

        /**
         * Extract eventCode information
         * There could be one or more eventCodes ???
         */
        $nodes = $xpath->query("/foo:alert/foo:info/foo:eventCode", $dom->documentElement);

        foreach($nodes as $node)
        {
            $evnt['valueName'] = $node->getElementsByTagName('valueName')->item(0)->textContent;
            $evnt['value'] = $node->getElementsByTagName('value')->item(0)->textContent;
            $inf->addEventCode($evnt['valueName'], $evnt['value']);
        }

        /**
         * Extract Parameter information
         * There could be one or more Parameters
         */
        $nodes = $xpath->query("/foo:alert/foo:info/foo:parameter", $dom->documentElement);

        foreach($nodes as $node)
        {
            $prm['valueName'] = $node->getElementsByTagName('valueName')->item(0)->textContent;
            $prm['value'] = $node->getElementsByTagName('value')->item(0)->textContent;
            $inf->addParameter($prm['valueName'], $prm['value']);
        }

        /**
         * Extract Reqource information
         * There could be one or more Reqources
         */
        $nodes = $xpath->query("/foo:alert/foo:info/foo:resource", $dom->documentElement);

        foreach($nodes as $node)
        {
            $res = new Msg_CapResource();
            $res->setResourceDesc($node->getElementsByTagName('resourceDesc')->item(0)->textContent);
            $res->setMimeType($node->getElementsByTagName('mimeType')->item(0)->textContent);
            $res->setSize($node->getElementsByTagName('size')->item(0)->textContent);
            $res->setUri($node->getElementsByTagName('uri')->item(0)->textContent);
            $res->setDerefUri($node->getElementsByTagName('derefUri')->item(0)->textContent);
            $res->setDigest($node->getElementsByTagName('digest')->item(0)->textContent);
            $inf->addResource($res);
        }


        /**
         * Extract Area information
         * There can be one or more Areas
         */
        $nodes = $xpath->query("/foo:alert/foo:info/foo:area", $dom->documentElement);

        foreach($nodes as $node)
        {
            $ar = new Msg_CapArea();
            $ar->setAreaDesc($node->getElementsByTagName('areaDesc')->item(0)->textContent);
            
            $polygons = $node->getElementsByTagName('polygon');
            foreach($polygons as $polygon)
            {
                $poly_arr = split(' ',$polygon->textContent);
                $ar->addPolygon($poly_arr);
            }
            
            $circles = $node->getElementsByTagName('circle');
            foreach($circles as $circle)
            {
                $c_elms = split(' ',$circle->textContent);
                $c_xy   = split(',', $c_elms[0]);
                $ar->addCircle($c_xy[0], $c_xy[1], $c_elms[1]);
            }
            
            $geocodes = $node->getElementsByTagName('geocode');
            foreach($geocodes as $geocode)
            {
                $valueName = $geocode->getElementsByTagName('valueName')->item(0)->textContent;
                $value  = $geocode->getElementsByTagName('value')->item(0)->textContent;
                $ar->addGeocode($valueName, $value);
            }
            
            $ar->setAltitude($node->getElementsByTagName('altitude')->item(0)->textContent);
            $ar->setCeiling($node->getElementsByTagName('ceiling')->item(0)->textContent);
            
            $inf->addArea($ar);
        }
        
        $this->addInfo($inf);
    }

    function array2string($arr,$sep=',')
    {
    	    if(is_array($arr))
        {
            $str = '';
            foreach($arr as $a)
                $str .= $a . $sep;
                
            return $str;
        }
    }

    function printFormattedMsg()
    {
        $info   = $this->info[0];
        $area   = $info->getArea();
        $res    = $info->getResource();

        print "<br /><center><h3>" . $info->getHeadline() . "</h3></center>";
        print "<h5>" . $info->getDescription() . "</h5>";
        print "<strong>Message Identifier\t: " .  $this->getIdentifier() . "</strong><br />";
        print "<strong>Sent By\t: " .  $this->getSender() . "</strong><br />";
        print "<strong>Date \t: " .  $this->getSent() . "</strong><br />";
        print "<strong>Language \t: " .  $info->getLanguage() . "</strong><br />";
       
        $head[] = array(
                        "Status", $this->getStatus(),
                        "Message Type", $this->getMsgType()
                       );
        $head[] = array(
                        "Source", $this->getSource(),
                        "Scope", $this->getScope()
                       );
        $head[] = array(
                        "Restriction", $this->getRestriction(),
                        "Address", $this->getAddress()
                       );
        $head[] = array(
                        "Code", $this->array2string($this->getCode(),' '),
                        "Note", $this->getNote()
                       );
        $head[] = array(
                        "References", $this->getReferences(),
                        "Incidents", $this->getIncidents()
                       );

        print "<br />";
        shn_html_table($head, null, null, array('class'=>'wide'), null);
        print "<br />";
        
        $this->__print_value('Category', $info->getCategory());
        $this->__print_value('Event', $info->getEvent());
        $this->__print_value('Response Type', $this->array2string($info->getResponseType()));
        $this->__print_value('Urgency', $info->getUrgency());
        $this->__print_value('Severity', $info->getSeverity());
        $this->__print_value('Certainty', $info->getCertainty());
        $this->__print_value('Audience', $info->getAudience());
        print "<br />";
        $this->__print_value('Sender Name', $info->getSendername());
        $this->__print_value('Instruction', $info->getInstruction());
        $this->__print_value('Contact', $info->getContact());
        $this->__print_value('Web', $info->getWeb());
        print "<br />   ";
        
        
        if(is_array($info->getEventCode()))
        {
            $this->__print_value('Event Code','');
            foreach ($info->getEventCode() as $ec)
            {
            	   $tbl_ec[] = array($ec['valueName'], $ec['value']);
            }
            $tbl_ec_h[] = array('Value Name', 'Value');
            shn_html_table($tbl_ec, $tbl_ec_h, null, array('class'=>'wide'), null);
            print "<br />   ";
        }        
        
        if ($info->getEffective() || $info->getOnset() || $info->getExpires())
        {
            $this->__print_value('Dates','');
            $tbl_dts_h[] = array('Effective', 'Onset', 'Expires');
            $tbl_dts[] = array($info->getEffective(), $info->getOnset(), $info->getExpires());
            shn_html_table($tbl_dts, $tbl_dts_h, null, array('class'=>'wide'), null);
        }
        
        
        print "<br />";
        
        if(is_array($info->getParameter()))
        {
            
            $tbl_Param_h[] = array('Value Name', 'Value');
            foreach ($info->getParameter() as $param)
                $tbl_Param[] = array($param['valueName'], $param['value']);
            
            print "<br /><br /><h3>Parameter</h3>";
            shn_html_table($tbl_Param, $tbl_Param_h, null, array('class'=>'wide'), null);
        }
        
        if(is_array($info->getResource()) && 1 < count($info->getResource()))
        {
            $tbl_res_h[] = array('Resource Description', 'Mime Type', 'Size', 'URI', 'DerefUri', 'Digest');
            foreach ($info->getResource() as $res)
            {
                 $tbl_res[] = array(
                                    $res->getResourceDesc(),
                                    $res->getMimeType(),
                                    $res->getSize(),
                                    $res->getUri(),
                                    $res->getDerefUri(),
                                    $res->getDigest()
                                   );
            }
            print "<br /><br /><h3>Resources</h3>";
            shn_html_table($tbl_res, $tbl_res_h, null, array('class'=>'wide'), null);
        }
        
        if(is_array($info->getArea()))
        {
            $tbl_ar_h[] = array('Area Description', 'Polygon', 'Circle', 'Geocode', 'Altitude', 'Ceiling');
            
            foreach($info->getArea() as $area)
            {
            	    if(is_array($area->getGeocode()))
                    foreach($area->getGeocode() as $gc)
                        $geo = $gc['valueName'] . ' : ' . $gc['value'] . '<br />';
                
                if(is_array($area->getPolygon()))
                    foreach($area->getPolygon() as $p)
                        $poly = $p . '<br />';
                
                if(is_array($area->getCircle()))
                    foreach($area->getCircle() as $c)
                        $crl = $c . '<br />';
                    
                $tbl_ar[] = array($area->getAreaDesc(), $poly, $crl, $geo, $area->getAltitude(), $area->getCeiling());
            }
            print "<br /><br /><h3>Area</h3>";
            shn_html_table($tbl_ar, $tbl_ar_h, null, array('class'=>'wide'), null);
        }
        
    }
    
    function __print_value($lab, $val)
    {
    	    print "<div><strong>$lab</strong> : $val</div>";
    }
    
    function __print_value_arr($lab, $val)
    {   
        if(is_array($val))
        {
            print "<h4>$lab</h4>";
            //print_r($val);
            //shn_html_table($val, null, null, array('class'=>'wide'), null);
        }	
    }


    function xmlAddChild($dom, $parent, $element, $elementVal)
    {
        if($elementVal != '')
        {
        	    $child = $dom->createElement($element);
            $child->appendChild($dom->createTextNode($elementVal));
            $parent->appendChild($child);
        }
        
//        if ($this->$element != '' && $elementVal == null)
//        {
//            $child = $dom->createElement($element);
//            $child->appendChild($dom->createTextNode($this->$element));
//            $parent->appendChild($child);
//        }
//        elseif ($this->$element != '' && $elementVal != null)
//        {
//            $child = $dom->createElement($element);
//            $child->appendChild($dom->createTextNode($elementVal));
//            $parent->appendChild($child);
//        }

    }

    function getXML()
    {
        $dom = new DomDocument('1.0', 'utf-8');

        $alert = $dom->createElement('alert');
        $alert->setAttribute('xmlns', 'urn:oasis:names:tc:emergency:cap:1.1');

        $dom->appendChild($alert);

        $this->xmlAddChild($dom, $alert, 'identifier', $this->getIdentifier());
        $this->xmlAddChild($dom, $alert, 'sender', $this->getSender());
        $this->xmlAddChild($dom, $alert, 'sent', $this->getSent());
        $this->xmlAddChild($dom, $alert, 'status', $this->getStatus());
        $this->xmlAddChild($dom, $alert, 'msgType', $this->getMsgType());
        $this->xmlAddChild($dom, $alert, 'source', $this->getSource());
        $this->xmlAddChild($dom, $alert, 'scope', $this->getScope());
        $this->xmlAddChild($dom, $alert, 'restriction', $this->getRestriction());
        $this->xmlAddChild($dom, $alert, 'address', $this->getAddress());
        
        if(is_array($this->getCode()))
        {
            foreach($this->getCode() as $c)
            {
                $this->xmlAddChild($dom, $alert, 'code', $c);
            }
        }
        
        $this->xmlAddChild($dom, $alert, 'note', $this->getNote());
        $this->xmlAddChild($dom, $alert, 'references', $this->getReferences());
        $this->xmlAddChild($dom, $alert, 'incidents', $this->getIncidents());

        //<info>
        $inf = $this->info[0];
        if ($inf != null)
        {
            $info = $dom->createElement('info');
            $alert->appendChild($info);
            
            $this->xmlAddChild($dom, $info, 'language', $inf->getLanguage());
            if(is_array($inf->getCategory()))
            {
                foreach($inf->getCategory() as $cat)
                {
                    $this->xmlAddChild($dom, $info, 'category', $cat);
                }
            }
            
            $this->xmlAddChild($dom, $info, 'event', $inf->getEvent());
            
            if(is_array($inf->getResponseType()))
            {
                foreach($inf->getResponseType() as $rt)
                {
                    $this->xmlAddChild($dom, $info, 'responseType', $rt);
                }
            }
            
            $this->xmlAddChild($dom, $info, 'urgency', $inf->getUrgency());
            $this->xmlAddChild($dom, $info, 'severity', $inf->getSeverity());
            $this->xmlAddChild($dom, $info, 'certainty', $inf->getCertainty());
            $this->xmlAddChild($dom, $info, 'audience', $inf->getAudience());
            $this->xmlAddChild($dom, $info, 'effective', $inf->getEffective());
            $this->xmlAddChild($dom, $info, 'onset', $inf->getOnset());
            $this->xmlAddChild($dom, $info, 'expires', $inf->getExpires());
            $this->xmlAddChild($dom, $info, 'senderName', $inf->getSendername());
            $this->xmlAddChild($dom, $info, 'headline', $inf->getHeadline());
            $this->xmlAddChild($dom, $info, 'description', $inf->getDescription());
            $this->xmlAddChild($dom, $info, 'instruction', $inf->getInstruction());
            $this->xmlAddChild($dom, $info, 'web', $inf->getWeb());
            $this->xmlAddChild($dom, $info, 'contact', $inf->getContact());
    
            if (is_array($inf->getEventCode()))
            {
                foreach ($inf->getEventCode() as $evnt)
                {
                    $eventCode = $dom->createElement('eventCode');
                    $info->appendChild($eventCode);
    
                    foreach ($evnt as $evnt_key=>$evnt_val)
                    {
                        $evnt_child = $dom->createElement($evnt_key);
                        $evnt_child->appendChild($dom->createTextNode($evnt_val));
                        $eventCode->appendChild($evnt_child);
                    }
    
                }
            }
    
            if (is_array($inf->getParameter()))
            {
                foreach ($inf->getParameter() as $prm)
                {
                    $parameter = $dom->createElement('parameter');
                    $info->appendChild($parameter);
    
                    foreach ($prm as $prm_key=>$prm_val)
                    {
                        $prm_child = $dom->createElement($prm_key);
                        $prm_child->appendChild($dom->createTextNode($prm_val));
                        $parameter->appendChild($prm_child);
                    }
    
                }
    
            }
            if(is_array($inf->getResource()))
            {
                foreach($inf->getResource() as $res)
                {
                	    $resource = $dom->createElement('resource');
                    $info->appendChild($resource);
                    
                    $this->xmlAddChild($dom, $resource, 'resourceDesc', $res->getResourceDesc());
                    $this->xmlAddChild($dom, $resource, 'mimeType', $res->getMimeType());
                    $this->xmlAddChild($dom, $resource, 'size', $res->getSize());
                    $this->xmlAddChild($dom, $resource, 'uri', $res->getUri());
                    $this->xmlAddChild($dom, $resource, 'derefUri', $res->getDerefUri());
                    $this->xmlAddChild($dom, $resource, 'digest', $res->getDigest());
                }
            }
            
            if(is_array($inf->getArea()))
            {
                foreach($inf->getArea() as $ar)
                {
                    $area = $dom->createElement('area');
                    $info->appendChild($area);
                    
                    $this->xmlAddChild($dom, $area, 'areaDesc', $ar->getAreaDesc());
                    
                    if(is_array($ar->getPolygon()))
                    {
                        foreach($ar->getPolygon() as $poly)
                            $this->xmlAddChild($dom, $area, 'polygon', $poly);
                    }
                    
                    if(is_array($ar->getCircle()))
                    {
                        foreach($ar->getCircle() as $cle)
                            $this->xmlAddChild($dom, $area, 'circle', $cle);
                    }
                    
                    if(is_array($ar->getGeocode()))
                    {
                        foreach($ar->getGeocode() as $geo)
                        {
                            $geocode = $dom->createElement('geocode');
                            $area->appendChild($geocode);
                            
                            $this->xmlAddChild($dom, $geocode, 'valueName', $geo['valueName']);
                            $this->xmlAddChild($dom, $geocode, 'value', $geo['value']);
                        }
                    }
        
                    $this->xmlAddChild($dom, $area, 'altitude', $ar->getAltitude());
                    $this->xmlAddChild($dom, $area, 'ceiling', $ar->getCeiling());           
                }
            }
        }
        return $dom->saveXML();

    }

    function saveXML($path, $file)
    {
        if (is_writable($path))
            file_put_contents($path.$file, $this->getXML());
        else
            print "plesae make the path : $file writable";
    }

    function printCapXML()
    {
        print '<pre>' . htmlspecialchars($this->getXML()) . '</pre>';
    }
    
    /**
     * Prints out the list of areas in a table
     */
    function printAreas($showDel=false)
    {
        $info = $this->getInfo();
        
        if(is_array($info->getArea()))
        {
            if (!$showDel)
                $th_ar[] = array(_t("Area Description"), _t("Polygon"), _t("Circle"), _t("Geocode"), _t("Altitude"), _t("Ceiling"));
            else
                $th_ar[] = array(_t("Area Description"), _t("Polygon"), _t("Circle"), _t("Geocode"), _t("Altitude"), _t("Ceiling"), _t("Remove"));
            
            $count = 0;
            
            foreach($info->getArea() as $area)
            {
                $del_str = '';
                 if ($showDel)
                    $del_str = '<a href="index.php?mod=msg&amp;act=cap_new' .
                                '&amp;seq=del_cap_area&amp;area_id=' . 
                                $count . '">' . _t("Remove") . '</a>';
                                
                if(is_array($area->getGeocode()))
                foreach($area->getGeocode() as $gc)
                    $geo = $gc['valueName'] . ' : ' . $gc['value'] . '<br />';
                
                if(is_array($area->getPolygon()))
                    foreach($area->getPolygon() as $p)
                        $poly = $p . '<br />';
                
                if(is_array($area->getCircle()))
                    foreach($area->getCircle() as $c)
                        $crl = $c . '<br />';
                    
                $tb_ar[] = array($area->getAreaDesc(), $poly, $crl, $geo, 
                                 $area->getAltitude(), $area->getCeiling(),
                                 $del_str);
            }
            print "<br /><br /><h3>Area</h3>";
            shn_html_table($tb_ar, $th_ar, null, array('class'=>'wide'), null);
        }
    }
    
    /**
     * Prints out the resources in a table
     */
    function printResource($showDel=false)
    {
        $info = $this->getInfo();
        
        if(is_array($info->getResource()) && 0 < count($info->getResource()))
        {
            $th_res[0] = array(_t("Resource Description"), _t("Mime Type"), _t("Size"), _t("URI"), _t("DerefUri"), _t("Digest"));
            
            if ($showDel)
                $th_res[0] = array(_t("Resource Description"), _t("Mime Type"), _t("Size"), _t("URI"), _t("DerefUri"), _t("Digest"), _t("Remove"));
            $count = 0;
            foreach ($info->getResource() as $res)
            {
                 $del_str = '';
                 if ($showDel)
                    $del_str = '<a href="index.php?mod=msg&amp;act=cap_new' .
                                '&amp;seq=del_cap_res&amp;res_id=' . 
                                $count . '">' . _t("Remove") . '</a>';
                 $tb_res[] = array(
                                    $res->getResourceDesc(),
                                    $res->getMimeType(),
                                    $res->getSize(),
                                    $res->getUri(),
                                    $res->getDerefUri(),
                                    $res->getDigest(),
                                    $del_str
                                   );
                $count++;
            }
            print "<br /><br /><h3>Resources</h3>";
            shn_html_table($tb_res, $th_res, null, array('class'=>'wide'), null);
        }
    }
    
    function alertElemValidate($elem)
    {
    	    if (!isset($elem) || strstr($elem, ' ') || strstr($elem, ',')
                                || strstr($elem, '&') || strstr($elem, '<'))
        {
            return false;
        }
        
        return true;
    }
    
    function addCode($code)
    {
    	    if(isset($code) && $code != '')
            $this->code[] = $code;
    }
    
    function addInfo($info,$index=null)
    {
    	    if($info->isValid() && $index == null)
                $this->info[] = $info;
            elseif($index != null)
                $this->info[$index] = $info;
    }
    
    /**
     * Set methods
     */
    function setIdentifier($identifier)
    {
        if($this->alertElemValidate($identifier))
            $this->identifier = $identifier;
    }
    
    function setSender($sender)
    {
        if($this->alertElemValidate($sender))
            $this->sender = $sender;
    }
    
    function setSent($sent)
    {
        if(isset($sent) && $sent != '')
            $this->sent = $sent;
    }
    
    function setStatus($status)
    {
        if(isset($status) && $status != '')
            $this->status = $status;
    }
    
    function setMsgType($msgType)
    {
        if(isset($msgType) && $msgType != '')
            $this->msgType = $msgType;
    }
    
    function setSource($source)
    {
        $this->source = $source;
    }
    
    function setScope($scope)
    {
        if(isset($scope) && $scope != '')
            $this->scope = $scope;
    }
    
    function setRestriction($restriction)
    {
        if($this->scope == 'Restricted')
        {
            if(isset($restriction) && $restriction != '')
                $this->restriction = $restriction;
            else
                add_error(_t("When the Scope = Restricted, A Restriction is needed"));
        }
    }
    
    function setAddress($address)
    {
        if($this->scope == 'Private')
        {
            if(isset($address) && $address != '')
                $this->address = $address;
            else
                add_error(_t("When the Scope = Private, An Address is needed"));
        }
    }
    
    function setCode($code)
    {
        $this->code = $code;
    }
    
    function setNote($note)
    {
        $this->note = $note;
    }
    
    function setReferences($references)
    {
        $this->references = $references;
    }
    
    function setIncidents($incidents)
    {
        $this->incidents = $incidents;
    }
    
    function setInfo($info, $index)
    {
        $this->info[$index] = $info;
    }
    
    /**
     * Get methods
     */
    function getIdentifier()
    {
        return $this->identifier;
    }
    
    function getSender()
    {
        return $this->sender;
    }
    
    function getSent()
    {
        return $this->sent;
    }
    
    function getStatus()
    {
        return $this->status;
    }
    
    function getMsgType()
    {
        return $this->msgType;
    }
    
    function getSource()
    {
        return $this->source;
    }
    
    function getScope()
    {
        return $this->scope;
    }
    
    function getRestriction()
    {
        return $this->restriction;
    }
    
    function getAddress()
    {
        return $this->address;
    }
    
    function getCode()
    {
        $codes = $this->code;
        if (is_array($codes))
        {
            foreach ($codes as $code)
                $code_str .= $code . ' ';
            return $code_str;
        }
        else
            return null;
    }
    
    function getNote()
    {
        return $this->note;
    }
    
    function getReferences()
    {
        return $this->references;
    }
    
    function getIncidents()
    {
        return $this->incidents;
    }
    
    function getInfo($index=null)
    {
        if($index == null)
            return $this->info[0];
        else
            return $this->info[$index];
    }
    
}

