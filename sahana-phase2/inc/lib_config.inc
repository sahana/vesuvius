<?php
function shn_config_update($modify, $config_file, $output_file)
{
    global $global;

    $fh_c = fopen($config_file,'r');
    $fh_t = fopen($output_file,'w');

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
}
?>
