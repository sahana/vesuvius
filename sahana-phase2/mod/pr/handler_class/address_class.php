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
	
	Class Address extends Data
	{
		public $a_uuid;
		public $address_type;
		public $address;
		public $postal_code;
		public $location_id;
		public $description;
		
		public $phone_list = array();
		public $mobile_list = array();
		public $email_list = array();
		public $web_list = array();		
		
		public function __construct()
		{
			Data::__construct();
		}
				
		public function get_person_address($p_uuid)
		{
			$result = Data::get_person_address($p_uuid);
			
			$this->a_uuid = $result['a_uuid'];
			$this->address = $result['address'];
			$this->address_type = $result['address_type'];
			$this->postal_code = $result['postal_code'];
			$this->location_id = $result['location_id'];
			$this->description = $result['description'];
			
			$telephone_list = Data::get_person_address_contact($this->a_uuid, 'telephone');			
			
			unset($this->phone_list);
			
			if(is_array($telephone_list) && count($telephone_list) != 0){
				foreach($telephone_list as $telephone){
					$this->phone_list[] = $telephone['field_value'];
				}
			}
			
			$mobile_list = Data::get_person_address_contact($this->a_uuid, 'mobile');
			
			unset($this->mobile_list);
			
			if(is_array($mobile_list) && count($mobile_list) != 0){
				foreach($mobile_list as $mobile){
					$this->mobile_list[] = $mobile['field_value'];
				}
			}
			
			$email_list = Data::get_person_address_contact($this->a_uuid, 'email');
			
			unset($this->email_list);
			
			if(is_array($email_list) && count($email_list) != 0){
				foreach($email_list as $email){
					$this->email_list[] = $email['field_value'];
				}
			}
			
			$web_list = Data::get_person_address_contact($this->a_uuid, 'web');
						
			unset($this->web_list);
			
			if(is_array($web_list) && count($web_list) != 0){
				foreach($web_list as $web){
					$this->web_list[] = $web['field_value'];
				}
			}

		}
		
		public function get_all_addresses($p_uuid)
		{
			$results = Data::get_person_all_address($p_uuid);
			
			$addresses = array();
			
			if(is_array($results) && count($results) != 0){
				foreach($results as $result){
					$addresses['address_type'][] = $result['address_type'];
					$addresses[$result['address_type']]['address'] = $result['address'];
					$addresses[$result['address_type']]['postal_code'] = $result['postal_code'];
					
					$telephone_list = Data::get_person_address_contact($result['a_uuid'], 'telephone');
					
					if(is_array($telephone_list) && count($telephone_list) != 0){
						foreach($telephone_list as $telephone){							
							$addresses[$result['address_type']]['telephone'][] = $telephone['field_value'];
						}
					}
					
					$mobile_list = Data::get_person_address_contact($result['a_uuid'], 'mobile');
								
					if(is_array($mobile_list) && count($mobile_list) != 0){
						foreach($mobile_list as $mobile){
							$addresses[$result['address_type']]['mobile'][] = $mobile['field_value'];
						}
					}
					
					$email_list = Data::get_person_address_contact($result['a_uuid'], 'email');
					
					if(is_array($email_list) && count($email_list) != 0){
						foreach($email_list as $email){
							$addresses[$result['address_type']]['email'][] = $email['field_value'];
						}
					}
					
					$web_list = Data::get_person_address_contact($result['a_uuid'], 'web');
										
					if(is_array($web_list) && count($web_list) != 0){
						foreach($web_list as $web){
							$addresses[$result['address_type']]['web'][] = $web['field_value'];
						}
					}					
				}
			}
			
			return $addresses;
		}
		
		public function get_person_address_information($p_uuid)
		{
			$result = Data::get_person_address($p_uuid);

			$this->a_uuid = $result['a_uuid'];
			$this->address = $result['address'];
			$this->address_type = Data::get_field_option_description('opt_address_type', $result['address_type']);
			$this->postal_code = $result['postal_code'];
			$this->location_id =Address::shn_pr_location_string($result['location_id']);
			$this->description = $result['description'];
			
			$telephone_list = Data::get_person_address_contact($this->a_uuid, 'telephone');			
			
			unset($this->phone_list);
			
			if(is_array($telephone_list) && count($telephone_list) != 0){
				foreach($telephone_list as $telephone){
					$this->phone_list[] = $telephone['field_value'];
				}
			}
			
			$mobile_list = Data::get_person_address_contact($this->a_uuid, 'mobile');
			
			unset($this->mobile_list);
			
			if(is_array($mobile_list) && count($mobile_list) != 0){
				foreach($mobile_list as $mobile){
					$this->mobile_list[] = $mobile['field_value'];
				}
			}
			
			$email_list = Data::get_person_address_contact($this->a_uuid, 'email');
			
			unset($this->email_list);
			
			if(is_array($email_list) && count($email_list) != 0){
				foreach($email_list as $email){
					$this->email_list[] = $email['field_value'];
				}
			}
			
			$web_list = Data::get_person_address_contact($this->a_uuid, 'web');
						
			unset($this->web_list);
			
			if(is_array($web_list) && count($web_list) != 0){
				foreach($web_list as $web){
					$this->web_list[] = $web['field_value'];
				}
			}

		}
		
		public function save_address_numbers($a_uuid, $number_type, $numbers)
		{
			if(is_array($numbers) && count($numbers) != 0){
				$insert_telephone = array();
					
				$insert_telephone['a_uuid'] = $a_uuid;
				$insert_telephone['field_type'] = $number_type;				
					 
				unset($this->phone_list);
					
				foreach($numbers as $number){
					$ac_uuid = shn_create_uuid($number_type);
					$insert_telephone['ac_uuid'] = $ac_uuid;					
					$this->phone_list[] = $number;
					$insert_telephone['field_value'] = $number;
						
					$res = $this->db->AutoExecute('pr_address_contacts', $insert_telephone, 'INSERT');
				}				
			}
		}
		
		public function save_address($p_uuid, $post, $location_id)
		{			
			//var_dump($post['addresses']);
			if(is_array($post['addresses']) && count($post['addresses']) != 0){				
				foreach($post['addresses'] as $key=>$address_type){		

					if($address_type != null && (!is_array($post['addresses'][$address_type]))){
						$this->a_uuid = shn_create_uuid('address');
						
						$insert_data = array();
						$insert_data['a_uuid'] = $this->a_uuid;
						$insert_data['address_type'] = $key;
						$insert_data['address'] = $post['addresses'][$key]['address'];
						$insert_data['postal_code'] = $post['addresses'][$key]['postal_code'];
						$insert_data['location_id'] = $location_id;
						$insert_data['description'] = 'description';

						$res = $this->db->AutoExecute('pr_address', $insert_data, 'INSERT');
							
						$insert_person_address = array();
						$insert_person_address['p_uuid'] = $p_uuid;
						$insert_person_address['a_uuid'] = $this->a_uuid;
							
						$this->db->AutoExecute('pr_person_address', $insert_person_address, 'INSERT');
				
						
						foreach($post['addresses'][$key] as $sub_key=>$address){
							switch($sub_key){
								case 'telephone':
									Address::save_address_numbers($this->a_uuid, 'telephone', $_POST['addresses'][$key][$sub_key]);								
									break;
								case 'mobile':
									Address::save_address_numbers($this->a_uuid, 'mobile', $_POST['addresses'][$key][$sub_key]);
									break;
								case 'email':
									Address::save_address_numbers($this->a_uuid, 'email', $_POST['addresses'][$key][$sub_key]);
									break;
								case 'web':
									Address::save_address_numbers($this->a_uuid, 'web', $_POST['addresses'][$key][$sub_key]);
									break;
							}
						}						
					}
				}
			}
		}
		
		public function update_address($post, $location_id)
		{	
			if(is_array($post['addresses']) && count($post['addresses']) != 0){				
				Data::delete_address_contacts($post);				
				Address::save_address($post['p_uuid'], $post, $location_id);				
			}			
		}
		
		public function shn_pr_location_string($loc)
		{
			global $global;
			$db=$global["db"];
			$loc_arr=array();
		   	shn_get_parents($loc,&$loc_arr);
		   	if($loc_arr[0]=='unknown'){
		   		add_information(_t('Unknown location'));
		   	}
		   	else{		   		
		   		$max=count($loc_arr)-1;
		   		array_pop($loc_arr);
		   		for($count=0;$count<$max;$count++){
		   			$x=array_pop($loc_arr);
		   			$q="SELECT name FROM location WHERE loc_uuid='{$x}'";
		    			$res=$db->Execute($q);
		    			if($count==0 ){
		    				$location=$location.$res->Fields("name");
		    			}else{
		   				$location=$location." -->".$res->Fields("name");
		    			}
		    			
		   		}
		   	}
		   	
		   	return $location;
		}
		
		function get_a_uuid()
		{
			return $this->a_uuid;
		}
		
		function get_address_type()
		{
			return $this->address_type;
		}
		
		function get_address()
		{
			return $this->address;
		}
		
		function get_postal_code()
		{
			return $this->postal_code;			
		}
		
		function get_location_id()
		{
			return $this->location_id;			
		}
		
		function get_description()
		{
			return $this->description;
		}
		
		function get_mobile_list()
		{
			return $this->mobile_list;
		}
		
		function get_email_list()
		{
			return $this->email_list;
		}
		
		function get_web_list()
		{
			return $this->web_list;
		}
		
		function get_phone_list()
		{
			return $this->phone_list;
		}
		
		function set_a_uuid($a_uuid)
		{
			$this->a_uuid = $a_uuid;
		}
		
		function set_address_type($address)
		{
			$this->address_type = $address_type;
		}
		
		function set_address($address)
		{
			$this->address = $address;
		}
		
		function set_postal_code($postal_code)
		{
			$this->postal_code = $postal_code;			
		}
		
		function set_location_id($location_id)
		{
			$this->location_id = $location_id;			
		}
		
		function set_description($description)
		{
			$this->description = $description;
		}
		
		function set_mobile_list($mobile_list)
		{
			$this->mobile_list = $mobile_list;
		}
		
		function set_email_list($email_list)
		{
			$this->email_list = $email_list;
		}
		
		function set_web_list($web_list)
		{
			$this->web_list = $web_list;
		}
		
		function set_phone_list($phone_list)
		{
			$this->phone_list = $phone_list;
		}
	}

