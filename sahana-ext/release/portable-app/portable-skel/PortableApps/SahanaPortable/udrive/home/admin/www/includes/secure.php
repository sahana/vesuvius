<?
/*
####################################################
# Name: The Uniform Server Security 0.5
# Developed By: The Uniform Server Development Team
# Modified Last By: Olajide Olaolorun (empirex) 
# Web: http://www.uniformserver.com
####################################################
*/

if ($unisecure=="1") {

	if ( !($usip == "127.0.0.1")) {
	#if ( !($usip == "127.0.0.1") || !($hname == "localhost")) { //Causes error on some machines
  		echo "
		<div id=\"main\">
		<h2>&#187; ".$US['secure1-head']."</h2>
		<h3>".$US['secure1-sub']."</h3>
		<p>
		".$US['secure1-text-0']." '<b>".$usip."</b>'.
		<br />
		".$US['secure1-text-1']." '<b>".$hname."</b>'.
		<br />
		<br /> 
		".$US['secure1-text-2']."
		<p>
		</div>"; 

		require "footer.php";

  	exit;
	}
}
?>
