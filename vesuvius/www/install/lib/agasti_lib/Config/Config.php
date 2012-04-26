<?php
//$config=array();
//$config['base_uuid']='pl.nlm.nih.gov/';
//$config['theme']="vesuvius";
//$config['db_name']='';
//$config['db_host']='';
//$config['db_port']="3306";
//$config['db_user']='';
//$config['db_pass']='';
//$config['db_engine']="mysql";
//$config['storage_engine']="innodb";
//$config['dbal_lib_name']="adodb";
//$config['enable_monitor_sql']=false;
//$config['locale']="en_US";
//$config['default_module']='rez';
//$config['default_action']='landing';
//$config['pwd_min_chars']=8;
//$config['pwd_max_chars']=16;
//$config['pwd_has_uppercase']=true;
//$config['pwd_has_lowercase']=true;
//$config['pwd_has_numbers']=true;
//$config['pwd_has_spchars']=false;
//$config['pwd_has_username']=true;
//$config['pwd_no_change_limit']=true;
//$config['enable_locale']=false;
//$config['enable_plus_web_services']=true;
//$config['enable_solr_for_search']=false;
//
//
//
//$abc=new Config();
//$abc->writeFile($config);
//$abc->loadFile("config.php");

class Config{

    function dump($arrayParameters)
    {
       $fileparameter='';
       $finalString='';
       foreach ($arrayParameters as $key => $value) {

        $finalVal=  $this->identifyVariable($value);
        $fileparameter.="$"."config['".$key."']"."=".$finalVal."; \n";

        }
        $finalString="<?php \n".$fileparameter."\n ?>";
        
        return $finalString;
     }


    function identifyVariable($parameter)
    {
        switch(true)
        {

            case ($parameter==='false' || $parameter==="false"):
                return 'false';
            case ($parameter==='true' || $parameter==="true"):
                return 'true';
            case null==$parameter:
                return "\"\"";
            case $parameter=='':
                return "";
            case ctype_digit($parameter):
                return is_string($parameter)? "\"".$parameter."\"":(int)$parameter;
            case (!ctype_digit($parameter)&& is_numeric($parameter)):
                return (int)$parameter;
            default:
                return "\"".$parameter."\"";
        }
    }


    function writeConfigFile($writingParas)
    {
        $string="<?php \n".$writingParas."\n ?>";

        $file = fopen("config.php", "w");
        fwrite($file, $string);
        fclose($file);
    }


    function loadFile($filename)
    {
        $file=fopen($filename, 'r');
        $config='';
        while(!feof($file)) {

            $data = fgets($file);
            if($data!='')
            {
                $arrayparameters=explode("=", $data);
                if(count($arrayparameters)==2 && $arrayparameters[0]!='' && $arrayparameters[1]!='')
                {
                    $arrayindex= self::getArrayIndex1($arrayparameters[0]);
                    $arrayvalue=  self::getArrayValue($arrayparameters[1]);
                    $config[$arrayindex]=$arrayvalue;
                }
            }
       }
        fclose($file);
        return $config;
    }


    function getArrayIndex1($index)
    {
        $indexVal=substr($index, strpos($index, "[")+2,-2);

        return $indexVal;
    }

    function getArrayValue($value)
    {
        $arrayVal=  substr($value, 0,-3);
        switch (true)
        {
            case ((substr($arrayVal, 0, 1)=="\"" && substr($arrayVal, -1)=="\"") && strlen($arrayVal)==2):
                return null;
            case (substr($arrayVal, 0, 1)=="\"" && substr($arrayVal, -1)=="\""):
                return $arrayVal;
            default:
                return $arrayVal;

        }

    }


}

?>
