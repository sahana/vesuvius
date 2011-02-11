<?php
// from:http://goo.gl/Wo1uE
// adds base64 decoding support to IE <= 7
$data = split(";", $_SERVER["QUERY_STRING"]);
$type = $data[0];
$data = split(",", $data[1]);
header("Content-type: ".$type);
echo base64_decode($data[1]);
