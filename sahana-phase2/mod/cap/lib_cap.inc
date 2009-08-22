<?php
/*
 * Sahana CAP alert aggregator Module
 * PHP version 5
 * LICENSE: This source file is subject to LGPL license 
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 * @author     Shree Kant Bohra <skbohra123@gmail.com> 
 * @package    Sahana - http://sahana.lk/
 * @module     CAP
 * @copyright  Lanka Software Foundation - http://www.opensource.lk 
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 */
global $global;
include_once $global['approot']."/inc/lib_http.inc";
function discover_feed($srcurl)
{	$atomlocation=array();	
	$url=parse_url($srcurl);
 	$fragment=$url["path"];
 	if(preg_match("/.atom|.xml|.rss/", $fragment)){
		$atomlocation[0]=$srcurl;
 		return $atomlocation;
 	}else{
 		$html=getFile($srcurl);
 		$atomlocation=getFeedLocation($html, $srcurl);
 		return $atomlocation;
 	}
}
 
/* Function to get feed documents list
*  based on keith devens RSS auto discovery function
*  this function scraps an html document, find out all 
*  <link> tags with atom or rss feed documents url and 
*  returns an array
*  @params string,string 
*  @return array 
 */
function getFeedLocation($html, $location)
{
    if(!$html or !$location){
        return false;
    }else{
        preg_match_all('/<link\s+(.*?)\s*\/?>/si', $html, $matches);
        $links = $matches[1];
        $final_links = array();
        $link_count = count($links);
        for($n=0; $n<$link_count; $n++){
            $attributes = preg_split('/\s+/s', $links[$n], 6);
            foreach($attributes as $attribute){
                $att = preg_split('/\s*=\s*/s', $attribute, 2);
                if(isset($att[1])){
                    $att[1] = preg_replace('/([\'"]?)(.*)\1/', '$2', $att[1]);
                    $final_link[strtolower($att[0])] = $att[1];
                }
            }
            $final_links[$n] = $final_link;
            
        }
        for($n=0; $n<$link_count; $n++){
			if(strtolower($final_links[$n]['rel']) == 'alternate'){
            	if(strtolower($final_links[$n]['type']) == 'application/atom+xml' || strtolower($final_links[$n]['type']== 'application/rss+xml')){
                    $href = $final_links[$n]['href'];
                }
                if(!$href and strtolower($final_links[$n]['type']) == 'text/xml'){
                    $href = $final_links[$n]['href'];
                }
                if($href){
                    if(strstr($href, "http://") !== false){ 
                        $full_url[] = $href;
                    }else{
                        $url_parts = parse_url($location);
                        $full_url[] = "http://$url_parts[host]";
                        if(isset($url_parts['port'])){
                            $full_url[count($full_url)-1] .= ":$url_parts[port]";
                        }
                        if($href{0} != '/'){ 
                            $full_url[count($full_url)-1] .= dirname($url_parts['path']);
                            if(substr($full_url[count($full_url)-1], -1) != '/'){
                                
                                $full_url[count($full_url)-1] .= '/';
                            }
                        }
                        $full_url[count($full_url)-1] .= $href;
                    }
                    //return $full_url;
                }
            }
        }
        if (isset($full_url)) {
            return $full_url;
        } else {
            return false;
        }
    }
}

/*Fuction to fetch html/xml document
 * using CURL library
 * @params string url of location to be fetched
 * @return document
 */

 
function getFile($location)
{
	
    $ch = curl_init($location);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Connection: close'));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_TIMEOUT, 10);
    $response = curl_exec($ch);
    curl_close($ch);
    if(!curl_errno($ch))
    {
    return $response;
    }
    else{
    add_error(_t("Problem in Network"));
	}
}



class parseFeedIndex
{
	var $mUrl;
	var $mTitle;
	var $mAuthor;
	var $mId;
	var $mGenerator;
	var $mUpdated;
	var $mLink;
	var $mFeed;
	var $mTotalsssfeed;
	var $mValidate;
	
	function setDocument()
	{
		$step=0;
		$file=getFile($this->mUrl);
		$xmlfile = new SimpleXMLElement($file);
		if($xmlfile->title){
			$this->mValidate=1;
			$this->mTitle = $xmlfile->title[0];
			$this->mId = $xmlfile->id[0];
			$this->mAuthor = $xmlfile->author[0];
			$this->mGenerator= $xmlfile->generator[0];
			$this->mUpdated=$xmlfile->updated[0];
			$this->mLink=$xmlfile->link[0];
			$this->mFeed=$xmlfile->id[0];
			
			
			while($xmlfile->entry[$step])
			{	
				$step++;
			}
			$this->mTotalfeed=$step;
		}
		else{
			$this->mValidate=1;
			$this->mTitle = $xmlfile->channel[0]->title[0];
			$this->mId = $xmlfile->channel[0]->link[0];
			if($xmlfile->channel[0]->managingEditor[0])
			$this->mAuthor = $xmlfile->channel[0]->managingEditor[0];
			if($xmlfile->channel[0]->webMaster[0])
			$this->mGenerator= $xmlfile->channel[0]->webMaster[0];
			if($xmlfile->channel[0]->lastBuildDate[0])
			$this->mUpdated=$xmlfile->channel[0]->lastBuildDate[0];
			if($xmlfile->channel[0]->link[0])
			$this->mLink=$xmlfile->channel[0]->link[0];
			if($xmlfile->channel[0]->link[0])
			$this->mFeed=$xmlfile->channel[0]->link[0];
			if($xmlfile->channel[0]->pubDate[0])
			$this->mUpdated=$xmlfile->channel[0]->pubDate[0];
			
			if($xmlfile->channel[0]->children('http://purl.org/dc/elements/1.1/')->date[0])
			$this->mUpdated=$xmlfile->channel[0]->children('http://purl.org/dc/elements/1.1/')->date[0];
			
			if($xmlfile->channel[0]->item[$step])
			{
			while($xmlfile->channel[0]->item[$step])
			{	
				$step++;
			}
			}
			else
			{
			while($xmlfile->item[$step])
			{	
				$step++;
			}	
			}
			$this->mTotalfeed=$step;
			
			}
		}
}

class fetchCap 
{  
	function fetchAlerts($url,$step=0)
	{
		$feedFile=getFile($url);
		if($feedFile)
		{		
		$alert=array();
		$xml = new SimpleXMLElement($feedFile);
		if($xml->entry){
		$alert['updated']=$xml->updated[0];
		while($xml->entry[$step]){
			if($xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->severity[0]=='Extreme'){
			$alert[$step]['severity']='1';	
			}elseif($xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->severity[0]=='Severe'){
			$alert[$step]['severity']='2';	
			}elseif($xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->severity[0]=='Moderate'){
			$alert[$step]['severity']='3';	
			}elseif($xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->severity[0]=='Minor'){
			$alert[$step]['severity']='4';	
			}else{
				$alert[$step]['severity']='5';
			}
			//$alert[$step]['link']=saveCAP($xml->entry[$step]->link[0]->attributes()->href);			
			
			$alert[$step]['feed_id']=$xml->entry[$step]->id[0];
			$alert[$step]['title']=$xml->entry[$step]->title[0];
			$alert[$step]['updated']=$xml->entry[$step]->updated[0];
			$alert[$step]['link']=$xml->entry[$step]->link[0]->attributes()->href;
			$alert[$step]['status']=$xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->status[0];
			$alert[$step]['category']=$xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->category[0];
			$alert[$step]['urgency']=$xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->urgency[0];
			$alert[$step]['certainity']=$xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->certainty[0];
			$alert[$step]['msgtype']=$xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->msgType[0];
			$alert[$step]['area']=$xml->entry[$step]->children('urn:oasis:names:tc:emergency:cap:1.1')->areaDesc[0];
			if($xml->entry[$step]->children('http://www.alerting.net/namespace/index_1.0')->latLonBox[0])
			$alert[$step]['longlat']=$xml->entry[$step]->children('http://www.alerting.net/namespace/index_1.0')->latLonBox[0];
			if($xml->entry[$step]->children('http://www.georss.org/georss')->point[0])
			{
			 $split=preg_split('/\s/',$xml->entry[$step]->children('http://www.georss.org/georss')->point[0],2); //get the cordiantes from database
			 $alert[$step]['longlat']=$split[0].','.$split[1];
			}
			$step++;
		}
		}else{
			
			if($xml->channel[0]->item[$step])
			{
				$alert['updated']=$xml->channel[0]->pubDate[0];
			while($xml->channel[0]->item[$step]){
				if($xml->channel[0]->item[$step]->title[0])
				$alert[$step]['title']=$xml->channel[0]->item[$step]->title[0];
				if($xml->channel[0]->item[$step]->id[0])
				$alert[$step]['feed_id']=$xml->channel[0]->item[$step]->link[0];
				if($xml->channel[0]->item[$step]->pubDate[0])
				$alert[$step]['updated']=$xml->channel[0]->item[$step]->pubDate[0];
				if($xml->channel[0]->item[$step]->link[0])
				$alert[$step]['link']=$xml->channel[0]->item[$step]->link[0];
				if($xml->channel[0]->item[$step]->children('http://www.w3.org/2003/01/geo/wgs84_pos#')->lat[0])
				$alert[$step]['longlat']=$xml->channel[0]->item[$step]->children('http://www.w3.org/2003/01/geo/wgs84_pos#')->lat[0].','.$xml->channel[0]->item[$step]->children('http://www.w3.org/2003/01/geo/wgs84_pos#')->long[0];
				$alert[$step]['status']='unknown';
				$alert[$step]['category']='unknown';
				$alert[$step]['urgency']='unknown';
				$alert[$step]['certainity']='unknown';
				$alert[$step]['msgtype']='unknown';
				$alert[$step]['area']='unknown';
				$step++;
			}
			}else{
				$alert['updated']=$xml->channel[0]->children('http://purl.org/dc/elements/1.1/')->date[0];
				$step=0;
			while($xml->item[$step]){
				
				$alert[$step]['title']=$xml->item[$step]->title[0];
				$alert[$step]['feed_id']=$xml->item[$step]->link[0];
				if($xml->item[$step]->children('http://www.geonet.org.nz/feeds/earthquake/')->time[0])
				$alert[$step]['updated']=$xml->item[$step]->children('http://www.geonet.org.nz/feeds/earthquake/')->time[0];
				if($xml->item[$step]->children('http://purl.org/dc/elements/1.1/')->date[0])
				$alert[$step]['updated']=$xml->item[$step]->children('http://purl.org/dc/elements/1.1/')->date[0];
				$alert[$step]['link']=$xml->item[$step]->link[0];
				$alert[$step]['longlat']=$xml->item[$step]->children('http://www.w3.org/2003/01/geo/wgs84_pos#')->lat[0].','.$xml->item[$step]->children('http://www.w3.org/2003/01/geo/wgs84_pos#')->long[0];
				$alert[$step]['status']='unknown';
				$alert[$step]['category']='unknown';
				$alert[$step]['urgency']='unknown';
				$alert[$step]['certainity']='unknown';
				$alert[$step]['msgtype']='unknown';
				$alert[$step]['area']='unknown';
				$step++;
			
			}
			
			}
		}
		
		$alert['total']=$step;
		return $alert;
	}
	
	
	else
	{
		return 'error';
	}
	}
	
	function saveCAP($location)
	{	
		global $global;
		$ch = curl_init($location);
		$filename = substr(strrchr($location, '/'),1);
		$savelocation = $global['approot']."/mod/cap/capalerts/".$filename;
		$fp = fopen($savelocation,'w'); 
		curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
    	curl_setopt($ch, CURLOPT_HTTPHEADER, array('Connection: close'));
    	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    	curl_setopt($ch, CURLOPT_TIMEOUT, 20);
    	curl_setopt($ch, CURLOPT_FILE, $fp);
    	curl_exec($ch);
    	curl_close($ch);
    	return $filename;
	
	}
	
	
	
	
	
}		

	
	
	

