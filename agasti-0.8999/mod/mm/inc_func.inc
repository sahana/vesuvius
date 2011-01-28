 <?php
 function recursiveDelete($str){
        if(is_file($str)){
        	 return @unlink($str);
        }
        elseif(is_dir($str)){
        	
        	$scan = glob(rtrim($str,'/').'/*');
            foreach($scan as $index=>$path){
                recursiveDelete($path);
                rmdir($str);
            }
            return @rmdir($str);
        }
    }


function list_dir($dir_handle,$path)
{  
	static $files;
	
    while (false !== ($file = readdir($dir_handle))) {
        $dir =$path.'/'.$file;
         if(is_dir($dir) && $file != '.' && $file !='..' )
        {	   
            $handle = @opendir($dir) or die("unable to open file");
            list_dir($handle, $dir);
        }elseif($file != '.' && $file !='..' && preg_match("/.sql/",$file))
        {	
        	$files[]=$dir;

        }
    }	
       	return $files;
}

function module_backup($module)
{
    global $global;
    if($module!="" or $module!=null)
    {
    $source=  $global['approot'].'mod/'.$module;
    $directory =$global['approot'].'www/tmp/mm_backups/mm_mod';
    $destination=$directory.'/'.$module;
    if(is_writeable($directory))
    {
        recursive_copy($source, $destination);
    }
    else
    {
        echo "folder unwritable";
    }
    }
    else
    {
        add_error(_t("Illegal access of this function"));
    }
}

function shn_mm_temp()
{
    module_backup("msg");

}


function recursive_copy($src,$dst) {
    $dir = opendir($src);
    @mkdir($dst);
    while(false !== ( $file = readdir($dir)) ) {
        if (( $file != '.' ) && ( $file != '..' )) {
            if ( is_dir($src . '/' . $file) ) {
                recursive_copy($src . '/' . $file,$dst . '/' . $file);
            }
            else {
                copy($src . '/' . $file,$dst . '/' . $file);
            }
        }
    }
    closedir($dir);
} 