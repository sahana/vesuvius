<?php
/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personImageTag
* @version      10
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

	private $sql_tag_id;
	private $sql_image_id;
	private $sql_tag_x;
	private $sql_tag_y;
	private $sql_tag_w;
	private $sql_tag_h;
	private $sql_tag_text;

	// Constructor
	public function __construct() {
		// init db
		global $global;
		$this->db = $global['db'];

		// init values
		$this->tag_id   = null;
		$this->image_id = null;
		$this->tag_x    = null;
		$this->tag_y    = null;
		$this->tag_w    = null;
		$this->tag_h    = null;
		$this->tag_text = null;

		$this->sql_tag_id   = null;
		$this->sql_image_id = null;
		$this->sql_tag_x    = null;
		$this->sql_tag_y    = null;
		$this->sql_tag_w    = null;
		$this->sql_tag_h    = null;
		$this->sql_tag_text = null;
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

		$this->sql_tag_id   = null;
		$this->sql_image_id = null;
		$this->sql_tag_x    = null;
		$this->sql_tag_y    = null;
		$this->sql_tag_w    = null;
		$this->sql_tag_h    = null;
		$this->sql_tag_text = null;

		// make sure tables are safe :)
		$q = "UNLOCK TABLES;";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag unlock tables ((".$q."))"); }
	}


	// initializes some values for a new instance (instead of when we load a previous instance)
	public function init() {
		$this->tag_id = shn_create_uuid("image_tag");
	}


	// synchronize SQL value strings with public attributes
	private function sync() {
		global $global;

		// build SQL value strings

		$this->sql_tag_id   = ($this->tag_id   === null) ? "NULL" : (int)$this->tag_id;
		$this->sql_image_id = ($this->image_id === null) ? "NULL" : (int)$this->image_id;
		$this->sql_tag_x    = ($this->tag_x    === null) ? "NULL" : (int)$this->tag_x;
		$this->sql_tag_y    = ($this->tag_y    === null) ? "NULL" : (int)$this->tag_y;
		$this->sql_tag_w    = ($this->tag_w    === null) ? "NULL" : (int)$this->tag_w;
		$this->sql_tag_h    = ($this->tag_h    === null) ? "NULL" : (int)$this->tag_h;
		$this->sql_tag_text = ($this->tag_text === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->tag_text)."'";
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
}



