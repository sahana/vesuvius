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

	Class Group extends Person
	{
		public $g_uuid;
		public $group_head_id;
		public $group_type;
		public $relationship_type;
		
		public $group_members = array();

		function __construct($g_uuid)
		{
			Data::__construct();
			
			if($g_uuid != null){
      			$this->get_group($g_uuid);
      		}
		}
		
		public function get_group($g_uuid)
		{
			$this->g_uuid = $g_uuid;
			$result = Data::get_group_information($this->g_uuid);
			$this->group_head_id = $result['group_head_id'];
			$this->group_type = $result['group_type'];
			$this->relationship_type = $result['relationship_type'];
		}
		
		public function get_group_information($g_uuid)
		{
			$this->g_uuid = $g_uuid;
				
			$result = Data::get_group_information($this->g_uuid);
			
			$this->group_head_id = $result['group_head_id'];
			$this->group_type = ucfirst(Data::get_field_option_description('opt_group_type', $result['group_type']));
			$this->relationship_type = ucfirst(Data::get_field_option_description('opt_relationship_type', $result['relationship_type']));

			Person::get_person_information($this->group_head_id);
			
			$members = Data::get_group_members($g_uuid);
			
			if(is_array($members) && count($members) != 0){
				foreach($members as $member){
					$this->group_members[] = $member['p_uuid'];
				}
			}
		}
		
		public function save_group()
		{			
			$post = $_POST;
			
			$this->g_uuid = shn_create_uuid('group');
			
			$res_person = Person::save_person();
	 		
			$insert_data = array();
			$insert_data['g_uuid'] = $this->g_uuid;
			$insert_data['group_head_id'] = $this->p_uuid;
			$insert_data['group_type'] = $post['opt_group_type'];								
			
			$res_group = $this->db->AutoExecute('pr_group', $insert_data, 'INSERT');
						
			$insert_member = array();
			$insert_member['g_uuid'] = $this->g_uuid;
			$insert_member['p_uuid'] = $this->p_uuid;			
			$insert_member['relationship_type'] = $post['opt_relationship_type'];						
			
			$res_member = $this->db->AutoExecute('pr_group_member', $insert_member, 'INSERT');
			
			Person::get_person($this->p_uuid);
			
			if($res_person && $res_group && $res_member){
				return true;
			}
			else{
				return false;
			}
		}
		
		public function save_group_member()
		{			
			$post = $_POST;
			 
			$res_person = Person::save_person();

			$this->g_uuid = $post['g_uuid'];
			
			$insert_member = array();
			$insert_member['g_uuid'] = $this->g_uuid;
			$insert_member['p_uuid'] = $this->p_uuid;			
			$insert_member['relationship_type'] = $post['opt_relationship_type'];						
			
			$res_member = $this->db->AutoExecute('pr_group_member', $insert_member, 'INSERT');
			
			if($res_person && $res_member){
				return true;
			}
			else{
				return false;
			}
		}
	
		function print_group_member_list()
		{
			print_group_member_list($this->g_uuid);
		}		
		
		function get_relationship_name($option_code)
		{
			$res = Data::get_field_option_description('opt_relationship_type',$option_code);
			
			return $res;
		}
		
		function delete_group($g_uuid)
		{
			$res = Data::delete_group($g_uuid);
			
			return $res;
		}
		
//		function get_field_option_description($field_name, $option_code)
//		{
//			$res = Data::get_field_option_description($field_name,$option_code);
//			
//			return $res;
//		}
		
		function get_g_uuid()
		{
			return $this->g_uuid;
		}
		
		function get_group_head_id()
		{
			return $this->group_head_id;
		}
		
		function get_group_type()
		{
			return $this->group_type;
		}
		
		function get_relationship_type()
		{
			return $this->relationship_type;
		}
		
		function set_g_uuid($g_uuid)
		{
			$this->g_uuid = $g_uuid;
		}
		
		function set_group_head_id($group_head_id)
		{
			$this->group_head_id = $group_head_id;
		}

		function set_group_type($group_type)
		{
			$this->group_type = $group_type;
		}
		
		function set_relationship_type($relationship_type)
		{
			$this->relationship_type = $relationship_type;
		}
		
		
	}
