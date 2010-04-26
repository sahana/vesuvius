<?php
class Pfif_Person{
	
	//Meta data
	public $person_record_id;
	public $entry_date;
	public $author_name;
	public $author_email;
	public $author_phone;
	public $source_name;
	public $source_date;
	public $source_url;
	
	//Static identifying information
	public $first_name;
	public $last_name;
	public $home_city;
	public $home_state;
	public $home_neighborhood;
	public $home_street;
	public $home_zip;
	public $photo_url;
	public $other;	
	public $notes = array();
	
	public function setNote(Pfif_Note $note){
		$this->notes[] = $note;
	}
	
	public function getNotes(){
		return $this->notes;
	}
	
	public function getNoteLatest(){
	    // TODO must implement correctly
	    if(count($this->notes) > 0){
            date_default_timezone_set('UTC');
            $latest_date = strtotime("1970-01-01T00:00:01Z");
            $latest_note = 0;
            foreach ($this->notes as $i =>$next_note) {
                $comp_date = strtotime($next_note->entry_date);
                if ($comp_date > $latest_date) {
                    $latest_date = $comp_date;
                    $latest_note = $i;
                }
            }
            return $this->notes[$latest_note];
	    }
	}
}

class Pfif_Note{
	public $note_record_id;
	public $entry_date;
	public $author_name;
	public $author_email;
	public $author_phone;
	public $source_date;
	public $found;
	public $email_of_found_person;
	public $phone_of_found_person;
	public $last_known_location;
	public $text;	
	
	
}
class Pfif{

	public $personArray = array();
	private  $dom_pfif;
	
	public function __construct(){

	}
	
	public function setPerson(Pfif_Person $person){
		$this->personArray[] =  $person;
        // error_log("Set $person->person_record_id ...");
	}
	
	public function getPersons(){
		return $this->personArray;
	}
	
	private function createXmlElement($domElement, $property , $value){
		$child = $this->dom_pfif->createElement($property, $value);
        $domElement->appendChild($child);
	}
	
	public function storeInXML(){

		$this->dom_pfif = new DomDocument('1.0', 'utf-8');
		$dom_pfif = $this->dom_pfif->createElement('pfif:pfif');
        $dom_pfif->setAttribute('xmlns:pfif', 'http://zesty.ca/pfif/1.1');
        $dom_pfif->setAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
        $dom_pfif->setAttribute('xsi:schemaLocation', 'http://zesty.ca/pfif/1.1/pfif-1.1.xsd');        
        $this->dom_pfif->appendChild($dom_pfif);
        
        foreach($this->getPersons() as $person){
        	$personElement = $this->dom_pfif->createElement('pfif:person');
        	
        	$this->createXmlElement($personElement , 'pfif:person_record_id' , $person->person_record_id);
        	$this->createXmlElement($personElement, 'pfif:entry_date' , $person->entry_date);
        	$this->createXmlElement($personElement, 'pfif:author_name' , $person->author_name);
        	$this->createXmlElement($personElement, 'pfif:author_email' , $person->author_email);
        	$this->createXmlElement($personElement, 'pfif:author_phone' , $person->author_phone);
        	$this->createXmlElement($personElement, 'pfif:source_name' , $person->source_name);
        	$this->createXmlElement($personElement, 'pfif:source_date' , $person->source_date);
        	$this->createXmlElement($personElement, 'pfif:source_url' , $person->source_url);
        	
        	$this->createXmlElement($personElement, 'pfif:first_name' , $person->first_name);
        	$this->createXmlElement($personElement, 'pfif:last_name' , $person->last_name);
        	$this->createXmlElement($personElement, 'pfif:home_city' , $person->home_city);
        	$this->createXmlElement($personElement, 'pfif:home_state' , $person->home_state);
        	$this->createXmlElement($personElement, 'pfif:home_neighborhood' , $person->home_neighborhood);
        	$this->createXmlElement($personElement, 'pfif:home_street' , $person->home_street);
        	$this->createXmlElement($personElement, 'pfif:home_zip' , $person->home_zip);
        	$this->createXmlElement($personElement, 'pfif:photo_url' , $person->photo_url);
        	$this->createXmlElement($personElement, 'pfif:other' , $person->other);
	
        
        	
        	foreach($person->getNotes() as $note){
        		$noteElement = $this->dom_pfif->createElement('pfif:note');
        		$this->createXmlElement($noteElement, 'pfif:note_record_id' , $note->note_record_id);
        		$this->createXmlElement($noteElement, 'pfif:entry_date' , $note->entry_date);
        		$this->createXmlElement($noteElement, 'pfif:author_name' , $note->author_name);
        		$this->createXmlElement($noteElement, 'pfif:author_email' , $note->author_email);
        		$this->createXmlElement($noteElement, 'pfif:author_phone' , $note->author_phone);
        		$this->createXmlElement($noteElement, 'pfif:source_date' , $note->source_date);
        		$this->createXmlElement($noteElement, 'pfif:found' , $note->found);
        		$this->createXmlElement($noteElement, 'pfif:email_of_found_person' , $note->email_of_found_person);
        		$this->createXmlElement($noteElement, 'pfif:phone_of_found_person' , $note->phone_of_found_person);
        		$this->createXmlElement($noteElement, 'pfif:last_known_location' , $note->last_known_location);
        		$this->createXmlElement($noteElement, 'pfif:text' , $note->text);

        		$personElement->appendChild($noteElement);
        	}        	
        	$this->dom_pfif->firstChild->appendChild($personElement);        	
        }
        // print $this->dom_pfif->saveXML();
        return $this->dom_pfif->saveXML();		
	}

    // TODO: may need to add logic to support services other than Google.
	public function loadFromService(
                        $id,
                        $service_name = 'google') {

        global $global;
        require_once $global['approot'] . 'mod/mpr/pfifconf.inc.php';
        // print "PFIF Configuration:<pre>";print_r($pfif_conf);print "</pre>";
        $service_uri = $pfif_conf['services'][$service_name]['read_url'];

        $pfif_uri = $service_uri."?id=".$id;
        // print "importing PFIF from $pfif_uri<br/>";

        $loaded = $this->loadFromXML($pfif_uri);
        return $loaded;
    }

    public function postDbToService($id, $svc='google') {
        return $this->postToService(true, $id, $svc);
    }

    public function postFileToService($filename, $svc='google') {
        return $this->postToService(false, $filename, $svc);
    }

	public function postToService(
                            $get_from_db = true,
                            $id_or_filename, // TODO: XML string or file name ???
                            $service_name = 'google') {
        global $global;
        require_once $global['approot'] . 'mod/mpr/pfifconf.inc.php';

        if ($get_from_db) {
            $persons = $this->loadFromDatabase('id?'.$id_or_filename);
            $xml = $this->storeInXML();
        } else {
            return 'Post from file is not yet implemented';
        }
        // print "PFIF Configuration:<pre>";print_r($pfif_conf);print "</pre>";
        $service_uri = $pfif_conf['services'][$service_name]['post_url'];

        // TODO: may need to add logic to support services other than Google.
        $auth_key = $pfif_conf['services'][$service_name]['auth_key'];
        $pfif_uri = $service_uri."?key=".$auth_key;
        // $posted = "Posted PFIF from <br/>".htmlentities($xml)."<br/> to $pfif_uri<br/>Status returned:<br/>";
        $posted = "Posted ".$id_or_filename." to $pfif_uri<br/>Status returned:<br/>";
        /*
                        * TODO: Can xml string be POSTed or do we HAVE to use CURL ? 
                        * curl -X POST -H 'Content-type: application/xml' --data-binary @your_file.xml \
    http://haiticrisis.appspot.com/api/write?key=your_auth_key
                        * @see http://haiticrisis.appspot.com/developers for response details 
                        */        
        
        $status .= '<?xml version="1.0"?>
<status:status>
  <status:write>
    <status:record_type>pfif:person</status:record_type>
    <status:parsed>1</status:parsed>
    <status:written>1</status:written>
    <status:skipped>
    </status:skipped>
  </status:write>

  <status:write>
    <status:record_type>pfif:note</status:record_type>
    <status:parsed>1</status:parsed>
    <status:written>1</status:written>
    <status:skipped>
    </status:skipped>
  </status:write>
</status:status>'; // false;
        return $posted."<pre>".htmlentities($status)."</pre>";
    }
    
function postGoogleItem($url, $item) {
  $ch = curl_init();    /* Create a CURL handle. */
  global $developerKey, $itemsFeedURL;

  /* Set cURL options. */
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_POST, true);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_FAILONERROR, true);
  curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    'Authorization: AuthSub token="' . $_POST['token'] . '"',
    'X-Google-Key: key=' . $developerKey,
    'Content-Type: application/xml'
  ));
  curl_setopt($ch, CURLOPT_POSTFIELDS, buildInsertXML());

  $result = curl_exec($ch);  /* Execute the HTTP request. */
  curl_close($ch);           /* Close the cURL handle. */

  return $result;
}

    
	public function loadFromXML($capxml){
		$this->dom_pfif = new DomDocument('1.0', 'utf-8');
        if(isset($capxml)){
            $this->dom_pfif->load($capxml);
            $this->xpath = new DomXPath($this->dom_pfif);     
        }
        
        $ns = 'http://zesty.ca/pfif/1.1';
        $persons = $this->getValueFromXmlElementTag($this->dom_pfif , 'person' , $ns); // $this->dom_pfif->getElementsByTagNameNS( $ns , 'person');
        // $dump = var_export($persons,true);
        // error_log("got persons:".$dump." length = ".$persons->length);
        if ($persons->length == 0) {
            return false;
        }
            
        foreach($persons as $person){
            
        	$pfif_person = new Pfif_Person();
        	$pfif_person->person_record_id = $this->getValueFromXmlElementTag($person , 'person_record_id' , $ns)->item(0)->nodeValue;        	
            // error_log("processing person:".$pfif_person->person_record_id);
	 		$pfif_person->entry_date = $this->getValueFromXmlElementTag($person , 'entry_date' , $ns)->item(0)->nodeValue;
	 		$pfif_person->author_name= $this->getValueFromXmlElementTag($person , 'author_name' , $ns)->item(0)->nodeValue;
	 		$pfif_person->author_email=  $this->getValueFromXmlElementTag($person , 'author_email' , $ns)->item(0)->nodeValue;
	 		$pfif_person->author_phone=  $this->getValueFromXmlElementTag($person , 'author_phone' , $ns)->item(0)->nodeValue;
	 		$pfif_person->source_name=  $this->getValueFromXmlElementTag($person , 'source_name' , $ns)->item(0)->nodeValue;
	 		$pfif_person->source_date=  $this->getValueFromXmlElementTag($person , 'source_date' , $ns)->item(0)->nodeValue;
	 		$pfif_person->source_url= $this->getValueFromXmlElementTag($person , 'source_url' , $ns)->item(0)->nodeValue;
            // error_log("meta-informaton done ...");
	
	//Static identifying information
	 		$pfif_person->first_name= $this->getValueFromXmlElementTag($person , 'first_name' , $ns)->item(0)->nodeValue;
	 		$pfif_person->last_name= $this->getValueFromXmlElementTag($person , 'last_name' , $ns)->item(0)->nodeValue;
	 		$pfif_person->home_city= $this->getValueFromXmlElementTag($person , 'home_city' , $ns)->item(0)->nodeValue;
	 		$pfif_person->home_state=  $this->getValueFromXmlElementTag($person , 'home_state' , $ns)->item(0)->nodeValue;
	 		$pfif_person->home_neighborhood=  $this->getValueFromXmlElementTag($person , 'home_neighborhood' , $ns)->item(0)->nodeValue;
	 		$pfif_person->home_street= $this->getValueFromXmlElementTag($person , 'home_street' , $ns)->item(0)->nodeValue;
	 		$pfif_person->home_zip=  $this->getValueFromXmlElementTag($person , 'home_zip' , $ns)->item(0)->nodeValue;
	 		$pfif_person->photo_url=  $this->getValueFromXmlElementTag($person , 'photo_url' , $ns)->item(0)->nodeValue;
	 		$pfif_person->other= $this->getValueFromXmlElementTag($person , 'other' , $ns)->item(0)->nodeValue;	
            // error_log("Static informaton done ...");
        	
        	$notes = $this->getValueFromXmlElementTag($person , 'note' , $ns); 
            // $dump = var_export($notes,true);
            // error_log("got notes:".$dump." count = ".$notes->length);
        	foreach($notes as $note){
        		$pfif_note = new Pfif_Note();

    			$pfif_note->note_record_id = $this->getValueFromXmlElementTag($note , 'note_record_id' , $ns)->item(0)->nodeValue;
    			$pfif_note->entry_date = $this->getValueFromXmlElementTag($note , 'entry_date' , $ns)->item(0)->nodeValue;
	 			$pfif_note->author_name =  $this->getValueFromXmlElementTag($note , 'author_name' , $ns)->item(0)->nodeValue;
	 			$pfif_note->author_email =  $this->getValueFromXmlElementTag($note , 'author_email' , $ns)->item(0)->nodeValue;
	 			$pfif_note->author_phone =  $this->getValueFromXmlElementTag($note , 'author_phone' , $ns)->item(0)->nodeValue;
	 			$pfif_note->source_date = $this->getValueFromXmlElementTag($note , 'source_date' , $ns)->item(0)->nodeValue;
	 			$pfif_note->found =  $this->getValueFromXmlElementTag($note , 'found' , $ns)->item(0)->nodeValue;
	 			$pfif_note->email_of_found_person = $this->getValueFromXmlElementTag($note , 'email_of_found_person' , $ns)->item(0)->nodeValue;
	 			$pfif_note->phone_of_found_person =  $this->getValueFromXmlElementTag($note , 'phone_of_found_person' , $ns)->item(0)->nodeValue;
	 			$pfif_note->last_known_location =  $this->getValueFromXmlElementTag($note , 'last_known_location' , $ns)->item(0)->nodeValue;
	 			$pfif_note->text =  $this->getValueFromXmlElementTag($note , 'text' , $ns)->item(0)->nodeValue;
	 			
	 			$pfif_person->setNote($pfif_note);	
        	}
        	$this->setPerson($pfif_person);
        }
        
        return true;
        
	}
	
	private function getValueFromXmlElementTag($elementNode , $elementName , $ns){
	    //$person->getElementsByTagNameNS($ns , 'person_record_id')->item(0)->nodeValue;
	    //var_dump('elementName' , $elementName);
	    $nsValue = $elementNode->getElementsByTagNameNS($ns , $elementName);
	    // var_dump('nsValue' , $nsValue->item(0)->nodeValue);
        //print("nsLength = $nsValue->length ");
	    $nonNsValue = $elementNode->getElementsByTagName($elementName);	   
	    // var_dump('nonNsValue' , $nonNsValue->item(0)->nodeValue);
	    if($nsValue->item(0)->nodeValue != null) { // Be aware: both of these could be NULL!
	        return $nsValue;
	    }else{
	        return $nonNsValue;
	    }
	    
	}

    // FIXME (chc 1/31/2010): Only displaying entry_date and text from latest note on LPF screen. Full history is available in stored Person instance.
	public function storeInDatabase(){
	    include_once 'add.inc';

        $skipped = "";
        foreach($this->getPersons() as $person) { 
			unset($_SESSION['mpr_add']['entry']);
			unset($_SESSION['mpr']['entry']);
			unset($_SESSION['mpr_add']['report_person']);
            
            // TBD: see if we already have this person. If yes, then SHOULD only add NOTES content, although
            //          if static info has been modified or is from a different source we need to be able to handle this.
            $lookup = $this->getReportedPerson($person->person_record_id);
            // print "<pre>";var_dump($lookup);print "</pre>";
            /*
                                 * This returns an empty array if uuid not found, or an array indexed by a mixture of integers 
                                 * and column names if uuid is found. Example:
                                *        array(28) {
                                *        [0]=>  string(20) "google.com/person.22"
                                *         ["p_uuid"]=>  string(20) "google.com/person.22"
                                *        [1]=>  string(25) "Yadlay, Brice, Marie-Yves"
                                *         ["full_name"]=>  string(25) "Yadlay, Brice, Marie-Yves"
                                *         [2]=>  string(5) "Cadet"
                                *         ["family_name"]=>  string(5) "Cadet"
                                *         [3]=>  NULL
                                *          ["l10n_name"]=>  NULL
                                *         [4]=>  NULL
                                *        ["idcard"]=>  NULL
                                *         [5]=>  NULL
                                *          ["passport"]=>  NULL
                                *        [6]=>  NULL
                                *          ["drv_license"]=>  NULL
                                *        [7]=>  NULL
                                 *        ["dob"]=>  NULL
                                *         [8]=>  NULL
                                 *        ["physical_comments"]=>  NULL
                                 *         [9]=>  NULL
                                  *       ["height"]=>  NULL
                                 *       [10]=>  NULL
                                 *       ["weight"]=>  NULL
                                 *       [11]=>  NULL
                                 *       ["phone"]=>  NULL
                                 *       [12]=>  NULL
                                 *       ["mobile"]=>  NULL
                                 *       [13]=>  NULL
                                 *       ["email"]=>  NULL
                                 *     }
                                */
            //var_dump('lookup returns:',$lookup);
            if (count($lookup) > 0)
            {
                // Person is already in DB, use update instead of add, although for now just skip
                $skipped .= $person->person_record_id."<br/>";
            //    print "skipping $person->person_record_id<br/>";
                // $continue;
            } else {
            //    print "processing $person->person_record_id<br/>";
			//$person = new Pfif_Person();			 
			$_SESSION['mpr_add']['entry']['p_uuid'] = $person->person_record_id;

            // This should be the date cloned into local repository. The home repository's entry_date is in source_date. (chc 1/26/10)
            //$_SESSION['mpr_add']['entry']['p_uuid'] = $person->entry_date;
            $person->entry_date = gmstrftime("%Y-%m-%dT%H:%M:%SZ");

			$_SESSION['mpr_add']['report_person']['rep_full_name'] = $person->author_name;
			$_SESSION['mpr_add']['report_person']['rep_email'] = $person->author_email;
			$_SESSION['mpr_add']['report_person']['rep_phone'] = $person->author_phone;

            //$_SESSION['mpr_add']['entry']['p_uuid'] = $person->source_name;
			//$_SESSION['mpr_add']['entry']['p_uuid'] = $person->source_date;
			//$_SESSION['mpr_add']['entry']['p_uuid'] = $person->source_url;
			// $comments .= "pfif.person/source_name:".$person->source_name."&nbsp;"; // TODO: remove after serialization
			// $comments .= "pfif.person/source_date:".$person->source_date."&nbsp;";
            
            // FIXME (chc 1/31/2010): href is being concatenated with base URL - make it a text entry for now. In any event, removing from comment due to LPF space limitations
			// $comments .= "source_url:<a href='$person->source_url' target='_blank'>".$person->source_url."</a><br/>";
			
			//Static identifying information
			$_SESSION['mpr_add']['entry']['full_name'] = $person->first_name.' '.$person->last_name; // LPF searches are on full_name
			$_SESSION['mpr_add']['entry']['family_name'] = $person->last_name;
			$_SESSION['mpr_add']['entry']['loc_select_3'] = $person->home_city;
			$_SESSION['mpr_add']['entry']['loc_select_2'] = $person->home_state;
			//$_SESSION['mpr_add']['entry']['p_uuid'] = $person->home_neighborhood; // TODO: coordinate with locations, see Glenn P.
			// FIXME: $comments .= "pfif.person/home_neighborhood:".$person->home_neighborhood."<br/>";

			$_SESSION['mpr_add']['entry']['address'] = $person->home_street.", ".$person->home_city.", ".$person->home_state;
			$_SESSION['mpr_add']['entry']['zip'] = $person->home_zip;

			if (!empty($person->photo_url))
            {
                // error_log("Found photo for ".$person->person_record_id." at ".$person->photo_url);
                /*
                                    * TODO: chc 1/27/10 : Need to transform photo_url to 
                                    *      entry[ {image, image_type, image_height, image_width, url} ] (need to mod add_inc:l891)
                                    *  in order for add_inc to save into DB. If store succeeds, the photo_url can is inserted as
                                    *  'url', otherwise the image will have to be cached locally, a null image and the local URL inserted.
                                    *  In the latter case, and in the case where we can't resolve the photo_url to a supported
                                    *  image, the photo_url will be available in comments.
                                    */
                include_once('webimage.inc');
                $image = new WebImage($person->photo_url, $person->person_record_id);
                // error_log("new WebImage() returns:".var_export($image,true));
                if ($image->is_initialized()){
                    // error_log("image type: $image->type width: $image->width height; $image->height");
                    $_SESSION['mpr']['entry']['image_type'] = $image->type;
                    $_SESSION['mpr']['entry']['image_height'] = $image->height;
                    $_SESSION['mpr']['entry']['image_width'] = $image->width;
                    $_SESSION['mpr']['entry']['url'] = $image->url;
                    $_SESSION['mpr']['entry']['image'] = $image->image;
                } else { // TODO: Note that add.inc:shn_mpr_addmp_commit() is going to insert an empty image record 
                    // TODO: should we stuff the URL so it can be retried later? (chc 2/1/2010)
                    error_log("shn_mod_mpr_WebImage:GET image failed for ".$person->person_record_id." from ".$person->photo_url);
                    $comments .= "photo_url:<a href='$person->photo_url'target='_blank'>".$person->photo_url."</a><br/>"; // FIXME: displayed URL is invalid
                }
            } else {
                // error_log("no photo for ".$person->person_record_id);
            }
            
			//$_SESSION['mpr_add']['entry']['p_uuid'] = $person->other;	
			$comments .= "pfif.person/other:".$person->other."<br/>";

            // TODO: chc 1/25/2010 : Need to get content from NOTE to insert in comments. This only updates
            //                                           the person's status based on the last note.
            $note = $person->getNoteLatest();
            // $msg = print_r($note,true);
            // error_log("Got latest note:".$msg);
			
            // chc 1/22/2010 : require explicit true,  since if no note or empty found tag this was defaulting to 'ali'
			// FIXME (chc 1/31/2010): Scan text for 'alive', 'well', 'dead', 'injured', 'hurt', etc and refine status as possible -
            //                                    use 'unk' for can't determine status at all, 'fou' for found, but health status indeterminate, 
            //                                    -- what is code for 'deceased' - is 'inj' correct for injuerd?
            if($note->found == 'true'){
			    $_SESSION['mpr_add']['entry']['opt_status'] = 'ali';			    
			}else{
			    $_SESSION['mpr_add']['entry']['opt_status'] = 'mis';
			}

            // TODO: for PFIF 1.2 can determine more granular health status
            $_SESSION['mpr_add']['entry']['phone'] = $note->phone_of_found_person;
            $_SESSION['mpr_add']['entry']['last_seen'] = $note->last_known_location;
            //$note->text;
            
			$comments = "last update:".$note->entry_date; // chc 1/31/2010 : date tage last note for display on LPF wall
			$comments .= ':'.$note->text.'&nbsp;';
            $comments .= (!empty($note->last_known_location)) ? '<br/>last seen:'.$note->last_known_location : '';
            $comments .= (!empty($note->email_of_found_person)) ? '<br/>email:'.$note->email_of_found_person : '';
            $comments .= (!empty($note->phone_of_found_person)) ? '<br/>phone:'.$note->phone_of_found_person : '';
            
            // Save full Person record in description as a comment for now.
            $comments .= '<!-- '.base64_encode(serialize($person)).' -->';
            // DEBUG: print "comments:".$comments;
            
            $_SESSION['mpr_add']['entry']['comments'] = $comments;
            
            try{
                // $dbparams = print_r($_SESSION['mpr_add'],true);
                //DEBUG: error_log("storing:".$dbparams);
                // $image_params = $_SESSION['mpr']['entry'];
                // unset($image_params['image']);
                // error_log("image params:".print_r($image_params,true));
                shn_mpr_addmp_commit();
            }
            catch(Exception $e ){
                print $e->getMessage();
                error_log('shn_mod_mpr_pfif.storeInDatabase:'.$e->getMessage());
                return false;
            }
          }
		}
        unset($person);
        if ($skipped != "")
        {
            print "The following record ids were omitted:<br/>".$skipped;
        }
		return true;
	}
    
	public function loadFromDatabase($status, $since_entry_date = null){
		global $conf;
		global $global;
		include_once $global['approot'] . "/inc/lib_uuid.inc";
        require_once $global['approot'] . 'mod/mpr/pfifconf.inc.php';
		
        $baseUuid = $conf['base_uuid'];
		$baseUrl = $pfif_conf['local_domain']; // $_SERVER['HTTP_HOST'];
        
		$personRecords = $this->getPersonFromDb($status, $since_entry_date);
        // TODO: until entry_date filter implement in get... need to filter it here
  		foreach($personRecords as $key =>$personRecord){
            // Get the PFIF history record
            $sourcePfif = $this->getSourcePfif($personRecord); // Leave it up to method to determine what info is needed.
            
/* DEBUG
            if (!$sourcePfif) {
                error_log("No source PFIF record found for ".$personRecord['p_uuid']." with key ".$key);
                error_log('personRecord: '.var_export($personRecord,true));
                // print 'personRecord: '.var_export($personRecord,true);
            }
*/
            
            $reporter = $this->getReportedPerson($personRecord['reporter']); // FALSE if this person originated in this LPF instance
  			$personRecord['reporter_record'] = $reporter;  		

  			//populate Persons
  			$person = new Pfif_Person(); 

            // Prepend repository id if locally created record, otherwise use p_uuid as is. (TODO: Do we need additional validation ?) 
            $p_uuid = $personRecord['p_uuid'];
            $id_prefix = (stripos($p_uuid,$baseUuid) === 0) ? $baseUrl .'/' : '';
	  		$person->person_record_id = $id_prefix.$p_uuid;

	  		$person->entry_date =  $personRecord['updated_time']; // TODO: Which table is this from? 
	  		$person->author_name = $personRecord['reporter_record']['full_name'];
			$person->author_email = $personRecord['reporter_record']['email'];
			$person->author_phone = $personRecord['reporter_record']['phone'];

            // Spec defines source_ info is for home repository. Use local info only for our own records, otherwise 
            // get from comments (for now). TODO: get original record from archive table. (chc 1/26/10)
			$person->source_name = $sourcePfif ? $sourcePfif->source_name : $baseUrl;
			$person->source_date = $sourcePfif ? $sourcePfif->source_date : $personRecord['updated_time']; //date('Y-m-d\Th:i:s\Z', time());  // *TODO* change time based on timezone should be done . Cant find the original date
			$person->source_url = $sourcePfif ? $sourcePfif->source_url : urlencode( "$baseUrl\index.php?mod=mpr&act=viewmp&id={$personRecord['p_uuid']}" );
			
            // var_dump('PFIF:<pre>',$sourcePfif,'</pre>');
            // print ($sourcePfif ? "havePfif: fi=".$sourcePfif->first_name." ln=".$sourcePfif->last__name : "no pfif: fu=".$personRecord['full_name']." fa=".$personRecord['family_name']."<br/>");
			$person->first_name = $sourcePfif ? $sourcePfif->first_name : $this->shn_full_name_to_first_name($personRecord['full_name'],$personRecord['family_name']);
			$person->last_name = $sourcePfif ? $sourcePfif->last_name : $personRecord['family_name']; // TODO: If family_name NULL assume it is last token of full_name? If so, need to handle first and last name in same block (chc 2/4/10)
			$person->home_city = $sourcePfif ? $sourcePfif->home_city : 'SHOULD BE IMPLEMENTED'; // TODO: get from location_details?
			$person->home_state = $sourcePfif ? $sourcePfif->home_state : 'SHOULD BE IMPLEMENTED'; // TODO: get from location_details?
			$person->home_neighborhood = $sourcePfif ? $sourcePfif->home_neighborhood : 'SHOULD BE IMPLEMENTED'; // TODO:  get ffrom location_details?
			$person->home_street = $sourcePfif ? $sourcePfif->street : $personRecord['address']; // TODO: is address the correct source?
			$person->home_zip = $personRecord['zip']; 
            // TODO: For now, referreing to original source, but that can go away. Need to check existence and if gone, substitue our copy?
			$person->photo_url = $sourcePfif ? $sourcePfif->photo_url : 'SHOULD BE IMPLEMENTED'; // get from image table
			$person->other = $sourcePfif ? $sourcePfif->other :  'SHOULD BE IMPLEMENTED'; // get from person_missing.comments and person_physical.injusries and .comments (and others?) 
			
            /*
                             * IF local DB's status record has an updated date-time later than the latest stored note, Then append this info to the PFIF note history (1.1). 
                             * Otherwise, just emit the notes from the archived PFIF record.
                             */
            if (true) { // FIXME: this lets the last note get sent out. Need to update condition as outlined above.
    			$note = new Pfif_Note();
                // FIXME: This will generate different ID's for the same note every time this record is emitted.
    			$note->note_record_id = $baseUrl.'/'. shn_create_uuid('pfif_note');
    			$note->entry_date = $personRecord['updated_time'];
    			$note->author_name = $personRecord['reporter_record']['full_name'];
    			$note->author_email = $personRecord['reporter_record']['email'];
    			$note->author_phone = $personRecord['reporter_record']['phone'];

                // Same as for person.source_*
    			$note->source_date = $personRecord['updated_time'];

                // TODO: Need to map 'fou', 'unk', etc
    			$note->found = $personRecord['status'] != 'mis' ? 'true' : 'false';

                // TODO: Check specification for whether these should be included when person is missing. Also, note that the
                //              found email/phone are not necessarily the same as the person's home info. How, if at all, is this
                //              captured in Sahana? (1/31/10: captured in contact table. Only include if found - 1.1.)
                if ($note->found == "true") {
        			$note->email_of_found_person = $personRecord['email'] ;
        			$note->phone_of_found_person = $personRecord['phone'] ;
                }
    			$note->last_known_location = $personRecord['last_seen'] ;
    			$note->text = 'SHOULD BE IMPLEMENTED'; // get from person_status.comments;
			}
            $person->setNote($note);
			
  			$this->setPerson($person);
  		}		
	}
	
    // TODO: Need to account for 'fou' and 'unk' statuses, limit search by date
	private function getPersonFromDb( $status = 'missing', $since_entry_date = null){
			global $global;
			
			$where = array();
            $id_check = explode('?',$status,2);
            // DEBUG: print "<pre/>".var_export($id_check,true)."</pre>count = ".count($id_check)."<br/>";
			if (count($id_check) == 2 && $id_check[0] == 'id') {
                $where[] = " ps.p_uuid = '$id_check[1]' ";
            }
            else if($status == 'missing'){
				$where[] = " ps.opt_status = 'mis' ";
			}			
			else if($status == 'injured'){
				$where[] = " ps.opt_status = 'inj' ";
			}else if($status == 'deceased'){
				$where[] = " ps.opt_status = 'dec' ";
			}else if($status == 'alive'){
				$where[] = " ps.opt_status = 'ali' ";
			}else {
				$where[] = " ps.opt_status = 'unk' OR ps.opt_status IS NULL ";
			}
            
            // TODO: incorporate since_entry_date into WHERE to support incremental exports
						
	        foreach($where as $whereElement){
           		$whereSql .= ($whereSql==null ?'':' AND ') . $whereElement;
        	}
        	$whereSql = $whereSql != null ? ' WHERE '. $whereSql : '';
			
			// DEBUG: error_log("getPersonFromDb: ".$status." \$whereSql = ".$whereSql);
            
		    $sql = "SELECT a.p_uuid , a.full_name, a.family_name, a.l10n_name, b.serial as idcard, c.serial as passport, d.serial as drv_license, e.birth_date as dob, f.comments as physical_comments, f.height, f.weight, g.contact_value as phone, h.contact_value as mobile, i.contact_value as email,
            j.address, j.postcode as zip, k.last_seen, k.last_clothing, k.comments , pr.rep_uuid as reporter , ps.updated as updated_time , ps.opt_status as status
		FROM person_uuid a        
		LEFT OUTER JOIN identity_to_person b ON b.p_uuid = a.p_uuid AND
		b.opt_id_type = 'nic'
		LEFT OUTER JOIN identity_to_person c ON c.p_uuid = a.p_uuid AND
		c.opt_id_type = 'pas'
		LEFT OUTER JOIN identity_to_person d ON d.p_uuid = a.p_uuid AND
		d.opt_id_type = 'dln'
		LEFT OUTER JOIN person_details e ON e.p_uuid = a.p_uuid
		LEFT OUTER JOIN person_physical f ON f.p_uuid = a.p_uuid
		LEFT OUTER JOIN contact g ON g.pgoc_uuid = a.p_uuid 
        AND g.opt_contact_type = 'curr'
		LEFT OUTER JOIN contact h ON h.pgoc_uuid = a.p_uuid 
        AND h.opt_contact_type = 'cmob'
		LEFT OUTER JOIN contact i ON i.pgoc_uuid = a.p_uuid 
        AND i.opt_contact_type = 'emai'
		LEFT OUTER JOIN location_details j ON j.poc_uuid = a.p_uuid
		RIGHT OUTER JOIN person_missing k ON k.p_uuid = a.p_uuid
        RIGHT JOIN person_status ps ON ps.p_uuid = a.p_uuid        
        RIGHT JOIN person_to_report pr ON pr.p_uuid = a.p_uuid
        $whereSql "  ;
		    
  		$array = $global['db']->GetAll($sql);
  		return $array;
	}
	
	private function getReportedPerson($p_uuid){
		global $global;
		$sql = "SELECT a.p_uuid , a.full_name, a.family_name, a.l10n_name, b.serial AS idcard, c.serial AS passport, d.serial AS drv_license, e.birth_date AS dob, f.comments AS physical_comments, f.height, f.weight, g.contact_value AS phone, h.contact_value AS mobile, i.contact_value AS email
		FROM person_uuid a
		LEFT OUTER JOIN identity_to_person b ON b.p_uuid = a.p_uuid
		AND b.opt_id_type = 'nic'
		LEFT OUTER JOIN identity_to_person c ON c.p_uuid = a.p_uuid
		AND c.opt_id_type = 'pas'
		LEFT OUTER JOIN identity_to_person d ON d.p_uuid = a.p_uuid
		AND d.opt_id_type = 'dln'
		LEFT OUTER JOIN person_details e ON e.p_uuid = a.p_uuid
		LEFT OUTER JOIN person_physical f ON f.p_uuid = a.p_uuid
		LEFT OUTER JOIN contact g ON g.pgoc_uuid = a.p_uuid
		AND g.opt_contact_type = 'curr'
		LEFT OUTER JOIN contact h ON h.pgoc_uuid = a.p_uuid
		AND h.opt_contact_type = 'cmob'
		LEFT OUTER JOIN contact i ON i.pgoc_uuid = a.p_uuid
		AND i.opt_contact_type = 'emai'
        WHERE a.p_uuid = '$p_uuid' "  ;
		
		//print $sql;
  		$array = $global['db']->GetRow($sql);
  		return $array;
	}
	
    /**
            * Gets the original PFIF history for a person
            *
            */
    private function getSourcePfif($person) {
        // print "<pre>".var_export($person,'true')."</pre/>";

        $pfif_person = false; // The return variable

        // For now, extract cached PFIF history from $reson_missing.comments column
        // Locate coment field, and deserialize embedded Person instance
        $comments = $person['comments'];
        $pStart = stripos($comments,'<!--');
        $pEnd = stripos($comments,'-->',$pStart);
        // print "<br/>found person between $pStart and $pEnd <br/>";
        
        if ($pStart > 0 && $pEnd > $pStart) {
            $pString = substr($comments,$pStart+5,$pEnd-$pStart-6);
        // error_log('source string:'.$pString.':EOS');
            $pfif_person = unserialize(base64_decode($pString));
        }
        
        return $pfif_person;
    }

    /**
            * Gets the first name from a Sahana full name.
            *
            */
    private function shn_full_name_to_first_name($full_name,$family_name) {
        $first_name = '';
        if (!isset($family_name)) {
           print("family_name is not set! <br/>");
            $parts = explode(' ',$full_name);
            $c = count($parts);
            $family_name = $c > 0 ? $parts[$c - 1] : '';
        }
        $first_name = str_replace(' '.$family_name,'',$full_name);
        print "replacing ".$family_name." with null in ".$full_name." to yield first_name = ".$first_name."<br/>";

        return $first_name;
    }
}