<?php
/**
 * shn_config_update 
 * 
 * @param mixed $modify 
 * @param mixed $config_file 
 * @param mixed $output_file 
 * @access public
 * @return void
 */
function shn_config_file_update($modify, $config_file, $output_file)
{
    global $global;

    $fh_c = fopen($config_file,'r');
    if (!( $fh_t = fopen($output_file,'w') ))
        return false; // if unable to open the file for write

    while (! feof ($fh_c) ) {
        
        $line = fgets($fh_c,1024);
        $match = false;

        // iterate through the list of possible replacements in the line
        foreach ($modify as $search => $replace ) {
        
            if (preg_match($search,$line)) {
                $match = true;
                fputs($fh_t,$replace."\n");
            }
        }
        if (!$match) // if no match was found output the default line
            fputs($fh_t, $line);
    }
    fclose($fh_c);
    fclose($fh_t);
    return true;
}

// Load the repective module conf.inc file
function shn_config_base_conf_fetch() 
{
    global $global;
    global $conf;

    $approot = $global['approot'];

    require ($approot.'conf/sysconf.inc');

    // include the module configuration files 
/*    $d = dir($approot.'conf/');
    while (false !== ($f = $d->read())) {
        if (preg_match('^[0-9]*.*\.inc$',$f)) {
          require ($approot.'conf/'.$f);
        }
    } */
}



// Load the repective module conf.inc file
function shn_config_module_conf_fetch($module = 'all') 
{
    global $global;
    global $conf;

    $approot = $global['approot'];

    if ('all' == $module) {
        // include the module configuration files 
        $d = dir($approot.'mod/');
        while (false !== ($f = $d->read())) {
            if (file_exists($approot.'mod/'.$f.'/conf.inc')) {
              include ($approot.'mod/'.$f.'/conf.inc');
            }
        } 
    } else {
        include ($approot.'mod/'.$module.'/conf.inc');
    }       
}

/**
 * shn_config_fetch 
 * 
 *    - all  : all configuration
 *    - base : base configuration
 *    - you can sepecify the module name
 *    
 * @param string $type 
 * @access public
 * @return void
 */
function shn_config_database_fetch($type='base')
{
    global $global;
    global $conf;

    if($type == 'all')
        $sql = "SELECT module_id, confkey, value FROM config";
    else
        $sql = "SELECT module_id, confkey, value FROM config WHERE module_id = '$type'";

    if($results = $global['db']->GetAll($sql)){
        foreach($results as $result)
            if($result['module_id'] == 'base')
                $conf[$result['module_id'].'_'.$result['confkey']] = $result['value'];
            else    
                $conf['mod_'.$result['module_id'].'_'.$result['confkey']] = $result['value'];
    }
}
?>
