<?php
/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personImageTag
* @version      11
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class personImageTag {

	public $tag_id;
	public $image_id;
	public $tag_x;
	public $tag_y;
	public $tag_w;
	public $tag_h;
	public $tag_text;

	public $Otag_id;
	public $Oimage_id;
	public $Otag_x;
	public $Otag_y;
	public $Otag_w;
	public $Otag_h;
	public $Otag_text;

	private $sql_tag_id;
	private $sql_image_id;
	private $sql_tag_x;
	private $sql_tag_y;
	private $sql_tag_w;
	private $sql_tag_h;
	private $sql_tag_text;

	private $sql_Otag_id;
	private $sql_Oimage_id;
	private $sql_Otag_x;
	private $sql_Otag_y;
	private $sql_Otag_w;
	private $sql_Otag_h;
	private $sql_Otag_text;

	public $updated_by_p_uuid;


	// Constructor
	public function __construct() {

		global $global;
		$this->db = $global['db'];

		$this->tag_id   = null;
		$this->image_id = null;
		$this->tag_x    = null;
		$this->tag_y    = null;
		$this->tag_w    = null;
		$this->tag_h    = null;
		$this->tag_text = null;

		$this->Otag_id   = null;
		$this->Oimage_id = null;
		$this->Otag_x    = null;
		$this->Otag_y    = null;
		$this->Otag_w    = null;
		$this->Otag_h    = null;
		$this->Otag_text = null;

		$this->sql_tag_id   = null;
		$this->sql_image_id = null;
		$this->sql_tag_x    = null;
		$this->sql_tag_y    = null;
		$this->sql_tag_w    = null;
		$this->sql_tag_h    = null;
		$this->sql_tag_text = null;

		$this->sql_Otag_id   = null;
		$this->sql_Oimage_id = null;
		$this->sql_Otag_x    = null;
		$this->sql_Otag_y    = null;
		$this->sql_Otag_w    = null;
		$this->sql_Otag_h    = null;
		$this->sql_Otag_text = null;

		$this->updated_by_p_uuid = null;
	}


	// Destructor
	public function __destruct() {

		$this->tag_id   = null;
		$this->image_id = null;
		$this->tag_x    = null;
		$this->tag_y    = null;
		$this->tag_w    = null;
		$this->tag_h    = null;
		$this->tag_text = null;

		$this->Otag_id   = null;
		$this->Oimage_id = null;
		$this->Otag_x    = null;
		$this->Otag_y    = null;
		$this->Otag_w    = null;
		$this->Otag_h    = null;
		$this->Otag_text = null;

		$this->sql_tag_id   = null;
		$this->sql_image_id = null;
		$this->sql_tag_x    = null;
		$this->sql_tag_y    = null;
		$this->sql_tag_w    = null;
		$this->sql_tag_h    = null;
		$this->sql_tag_text = null;

		$this->sql_Otag_id   = null;
		$this->sql_Oimage_id = null;
		$this->sql_Otag_x    = null;
		$this->sql_Otag_y    = null;
		$this->sql_Otag_w    = null;
		$this->sql_Otag_h    = null;
		$this->sql_Otag_text = null;

		$this->updated_by_p_uuid = null;
	}


	// initializes some values for a new instance (instead of when we load a previous instance)
	public function init() {

		$this->tag_id = shn_create_uuid("image_tag");
	}


	// load data from db
	public function load() {

		$q = "
			SELECT *
			FROM image_tag
			WHERE tag_id = '".mysql_real_escape_string((string)$this->tag_id)."' ;
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "imageTag load 1 ((".$q."))"); }

		if($result != NULL && !$result->EOF) {

			$this->tag_id   = $result->fields['tag_id'];
			$this->image_id = $result->fields['image_id'];
			$this->tag_x    = $result->fields['tag_x'];
			$this->tag_y    = $result->fields['tag_y'];
			$this->tag_w    = $result->fields['tag_w'];
			$this->tag_h    = $result->fields['tag_h'];
			$this->tag_text = $result->fields['tag_text'];

			$this->Otag_id   = $result->fields['tag_id'];
			$this->Oimage_id = $result->fields['image_id'];
			$this->Otag_x    = $result->fields['tag_x'];
			$this->Otag_y    = $result->fields['tag_y'];
			$this->Otag_w    = $result->fields['tag_w'];
			$this->Otag_h    = $result->fields['tag_h'];
			$this->Otag_text = $result->fields['tag_text'];
		}
	}


	// Delete function
	public function delete() {

		// just to mysql-ready the data nodes...
		$this->sync();

		$q = "
			DELETE FROM image_tag
			WHERE tag_id = ".$this->sql_tag_id.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person delete imageTag 1 ((".$q."))"); }
	}


	// synchronize SQL value strings with public attributes
	private function sync() {

		// build SQL value strings
		$this->sql_tag_id   = ($this->tag_id   === null) ? "NULL" : (int)$this->tag_id;
		$this->sql_image_id = ($this->image_id === null) ? "NULL" : (int)$this->image_id;
		$this->sql_tag_x    = ($this->tag_x    === null) ? "NULL" : (int)$this->tag_x;
		$this->sql_tag_y    = ($this->tag_y    === null) ? "NULL" : (int)$this->tag_y;
		$this->sql_tag_w    = ($this->tag_w    === null) ? "NULL" : (int)$this->tag_w;
		$this->sql_tag_h    = ($this->tag_h    === null) ? "NULL" : (int)$this->tag_h;
		$this->sql_tag_text = ($this->tag_text === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->tag_text)."'";

		$this->sql_Otag_id   = ($this->Otag_id   === null) ? "NULL" : (int)$this->Otag_id;
		$this->sql_Oimage_id = ($this->Oimage_id === null) ? "NULL" : (int)$this->Oimage_id;
		$this->sql_Otag_x    = ($this->Otag_x    === null) ? "NULL" : (int)$this->Otag_x;
		$this->sql_Otag_y    = ($this->Otag_y    === null) ? "NULL" : (int)$this->Otag_y;
		$this->sql_Otag_w    = ($this->Otag_w    === null) ? "NULL" : (int)$this->Otag_w;
		$this->sql_Otag_h    = ($this->Otag_h    === null) ? "NULL" : (int)$this->Otag_h;
		$this->sql_Otag_text = ($this->Otag_text === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Otag_text)."'";
	}


	// save the image tag
	public function insert() {

		$this->sync();
		$q = "
			INSERT INTO image_tag (
				tag_id,
				image_id,
				tag_x,
				tag_y,
				tag_w,
				tag_h,
				tag_text )
			VALUES (
				".$this->sql_tag_id.",
				".$this->sql_image_id.",
				".$this->sql_tag_x.",
				".$this->sql_tag_y.",
				".$this->sql_tag_w.",
				".$this->sql_tag_h.",
				".$this->sql_tag_text." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag insert ((".$q."))"); }
	}


	// Update / Save Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Update / Save Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Update / Save Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// save the person (subsequent save = update)
	public function update() {

		$this->sync();
		$this->saveRevisions();

		$q = "
			UPDATE image_tag
			SET
				image_id = ".$this->sql_image_id.",
				tag_x    = ".$this->sql_tag_x.",
				tag_y    = ".$this->sql_tag_y.",
				tag_w    = ".$this->sql_tag_w.",
				tag_h    = ".$this->sql_tag_h.",
				tag_text = ".$this->sql_tag_text."

			WHERE tag_id = ".$this->sql_tag_id.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag update ((".$q."))"); }
	}


	// save any changes since object was loaded as revisions
	function saveRevisions() {

		if($this->image_id != $this->Oimage_id) { $this->saveRevision($this->sql_image_id, $this->sql_Oimage_id, 'image_tag', 'image_id' ); }
		if($this->tag_x    != $this->Otag_x)    { $this->saveRevision($this->sql_tag_x,    $this->sql_Otag_x,    'image_tag', 'tag_x'    ); }
		if($this->tag_y    != $this->Otag_y)    { $this->saveRevision($this->sql_tag_y,    $this->sql_Otag_y,    'image_tag', 'tag_y'    ); }
		if($this->tag_w    != $this->Otag_w)    { $this->saveRevision($this->sql_tag_w,    $this->sql_Otag_w,    'image_tag', 'tag_w'    ); }
		if($this->tag_h    != $this->Otag_h)    { $this->saveRevision($this->sql_tag_h,    $this->sql_Otag_h,    'image_tag', 'tag_h'    ); }
		if($this->tag_text != $this->Otag_text) { $this->saveRevision($this->sql_tag_text, $this->sql_Otag_text, 'image_tag', 'tag_text' ); }
	}


	// save the revision
	function saveRevision($newValue, $oldValue, $table, $column) {

		// note the revision
		$q = "
			INSERT into person_updates (`p_uuid`, `updated_table`, `updated_column`, `old_value`, `new_value`, `updated_by_p_uuid`)
			VALUES (".$this->sql_p_uuid.", '".$table."', '".$column."', ".$oldValue.", ".$newValue.", '".$this->updated_by_p_uuid."');
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag saveRevision ((".$q."))"); }
	}
}



