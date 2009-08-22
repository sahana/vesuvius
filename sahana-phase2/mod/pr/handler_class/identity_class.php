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

	Class Identity extends Data
	{
		public $i_uuid;
		public $nic;
		public $password;
		public $dln;
		
		public $identity_list = array();
		
		public function __construct($p_uuid)
		{
			Data::__construct();
			
			if($p_uuid != null){
      			$this->get_person_identity($p_uuid);
      		}
		}
		
		public function get_person_identity($p_uuid)
		{
			$results = Data::get_person_identity($p_uuid);
						
			if(is_array($results) && count($results) != 0){
				$i = 0;
				
				unset($this->identity_list);
				
				foreach($results as $result){
					$this->identity_list[$i]['identity_value'] = $result['identity_value'];
					$this->identity_list[$i]['identity_type'] = $result['identity_type'];
					$this->identity_list[$i]['option_description'] = $result['option_description'];
					$i++;
				}
			}
		}
		
		public function save_identity($p_uuid, $post)
		{	
			$identity_types = Identity::get_identity_types();
				
			if(is_array($identity_types) && count($identity_types) != 0){
				foreach($identity_types as $identity_type){
					if($post[$identity_type['option_code']] != null){
						$this->i_uuid = shn_create_uuid('identity');
						$insert_data = array();
						$insert_data['i_uuid'] = $this->i_uuid;						
						$insert_data['identity_type'] = $identity_type['option_code'];
						$insert_data['identity_value'] = $post[$identity_type['option_code']];
						
						$res = $this->db->AutoExecute('pr_identity', $insert_data, 'INSERT');
 
						$insert_person_identity = array();
						$insert_person_identity['p_uuid'] = $p_uuid;
						$insert_person_identity['i_uuid'] = $this->i_uuid;
			
						$this->db->AutoExecute('pr_identity_individual', $insert_person_identity, 'INSERT');
					}
				}	
			}
		}
		
		public function update_identity($post)
		{
			Data::delete_identity($post);
			
			$identity_types = Identity::get_identity_types();
				
			if(is_array($identity_types) && count($identity_types) != 0){
				foreach($identity_types as $identity_type){
					if($post[$identity_type['option_code']] != null){
						$this->i_uuid = shn_create_uuid('identity');
						$insert_data = array();
						$insert_data['i_uuid'] = $this->i_uuid;						
						$insert_data['identity_type'] = $identity_type['option_code'];
						$insert_data['identity_value'] = $post[$identity_type['option_code']];
						
						$res = $this->db->AutoExecute('pr_identity', $insert_data, 'INSERT');
 
						$insert_person_identity = array();
						$insert_person_identity['p_uuid'] = $post['p_uuid'];
						$insert_person_identity['i_uuid'] = $this->i_uuid;
			
						$this->db->AutoExecute('pr_identity_individual', $insert_person_identity, 'INSERT');
					}
				}	
			}			
		}
		
		public function get_identity_types()
		{
			$sql = "SELECT * FROM field_options WHERE field_name = 'opt_identity_type'";
			
			$res = $this->db->GetAll($sql);

			return $res;
		}
	}

