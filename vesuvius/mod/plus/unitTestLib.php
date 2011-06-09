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
			if($pos === false) {
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



////// PLUS UNIT TEST FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////



function version() {
	global $sites;
	echo "<tr><td>version()</td>";
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
	echo "<tr><td>getEventList()</td>";
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
	echo "<tr><td>getEventListUser(user, pass)</td>";
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
	echo "<tr><td>getGroupList()</td>";
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
	echo "<tr><td>getHospitalList()</td>";
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
	echo "<tr><td>getHospitalData(uuid)</td>";
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
	echo "<tr><td>getHospitalPolicy(uuid)</td>";
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















