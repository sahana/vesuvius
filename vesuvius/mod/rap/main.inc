<?
/**
 * @name         Report a Person
 * @version      1.2
 * @package      rap
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0810
 */


require_once($global['approot']."/inc/lib_uuid.inc");


/**
 * Check Credz
 *
 * @access public
 * @return void
 */
function shn_rap_checkCredz() {
	$good = false;
	if(isset($_SESSION['logged_in']) && $_SESSION['logged_in'] == 1) {
		if(isset($_SESSION['group_id']) && $_SESSION['group_id'] != 3) { // not anonymous
			$good = true; // allowed to report
		}
	}
	return $good;
}



/**
 * Default function
 *
 * @access public
 * @return void
 */
function shn_rap_default() {
	if(shn_rap_checkClosed()) {
		shn_rap_showClosedMessage();
		return;
	}
	?>
	<h2>Before you begin...</h2>
	<ul>
		<li>Make sure the person you are reporting is not already in the system.</li>
		<li>Perform a <a href="index.php?mod=inw&act=default">search</a> to confirm you are not reporting someone that has already been reported.</li>
	</ul>
	<br>
	<br>
	<?php
	if(shn_rap_checkCredz()) {
		echo '<a href="index.php?mod=rap&act=controller"><span class="styleTehButton">Begin the process of Reporting a new Person</span></a>';
	} else {

		echo '<b>You must first login to add a person to the registry. If you do not yet have an account, <a href="index.php?mod=pref&amp;act=signup">please create one first.</a></b>';
	}
}



/**
 * Shows a messgage informing the user that the current event is closed.
 *
 * @access public
 * @return void
 */
function shn_rap_showClosedMessage() {
	global $global;
	$q = "
		SELECT *
		FROM incident
		WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."';
	";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$external_report = $row['external_report'];

	if(shn_rap_checkClosed() == 2) {
		echo htmlspecialchars_decode($external_report);
	} else {
		echo "
			<h2>Reporting Closed</h2>
			This event is closed and is no longer accepting new person reports.
		";
	}
}



/**
 * Event CLOSED Check
 *
 * @access public
 * @return void
 */
function shn_rap_checkClosed() {
	global $global;
	$q = "
		SELECT *
		FROM incident
		WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."';
	";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$closed = $row['closed'];
	return $closed;
}





/**
 * This is the RAP Controller
 * @access public
 * @return void
 */
function shn_rap_controller() {
	global $global;

	if(shn_rap_checkClosed() > 0) {
		shn_rap_showClosedMessage();
		return;
	}

	//Controller
	$case = isset($_REQUEST['seq']) ? $_REQUEST['seq'] : null;
	switch($case) {
		case 'entry' :
			if (shn_rap_validate()) {
				//clean the $_POST to remove the conflicts
				$_POST = null;
				shn_rap_uploadPic();
			} else {
				shn_rap_entry(true);
			}
		break;


		case 'uploadPic' :
			shn_rap_cropPic();
			break;

		case 'cropPic' :
			shn_rap_commitPicture();
			break;

		default :
			shn_rap_entry();
		break;
	}
}




/**
 * This is the Report a Person Form
 * @param mixed $errors
 * @access public
 * @return void
 */
function shn_rap_entry($errors=false) {
	global $global;
	global $conf;

	if(!shn_rap_checkCredz()) {
		echo '<b>You must first login to add a person to the registry. If you do not yet have an account, <a href="index.php?mod=pref&amp;act=signup">please create one first.</a><b>';
		return;
	}

	//echo "<h1>Reporting a New Person</h1>";

	if($errors) {
		display_errors();
	}

	shn_form_fopen("controller", null, array('enctype'=>'enctype="multipart/form-data"', 'req_message' => true));
		shn_form_hidden(array('seq'=>'entry'));

		shn_form_fsopen(_t('Information Privacy'));
			?><p><?php echo _t("<span class=\"publicText\">Public</span> Denotes information that, if provided, can be exposed to the general public.<br><br>".
			"<span class=\"privateText\">Private</span> Denotes information that will not be available to the public. <br><br>Private information may be made available to or shared with other family members and friends you designate, emergency responders, medical providers, clergy/councilors, law enforcement, or authorized displaced-person agencies."); ?></p><?php
		shn_form_fsclose();

		shn_form_fsopen(_t('Person\'s Status'));
			$q = "
				select *
				from field_options
				where field_name='opt_status';
			";
			$res = $global['db']->Execute($q);
			$opt_status = array();
			while (!$res->EOF) {
				$opt_status[$res->fields['option_code']] = $res->fields['option_description'];
				$res->MoveNext();
			}
			shn_form_select($opt_status, "Health / Locational Status", "opt_status", array('public'=>true, 'help'=>'Please specify to the best of your knowledge the condition of the person you are reporting.'),  array('value'=>'unk'));
		shn_form_fsclose();

		shn_form_fsopen(_t('Basic Person Details'));
			?><p><?php echo  _t('Please enter any of the following details of the person:'); ?></p>	<?php
			shn_form_text(_t('Given Name '),'given_name','size="30"',array('req'=>true, 'help'=>'The person\'s first name or the name by which (s)he is most frequently known.', 'public'=>true));
			shn_form_text(_t('Family Name'),'family_name','size="30"', array('help'=>_t('The person\'s surname or last name.'), 'public'=>true));
			shn_form_text(_t('Age'),'age','size="8"', array('help'=>_t('The exact age for the person or a best guess (can be combined with the age range below if an exact number is not known).'), 'public'=>true));
			shn_form_text(_t('Lower End of Age Range'),'age_lower','size="8"', array('help'=>_t('The lower limit for a person\'s age if an exact age is not known. (optional if exact age is known)'), 'public'=>true));
			shn_form_text(_t('Upper End of Age Range'),'age_upper','size="8"', array('help'=>_t('The upper limit for a person\'s age if an exact age is not known. (optional if exact age is known)'), 'public'=>true));
			shn_form_opt_select("opt_gender",_t('Gender'),null,array('sort'=>'display_order, option_description ASC', 'value'=>null, 'public'=>true));
			shn_form_opt_select("opt_religion",_t('Religion'), null,array('sort'=>'display_order, option_description ASC', 'value'=>null, 'private'=>true));
			shn_form_opt_select("opt_race",_t('Race'),null,array('sort'=>'display_order, option_description ASC', 'value'=>null, 'private'=>true, 'help'=>'The Race choices are those commonly used by the US Government.'));
		shn_form_fsclose();

		shn_form_fsopen(_t('Person\'s Contact Information'));
			shn_form_textarea(_t('Home Address'), "address", null, array('cols'=>48, 'help' => _t('Please specify the address of the person you are reporting.'), 'private'=>true));
			shn_form_text(_t('Home Zip Code'), 'zip', 'size="15"', array('private'=>true));
			shn_form_text(_t('Home Phone Number'), 'phone', 'size="15"', array('private'=>true));
			shn_form_text(_t('Mobile Phone Number'), 'mobile', 'size="15"', array('private'=>true));
			shn_form_text(_t('Email Address'), 'email', 'size="25"', array('private'=>true));
		shn_form_fsclose();

		shn_form_fsopen(_t('Person\'s Physical Details'));
			shn_form_opt_select("opt_eye_color",_t('Eye Color'),null, array('sort'=>'display_order, option_description ASC', 'value'=>null, 'public'=>true));
			shn_form_opt_select("opt_skin_color",_t('Skin Color'),null,array('sort'=>'display_order, option_description ASC', 'value'=>null, 'public'=>true, 'help'=>'The choices for Skin Color are those used by governmental agencies and law enforcement when reporting missing people.  These are frequently-used descriptive words, rather than precise colors.  Adjectives like “light” and “dark” may be considered in conjunction with the choices for “Race” and “Ethnicity” fields above.'));
			shn_form_opt_select("opt_hair_color",_t('Hair Color'),null,array('sort'=>'display_order, option_description ASC', 'value'=>null, 'public'=>true));

			shn_form_text(_t("Height"),'height','size="10"',array('public'=>true, 'help'=>'Use Metric or English system, include units.'));
			shn_form_text(_t('Weight'),'weight','size="10"',array('public'=>true, 'help'=>'Use Metric or English system, include units.'));

			shn_form_textarea(_t('Other Obvious Distinctive Features'),'physical', null, array('cols'=>48, 'public'=>true));
		shn_form_fsclose();

		shn_form_fsopen(_t('Last Known Details'), "missingDetails");
			shn_form_textarea(_t('Last Seen Location'),'last_seen', null, array('cols'=>48, 'public'=>true));
			shn_form_textarea(_t('Last Seen Clothing/Appearance'),'last_clothing', null, array('cols'=>48, 'public'=>true));
			shn_form_textarea(_t('Other Comments'),'comments', null, array('cols'=>48, 'public'=>true));
		shn_form_fsclose();

		shn_form_submit("Next", "class=\"styleTehButton\"");
	shn_form_fclose();
	echo "<br><br>";
}



/**
 * This is the Add Entry Validation function
 * @access public
 * @return void
 */
function shn_rap_validate() {
	global $global;
	global $conf;
	require_once($global['approot']."/inc/lib_validate.inc");

	$error_flag = false;

	//clean the post -- trim them all
	foreach($_POST as $k => $v) {
		$v = trim($v);
		if($v != '') {
			$local_post[$k] = $v;
		}
	}

	$_SESSION['rap']['entry'] = $local_post;
	if(!isset($_SESSION['rap']['entry']['p_uuid'])) {
		$_SESSION['rap']['entry']['p_uuid'] = shn_create_uuid();
	}

	// anything entered?
	if(empty($local_post)) {
		add_error(_t("Please fill out the form with as much information as possible about the person you are reporting."));
		return false;
	}

	// fullname entered?
	if(!isset($local_post['given_name'])) {
		add_error(_t("Please enter the Given Name of the person you are reporting."));
		$error_flag = true;
	}

	if($error_flag) {
		return false;
	} else {
		// set session
		return true;
	}
}




/**
 * This is the image upload form
 * @param mixed $errors
 * @access public
 * @return void
 */
function shn_rap_uploadPic($errors=false) {
	echo "<h1>Add a Photograph of the Person</h1>";

	if(!shn_rap_checkCredz()) {
		echo '<b>You must first login to add a person to the registry. If you do not yet have an account, <a href="index.php?mod=pref&amp;act=signup">please create one first.</a><b>';
		return;
	}

	if($errors) {
		display_errors();
	}

	?><br>If you have an image of the person you are reporting, click browse to add it to the registry. Otherwise, click next to continue.<br><br><br><?php

	shn_form_fopen("controller", null, array('enctype'=>'enctype="multipart/form-data"'));
		shn_form_hidden(array('seq'=>'uploadPic'));
		shn_form_fsopen("Upload Picture");
			shn_form_upload("Upload Picture", "picture");
		shn_form_fsclose();
		shn_form_submit("Next", "class=\"styleTehButton\"");
	shn_form_fclose();
}




function shn_rap_cropPic() {
	if(!shn_rap_checkCredz()) {
		echo '<b>You must first login to add a person to the registry. If you do not yet have an account, <a href="index.php?mod=pref&amp;act=signup">please create one first.</a><b>';
		return;
	}

	// No file was uploaded ignore
	if($_FILES['picture']['error'] != 0) {
		shn_form_hidden(array('seq'=>'cropPic'));
		shn_rap_commitPerson();

	} else {


		// Get the file information
		$userfile_name = $_FILES["picture"]["name"];
		$userfile_tmp  = $_FILES["picture"]["tmp_name"];
		$userfile_size = $_FILES["picture"]["size"];

		$info = getimagesize($_FILES['picture']['tmp_name']);
		//check the image type
		if (!$info) {
			add_error(_t("Invalid image type please try again"));
			$error = true;
		}

		$width  = $info[0];
		$height = $info[1];
		$mime   = $info['mime'];

		if($width > 500) {
			$ratio = 500 / $width;
			$useWidth = 500;
			$useHeight = $height * $ratio;
		} else {
			$ratio = 1.0;
			$useWidth = $width;
			$useHeight = $height;
		}

		$extR = explode("/", $info['mime']);
		$ext = $extR[1];
		$cwd = getcwd();

		$date = date("Ymd_His_");

		$filename             = basename($_FILES["picture"]["name"]);
		$filename             = str_replace(" ", "+", $filename);
		$file_ext             = substr($filename, strrpos($filename, ".") + 1);
		$large_image_location = $cwd."/tmp/rap_cache/".$date.$filename;
		$thumb_image_location = $cwd."/tmp/rap_cache/".$date."thumb_".$filename;
		$imgPath              =             "tmp/rap_cache/".$date.$filename;
		$thumbPath            =             "tmp/rap_cache/".$date."thumb_".$filename;
		$original_filename    = $filename;

		move_uploaded_file($userfile_tmp, $large_image_location);
		chmod ($large_image_location, 0777);

		require_once("../inc/lib_image.inc");
		shn_image_resize_height($imgPath, $thumbPath, 320);
		chmod ($thumbPath, 0777);

		?>
		<script type="text/javascript" src="res/js/jquery-1.4.4.min.js"></script>
		<script type="text/javascript" src="res/js/jquery.imgareaselect.pack.js"></script>

		<h1>Crop the Image</h1>
		<ul>
			<li>Click and drag to draw a box around the important part of the image.</li>
			<li>You may then resize the rectangular selection grid to refine your rectangular selection area.</li>
			<li>You may also drag to move the selection box around inside the image.</li>
			<li>A good selection is to highlight the area around the person's face so that it becomes more prominant in the thumbnail image.</li>
			<li>We will use this cropped portion of the image to generate a thumbnail image.</li>
		</ul>

		<?php
			shn_form_fopen("controller", null, array('enctype'=>'enctype="multipart/form-data"'));
				shn_form_hidden(array('seq'=>'cropPic'));
				shn_form_hidden(array('ratio'=>$ratio));
				shn_form_hidden(array('width'=>$width));
				shn_form_hidden(array('height'=>$height));
				shn_form_hidden(array('mime'=>$mime));
				shn_form_hidden(array('wwwPath'=>$imgPath));
				shn_form_hidden(array('thumbPath'=>$thumbPath));
				shn_form_hidden(array('original_filename'=>$original_filename));
				shn_form_hidden(array('realPath'=>$large_image_location));
				shn_form_fsopen(_t(''));
		?>
		<div style="display: block;">

			<p style="font-size: 110%; font-weight: bold; padding-left: 0.1em; margin: 0px 0px 0px 20px;">Original Image</p>
			<div style="float: left; padding: 10px; background-color: #fff; border: 1px solid #000; display:block; margin: 0px 20px 20px 20px;">
				<img src="<?php echo $imgPath; ?>" id="photo" width="<?php echo $useWidth; ?>">
			</div>

			<div style="float: left; width: 400px;">
				<p style="font-size: 110%; font-weight: bold; padding-left: 0.1em;">Thumbnail Preview</p>
				<div class="frame" style="margin: 0 1em; width: 200px; height: 150px;">
					<div id="preview" style="width: 200px; height: 150px; overflow: hidden; padding: 0px; background-color: #fff; border: 1px solid #000; display: block;">
						<img src="<?php echo $imgPath; ?>" style="width: 200px; height: 150px;">
					</div>
				</div>
				<table style="margin-top: 40px;">
					<thead>
						<tr>
							<th colspan="2" style="font-size: 110%; font-weight: bold; text-align: left; padding-left: 0.1em;">Coordinates</th>
							<th colspan="2" style="font-size: 110%; font-weight: bold; text-align: left; padding-left: 0.1em;">Dimensions</th>
						</tr>
					</thead>
					<tbody>
						<tr>
							<td style="width: 10%;">
								<b>X<sub>1</sub>:</b>
							</td>
							<td style="width: 30%;">
								<input type="text" name="x1" id="x1" value="10" readonly>
							</td>
							<td style="width: 20%;">
								<b>Width:</b>
							</td>
							<td>
								<input type="text" name="w"  id="w"  value="80" readonly>
							</td>
						</tr>
						<tr>
							<td>
								<b>Y<sub>1</sub>:</b>
							</td>
							<td>
								<input type="text" name="y1" id="y1" value="10" readonly>
							</td>
							<td>
								<b>Height:</b>
							</td>
							<td>
								<input type="text" name="h"  id="h"  value="60" readonly>
							</td>
						</tr>
						<tr>
							<td>
								<b>X<sub>2</sub>:</b>
							</td>
							<td>
								<input type="text" name="x2" id="x2" value="90" readonly>
							</td>
							<td>&nbsp;</td>
							<td>&nbsp;</td>
						</tr>
						<tr>
							<td><b>Y<sub>2</sub>:</b></td>
							<td>
								<input type="text" name="y2" id="y2" value="70" readonly>
							</td >
							<td></td>
							<td></td>
						</tr>
					</tbody>
				</table>
			</div>


			<script type="text/javascript">
				function preview(img, selection) {
					if (!selection.width || !selection.height)
						return;
					var scaleX = 200 / selection.width;
					var scaleY = 150 / selection.height;
					$('#preview img').css( {
						width: Math.round(scaleX * <?php echo $useWidth; ?>),
						height: Math.round(scaleY * <?php echo $useHeight; ?>),
						marginLeft: -Math.round(scaleX * selection.x1),
						marginTop: -Math.round(scaleY * selection.y1)
					});
					$('#x1').val(selection.x1);
					$('#y1').val(selection.y1);
					$('#x2').val(selection.x2);
					$('#y2').val(selection.y2);
					$('#w').val(selection.width);
					$('#h').val(selection.height);
				}

				$(function () {
					$('#photo').imgAreaSelect( {
						x1: 10, y1: 10, x2: 90, y2: 70,
						handles: true,
						fadeSpeed: 200,
						persistent: true,
						onInit: preview,
						onSelectChange: preview
					});
				});
				// aspectRatio: '4:3', ------REMOVED
			</script>
		</div>
		<div style="clear: both; height: 50px;"></div>

		<?php
		shn_form_fsclose();
		shn_form_submit("Finish and Save this Person", "class=\"styleTehButton\"");
		shn_form_fclose();
	}
}



function shn_rap_commitPicture() {
	shn_rap_commitPerson(true);
}




/**
 * This function commits the given Missing person's data to the databsae.
 * @access public
 * @return void
 */
function shn_rap_commitPerson($saveImage = false) {
	global $global;
	global $conf;

	if(!shn_rap_checkCredz()) {
		echo '<b>You must first login to add a person to the registry. If you do not yet have an account, <a href="index.php?mod=pref&amp;act=signup">please create one first.</a><b>';
		return;
	}

	include_once($global['approot'].'inc/lib_uuid.inc');

	// status has to be set.... ALWAYS
	isset($_SESSION['rap']['entry']['opt_status'])     ? $status      = "'".mysql_real_escape_string($_SESSION['rap']['entry']['opt_status'])."'"     : $status      = "'unk'";

	// set defaults for all rest to null

	// except given name which is always present
	$given_name = "'".mysql_real_escape_string($_SESSION['rap']['entry']['given_name'])."'";
	isset($_SESSION['rap']['entry']['family_name'])    ? $family_name = "'".mysql_real_escape_string($_SESSION['rap']['entry']['family_name'])."'"    : $family_name = "NULL";

	$full_part = isset($_SESSION['rap']['entry']['family_name']) ? " ".$_SESSION['rap']['entry']['family_name'] : "";
	$full_name = "'".mysql_real_escape_string($_SESSION['rap']['entry']['given_name'].$full_part)."'";

	isset($_SESSION['rap']['entry']['opt_gender'])     ? $gender      = "'".mysql_real_escape_string($_SESSION['rap']['entry']['opt_gender'])."'"     : $gender      = "NULL";
	isset($_SESSION['rap']['entry']['age'])            ? $age         = "'".mysql_real_escape_string($_SESSION['rap']['entry']['age'])."'"            : $age         = "NULL";
	isset($_SESSION['rap']['entry']['age_lower'])      ? $minAge      = "'".mysql_real_escape_string($_SESSION['rap']['entry']['age_lower'])."'"      : $minAge      = "NULL";
	isset($_SESSION['rap']['entry']['age_upper'])      ? $maxAge      = "'".mysql_real_escape_string($_SESSION['rap']['entry']['age_upper'])."'"      : $maxAge      = "NULL";
	isset($_SESSION['rap']['entry']['opt_religion'])   ? $religion    = "'".mysql_real_escape_string($_SESSION['rap']['entry']['opt_religion'])."'"   : $religion    = "NULL";
	isset($_SESSION['rap']['entry']['opt_race'])       ? $race        = "'".mysql_real_escape_string($_SESSION['rap']['entry']['opt_race'])."'"       : $race        = "NULL";

	isset($_SESSION['rap']['entry']['address'])        ? $address     = "'".mysql_real_escape_string($_SESSION['rap']['entry']['address'])."'"        : $address     = "NULL";
	isset($_SESSION['rap']['entry']['zip'])            ? $zip         = "'".mysql_real_escape_string($_SESSION['rap']['entry']['zip'])."'"            : $zip         = "NULL";
	isset($_SESSION['rap']['entry']['phone'])          ? $phone       = "'".mysql_real_escape_string($_SESSION['rap']['entry']['phone'])."'"          : $phone       = "NULL";
	isset($_SESSION['rap']['entry']['mobile'])         ? $mobile      = "'".mysql_real_escape_string($_SESSION['rap']['entry']['mobile'])."'"         : $mobile      = "NULL";
	isset($_SESSION['rap']['entry']['email'])          ? $email       = "'".mysql_real_escape_string($_SESSION['rap']['entry']['email'])."'"          : $email       = "NULL";

	isset($_SESSION['rap']['entry']['opt_eye_color'])  ? $eye         = "'".mysql_real_escape_string($_SESSION['rap']['entry']['opt_eye_color'])."'"  : $eye         = "NULL";
	isset($_SESSION['rap']['entry']['opt_skin_color']) ? $skin        = "'".mysql_real_escape_string($_SESSION['rap']['entry']['opt_skin_color'])."'" : $skin        = "NULL";
	isset($_SESSION['rap']['entry']['opt_hair_color']) ? $hair        = "'".mysql_real_escape_string($_SESSION['rap']['entry']['opt_hair_color'])."'" : $hair        = "NULL";
	isset($_SESSION['rap']['entry']['height'])         ? $height      = "'".mysql_real_escape_string($_SESSION['rap']['entry']['height'])."'"         : $height      = "NULL";
	isset($_SESSION['rap']['entry']['weight'])         ? $weight      = "'".mysql_real_escape_string($_SESSION['rap']['entry']['weight'])."'"         : $weight      = "NULL";
	isset($_SESSION['rap']['entry']['physical'])       ? $physical    = "'".mysql_real_escape_string($_SESSION['rap']['entry']['physical'])."'"       : $physical    = "NULL";
	isset($_SESSION['rap']['entry']['last_seen'])      ? $seen        = "'".mysql_real_escape_string($_SESSION['rap']['entry']['last_seen'])."'"      : $seen        = "NULL";
	isset($_SESSION['rap']['entry']['last_clothing'])  ? $clothing    = "'".mysql_real_escape_string($_SESSION['rap']['entry']['last_clothing'])."'"  : $clothing    = "NULL";
	isset($_SESSION['rap']['entry']['comments'])       ? $comments    = "'".mysql_real_escape_string($_SESSION['rap']['entry']['comments'])."'"       : $comments    = "NULL";

	// NULL values that come in as "select"
	if($race     == "'select'") { $race     = "NULL"; }
	if($religion == "'select'") { $religion = "NULL"; }
	if($gender   == "'select'") { $gender   = "NULL"; }
	if($hair     == "'select'") { $hair     = "NULL"; }
	if($eye      == "'select'") { $eye      = "NULL"; }
	if($skin     == "'select'") { $skin     = "NULL"; }

	// NULL Values that come in as u or unk
	if($race     == "'U'")   { $race     = "NULL"; }
	if($religion == "'UNK'") { $religion = "NULL"; }
	if($gender   == "'unk'") { $gender   = "NULL"; }
	if($eye      == "'UNK'") { $eye      = "NULL"; }
	if($skin     == "'UNK'") { $skin     = "NULL"; }
	if($hair     == "'UNK'") { $hair     = "NULL"; }

	$q0  = "
		SELECT *
		FROM incident
		WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."';
	";
	$r0  = $global['db']->Execute($q0);
	$row = $r0->FetchRow();
	$id = $row['incident_id'];

	$uuid = $_SESSION['rap']['entry']['p_uuid'];

	// insert person
	$q1 = "
		INSERT INTO person_uuid (p_uuid, full_name, family_name, given_name, incident_id, hospital_uuid)
		VALUES (
			'".$uuid."',
			".$full_name.",
			".$family_name.",
			".$given_name.",
			'".$id."',
			NULL
		);
	";
	$res = $global['db']->Execute($q1);


	// insert person's status
	$q5 = "
		INSERT INTO person_status (p_uuid, opt_status, last_updated, creation_time)
		VALUES ( '".$uuid."', ".$status.", CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);
	";
	$res = $global['db']->Execute($q5);



	// insert into rap_log
	$q7 = "
		INSERT INTO rap_log (p_uuid)
		VALUES ('".$uuid."');
	";
	$res = $global['db']->Execute($q7);


	// insert person's details
	$q8 = "
		INSERT INTO person_details (p_uuid, opt_race, opt_religion, opt_gender, years_old, minAge, maxAge, last_seen, last_clothing, other_comments)
		VALUES ('".$uuid."', ".$race.", ".$religion.", ".$gender.", ".$age.", ".$minAge.", ".$maxAge.", ".$seen.", ".$clothing.", ".$comments.");
	";
	$res = $global['db']->Execute($q8);


	// insert person
	$q11 = "
		INSERT INTO person_to_report (p_uuid, rep_uuid)
		VALUES ('".$uuid."','".$_SESSION['user_p_uuid']."');
	";
	$res = $global['db']->Execute($q11);


	// insert personal physical
	$q12 = "
		INSERT INTO person_physical (p_uuid, height, weight, opt_eye_color, opt_skin_color, opt_hair_color, comments)
		VALUES ('".$uuid."', ".$height.", ".$weight.", ".$eye.", ".$skin.", ".$hair.", ".$physical.");";
	$res = $global['db']->Execute($q12);


	// insert phone
	$q13 = "
		INSERT INTO contact (p_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'curr', ".$phone.");";
	$res = $global['db']->Execute($q13);


	// insert phone mobile
	$q14 = "
		INSERT INTO contact (p_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'cmob', ".$mobile.");";
	$res = $global['db']->Execute($q14);


	// insert address
	$q15 = "
		INSERT INTO contact (p_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'home', ".$address.");";
	$res = $global['db']->Execute($q15);


	// insert zip
	$q16 = "
		INSERT INTO contact (p_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'zip', ".$zip.");";
	$res = $global['db']->Execute($q16);


	// insert email
	$q17 = "
		INSERT INTO contact (p_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'email', ".$phone.");";
	$res = $global['db']->Execute($q17);


	// save an image if we have one
	if($saveImage) {

		$image_type   = mysql_real_escape_string($_REQUEST['mime']);
		$image_height = mysql_real_escape_string($_REQUEST['height']);
		$image_width  = mysql_real_escape_string($_REQUEST['width']);
		$url          = mysql_real_escape_string($_REQUEST['wwwPath']);
		$url_thumb    = mysql_real_escape_string($_REQUEST['thumbPath']);
		$original_filename = mysql_real_escape_string($_REQUEST['original_filename']);

		$ratio = $_REQUEST['ratio'];
		$x1    = $_REQUEST['x1'];
		$y1    = $_REQUEST['y1'];
		$w     = $_REQUEST['w'];
		$h     = $_REQUEST['h'];

		$tag_x = $x1 / $ratio;
		$tag_y = $y1 / $ratio;
		$tag_w = $w  / $ratio;
		$tag_h = $h  / $ratio;


		$q18 = "
			INSERT INTO image (p_uuid, image_type, image_height, image_width, url, url_thumb, original_filename)
			VALUES ('".$uuid."', '".$image_type."', '".$image_height."', '".$image_width."', '".$url."', '".$url_thumb."', '".$original_filename."');
		";
		$res = $global['db']->Execute($q18);

		// get the id of the last inserted item
		$q19 = "
			select *
			from image
			order by image_id DESC limit 1;
		";
		$res = $global['db']->Execute($q19);
		$image_id = $res->fields['image_id'];

		$q20 = "
			INSERT INTO image_tag (image_id, tag_x, tag_y, tag_w, tag_h, tag_text)
			VALUES ('".$image_id."', '".$tag_x."', '".$tag_y."', '".$tag_w."', '".$tag_h."', '".$tag_text."');
		";
		$res = $global['db']->Execute($q20);
	}


/*
echo "Q1>> ".$q1."<br>";
echo "Q5>> ".$q5."<br>";
echo "Q7>> ".$q7."<br>";
echo "Q8>> ".$q8."<br>";
echo "Q11>> ".$q11."<br>";
echo "Q12>> ".$q12."<br>";
echo "Q13>> ".$q13."<br>";
echo "Q14>> ".$q14."<br>";
echo "Q15>> ".$q15."<br>";
echo "Q16>> ".$q16."<br>";
echo "Q17>> ".$q17."<br>";
*/

/*

Array
(
    [shortname] => cmax2009
    [mod] => rap
    [act] => controller
    [seq] => cropPic
    [ratio] => 0.533049040512
    [width] => 938
    [height] => 778
    [mime] => image/png
    [wwwPath] => tmp/rap_cache/20100910_033148_rent2.png
    [thumbPath] => tmp/rap_cache/20100910_033148_thumb_rent2.png
    [realPath] => /home/gmiernicki/public_html/sahanaDev/www/tmp/rap_cache/20100910_033148_rent2.png
    [x1] => 10
    [w] => 80
    [y1] => 10
    [h] => 60
    [x2] => 90
    [y2] => 70
    [PHPSESSID] => eae03304bf43364655ab53aa6d205de0

*/

	add_confirmation("You have successfully registered <b>".$full_name."</b> into the registry.");
	add_confirmation("You can follow this link: <b><a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($uuid)."\">".$uuid."</a></b> to make changes to the person's record or use the tools available there to share this information with others.");
	add_confirmation("If you come back to the site at a later time, you can find this person again by visiting the <a href=\"index.php?mod=pref&act=tracking\"><b>My People</b></a> link above.");

	global $conf;
	if($conf['enable_solr_for_search'] == true) {
		add_confirmation("It may take up to 5 minutes before the person you just reported shows up in our search results.");
	}
}



