<?php
/* $Id: individual.inc,v 1.2 2006-06-29 06:06:28 thushari Exp $ */


/**
 * Data Import upload file 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	  Thushari Silva <atpsilva@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage imp
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

global $global;


include_once ($global['approot'].'mod/imp/utils/array.inc');
include_once ($global['approot'].'mod/imp/utils/type.inc');


class imp_Contact_DAO_Individual {
    /**
    * static instance to hold the table name
    *
    * @var string
    * @static
    */
    static $_tableName = 'imp_individual';
    /**
    * static instance to hold the field values
    *
    * @var array
    * @static
    */
    static $_fields = null;
    
    /**
    * static instance to hold the values that can
    * be imported / apu
    *
    * @var array
    * @static
    */
    static $_import = null;
   
    /**
    * Unique Individual ID
    *
    * @var int unsigned
    */
    public $p_uuid;
     
    /**
    * Full Name.
    *
    * @var string
    */
    public $full_name;
    /**
    * Family Name.
    *
    * @var string
    */
    public $family_name;
    /**
    * Localized Name.
    *
    * @var string
    */
    public $l10n_name;
    
    /**
    * Custom Name.
    *
    * @var string
    */
    public $custom_name;
   
    /**
    * id card #, passport #, Driving License # etc
    *
    * @var string
    */
    public $serial;
  
    /**
    * Date of birth
    *
    * @var date
    */
    public $birth_date;
    /**
    *
    * @var boolean
    */
    public $isReliefWorker;



    /**
    * whether injured, missing etc..
    * @var string
    */
    public $opt_status;


    /**
    * date of update
    * @var string
    */
    public $updated;

 /**
    * phone#, email etc..
    * @var string
    */
    public $contact_value;

  /**
    *
    * @var boolean
    */
    public $isvictim;

    /**
    *
    * @var string
    */
    public $opt_contact_type;

    /**
    *
    * @var string
    */
    public $opt_age_group;


    /**
    *
    * @var string
    */
     public $opt_person_loc_type;
   
    /**
    *
    * @var string
    */
     public $address;
   

    /**
    *
    * @var string
    */
     public $postcode;


    /**
    * class constructor
    *
    * @access public
    * @return imp_individual
    */
    function __construct() 
    {
        
    }
    
    /**
    * returns all the column names of this table
    *
    * @access public
    * @return array
    */
    function &fields() 
    {
        if (!(self::$_fields)) {
            self::$_fields = array(
                'p_uuid'=>array(
                    'name'=>'p_uuid',
                    'type'=>imp_Utils_Type::T_INT,
                    'required'=>true,
		    'import'=>true,
		   
                ) ,
                'full_name'=>array(
                    'name'=>'full_name',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Full Name') ,
                    'maxlength'=>100,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_individual.full_name',
                    'headerPattern'=>'/^full|(f(ull\s)?name)$/i',
                    'dataPattern'=>'/^\w+(\s\w+)?$/',
                   
                ) ,
                'family_name'=>array(
                    'name'=>'family_name',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Family Name') ,
                    'maxlength'=>50,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_individual.family_name',
                    'headerPattern'=>'/^family|(f(amily\s)?name)$/i',
                    'dataPattern'=>'/^\w+$/',
                    
                ) ,
                'l10n_name'=>array(
                    'name'=>'l10n_name',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Localized Name') ,
                    'maxlength'=>100,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_individual.l10n_name',
                    'headerPattern'=>'/^l10n|(l(10n\s)?name)$/i',
                    'dataPattern'=>'/^\w+$/',
                   
                ) ,
                'custom_name'=>array(
                    'name'=>'custom_name',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Custom Name') ,
                    'maxlength'=>50,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_individual.custom_name',
                    'headerPattern'=>'/^custom|(c(ustom\s)?name)$/i',
                    'dataPattern'=>'/^\w+(\s\w+)?+$/',
                ) ,
                'serial'=>array(
                    'name'=>'serial',
                    'type'=>imp_Utils_Type::T_STRING,
		    'title'=>_('Serial No') ,
                    'import'=>true,
		    'where'=>'imp_individual.serial',
                    'headerPattern'=>'/gender/i',
                    'dataPattern'=>'/^\w+(\s\w+)?+$/',
	    ) ,
		 'opt_id_type'=>array(
                    'name'=>'opt_id_type',
                    'type'=>imp_Utils_Type::T_STRING,
		    'title'=>_('ID Type') ,
                    'import'=>true,
		    'where'=>'imp_individual.opt_id_type',
		    'headerPattern'=>'/^id|(i(d\s)?type)$/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
		    

         	),
                'isReliefWorker'=>array(
                    'name'=>'isReliefWorker',
                    'type'=>imp_Utils_Type::T_STRING,
		    'title'=>_('Is Relief Worker') ,
                    'import'=>true,
		    'where'=>'imp_individual.isReliefWorker',
		    'headerPattern'=>'/ReliefWorker/i',
		    'dataPattern'=>'/^{0,1}?$/',

                ) ,
                'opt_status'=>array(
                    'name'=>'opt_status',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Option Status'),
		    'import'=>true,
		    'where'=>'imp_individual.opt_status',
		    'headerPattern'=>'/status/i',
		    'dataPattern'=>'/^\w+\s\w+?+$/',
                ) ,
                'opt_contact_type '=>array(
                    'name'=>'opt_contact_type ',
                    'type'=>imp_Utils_Type::T_STRING,
		    'title'=>_('Contact Type') ,
                    'import'=>true,
		    'where'=>'imp_individual.opt_contact_type',
	 'headerPattern'=>'/^opt|(o(pt\s)contact|(c(ontact\s))?type)$/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
                   
                ) ,
                'contact_value'=>array(
                    'name'=>'contact_value',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Contact Value') ,
                    'maxlength'=>100,
                    'size'=>imp_Utils_Type::HUGE,
                    'import'=>true,
                    'where'=>'imp_individual.contact_value',
                    'headerPattern'=>'/^contact|(c(ontact\s)?value)$/i',
                    'dataPattern'=>'//',
                    
                ) ,
                'isvictim'=>array(
                    'name'=>'isvictim',
		    'title'=>_('Is Victim') ,
                    'type'=>imp_Utils_Type::T_BOOLEAN,
		    'import'=>true,
		    'where'=>'imp_individual.isvictim',
		    'headerPattern'=>'/victim/i',
		    'dataPattern'=>'/^{0,1}?$/',
                ) ,
		    'relation'=>array(
                    'name'=>'relation ',
                    'type'=>imp_Utils_Type::T_STRING,
		    'import'=>true,
		    'where'=>'imp_individual.relation ',
                    'headerPattern'=>'/relation/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
		    
                ) ,
                'birth_date'=>array(
                    'name'=>'birth_date',
                    'type'=>imp_Utils_Type::T_DATE,
                    'title'=>_('Birth Date') ,
                    'import'=>true,
                    'where'=>'imp_individual.birth_date',
                    'headerPattern'=>'/^(birth|dob)/i',
                    'dataPattern'=>'/\d{4}-?\d{2}-?\d{2}/',
                
                ) ,
                'opt_age_group'=>array(
                    'name'=>'opt_age_group',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Age Group') ,
                    'where'=>'imp_individual.opt_age_group',
                    'headerPattern'=>'/age/i',
                    'dataPattern'=>'',
                    'import'=>true,
                ) ,
                'opt_person_loc_type'=>array(
                    'name'=>'opt_person_loc_type',
                    'type'=>imp_Utils_Type::T_STRING,
		    'title'=>_('Location Type') ,
                    'import'=>true,
                    'where'=>'imp_individual.opt_person_loc_type',
                    'headerPattern'=>'/location/i',
                ) ,
                'address'=>array(
                    'name'=>'address',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Address') ,
                    'import'=>true,
                    'where'=>'imp_individual.address',
                    'headerPattern'=>'/address/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
                ) ,

		'postcode'=>array(
                    'name'=>'postcode',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Postal Code') ,
                    'import'=>true,
                    'where'=>'imp_individual.postcode',
                    'headerPattern'=>'/code/i',
	        ),   
                'long_lat'=>array(
                    'name'=>'long_lat',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Lonigitde Latitude') ,
                    'import'=>true,
                    'where'=>'imp_individual.long_lat',
                    'headerPattern'=>'/^long|(l(ong\s)?lat)$/i',
		    'dataPattern'=>'//',
       	        ) , 
		'next_kin_uuid'=>array(
                    'name'=>'next_kin_uuid',
                    'type'=>imp_Utils_Type::T_INT,
                    'required'=>true,
		    'import'=>true,
		    'headerPattern'=>'/^kin|(k(in\s)?uuid)$/i',
		    'dataPattern'=>'/^\w+\s\w+?+$/',
	        ),
                 'opt_country'=>array(
                    'name'=>'opt_country',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Address') ,
                    'import'=>true,
                    'where'=>'imp_individual.opt_country',
                    'headerPattern'=>'/country/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
                ) ,
		'opt_race'=>array(
                    'name'=>'opt_race',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Race'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_race',
                    'headerPattern'=>'/race/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
        	),
		'opt_religion'=>array(
                    'name'=>'opt_religion',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Religion'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_religion',
                    'headerPattern'=>'/religion/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
        	),
		'opt_marital_status'=>array(
                    'name'=>'opt_marital_status',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Marital Status'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_marital_status',
                    'headerPattern'=>'/^marital|(m(arital\s)?status)$/i',
		    'dataPattern'=>'/^\w+(\S\w+)?+$/',
        	),
		'opt_gender'=>array(
                    'name'=>'opt_gender',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Gender'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_gender',
                    'headerPattern'=>'/^(gender|sex)/i',
                    'dataPattern'=>'/^(f|m|(fe)?male)\.?$/i',
		    
              	),
		'occupation'=>array(
                    'name'=>'occupation',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Occupation'),
                    'import'=>true,
                    'where'=>'imp_individual.occupation',
                    'headerPattern'=>'/occupation/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
        	),
		'opt_blood_type'=>array(
                    'name'=>'opt_blood_type',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Blood Type'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_blood_type',
                    'headerPattern'=>'/^blood|(b(lood\s)?type)$/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
        	),
		'height'=>array(
                    'name'=>'height',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Height'),
                    'import'=>true,
                    'where'=>'imp_individual.height',
                    'headerPattern'=>'/height/i',
		    'dataPattern'=>'//',
        	),
		'weight'=>array(
                    'name'=>'weight',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Weight'),
                    'import'=>true,
                    'where'=>'imp_individual.weight',
                    'headerPattern'=>'/weight/i',
		    'dataPattern'=>'//',
        	),
		'opt_eye_color'=>array(
                    'name'=>'opt_eye_color',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Eye Colour'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_eye_color',
                    'headerPattern'=>'/^eye|(e(ye\s)?colour)$/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
        	),
		'opt_skin_color'=>array(
                    'name'=>'opt_skin_color',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Skin Colour'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_skin_color',
                    'headerPattern'=>'/^skin|(s(kin\s)?colour)$/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
        	),
		'opt_hair_color'=>array(
                    'name'=>'opt_hair_color',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Hair Colour'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_hair_color',
                    'headerPattern'=>'/^hair|(h(air\s)?colour)$/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
        	),
		'injuries'=>array(
                    'name'=>'injuries',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Injuries'),
                    'import'=>true,
                    'where'=>'imp_individual.injuries',
                    'headerPattern'=>'/injuries/i',
		    'dataPattern'=>'//',
              ), 
	      	'comments_physical'=>array(
                    'name'=>'comments_physical',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Comments Physical'),
                    'import'=>true,
                    'where'=>'imp_individual.comments_physical',
                    'headerPattern'=>'/comments/i',
		    'dataPattern'=>'//',
              ),  
		'last_seen'=>array(
                    'name'=>'last_seen',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Last Seen'),
                    'import'=>true,
                    'where'=>'imp_individual.last_seen',
                    'headerPattern'=>'/^last|(l(ast\s)?seen)$/i',
		    'dataPattern'=>'//',
              ), 
	      'last_clothing'=>array(
                    'name'=>'last_clothing',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Last Clothing'),
                    'import'=>true,
                    'where'=>'imp_individual.last_clothing',
                    'headerPattern'=>'/clothing/i',
		    'dataPattern'=>'//',
              ), 
	      'comments_missing'=>array(
                    'name'=>'comments_missing',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Comments Missing'),
                    'import'=>true,
                    'where'=>'imp_individual.comments_missing',
                    'headerPattern'=>'/comments/i',
		    'dataPattern'=>'//',
              ),  
	      'details'=>array(
                    'name'=>'details',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Details'),
                    'import'=>true,
                    'where'=>'imp_individual.details',
                    'headerPattern'=>'/details/i',
		    'dataPattern'=>'//',
              ), 
	       'date_of_death'=>array(
                    'name'=>'date_of_death',
                    'type'=>imp_Utils_Type::T_DATE,
                    'title'=>_('Date of Death') ,
                    'import'=>true,
                    'where'=>'imp_individual.date_of_death',
                    'headerPattern'=>'/^date|(d(ate\s)?death)$/i',
                    'dataPattern'=>'/\d{4}-?\d{2}-?\d{2}/',
                ) ,
	        'location'=>array(
                    'name'=>'location',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Location'),
                    'import'=>true,
                    'where'=>'imp_individual.location',
                    'headerPattern'=>'/location/i',
		    'dataPattern'=>'//',
              ), 
	      'place_of_death'=>array(
                    'name'=>'place_of_death',
                    'type'=>imp_Utils_Type::T_DATE,
                    'title'=>_('Place of Death') ,
                    'import'=>true,
                    'where'=>'imp_individual.place_of_death',
                    'headerPattern'=>'/^place|(p(lace\s)?death)$/i',
                    'dataPattern'=>'//',
                ) ,
		'comments_deceased'=>array(
                    'name'=>'comments_deceased',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Comments Deceased'),
                    'import'=>true,
                    'where'=>'imp_individual.comments_deceased',
                    'headerPattern'=>'/comments/i',
		    'dataPattern'=>'//',
              ),  
	      'parent_id'=>array(
                    'name'=>'parent_id',
                    'type'=>imp_Utils_Type::T_INT,
                    'title'=>_('Parent Id'),
                    'import'=>true,
                    'where'=>'imp_individual.parent_id',
                    'headerPattern'=>'/^parent|(p(arent\s)?id)$/i',
		    'dataPattern'=>'//',
              ), 
	      'search_id'=>array(
                    'name'=>'search_id',
                    'type'=>imp_Utils_Type::T_INT,
                    'title'=>_('Search Id'),
                    'import'=>true,
                    'where'=>'imp_individual.search_id',
                    'headerPattern'=>'/^search|(s(earch\s)?id)$/i',
		    'dataPattern'=>'//',
              ), 
	      'opt_location_type'=>array(
                    'name'=>'opt_location_type',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Location Type'),
                    'import'=>true,
                    'where'=>'imp_individual.opt_location_type',
                    'headerPattern'=>'/^location|(l(ocation\s)?type)$/i',
		    'dataPattern'=>'//',
              ), 
	      'loc_name'=>array(
                    'name'=>'loc_name',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Location Name'),
                    'import'=>true,
                    'where'=>'imp_individual.loc_name',
                    'headerPattern'=>'/^loc|(l(oc\s)?name)$/i',
		    'dataPattern'=>'//',
              ), 
              'iso_code'=>array(
                    'name'=>'iso_code',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('ISO Code'),
                    'import'=>true,
                    'where'=>'imp_individual.iso_code',
                    'headerPattern'=>'/^iso|(i(so\s)?code)$/i',
		    'dataPattern'=>'//',
              ), 
	      'description'=>array(
                    'name'=>'description',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Description'),
                    'import'=>true,
                    'where'=>'imp_individual.description',
                    'headerPattern'=>'/description/i',
		    'dataPattern'=>'//',
              ), 
            );
        }
        return self::$_fields;
    }
    /**
    * returns the names of this table
    *
    * @access public
    * @return string
    */
   function getTableName() 
    {
        return self::$_tableName;
    }
    /**
    * returns the list of fields that can be imported
    *
    * @access public
    * return array
    */
    function &import() 
    {
        if (!(self::$_import)) {
            self::$_import = array();
            $fields = &self::fields();
            foreach($fields as $name=>$field) {
                if (imp_Utils_Array::value('import', $field)) {
                        self::$_import[$name] = &$fields[$name];
                    
                }
            }
        }
        return self::$_import;
    }
   
 

 /**
    * returns the list of header pattern og the imported field
    *
    * @access public
    * return array
    */


    
}
?>
