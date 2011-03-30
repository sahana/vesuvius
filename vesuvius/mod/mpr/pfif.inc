<?php
/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Nilushan Silva
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */

// PFIF 1.1

$failed_images = null;
include_once('pfif_util.inc.php');
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
            $dtz = date_default_timezone_get();
            date_default_timezone_set('UTC');
            $latest_date = strtotime("1970-01-01T00:00:01Z");
            $latest_note = 0;
            foreach ($this->notes as $i =>$next_note) {
                $comp_date = strtotime($next_note->source_date); // chc 2/19/2010 : change entry_date to source_date per PFIF ec.
                if ($comp_date > $latest_date) {
                    $latest_date = $comp_date;
                    $latest_note = $i;
                }
            }
            date_default_timezone_set($dtz);
            return $this->notes[$latest_note];
	    } else {
            return false;
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
// TODO: chc 8/22/10 : double check person import accounting. Added error count fields to pfif_info so that
//                     pfif_person_count represents the total persons imported
//                     pfif_insert_errors = number of imports that failed on insert
//                     pfif_person_updates = number of imports that were updates
//                     pfif_update_errors = number of updates that failed on insert
//                     TODO: shouldn't person_count be reduced by the number of updates and errors?
//                     TODO: repository total should reflect #persons stored, right?
class Pfif{

	public $personArray = array(); // v1.1 or v1.2 with nested notes
    // public $noteArray = array();  // v1.2 independent notes
    // private $pfif_version = null;
	private  $dom_pfif;
	private  $pfif_conf = array();

	public function __construct(){

	}

    public function setPfifConf($incident_id, $config_array) {
        $this->pfif_conf = $config_array;
        $incident = $incident_config['incident_id'];
        if (!empty($incident_id)) {
            $_SESSION['user_pref_ims_incident_id'] = $incident_id;
        }
    }

/*  v1.2
           public function setVersion($v) {
                $this->pfif_version = $v;
         }

         public function getVersion( {
                return $this->pfif_version;
         }
*/
	public function setPerson(Pfif_Person $person){
		$this->personArray[] =  $person;
        // error_log("Set $person->person_record_id ...");
	}
/* v1.2
	public function setPerson(Pfif_Person $note){
		$this->noteArray[] =  $note;
        // error_log("Set $note->note_record_id ...");
	}
    */
	public function getPersons(){
		return $this->personArray;
	}

/* v1.2
	public function getNotes(){
		return $this->noteArray;
	}  */

	private function createXmlElement($domElement, $property , $value){
		if (!empty($value)) {
            // $child = $this->dom_pfif->createElement($property, $value);
            // FIXME: 3/10/10 chc experimental
            $child = $this->dom_pfif->createElement($property);
            $text = $this->dom_pfif->createTextNode($value);
            $child->appendChild($text);
            $domElement->appendChild($child);
        }
	}

    private function check_init() {
        if (empty($this->pfif_conf)) {
            throw new RuntimeException("PFIF Configuration not set");
        } else if (empty($_SESSION['user_pref_ims_incident_id'])) {
            throw new RuntimeException("No incident set in \$_SESSION['user_pref_ims_incident_id']");
        }

        return true;
    }

    // Count number of entries with same entry_date
    // This is needed when performing incremental harvests so
    // that previously harvested records can be skipped.
    private function reset_log_dates($entry_date) {
    global $first_entry_date, $last_entry_date, $last_entry_count;

        $first_entry_date = $entry_date; // Save first entry date from source repository
        $last_entry_date = $first_entry_date;
        $last_entry_count = 0;
    }

    private function update_log_dates($entry_date) {
    global $first_entry_date, $last_entry_date, $last_entry_count;

        if ($entry_date == $last_entry_date) {
            $last_entry_count += 1;
        } else {
            $last_entry_date = $entry_date;
            $last_entry_count = 1;
        }
    }

    private function save_log_dates() {
    global $first_entry_date, $last_entry_date, $last_entry_count;

         $_SESSION['pfif_info']['first_entry'] = $first_entry_date;
        $_SESSION['pfif_info']['last_entry'] = $last_entry_date;
        $_SESSION['pfif_info']['last_entry_count'] = $last_entry_count;
    }
    /**
            *
            *  Returns a PFIF compliant XML document containind person and note records in this PFIF instance.
            *
            *  @todo Need to add a top level note processing loop. (See loadFromXML for details.)
            *
            */
	public function storeInXML($ver='1.2',$test=''){
    global $first_entry_date, $last_entry_date, $last_entry_count;

        $this->check_init();

        $emit1dot2 = ($ver == PFIF_V_1_2) ? true : false;

		$this->dom_pfif = new DomDocument('1.0', 'utf-8');
		$dom_pfif = $this->dom_pfif->createElement('pfif:pfif');
        $dom_pfif->setAttribute('xmlns:pfif', 'http://zesty.ca/pfif/'.$ver);
        $dom_pfif->setAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
        $ns = 'http://zesty.ca/pfif/'.$ver;
        $dom_pfif->setAttribute('xsi:schemaLocation', "$ns $ns/pfif-$ver.xsd");
        $this->dom_pfif->appendChild($dom_pfif);

        $pfif_persons = $this->getPersons();
        $this->reset_log_dates($pfif_persons[0]->entry_date);
        foreach($pfif_persons as $person){
                        // Update last_entry_count
            $this->update_log_dates($person->entry_date);
        	$personElement = $this->dom_pfif->createElement('pfif:person');

        	$this->createXmlElement($personElement , 'pfif:person_record_id' , $person->person_record_id.$test);
        	$this->createXmlElement($personElement, 'pfif:entry_date' , utc_date($person->entry_date)); // FIXME: needs to be UTC in 'YYYY-MM-DDThh:mm:ssZ' format

        	$this->createXmlElement($personElement, 'pfif:author_name' , $person->author_name); // FIXME: if empty, see if name can be parsed from author_email (or should this be done in loadFrom DB?) : chc 2/25/2010
            // TODO: Condition output of $email and phone on author's consent.
        	// $this->createXmlElement($personElement, 'pfif:author_email' , $person->author_email);
        	// $this->createXmlElement($personElement, 'pfif:author_phone' , $person->author_phone);

        	$this->createXmlElement($personElement, 'pfif:source_name' , $person->source_name);
        	$this->createXmlElement($personElement, 'pfif:source_date' , utc_date($person->source_date));
        	$this->createXmlElement($personElement, 'pfif:source_url' , $person->source_url);

        	$this->createXmlElement($personElement, 'pfif:first_name' , $person->first_name);
        	$this->createXmlElement($personElement, 'pfif:last_name' , $person->last_name.$test);
        	$this->createXmlElement($personElement, 'pfif:home_city' , $person->home_city);
        	$this->createXmlElement($personElement, 'pfif:home_state' , $person->home_state);
        	$this->createXmlElement($personElement, 'pfif:home_neighborhood' , $person->home_neighborhood);
        	$this->createXmlElement($personElement, 'pfif:home_street' , $person->home_street);
            if ($emit1dot2) {
                $this->createXmlElement($personElement, 'pfif:home_postal_code' , $person->home_zip);
            } else {
            	$this->createXmlElement($personElement, 'pfif:home_zip' , $person->home_zip);
            }

        	$this->createXmlElement($personElement, 'pfif:photo_url' , $person->photo_url);

            /**
                                    * FIXME: 2/25/2010 chc : get these 1.2 elements from the Person class after serialized
                                    * instances have been exported from person_missing.comments to pfif_* tables. For now,
                                    * if version is 1.2 get them from person.other and emit them as separate elements.
                                    */
            $other1dot2 = split_other($person->other,$ver);
            if ($emit1dot2) {
                $this->createXmlElement($personElement,
                                        'pfif:age', $other1dot2['age']); // $person->age;
                $this->createXmlElement($personElement,
                                        'pfif:sex', $other1dot2['sex']); // $person->sex;
                $this->createXmlElement($personElement,
                                        'pfif:date_of_birth', $other1dot2['date_of_birth']); // $person->date_of_birth;
            }
            $this->createXmlElement($personElement,
                                    'pfif:other', $other1dot2['other']); // $person->other;

        	foreach($person->getNotes() as $note){
        		$noteElement = $this->dom_pfif->createElement('pfif:note');
        		$this->createXmlElement($noteElement, 'pfif:note_record_id' , $note->note_record_id.$test);
        		$this->createXmlElement($noteElement, 'pfif:entry_date' , utc_date($note->entry_date));
        		$this->createXmlElement($noteElement, 'pfif:author_name' , $note->author_name);
                // TODO: chc 3/30/10 : A policy decision is required in order to allow these to be emitted without the author's consent,
                //                                       or a software/db mechanism is needed to allow the author to provide consent.
                // $this->createXmlElement($noteElement, 'pfif:author_email' , $note->author_email);
        		// $this->createXmlElement($noteElement, 'pfif:author_phone' , $note->author_phone);
        		$this->createXmlElement($noteElement, 'pfif:source_date' , utc_date($note->source_date));
                $this->createXmlElement($noteElement, 'pfif:found' , $note->found);

                // TODO: chc 3/30/10 : These should only be emitted to trusted parties.
                // $this->createXmlElement($noteElement, 'pfif:email_of_found_person' , $note->email_of_found_person);
        		// $this->createXmlElement($noteElement, 'pfif:phone_of_found_person' , $note->phone_of_found_person);
        		$this->createXmlElement($noteElement, 'pfif:last_known_location' , $note->last_known_location);

                $text1dot2 = split_text($note->text,$ver);
        		if ($emit1dot2) {
                    $prid = $text1dot2[PFIF_1_2_PID];
                    if (!empty($prid))  {
                        $prid .= $test;
                    }
                    $this->createXmlElement($noteElement, 'pfif:person_record_id' , $prid); // $note->person_record_id);
                    $this->createXmlElement($noteElement, 'pfif:linked_person_record_id' , $text1dot2[PFIF_1_2_LPID]); // $note->linked_person_record_id);
                    $this->createXmlElement($noteElement, 'pfif:status' , $text1dot2[PFIF_1_2_STS]); // $note->status);
                }
        		$this->createXmlElement($noteElement, 'pfif:text' , $text1dot2['text']); // $note->text);

        		$personElement->appendChild($noteElement);
        	}
        	$this->dom_pfif->firstChild->appendChild($personElement);
            unset($note);
        }
        unset($person);

        // Update status info
        var_dump("first/last/count:end",$first_entry_date,$last_entry_date,$last_entry_count);
        $this->save_log_dates();
        // print $this->dom_pfif->saveXML();
        return $this->dom_pfif->saveXML();
	}

    // TODO: may need to add logic to support services other than Google.
	public function loadFromService(
                        $id,
                        $service_name = 'googlehaiti') {
        $this->check_init();

        $service_uri = $this->pfif_conf['services'][$service_name]['read_url'];

        $pfif_uri = $service_uri."?id=".$id;
        // print "importing PFIF from $pfif_uri<br/>";

        $loaded = $this->loadFromXML($pfif_uri);
        return $loaded;
    }

    public function postDbToService($id, $svc='google') {
        return $this->postToService('id', $id, $svc);
    }

    public function postXmlToService($xml, $svc='google') {
        return $this->postToService('xml', $xml, $svc);
    }

    public function postFileToService($filename, $svc='google') {
        return $this->postToService('file', $filename, $svc);
    }

	public function postToService( // TODO: do we need to specify version  ??
                            $source_type, // 'id','xml','file'
                            $source_data, // pfif id,  XML string, or file name
                            $service_name = 'googlehaiti') {
        $this->check_init();

        if ($source_type == 'id') {
            $persons = $this->loadFromDatabase('id?'.$id_or_filename);
            $xml = $this->storeInXML();
        } else if ($source_type == 'xml') {
            // TBD: What has to be done with XML input ? Should we validate it?
            $xml = $source_data;
        } else {
            $loaded = $this->loadFromXML($filename);
            $xml = $loaded ? $this->storeInXML() : false;
        }
        print "posting to service $service_name \n";
        if ($xml) {
            $service_config = $this->pfif_conf['services'][$service_name];
            $status = $this->postGoogleItem($service_config, $xml);
        } else {
            $status = "<status:status>Error reading input from $source_type.</status:status>";
        }
        return $status;
    }

    function postGoogleItem($service_config, $item, $item_type='data') {
        // DEBUG:  print "PFIF Configuration:<pre>";print_r($service_config);print "</pre>";
        $service_uri = $service_config['post_url'];

        // TODO: may need to add logic to support services other than Google.
        $auth_key = $service_config['auth_key'];
        $pfif_uri = $service_uri."?key=".$auth_key;
        // $posted = "Posted PFIF from <br/>".htmlentities($xml)."<br/> to $pfif_uri<br/>Status returned:<br/>";
        /*
                        * TODO: Can xml string be POSTed or do we HAVE to use CURL ?
                        * curl -X POST -H 'Content-type: application/xml' --data-binary @your_file.xml \
    http://haiticrisis.appspot.com/api/write?key=your_auth_key
                        * @see http://haiticrisis.appspot.com/developers for response details
                        */
     $ch = curl_init();    /* Create a CURL handle. */
      print "cURL init ".($ch ? "true" : "false")."\n";
      /* Set cURL options. */
      $status = $ch ? curl_setopt($ch, CURLOPT_URL, $pfif_uri) : false;
      print "URL $pfif_uri set ".($status ? "true" : "false")."\n";

      $status &= $status ? curl_setopt($ch, CURLOPT_POST, true) : false;
      print "POST set ".($status ? "true" : "false")."\n";

      $status &= $status ? curl_setopt($ch, CURLOPT_RETURNTRANSFER, true) : false;
      print "RETURNTRANSFER set ".($status ? "true" : "false")."\n";

      $status &= $status ? curl_setopt($ch, CURLOPT_FAILONERROR, true) : false;
      print "FAILONERROR set ".($status ? "true" : "false")."\n";

      $status &= $status ? curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/xml'
      )) : false;
      print "HTTPHEADER set ".($status ? "true" : "false")."\n";

      $status &= $status ? curl_setopt($ch, CURLOPT_POSTFIELDS, $item) : false; // TODO: if item_type= 'file' use @ syntax
      print "POSTFIELDS set ".($status ? "true" : "false")."\n";

      //$status=false; //debug-skip exec

      $result = $status ? curl_exec($ch) : "POST not executed";  /* Execute the HTTP request. */
      if (!$result) {
        $result = curl_error($ch)."\n";
      }
      $result .= print_r(curl_getinfo($ch),true);

      curl_close($ch);           /* Close the cURL handle. */

      return $result;
    }


	public function loadFromXML($capxml){
    global $dummy_node_list;
		$this->dom_pfif = new DOMDocument('1.0', 'utf-8');
        if(isset($capxml)){
            if (stripos($capxml,'<'.PFIF_NS_PREFIX.':') === FALSE) {
                // print "loading from file/url ...\n>".$capxml."<\n with length ".strlen($capxml)."\n";
                $lst = $this->dom_pfif->load($capxml); // load from file or URL
            } else {
                //print "loading from string ...\n";
                $lst = $this->dom_pfif->loadXML($capxml); // load from string
            }
            //print "loadXML status = ".($lst ? "TRUE" : "FALSE")." for\n$capxml\n";
            $this->xpath = new DomXPath($this->dom_pfif);
        }
        set_dummy_node_list($this->dom_pfif); // FIXME: this is a workaround for errors resulting from empty elements. Need to reork the interface between process_persons/process_notes and getValueFromXmlElementTag to eliminate this.

        $ns = $this->dom_pfif->documentElement->lookupnamespaceURI(PFIF_NS_PREFIX); // 'http://zesty.ca/pfif/1.1';

        $is_ver1dot2 = ($ns == PFIF_1_2_NAMESPACE) ? true : false;
        // DEBUG: print('loadFromXML: ns='.$ns.'\n');
        // $this->pfif_version = $is_ver1dot2 ? $PFIF_V_1_2 :  $PFIF_V_1_1;

        $persons = $this->getValueFromXmlElementTag($this->dom_pfif , 'person' , $ns); // $this->dom_pfif->getElementsByTagNameNS( $ns , 'person');
        // $dump = var_export($persons,true);
        // error_log("got persons:".$dump." length = ".$persons->length);

        if ($persons->length > 0) {
            $this->process_persons($persons,$ns,$is_ver1dot2); // TODO: can omit 2nd arg after all 1.2 vars and methos are in place
        }
        $_SESSION['pfif_info']['pfif_person_count']= $persons->length; // FIXME: this is the number of records imported, we need to track how many were successfully stored in the DB as inserts or updates.
                                                                       //        current store logic does not account for this.


        $notes = $is_ver1dot2 ? $this->getTopLevelNotes($this->dom_pfif , 'note' , $ns) : $dummy_node_list; // TBD: does this return nested notes or only top-level notes?
        if ($notes->length > 1 || ($notes->length == 1 && !($notes->item(0)->tagName == MISSING_NODE_TAGNAME ))) {
            // TODO: delete demmy_person and fix process_notes arg list after all 1.2 vars and methods are in place
            $dummy_person = new Pfif_Person();
            $dummy_person->person_record_id = PFIF_NOTE_CONTAINER_ID;
            $this->process_notes($notes,$dummy_person,$ns,$is_ver1dot2);
            $this->setPerson($dummy_person);
        }
        $_SESSION['pfif_info']['pfif_note_count']= $notes->length; // FIXME: this is the number of records imported, we need to track how many were successfully stored in the DB as inserts or updates.
                                                                   //        current store logic does not account for this.

        if ($persons->length + $notes->length == 0)
            return false;
        else
            return true;
	}

    private function process_persons($persons,$ns,$is_ver1dot2) { // TODO: can omit 2nd arg after all 1.2 vars and methos are in place, since available prom $this->getVersion()
    global $pfif_node_cache;

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

            if ($is_ver1dot2) {
                $pfif_person->home_zip=  $this->getValueFromXmlElementTag($person , 'home_postal_code' , $ns)->item(0)->nodeValue;
            } else {
                $pfif_person->home_zip=  $this->getValueFromXmlElementTag($person , 'home_zip' , $ns)->item(0)->nodeValue;
            }

	 		$pfif_person->photo_url=  $this->getValueFromXmlElementTag($person , 'photo_url' , $ns)->item(0)->nodeValue;
	 		$pfif_person->other= $this->getValueFromXmlElementTag($person , 'other' , $ns)->item(0)->nodeValue;
            if ($is_ver1dot2) {
                // TODO: after serialized person objects have been extracted from HEPL DB merge_other with setting of appropriate attributes:
                // $pfif_person->age =
                $age = $this->getValueFromXmlElementTag($person , PFIF_1_2_AGE , $ns)->item(0)->nodeValue;
                // $pfif_person-date_of_birth =
                $dob = $this->getValueFromXmlElementTag($person , PFIF_1_2_DOB , $ns)->item(0)->nodeValue;
                // $pfif_person->sex =
                $sex = $this->getValueFromXmlElementTag($person , PFIF_1_2_SEX , $ns)->item(0)->nodeValue;
                $pfif_person->other .= merge_other($age,$dob,$sex);
            }
            // error_log("Static informaton done ...");

            // Embedded notes are supported in both PFIF 1.1 and 1.2, so lets see if there are any.
        	$notes = $this->getValueFromXmlElementTag($person , 'note' , $ns);
            if ($notes->length > 1 || ($notes->length == 1 && !($notes->item(0)->tagName == MISSING_NODE_TAGNAME )))  {
                $this->process_notes($notes, $pfif_person, $ns, $is_ver1dot2);
            }

        	$this->setPerson($pfif_person);
            $pfif_node_cache[$pfif_person->person_record_id] = $person; // FIXME: temporary hack : should be able to get nodes by person_record_id using XPath
        }
        unset($person);
    }

	private function process_notes($notes, $pfif_person, $ns, $is_ver1dot2) {
        foreach($notes as $note){

            $pfif_note = new Pfif_Note();
            // $pfif_note->pfif_version = $is_ver1dot2 ? $PFIF_V_1_2 :  $PFIF_V_1_1;

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
            if ($is_ver1dot2) {
                // $pfif_note->person_record_id =
                $pr_id = $this->getValueFromXmlElementTag($note , 'person_record_id' , $ns)->item(0)->nodeValue;
                // $pfif_note->linked_person_record_id =
                $lpr_id = $this->getValueFromXmlElementTag($note , 'linked_person_record_id' , $ns)->item(0)->nodeValue;
                // $pfif_not->status=
                $sts = $this->getValueFromXmlElementTag($note , 'status' , $ns)->item(0)->nodeValue;

                $pfif_note->text .= merge_text($pr_id, $lpr_id, $sts);
            }

            if (!empty($pfif_person)) {
                $pfif_person->setNote($pfif_note);
            } else {
                // v1.2: $this->setNote($pfif_note);
            }
        }
        unset($note);

    }

    private function getTopLevelNotes($pfif, $ns) {
        $note_list = $pfif->createElement('top_level_notes');
        $notes = $this->getValueFromXmlElementTag($pfif , 'note' , $ns);
        foreach ($notes as $note) {
            $p =  $note->parentNode;
            if ($p->nodeName != 'pfif:person') {
                $note_list->appendChild($p);
            }
        }
        unset($note);
        return $note_list->getElementsByTagName('*');
    }
    // chc  3/8/2010 : only try nonNs if ns failed. Return a dummy node list if both fail.
    private function getValueFromXmlElementTag($elementNode, $elementName , $ns) {
        global $dummy_node_list;

        $return_value = null;
	    //var_dump('elementName' , $elementName);
	    $nsValue = $elementNode->getElementsByTagNameNS($ns , $elementName);
	    // var_dump('nsValue' , $nsValue); //->item(0)->nodeValue);
        //print("nsLength = $nsValue->length ");
	    if($nsValue->length != 0) { //item(0)->nodeValue != null) { // Be aware: both of these could be NULL!
	        $return_value = $nsValue;
	    }else{
            // Try to get the element without namespace
            $nonNsValue = $elementNode->getElementsByTagName($elementName);
            // var_dump('nonNsValue' , $nonNsValue); // ->item(0)->nodeValue);
	        if ($nonNsValue->length != 0) { // item(0)->nodeValue != null) {
                $return_value = $nonNsValue;
            } else {
                //Create an empty element
                // DEBUG: print "returning dummy_node_list for element $elementName \n";
                $return_value = $dummy_node_list;
            }
	    }

        return $return_value;
	}

    // FIXME (chc 1/31/2010): Only displaying entry_date and text from latest note on LPF screen. Full history is available in stored Person instance.
	public function storeInDatabase(){
    global $conf, $global,$failed_images, $first_entry_date, $last_entry_date, $last_entry_count;
        // $this->check_init(); // FIXME: is this needed? don't think it uses pfif_conf

        include_once 'add.inc';

        $failed_images = array();
        $_SESSION['pfif_info']['person_updates'] = 0;
        $_SESSION['pfif_info']['images_in'] = 0;
        $_SESSION['pfif_info']['images_retried'] = 0;
        $_SESSION['pfif_info']['images_failed'] = 0;
        $pfif_persons = $this->getPersons();
        $this->reset_log_dates($pfif_persons[0]->entry_date);

        error_log("conf check:".$conf['mod_mpr_upload_pic_handler']);
        var_dump("first/last/count:start",$first_entry_date,$last_entry_date,$last_entry_count);
        foreach($pfif_persons as $person) {
			unset($_SESSION['mpr_add']['entry']);
			unset($_SESSION['mpr']['entry']);
			unset($_SESSION['mpr_add']['report_person']);
            $comments = "";

            // TBD: see if we already have this person. If yes, then SHOULD only add NOTES content, although
            //          if static info has been modified or is from a different source we need to be able to handle this.
            //          Proposal on the table is to create a Note that documents the changes.
            $lookup = $this->getReportedPerson($person->person_record_id);
            //var_dump('lookup returns:',$lookup);

            if ($person->person_record_id == PFIF_NOTE_CONTAINER_ID || count($lookup) > 0)
            {
                // This is either a 1.2. note container OR
                // this Person is already in DB, use update instead of add, although for now just skip
                $p_uuid = $this->_pfif_prepare_update($person,$lookup);

                // Update mpr tables
                try{
                    shn_mpr_editmp_commit();
                    $errchk = $global['db']->ErrorMsg();
                    if (!empty($errchk)) {
                        error_log("shn_mod_mpr_pfif.storeInDatabase: shn_mpr_editmp_commit failed for ".$p_uuid." / ".$person->first_name." ".$person->last_name.":".$errchk);
                        $_SESSION['pfif_info']['person_update_errors'] += 1;
                    } else {
                        $_SESSION['pfif_info']['person_updates'] += 1;

                        // Update  pfif_person and pfif_note tables
                        try{
                            $this->shn_mpr_editpfif_commit($person,$p_uuid); // DB error reported by method
                        } catch(Exception $e) {
                            print $e->getMessage();
                            error_log('shn_mod_mpr_pfif.storeInDatabase:'.$e->getMessage());
                        }
                    }
                }
                catch(Exception $e ){
                    print $e->getMessage();
                    error_log('shn_mod_mpr_pfif.storeInDatabase:'.$e->getMessage());
                    $_SESSION['pfif_info']['person_update_errors'] += 1;
                    return false;
                }
            } else {
                // Update last_entry_count (only update for new records)
                $this->update_log_dates($person->entry_date);

                // Map PFIF content into session mpr_add arrays
                $p_uuid = $this->_pfif_prepare_insert($person);

                // Save to mpr tables
                try{
                    shn_mpr_addmp_commit();
                    $errchk = $global['db']->ErrorMsg();
                    if (!empty($errchk)) {
                        error_log("shn_mod_mpr_pfif.storeInDatabase: shn_mpr_addmp_commit failed for ".$p_uuid." / ".$person->first_name." ".$person->last_name.":".$errchk);
                        $_SESSION['pfif_info']['person_insert_errors'] += 1;
                    } else {
                        // Save to  pfif_person and pfif_note tables
                        // FIXME: There is no way for this to succeed no that pfif_xml.p_uuid has a foreign key constraint. (chc 8/22/2010)
                        try{
                            $this->shn_mpr_addpfif_commit($person,$p_uuid); // DB error reported in method
                        } catch(Exception $e) {
                            print $e->getMessage();
                            error_log('shn_mod_mpr_pfif.storeInDatabase:'.$e->getMessage());
                        }
                    }
                }
                catch(Exception $e ){
                    print $e->getMessage();
                    error_log('shn_mod_mpr_pfif.storeInDatabase:'.$e->getMessage());
                    $_SESSION['pfif_info']['person_insert_errors'] += 1;
                    return false;
                }

            }
		}
        unset($person);
        var_dump("first/last/count:end",$first_entry_date,$last_entry_date,$last_entry_count);

        // Update status info
        $this->save_log_dates();

        if (!empty($failed_images))
        {
            $_SESSION['pfif_info']['images_failed'] = count($failed_images);
            // TODO: Implement retry for failed images.
            print "The following photo_url were not retrieved:<br/>\n";
            print_r($failed_images);
        }
		return true;
	}

    // TODO: chc 4/13/10 : Can probably move these into a pfif_helper script.
    private function _pfif_prepare_insert($person) {
        $p_uuid =  $person->person_record_id; // shn_create_uuid();
        $_SESSION['mpr_add']['entry']['p_uuid'] = $p_uuid;

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
        // TODO: Does Sahana support home_country ?
        //$_SESSION['mpr_add']['entry']['p_uuid'] = $person->home_neighborhood; // TODO: coordinate with locations, see Glenn P.
        // FIXME: $comments .= "pfif.person/home_neighborhood:".$person->home_neighborhood."<br/>";

        $_SESSION['mpr_add']['entry']['address'] = $person->home_street.", ".$person->home_city.", ".$person->home_state;
        $_SESSION['mpr_add']['entry']['zip'] = $person->home_zip; // v1.2 = home_postal_code
        fetch_image($person->photo_url,
                    $person->source_name,
                    $person->person_record_id,
                    $person->source_url); // Populates [mpr][entry][image]

        /**
                                * FIXME: 2/25/2010 chc : get these 1.2 elements from the Person class after serialized
                                * instances have been exported from person_missing.comments to pfif_* tables. For now,
                                * if version is 1.2 get them from person.other and emit them as separate elements.
                                */
         $other1dot2 = split_other($person->other,PFIF_V_1_2);
        // TODO: Need to map AGE to 'opt_age_group' := {1,2,3,4,...,100}, DOB to 'dob' only if fully specified.
        $age_info = shn_map_age_from_pfif($other1dot2[PFIF_1_2_DOB], // $person->date_of_birth;
                                          $other1dot2[PFIF_1_2_AGE], // $person->age;
                                          $person->source_date);
        if (!empty($age_info['opt_age_group'])) {
            $_SESSION['mpr']['entry']['opt_age_group'] = $age_info['opt_age_group'];
        }
        if (!empty($age_info['date_of_birth'])) {
            $_SESSION['mpr']['entry']['dob'] = $age_info['date_of_birth'];
        }
        $_SESSION['mpr']['entry']['gender'] = shn_map_gender_from_pfif($other1dot2[PFIF_1_2_SEX]); // $person->sex;
        $person_other = $other1dot2['other'];

        $comments .= !empty($person_other) ? "person/other:".$person_other."<br/>" : '';

        // TODO: chc 1/25/2010 : Need to get content from NOTE to insert in comments.
        //  This only updates the person's status based on the last note.
        $note_elem = '';
        $note = $person->getNoteLatest();
        if ($note) {
            $status = shn_map_status_from_pfif($note);
            $_SESSION['mpr_add']['entry']['opt_status'] = $status; // 'mis';

            if (!empty($note->phone_of_found_person))
                $_SESSION['mpr_add']['entry']['phone'] = $note->phone_of_found_person;
            if (!empty($note->email_of_found_person))
                $_SESSION['mpr_add']['entry']['email'] = $note->email_of_found_person;
            if (!empty($note->last_known_location))
                $_SESSION['mpr_add']['entry']['last_seen'] = $note->last_known_location;

            // Gather entry_date, last_known_location and text if  not empty
            // (Note that note->text may include PFIF1.2 linkage and status info.)
            $note_info = !empty($note->entry_date) ? "updated:".$note->entry_date."&nbsp" : ''; // chc 1/31/2010 : date tag last note for display on LPF wall
            $note_info .= !empty($note->last_known_location) ? '<br/>last seen:'.$note->last_known_location : '<br/>';
            $note_info .= !empty($note->text) ? '&nbsp;note/text:'.$note->text.'&nbsp;' : '';
            $note_elem = strlen($note_info) > 0 ? "&nbsp;<note_info>$note_info</note_info> " : '';
        } else {
            // If no note, set status to unknown.
            $_SESSION['mpr_add']['entry']['opt_status']='unk';            }

        // FIXME: Privacy concern: refer back to source ???

        // TODO: Send to pfif_person and pfif_note tables
        // Save full Person record in description as a comment for now.
        // $comments .= '<!-- '.base64_encode(serialize($person)).' -->';
        // DEBUG: print "comments:".$comments;

        $_SESSION['mpr_add']['entry']['comments'] = $comments.$note_elem;

        return $p_uuid;

    }

    private function _pfif_prepare_update($person,$lookup) {
        $p_uuid =  $person->person_record_id; // shn_create_uuid();
        print "updating $person->person_record_id<br/>\n";
        return $p_uuid;
    }

	public function loadFromDatabase($status, $since_entry_date = null){
        $this->check_init();

		global $conf;
		global $global;
		include_once $global['approot'] . "/inc/lib_uuid.inc";

        $baseUuid = $conf['base_uuid'];
        $pfifDomain = $this->pfif_conf['pfif_domain'];
		$baseUrl = "http://".$this->pfif_conf['disaster_id'].$this->pfif_conf['source_url_domain'];

		$personRecords = $this->getPersonFromDb($status, $since_entry_date);
        $record_count = count($personRecords);
  		foreach($personRecords as $key =>$personRecord){
            // Get the PFIF history record
            $sourcePfif = $this->getSourcePfif($personRecord);

            $reporter = $this->getReportedPerson($personRecord['reporter']); // non-empty array with count()-0 if this person originated in this LPF instance
  			if (count($reporter) > 0) {
                $personRecord['reporter_record'] = $reporter;
            }

  			//populate Persons
  			$person = new Pfif_Person();

            // Prepend repository id if locally created record, otherwise use p_uuid as is.
            $p_uuid = $personRecord['p_uuid'];
            $id_list[] = $p_uuid;
            $id_prefix = (!$sourcePfif && strpos($p_uuid,$pfifDomain)===FALSE) ? $pfifDomain.'/'.$this->pfif_conf['disaster_id'].'.' : '';
	  		$person->person_record_id = $id_prefix.$p_uuid;

	  		$person->entry_date =  $personRecord['updated_time']; // TODO: Check sourcePfif, since person_status.updated may change if status changes.

            if (count($personRecord['reporter_record']) > 0) {
                // error_log("reporter_record is set!");
    	  		$person->author_name = $personRecord['reporter_record']['full_name'];
    			$person->author_email = $personRecord['reporter_record']['email'];
    			$person->author_phone = $personRecord['reporter_record']['phone'];
            } else if (isset($personRecord['author_email'])) {
                $author_info = hepl_parse_email($personRecord['author_email']);
                $person->author_name = !empty($author_info['user']) ? $author_info['user'] : '';
                $person->author_email = !empty($author_info['addr']) ? $author_info['addr'] : '';
            }

            // Spec defines source_ info is for home repository. Use local info only for our own records, otherwise
            // get from comments (for now). TODO: get original record from archive table. (chc 1/26/10)
			$person->source_name = $sourcePfif ? $sourcePfif->source_name : $baseUrl;
			$person->source_date = $sourcePfif ? $sourcePfif->source_date
                                            : $personRecord['updated_time'];
			$person->source_url = $sourcePfif ?
                                    $sourcePfif->source_url :
                                    $baseUrl."/inw/details.php?uuid=".
                                    (empty($id_prefix) ?
                                            $personRecord['p_uuid'] :
                                            $p_uuid);

            // TODO: combine name methods into single method returning array('first','last');
			$person->first_name = $sourcePfif ?
                    $sourcePfif->first_name :
                    shn_full_name_to_first_name(
                                    $personRecord['full_name'],
                                    $personRecord['family_name']);

			$person->last_name = $sourcePfif ?
                    $sourcePfif->last_name :
                    shn_determine_last_name(
                                    $personRecord['full_name'],
                                    $personRecord['family_name']);

			$person->home_city = $sourcePfif ? $sourcePfif->home_city : ''; // TODO: get from location_details?
			$person->home_state = $sourcePfif ? $sourcePfif->home_state : ''; // TODO: get from location_details?
			$person->home_neighborhood = $sourcePfif ? $sourcePfif->home_neighborhood : ''; // TODO:  get ffrom location_details?
			$person->home_street = $sourcePfif ? $sourcePfif->street : $personRecord['address']; // TODO: is address the correct source?
			$person->home_zip = $personRecord['zip'];
            // TODO: For now, referreing to original source, but that can go away. Need to check existence and if gone, substitue our copy?

			if ($sourcePfif) {
                $person->photo_url = $sourcePfif->photo_url;
				$person->other = $sourcePfif->other;
			} else {
                $photo_url = $personRecord['image_url'];
                $person->photo_url = $photo_url[0] == '/' ? $baseUrl.$photo_url : $photo_url; // some PL images have http://hostname other's are webroot-relative
            }
            /**
                                    * FIXME: 2/25/2010 chc : add these 1.2 elements to the Person class after serialized
                                    * instances have been exported from person_missing.comments to pfif_* tables. For now,
                                    * stuff them in other and let storeInXml determine how to emit them.
                                    */
            $person->other .= PFIF_1_2_OPEN_TAG;
            $gender = shn_map_gender_to_pfif($personRecord, $sourcePfif);
            if (!empty($gender)) {
                $person->other .= PFIF_1_2_SEX.':'.$gender.' ';
            }
			$age = shn_map_age_to_pfif($personRecord, $sourcePfif);
            if (!empty($age)) {
                $person->other .= PFIF_1_2_AGE.':'.$age;
            }
            $person->other .= PFIF_1_2_CLOSE_TAG;

			$add_comments = $personRecord['physical_comments'];
			$person->other .= !empty($add_comments) ? "shn_physical_detail:".$add_comments : '';

            /*
                             * IF local DB's status record has an updated date-time later than the latest stored note, Then append this info to the PFIF note history (1.1).
                             * Otherwise, just emit the notes from the archived PFIF record.
                             */
            $previous_note = $sourcePfif ? $sourcePfif->getNoteLatest() : null;
            // var_dump("PREVIOUS NOTE",$previous_note);
            if ($this->is_note_updated($previous_note, $personRecord)) { // FIXME: this lets the last note get sent out. Need to update condition as outlined above.
                print "note updated, creating new note ...\n";
    			$note = new Pfif_Note();
                // FIXME: This will generate different ID's for the same note every time this record is emitted.
    			$note->note_record_id = $pfifDomain.'/'.$this->pfif_conf['disaster_id'].'.'.shn_create_uuid('note');
    			$note->entry_date = $personRecord['updated_time'];

                if (count($personRecord['reporter_record']) > 2) {
        			$note->author_name = $personRecord['reporter_record']['full_name'];
        			$note->author_email = $personRecord['reporter_record']['email'];
        			$note->author_phone = $personRecord['reporter_record']['phone'];
                } else if (isset($personRecord['author_email'])) {
                    // TODO: Is this always true ?
                    print "using person author info for note\n";
                    $note->author_name = $person->author_name;
                    $note->author_email = $person->author_email; // $personRecord['author_email'];
                }

                // Same as for person.source_*
    			$note->source_date = $personRecord['updated_time'];

                $note->found = shn_map_status_to_pfif(
                                           $personRecord['status'],
                                           $personRecord['isvictim'],
                                           '1.1'); // true or false
                // $note->
                $status = shn_map_status_to_pfif(
                                           $personRecord['status'],
                                           $personRecord['isvictim'],
                                           '1.2');

                // TSpecification dictates that these  be included only if person isfound.
                if ($note->found == "true") {
        			$note->email_of_found_person = $personRecord['email'] ;
        			$note->phone_of_found_person = $personRecord['phone'] ;
                }

                // FIXME: Temporary hack for Feb HEPL export
                $loc = $personRecord['last_seen'];
                if (empty($loc)) {
                    $tmp = hepl_parse_name($personRecord['full_name']);
                    $loc = $tmp['last_seen'];
                }
    			$note->last_known_location = $loc;
    			$note->text = $this->getCommentText($personRecord,$sourcePfif); // TODO: Replace with reference to pfif_note table.
                $note->text .= merge_text(null,null,$status);
            } else {
                // Use latest note
                print "Reusing previous note ...\n";
                $note = $previous_note;
			}
            $person->setNote($note);

  			$this->setPerson($person);
  		}
        unset($personRecord);
        // print_r($id_list);
        if ($personRecords != false && $record_count > 0) {
            return $record_count;
        } else {
            return false;
        }
	}


    // TODO: Need to account for 'fou' and 'unk' statuses, limit search by date
    // TODO: Need to filter on incident ID.
	private function getPersonFromDb( $status = 'missing', $since_entry_date = null){
			global $global;

			$where = array();
            // $isLpfQuery = false;
            $id_check = explode('?',$status,2);
            // DEBUG: print "<pre/>".var_export($id_check,true)."</pre>count = ".count($id_check)."<br/>";
            $where[] = " ps.isvictim = '1' ";
			if (count($id_check) == 2 && $id_check[0] == 'id') {
                $where[] = " ps.p_uuid = '$id_check[1]' ";
                // $isLpfQuery = stripos($id_check[1],'HAITI-2') === false ? false : true;
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
			}else if ($status != 'all') {
				$where[] = " ps.opt_status = 'unk' OR ps.opt_status IS NULL ";
			} // omit opt_status condition if status = 'all'

            // TODO: incorporate since_entry_date into WHERE to support incremental exports
			if ($since_entry_date != null) {
                $where[] = " ps.updated >= '$since_entry_date' ";
            }
	        foreach($where as $whereElement){
           		$whereSql .= ($whereSql==null ?'':' AND ') . $whereElement;
        	}
        	$whereSql = $whereSql != null ? ' WHERE '. $whereSql : '';
			$mpresRestriction = ' AND NOT l.email_from IS NULL';
			// DEBUG:  error_log("getPersonFromDb: ".$status." \$whereSql = ".$whereSql);

            // $array = false;
            // if ($isLpfQuery) {
                // DEBUG:
                error_log("calling getMpresRecords(".$whereSql.")");
                $array1 = $this->getMpresPerson($whereSql.$mpresRestriction);
                print "got ".count($array1)." records\n";
            //} else {
                //DEBUG:
                error_log("calling getMprAddedRecords(".$whereSql.")");
                $array2 = $this->getMprAddedRecords($whereSql);
                print "got ".count($array2)." records\n";
            //}
            // DEBUG: error_log("Found:".var_export($array,true));
            if ($array1 !== false && $array2 !== false) {
                return array_merge($array1,$array2);
            } else if ($array1 != false) {
                return $array1;
            } else {
                return $array2;
            }
	}

	private function getMprAddedRecords($whereSql) {
    		global $global;
/*
DEBUGGING: omit identity_to_person from JOIN to avoid long query resulting from mixing MPR and MPRES entries
SELECT after a.l10n_name:  b.serial as idcard, c.serial as passport, d.serial as drv_license,
FROM after peron
		LEFT OUTER JOIN identity_to_person b ON b.p_uuid = a.p_uuid AND
		b.opt_id_type = 'nic'
		LEFT OUTER JOIN identity_to_person c ON c.p_uuid = a.p_uuid AND
		c.opt_id_type = 'pas'
		LEFT OUTER JOIN identity_to_person d ON d.p_uuid = a.p_uuid AND
		d.opt_id_type = 'dln'
*/
		    $sql = "SELECT a.p_uuid , a.full_name, a.family_name, a.l10n_name, e.birth_date as dob, e.opt_age_group, e.opt_gender, f.comments as physical_comments, f.height, f.weight, g.contact_value as phone, h.contact_value as mobile, i.contact_value as email,
            j.address, j.postcode as zip, k.last_seen, k.last_clothing, k.comments , pr.rep_uuid as reporter , ps.updated as updated_time , ps.opt_status as `status`, im.url as image_url
		FROM person_uuid a
		LEFT OUTER JOIN person_details e ON e.p_uuid = a.p_uuid
		LEFT OUTER JOIN person_physical f ON f.p_uuid = a.p_uuid
		LEFT OUTER JOIN contact g ON g.pgoc_uuid = a.p_uuid
        AND g.opt_contact_type = 'curr'
		LEFT OUTER JOIN contact h ON h.pgoc_uuid = a.p_uuid
        AND h.opt_contact_type = 'cmob'
		LEFT OUTER JOIN contact i ON i.pgoc_uuid = a.p_uuid
        AND i.opt_contact_type = 'emai'
		LEFT OUTER JOIN location_details j ON j.poc_uuid = a.p_uuid
        LEFT OUTER JOIN image im ON a.p_uuid = im.x_uuid
		RIGHT OUTER JOIN person_missing k ON k.p_uuid = a.p_uuid
        RIGHT JOIN person_status ps ON ps.p_uuid = a.p_uuid
        RIGHT JOIN person_to_report pr ON pr.p_uuid = a.p_uuid
        $whereSql "  ;

        // DEBUG:  error_log("getMprAddedRecords: ".$sql);
		// print "callinb db ...\n";
  		$array = $global['db']->GetAll($sql);
        // print "returning ...\n";
        // var_dump($array);
  		return $array;
    }

	private function getMpresPerson($where_uuid) {
		global $global;

       $sql = "SELECT p.p_uuid,p.full_name,p.family_name,
       d.opt_age_group,d.opt_gender,d.years_old,
       m.last_seen,m. comments,
       ps.opt_status as `status`,ps.updated as updated_time,ps.isvictim,
       l.email_from as author_email, l.update_time, i.url as image_url
       FROM person_uuid p
       LEFT OUTER JOIN person_details d USING (p_uuid)
       LEFT OUTER JOIN mpres_log l USING (p_uuid)
       LEFT OUTER JOIN image i ON p.p_uuid = i.x_uuid
       RIGHT OUTER JOIN person_missing m ON m.p_uuid = p.p_uuid
       RIGHT JOIN person_status ps ON ps.p_uuid = p.p_uuid
        $where_uuid ";

       /* $sql = "SELECT p.p_uuid,p.full_name,p.family_name,
       d.opt_age_group,d.opt_gender,d.years_old,
       m.last_seen,m. comments,
       ps.opt_status as `status`,ps.updated as updated_time,ps.isvictim,
       l.email_from as author_email, l.update_time, i.url as image_url
       FROM mpres_log l
       LEFT JOIN person_status ps ON ps.p_uuid = l.p_uuid
       LEFT OUTER JOIN person_details d ON d.p_uuid = l.p_uuid
       LEFT OUTER JOIN image i ON l.p_uuid = i.x_uuid
       LEFT OUTER JOIN person_uuid p ON p.p_uuid = l.p_uuid
       RIGHT OUTER JOIN person_missing m ON m.p_uuid = l.p_uuid
        $where_uuid ";
        */

		//print $sql;
        // DEBUG:  error_log("getMpresPerson: ".$sql);

  		$array = $global['db']->GetAll($sql);
        if ($array === false) {
            error_log("Query ERROR:".$global['db']->_errorMsg);
        }
        // error_log("Got ".count($array)." records");
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
            * Stores imported and internally generated PFIF  records in PFIF tables.
            *
            */
    private function shn_mpr_addpfif_commit($person, $p_uuid) {
    global $global,$pfif_node_cache;
        // Get source version
        $ns = $this->dom_pfif->documentElement->lookupnamespaceURI(PFIF_NS_PREFIX); // 'http://zesty.ca/pfif/1.1';

        // Map $person fields to pfif_xml table (xml_id auto-assigned)
        $insert_array = array();
        $insert_array['p_uuid'] = $p_uuid;
        $insert_array['type'] = 'person';
        $insert_array['pfif_version'] = ($ns == PFIF_1_2_NAMESPACE) ? PFIF_V_1_2 : PFIF_V_1_1;
        $insert_array['src_repository_id'] = '1'; // TODO: how obtained?
        $insert_array['entry_date'] = $person->entry_date;
        $person_node = $pfif_node_cache[$person->person_record_id];
        // var_dump('saving',$p_uuid,' node ',substr($person_node,0,40));
        $insert_array['document'] = mysql_real_escape_string($this->dom_pfif->saveXML($person_node));
        shn_db_insert($insert_array,'pfif_xml',false); // ,'p_uuid'); chc 8/20/10 no longer using p_uuid since it is a foreign key
        $errchk = $global['db']->ErrorMsg();
        if (!empty($errchk)) {
            error_log("Error saving pfif_xml for ".$p_uuid." / ".$person->first_name." ".$person->last_name.":".$errchk);
        }
        unset($pfif_node_cache[$person->person_record_id]);
        $insert_array = null;

        // Update the pfif_log

        return true;
    }
    private function shn_mpr_editpfif_commit($person, $p_uuid) {
    global $global,$pfif_node_cache;
        error_log("shn_mod_mpr_pfif: update for person_id ".$p_uuid." not implemented.");
        return true;
    }
    /**
            *
            * TODO: Check what loadFromDatabase does with person_missing->comments.
            * The next three functions provide access to the unmapped PFIF content stored in person_missing.comments
            * in the following format:
            * "person/other:".<person->other>."<note_info>".["updated:".<note->entry_date>&nbsp;]"<br/>".[last_seen:".<note->last_known_location>].["&nbsp;note/text:".<note->text>["<pfif1.2>person_record_id:... linked_person_record_id:... status: </pfif1.2>].&nbsp;][<!-- serialized person record (haiticrisis 1/28 import only) -->]
            *
            */

    /**
            * Gets the original PFIF history for a person
            *
            */
    //private function getSourcePfif($person) {
    public function getSourcePfif($person) {
    global $global;
        // print "<pre>".var_export($person,'true')."</pre/>";

        $pfif_person = false; // The return variable

        // For now, extract cached PFIF history from $reMsgson_missing.comments column
        // Locate coment field, and deserialize embedded Person instance
        $comments = $person['comments'];
        $pStart = stripos($comments,'<!--');
        $pEnd = stripos($comments,'-->',$pStart);

        if ($pStart > 0 && $pEnd > $pStart) {
            $pString = substr($comments,$pStart+5,$pEnd-$pStart-6);
        // error_log('source string:'.$pString.':EOS');
            $pfif_person = unserialize(base64_decode($pString));
        } else if ($global['db']->MetaColumns('pfif_xml')) {
            // No person in comments, try pfif_xml table if it exists
            $sql = "SELECT `document` FROM `pfif_xml` WHERE `p_uuid` = '".$person['person_record_id']."'";
            print "$sql \n";
            $rs = $global['db']->GetAll($sql);
            if ($rs) {
                $rsxml = "<?xml version='1.0'?>";
                $rsxml .='<pfif:pfif xmlns:pfif="http://zesty.ca/pfif/1.2" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://
zesty.ca/pfif/1.2 http://zesty.ca/pfif/1.2/pfif-1.2.xsd">';
                $rsxml .= $rs[0]['document'];
                $rsxml .= "</pfif:pfif>";
                $pf = new Pfif();
                $pfif_person = $pf->loadFromXML($rsxml);
            }
        }

        return $pfif_person;
    }

   /**
        *
        *  Extracts comment text from the latest NOTE if the source PFIF is available, otherwise
        *  use the persom_missing.comments text (making sure that any serialized Person comments are stripped.
        * (The latter is just for safety in the event the deserialization failed to produce a Person instance in
        *  $source.)
        *
        */
    private function getCommentText($person,$source) {
        $comment_text = "";
        if ($source) {
            $note = $source->getNoteLatest();
            $comment_text = (!empty($note)) ? $note->text : '';
        } else {
            $comments = $person['comments'];
            $pStart = stripos($comments,'<note_info>');
            if ($pStart === FALSE) {
                $comment_text = $comments;
            } else {
                $comment_text =  substr($comments,0,$pStart - 1);
            }
        }

        return $comment_text;
    }

   /**
        *
        *  Extracts comment text from the latest NOTE if the source PFIF is available, otherwise
        *  use the persom_missing.comments text (making sure that any serialized Person comments are stripped.
        * (The latter is just for safety in the event the deserialization failed to produce a Person instance in
        *  $source.)
        *
        */
    private function getNoteText($person,$source) {
        $comment_text = "";
        if ($source) {
            $note = $source->getNoteLatest();
            $comment_text = (!empty($note)) ? $note->text : '';
        } else {
            $comments = $person['comments'];
            $pStart = stripos($comments,'<note_info>');
            if ($pStart === FALSE) {
                $comment_text = $comments;
            } else {
                $comment_text =  substr($comments,0,$pStart - 1);
            }
        }

        return $comment_text;
    }

    /**
            * Returns @code(true) if person status has been updated since the last note. Otherwise, false.
            */
    private function is_note_updated($prev_note,$cur_person) {
        $updated = null;
        if (!empty($prev_note)) {
            $dtz = date_default_timezone_get();
            date_default_timezone_set('UTC');
            $note_time = strtotime($prev_note->entry_date); // Note time is UTC
            $update_time = strtotime($cur_person['update_time']); // DB time is local time
            $updated = $update_time > $note_time ? true : false;
            date_default_timezone_set($dtz);
        } else {
            $updated = true; // no previous note
        }
        return $updated;
    }
}