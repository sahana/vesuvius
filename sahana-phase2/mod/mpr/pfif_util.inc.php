<?php
/**
* @package     pfif
* @version      1.1
* @author       Nilushan Silva <>
* @author       Carl H. Cornwell <ccornwell@mail.nih.gov>
* LastModified: 2010:0304:2003
* License:      LGPL
* @link         TBD
*/
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

define("PFIF_NOTE_CONTAINER_ID" , "pl.nln.nih.gov/note.container");
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
        * Transform date to UTC format.
        *
        */
function utc_date($d) {
    
    // If date had a 'T' separator and 'Z' as last character, then it is already in proper format. Otherwise, assume it needs conversion.
    if (!empty($d)) {
    $ts = strtotime($d);
    $z = gmdate('Y-m-d\TH:i:s\Z',$ts);
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

function shn_full_name_to_first_name($full_name,$family_name) {
    // var_dump("full_name_to_first_name",$full_name,$family_name);
    // FIXME: Temporary hack for Feb HEPL export 
    $tmp = hepl_parse_name($full_name);
    $full_name = $tmp['name'];
    
    $first_name = '';
    if (!isset($family_name)) {
       # print("family_name is not set! <br/>");
        $parts = explode(' ',$full_name);
        $c = count($parts);
        $family_name = $c > 0 ? $parts[$c - 1] : '';
    }
    $first_name = str_replace(' '.$family_name,'',$full_name);
    #print "replacing ".$family_name." with null in ".$full_name." to yield first_name = ".$first_name."<br/>";
    return $first_name;
}

function shn_determine_last_name($full_name,$family_name) {
    if (isset($family_name)) {
        $last_name = $family_name;
    } else {
        // FIXME: Temporary hack for Feb HEPL export 
        $tmp = hepl_parse_name($full_name);
        $full_name = $tmp['name'];
        
        $first_name = '';
        $parts = explode(' ',$full_name);
        $c = count($parts);
        $last_name = $c > 0 ? $parts[$c - 1] : '';
    }
    return $last_name;
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
         *    Map note's found (v1.1 & 1.2) and status (v1.2 only) fields to sahana opt_status value.
         *
         *    FIXME (chc 1/31/2010): Scan text for 'alive', 'well', 'dead', 'injured', 'hurt', etc and
         *                   refine status as possible 
         *                   --  use 'unk' for can't determine status at all, 
         *                               'fnd' for found,  but health status indeterminate, 
         *                               'dec' for deceased and
         *                               'inj' for injured?
         */
function shn_map_status_from_pfif($note) {
    $status_map = 
        array('information_sought'=>'unk',
              'believed_alive'=>'ali',
              'believed_missing'=>'mis',
              'believed_dead'=>'dec',
              'is_note_author'=>'ali');

    $result = '';

    // Look for PFIF 1.2 element in $note->text. If found, convert $note->status value, 
    $text1dot2 = split_text($note->text,PFIF_V_1_2);
    $status = $text1dot2[PFIF_1_2_STS];
    
    // otherwise use $note->found and return 'mis' or 'fnd'.
    if(!empty($status)) {
       $result = $status;
        
    } else {
        $result = $note->found == 'true' ? 'fnd' : 'mis';
    }
    
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
    $gender_map = array('unk'=>'', 'mal'=>'male', 'fml'=>'female'); // PFIF 1.2 defines an 'oth)er' category, but it is not clear what that means. The spec states that if gender is unknown it should be omitted.
    
    // TODO: need to sort out 1.1 vs 1.2 sources. for now, only concerned with local records (chc 2/24/10)
    $g = $gender_map[$personRecord['opt_gender']];
    //DEBUG: error_log("mapped gender to ".$g);
    return $g;
}

function shn_map_gender_from_pfif($pfif_sex) {
    $gender_map = array('male'=>'mal', 'female'=>'fml','other'=>'unk'); //// PFIF 1.2 defines an 'oth)er' category, but it is not clear what that means, so we map to unkown, which means indeterminate or otherwise unreportable as male or female. The spec states that if gender is unknown it should be omitted.

    if (empty($sex)) {
        $g = 'unk'; 
    } else {
        $g = $gender_map[$sex];
    }
}
/**
 *
 * Maps Approximate age, if given, or age range to PFIF age element.
 *
 * @param personRecord  resultset from db for person of interest
 * @param person        Person instance containing original imported PFIF person record
 *
 */
function shn_map_age_to_pfif($personRecord, $source_person) {
    // TODO: need to sort out 1.1 vs 1.2 sources. for now, only concerned with local records (chc 2/24/10)
    if (!empty($personRecord['years_old'])) {
        return $personRecord['years_old']; // perhaps from mpres
    } else {
        // TODO: if opt_age_range empty compute from DOB if present ?? (chc 3/10/2010)
        return $personRecord['opt_age_range']; // perhaps from mpr.add: may be empty
    }
}

/**
     *
     * Maps PFIF age and/or date_of_birth fields to appropriate combination of Sahana
     *  birth_date, years_old and opt_age_group
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
    //                 is psecified to the day. Otherwise, may use partial date to establish age if age is not specified.
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
            $result['opt_age_group'] = $range[0];
        } else {
            $result['opt_age_group'] = round(($range[0]+$range[1])/2);
        }
    } else if (!empty($dob)) {
        $reftime = strtotime($source_date);
        $refdate = getdate($reftime);
        $birthtime = strtotime($dob);
        $birthday = getdate($birthtime);
        $result['opt_age_group'] = $refdate['year'] - $birthday['year'];
    }
    return $result;
}

function split_other($oth,$v) {
    // error_log("splitting ".$oth);
    $result = array();
    $result[PFIF_1_2_AGE] = null;
    $result[PFIF_1_2_SEX] = null;
    $result[PFIF_1_2_DOB] = null;

        $ofs = strlen(PFIF_1_2_OPEN_TAG);
    // Scan for pfif 1.2 block
    $p2start = stripos($oth,PFIF_1_2_OPEN_TAG);
    $p2end = stripos($oth,PFIF_1_2_CLOSE_TAG,$p2start);
    if ($p2start === FALSE) {
        $result['other'] = $oth;
    } else if ($v == '1.2') {
        $tok_start = $p2start + $ofs;
        $p2 = substr($oth,$tok_start,$p2end - $tok_start);
        $delim = ': ';
        $tok = strtok($p2,$delim);
        while ($tok !== FALSE) {
            $result[$tok] = strtok($delim);
            $tok = strtok($delim);
        }
        $result['other'] = substr($oth,0,$p2start);
    } else {
        $p2mid = $p2start+$ofs;
        $result['other'] = substr($oth,0,$p2start).' '.
                           substr($oth,$p2mid,$p2end-$p2mid).
                           substr($oth,$p2end+$ofs+1);
    }
    // error_log(var_export($result,true));
    return $result;
}

function merge_other($age,$dob,$sex) {
    $delim = ': ';
    $result = PFIF_1_2_OPEN_TAG;
    $result .= !empty($age) ? PFIF_1_2_AGE.':'.$age.' ' : '';
    $result .= !empty($dob) ? PFIF_1_2_DOB.':'.$dob.' ' : '';
    $result .= !empty($sex) ?PFIF_1_2_SEX.':'.$sex : '';
    if (strlen($result) > strlen(PFIF_1_2_OPEN_TAG))
        $result .= PFIF_1_2_CLOSE_TAG;
    else
        $result = '';
    return $result;
}

function split_text($text,$v) {
    // print ("splitting'$text' using version $v \n");
    // error_log("splitting ".$text);
    $result = array();
    $result[PFIF_1_2_PID] = null;
    $result[PFIF_1_2_LPID] = null;
    $result[PFIF_1_2_STS] = null;

    $ofs = strlen(PFIF_1_2_OPEN_TAG);
    // Scan for pfif 1.2 block
    $p2start = stripos($text,PFIF_1_2_OPEN_TAG);
    $p2end = stripos($text,PFIF_1_2_CLOSE_TAG,$p2start);
    if ($p2start === FALSE) {
        $result['text'] = $text;
    } else if ($v == '1.2') {
        $tok_start = $p2start + $ofs;
        $p2 = substr($text,$tok_start,$p2end - $tok_start);
        $delim = ': ';
        $tok = strtok($p2,$delim);
        while ($tok !== FALSE) {
            $result[$tok] = strtok($delim);
            $tok = strtok($delim);
        }
        $result['text'] = substr($text,0,$p2start);
    } else {
        $p2mid = $p2start+$ofs;
        $result['text'] = substr($text,0,$p2start).' '.
                           substr($text,$p2mid,$p2end-$p2mid).
                           substr($text,$p2end+$ofs+1);
    }
    // error_log(var_export($result,true));
    // print_r ($result);
    return $result;
}

function merge_text($pid,$l_pid,$status) {
    // print "merging ($pid, $l_pid, $status) into ";

    $delim = ': ';
    $result = PFIF_1_2_OPEN_TAG;
    $result .= !empty($pid) ? PFIF_1_2_PID.':'.$pid.' ' : '';
    $result .= !empty($l_pid) ? PFIF_1_2_LPID.':'.$l_pid.' ' : '';
    $result .= !empty($status) ? PFIF_1_2_STS.':'.$status : '';
    if (strlen($result) > strlen(PFIF_1_2_OPEN_TAG))
        $result .= PFIF_1_2_CLOSE_TAG;
    else
        $result = '';
        
    // print "'$result'\n";
    return $result;
}

/**
    *
    *  Attempts to retrieve the image referenced by photo_url. If successful, queues image info for insertion in image table.
    *
    */
function fetch_image($photo_url,$source_name,$person_record_id) {
    global $failed_images;

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
            include_once('webimage.inc');
            // Google-hack: combine source_url and photo_url 
            // TODO: possible (generalization, if photo-url starts with '/' append to source-url. 
            // May not always work. (chc 3/5/2010)
            $photo_url = $person->photo_url;
            if ($photo_url[0] == '/' && 
                ((stripos($source_name,
                          'chilepersonfinder.appspot') !== FALSE ) ||
                 (stripos($source_name, 
                          'haiticrisis.appspot') !== FALSE )
                 )) {
                $photo_url = 'http://'.$source_name.$photo_url;
                // error_log("Using Google photo: ".$photo_url);
            } else {
                // error_log("Using other photo: ".$photo_url);
            }
            $image = new WebImage($photo_url, $person_record_id);
            // error_log("new WebImage() returns:".var_export($image,true));
            if ($image->is_initialized()){
                // error_log("image type: $image->type width: $image->width height; $image->height");
                $_SESSION['mpr']['entry']['image_type'] = $image->type;
                $_SESSION['mpr']['entry']['image_height'] = $image->height;
                $_SESSION['mpr']['entry']['image_width'] = $image->width;
               
                // Gen cache filename from id, ..
                $filePath = "../../www".PFIF_IMG_CACHE_DIR;
                $fileName = str_replace("/", "SLASH", $person->person_record_id).".".$image->type;
                $localUrl = PFIF_IMG_CACHE_DIR.$fileName;

                // and write image to cache
                $handle = fopen($filePath."/".$fileName,'w');
                $status = fwrite($handle,$image->data);
                fclose($handle);
                
                if ($status) { // write succeeded
                    // Create thumbnail if image height exceeds threshold
                    shn_image_resize_height($filePath.$fileName,
                                        $filePath.
                                        PFIF_IMG_THUMB_PREFIX.
                                        $fileName,
                                        320);
                    $_SESSION['mpr']['entry']['url'] = $localUrl;
                    $_SESSION['mpr']['entry']['image'] = null;
                } else { // image write failed, store in DB
                    $_SESSION['mpr']['entry']['url'] = $image->url;
                    $_SESSION['mpr']['entry']['image'] = $image->image;
                }
            } else { // TODO: Note that add.inc:shn_mpr_addmp_commit() is going to insert an empty image record 
                // TODO: should we stuff the URL so it can be retried later? (chc 2/1/2010)
                error_log("shn_mod_mpr_WebImage:GET image failed for ".$person_record_id." from ".$photo_url);
                $failed_images[] = array('x_uuid'=>$person_record_id,'url'=>$photo_url);
            }
        } else {
            // error_log("no photo for ".$person->person_record_id);
        }
}
