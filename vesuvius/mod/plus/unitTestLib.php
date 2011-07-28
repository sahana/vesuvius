<?
/**
 * @name         PL User Services
 * @version      1.9.4
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0705
 */

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
			table {}
			th {
				font-size: 150%;
			}
			td {
				background-color: #333;
				text-align: center;
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
			.minw { min-width: 150px; }
		</style>
	";
}



function init2() {
 	global $sites;
	echo "
		<table><tr><th>#</th><th>function</th>
	";
	foreach($sites as $name => $wsdl) {
		echo "<th class=\"minw\">".$name."</th>";
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">version</td>";
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getEventList</td>";
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getEventListUser</td>";
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getGroupList</td>";
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getHospitalList</td>";
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getHospitalData</td>";
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getHospitalPolicy</td>";
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



function getHospitalLegalese($uuid) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getHospitalLegalese</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getHospitalLegalese', array('hospital_uuid'=>$uuid));
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">registerUser</td>";
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">changeUserPassword</td>";
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



function resetUserPassword($username) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">resetUserPassword</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('resetUserPassword', array('username'=>$username));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function forgotUsername($email) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">forgotUsername</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('forgotUsername', array('email'=>$email));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function checkUserAuth($username, $password) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">checkUserAuth</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('checkUserAuth', array('username'=>$username, 'password'=>$password));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function getUserStatus($username) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getUserStatus</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getUserStatus', array('username'=>$username));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function getUserGroup($username) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getUserGroup</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getUserGroup', array('username'=>$username));
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
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getSessionTimeout</td>";
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


function search($shortname, $searchTerm) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">search</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('search', array(
			'eventShortname'       => $shortname,
			'searchTerm'           => $searchTerm,
			'filterStatusMissing'  => true,
			'filterStatusAlive'    => true,
			'filterStatusInjured'  => true,
			'filterStatusDeceased' => true,
			'filterStatusUnknown'  => true,
			'filterStatusFound'    => true,
			'filterGenderComplex'  => true,
			'filterGenderMale'     => true,
			'filterGenderFemale'   => true,
			'filterGenderUnknown'  => true,
			'filterAgeChild'       => true,
			'filterAgeAdult'       => true,
			'filterAgeUnknown'     => true,
			'filterHospitalSH'     => true,
			'filterHospitalNNMCC'  => true,
			'filterHospitalOther'  => true,
			'pageStart'            => 0,
			'perPage'              => 10,
			'sortBy'               => "",
			'mode'                 => true
			));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}



function searchWithAuth($shortname, $searchTerm, $username, $password) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">searchWithAuth</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('searchWithAuth', array(
			'eventShortname'       => $shortname,
			'searchTerm'           => $searchTerm,
			'filterStatusMissing'  => true,
			'filterStatusAlive'    => true,
			'filterStatusInjured'  => true,
			'filterStatusDeceased' => true,
			'filterStatusUnknown'  => true,
			'filterStatusFound'    => true,
			'filterGenderComplex'  => true,
			'filterGenderMale'     => true,
			'filterGenderFemale'   => true,
			'filterGenderUnknown'  => true,
			'filterAgeChild'       => true,
			'filterAgeAdult'       => true,
			'filterAgeUnknown'     => true,
			'filterHospitalSH'     => true,
			'filterHospitalNNMCC'  => true,
			'filterHospitalOther'  => true,
			'pageStart'            => 0,
			'perPage'              => 10,
			'sortBy'               => "",
			'mode'                 => true,
			'username'             => $username,
			'password'             => $password
			));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}


////// PLUS UNIT TEST REPORTING FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST REPORTING FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST REPORTING FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


function reportPerson($personXML, $eventShortName, $xmlFormat, $user, $pass) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">reportPerson</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('reportPerson', array('personXML'=>$personXML, 'eventShortName'=>$eventShortName, 'xmlFormat'=>$xmlFormat, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}


function createPersonUuid($user, $pass) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">createPersonUuid</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('createPersonUuid', array('username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}


function createPersonUuidBatch($number, $user, $pass) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">createPersonUuidBatch</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('createPersonUuidBatch', array('number'=>$number, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}

function createNoteUuid($user, $pass) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">createNoteUuid</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('createNoteUuid', array('username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}

function createNoteUuidBatch($number, $user, $pass) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">createNoteUuidBatch</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('createPersonUuidBatch', array('number'=>$number, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL</blink></td>";
		}
	}
	echo "</tr>";
}

