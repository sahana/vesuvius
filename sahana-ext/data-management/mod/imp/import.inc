<?php
/* $Id: import.inc,v 1.1 2006-03-20 11:26:11 janakawicks Exp $ */

/**
 * Import data file of the Data Import Module 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Thushari Silva <atpsilva@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage imp
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";




function shn_imp_imp_per_Import_Individual()
{ 
global $global;
    $db=$global['db']; 
    
$q = "CREATE TABLE IF NOT EXISTS Imp_individual (
 p_id BIGINT NOT NULL AUTO_INCREMENT,
 p_uuid BIGINT,
 full_name VARCHAR(100), 
 family_name VARCHAR(50), 
 l10n_name VARCHAR(100), 
  custom_name VARCHAR(50),
 serial VARCHAR(100), 
  opt_id_type VARCHAR(10),
 isReliefWorker TINYINT, 
 opt_status VARCHAR(10),
 isvictim BOOL DEFAULT 1,
 opt_contact_type VARCHAR(10), 
 contact_value VARCHAR(100), 
 opt_person_loc_type VARCHAR(10),
 address TEXT, 
 postcode VARCHAR(30),
 long_lat VARCHAR(20),
 next_kin_uuid BIGINT,
 birth_date DATE,
 opt_age_group VARCHAR(10),     
 relation VARCHAR(50),
 opt_country VARCHAR(10),
 opt_race VARCHAR(10),
 opt_religion VARCHAR(10),
 opt_marital_status VARCHAR(10),
 opt_gender VARCHAR(10),
 occupation VARCHAR(100),
 opt_blood_type VARCHAR(10),
 height VARCHAR(10),
 weight VARCHAR(10),
 opt_eye_color VARCHAR(50),
 opt_skin_color VARCHAR(50),
 opt_hair_color VARCHAR(50),
 injuries TEXT,
 comments_physical TEXT,
 last_seen TEXT,
 last_clothing TEXT,
 comments_missing TEXT,
 details TEXT,
 date_of_death DATE,
 location VARCHAR(20),
 place_of_death TEXT,
 comments_deceased TEXT,
 parent_id BIGINT DEFAULT 0,
 search_id VARCHAR(20),
 opt_location_type VARCHAR(10),
 loc_name VARCHAR(100) NOT NULL,
 iso_code VARCHAR(20),
 description TEXT,

PRIMARY KEY (p_id)
); ";



  $res_pers=$db->Execute($q);

  $filename= $_SESSION['filename'];
 
  $rowsimported = 0 ; 
  
  $mapping=$_SESSION['mapping']; 
 
  $handle = fopen($filename, "r");
  $rows= 0; 
    while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
     
         	    
    for($i=0; $i<count($mapping); $i++)
    {
     if( $mapping[$i]!= 'do_not_import'){		    
      switch ($mapping[$i])
      { 
	 case 'p_uuid':
		 $insert_array['p_uuid']= $data[$i] ; 
	         break; 
         case 'full_name': 
	         $insert_array['full_name'] = $data[$i]; 
	         break; 
	 case 'family_name':
		$insert_array['family_name'] = $data[$i];
		break;
	case 'l10n_name' : 
		$insert_array['l10n_name']=$data[$i]; 
		break; 
	case 'custom_name':
		$insert_array['custom_name'] = $data[$i]; 
		break;
	case 'serial': 
	        $insert_array['serial'] = $data[$i]; 
		break; 
	case 'opt_id_type': 
		$insert_array['opt_id_type'] = $data[$i]; 
	case 'isReliefWorker': 
		$insert_array['isReliefWorker']	= $data[$i];
		break; 
	case 'opt_status': 
		$insert_array['opt_status'] = $data[$i];
		break; 
	case 'isvictim' :
		$insert_array['isvictim'] =  $data[$i]; 
		break; 
	case 'opt_contact_type': 
		$insert_array['opt_contact_type'] = $data[$i];
		break; 
	case 'contact_value': 
		$insert_array['contact_value'] = $data[$i];
		break; 
	case 'opt_person_loc_type' : 
		$insert_array['opt_person_loc_type'] = $data[$i];
		break;
	case 'address': 
		$insert_array['address']= $data[$i]; 
		break; 
	case 'postcode' : 
	 	$insert_array['postcode'] = $data[$i];
		break; 
	case 'long_lat' : 
		$insert_array['long_lat'] = $data[$i];
		break; 
	case 'next_kin_uuid':
	     $insert_array['next_kin_uuid']=  $data[$i];
	     break;
        case 'birth_date':
	     $insert_array['birth_date'] = $data[$i];
	     break; 
        case 'opt_age_group': 
	     $insert_array['opt_age_group'] = $data[$i];
	     break;
	case 'relation': 
	     $insert_array['relation'] = $data[$i];
	     break;
     	case 'opt_country': 
	    $insert_array['opt_country'] = $data[$i];  
	    break;
        case 'opt_race' : 
		$insert_array['opt_race'] = $data[$i]; 
	case 'opt_religion': 
		$insert_array['opt_religion'] = $data[$i];
		break; 
	case 'opt_marital_status': 
		$insert_array['opt_marital_status'] =  $data[$i];
		break; 
	case 'opt_gender': 
		$insert_array['opt_gender'] = $data[$i];
		break; 
	case 'occupation': 
		$insert_array['occupation'] = $data[$i];
		break; 
	case 'opt_blood_type': 
		$insert_array['opt_blood_type'] = $data[$i];
		break; 
	case 'height' : 
		$insert_array['height'] = $data[$i];
		break;
	case 'weight': 
		$insert_array['weight'] = $data[$i];
		break; 
	case 'opt_eye_color' :
		$insert_array['opt_eye_color']=  $data[$i];
		break;
	case 'opt_skin_color': 
		$insert_array['opt_skin_color'] = $data[$i];
	       break;
       case 'opt_hair_color':
	       $insert_array['opt_hair_color'] = $data[$i];
	       break; 
       case 'injuries': 
	       $insert_array['injuries'] =  $data[$i];
	      break; 
        case 'comments_physical': 
	      $insert_array['comments_physical'] = $data[$i];
	      break;
	case 'last_seen': 
		$insert_array['last_seen'] =  $data[$i];
		break; 
	case 'last_clothing': 
		$insert_array['last_clothing'] = $data[$i];
	       break; 
       case 'comments_missing' :
	       $insert_array['comments_missing'] = $data[$i];
	       break; 
       case 'details':
	       $insert_array['details'] = $data[$i];
	       break; 
       case 'date_of_death': 
	       $insert_array['date_of_death'] = $data[$i];
	       break; 
       case 'location': 
	       $insert_array['location']= $data[$i];
	       break; 
       case 'place_of_death': 
               $insert_array['place_of_death']= $data[$i+1];
		break; 
	case 'comments_deceased': 
		$insert_array['comments_deceased'] = $data[$i];
		break; 
	case 'parent_id': 
		$insert_array['parent_id'] = $data[$i];
		break; 
	case 'search_id': 
		$insert_array['search_id'] = $data[$i];
		break; 
	case 'opt_location_type': 
		$insert_array['opt_location_type'] =  $data[$i];
		break;
	case 'loc_name': 
		$insert_array['loc_name'] = $data[$i];
		break;
	case 'iso_code': 
		$insert_array['iso_code'] = $data[$i];
		break; 
	case 'description': 
		$insert_array['description']= $data[$i];
		break; 
	default : 
	 break;	
		
      } //end switch
     
    }//end if 
    else { 
	continue; 
      }
          
    }//end of for loop	 
    
//To be discussed 
// if ($insert_array['p_uuid']== '')
 //   $insert_array['p_uuid'] = shn_create_uuid('p');	

if((!$_SESSION['skipColumnHeader'])&& $rows ===0 ){
++$rows	;
continue; 
}
else {
  shn_db_insert($insert_array,'imp_individual',true,'p_id');
 ++ $rowsimported ; 
 }
  ++$rows;
   }//end of the while loop  
   shn_form_fopen("imp_per_summary",null,array('req'=> false));  
   shn_form_fsopen(_('Summary'));
    echo 'Import has completed successfully. The information below summarizes the results.'; 
    ?>
    <p></p>
    <p><?php echo('Total Number of Rows in the Upload File: ');
      echo $rows; ?></p>
    <?php
   
    echo 'Total Number of Imported Rows:'; 
    echo $rowsimported ;
    shn_form_fsclose();
    shn_form_submit(_('Done')); 
    shn_form_fclose();
fclose($handle);
 
} 



function shn_imp_imp_per_Import_Organization()
{ 
global $global;
    $db=$global['db']; 
    
$q = "CREATE TABLE IF NOT EXISTS Imp_Organization(
 o_id BIGINT NOT NULL AUTO_INCREMENT,
 o_uuid BIGINT,
 parent_id BIGINT DEFAULT 0, 
 name VARCHAR(100), 
 opt_org_type VARCHAR(100), 
 reg_no VARCHAR(100),
 man_power VARCHAR(100), 
 resources TEXT,
 privacy INT(1) DEFAULT 1, 
 opt_sector VARCHAR(100),
 
PRIMARY KEY (o_id)); ";



  $res_pers=$db->Execute($q);

  $filename= $_SESSION['filename'];
 
  $rowsimported = 0 ; 
  
  $mapping=$_SESSION['mapping']; 
 
  $handle = fopen($filename, "r");
  $rows= 0; 
    while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
     
         	    
    for($i=0; $i<count($mapping); $i++)
    {
     if( $mapping[$i]!= 'do_not_import'){		    
      switch ($mapping[$i])
      { 
	 case 'o_uuid':
		 $insert_array['o_uuid']= $data[$i] ; 
	         break; 
         case 'parent_id': 
	         $insert_array['parent_id'] = $data[$i]; 
	         break; 
	 case 'name':
		$insert_array['name'] = $data[$i];
		break;
	case 'opt_org_type' : 
		$insert_array['opt_org_type']=$data[$i]; 
		break; 
	case 'reg_no':
		$insert_array['reg_no'] = $data[$i]; 
		break;
	case 'man_power': 
	        $insert_array['man_power'] = $data[$i]; 
		break; 
	case 'resources': 
		$insert_array['resources'] = $data[$i]; 
	case 'privacy': 
		$insert_array['privacy']	= $data[$i];
		break; 
	case 'opt_sector': 
		$insert_array['opt_sector'] = $data[$i];
		break; 
	default : 
	 break;	
		
      } //end switch
     
    }//end if 
    else { 
	continue; 
      }
          
    }//end of for loop	 
    


if((!$_SESSION['skipColumnHeader'])&& $rows ===0 ){
++$rows	;
continue; 
}
else {
  shn_db_insert($insert_array,'Imp_Organization',true,'o_id');
 ++ $rowsimported ; 
 }
  ++$rows;
   }//end of the while loop  
   shn_form_fopen("imp_per_summary",null,array('req'=> false));  
   shn_form_fsopen(_('Summary'));
    echo 'Import has completed successfully. The information below summarizes the results.'; 
    ?>
    <p></p>
    <p><?php echo('Total Number of Rows in the Upload File: ');
      echo $rows; ?></p>
    <?php
   
    echo 'Total Number of Imported Rows:'; 
    echo $rowsimported ;
    shn_form_fsclose();
    shn_form_submit(_('Done')); 
    shn_form_fclose();
fclose($handle);
 
} 


?>



