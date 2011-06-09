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

////// PLUS UNIT TEST FUNCTIONS ////////


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















