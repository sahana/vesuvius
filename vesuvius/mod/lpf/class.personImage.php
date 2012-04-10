<?php
/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personImage
* @version      15
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
	public $principal;

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
	public $Oprincipal;

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
	private $sql_principal;

	private $sql_Oimage_id;
	private $sql_Op_uuid;
	private $sql_Oimage_type;
	private $sql_Oimage_height;
	private $sql_Oimage_width;
	private $sql_Ocreated;
	private $sql_Ourl;
	private $sql_Ourl_thumb;
	private $sql_Ooriginal_filename;
	private $sql_Oprincipal;

	public $updated_by_p_uuid;
	public $tags;
	public $invalid; // false by default, true when the image data turns out to be an invalid mime type


	// Constructor
	public function __construct() {

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
		$this->principal             = 1;

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
		$this->Oprincipal             = 1;

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
		$this->sql_principal         = null;

		$this->sql_Oimage_id          = null;
		$this->sql_Op_uuid            = null;
		$this->sql_Oimage_type        = null;
		$this->sql_Oimage_height      = null;
		$this->sql_Oimage_width       = null;
		$this->sql_Ocreated           = null;
		$this->sql_Ourl               = null;
		$this->sql_Ourl_thumb         = null;
		$this->sql_Ooriginal_filename = null;
		$this->sql_Oprincipal         = null;

		$this->updated_by_p_uuid     = null;
		$this->tags                  = array();
		$this->invalid               = false;
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
		$this->principal             = null;

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
		$this->Oprincipal             = null;

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
		$this->sql_principal         = null;

		$this->sql_Oimage_id          = null;
		$this->sql_Op_uuid            = null;
		$this->sql_Oimage_type        = null;
		$this->sql_Oimage_height      = null;
		$this->sql_Oimage_width       = null;
		$this->sql_Ocreated           = null;
		$this->sql_Ourl               = null;
		$this->sql_Ourl_thumb         = null;
		$this->sql_Ooriginal_filename = null;
		$this->sql_Oprincipal         = null;
		$this->sql_Oprincipal         = null;

		$this->tags                  = null;
		$this->updated_by_p_uuid     = null;
		$this->invalid               = null;
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
			$this->principal             = $result->fields['principal'];
			$this->fullSizePath          = $global['approot']."www/".$result->fields['url'];
			$this->thumbnailPath         = $global['approot']."www/".$result->fields['url_thumb'];
			$this->fileContent           = file_get_contents($global['approot']."www/".$result->fields['url']);
			$this->encode();

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
			$this->Oprincipal             = $this->principal;
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
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "image load loadImageTags 1 ((".$q."))"); }
		while(!$result == NULL && !$result->EOF) {

			$t = new personImageTag();
			$t->image_id = $this->image_id;
			$t->tag_id = $result->fields['tag_id'];
			$t->load();
			$this->tags[] = $t;
			$result->MoveNext();
		}
	}


	// Delete function
	public function delete() {

		// just to mysql-ready the data nodes...
		$this->sync();

		// delete all associated tags
		$this->deleteImageTags();

		// remove from filesystem this image
		$this->unwrite();

		// delete from db
		$q = "
			DELETE FROM image
			WHERE image_id = ".$this->sql_image_id.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person image delete 1 ((".$q."))"); }
	}


	private function deleteImageTags() {

		foreach($this->tags as $tag) {
			$tag->delete();
		}
	}


	// synchronize SQL value strings with public attributes
	private function sync() {

		// build SQL strings from values

		$this->sql_image_id          = ($this->image_id          === null) ? "NULL" : "'".(int)$this->image_id."'";
		$this->sql_p_uuid            = ($this->p_uuid            === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->p_uuid)."'";
		$this->sql_image_type        = ($this->image_type        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->image_type)."'";
		$this->sql_image_height      = ($this->image_height      === null) ? "NULL" : "'".(int)$this->image_height."'";
		$this->sql_image_width       = ($this->image_width       === null) ? "NULL" : "'".(int)$this->image_width."'";
		$this->sql_created           = ($this->created           === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->created)."'";
		$this->sql_url               = ($this->url               === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url)."'";
		$this->sql_url_thumb         = ($this->url_thumb         === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url_thumb)."'";
		$this->sql_original_filename = ($this->original_filename === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->original_filename)."'";
		$this->sql_principal         = ($this->principal         === null) ? "'1'"  : "'".mysql_real_escape_string((int)$this->principal)."'";

		$this->sql_Oimage_id          = ($this->Oimage_id          === null) ? "NULL" : "'".(int)$this->Oimage_id."'";
		$this->sql_Op_uuid            = ($this->Op_uuid            === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Op_uuid)."'";
		$this->sql_Oimage_type        = ($this->Oimage_type        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Oimage_type)."'";
		$this->sql_Oimage_height      = ($this->Oimage_height      === null) ? "NULL" : "'".(int)$this->Oimage_height."'";
		$this->sql_Oimage_width       = ($this->Oimage_width       === null) ? "NULL" : "'".(int)$this->Oimage_width."'";
		$this->sql_Ocreated           = ($this->Ocreated           === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ocreated)."'";
		$this->sql_Ourl               = ($this->Ourl               === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ourl)."'";
		$this->sql_Ourl_thumb         = ($this->Ourl_thumb         === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ourl_thumb)."'";
		$this->sql_Ooriginal_filename = ($this->Ooriginal_filename === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ooriginal_filename)."'";
		$this->sql_Oprincipal         = ($this->Oprincipal         === null) ? "'1'"  : "'".mysql_real_escape_string((int)$this->Oprincipal)."'";
	}


	public function decode() {

		$this->fileContent = base64_decode($this->fileContentBase64);
	}


	public function encode() {

		$this->fileContentBase64 = base64_encode($this->fileContent);
	}


	private function unwrite() {

		global $global;

		$webroot  = $global['approot']."www/";
		$file     = $webroot.$this->url;
		$thumb    = $webroot.$this->url_thumb;
		$original = str_replace("full.jpg", "original", $file);

		if(!unlink($file)) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, "unable to delete file", "person image unwrite 1 ((".$file."))");
		} else {
			if(file_exists($original)) {
				unlink($original);
			}
			// we don't log problems deleting originals as we dont always have them and it would fill up the log...
		}
		// only delete the thumb if its not the same as the fullsized file
		if($thumb != $file) {
			if(!unlink($thumb)) {
				daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, "unable to delete file", "person image unwrite 2 ((".$thumb."))");
			}
		}
	}


	private function write() {

		global $global;
		require_once($global['approot']."inc/lib_image.inc");

		// base64 to hex
		$this->decode();

		$filename = str_replace("/", "_", $this->p_uuid); // make pl.nlm.nih.gov/person.123456 into pl.nlm.nih.gov_person.123456
		$filename = $filename."_".$this->image_id."_"; // filename now like pl.nlm.nih.gov_person.123456_112233_
		$path = $global['approot']."www/tmp/plus_cache/".$filename; // path is now like /opt/pl/www/tmp/plus_cache/pl.nlm.nih.gov_person.123456_112233_

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
		} elseif(stripos($mime,"jpeg") !== FALSE) {
			$ext = ".jpg";
		} else {
			$this->invalid = true;
		}

		if(!$this->invalid) {

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
			chmod($path."full".$ext,  0777);
			chmod($path."thumb".$ext, 0777);
		}
		chmod($path."original", 0777);
	}


	// save the image
	public function insert() {

		// save image to disk
		$this->write();

		// db insert only a valid image
		if(!$this->invalid) {

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
					original_filename,
					principal )
				VALUES (
					".$this->sql_image_id.",
					".$this->sql_p_uuid.",
					".$this->sql_image_type.",
					".$this->sql_image_height.",
					".$this->sql_image_width.",
					".$this->sql_url.",
					".$this->sql_url_thumb.",
					".$this->sql_original_filename.",
					".$this->sql_principal." );
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage insert ((".$q."))"); }

			$this->insertImageTags();
		}
	}


	private function insertImageTags() {

		foreach($this->tags as $tag) {
			$tag->insert();
		}
	}


	/** Update / Save Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Update / Save Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Update / Save Functions ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


	// save the person (subsequent save = update)
	public function update() {

		$this->sync();
		$this->saveRevisions();

		$q = "
			UPDATE image
			SET
				p_uuid            = ".$this->sql_p_uuid.",
				image_type        = ".$this->sql_image_type.",
				image_height      = ".$this->sql_image_height.",
				image_width       = ".$this->sql_image_width.",
				url               = ".$this->sql_url.",
				url_thumb         = ".$this->sql_url_thumb.",
				original_filename = ".$this->sql_original_filename."
				principal         = ".$this->sql_principal."
			WHERE image_id = ".$this->sql_image_id.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage update ((".$q."))"); }

		$this->updateImageTags();
	}


	private function updateImageTags() {

		foreach($this->tags as $tag) {
			$tag->updated_by_p_uuid = $this->updated_by_p_uuid;
			$tag->update();
		}
	}


	// save any changes since object was loaded as revisions
	function saveRevisions() {

		if($this->p_uuid            != $this->Op_uuid)            { $this->saveRevision($this->sql_p_uuid,            $this->sql_Op_uuid,            'image', 'p_uuid'            ); }
		if($this->image_type        != $this->Oimage_type)        { $this->saveRevision($this->sql_image_type,        $this->sql_Oimage_type,        'image', 'image_type'        ); }
		if($this->image_height      != $this->Oimage_height)      { $this->saveRevision($this->sql_image_height,      $this->sql_Oimage_height,      'image', 'image_height'      ); }
		if($this->image_width       != $this->Oimage_width)       { $this->saveRevision($this->sql_image_width,       $this->sql_Oimage_width,       'image', 'image_width'       ); }
		if($this->url               != $this->Ourl)               { $this->saveRevision($this->sql_url,               $this->sql_Ourl,               'image', 'url'               ); }
		if($this->url_thumb         != $this->Ourl_thumb)         { $this->saveRevision($this->sql_url_thumb,         $this->sql_Ourl_thumb,         'image', 'url_thumb'         ); }
		if($this->original_filename != $this->Ooriginal_filename) { $this->saveRevision($this->sql_original_filename, $this->sql_Ooriginal_filename, 'image', 'original_filename' ); }
		if($this->principal         != $this->Oprincipal)         { $this->saveRevision($this->sql_principal,         $this->sql_Oprincipal,         'image', 'principal'         ); }
	}


	// save the revision
	function saveRevision($newValue, $oldValue, $table, $column) {

		// note the revision
		$q = "
			INSERT into person_updates (`p_uuid`, `updated_table`, `updated_column`, `old_value`, `new_value`, `updated_by_p_uuid`)
			VALUES (".$this->sql_p_uuid.", '".$table."', '".$column."', ".$oldValue.", ".$newValue.", '".$this->updated_by_p_uuid."');
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage saveRevision ((".$q."))"); }
	}
}



