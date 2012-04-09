<?php
/**
 * @name         LPF Library
 * @version      28
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0126
 */



// Enumerated Types...
global $global;
$global['enumTriageStatusTags']  = array('Green', 'BH Green', 'Yellow', 'Red', 'Gray', 'Black');
$global['enumGenders']           = array('M', 'F', 'U', 'C');
$global['enumDistrStatus']       = array('Actual', 'Exercise', 'System', 'Test');
$global['enumDistrType']         = array('Ack', 'Cancel', 'Dispatch', 'Error', 'Report', 'Request', 'Response', 'Update');
$global['enumXmlFormats']        = array('REUNITE2', 'REUNITE3', 'REUNITE4', 'TRIAGEPIC0', 'TRIAGEPIC1');

// whether to save the xml attachments for debug purposes
$global['debugAndSaveXmlToFile'] = true;
$global['debugAndSaveXmlToFilePath'] = $global['approot']."www/tmp/debug_cache/";

// load uuid library for generating id's
require_once($global['approot']."/inc/lib_uuid.inc");

// load classes...
require_once($global['approot']."/mod/lpf/class.person.php");
require_once($global['approot']."/mod/lpf/class.personEdxl.php");
require_once($global['approot']."/mod/lpf/class.personImage.php");
require_once($global['approot']."/mod/lpf/class.personImageTag.php");
require_once($global['approot']."/mod/lpf/class.voiceNote.php");
require_once($global['approot']."/mod/lpf/class.XMLParser.php");
require_once($global['approot']."/mod/lpf/class.pop.php");
require_once($global['approot']."/mod/lpf/class.nameParser.php");
require_once($global['approot']."/mod/lpf/class.googleGeocoder.php");
require_once($global['approot']."/mod/lpf/class.googl.php");
require_once($global['approot']."/mod/lpf/class.arr2xml.php");
require_once($global['approot']."/mod/lpf/lib_helper.inc");
