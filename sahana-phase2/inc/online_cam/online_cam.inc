<?php
function shn_online_cam($image_id){
    // generate random key.
    $seed = rand();
    $key = md5("KEY:".$seed);
    $_SESSION['online_cam']['seckey'] =  $key;
    $_SESSION['online_cam']['image_id'] = $image_id;
    //var_dump($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
    $server = "http://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
    
    if(substr($server,(strlen($server)-1),1)=='/'){
        $server = substr($server,0,(strlen($server)-1));
    }
    $server = urlencode($server);
    ?>

    <div id="home">
    <object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000"
        codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=9,0,0,0"
        width="300"
        height="220"
        align="middle"
        id="main"><!-- 
    <param name="allowScriptAccess" value="sameDomain" />
    <param name="movie" value="res/flash/online_cam.swf" />
    <param name="quality" value="high" />
    <param name="bgcolor" value="#ffffff" />
    <param name="FlashVars" value="serverUrl=http://192.168.0.7/sahana-dev&seckey=<?php echo $key; ?>" />-->
    <embed src="res/flash/online_cam.swf"
           width="300"
           height="220"
           autostart="false"
           quality="high"
           bgcolor="#000000"
           FlashVars="serverUrl=http://192.168.0.7/sahana-dev&seckey=<?php echo $key; ?>"
           name="main"
           align="middle"
           allowScriptAccess="sameDomain"
           type="application/x-shockwave-flash"
           pluginspage="http://www.macromedia.com/go/getflashplayer" />
    </object>
<?php   
}

function shn_online_cam_get_image_file_name($image_id){
    global $global;
    $name = $global['approot']."www/tmp/online_cam_".$image_id.".png";	
    return $name;
}

