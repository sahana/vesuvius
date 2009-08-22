<?php
	/**
	 *
	 * PHP version 5
	 *
	 * LICENSE: This source file is subject to LGPL license
	 * that is available through the world-wide-web at the following URI:
	 * http://www.gnu.org/copyleft/lesser.html
	 *
	 * @package    Sahana - http://sahana.sourceforge.net
	 * @author     Kethees <sdkethees@gmail.com>
	 * @copyright  Lanka Software Foundation - http://www.opensource.lk
	 */

	Class Person extends Data
	{
		public $p_uuid;
		public $full_name;
		public $first_name;
		public $last_name;
		public $middle_name;
		public $nick_name;
		public $title;
		public $birth_date;
		public $religion;
		public $race;
		public $martial_status;
		public $gender;
		public $occupation;
		public $image_id;
		public $location_id;
		public $description;		
		
		public function __construct($p_uuid)
		{
			Data::__construct();
			
			if($p_uuid != null){
      			$this->get_person($p_uuid);
      		}      		
		}
		
		public function get_person($p_uuid)
		{
			$result = Data::get_person_data($p_uuid);			
			$this->p_uuid = $p_uuid;			
			$this->first_name = $result['first_name'];
			$this->last_name = $result['last_name'];
			$this->middle_name = $result['middle_name'];
			$this->nick_name = $result['nick_name'];
			$this->title = $result['title'];
			$this->birth_date = $result['birth_date'];
			$this->religion = $result['religion'];
			$this->race = $result['race'];
			$this->martial_status = $result['martial_status'];
			$this->gender = $result['gender'];
			$this->occupation = $result['occupation'];
			$this->image_id = $result['image_id'];
			$this->location_id = $result['location_id'];
			$this->description = $result['description'];
			
			Address::get_person_address($p_uuid);
			Identity::get_person_identity($p_uuid);
		}

		public function get_person_information($p_uuid)
		{
			$result = Data::get_person_data($p_uuid);
			
			$this->p_uuid = $p_uuid;			
			$this->first_name = ucfirst($result['first_name']);
			$this->last_name = ucfirst($result['last_name']);
			$this->middle_name = ucfirst($result['middle_name']);
			$this->nick_name = ucfirst($result['nick_name']);
			$this->title = Data::get_field_option_description('opt_title', $result['title']);
			$this->birth_date = $result['birth_date'];
			$this->religion = Data::get_field_option_description('opt_religion', $result['religion']);
			$this->race = Data::get_field_option_description('opt_race', $result['race']);
			$this->martial_status = Data::get_field_option_description('opt_marital_status', $result['martial_status']);
			$this->gender = Data::get_field_option_description('opt_gender', $result['gender']);
			$this->occupation = ucfirst($result['occupation']);
			$this->image_id = $result['image_id'];
			//$this->location_id =Address::shn_pr_location_string($result['location_id']);
			$this->description = $result['description'];
			
			if($this->title != ''){
				$this->full_name = $this->title .". ". $this->first_name ." " . $this->last_name;
			}
			else{
				$this->full_name = $this->first_name ." " . $this->last_name;
			}
			
			Address::get_person_address_information($p_uuid);
			Identity::get_person_identity($p_uuid);
		}
		
		
		public function update_person()
		{
			$post = $_POST;
			
			$location_id = shn_location_get_form_submit_loc();
			
			$update_data = array();
			$update_data['p_uuid'] = $post['p_uuid'];
			$update_data['first_name'] = $post['first_name'];
			$update_data['last_name'] = $post['last_name'];
			$update_data['middle_name'] = $post['middle_name'];
			$update_data['nick_name'] = $post['nick_name'];
			$update_data['title'] = $post['opt_title'];
			$update_data['birth_date'] = $post['birth_date'];
			$update_data['religion'] = $post['opt_religion'];
			$update_data['race'] = $post['opt_race'];
			$update_data['martial_status'] = $post['opt_marital_status'];
			$update_data['gender'] = $post['opt_gender'];
			$update_data['occupation'] = $post['occupation'];
			$update_data['image_id'] = $post['image_id'];
			$update_data['location_id'] = $location_id;
			$update_data['description'] = $post['description'];
			
			$res = $this->db->AutoExecute('pr_person', $update_data, 'UPDATE',"p_uuid='{$update_data['p_uuid']}'");
				
			if($res){				
				Address::update_address($post, $location_id);
				Identity::update_identity($post);
				Person::update_person_image($post['p_uuid'], $_FILES['picture']);
			}
			
			$this->get_person($post['p_uuid']);
			
			return $res;
		}
		
		public function save_person()
		{	
			$post = $_POST;
			if($post['first_name'] == null){		
				add_error(_t('Please enter first name.'));
				return;	
			}
			else if($post['opt_address_type'] == null){				
				add_error(_t('Please select address type.'));
				return;	
			}
			
			$location_id = shn_location_get_form_submit_loc();
			
	 		$this->p_uuid = shn_create_uuid('person');
	 		
			$insert_data = array();
			$insert_data['p_uuid'] = $this->p_uuid;
			$insert_data['first_name'] = $post['first_name'];
			$insert_data['last_name'] = $post['last_name'];
			$insert_data['middle_name'] = $post['middle_name'];
			$insert_data['nick_name'] = $post['nick_name'];
			$insert_data['title'] = $post['title'];
			$insert_data['birth_date'] = $post['birth_date'];
			$insert_data['religion'] = $post['opt_religion'];
			$insert_data['race'] = $post['opt_race'];
			$insert_data['martial_status'] = $post['opt_marital_status'];
			$insert_data['gender'] = $post['opt_gender'];
			$insert_data['occupation'] = $post['occupation'];
			$insert_data['image_id'] = $post['image_id'];
			$insert_data['location_id'] = $location_id;
			$insert_data['description'] = $post['description'];
			
			$res = $this->db->AutoExecute('pr_person', $insert_data, 'INSERT');			
			
			if($res){
				Address::save_address($this->p_uuid, $post, $location_id);
				Identity::save_identity($this->p_uuid, $post);
				Person::save_person_image($this->p_uuid, $_FILES['picture']);
			}
			
			$this->get_person($this->p_uuid);
			
			return $res;
		}
		
		public function save_person_api()
		{	
			$post = $_POST;
	 		$this->p_uuid = shn_create_uuid('person');
	 		
			$insert_data = array();
			$insert_data['p_uuid'] = $this->p_uuid;
			$insert_data['first_name'] = $post['first_name'];			 
			$insert_data['last_name'] = $post['last_name'];
			
			$this->full_name = $insert_data['first_name'] ." ". $insert_data['last_name']; 
			
			$insert_data['middle_name'] = $post['middle_name'];
			$insert_data['nick_name'] = $post['nick_name'];
			$insert_data['title'] = $post['title'];
			$insert_data['birth_date'] = $post['birth_date'];
			$insert_data['religion'] = $post['opt_religion'];
			$insert_data['race'] = $post['opt_race'];
			$insert_data['martial_status'] = $post['opt_marital_status'];
			$insert_data['gender'] = $post['opt_gender'];
			$insert_data['occupation'] = $post['occupation'];
			$insert_data['image_id'] = $post['image_id'];
			$insert_data['location_id'] = $location_id;
			$insert_data['description'] = $post['description'];
			
			//$res = $this->db->AutoExecute('pr_person', $insert_data, 'INSERT');			
			
			if($res){
				$location_id = shn_location_get_form_submit_loc();
				Address::save_address($this->p_uuid, $post, $location_id);
				Identity::save_identity($this->p_uuid, $post);
				Person::save_person_image($this->p_uuid, $_FILES['picture']);
			}		
			
			return $this->p_uuid;
		}
		
		public function save_person_image($p_uuid, $image_file){
			global $global;						
			if ($image_file != null) {
				$info = getimagesize($image_file['tmp_name']);				 
				if ($info) {
					list ($ignore, $ext) = split("\/", $info['mime']);
		
					$size = filesize($image_file['tmp_name']);
					$pic = fread(fopen($image_file['tmp_name'], "r"), $size);					
				}
						
				$upload_dir = $global['approot'] . 'www/tmp/';
				$uploadfile = $upload_dir . 'ori_' . $p_uuid . $ext;
				move_uploaded_file($image_file['tmp_name'], $uploadfile);
				$desc_path = $upload_dir . 'thumb_' . $p_uuid . $ext;
				
				shn_image_to_db_ex($p_uuid, $pic, $ext, $info[1], $info[0], null, 'pr');
				shn_image_resize($uploadfile, $desc_path, 100, 100);		
			}
		}
		
		public function update_person_image($p_uuid, $image_file){						
			global $global;						
			if ($image_file != null) {
				$info = getimagesize($image_file['tmp_name']);
				
				if ($info) {
					list ($ignore, $ext) = split("\/", $info['mime']);
		
					$size = filesize($image_file['tmp_name']);
					$pic = fread(fopen($image_file['tmp_name'], "r"), $size);					
				}
						
				$upload_dir = $global['approot'] . 'www/tmp/';
				$uploadfile = $upload_dir . 'ori_' . $p_uuid . $ext;
				move_uploaded_file($image_file['tmp_name'], $uploadfile);
				$desc_path = $upload_dir . 'thumb_' . $p_uuid . $ext;
				Data::delete_image($p_uuid);
				shn_image_to_db_ex($p_uuid, $pic, $ext, $info[1], $info[0], null, 'pr');
				shn_image_resize($uploadfile, $desc_path, 100, 100);		
			}
		}
		
		public function delete_person($p_uuid)
		{
			$res = Data::delete_person($p_uuid);

			return $res;
		}
		
		function get_p_uuid()
		{
			return $this->p_uuid;
		}
		
		function get_first_name()
		{
			return $this->first_name;
		}
		
		function get_last_name()
		{
			return $this->last_name;
		}
		
		function get_middle_name()
		{
			return $this->middle_name;
		}
		
		function get_nick_name()
		{
			return $this->nick_name;
		}
		
		function get_title()
		{
			return $this->title;
		}
		
		function get_birth_date()
		{
			return $this->birth_date;
		}
		
		function get_religion()
		{
			return $this->religion;
		}
		
		function get_race()
		{
			return $this->race;
		}
		
		function get_martial_status()
		{
			return $this->martial_status;
		}
		
		function get_gender()
		{
			return $this->gender;
		}
		
		function get_occupation()
		{
			return $this->occupation;
		}
		
		function get_image_id()
		{
			return $this->image_id;
		}
		
		function get_location_id()
		{
			return $this->location_id;
		}
		
		function get_description()
		{
			return $this->description;
		}
		
		function set_p_uuid($p_uuid)
		{
			$this->p_uuid = $p_uuid;
		}
		
		function set_first_name($first_name)
		{
			$this->first_name = $first_name;
		}
		
		function set_last_name($last_name)
		{
			$this->last_name = $last_name;
		}
		
		function set_middle_name($middle_name)
		{
			$this->middle_name = $middle_name;
		}
		
		function set_nick_name($nick_name)
		{
			$this->nick_name = $nick_name;
		}
		
		function set_title($title)
		{
			$this->title = $title;
		}
		
		function set_birth_date($birth_date)
		{
			$this->birth_date = $birth_date;
		}
		
		function set_religion($religion)
		{
			$this->religion = $religion;
		}
		
		function set_race($race)
		{
			$this->race = $race;
		}
		
		function set_martial_status($martial_status)
		{
			$this->martial_status = $martial_status;
		}
		
		function set_gender($gender)
		{
			$this->gender = $gender;
		}
		
		function set_occupation($occupation)
		{
			$this->occupation = $occupation;
		}
		
		function set_image_id($image_id)
		{
			$this->image_id = $image_id;
		}
		
		function set_location_id($location_id)
		{
			$this->location_id = $location_id;
		}
		
		function set_description($description)
		{
			$this->description = $description;
		}
	}

