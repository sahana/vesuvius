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


// WebImage -- a class to encapsulate the image table

require_once($global['approot'] . "/inc/lib_image.inc");

class WebImage {

   private $id = null;
   public $image = null;    // The binary image
   public $type = "";       // MIME type for image
   public $height = 0;      // The number of lines in the image
   public $width = 0;       // The number of pixels per line
   public $url = null;      // The source URL for the image
   private $initialized = false;

   public function __construct($url = null, $uuid = null) {
      // pfif_error_log('WebImage:'.$url.','.$uuid);
      if (isset($url) && isset($uuid)) {
         // pfif_error_log('WebImage:args ok');
         $this->set_id($uuid);
         $this->_init($url);
      } else {
         pfif_error_log('shn_mod_pfif_WebImage: bad arguments (url = ' . $url . ' uuid= ' . $uuid . ')');
      }
   }

   public function is_initialized() {
      return $this->initialized;
   }

   public function set_id($uuid) {
      $this->id = $uuid;
   }

   public function set_image($url) {
      $status = false;
      if (isset($url)) {
         $this->_init($url);
         $status = true;
      }
      return $status;
   }

   private function _init($url) {
      // Check the URL to be sure it exists and is for a supported image type
      // Fetch the image
      $image_data = false;
      $image_info = @getimagesize($url);
      //pfif_error_log('_init.image_info:'.var_export($image_info,true));

      $type = ($image_info != false) ? $image_info['mime'] : false;
      // pfif_error_log('_init.type:'.var_export($type,true));

      $is_valid_type = ($type != false) ? shn_check_valid_image_type($type) : false;
      // pfif_error_log('is_valid_type:'.var_export($is_valid_type,true));

      if ($is_valid_type) {
         // FIXME (chc 1/31/2010):: Use shn_image_resize_height to rescale oversize images on import
         $image_data = file_get_contents($url, FILE_BINARY);
         if ($image_data === false) {
            pfif_error_log('_init.file_get_contents failed for: ' . $url);
         }
      }
      // Set the image type and size.
      if ($image_data !== false) {
         $this->url = $url; //$saveFile;
         $this->image = $image_data; // null;
         $this->width = $image_info[0];
         $this->height = $image_info[1];
         list(, $this->type) = explode('/', $type);
         $this->initialized = true;
         unset($image_data);
      } else {
         // pfif_error_log("Image get failed for ".$url);
      }
   }

}
