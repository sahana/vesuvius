<?php
//$htaccess=array();
//$htaccess['ErrorDocument 404']="/index.php";
//$htaccess['DirectoryIndex']="/index.php";
//$htaccess['RewriteEngine']="On";
//$htaccess['RewriteBase']="/";
//$htaccess['RewriteCond']=array();
//$htaccess['RewriteCond'][0]="%{REQUEST_FILENAME} -d [OR]";
//$htaccess['RewriteCond'][1]="%{REQUEST_FILENAME} -f";
//$htaccess['RewriteRule']=array();
//$htaccess['RewriteRule'][0]=".* - [S=7]";
//$htaccess['RewriteRule'][1]="^(person.[0-9]+)$ index.php?mod=eap&act=modrewrite&val=$1";
//$htaccess['RewriteRule'][2]="^(about|ABOUT)$ index.php?mod=rez&act=default&page_id=-30 [L]";
//$htaccess['RewriteRule'][3]="^(plus|PLUS)$ index.php?mod=rez&act=default&page_id=-45 [L]";
//$htaccess['RewriteRule'][4]="^(login|LOGIN)$ index.php?mod=pref&act=loginForm [L]";
//$htaccess['RewriteRule'][5]="^([^/][a-z0-9]+)$ index.php?shortname=$1";
//$htaccess['RewriteRule'][6]="^([^/][a-z0-9]+)/$ index.php?shortname=$1";
//$htaccess['RewriteRule'][7]="^([^/][a-z0-9]+)/(.+)$ $2?shortname=$1 [QSA]";
//
//$a=new Htaccess();
//$a->writeFile($htaccess);
//$a->loadFile();

class Htaccess
{
    function dump($fileArray){

        $fileContent="";
        foreach ($fileArray as $key => $value) {
            if(!is_array($fileArray[$key])){
                $fileContent.=$key." ".$value."\n";
            }
            else if(is_array($fileArray[$key])){
                foreach ($fileArray[$key] as $elementValue) {
                    $fileContent.=$key." ".$elementValue."\n";
                }
            }
        }
        return $fileContent;
    }

//    function writeContent($fileContent){
//        $file = fopen(".htaccess", "w");
//        fwrite($file, $fileContent);
//        fclose($file);
//    }

    function loadFile($filename){
        $htaccessvar=array();
        $file=fopen($filename, 'r');
        while(!feof($file)){
            $data = fgets($file);
            if($data!=''){
                $arrayparameters=explode(" ", $data);
//                if(count($arrayparameters)==2){
//                    $htaccessvar[$arrayparameters[0]]=$arrayparameters[1];
//                }
                if(count($arrayparameters)>2 && $arrayparameters[0]=="ErrorDocument" && $arrayparameters[1]=="404"){
                    $elementVal='';
                    for($i=2;$i<count($arrayparameters);$i++){
                        $elementVal.=$arrayparameters[$i]." ";
                    }
                    $htaccessvar[$arrayparameters[0]." ".$arrayparameters[1]]=$elementVal;
                }
                else if(count($arrayparameters)>=2){
                    $subArray=array();
                    $subArrayIndex=0;
                    foreach ($htaccessvar as $key1 => $value1) {
                        if($arrayparameters[0]==$key1 && !is_array($value1)){
                            $subArray[0]=$value1;
                            $elementVal='';
                            for($i=1;$i<count($arrayparameters);$i++){
                                $elementVal.=$arrayparameters[$i]." ";
                            }
                            $subArray[1]=$elementVal;
                            $htaccessvar[$key1]=$subArray;
                        }
                        else if($arrayparameters[0]==$key1 && is_array($value1)){
                            $elementVal='';
                            for($i=1;$i<count($arrayparameters);$i++){
                                $elementVal.=$arrayparameters[$i]." ";
                            }
                            $value1[count($value1)]=$elementVal;
                            $htaccessvar[$key1]=$value1;
                        }
                        else{
                            $elementVal='';
                            for($i=1;$i<count($arrayparameters);$i++){
                                $elementVal.=$arrayparameters[$i]." ";
                            }
                            $htaccessvar[$arrayparameters[0]]=$elementVal;
                        }
                    }
                }
            }
        }
        return $htaccessvar;
    }
}
?>
