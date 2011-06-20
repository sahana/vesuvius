<?
function init() {
	echo "
		<body>
		<style>
			body {
				background-color: #000;
				color: #fff;
				font-size: 12px;
				font-family: courier;
				margin: 20px;
			}
			table {
				width: 100%;
			}
			th {
				font-size: 150%;
			}
			td {
				background-color: #333;
				text-align: center;
				width: 20%;
				border: 1px solid #000;
			}
			td.func {
				text-align: left;
				padding-left: 5px;
			}
			td.pass {
				color: green;
				background-color: green;
			}
			td.fail {
				color: white;
				background-color: red;
				font-weight: bold;
			}
			a:link, a:visited, a:hover, a:active {color: orange; text-decoration: none;}
			a:hover {text-decoration:underline;}
		</style>
	";
}



function init2() {
	global $sites;
	echo "
		<table><tr><th>function</th>
	";
	foreach($sites as $name => $wsdl) {
		echo "<th>".$name."</th>";
	}
	echo "</tr>";
}



function showEntry() {
	global $conf;
	echo "
		<h1>PLUS Web Service Unit Tests</h1>
		<br>
		<h2>Available API Levels:</h2><br>
	";
        $dir   = getcwd();
        $files = scandir($dir);
        $j     = count($files);
        for ($i = 0; $i < $j; $i++) {
                if ($files[$i] == "." || $files[$i] == "..") {
                        array_splice($files, $i, 1);
                        $j--;
                } else {
			$pos = strpos($files[$i], "api_");
			$til = strpos($files[$i], "~");
			if($pos === false || $til) {
				// not an api
			} else {
				$a = str_replace("api_", "", $files[$i]);
				$a = str_replace(".inc", "", $a);
				if($a == $conf['mod_plus_latest_api']) {
					$b = " (current)";
				} else {
					$b = "";
				}
				echo "<h2><a href=\"unitTest.php?api=".$a."\">".$a."</a>".$b."</h2>";
			}
		}
        }
}



// stub to not fatally die!
function _t() {}



////// PLUS UNIT TEST GENERAL FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST GENERAL FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST GENERAL FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


function version() {
	global $sites;
	echo "<tr><td class=\"func\">version()</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		//$client->useHTTPPersistentConnection();
		$result = $client->call('version', array(null));
		if(is_array($result) && (($result['versionMajor'] == 1) || ($result['versionMajor'] == 2))) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function getEventList() {
	global $sites;
	echo "<tr><td class=\"func\">getEventList()</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getEventList', array(null));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function getEventListUser($username, $password) {
	global $sites;
	echo "<tr><td class=\"func\">getEventListUser(user,pass)</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getEventListUser', array('username'=>$username, 'password'=>$password));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function getGroupList() {
	global $sites;
	echo "<tr><td class=\"func\">getGroupList()</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getGroupList', array(null));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function getHospitalList() {
	global $sites;
	echo "<tr><td class=\"func\">getHospitalList()</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getHospitalList', array(null));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function getHospitalData($uuid) {
	global $sites;
	echo "<tr><td class=\"func\">getHospitalData(uuid)</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getHospitalData', array('hospital_uuid'=>$uuid));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function getHospitalPolicy($uuid) {
	global $sites;
	echo "<tr><td class=\"func\">getHospitalPolicy(uuid)</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getHospitalPolicy', array('hospital_uuid'=>$uuid));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



////// PLUS UNIT TEST ACCOUNT FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST ACCOUNT FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST ACCOUNT FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


function registerUser($username, $emailAddress, $password, $givenName, $familyName) {
	global $sites;
	echo "<tr><td class=\"func\">registerUser(username, emailAddress, password, givenName, familyName)</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('registerUser', array('username'=>$username, 'emailAddress'=>$emailAddress, 'password'=>$password, 'givenName'=>$givenName, 'familyName'=>$familyName));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function changeUserPassword($username, $oldPassword, $newPassword) {
	global $sites;
	echo "<tr><td class=\"func\">changeUserPassword(username, oldPassword, newPassword)</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('changeUserPassword', array('username'=>$username, 'oldPassword'=>$oldPassword, 'newPassword'=>$newPassword));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}


function getSessionTimeout() {
	global $sites;
	echo "<tr><td class=\"func\">getSessionTimeout()</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getSessionTimeout', array(null));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}


////// PLUS UNIT TEST SEARCH FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST SEARCH FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST SEARCH FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







////// PLUS UNIT TEST REPORTING FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST REPORTING FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST REPORTING FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////













