<?php
/**
 * @name         Person Finder Interchange Format
 * @version      2
 * @package      pfif
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0223
 */


require_once('webimage.inc');

define("PFIF_NS_PREFIX", "pfif");
define("PFIF_1_2_NAMESPACE", "http://zesty.ca/pfif/1.2");
define("PFIF_1_3_NAMESPACE", "http://zesty.ca/pfif/1.3");
define("PFIF_V_1_2", "1.2");
define("PFIF_V_1_3", "1.3");

define("PFIF_IMG_CACHE_DIR", "tmp/pfif_cache/");
define("PFIF_IMG_THUMB_PREFIX", "thumb_");

/**
 * Transform local time to UTC time.
 *
 */
function utc_date($d) {
   if (!empty($d)) {
      $ts = strtotime($d);
      $z = gmdate('Y-m-d\TH:i:s\Z', $ts);
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
      $z = date('Y-m-d H:i:s', $ts);
   } else {
      $z = null;
   }
   return $z;
}

/**
 * Map sahana opt_status value to PFIF value.
 * @see shn_map_status_from_pfif
 */
function shn_map_status_to_pfif($status) {
   $status_map =
           array('unk' => 'information_sought',
               'fnd' => 'believed_alive',
               'inj' => 'believed_alive',
               'ali' => 'believed_alive',
               'mis' => 'believed_missing',
               'dec' => 'believed_dead');

   $value = 'information_sought'; //default
   $value = $status_map[$status];
   return $value;
}

/**
 *    Map note's found and status fields to sahana opt_status value.
 */
function shn_map_status_from_pfif($status, $found, $old_status) {
   // PFIF to PL mapping.
   $status_map =
           array('information_sought' => 'unk',
               'believed_alive' => 'ali',
               'believed_missing' => 'mis',
               'believed_dead' => 'dec',
               'is_note_author' => 'ali');

   // Overrider earlier statuses using this mapping.
   $status_ranking_map =
           array('unk' => array('unk' => 'unk',
                   'ali' => 'ali',
                   'mis' => 'mis',
                   'dec' => 'dec'),
               'mis' => array('unk' => 'mis',
                   'ali' => 'ali',
                   'mis' => 'mis',
                   'dec' => 'dec'),
               'fnd' => array('unk' => 'fnd',
                   'ali' => 'ali',
                   'mis' => 'fnd',
                   'dec' => 'dec'),
               'inj' => array('unk' => 'inj',
                   'ali' => 'ali',
                   'mis' => 'inj',
                   'dec' => 'dec'),
               'dec' => array('unk' => 'dec',
                   'ali' => 'ali',
                   'mis' => 'dec',
                   'dec' => 'dec'),
               'ali' => array('unk' => 'ali',
                   'ali' => 'ali',
                   'mis' => 'ali',
                   'dec' => 'dec'));

   // Map new status from PFIF record.
   $new_status = 'unk';  // default for unspecified status
   $old_status = (empty($old_status)) ? 'unk' : $old_status;
   if (!empty($status)) {
      $new_status = $status_map[$status];
   }
   // We have to do something with the "found" field if present. Since it means
   // the person was directly contacted, have it override any accompanying status
   // by always translating to "alive".
   if ($found == 'true') {
      $new_status = 'ali';
   }

   // Do the ranking mapping.
   $result = $status_ranking_map[$old_status][$new_status];
   //pfif_error_log("Old status: " . $old_status . " new status: " . $result);
   return $result;
}

/**
 * Maps gender, if given, to PFIF sex element.
 *
 * @param personRecord  resultset from db for person of interest
 * @param person        Person instance containing original imported PFIF person record.
 *
 */
function shn_map_gender_to_pfif($personRecord, $source_person) {
   $gender_map = array('mal' => 'male', 'fml' => 'female', 'cpx' => 'other'); // PFIF defines an 'oth)er' category, but it is not clear what that means.
   // The spec states that if gender is unknown it should be omitted.
   $g = '';
   if (!empty($personRecord['opt_gender'])) {
      $g = $gender_map[$personRecord['opt_gender']];
      //DEBUG: pfif_error_log("mapped gender to ".$g);
   }
   return $g;
}

function shn_map_gender_from_pfif($pfif_sex) {
   $gender_map = array('male' => 'mal', 'female' => 'fml', 'other' => 'cpx'); 
   // PFIF defines an 'oth)er' category, but it is not clear what that means.
   // It does not mean unknown, however. So we map it to complex.
   return array_key_exists($pfif_sex, $gender_map)? $gender_map[$pfif_sex] : null;
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
      $age = $personRecord['minAge'] . '-' . $personRecord['maxAge'];
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
      $range = explode('-', $age);
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
 *  Retrieves the image referenced by photo_url. If successful, returns image info for insertion in image table.
 */
function fetch_image($photo_url, $person_record_id) {
   global $failed_images;

   $result = array();
   // var_dump('id',$person_record_id,'photo_url',$photo_url,'empty?',empty($photo_url));
   if (!empty($photo_url)) {
      // pfif_error_log("Found photo for ".$person->person_record_id." at ".$person->photo_url);
      $image = new WebImage($photo_url, $person_record_id);
      // pfif_error_log("new WebImage() returns:".var_export($image,true));
      if ($image->is_initialized()) {
         // pfif_error_log("image type: $image->type width: $image->width height; $image->height");
         $result['image_type'] = $image->type;
         $result['image_height'] = $image->height;
         $result['image_width'] = $image->width;
         $result['original_filename'] = $photo_url;

         // Gen cache filename from id, ..
         $filePath = '/opt/pl/www/'.PFIF_IMG_CACHE_DIR;
         $fileName = str_replace("/", "SLASH", $person_record_id) . "__" . rand(1000000000, 1999999999) . "." . $image->type;
         $localUrl = PFIF_IMG_CACHE_DIR . $fileName;

         // and write image to cache
         $handle = fopen($filePath . "/" . $fileName, 'w');
         $status = fwrite($handle, $image->image);
         fclose($handle);

         if ($status) { // write succeeded
            $result['url'] = $localUrl;

            // Create thumbnail if image height exceeds threshold
            if ($image->height > 320 || $image->width > 320) {
               $thumbName = PFIF_IMG_THUMB_PREFIX . $fileName;
               shn_image_resize_height($filePath . $fileName, $filePath . $thumbName, 320);
            } else {
               $thumbName = $fileName;
            }
            $result['url_thumb'] = PFIF_IMG_CACHE_DIR . $thumbName;
         } else { // image write failed
            pfif_error_log("fetch_image:error writing file " . $filePath . "/" . $fileName);
         }
         $_SESSION['pfif_info']['images_in'] += 1;
      } else {
         $failed_images[] = array('p_uuid' => $person_record_id, 'url' => $photo_url);
      }
   } else {
      // pfif_error_log("no photo for ".$person->person_record_id);
   }
   return $result;
}

function pfif_error_log($msg) {
   error_log("[".date("Y-m-d H:i:s")."] $msg");
}

