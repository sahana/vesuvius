<?php
/**
* @package     pfif
* @version      1.1
* @author       Nilushan Silva <>

* LastModified: 2010:0304:2003
* License:      LGPL
* @link         TBD
*/
$failed_images = null;
include_once('tools.inc');
include_once('pfif_util.inc.php');
class Pfif_Person {
	//Meta data
	public $person_record_id;
	public $entry_date;
	public $expiry_date;
	public $author_name;
	public $author_email;
	public $author_phone;
	public $source_name;
	public $source_date;
	public $source_url;

	//Static identifying information
	public $full_name;
	public $first_name;
	public $last_name;
	public $home_city;
	public $home_state;
	public $home_neighborhood;
	public $home_country;
	public $home_street;
	public $home_postal_code;
	public $photo_url;
	public $sex;
	public $date_of_birth;
	public $age;
	public $other;
}

class Pfif_Note {
	public $note_record_id;
        public $person_record_id;
        public $linked_person_record_id;
	public $entry_date;
	public $author_name;
	public $author_email;
	public $author_phone;
	public $source_date;
	public $found;
	public $status;
	public $email_of_found_person;
	public $phone_of_found_person;
	public $last_known_location;
	public $text;
}

class Pfif {
   public $personArray = array();
   public $noteArray = array();
   private $pfif_version = null;    // PFIF version
   private $source_repos_id = null;  // source repository id
   private $pfif_conf = array();
   private $dom_pfif;

   public function __construct() {
   }

   // Set PFIF configuration.
   public function setPfifConf($config_array, $service_name) {
      $this->pfif_conf = $config_array;
      $this->setSourceReposId($config_array['map'][$service_name]);
      $incident_id = $config_array['service_to_incident'][$service_name]['incident_id'];
      if (!empty($incident_id)) {
         $_SESSION['user_pref_ims_incident_id'] = $incident_id;
      }
   }

   public function setVersion($v) {
      $this->pfif_version = $v;
   }

   public function getVersion() {
      return $this->pfif_version;
   }

   public function setSourceReposId($id) {
      $this->source_repos_id = $id;
   }

   public function getSourceReposId() {
      return $this->source_repos_id;
   }

   public function setPerson(Pfif_Person $person) {
      $this->personArray[] = $person;
      //error_log("Set $person->person_record_id ...");
   }

   public function setNote(Pfif_Note $note) {
      $this->noteArray[] = $note;
      //error_log("Set $note->note_record_id ...");
   }

   public function setNotes($notes) {
      $this->noteArray = array_merge($this->noteArray, $notes);
   }

   public function getPersons() {
      return $this->personArray;
   }


   // Return all notes or notes for a specified person.
   public function getNotes($person_record_id='') {
      if (empty($person_record_id)) {
         // Return all notes.
         $notes = $this->noteArray;
      } else {
         // Return notes for this person_record_id.
         $notes = array();
         foreach($this->noteArray as $note) {
            if ($note->person_record_id == $person_record_id) {
               $notes[] = $note;
            }
         }
      }
      return $notes;
   }

   private function createXmlElement($domElement, $property, $value) {
      if (!empty($value)) {
         //$child = $this->dom_pfif->createElement($property, $value);
         $child = $this->dom_pfif->createElement($property);
         // FIXME: createTextNode escapes the text; use alternate approach above if
         // this is not what we want.
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

   // Reset log first entry date to first entry date from source repository.
   private function reset_log_dates($entry_date) {
      global $first_entry_date, $last_entry_date, $last_entry_count;

      $first_entry_date = $entry_date;
      $last_entry_date = $first_entry_date;
      $last_entry_count = 0;
   }

   // Count number of entries with same entry_date
   // This is needed when performing incremental harvests so
   // that previously harvested records can be skipped.
   private function update_log_dates($entry_date) {
      global $first_entry_date, $last_entry_date, $last_entry_count;

      if ($entry_date == $last_entry_date) {
         $last_entry_count += 1;
      } else {
         // Note: last_entry_date should always be greater than entry date.
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
    *  Returns a PFIF-compliant XML document containing person and note records in this PFIF instance.
    */
   public function storeInXML() {
      global $first_entry_date, $last_entry_date, $last_entry_count;

      $this->check_init();

      $this->dom_pfif = new DomDocument('1.0', 'utf-8');
      $dom_pfif = $this->dom_pfif->createElement('pfif:pfif');
      $dom_pfif->setAttribute('xmlns:pfif', 'http://zesty.ca/pfif/1.3');
      $dom_pfif->setAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
      $ns = 'http://zesty.ca/pfif/1.3';
      $dom_pfif->setAttribute('xsi:schemaLocation', "$ns $ns/pfif-1.3.xsd");
      $this->dom_pfif->appendChild($dom_pfif);

      $pfif_persons = $this->getPersons();
      $this->reset_log_dates($pfif_persons[0]->entry_date);
      foreach ($pfif_persons as $person) {
         // Update last_entry_count
         $this->update_log_dates($person->entry_date);
         $personElement = $this->dom_pfif->createElement('pfif:person');
         $this->createXmlElement($personElement, 'pfif:person_record_id', $person->person_record_id);
         $this->createXmlElement($personElement, 'pfif:entry_date', utc_date($person->entry_date));
         $this->createXmlElement($personElement, 'pfif:expiry_date', utc_date($person->expiry_date));
         // FIXME: if empty, see if name can be parsed from author_email (or should this be done in loadFrom DB?) : chc 2/25/2010
         $this->createXmlElement($personElement, 'pfif:author_name', $person->author_name);
         // TODO: Condition output of email and phone on author's consent.
         // $this->createXmlElement($personElement, 'pfif:author_email' , $person->author_email);
         // $this->createXmlElement($personElement, 'pfif:author_phone' , $person->author_phone);
         $this->createXmlElement($personElement, 'pfif:source_name', $person->source_name);
         $this->createXmlElement($personElement, 'pfif:source_date', utc_date($person->source_date));
         $this->createXmlElement($personElement, 'pfif:source_url', $person->source_url);
         $this->createXmlElement($personElement, 'pfif:full_name', $person->full_name);
         $this->createXmlElement($personElement, 'pfif:first_name', $person->first_name);
         $this->createXmlElement($personElement, 'pfif:last_name', $person->last_name);
         $this->createXmlElement($personElement, 'pfif:sex', $person->sex);
         $this->createXmlElement($personElement, 'pfif:age', $person->age);
         $this->createXmlElement($personElement, 'pfif:date_of_birth', $person->date_of_birth);
         $this->createXmlElement($personElement, 'pfif:home_street', $person->home_street);
         $this->createXmlElement($personElement, 'pfif:home_neighborhood', $person->home_neighborhood);
         $this->createXmlElement($personElement, 'pfif:home_city', $person->home_city);
         $this->createXmlElement($personElement, 'pfif:home_state', $person->home_state);
         $this->createXmlElement($personElement, 'pfif:home_country', $person->home_country);
         $this->createXmlElement($personElement, 'pfif:home_postal_code', $person->home_postal_code);
         $this->createXmlElement($personElement, 'pfif:photo_url', $person->photo_url);
         $this->createXmlElement($personElement, 'pfif:other', $person->other);

         // Embed all notes associated with this person.
         $pfif_notes = $this->getNotes($person->person_record_id);
         foreach ($pfif_notes as $note) {
            $noteElement = $this->dom_pfif->createElement('pfif:note');
            $this->createXmlElement($noteElement, 'pfif:note_record_id', $note->note_record_id);
            $this->createXmlElement($noteElement, 'pfif:person_record_id', $note->person_record_id);
            $this->createXmlElement($noteElement, 'pfif:linked_person_record_id', $note->linked_person_record_id);
            $this->createXmlElement($noteElement, 'pfif:entry_date', utc_date($note->entry_date));
            $this->createXmlElement($noteElement, 'pfif:author_name', $note->author_name);
            // A policy decision is required in order to allow these to be emitted without the author's consent,
            // or a software/db mechanism is needed to allow the author to provide consent.
            // $this->createXmlElement($noteElement, 'pfif:author_email' , $note->author_email);
            // $this->createXmlElement($noteElement, 'pfif:author_phone' , $note->author_phone);
            $this->createXmlElement($noteElement, 'pfif:source_date', utc_date($note->source_date));
            $this->createXmlElement($noteElement, 'pfif:found', $note->found);
            $this->createXmlElement($noteElement, 'pfif:status', $note->status);
            $this->createXmlElement($noteElement, 'pfif:last_known_location', $note->last_known_location);
            // These should only be emitted to trusted parties.
            // $this->createXmlElement($noteElement, 'pfif:email_of_found_person' , $note->email_of_found_person);
            // $this->createXmlElement($noteElement, 'pfif:phone_of_found_person' , $note->phone_of_found_person);
            $this->createXmlElement($noteElement, 'pfif:text', $note->text);
            $personElement->appendChild($noteElement);

         }
         $this->dom_pfif->firstChild->appendChild($personElement);
         unset($note);
      }
      unset($person);

      // Update status info
      //var_dump("first/last/count:end", $first_entry_date, $last_entry_date, $last_entry_count);
      $this->save_log_dates();
      // print $this->dom_pfif->saveXML();
      return $this->dom_pfif->saveXML();
   }

   // TODO: may need to add logic to support services other than Google.
   public function loadFromService($id, $service_name = 'googlehaiti') {
      $this->check_init();

      $service_uri = $this->pfif_conf['services'][$service_name]['read_url'];

      $pfif_uri = $service_uri . "?id=" . $id;
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

   public function postToService(
           $source_type, // 'id','xml','file'
           $source_data, // pfif id,  XML string, or file name
           $service_name = 'googlejapan') {
      $this->check_init();

      if ($source_type == 'id') {
         $persons = $this->loadFromDatabase('id?' . $id_or_filename);
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


   // Load PFIF XML data into Pfif_Person classe.
   public function loadPersonsFromXML($capxml) {
      $this->dom_pfif = new DOMDocument('1.0', 'utf-8');
      if (isset($capxml)) {
         if (stripos($capxml, '<' . PFIF_NS_PREFIX . ':') === FALSE) {
            // print "loading from file/url ...\n>".$capxml."<\n with length ".strlen($capxml)."\n";
            $lst = $this->dom_pfif->load($capxml); // load from file or URL
         } else {
            //print "loading from string ...\n";
            $lst = $this->dom_pfif->loadXML($capxml); // load from string
         }
         //print "loadXML status = ".($lst ? "TRUE" : "FALSE")." for\n$capxml\n";
      }

      // FIXME: this is a workaround for errors resulting from empty elements. Need to rework the interface between
      // process_persons/process_notes and getValueFromXmlElementTag to eliminate this.
      set_dummy_node_list($this->dom_pfif);

      $ns = $this->dom_pfif->documentElement->lookupnamespaceURI(PFIF_NS_PREFIX); // 'http://zesty.ca/pfif/1.2';
      // DEBUG: print('loadPersonsFromXML: ns='.$ns.'\n');
      $this->setVersion(($ns == PFIF_1_2_NAMESPACE) ? PFIF_V_1_2 : PFIF_V_1_1);

      $persons = $this->dom_pfif->getElementsByTagNameNS($ns , 'person');
      // $dump = var_export($persons, true);
      // error_log("got persons:".$dump." length = ".$persons->length);
      if ($persons->length > 0) {
         $this->process_persons($persons, $ns);
      }

      return ($persons->length == 0)? false : true;
   }
   // Load PFIF XML data into Pfif_Note classe.
   public function loadNotesFromXML($capxml) {
      $this->dom_pfif = new DOMDocument('1.0', 'utf-8');
      if (isset($capxml)) {
         if (stripos($capxml, '<' . PFIF_NS_PREFIX . ':') === FALSE) {
            // print "loading from file/url ...\n>".$capxml."<\n with length ".strlen($capxml)."\n";
            $lst = $this->dom_pfif->load($capxml); // load from file or URL
         } else {
            //print "loading from string ...\n";
            $lst = $this->dom_pfif->loadXML($capxml); // load from string
         }
         //print "loadXML status = ".($lst ? "TRUE" : "FALSE")." for\n$capxml\n";
      }

      // FIXME: this is a workaround for errors resulting from empty elements. Need to rework the interface between
      // process_persons/process_notes and getValueFromXmlElementTag to eliminate this.
      set_dummy_node_list($this->dom_pfif);

      $ns = $this->dom_pfif->documentElement->lookupnamespaceURI(PFIF_NS_PREFIX); // 'http://zesty.ca/pfif/1.2';
      // DEBUG: print('loadNotesFromXML: ns='.$ns.'\n');
      $this->setVersion(($ns == PFIF_1_2_NAMESPACE) ? PFIF_V_1_2 : PFIF_V_1_1);

      $notes = $this->dom_pfif->getElementsByTagNameNS($ns , 'note');
      if ($notes->length > 0) {
         $this->process_notes($notes, $ns);
      }

      return ($notes->length == 0)? false : true;
   }

   // Extract DOM person data into pif_person.
   // Drop any embedded notes on the floor and process them as a separate feed.
   private function process_persons($persons, $ns) {
      // Get source version
      $ns = $this->dom_pfif->documentElement->lookupnamespaceURI(PFIF_NS_PREFIX); // 'http://zesty.ca/pfif/1.2';

      foreach ($persons as $person) {
         $pfif_person = new Pfif_Person();
         $pfif_person->person_record_id = $this->getValueFromXmlElementTag($person, 'person_record_id', $ns)->item(0)->nodeValue;
         // error_log("processing person:".$pfif_person->person_record_id);
         $pfif_person->entry_date = local_date($this->getValueFromXmlElementTag($person, 'entry_date', $ns)->item(0)->nodeValue);
         $pfif_person->author_name = $this->getValueFromXmlElementTag($person, 'author_name', $ns)->item(0)->nodeValue;
         $pfif_person->author_email = $this->getValueFromXmlElementTag($person, 'author_email', $ns)->item(0)->nodeValue;
         $pfif_person->author_phone = $this->getValueFromXmlElementTag($person, 'author_phone', $ns)->item(0)->nodeValue;
         $pfif_person->source_name = $this->getValueFromXmlElementTag($person, 'source_name', $ns)->item(0)->nodeValue;
         $pfif_person->source_date = local_date($this->getValueFromXmlElementTag($person, 'source_date', $ns)->item(0)->nodeValue);
         $pfif_person->source_url = $this->getValueFromXmlElementTag($person, 'source_url', $ns)->item(0)->nodeValue;
         // error_log("meta-informaton done ...");
         // Static identifying information
         $pfif_person->full_name = $this->getValueFromXmlElementTag($person, 'full_name', $ns)->item(0)->nodeValue;
         $pfif_person->first_name = $this->getValueFromXmlElementTag($person, 'first_name', $ns)->item(0)->nodeValue;
         $pfif_person->last_name = $this->getValueFromXmlElementTag($person, 'last_name', $ns)->item(0)->nodeValue;
         $pfif_person->home_city = $this->getValueFromXmlElementTag($person, 'home_city', $ns)->item(0)->nodeValue;
         $pfif_person->home_state = $this->getValueFromXmlElementTag($person, 'home_state', $ns)->item(0)->nodeValue;
         $pfif_person->home_neighborhood = $this->getValueFromXmlElementTag($person, 'home_neighborhood', $ns)->item(0)->nodeValue;
         $pfif_person->home_street = $this->getValueFromXmlElementTag($person, 'home_street', $ns)->item(0)->nodeValue;
         $pfif_person->home_country = $this->getValueFromXmlElementTag($person, 'home_country', $ns)->item(0)->nodeValue;
         $pfif_person->home_postal_code = $this->getValueFromXmlElementTag($person, 'home_postal_code', $ns)->item(0)->nodeValue;
         $pfif_person->photo_url = $this->getValueFromXmlElementTag($person, 'photo_url', $ns)->item(0)->nodeValue;
         $pfif_person->other = $this->getValueFromXmlElementTag($person, 'other', $ns)->item(0)->nodeValue;
         $pfif_person->age = $this->getValueFromXmlElementTag($person, 'age', $ns)->item(0)->nodeValue;
         $pfif_person->date_of_birth = $this->getValueFromXmlElementTag($person, 'date_of_birth', $ns)->item(0)->nodeValue;
         $pfif_person->sex = $this->getValueFromXmlElementTag($person, 'sex', $ns)->item(0)->nodeValue;
         // error_log("Static informaton done ...");
         $this->setPerson($pfif_person);
      }
      unset($person);
   }

   // Extract DOM note data into pfif_notes.
   private function process_notes($notes, $ns) {
      foreach ($notes as $note) {
         $pfif_note = new Pfif_Note();
         $pfif_note->note_record_id = $this->getValueFromXmlElementTag($note, 'note_record_id', $ns)->item(0)->nodeValue;
         $pfif_note->entry_date = local_date($this->getValueFromXmlElementTag($note, 'entry_date', $ns)->item(0)->nodeValue);
         $pfif_note->author_name = $this->getValueFromXmlElementTag($note, 'author_name', $ns)->item(0)->nodeValue;
         $pfif_note->author_email = $this->getValueFromXmlElementTag($note, 'author_email', $ns)->item(0)->nodeValue;
         $pfif_note->author_phone = $this->getValueFromXmlElementTag($note, 'author_phone', $ns)->item(0)->nodeValue;
         $pfif_note->source_date = local_date($this->getValueFromXmlElementTag($note, 'source_date', $ns)->item(0)->nodeValue);
         $pfif_note->status = $this->getValueFromXmlElementTag($note, 'status', $ns)->item(0)->nodeValue;
         $pfif_note->found = $this->getValueFromXmlElementTag($note, 'found', $ns)->item(0)->nodeValue;
         $pfif_note->email_of_found_person = $this->getValueFromXmlElementTag($note, 'email_of_found_person', $ns)->item(0)->nodeValue;
         $pfif_note->phone_of_found_person = $this->getValueFromXmlElementTag($note, 'phone_of_found_person', $ns)->item(0)->nodeValue;
         $pfif_note->last_known_location = $this->getValueFromXmlElementTag($note, 'last_known_location', $ns)->item(0)->nodeValue;
         $pfif_note->text = $this->getValueFromXmlElementTag($note, 'text', $ns)->item(0)->nodeValue;
         $pfif_note->person_record_id = $this->getValueFromXmlElementTag($note, 'person_record_id', $ns)->item(0)->nodeValue;
         $pfif_note->linked_person_record_id = $this->getValueFromXmlElementTag($note, 'linked_person_record_id', $ns)->item(0)->nodeValue;
         $this->setNote($pfif_note);
      }
      unset($note);
   }

   // chc  3/8/2010 : only try nonNs if ns fails.
   private function getValueFromXmlElementTag($elementNode, $elementName, $ns) {
      global $dummy_node_list;

      $return_value = null;
      //var_dump('elementName' , $elementName);
      $nsValue = $elementNode->getElementsByTagNameNS($ns, $elementName);
      // var_dump('nsValue' , $nsValue); //->item(0)->nodeValue);
      //print("nsLength = $nsValue->length ");
      if ($nsValue->length != 0) { //item(0)->nodeValue != null) { // Be aware: both of these could be NULL!
         $return_value = $nsValue;
      } else {
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

   // Store person (no notes) in database. PFIF 1.3 allows for persons to be reimported when expiration
   // date changes. Specification states they'll also have a new source_date and entry_date.
   public function storePersonsInDatabase() {
      global $conf, $global, $failed_images, $first_entry_date, $last_entry_date, $last_entry_count;

      include_once 'add.inc';

      $failed_images = array();
      $_SESSION['pfif_info']['images_in'] = 0;
      $_SESSION['pfif_info']['images_retried'] = 0;
      $_SESSION['pfif_info']['images_failed'] = 0;
      $pfif_persons = $this->getPersons();
      $this->reset_log_dates($pfif_persons[0]->entry_date);

      //error_log("conf check:" . $conf['mod_mpr_upload_pic_handler']);
      //var_dump("first/last/count at start: ", $first_entry_date, $last_entry_date, $last_entry_count);
      foreach ($pfif_persons as $person) {
         unset($_SESSION['mpr_add']['entry']);
         unset($_SESSION['mpr']['entry']);
         unset($_SESSION['mpr_add']['report_person']);

         // Update last_entry_count.
         $this->update_log_dates($person->entry_date);

         // The shn_* routines don't throw exceptions. So check for duplicate.
         $lookup = $this->checkForReportedPerson($person->person_record_id);
         //var_dump('lookup returns:',$lookup);
         if (count($lookup) > 0) {
            // This is a duplicate person. Check for expiry_date update.
            if (strtotime($person->source_date) != strtotime($lookup['source_date'])) {
               var_dump('Old and new source dates not equal:',$lookup['source_date'],$person->source_date);
               $source_date = local_time($person->source_date);
               $entry_date = strftime("%Y-%m-%d %H:%M:%S")
               $expiry_date = local_time($person->$expiry_date);
               $p_uuid = $lookup['p_uuid'];
               // Update existing person with changed expiration date.
               $sql = "UPDATE person_uuid SET source_date='$source_date', entry_date='$entry_date',expiry_date='$expiry_date'".
                      " WHERE p_uuid='$p_uuid'";
               $st = $global['db']->Execute($sql);
               if($st === false) {
                  $errchk = $global['db']->ErrorMsg();
                  error_log("Error updating expiry_date in person_uuid: ".$errchk);
                  $_SESSION['pfif_info']['person_insert_errors'] += 1;
               }
               $sql = "UPDATE pfif_person SET source_date='$source_date', entry_date='$entry_date',expiry_date='$expiry_date'".
                      " WHERE p_uuid='$p_uuid'";
               if($st === false) {
                  $errchk = $global['db']->ErrorMsg();
                  error_log("Error updating expiry_date in pfif_person: ".$errchk);
                  $_SESSION['pfif_info']['person_insert_errors'] += 1;
               }
            } else {
               // This is an exact duplicate for some reason, so flag it.
               $_SESSION['pfif_info']['person_insert_errors'] += 1;
            }
            // All done with this person.
            continue;
         }

         // Map PFIF content into session mpr_add arrays
         $this->_pfif_prepare_person_insert($person);

         // Save to mpr tables
         try {
            shn_mpr_addperson_commit();
            $errchk = $global['db']->ErrorMsg();
            if (!empty($errchk)) {
               error_log("shn_mod_mpr_pfif.storeInDatabase: shn_mpr_addperson_commit failed for "
                         . $person->person_record_id . ":" . $errchk);
               $_SESSION['pfif_info']['person_insert_errors'] += 1;
               // Interrupt further processing of this person.
               continue;
            } else {
               // Save to pfif_person table.
               try {
                  $this->shn_mpr_addpfifperson_commit($person); // DB error reported in method
               } catch (Exception $e) {
                  print $e->getMessage();
                  error_log('shn_mod_mpr_pfif.storeInDatabase:' . $e->getMessage());
               }
            }
         } catch (Exception $e) {
            print $e->getMessage();
            error_log('shn_mod_mpr_pfif.storeInDatabase:' . $e->getMessage());
            $_SESSION['pfif_info']['person_insert_errors'] += 1;
            return false;
         }
      }
      unset($person);
      //var_dump("first/last/count at end: ", $first_entry_date, $last_entry_date, $last_entry_count);

      // Update status info
      $this->save_log_dates();

      if (!empty($failed_images)) {
         $_SESSION['pfif_info']['images_failed'] = count($failed_images);
         // TODO: Implement retry for failed images.
         print "The following photo_url were not retrieved:<br/>\n";
         print_r($failed_images);
      }

      // Update number of persons actually processed.
      $_SESSION['pfif_info']['pfif_person_count'] = count($pfif_persons)-$_SESSION['pfif_info']['person_insert_errors'];

      return true;
   }

   public function storeNotesInDatabase() {
      global $conf, $global, $first_entry_date, $last_entry_date, $last_entry_count;

      // TODO: A lot of these legacy routines are incorrectly written to expect thrown exceptions or error codes
      // which don't exist. Need to do an audit all these.
      include_once 'add.inc';

      $_SESSION['pfif_info']['note_insert_errors'] = 0;
      $pfif_notes = $this->getNotes();
      $this->reset_log_dates($pfif_notes[0]->entry_date);

      //var_dump("first/last/count at start: ", $first_entry_date, $last_entry_date, $last_entry_count);
      foreach ($pfif_notes as $note) {
         // Update last_entry_count.
         $this->update_log_dates($note->entry_date);

         // Save to pfif_note table.
         try {
             $this->shn_mpr_addpfifnote_commit($note); // DB error reported in method
         } catch (Exception $e) {
             print $e->getMessage();
             $_SESSION['pfif_info']['note_insert_errors'] += 1;
             error_log('shn_mod_mpr_pfif.storeInDatabase:' . $e->getMessage());
             // Interrupt further processing of this note.
             continue;
         }
      // Sahana tables with dynamic data are now updated by a cron task.
      // So nothing more to do.
      }
      unset($note);
      //var_dump("first/last/count at end: ", $first_entry_date, $last_entry_date, $last_entry_count);

      // Update status info
      $this->save_log_dates();

      // Update number of notes actually processed.
      $_SESSION['pfif_info']['pfif_note_count'] = count($pfif_notes)-$_SESSION['pfif_info']['note_insert_errors'];

      return true;
   }

   // TODO: Can probably move these into a pfif_helper script.
   private function _pfif_prepare_person_insert($person) {
      $_SESSION['mpr_add']['entry']['p_uuid'] = $person->person_record_id;
      if (!empty($person->expiry_date)) {
         $_SESSION['mpr_add']['report_person']['expiry_date'] = $person->expiry_date;
      }

      if (!empty($person->author_name)) {
         $_SESSION['mpr_add']['report_person']['rep_full_name'] = $person->author_name;
      }
      if (!empty($person->author_email)) {
         $_SESSION['mpr_add']['report_person']['rep_email'] = $person->author_email;
      }
      if (!empty($person->author_phone)) {
         $_SESSION['mpr_add']['report_person']['rep_phone'] = $person->author_phone;
      }

      //Static identifying information
      $_SESSION['mpr_add']['entry']['incident_id'] = $_SESSION['user_pref_ims_incident_id'];
      $_SESSION['mpr_add']['entry']['full_name'] = $person->full_name;
      $_SESSION['mpr_add']['entry']['given_name'] = $person->first_name;
      $_SESSION['mpr_add']['entry']['family_name'] = $person->last_name;
      // TODO: are these next two used?
      $_SESSION['mpr_add']['entry']['loc_select_3'] = $person->home_city;
      $_SESSION['mpr_add']['entry']['loc_select_2'] = $person->home_state;
      // TODO: PFIF also may have home_country and home_neighborhood?
      $_SESSION['mpr_add']['entry']['address'] = '';
      if (!empty($person->home_street)) {
         $_SESSION['mpr_add']['entry']['address'] = $person->home_street . ", ";
      }
      if (!empty($person->home_city)) {
         $_SESSION['mpr_add']['entry']['address'] .= $person->home_city . ", ";
      }
      if (!empty($person->home_state)) {
         $_SESSION['mpr_add']['entry']['address'] .= $person->home_state;
      }
      if (!empty($person->home_postal_code)) {
         $_SESSION['mpr_add']['entry']['zip'] = $person->home_postal_code;
      }
      fetch_image($person->photo_url,
              $person->source_name,
              $person->person_record_id,
              $person->source_url); // Populates [mpr][entry][image]

      $age_info = shn_map_age_from_pfif($person->date_of_birth,
                                        $person->age,
                                        $person->source_date);
      if (!empty($age_info['years_old'])) {
         $_SESSION['mpr_add']['entry']['years_old'] = $age_info['years_old'];
      } else {
         if (!empty($age_info['minAge'])) {
            $_SESSION['mpr_add']['entry']['minAge'] = $age_info['minAge'];
         }
         if (!empty($age_info['maxAge'])) {
            $_SESSION['mpr_add']['entry']['maxAge'] = $age_info['maxAge'];
         }
      }
      if (!empty($age_info['date_of_birth'])) {
         $_SESSION['mpr_add']['entry']['dob'] = $age_info['date_of_birth'];
      }
      $_SESSION['mpr_add']['entry']['opt_gender'] = shn_map_gender_from_pfif($person->sex);
      // Set status to unknown.
      $_SESSION['mpr_add']['entry']['opt_status'] = 'unk';
      // Set creation_time and last_updated.
      // Since last_updated is key to getting cron-scheduled updates from notes, and since
      // sometimes a note has already arrived with exactly the same time, make last_updated
      // one second earlier than creation time.
      if (!empty($person->source_date)) {
         $_SESSION['mpr_add']['entry']['creation_time'] = $person->source_date;
         $earlier = date('Y-m-d H:i:s', strtotime($person->source_date)-1);
         $_SESSION['mpr_add']['entry']['last_updated'] = $earlier;
      } else {
         // Pick an arbitrary early date.
         $_SESSION['mpr_add']['entry']['creation_time'] = '2000-01-01 00:00:00';
         $_SESSION['mpr_add']['entry']['last_updated'] = '2000-01-01 00:00:00';
      }
      // Save "other" field to person details comments.
      if (!empty($person->other)) {
         $_SESSION['mpr_add']['entry']['other_comments'] = $person->other;
      }
   }

   // Load from database based either on person ID (for testing) or last export date.
   public function loadFromDatabase($id, $since_entry_date, $skip) {
      global $conf, $global;
      include_once $global['approot'] . "/inc/lib_uuid.inc";

      $this->check_init();
      $baseUuid = $conf['base_uuid'];
      $pfifDomain = substr($baseUuid, 0, -1);  // omit trailing "/"
      $baseUrl = "https://" . $pfifDomain;

      // Get person records based on filters.
      $personRecords = $this->getPersonFromDb($status, $since_entry_date, $skip);
      $record_count = count($personRecords);

      foreach ($personRecords as $personRecord) {
         // Get the PFIF record if any.
         $sourcePfif = $this->getSourcePfif($personRecord);

         // Populate person.
         $person = new Pfif_Person();

         $person->person_record_id = $personRecord['p_uuid'];
         $person->entry_date = $personRecord['creation_time'];
         $person->expiry_date = $sourcePfif ? $sourcePfif->expiry_date : $personRecord['expiry_date'];

         $reporter = $this->getReportedPerson($personRecord['reporter']);
         if (count($reporter) > 0) {
            // error_log("reporter_record is set!");
            $personRecord['reporter_record'] = $reporter;
            $person->author_name = $personRecord['reporter_record']['full_name'];
            $person->author_email = $personRecord['reporter_record']['email'];
            $person->author_phone = $personRecord['reporter_record']['phone'];
         }

         // Spec defines source_ info is for home repository. Use local info only for our own records.
         $person->source_name = $sourcePfif ? $sourcePfif->source_name : $pfifDomain;
         $person->source_date = $sourcePfif ? $sourcePfif->source_date : $personRecord['creation_time'];
         $person->source_url = $sourcePfif ? $sourcePfif->source_url : 'https://' . $personRecord['p_uuid'];

         $person->full_name = $sourcePfif ? $sourcePfif->full_name : $personRecord['full_name'];
         $person->first_name = $sourcePfif ? $sourcePfif->first_name : $personRecord['first_name'];
         $person->last_name = $sourcePfif ? $sourcePfif->last_name : $personRecord['last_name'];

         // Note: For when no source PFIF, we could try to parse $personRecord['address'] better.
         $person->home_city = $sourcePfif ? $sourcePfif->home_city : '';
         $person->home_state = $sourcePfif ? $sourcePfif->home_state : '';
         $person->home_neighborhood = $sourcePfif ? $sourcePfif->home_neighborhood : '';
         $person->home_street = $sourcePfif ? $sourcePfif->home_street : $personRecord['address'];
         $person->home_country = $sourcePfif ? $sourcePfif->home_country : '';
         $person->home_postal_code = $sourcePfif ? $sourcePfif->home_postal_code : $personRecord['zip'];

         if ($sourcePfif) {
            $person->photo_url = $sourcePfif->photo_url;
         } else {
            if (!empty($personRecord['image_url'])) {
               $photo_url = $personRecord['image_url'];
               $person->photo_url = $photo_url[0] == '/' ? $baseUrl . $photo_url : $baseUrl . '/' . $photo_url;
            }
         }

         // Since our gender mapping is not lossless (PFIF has "other" category), use the PFIF if it exists.
         if ($sourcePfif) {
            $person->sex = $sourcePfif->sex;
         } else {
            $person->sex = shn_map_gender_to_pfif($personRecord, $sourcePfif);
         }

         // Use the PFIF age if it exists since we only have to copy it.
         if ($sourcePfif) {
            $person->age = $sourcePfif->age;
         } else {
            $person->age = shn_map_age_to_pfif($personRecord);
         }
         $person->date_of_birth = $sourcePfif ? $sourcePfif->date_of_birth : $personRecord['dob'];
         if ($sourcePfif) {
            $person->other = $sourcePfif->other;
         } else {
            $details = array();
            if (!empty($personRecord['height'])) {
               $details['height'] = 'height: ' . $personRecord['height'];
            }
            if (!empty($personRecord['weight'])) {
               $details['weight'] = 'weight: ' . $personRecord['weight'];
            }
            if (!empty($personRecord['opt_eye_color'])) {
               $details['eye_color'] = 'eye color: ' . shn_get_field_opt($personRecord['opt_eye_color'], 'opt_eye_color');
            }
            if (!empty($personRecord['opt_skin_color'])) {
               $details['skin_color'] = 'skin color: ' . shn_get_field_opt($personRecord['opt_skin_color'], 'opt_skin_color');
            }
            if (!empty($personRecord['opt_hair_color'])) {
               $details['hair_color'] = 'hair color: ' . shn_get_field_opt($personRecord['opt_hair_color'], 'opt_hair_color');
            }
            if (!empty($personRecord['physical_comments'])) {
               $details['physical_comments'] = 'other physical: ' . $personRecord['physical_comments'];
            }
            if (!empty($personRecord['other_comments'])) {
               $details['other_comments'] = 'other: ' . $personRecord['other_comments'];
            }
            if (count($details) > 0) {
               $person->other = "description: ";
               foreach ($details as $detail) {
                  $person->other .= $detail . ', ';
               }
               $person->other = substr($person->other, 0, -2);
            }
         }
         $this->setPerson($person);
         $notes = $this->getPfifNotes($person->person_record_id);
         $this->setNotes($notes);
      }
      unset($personRecord);
      if ($personRecords != false && $record_count > 0) {
         return $record_count;
      } else {
         return false;
      }
   }

   // Use specified person_record_id (for testing) or threshhold date and
   // number of records to skip.
   private function getPersonFromDb($id, $since_entry_date, $skip) {
      global $global;

      $whereSql = '';
      if (!empty($id)) {
         $whereSql = " WHERE ps.isvictim = '1' AND ps.p_uuid = '$id'";
      } else {
         $where = array();
         $where[] = " ps.isvictim = '1' ";
         $where[] = " ps.last_updated >= '$since_entry_date' ";
         $where[] = " a.incident_id = " . $_SESSION['user_pref_ims_incident_id'];

         foreach ($where as $whereElement) {
            $whereSql .= ( $whereSql == null ? '' : ' AND ') . $whereElement;
         }
         $whereSql = $whereSql != null ? ' WHERE ' . $whereSql : '';
         $large_num = 1e12;
         $whereSql .= " ORDER BY ps.status_id ASC LIMIT $skip,$large_num";
      }

      // DEBUG:
      error_log("calling getMprAddedRecords(" . $whereSql . ")");
      $array2 = $this->getMprAddedRecords($whereSql);
      print "got " . count($array2) . " records\n";
      return $array2;
   }

   private function getMprAddedRecords($whereSql) {
      global $global;
      $sql = "SELECT a.p_uuid , a.full_name, a.family_name, a.given_name, a.l10n_name, a.expiry_date, e.birth_date as dob, e.opt_gender, e.years_old, e.minAge, e.maxAge,
            f.comments as physical_comments, f.height, f.weight, f.opt_eye_color, f.opt_skin_color, f.opt_hair_color, f.injuries, g.contact_value as phone, h.contact_value as mobile, i.contact_value as email,
            j.contact_value AS address, k.contact_value AS zip, e.last_seen, e.last_clothing, e.other_comments, pr.rep_uuid as reporter,
            ps.status_id, ps.last_updated, ps.creation_time, ps.opt_status as `status`, im.url as image_url
		FROM person_uuid a
		LEFT OUTER JOIN person_details e ON e.p_uuid = a.p_uuid
		LEFT OUTER JOIN person_physical f ON f.p_uuid = a.p_uuid
		LEFT OUTER JOIN contact g ON g.p_uuid = a.p_uuid
        AND g.opt_contact_type = 'curr'
		LEFT OUTER JOIN contact h ON h.p_uuid = a.p_uuid
        AND h.opt_contact_type = 'cmob'
		LEFT OUTER JOIN contact i ON i.p_uuid = a.p_uuid
        AND i.opt_contact_type = 'email'
		LEFT OUTER JOIN contact j ON j.p_uuid = a.p_uuid
        AND j.opt_contact_type = 'home'
		LEFT OUTER JOIN contact k ON k.p_uuid = a.p_uuid
        AND k.opt_contact_type = 'zip'
        LEFT OUTER JOIN image im ON a.p_uuid = im.p_uuid
        LEFT OUTER JOIN person_status ps ON ps.p_uuid = a.p_uuid
        LEFT OUTER JOIN person_to_report pr ON pr.p_uuid = a.p_uuid
        $whereSql ";

      // DEBUG:  error_log("getMprAddedRecords: ".$sql);
      // print "callinb db ...\n";
      $array = $global['db']->GetAll($sql);
      // print "returning ...\n";
      // var_dump($array);
      return $array;
   }

   private function checkForReportedPerson($p_uuid) {
      global $global;
      $sql = "SELECT p_uuid,source_date,entry_date,expiry_date FROM person_uuid WHERE p_uuid = '$p_uuid'";
      $array = $global['db']->GetRow($sql);
      return $array;
   }

   private function getReportedPerson($p_uuid) {
      global $global;
      $sql = "SELECT a.p_uuid , a.full_name, a.family_name, a.l10n_name, e.birth_date AS dob, f.comments AS physical_comments,
              f.height, f.weight, g.contact_value AS phone, h.contact_value AS mobile, i.contact_value AS email
		FROM person_uuid a
		LEFT OUTER JOIN person_details e ON e.p_uuid = a.p_uuid
		LEFT OUTER JOIN person_physical f ON f.p_uuid = a.p_uuid
		LEFT OUTER JOIN contact g ON g.p_uuid = a.p_uuid
		AND g.opt_contact_type = 'curr'
		LEFT OUTER JOIN contact h ON h.p_uuid = a.p_uuid
		AND h.opt_contact_type = 'cmob'
		LEFT OUTER JOIN contact i ON i.p_uuid = a.p_uuid
		AND i.opt_contact_type = 'email'
        WHERE a.p_uuid = '$p_uuid' ";

      //print $sql;
      $array = $global['db']->GetRow($sql);
      return $array;
   }

   /**
    * Stores imported PFIF person records in PFIF tables.
    * TODO: Store internally generated PFIF records in PFIF tables?
    */
    private function shn_mpr_addpfifperson_commit(Pfif_Person $person) {
      global $global;
      $audit_flag = defined(MPR_ADD_AUDIT_ENABLED) ? MPR_ADD_AUDIT_ENABLED : false;
      // Gather $person fields for pfif_person table
      $insert_array = array();
      $insert_array['p_uuid'] = $person->person_record_id;
      $insert_array['source_version'] = $this->getVersion();
      $insert_array['source_repository_id'] = $this->getSourceReposId();
      $insert_array['entry_date'] = strftime("%Y-%m-%d %H:%M:%S ");
      if (!empty($person->expiry_date)) {
         $insert_array['expiry_date'] = $person->expiry_date;
      }
      if (!empty($person->author_name)) {
         $insert_array['author_name'] = $person->author_name;
      }
      if (!empty($person->author_email)) {
         $insert_array['author_email'] = $person->author_email;
      }
      if (!empty($person->author_phone)) {
         $insert_array['author_phone'] = $person->author_phone;
      }
      if (!empty($person->source_name)) {
         $insert_array['source_name'] = $person->source_name;
      }
      $insert_array['source_date'] = $person->source_date;
      $insert_array['source_url'] = $person->source_url;
      if (!empty($person->full_name)) {
         $insert_array['full_name'] = $person->full_name;
      }
      if (!empty($person->first_name)) {
         $insert_array['first_name'] = $person->first_name;
      }
      if (!empty($person->last_name)) {
         $insert_array['last_name'] = $person->last_name;
      }
      if (!empty($person->home_city)) {
         $insert_array['home_city'] = $person->home_city;
      }
      if (!empty($person->home_state)) {
         $insert_array['home_state'] = $person->home_state;
      }
      if (!empty($person->home_country)) {
         $insert_array['home_country'] = $person->home_country;
      }
      if (!empty($person->home_neighborhood)) {
         $insert_array['home_neighborhood'] = $person->home_neighborhood;
      }
      if (!empty($person->home_street)) {
         $insert_array['home_street'] = $person->home_street;
      }
      if (!empty($person->home_postal_code)) {
         $insert_array['home_postal_code'] = $person->home_postal_code;
      }
      if (!empty($person->photo_url)) {
         $insert_array['photo_url'] = $person->photo_url;
      }
      if (!empty($person->sex)) {
         $insert_array['sex'] = $person->sex;
      }
      if (!empty($person->date_of_birth)) {
         $insert_array['date_of_birth'] = $person->date_of_birth;
      }
      if (!empty($person->age)) {
         $insert_array['age'] = $person->age;
      }
      if (!empty($person->other)) {
         $insert_array['other'] = $person->other;
      }
      shn_db_insert($insert_array, 'pfif_person', $audit_flag, 'p_uuid');
      $errchk = $global['db']->ErrorMsg();
      if (!empty($errchk)) {
         error_log("Error saving pfif_person for " . $person->person_record_id . ": " . $errchk);
      }
      $insert_array = null;
      return true;
   }

    /**
    * Stores all imported PFIF note records in PFIF tables.
    * TODO: Store internally generated PFIF records in PFIF tables?
    */
    private function shn_mpr_addpfifnote_commit(Pfif_Note $note) {
      global $global;
      $audit_flag = defined(MPR_ADD_AUDIT_ENABLED) ? MPR_ADD_AUDIT_ENABLED : false;
      // Gather note fields for pfif_note table.
      $insert_array = array();
      $insert_array['note_record_id'] = $note->note_record_id;
      $insert_array['p_uuid'] = $note->person_record_id;
      $insert_array['source_version'] = $this->getVersion();
      $insert_array['source_repository_id'] = $this->getSourceReposId();
      if (!empty($note->linked_person_record_id)) {
         $insert_array['linked_person_record_id'] = $note->linked_person_record_id;
      }
      $insert_array['entry_date'] = strftime("%Y-%m-%d %H:%M:%S ");
      if (!empty($note->author_name)) {
         $insert_array['author_name'] = $note->author_name;
      }
      if (!empty($note->author_email)) {
         $insert_array['author_email'] = $note->author_email;
      }
      if (!empty($note->author_phone)) {
         $insert_array['author_phone'] = $note->author_phone;
      }
      $insert_array['source_date'] = $note->source_date;
      if (!empty($note->found)) {
         $insert_array['found'] = $note->found;
      }
      if (!empty($note->status)) {
         $insert_array['status'] = $note->status;
      }
      if (!empty($note->email_of_found_person)) {
         $insert_array['email_of_found_person'] = $note->email_of_found_person;
      }
      if (!empty($note->phone_of_found_person)) {
         $insert_array['phone_of_found_person'] = $note->phone_of_found_person;
      }
      if (!empty($note->last_known_location)) {
         $insert_array['last_known_location'] = $note->last_known_location;
      }
      if (!empty($note->text)) {
         $insert_array['text'] = $note->text;
      }
      shn_db_insert($insert_array, 'pfif_note', $audit_flag, 'note_record_id');
      $errchk = $global['db']->ErrorMsg();
      if (!empty($errchk)) {
         error_log("Error saving pfif_note " . $note->note_record_id . ": " .  $errchk);
         $_SESSION['pfif_info']['note_insert_errors'] += 1;
      }
      //print("\nSaved pfif_note: " . $note->note_record_id . " for person: " . $note->person_record_id);
      $insert_array = null;
      return true;
   }

    /**
     * Gets the source PFIF person
     */
   //private function getSourcePfif($person) {
   public function getSourcePfif($person) {
      global $global;
      // print "<pre>".var_export($person,'true')."</pre/>";
      $pfif_person = false; // The return variable

      $sql = "SELECT * FROM pfif_person WHERE p_uuid = '" . $person['p_uuid'] . "'";
      $rs = $global['db']->GetRow($sql);
      if (count($rs) > 0) {
         $pfif_person = new Pfif_Person();
         $pfif_person->person_record_id = $rs['p_uuid'];
         // error_log("processing person:".$pfif_person->person_record_id);
         $pfif_person->entry_date = $rs['entry_date'];
         $pfif_person->expiry_date = $rs['expiry_date'];
         $pfif_person->author_name = $rs['author_name'];
         $pfif_person->author_email = $rs['author_email'];
         $pfif_person->author_phone = $rs['author_phone'];
         $pfif_person->source_name = $rs['source_name'];
         $pfif_person->source_date = $rs['source_date'];
         $pfif_person->source_url = $rs['source_url'];
         // error_log("meta-information done ...");
         // Static identifying information
         $pfif_person->full_name = $rs['full_name'];
         $pfif_person->first_name = $rs['first_name'];
         $pfif_person->last_name = $rs['last_name'];
         $pfif_person->home_city = $rs['home_city'];
         $pfif_person->home_state = $rs['home_state'];
         $pfif_person->home_neighborhood = $rs['home_neighborhood'];
         $pfif_person->home_street = $rs['home_street'];
         $pfif_person->home_country = $rs['home_country'];
         $pfif_person->home_postal_code = $rs['home_postal_code'];
         $pfif_person->photo_url = $rs['photo_url'];
         $pfif_person->other = $rs['other'];
         $pfif_person->age = $rs['age'];
         $pfif_person->date_of_birth = $rs['date_of_birth'];
         $pfif_person->sex = $rs['sex'];
         // error_log("Static informaton done ...");
      }
      unset($person);
      return $pfif_person;
   }

    /**
     * Gets the PFIF notes for a person.
     */
   private function getPfifNotes($person) {
      global $global;

      $notes = array();
      $sql = "SELECT * FROM pfif_note WHERE p_uuid = '$person' ORDER BY source_date";
      $results = $global['db']->GetAll($sql);
      foreach($results as $rs){
         $pfif_note = new Pfif_Note();
         $pfif_note->note_record_id = $rs['note_record_id'];
         $pfif_note->person_record_id = $rs['p_uuid'];
         $pfif_note->linked_person_record_id = $rs['linked_person_record_id'];
         $pfif_note->entry_date = $rs['entry_date'];
         $pfif_note->author_name = $rs['author_name'];
         $pfif_note->author_email = $rs['author_email'];
         $pfif_note->author_phone = $rs['author_phone'];
         $pfif_note->source_date = $rs['source_date'];
         $pfif_note->email_of_found_person = $rs['email_of_found_person'];
         $pfif_note->phone_of_found_person = $rs['phone_of_found_person'];
         $pfif_note->status = $rs['status'];
         $pfif_note->found = $rs['found'];
         $pfif_note->last_known_location = $rs['last_known_location'];
         $pfif_note->text = $rs['text'];
         $notes[] = $pfif_note;
      }
      unset($rs);
      return $notes;
   }
}
