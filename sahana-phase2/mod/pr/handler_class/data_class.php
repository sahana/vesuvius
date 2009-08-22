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

	Class Data
	{
		public $db;
		
		function __construct()
		{
			global $global;
      		$this->db = $global['db'];
		}
		
		public static function get_person_data($p_uuid) 
		{		
			global $global;
      		$db = $global['db'];
      			
		    $sql = "SELECT * FROM pr_person WHERE p_uuid= '$p_uuid'";		    
		    $res = $db->GetRow($sql);

			return $res;	   
	 	}
	 	
		public function get_person_address($p_uuid) 
		{		
			global $global;
      		$db = $global['db'];
      			
		    $sql = "SELECT a.* FROM 
		    		pr_address a
					INNER JOIN pr_person_address pa ON pa.a_uuid = a.a_uuid
					WHERE pa.p_uuid = '$p_uuid'";
		    	    
		    $res = $db->GetRow($sql);

			return $res;	   
	 	}
	 	
		public function get_person_all_address($p_uuid) 
		{		
			global $global;
      		$db = $global['db'];
      			
		    $sql = "SELECT a.* FROM 
		    		pr_address a
					INNER JOIN pr_person_address pa ON pa.a_uuid = a.a_uuid
					WHERE pa.p_uuid = '$p_uuid'";
		    	    
		    $res = $db->GetAll($sql);

			return $res;	   
	 	}
	 	
	 	public function get_person_identity($p_uuid)
	 	{
	 		global $global;
      		$db = $global['db'];
      			
		    $sql = "SELECT i.identity_type,i.identity_value, f.option_description 
					FROM pr_identity i
					INNER JOIN pr_identity_individual ii ON i.i_uuid = ii.i_uuid
					INNER JOIN field_options f ON i.identity_type = f.option_code
					WHERE ii.p_uuid = '$p_uuid' AND field_name = 'opt_identity_type'";
		    	    
		    $res = $db->GetAll($sql);

			return $res;
	 	}
	 	public function get_person_address_contact($a_uuid, $field_type)
	 	{
	 		global $global;
      		$db = $global['db'];
      			
		    $sql = "SELECT * FROM pr_address_contacts 
		            WHERE a_uuid = '$a_uuid' AND field_type = '$field_type'";
		    	    
		    $res = $db->GetAll($sql);

			return $res;
	 	}
	 	
	 	public function delete_image($p_uuid)
	 	{
	 		global $global;
	 		$db = $global['db'];
	 		
	 		$sql = "DELETE FROM image WHERE x_uuid = '$p_uuid'";
	 		$db->Execute($sql);
	 		
	 	}
	 	
	 	public function delete_person($p_uuid)
	 	{
	 		global $global;
	 		$db = $global['db'];
	 		
	 		$sql1 = "DELETE FROM pr_person WHERE p_uuid = '$p_uuid'";
	 		$res = $db->Execute($sql1);
	 		
	 		if($res){
		 		$sql2 = "DELETE FROM pr_address 
		 				 WHERE a_uuid IN (SELECT a_uuid FROM pr_person_address WHERE p_uuid = '$p_uuid')";
		 		$db->Execute($sql2);
		 		
		 		$sql3 = "DELETE FROM pr_address_contacts 
		 				WHERE a_uuid = (SELECT a_uuid FROM pr_person_address WHERE p_uuid = '$p_uuid')";
		 		$db->Execute($sql3);
		 		
		 		$sql4 = "DELETE FROM pr_person_address WHERE p_uuid = '$p_uuid'";
		 		$db->Execute($sql4);
		 		
		 		$sql5 = "DELETE FROM pr_identity 
		 				 WHERE i_uuid IN  (SELECT i_uuid FROM pr_identity_individual WHERE p_uuid = '$p_uuid')";
		 		$db->Execute($sql5);
		 		
		 		$sql6 = "DELETE FROM pr_identity_individual WHERE p_uuid = '$p_uuid'";
		 		$db->Execute($sql6);

		 		
		 		
		 		//$sql6 = "DELETE FROM pr_image WHERE p_uuid = '$p_uuid'";
		 		//$db->Execute($sql6);
	 		}
	 		
	 		return $res;
	 	}
	 	
	 	public function delete_address_contacts($post)
	 	{
	 		global $global;
	 		$db = $global['db'];
	 		
	 		$sql = "DELETE FROM pr_address_contacts WHERE a_uuid = '{$post['a_uuid']}'";
		 	$db->Execute($sql);
		 		
		 	$sql1 = "DELETE FROM pr_person_address WHERE p_uuid = '{$post['p_uuid']}'";
		 	$db->Execute($sql1);
		 	
		 	$sql2 = "DELETE FROM pr_address WHERE a_uuid = '{$post['a_uuid']}'";
		 	$db->Execute($sql2);
	 	}
	 	
	 	public function delete_identity($post)
	 	{
	 		global $global;
	 		$db = $global['db'];
	 		
	 		$sql = "DELETE FROM pr_identity 
	 				WHERE i_uuid IN (SELECT i_uuid FROM pr_identity_individual WHERE p_uuid = '{$post['p_uuid']}')";
	 		$db->Execute($sql);
	 		
	 		$sql1= "DELETE FROM pr_identity_individual WHERE p_uuid = '{$post['p_uuid']}'";
	 		$db->Execute($sql1);
	 	}
	 	
	 	public function delete_group($g_uuid)
	 	{
	 		global $global;
	 		$db = $global['db'];
	 		
	 		$sql1 = "DELETE FROM pr_group WHERE g_uuid = '$g_uuid'";
	 		$res = $db->Execute($sql1);
	 		
	 		$sql = "SELECT p_uuid FROM pr_group_member WHERE g_uuid = '$g_uuid'";
	 		$results = $db->GetAll($sql); 		
	 			 		
	 		if(is_array($results) && count($results) != 0){
	 			foreach($results as $result){
	 				$result['p_uuid'];
	 				Data::delete_person($result['p_uuid']);
	 			}
	 		}
	 		
	 		$sql2 = "DELETE FROM pr_group_member WHERE g_uuid = '$g_uuid'";
	 		$db->Execute($sql2);
	 		
	 		return $res;
	 		
	 	}
	 	
		public static function get_person_list_sql($post = null) 
		{			
		    $sql = "SELECT p_uuid, first_name, last_name, middle_name, nick_name, title, birth_date, religion, gender, occupation 
		            FROM pr_person ";
		    
		    $where = " WHERE (first_name LIKE '%{$post['any_name']}%' OR 
		    		   last_name LIKE '%{$post['any_name']}%' OR 
		    		   middle_name LIKE '%{$post['any_name']}%' OR 
		    		   nick_name LIKE '%{$post['any_name']}%') ";
		    
		    if($post['opt_gender'] != null){
		    	$where .= " AND gender = '{$post['opt_gender']}' ";
		    }
		    
		    if($post['opt_religion'] != null && $post['opt_religion'] != 'unk'){
		    	$where .= " AND religion = '{$post['opt_religion']}' ";
		    }
		    
			if($post['occupation'] != null){
		    	$where .= " AND occupation LIKE '%{$post['occupation']}%' ";
		    }
		    
			if($post['birth_date'] != null){
		    	$where .= " AND birth_date = '{$post['birth_date']}' ";
		    }
		    
		    $sql .= $where;
		    
			return  $sql;
	 	}
	 	
	 	public function get_person_id_list()
	 	{
	 		global $global;
      		$db = $global['db'];
      		
	 		$sql = "SELECT p_uuid FROM pr_person ";
	 		
	 		$res = $db->GetAll($sql);

			return $res;
	 	}
	 	
		public function get_group_id_list()
	 	{
	 		global $global;
      		$db = $global['db'];
      		
	 		$sql = "SELECT g_uuid FROM pr_group";
	 		
	 		$res = $db->GetAll($sql);

			return $res;
	 	}
	 	
	 	public function get_group_members($g_uuid)
	 	{
	 		global $global;
      		$db = $global['db'];
      		
      		$sql = "SELECT p_uuid FROM pr_group_member WHERE g_uuid = '$g_uuid'";
      		
      		$res = $db->GetAll($sql);

			return $res;
	 	}
	 	
	 	public static function get_group_member_list($g_uuid)
	 	{	 	
	 		global $global;
      		$db = $global['db'];
      			
	 		$sql = "SELECT p.p_uuid, pg.g_uuid, p.first_name, p.last_name, pg.relationship_type
					FROM pr_person p
					INNER JOIN pr_group_member pg ON p.p_uuid = pg.p_uuid
					WHERE pg.g_uuid = '$g_uuid'";
	 		
	 		//$db->StartTrans();
	 		//$db->SetFetchMode(ADODB_FETCH_ASSOC);
	 		//$db->SetFetchMode(ADODB_FETCH_NUM);
        	$res = $db->GetAll($sql);
        	//$db->CompleteTrans();

			return $res;
	 	}
	 	
	 	public function get_group_information($g_uuid)
	 	{
	 		global $global;
      		$db = $global['db'];
      			
		    $sql = "SELECT g.group_head_id, g.group_type, gm.relationship_type 
					FROM pr_group g
					INNER JOIN pr_group_member gm ON g.g_uuid = gm.g_uuid AND g.group_head_id = gm.p_uuid
					WHERE g.g_uuid = '$g_uuid'";
		    	    
		    $res = $db->GetRow($sql);

			return $res;	
	 	}
	 	
	 	public static function get_field_option_description($field_name, $option_code)
	 	{
	 		global $global;
      		$db = $global['db'];
      		
      		$sql = "SELECT option_description 
      				FROM field_options 
      				WHERE field_name = '$field_name' AND option_code = '$option_code'";
      		
      		$res = $db->GetOne($sql);

			return $res;      		
	 	}
	 	
	 	function get_group_list_sql($post = null) {
	 		global $global;
      		$db = $global['db'];
      		
      		$sql = "SELECT pg.g_uuid, CONCAT(CONCAT(p.first_name, ' '), p.last_name) full_name, pg.group_type, COUNT(pgm.g_uuid) no_of_members
					FROM pr_group pg
					INNER JOIN pr_person p ON pg.group_head_id = p.p_uuid
					INNER JOIN pr_group_member pgm ON pg.g_uuid = pgm.g_uuid ";
      		
      		$where = " WHERE (p.first_name LIKE '%{$post['any_name']}%' OR p.last_name LIKE '%{$post['any_name']}%') ";
      		
      		$group_by = " GROUP BY pg.g_uuid";
      		
      		if($post['opt_group_type'] != null){
      			$where .= " AND pg.group_type = '{$post['opt_group_type']}'";
      		}
      		
	 		if($post['opt_gender'] != null){
		    	$where .= " AND p.gender = '{$post['opt_gender']}' ";
		    }
		    
		    if($post['opt_religion'] != null && $post['opt_religion'] != 'unk'){
		    	$where .= " AND p.religion = '{$post['opt_religion']}' ";
		    }
		    
			if($post['occupation'] != null){
		    	$where .= " AND p.occupation LIKE '%{$post['occupation']}%' ";
		    }
		    
			if($post['birth_date'] != null){
		    	$where .= " AND p.birth_date = '{$post['birth_date']}' ";
		    }
      		
      		$sql .= $where . $group_by;
      		
      		$res = $db->GetAll($sql);

			return $sql;
	 	}
	 	
	 	function get_pr_gender()
	 	{
	 		$array ['data']=array();
			$array ['label']=array();
			
			$res = Data::get_gender_count();
			if(is_array($res) && count($res) != 0){
				foreach($res as $rs){
					if($rs['gender'] !=''){
						$array['data'][] = $rs['count'];
						$array['label'][] = eregi_replace(',','',$rs['des']);
					}
					else{
						$array['data'][] = $rs['count'];
						$array['label'][] = 'Unknown';					
					}
				}
			}
			return $array;
	 	}
	 	
		function get_gender_count($type){
			global $global;
			$db = $global['db'];
			
			$sql = "SELECT pr.gender AS gender, count(pr.gender) AS count,f.option_description AS 'des' 
					FROM pr_person as pr 
					LEFT JOIN field_options as f ON f.option_code = pr.gender AND f.field_name = 'opt_gender' 
					GROUP BY pr.gender 
					ORDER BY option_description";
			
			$fetchmode=$db->SetFetchMode(ADODB_FETCH_ASSOC);
			$res = $db->GetAll($sql);
			$db->SetFetchMode($fetchmode);
			
			return $res;
		}
		
		function get_pr_religion()
	 	{
	 		$array ['data']=array();
			$array ['label']=array();
			
			$res = Data::get_religion_count();
			if(is_array($res) && count($res) != 0){
				foreach($res as $rs){
					if($rs['religion'] !=''){
						$array['data'][] = $rs['count'];
						$array['label'][] = eregi_replace(',','',$rs['des']);
					}
					else{
						$array['data'][] = $rs['count'];
						$array['label'][] = 'Unknown';					
					}
				}
			}
			return $array;
	 	}
		
		function get_religion_count($type){
			global $global;
			$db = $global['db'];
			
			$sql = "SELECT pr.religion AS religion, count(pr.religion) AS count,f.option_description AS 'des' 
					FROM pr_person as pr 
					LEFT JOIN field_options as f ON f.option_code = pr.religion AND f.field_name = 'opt_religion' 
					GROUP BY pr.religion 
					ORDER BY option_description";
			
			$fetchmode=$db->SetFetchMode(ADODB_FETCH_ASSOC);
			$res = $db->GetAll($sql);
			$db->SetFetchMode($fetchmode);
			
			return $res;
		}
		
		function get_pr_martial_status()
	 	{
	 		$array ['data']=array();
			$array ['label']=array();
			
			$res = Data::get_martial_status_count();
			if(is_array($res) && count($res) != 0){
				foreach($res as $rs){
					if($rs['martial_status'] !=''){
						$array['data'][] = $rs['count'];
						$array['label'][] = eregi_replace(',','',$rs['des']);
					}
					else{
						$array['data'][] = $rs['count'];
						$array['label'][] = 'Unknown';					
					}
				}
			}
			return $array;
	 	}
		
		function get_martial_status_count($type)
		{
			global $global;
			$db = $global['db'];
			
			$sql = "SELECT pr.martial_status AS martial_status, count(pr.martial_status) AS count,f.option_description AS 'des' 
					FROM pr_person as pr 
					LEFT JOIN field_options as f ON f.option_code = pr.martial_status AND f.field_name = 'opt_marital_status' 
					GROUP BY pr.martial_status
					ORDER BY option_description";
			
			$fetchmode=$db->SetFetchMode(ADODB_FETCH_ASSOC);
			$res = $db->GetAll($sql);
			$db->SetFetchMode($fetchmode);
			
			return $res;
		}	
		
	}

