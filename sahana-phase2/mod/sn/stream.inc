<?php

require_once ($global['approot'].'inc/lib_image.inc');


function shn_dvr_default(){


}


function shn_sn_gr_img()
{
    global $global;
  echo 'streaminiggggggggggggggg';

    $x_uuid = $_GET['x_uuid'];
    switch ($_GET['stream_type']){
        case 'image' :
            if($_GET['session']){
                shn_show_image_stream($x_uuid, true, $_SESSION['sn']['group']['image'],true);
            }else{
                if($_GET['thumbnail'])
                    shn_show_image_stream($x_uuid,true);
                else
                    shn_show_image_stream($x_uuid,false);
            }
     break;
    }
}







