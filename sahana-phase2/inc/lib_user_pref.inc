<?php
function shn_user_pref_populate()
{
    global $global;
    
    $sql = "SELECT module_id, pref_key, value FROM user_preference WHERE p_uuid = '".$_SESSION['user_id']."'";
    $arr = $global['db']->GetAll($sql);
    if(! empty($arr)){
        //clean the session
        $_SESSION['user_pref'] = null;
        foreach($arr as $row){
            $_SESSION['user_pref_'.$row['module_id'].'_'.$row['pref_key']] = $row['value'];
        }
    }else{
        //go with the session.. hmmm
    }
}
function shn_get_user_pref_value($module,$key,$userid=NULL)
{
    global $global;
    if(NULL==$userid){
    	$userid=$_SESSION['user_id'];
    }
    $sql = "SELECT value FROM user_preference WHERE p_uuid = '".$_SESSION['user_id']."' AND module_id = '$module' AND pref_key='$key'";
    $res = $global['db']->Execute($sql);
    if(NULL!=$res){
    	return $res->fields['value'];
    }
    else{
    	return NULL;
    }
    
}
function shn_user_pref_update($module,$key,$value=null,$delete=false)
{
    global $global;
    if($delete){
        $sql = "DELETE FROM user_preference WHERE p_uuid = '".$_SESSION['user_id']."' AND module_id = '$module' 
                AND pref_key = '$key' ";
        $global['db']->Execute($sql);
    }else{
        //create the session
        $_SESSION['user_pref_'.$module.'_'.$key] = $value;
        
        //dump to the database
        $sql = "DELETE FROM user_preference WHERE p_uuid = '".$_SESSION['user_id']."' AND module_id = '$module' 
                AND pref_key = '$key' ";
        $global['db']->Execute($sql);
        $sql = "INSERT INTO user_preference (p_uuid, module_id, pref_key, value) VALUES
                ('{$_SESSION['user_id']}','$module','$key','$value') ";
        $global['db']->Execute($sql);
    }
    return $value;
}

function _shn_pref_ajax_update($module,$key,$value){
	shn_user_pref_update($module,$key,$value);
}

