<?php
global $connect;
$connect=mysql_connect("localhost","root","root") or die(mysql_error());
$mysql="sahana_mdrs";

mysql_select_db($mysql);
mysql_query('TRUNCATE TABLE `location`',$connect);

$data=file_get_contents("sri_lanka_gn.csv");
$exp =array();

$data = preg_replace('/'.chr(10).'/','<br/>',$data);
$exp = explode('<br/>',$data);

$i = 0;
$count = 0;
foreach($exp as $e){
    // FOR EACH LINE
    $e = str_replace('"','',$e);
    $locs = explode(',',$e);


    $last_parent = null;
    // FOR EACH LOCATION
    $j = 0;

    foreach($locs as $loc){
    
        $loc = trim($loc);
        // IF STRING IS NOT EMPTY
        if(strlen($loc)>0){

            $id = 'lc-'.($i+1);
            $loc_type = ($j+1);

            // GET LAST PARENT
            $query = null;
            if($j>0){
                $last_parent = "'".getLocUUID($locs[$j-1],($loc_type-1))."'";
                $query1 = "SELECT COUNT(*) FROM location WHERE name='".$loc."' AND opt_location_type='".$loc_type."' AND parent_id=".$last_parent;
            }else{
                $last_parent = 'NULL';
                $query1 = "SELECT COUNT(*) FROM location WHERE name='".$loc."' AND opt_location_type='".$loc_type."'";
            }

            // CHECK IF INSERTED
            
            //echo $query1."<br/>\n";
            $res = mysql_query($query1,$connect);
            $res = mysql_fetch_array($res);
            $count = $res[0];

            if($count=="0"){
                echo "INSERTING ".$loc."\n";
                $query2 = "INSERT INTO location (loc_uuid, parent_id, opt_location_type, name ) VALUES ('".$id."', ".$last_parent.",'".$loc_type."' , '".$loc."')";
                //echo $query2."<br/>\n";
                $res = mysql_query($query2,$connect);
                if(mysql_errno($connect)>0){
                    echo mysql_error($connect);
                    break 2;
                }
                $count++;

                $i++;
            }else{
                echo "NOT INSERTING ".$loc."\n";
            }
        }
        $j++;
    }
}

echo "{$count} Locations inserted successfully.<br/>\n";

function getLocUUID($loc,$level){
    global $connect;
    $query1 = "SELECT loc_uuid FROM location WHERE name='".$loc."' AND opt_location_type='".$level."'";
    $res = mysql_query($query1,$connect);
    if($res){
        $res = mysql_fetch_array($res);
        return $res[0];
    }else{
        return null;
    }
}
