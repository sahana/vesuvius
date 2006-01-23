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
function shn_config_update($modify, $config_file, $output_file)
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
?>
