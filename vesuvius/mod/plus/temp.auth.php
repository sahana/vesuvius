<?


function shn_soap_ws_authenticate(){
	global $global;
	if(shn_acl_is_web_service_auth_enabled()==true){


		/* HTTP basic authentication
		 * Since i wanted to authenticate based on the following policy, had to use the basic authentication
		 * credentials in an alternative way.
		 * Policy: In the process of signing up for the API key the following are issued
		 * 1. API key
		 * 2. Password
		 * 3. Secret Code
		 * API key and Password helps to identify the user. How ever, since these are transmitted in plain text
		 * needed something additional to prevent impersonation.
		 * Thus a digest is signed using HMAC_Sha1 algorithm and this signature is sent in the basic authentication.
		 * The digest is also , sent created using the time and few other values. How ever ,yet to write code to use those.
		 * Since the secret is shared only between the web server and user , only the user could have signed to be matched with the
		 * signature created with the shared secret at the server applied on the digest.
		 * How ever with basic authentication, only two values could be sent, but here 4 values are being sent.
		 * API key, password and digest were sent as PHP_AUTH_USER seperated by comma.
		 * PHP_AUTH_PW contains the signature. How ever , there are restrictions on the characters that
		 * can be sent in PHP_AUTH_PW. Thus most of the time , only part of the wierd signature gets transmitted.
		 * As a work around md5 hash is applied to the signature and sent , and doing the comparison also md5 is used at the last stage.
		 *
		 */
		if (!isset($_SERVER['PHP_AUTH_USER'])) {
			/*
			 * send the basic authentication challenge
			 */

			header('WWW-Authenticate: Basic realm="Sahana"');
			header("HTTP/1.0 401 Unauthorized");
			return false;
		}else{

			$arg1=explode(",", trim($_SERVER['PHP_AUTH_USER']));
			$sign=$_SERVER['PHP_AUTH_PW'];
			$digest=$arg1[2];

			// store the key globally so it can be logged elsewhere
			$global['api_key'] = $arg1[0];

			/*
			 * authenticate the user using the API Key and Password, if succeeds returns the secret for that user
			 */
			$secret=shn_authenticate_ws_user($arg1[0],$arg1[1]);

			if($secret==null){
				// return true;

				header("HTTP/1.0 401 Unauthorized");
				return false;
			}else{
				/*
				 * Verify the signature to ensure the digest was signed using the same secret the server is having in its database
				 */
				if(shn_authenticate_ws_signature($secret,$sign,$digest)==false){
					header("HTTP/1.0 401 Unauthorized");
					return false;
				}else{
					return true;
				}
			}
		}

	}else{
		//authentication is disabled from admin
		return true;
	}

}

function shn_authenticate_ws_signature($secret,$sign,$digest){

	$cmp_sign=md5(shn_acl_hmac_sha1($digest,$secret));

	if($sign==$cmp_sign){

		return true;
	}else{
		return false;
	}

}


function shn_authenticate_ws_user($user,$pwd,$extra_opts=null)
{
	global $global;
	$db=$global['db'];
	$sql="select secret,domain from ws_keys where api_key='{$user}' and password='{$pwd}'";
	$res=$db->Execute($sql);
	if(($res==null) or ($res->EOF)){
		return null;
	}else {
		return $res->fields["secret"];
	}
}