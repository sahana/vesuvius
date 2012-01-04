<?php
/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personImage
* @version      10
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class personImage {

	public $image_id;
	public $p_uuid;
	public $image_type;
	public $image_height;
	public $image_width;
	public $created;
	public $url;
	public $url_thumb;
	public $original_filename;
	public $fileContentBase64;
	public $fileContent;
	public $fullSizePath;
	public $thumbnailPath;

	public $Oimage_id;
	public $Op_uuid;
	public $Oimage_type;
	public $Oimage_height;
	public $Oimage_width;
	public $Ocreated;
	public $Ourl;
	public $Ourl_thumb;
	public $Ooriginal_filename;
	public $OfileContentBase64;
	public $OfileContent;
	public $OfullSizePath;
	public $OthumbnailPath;

	private $sql_image_id;
	private $sql_p_uuid;
	private $sql_image_type;
	private $sql_image_height;
	private $sql_image_width;
	private $sql_created;
	private $sql_url;
	private $sql_url_thumb;
	private $sql_original_filename;

	public $tags;


	// Constructor
	public function __construct() {
		// init db
		global $global;
		$this->db = $global['db'];

		$this->image_id              = null;
		$this->p_uuid                = null;
		$this->image_type            = null;
		$this->image_height          = null;
		$this->image_width           = null;
		$this->created               = null;
		$this->url                   = null;
		$this->url_thumb             = null;
		$this->original_filename     = null;
		$this->fileContentBase64     = null;
		$this->fileContent           = null;
		$this->fullSizePath          = null;
		$this->thumbnailPath         = null;

		$this->Oimage_id              = null;
		$this->Op_uuid                = null;
		$this->Oimage_type            = null;
		$this->Oimage_height          = null;
		$this->Oimage_width           = null;
		$this->Ocreated               = null;
		$this->Ourl                   = null;
		$this->Ourl_thumb             = null;
		$this->Ooriginal_filename     = null;
		$this->OfileContentBase64     = null;
		$this->OfileContent           = null;
		$this->OfullSizePath          = null;
		$this->OthumbnailPath         = null;

		$this->sql_image_id          = null;
		$this->sql_p_uuid            = null;
		$this->sql_image_type        = null;
		$this->sql_image_height      = null;
		$this->sql_image_width       = null;
		$this->sql_created           = null;
		$this->sql_url               = null;
		$this->sql_url_thumb         = null;
		$this->sql_original_filename = null;

		$this->tags                  = array();
	}


	// Destructor
	public function __destruct() {
		$this->image_id              = null;
		$this->p_uuid                = null;
		$this->image_type            = null;
		$this->image_height          = null;
		$this->image_width           = null;
		$this->created               = null;
		$this->url                   = null;
		$this->url_thumb             = null;
		$this->original_filename     = null;
		$this->fileContentBase64     = null;
		$this->fileContent           = null;
		$this->fullSizePath          = null;
		$this->thumbnailPath         = null;

		$this->Oimage_id              = null;
		$this->Op_uuid                = null;
		$this->Oimage_type            = null;
		$this->Oimage_height          = null;
		$this->Oimage_width           = null;
		$this->Ocreated               = null;
		$this->Ourl                   = null;
		$this->Ourl_thumb             = null;
		$this->Ooriginal_filename     = null;
		$this->OfileContentBase64     = null;
		$this->OfileContent           = null;
		$this->OfullSizePath          = null;
		$this->OthumbnailPath         = null;

		$this->sql_image_id          = null;
		$this->sql_p_uuid            = null;
		$this->sql_image_type        = null;
		$this->sql_image_height      = null;
		$this->sql_image_width       = null;
		$this->sql_created           = null;
		$this->sql_url               = null;
		$this->sql_url_thumb         = null;
		$this->sql_original_filename = null;

		$this->tags                  = null;

		// make sure tables are safe :)
		$q = "UNLOCK TABLES;";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage unlock ((".$q."))"); }
	}

	// initializes some values for a new instance (instead of when we load a previous instance)
	public function init() {
		$this->image_id = shn_create_uuid("image");
	}


	// load data from db
	public function load() {

		global $global;

		$q = "
			SELECT *
			FROM image
			WHERE image_id = '".mysql_real_escape_string((string)$this->image_id)."' ;
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "image load 1 ((".$q."))"); }

		if($result != NULL && !$result->EOF) {

			$this->image_id              = $result->fields['image_id'];
			$this->p_uuid                = $result->fields['p_uuid'];
			$this->image_type            = $result->fields['image_type'];
			$this->image_height          = $result->fields['image_width'];
			$this->image_width           = $result->fields['image_height'];
			$this->created               = $result->fields['created'];
			$this->url                   = $result->fields['url'];
			$this->url_thumb             = $result->fields['url_thumb'];
			$this->original_filename     = $result->fields['original_filename'];
			$this->fullSizePath          = $global['approot']."www/".$result->fields['url'];
			$this->thumbnailPath         = $global['approot']."www/".$result->fields['url_thumb'];
			$this->fileContent           = file_get_contents($global['approot']."www/".$result->fields['url']);
			$this->fileContentBase64     = base64_encode($this->fileContent);

			// copy the original values for use in diff'ing an update...
			$this->Oimage_id              = $this->image_id;
			$this->Op_uuid                = $this->p_uuid;
			$this->Oimage_type            = $this->image_type;
			$this->Oimage_height          = $this->image_height;
			$this->Oimage_width           = $this->image_width;
			$this->Ocreated               = $this->created;
			$this->Ourl                   = $this->url;
			$this->Ourl_thumb             = $this->url_thumb;
			$this->Ooriginal_filename     = $this->original_filename;
			$this->OfullSizePath          = $this->fullSizePath;
			$this->OthumbnailPath         = $this->thumbnailPath;
			$this->OfileContent           = $this->fileContent;
			$this->OfileContentBase64     = $this->fileContentBase64;

			$this->loadImageTags();
		}
	}


	private function loadImageTags() {

		// find all image tags for this person
		$q = "
			SELECT *
			FROM image_tag
			WHERE image_id = '".mysql_real_escape_string((string)$this->image_id)."' ;
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "loadImageTags 1"); }
		while(!$result == NULL && !$result->EOF) {

			$t = new personImageTag();
			$t->image_id = $this->image_id;
			$t->tag_id = $result->fields['tag_id'];
			$t->load();
			$this->tags[] = $t;
			$result->MoveNext();
		}
	}


	// synchronize SQL value strings with public attributes
	private function sync() {
		global $global;

		// build SQL strings from values

		$this->sql_image_id          = ($this->image_id          === null) ? "NULL" : (int)$this->image_id;
		$this->sql_p_uuid            = ($this->p_uuid            === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->p_uuid)."'";
		$this->sql_image_type        = ($this->image_type        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->image_type)."'";
		$this->sql_image_height      = ($this->image_height      === null) ? "NULL" : (int)$this->image_height;
		$this->sql_image_width       = ($this->image_width       === null) ? "NULL" : (int)$this->image_width;
		$this->sql_created           = ($this->created           === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->created)."'";
		$this->sql_url               = ($this->url               === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url)."'";
		$this->sql_url_thumb         = ($this->url_thumb         === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url_thumb)."'";
		$this->sql_original_filename = ($this->original_filename === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->original_filename)."'";
	}


	public function decode() {
		$this->fileContent = base64_decode($this->fileContentBase64);
	}


	private function write() {
		global $global;
		require_once($global['approot']."inc/lib_image.inc");

		// base64 to hex
		$this->decode();

		// generate path and filename portion
		$a = explode("/", $this->p_uuid);

		$filename = $a[0]."_".$a[1]; // make pl.nlm.nih.gov/person.123456 into pl.nlm.nih.gov_person.123456
		$filename = $filename."_".$this->image_id."_"; // filename now like person.123456_112233_
		$path = $global['approot']."www/tmp/plus_cache/".$filename; // path is now like /opt/pl/www/tmp/plus_cache/person.123456_112233_

		// save original like /opt/pl/www/tmp/plus_cache/person.123456_112233_original
		file_put_contents($path."original", $this->fileContent);

		// get information from original file
		$info = getimagesize($path."original");
		$this->image_width  = $info[0];
		$this->image_height = $info[1];
		list(,$mime) = explode("/",$info['mime']);
		$mime = strtolower($mime);
		$this->image_type = $mime;
		if(stripos($mime,"png") !== FALSE) {
			$ext = ".png";
		} elseif(stripos($mime,"gif") !== FALSE) {
			$ext = ".gif";
		} else {
			$ext = ".jpg";
		}

		// save full size resampled image like /opt/pl/www/tmp/plus_cache/person.123456_112233_full.ext
		shn_image_resize($path."original", $path."full".$ext, $this->image_width, $this->image_height);

		// save thumb resampled image (320px height) like /opt/pl/www/tmp/plus_cache/person.123456_112233_thumb.ext
		shn_image_resize_height($path."original", $path."thumb".$ext, 320);

		$this->fullSizePath  = $path."full".$ext;
		$this->thumbnailPath = $path."thumb".$ext;

		// update URLs
		$this->url       = "tmp/plus_cache/".$filename."full".$ext;
		$this->url_thumb = "tmp/plus_cache/".$filename."thumb".$ext;

		// make the files world writeable for other users/applications and to handle deletes
		chmod($path."original",   0777);
		chmod($path."full".$ext,  0777);
		chmod($path."thumb".$ext, 0777);
	}


	// save the image
	public function insert() {

		// save image to disk
		$this->write();

		// db insert
		$this->sync();
		$q = "
			INSERT INTO image (
				image_id,
				p_uuid,
				image_type,
				image_height,
				image_width,
				url,
				url_thumb,
				original_filename )
			VALUES (
				'".$this->sql_image_id."',
				".$this->sql_p_uuid.",
				".$this->sql_image_type.",
				'".$this->sql_image_height."',
				'".$this->sql_image_width."',
				".$this->sql_url.",
				".$this->sql_url_thumb.",
				".$this->sql_original_filename." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage insert ((".$q."))"); }

		$this->insertImageTags();
	}


	private function insertImageTags() {
		foreach($this->tags as $tag) {
			$tag->insert();
		}
	}
}



