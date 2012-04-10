<?
/**
 * @name         PL User Services
 * @version      24
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0221
 */


function init() {
	echo "
		<body>
		<style>
			body {
				background-color: #000;
				color: #fff;
				font-family: courier;
				margin: 20px;
			}
			table { font-size: 14px; }
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
			td.stub {
				color: black;
				background-color: yellow;
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
			$f = strpos($files[$i], "f.inc");
			if($pos === false || $til || $f) {
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
		if(is_array($result) && ((int)$result['version'] > 23)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".(int)$result['version'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function getHospitalLegaleseAnon($uuid) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getHospitalLegaleseAnon</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getHospitalLegaleseAnon', array('hospital_uuid'=>$uuid));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}


function getHospitalLegaleseTimestamps($uuid) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getHospitalLegaleseTimestamps</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getHospitalLegaleseTimestamps', array('hospital_uuid'=>$uuid));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function resetUserPassword($email) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">resetUserPassword</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('resetUserPassword', array('email'=>$email));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			'username'             => $username,
			'password'             => $password
			));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}


function searchCount($shortname, $searchTerm) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">searchCount</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('searchCount', array(
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
			));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function searchCountWithAuth($shortname, $searchTerm, $username, $password) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">searchCountWithAuth</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('searchCountWithAuth', array(
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
			'username'             => $username,
			'password'             => $password
			));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
		$x = file_get_contents("reference_TRIAGEPIC1.xml");
		$result = $client->call('reportPerson', array('personXML'=>$x, 'eventShortName'=>'test', 'xmlFormat'=>'TRIAGEPIC1', 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && (($result['errorCode'] == 419) || ($result['errorCode'] == 420))) {
			echo "<td class=\"stub\">WARN(".$result['errorCode'].")</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
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
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



////// PLUS UNIT TEST Revision FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST Revision FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST Revision FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function reReportPerson($uuid, $personXML, $eventShortname, $xmlFormat, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">reReportPerson</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$x = file_get_contents("reference_TRIAGEPIC1.xml");
		$result = $client->call('reReportPerson', array('uuid'=>$uuid, 'personXML'=>$x, 'eventShortname'=>'test', 'xmlFormat'=>'TRIAGEPIC1', 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} elseif(is_array($result) && isset($result['errorCode']) && (($result['errorCode'] == 419) || ($result['errorCode'] == 420))) {
			echo "<td class=\"stub\">WARN(".$result['errorCode'].")</td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}


function expirePerson($uuid, $explanation, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">expirePerson</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('expirePerson', array('uuid'=>$uuid, 'explanation'=>$explanation, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0 || ($result['errorCode'] == 413))) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function getPersonExpiryDate($uuid) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getPersonExpiryDate</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getPersonExpiryDate', array('uuid'=>$uuid));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function setPersonExpiryDate($uuid, $expiryDate, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">setPersonExpiryDate</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('setPersonExpiryDate', array('uuid'=>$uuid, 'expiryDate'=>$expiryDate, 'user'=>$user, 'pass'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function setPersonExpiryDateOneYear($uuid, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">setPersonExpiryDateOneYear</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('setPersonExpiryDateOneYear', array('uuid'=>$uuid, 'user'=>$user, 'pass'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function getUuidByMassCasualtyId($mcid, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getUuidByMassCasualtyId</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getUuidByMassCasualtyId', array('mcid'=>$mcid, 'shortname'=>'test', 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 407)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}


function changeMassCasualtyId($newMcid, $uuid, $user, $pass) {
 	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">changeMassCasualtyId</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('changeMassCasualtyId', array('newMcid'=>$newMcid, 'uuid'=>$uuid, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}


function hasRecordBeenRevised($uuid, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">hasRecordBeenRevised</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('hasRecordBeenRevised', array('uuid'=>$uuid, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function addComment($uuid, $comment, $status, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">addComment</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('addComment', array('uuid'=>$uuid, 'comment'=>$comment, 'status'=>$status, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function getPersonPermissions($uuid, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getPersonPermissions</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getPersonPermissions', array('uuid'=>$uuid, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



////// PLUS UNIT TEST Image List FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST Image List FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// PLUS UNIT TEST Image List FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



function getImageCountsAndTokens($user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getImageCountsAndTokens</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getImageCountsAndTokens', array('username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function getImageList($tokenStart, $tokenEnd, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getImageList</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getImageList', array('tokenStart'=>$tokenStart, 'tokenEnd'=>$tokenEnd, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function getImageListBlock($tokenStart, $stride, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getImageListBlock</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getImageListBlock', array('tokenStart'=>$tokenStart, 'stride'=>$stride, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}



function getNullTokenList($tokenStart, $tokenEnd, $user, $pass) {
	global $sites;
	global $count;
	$count++;
	echo "<tr><td>".$count."</td><td class=\"func\">getNullTokenList</td>";
	foreach($sites as $name => $wsdl) {
		$client = new nusoap_client($wsdl);
		$result = $client->call('getImageList', array('getNullTokenList'=>$tokenStart, 'tokenEnd'=>$tokenEnd, 'username'=>$user, 'password'=>$pass));
		if(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 0)) {
			echo "<td class=\"pass\">&nbsp;</td>";
		} elseif(is_array($result) && isset($result['errorCode']) && ($result['errorCode'] == 9998)) {
			echo "<td class=\"stub\"><blink>STUB</blink></td>";
		} else {
			echo "<td class=\"fail\"><blink>FAIL(".$result['errorCode'].")</blink></td>";
		}
	}
	echo "</tr>";
}






