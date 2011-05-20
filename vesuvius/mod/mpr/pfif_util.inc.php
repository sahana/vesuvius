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


require_once('webimage.inc');

define("PFIF_NS_PREFIX","pfif");
define("PFIF_1_2_NAMESPACE","http://zesty.ca/pfif/1.2");
define("PFIF_V_1_1" , "1.1");
define("PFIF_V_1_2" , "1.2");

define("PFIF_1_2_OPEN_TAG", '<pfif1.2>');
define("PFIF_1_2_CLOSE_TAG" , "</pfif1.2>");
define("PFIF_1_2_AGE" , "age");
define("PFIF_1_2_DOB" , "date_of_birth");
define("PFIF_1_2_SEX" , "sex");
define("PFIF_1_2_VER" , "ver");
define ("PFIF_1_2_PID" , "person");
define ("PFIF_1_2_LPID" , "duplicates");
define ("PFIF_1_2_STS" , "status");

define("PFIF_NOTE_CONTAINER_ID" , "pl.nlm.nih.gov/note.container");
define ("MISSING_NODE_TAGNAME", "empty_child");

define("PFIF_IMG_CACHE_DIR","/tmp/pfif_cache/");
define("PFIF_IMG_THUMB_PREFIX","thumb_");

$pfif_node_cache = array(); // FIXME: temporary hack : should be able to get nodes by person_record_id using XPath

// HACK ALERT: A dummy node list to prevent non-object access errors on missing elements.
$dummy_node_list = null;
function set_dummy_node_list($documentNode) {
    global $dummy_node_list;

    $dummy_element = $documentNode->createElement('empty_node');
    $dummy_child = $documentNode->createElement(MISSING_NODE_TAGNAME);
    $dummy_element->appendChild($dummy_child);
    $dummy_node_list = $dummy_element->getElementsByTagName('*');
}

/**
 * Transform local time to UTC time.
 *
 */
function utc_date($d) {
    if (!empty($d)) {
       $ts = strtotime($d);
       $z = gmdate('Y-m-d\TH:i:s\Z',$ts);
    } else {
       $z = null;
    }
    return $z;
}

/**
 * Transform UTC time to local time.
 *
 */
function local_date($d) {
    if (!empty($d)) {
       $ts = strtotime($d);
       $z = date('Y-m-d H:i:s',$ts);
    } else {
       $z = null;
    }
    return $z;
}

/**
        * Gets the first name from a Sahana full name.
        *
        */
function hepl_parse_name($s) {
    $parts = explode(",",$s);
    $p['name'] = $parts[0];
    if (count($parts) > 1) {
        $p['last_seen']=$parts[2];
    }
    return $p;
}

/**
        * Extracts name and e-mail from  an RFC 2822 e-mail address string.
        *
        * Splits "User <mailbox-id@domain>" into array('sender'=>"user", 'addr'=>"mailbox-id@domain")
        * Note that User may contain orgainzation info such as (NIH/NLM/LHC)[E] that seems to be consistently enclosed in quotes.
        * These should be parsed separately and the () and [] encapsed comments discarded. Thus, given input
        *      "Antani, Sameer (NIH/NLM/LHC) [E]" <santani@mail.nih.gov>
        * this function should return
        *       ['user'] = Antani, Sameer
        *       ['addr'] = santani@mail.nih.gov
        *
        */
function hepl_parse_email($em) {
    print "parsing email: $m \n";
    $result = array();
    if ($em[0] == '"') {
        $endqt = stripos($em,'"',1);
        $userstr = substr($em,1,$endqt-1);
        $rightstr = trim(substr($em,$endqt+1));
        $emailstr = trim(substr($rightstr,1));
        $emailstr = substr($emailstr,0,strlen($emailstr)-1); // trim closing '>'
    } else {
        $tmp = explode('<',$em);
        switch (count($tmp)) {
            case 1: // TODO: check for '@' to determine whether display or addr is present ?
                $userstr = '';
                $emailstr = trim($tmp[0]);
            case 2:
                $userstr = trim($tmp[0]);
                $emailstr = trim($tmp[1]);
                $emailstr = substr($emailstr,0,strlen($emailstr)-1); // trim closing '>'
                break;
            default:
                $userstr = '';
                $emailstr = '';
        }
    }
    // TODO: Discard comments from User string
    $result['user'] = $userstr;
    $result['addr'] = substr($emailstr,0,strlen($emailstr));
    print "returning ".print_r($result,true)."\n";
    return $result;
}

/**
* Map Sahana MPR status values to PFIF found (1.1) or status  (1.2) values
* PFIF 1.1 defines only found = {true, false}. PFIF 1.2 uses status as defined below (with corresponding Sahana
* value in parens):
    information_sought ('unk')
        The author of the note is seeking information on the person in question.
    is_note_author ('ali', AND isvictim = 0)
        The author of the note is the person in question.
    believed_alive ('ali')
        The author of the note has received information that the person in question is alive.
    believed_missing ('mis')
        The author of the note has reason to believe that the person in question is still missing.
    believed_dead ('dec')
        The author of the note has received information that the person in question is dead.

   @see shn_map_status_from_pfif
*/
function shn_map_status_to_pfif($status, $isvictim, $ver='1.2') {
    $status_map =
        array('unk'=>array('1.1'=>'false','1.2'=>'information_sought'),
              'fnd'=>array('1.1'=>'true','1.2'=>'information_sought'),
              'ali'=>array('1.1'=>'true','1.2'=>'believed_alive'),
              'mis'=>array('1.1'=>'false','1.2'=>'believed_missing'),
              'dec'=>array('1.1'=>'true','1.2'=>'believed_dead'));

    $value = '';
    if ($ver == '1.2' && !($isvictim == '1') && $status == 'ali') {
        $value = 'is_note_author';
    } else {
        $value = $status_map[$status][$ver];
    }
    return $value;

}

/**
 *    Map note's found and status fields to sahana opt_status value.
*/
function shn_map_status_from_pfif($status, $found, $old_status) {
    // PFIF to PL mapping.
    $status_map =
        array('information_sought'=>'unk',
              'believed_alive'=>'ali',
              'believed_missing'=>'mis',
              'believed_dead'=>'dec',
              'is_note_author'=>'ali');

    // Overrider earlier statuses using this mapping.
    $status_ranking_map = 
       array('unk'=>array('unk'=>'unk',
                          'ali'=>'ali',
                          'mis'=>'mis',
                          'dec'=>'dec',
                          'fnd'=>'fnd'),
             'mis'=>array('unk'=>'mis',
                          'ali'=>'ali',
                          'mis'=>'mis',
                          'dec'=>'dec',
                          'fnd'=>'fnd'),
             'fnd'=>array('unk'=>'fnd',
                          'ali'=>'ali',
                          'mis'=>'fnd',
                          'dec'=>'dec',
                          'fnd'=>'fnd'),
             'inj'=>array('unk'=>'inj',
                          'ali'=>'ali',
                          'mis'=>'inj',
                          'dec'=>'dec',
                          'fnd'=>'inj'),
             'dec'=>array('unk'=>'dec',
                          'ali'=>'ali',
                          'mis'=>'dec',
                          'dec'=>'dec',
                          'fnd'=>'dec'),
             'ali'=>array('unk'=>'ali',
                          'ali'=>'ali',
                          'mis'=>'ali',
                          'dec'=>'dec',
                          'fnd'=>'ali'));

    // Map new status from PFIF record.
    $new_status = 'unk';  // default for unspecified status
    $old_status = (empty($old_status))? 'unk' : $old_status; 
    if(!empty($status)) {
       $new_status = $status_map[$status];
    } 
    // We have to do something with the "found" field if present. Have it
    // outrank a concurrent status of "missing" or "unknown".
    if ($found == 'true' && ($new_status == 'unk' || $new_status == 'mis')) {
        $new_status = 'fnd';
    }

    // Do the ranking mapping.
    $result = $status_ranking_map[$old_status][$new_status];
    //error_log("Old status: " . $old_status . " new status: " . $result); 
    return $result;
}

/**
 * Maps gender, if given, to PFIF sex  element.
 *
 * @param personRecord  resultset from db for person of interest
 * @param person        Person instance containing original imported PFIF person record.
 *
 */
function shn_map_gender_to_pfif($personRecord, $source_person) {
    $gender_map = array('unk'=>'', 'mal'=>'male', 'fml'=>'female'); // PFIF 1.2 defines an 'oth)er' category, but it is not  clear what that means.
                                                                    // The spec states that if gender is unknown it should be omitted.
    // TODO: factor in PFIF record
    $g = '';
    if (!empty($personRecord['opt_gender'])) {
       $g = $gender_map[$personRecord['opt_gender']];
       //DEBUG: error_log("mapped gender to ".$g);
    }
    return $g;
}

function shn_map_gender_from_pfif($pfif_sex) {
    $gender_map = array('male'=>'mal','female'=>'fml','other'=>'unk'); //// PFIF 1.2 defines an 'oth)er' category, but it is not clear what that means, so we map to unkown, which means indeterminate or otherwise unreportable as male or female. The spec states that if gender is unknown it should be omitted.

    return $gender_map[$pfif_sex];
}

/**
 *
 * Maps Approximate age, if given, or age range to PFIF age element.
 *
 * @param personRecord  resultset from db for person of interest
 *
 */
function shn_map_age_to_pfif($personRecord) {
    $age = '';
    if (!empty($personRecord['years_old'])) {
        $age = $personRecord['years_old'];   // perhaps from mpres
    } else if (!empty($personRecord['minAge']) && !empty($personRecord['maxAge'])) {
        $age = $personRecord['minAge'].'-'.$personRecord['minAge'];
    }
    return $age;
}

/**
     *
     * Maps PFIF age and/or date_of_birth fields to appropriate combination of Sahana
     *  birth_date and years_old
     *
     * @param $age          contents of the person.age element
     * @param person       contents of the person.data_of_birth element
     */
function shn_map_age_from_pfif($dob, $age, $source_date) {
    $result = array();
    // TODO: dob can be YYYY, YYY-MM or YYYY-MM-DD.
    //              Use datediff to get approximate age in years
    //     NOTE: that MySQL allows partial dates specified as YYYY0000 or YYYYMM00, however we don't know
    //                 how Sahana will respond when such partial dates are encountered. So, only store date_of_birth when it
    //                 is specified to the day. Otherwise, may use partial date to establish age if age is not specified.
    if (!empty($dob)) {
        $full_dob = strlen($dob) == 10 ? $dob : false;
        if ($full_dob) {
            $result['date_of_birth'] = $full_dob;
        }
    }

    // FIXME: Should a fully specified DOB trump age? (chc 20100309)
    // age can be a single number or a range. split on '-' to get min and max
    if (!empty($age)) {
        $range = explode('-',$age);
        if (count($range) == 1) {
            $result['years_old'] = $range[0];
        } else {
            $result['minAge'] = $range[0];
            $result['maxAge'] = $range[1];
        }
    } else if (!empty($dob)) {
        $reftime = strtotime($source_date);
        $refdate = getdate($reftime);
        $birthtime = strtotime($dob);
        $birthday = getdate($birthtime);
        $result['years_old'] = $refdate['year'] - $birthday['year'];
    }
    return $result;
}

    /**
    *
    *  Experimental: return the base URL needed to resolve a relative photo_url
    *  NOTE: This is needed to resolve a change in Google's treatment of source_name and source_url since
     *       the initial release of Haiti and Chile person finder apps.
     * @return String the host needed to resolve a relative URL
     * @param String $surl the PFIF source_url
     * @param String $surl the PFIF source_name
    *
    */
    function extract_url_host($surl,$sname) {
        $p = parse_url($surl,PHP_URL_HOST);
        return $p;
    }

    /**
    *
    *  Attempts to retrieve the image referenced by photo_url. If successful, queues image info for insertion in image table.
    *
    */
function fetch_image($photo_url,$source_name,$person_record_id,$source_url=null) {
    global $failed_images;
    // var_dump('id',$person_record_id,'photo_url',$photo_url,'empty?',empty($photo_url));
    if (!empty($photo_url))
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
            // Google-hack: combine source_url and photo_url
            // TODO: 8/19/2010 - move this to find_best_image ???
            // TODO: possible (generalization, if photo-url starts with '/' append to source-url.
            // May not always work. (chc 3/5/2010)
            // TODO: (chc 8/10/10) : need to add Pakistan instance ... is '.appspot' sufficient?
            // $photo_url = $person->photo_url;
            if ($photo_url[0] == '/' &&
                ((stripos($source_name,
                          'google.com') !== FALSE ) ||
                 (stripos($source_name,
                          'chilepersonfinder.appspot') !== FALSE ) ||
                 (stripos($source_name,
                          'haiticrisis.appspot') !== FALSE )
                 )) {
                $host = extract_url_host($source_url,$source_name);
                $photo_url = 'http://'.$host.$photo_url;
                // error_log("Using Google photo: ".$photo_url);
            } else {
                // See whether there is a better photo (site-specific)
                $alt_photo_url = find_best_image($photo_url);
                if ($alt_photo_url){
                    // error_log("fetch_image:Using ".$alt_photo_url." in place of ".$photo_url);
                    $photo_url = $alt_photo_url;
                }
            }
            $image = new WebImage($photo_url, $person_record_id);
            // error_log("new WebImage() returns:".var_export($image,true));
            if ($image->is_initialized()){
                // error_log("image type: $image->type width: $image->width height; $image->height");
                $_SESSION['mpr']['entry']['image_type'] = $image->type;
                $_SESSION['mpr']['entry']['image_height'] = $image->height;
                $_SESSION['mpr']['entry']['image_width'] = $image->width;
                $_SESSION['mpr']['entry']['original_filename'] = $photo_url;

                // Gen cache filename from id, ..
                $filePath = "../../www".PFIF_IMG_CACHE_DIR;
                $fileName = str_replace("/", "SLASH", $person_record_id)."__".rand(1000000000, 1999999999).".".$image->type;
                $localUrl = PFIF_IMG_CACHE_DIR.$fileName;

                // and write image to cache
                $handle = fopen($filePath."/".$fileName,'w');
                $status = fwrite($handle,$image->image);
                fclose($handle);

                if ($status) { // write succeeded
                    // error_log("fetch_image:wrote file ".$filePath."/".$fileName);
                    $_SESSION['mpr']['entry']['url'] = $localUrl;
                    $_SESSION['mpr']['entry']['image'] = null;

                    // Create thumbnail if image height exceeds threshold
                    if ($image->height > 320 || $image->width > 320) {
                        $thumbName = PFIF_IMG_THUMB_PREFIX.$fileName;
                        shn_image_resize_height($filePath.$fileName,
                                                $filePath.$thumbName,
                                                320);
                    } else {
                        $thumbName = $fileName;
                    }
                    $_SESSION['mpr']['entry']['url_thumb'] = PFIF_IMG_CACHE_DIR.$thumbName;
                } else { // image write failed, store in DB
                    error_log("fetch_image:error writing file ".$filePath."/".$fileName);
                    $_SESSION['mpr']['entry']['url'] = $image->url;
                    $_SESSION['mpr']['entry']['url_thumb'] = null; // TODO: should we chance storing the raw URL here?
                    $_SESSION['mpr']['entry']['image'] = $image->image;
                }
                $_SESSION['pfif_info']['images_in'] += 1;
            } else { // TODO: Note that add.inc:shn_mpr_addmp_commit() is going to insert an empty image record
                // TODO: should we stuff the URL so it can be retried later? (chc 2/1/2010)
                error_log("fetch_image:GET image failed for ".$person_record_id." from ".$photo_url);
                $failed_images[] = array('x_uuid'=>$person_record_id,'url'=>$photo_url);
            }
        } else {
            // error_log("no photo for ".$person->person_record_id);
        }
}

/**
    *
    *  Attempts to locate a higher resolution version of the image referenced by photo_url.
    *
    *  @return String  an alternate photo_url for a higher resolution versrion or @code(false)
    *  @param String  the provided photo_url
    */
function find_best_image($photo_url) {
    $alt_photo_url = false;
    if (stripos($photo_url,'i.cdn.turner.com/ireport') > 0) {
        // CNN iReports stores 3 versions of image: _sm, _md and _lg. Go for large.
        $base = basename($photo_url,'jpg');
        $repl = false;
        if (stripos($photo_url,'_sm') > 0) {
            $repl = '_sm';
        } else if (stripos($photo_url,'_md') > 0) {
            $repl = '_md';
        }
        if ($repl) {
            $alt_photo_url = substr_replace($photo_url,'_lg',strlen($photo_url)-7,3);
        }
    } else if (stripos($photo_url,'http://www.ireport.com/docs/DOC') !== false) {
        // Some iReports photo_urls point to the embedding page. The default image
        // is contained in a link tag with ref value "image_src".
        $alt_photo_url = find_image_in_cnn_page($photo_url);
    } else if (stripos($photo_url,'http://sitelife.cbc.ca') !== false) {
        // Sitelife stores 3 versions of image: .Small, .Medium, Large and .Full. Go for Full.
        $alt_photo_url = find_best_sitelife_image($photo_url);
    }
    return $alt_photo_url;
}

// TODO: See parsecnn.php for how to get image URL from link tag in a document page
function find_image_in_cnn_page($page_url) {
    $alt_photo_url = $page_url; // just echo input for now
    return $alt_photo_url;
}

function find_best_sitelife_image($photo_url) {
    $alt_photo_url = false;
    $base = basename($photo_url,'jpg');
    $repl = false;
    if (stripos($photo_url,'.Small') > 0) {
        $repl = '.Small';
    } else if (stripos($photo_url,'.Medium') > 0) {
        $repl = '.Medium';
    } else if (stripos($photo_url,'.Large') > 0) {
        $repl = '.Large';
    }
    if ($repl) {
        $l = strlen($repl);
        $alt_photo_url = substr_replace($photo_url,'.Full',strlen($photo_url)-$l - 5).".jpg";
    }
    return $alt_photo_url;
}
