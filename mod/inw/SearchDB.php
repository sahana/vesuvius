<?php

class SearchDB {

	public
		$incident,
		$searchTerm,
		$searchMode,
		$pageStart,
		$perPage,
		$sortBy,
		$mode,
		$statusString,
		$missing,
		$alive,
		$injured,
		$deceased,
		$unknown,
		$found,
		$genderString,
		$male,
		$female,
		$complex,
		$genderUnk,
		$ageString,
		$child,
		$adult,
		$ageUnk,
		$hospitalString,
		$suburban,
		$nnmc,
		$otherHosp,
		$results,
		$numRowsFound,
		$allCount,
		$lastUpdated,
		$SOLRqueryTime,
		$SOLRfacetResults,
		$SOLRjson;

	private
		$whereClause,
		$whereClausePrecise,
		$whereClauseBroad,
		$whereClauseSoundex,
		$SOLRfq,
		$fromClause,
		$SOLRroot,
		$SOLRport,
		$SOLRquery,
		$searchImage,
		$searchUnknown,
		$db,
		$conf;


	/**
	 *  Constructor
	 *
	 * Params:
	 * $searchMode = "solr" or "sql"
	 * $sStatus = "missing;alive;injured;deceased;unknown;found"
	 * $sPageControls = "pageStart;perPage;sortBy;mode"
	 * $sGender = gender imploded
	 * $sAge = age imploded
	 *
	 */
	public function SearchDB($searchMode, $incident, $searchTerm, $sStatus = "true;true;true;true;true;true", $sGender="true;true;true;true", $sAge="true;true;true", $sHospital="true;true;true", $sPageControls="0;-1;;true") {

		global $conf;
		$this->incident = $incident;

		// Look for hidden search string for filtering on images (PL-261).
                $this->searchImage = "";

		if (strpos($searchTerm, "[image]") !== false) {
			$this->searchImage = "only";

                } else if (strpos($searchTerm, "[-image]") !== false) {
			$this->searchImage = "none";
		}

		// Search string "unknown" means return records with no names (PL-225).
                $this->searchUnknown = (strpos($searchTerm, "unknown") !== false)? true : false;

		// Removed a number of symbols to allow power users to exploit SOLR syntax (PL-265).
		$toReplace = array(",", ".", "/", "\\", "@", "$", "%", "^", "&", "#", "[image]", "[-image]", "unknown");
		$this->searchTerm = strtolower(str_replace($toReplace, "", $searchTerm));
		$this->setStatusFilters($sStatus);
		$this->setPageControls($sPageControls);
		$this->setGenderFilters($sGender);
		$this->setAgeFilters($sAge);
		$this->setHospitalFilters($sHospital);
		$this->numRowsFound = -1;
		$this->searchMode = $searchMode;

		if (strpos($this->sortBy, "full_name") !== false) {
			// Sort on last name first, first name last (PL-237).
			$this->sortBy = str_replace("full_name", "family_name", $this->sortBy) . ",given_name asc";
		}

		// Accommodate age ranges in sort (PL-260).
		$this->sortBy = ($searchMode == "solr") ?
			str_replace("years_old", "max(max(years_old,0),div(sum(max(minAge,0),max(maxAge,0)),2))", $this->sortBy) :
			str_replace("years_old", "greatest(coalesce(years_old,0), (coalesce(minAge,0)+coalesce(maxAge,0))/2)", $this->sortBy);

		if ( $searchMode == "sql" ) {

			// make sql mode sort by updated as default.
			if ( $this->sortBy == "" ) {
				$this->sortBy = "updated desc";
			}

			$this->buildFromClause();
			$this->buildWhereClause();
			$this->buildMainQuery();

		} else if ( $searchMode == "solr" ) {

			$this->SOLRroot = $conf["SOLR_root"];
			$this->SOLRport = $conf["SOLR_port"];
			$this->buildSOLRFilters();
			$this->buildSOLRQuery();
		}
	}


	private function setStatusFilters($sStatus) {

		$tempArray = explode(";", $sStatus);
		$this->missing   = $tempArray[0];
		$this->alive     = $tempArray[1];
		$this->injured   = $tempArray[2];
		$this->deceased  = $tempArray[3];
		$this->unknown   = $tempArray[4];
		$this->found     = $tempArray[5];
	}


	private function setPageControls($sPageControls) {

		$tempArray = explode(";", $sPageControls);
		$this->pageStart = $tempArray[0];
		$this->perPage   = $tempArray[1];
		$this->sortBy    = $tempArray[2];
		$this->mode      = $tempArray[3];  // false = handsfree
	}


	private function setGenderFilters($sGender) {

		$tempArray = explode(";", $sGender);
		$this->complex   = $tempArray[0];
		$this->male      = $tempArray[1];
		$this->female    = $tempArray[2];
		$this->genderUnk = $tempArray[3];
	}


	private function setAgeFilters($sAge) {

		$tempArray = explode(";", $sAge);
		$this->child     = $tempArray[0];
		$this->adult     = $tempArray[1];
		$this->ageUnk    = $tempArray[2];
	}


	private function setHospitalFilters($sHospital) {

		$tempArray = explode(";", $sHospital);
		$this->suburban  = $tempArray[0];
		$this->nnmc      = $tempArray[1];
		$this->otherHosp = $tempArray[2];
	}


	private function initDBConnection() {

		global $global;
		$this->db = $global["db"];
	}


	private function buildWhereClause() {
		$this->buildFiltersClause();
	}


	private function buildFiltersClause() {

		$this->statusString = "";

		if ($this->missing == "true")   $this->statusString .= "mis;";
		if ($this->alive == "true")     $this->statusString .= "ali;";
		if ($this->injured == "true")   $this->statusString .= "inj;";
		if ($this->deceased == "true")  $this->statusString .= "dec;";
		if ($this->unknown == "true")   $this->statusString .= "unk;";
		if ($this->found == "true")     $this->statusString .= "fnd;";

		$this->genderString = "";

		if ($this->male == "true")      $this->genderString .= "mal;";
		if ($this->female == "true")    $this->genderString .= "fml;";
		if ($this->complex == "true")   $this->genderString .= "cpx;";
		if ($this->genderUnk == "true") $this->genderString .= "unk;";

		$this->ageString = "";

		if ($this->child == "true")     $this->ageString .= "youth;";
		if ($this->adult == "true")     $this->ageString .= "adult;";
		if ($this->adult == "true" ||   $this->child == "true") $this->ageString .= "both;";
		if ($this->ageUnk == "true")    $this->ageString .= "unknown;";

		$this->hospitalString = "";

		if ( $this->suburban == "true" )  $this->hospitalString .= "suburban;";
		if ( $this->nnmc == "true" )      $this->hospitalString .= "wrnmmc;";
		if ( $this->otherHosp == "true" ) $this->hospitalString .= "other;";
	}


	private function buildMainQuery() {
		$this->mainQ = "SELECT * " . $this->fromClause . " WHERE ";
	}


	// kinda redudant now because of the view, but this might change later.
	private function buildFromClause() {
		$this->fromClause =  "FROM person_search";
	}


	private function getTotalResults() {

		$qTA = "SELECT count(*)	" . $this->fromClause . " WHERE shortname = '" . $this->incident . "'";
		$result = $this->db->Execute($qTA);
		while (!$result == NULL && !$result->EOF) {
			$this->allCount = $result->fields[0];
			mysql_free_result($result);
			break;
		}
	}


	public function executeSearch() {

		if ( $this->searchMode == "solr" )   $this->executeSOLRQuery();
		elseif ( $this->searchMode == "sql") $this->executeSQLQuery();
	}


	private function executeSQLQuery() {

		global $conf;
		global $global;

		$mysqli = new mysqli( $conf["db_host"], $conf["db_user"], $conf["db_pass"], $conf["db_name"], $conf["db_port"] );

		if ( $this->mode != "true" || $this->perPage == "-1") {
			$this->pageStart = 0;
			$this->perPage = 2000;
		}

                // Set "unknown" flag for SQL search (PL-225).
                if ($this->searchUnknown) $this->searchTerm = 'unknown';

		$proc = "CALL PLSearch('$this->searchTerm', '$this->statusString', '$this->genderString', '$this->ageString', '$this->hospitalString', '$this->incident', '$this->sortBy', $this->pageStart, $this->perPage)";

		$res = $mysqli->multi_query( "$proc; SELECT @allCount;" );

		$this->numRowsFound = 0;
		$maxDate = new DateTime('0001-01-01 01:01:01');   // initialize to some old date
		if($res) {
			$results = 0;
			$c = 0;
			do {
				if($result = $mysqli->store_result()) {
					if($c == 0) {
						while($row = $result->fetch_assoc()) {

							require_once($global['approot']."/mod/lpf/lib_helper.inc");
							$encodedUUID = makePersonUrl($row["p_uuid"]);
							$this->results[] = array(
								'p_uuid'             => $row["p_uuid"],
								'encodedUUID'        => $encodedUUID,
								'full_name'          => htmlspecialchars($row["full_name"]),
								'given_name'         => htmlspecialchars($row["given_name"]),
								'family_name'        => htmlspecialchars($row["family_name"]),
								'opt_status'         => str_replace("\"", "", $row["opt_status"]),
								'imageUrl'           => htmlspecialchars($row["url_thumb"]),
								'imageWidth'         => $row["image_width"],
								'imageHeight'        => $row["image_height"],
								'years_old'          => $row["years_old"],
								'minAge'             => $row["minAge"],
								'maxAge'             => $row["maxAge"],
								'statusSahanaUpdated'=> $row["updated"],
								'last_seen'          => htmlspecialchars($row["last_seen"]),
								'comments'           => htmlspecialchars(strip_tags($row["comments"])),
								'gender'             => $row["opt_gender"],
								'hospitalIcon'       => $row["icon_url"],
								'mass_casualty_id'   => $row["mass_casualty_id"]
							);
		        				$date = new DateTime($row["updated"]);
							if ($date > $maxDate) {
                         					$maxDate = $date;
							}
							$this->numRowsFound++;
						}
					}
					$result->close();
					if($mysqli->more_results()) {
						$c += 1;
					}
				}
			} while($mysqli->more_results() && $mysqli->next_result());
		}
		$mysqli->close();
		$this->lastUpdated = $maxDate->format('Y-m-d H:i:s');
	}


	public function getSQLAllCount() {

		$qRC = "SELECT COUNT(p.p_uuid) FROM person_uuid p JOIN incident i ON p.incident_id = i.incident_id WHERE i.shortname = '$this->incident' ;";
		$result = $this->db->Execute($qRC);
		while(!$result == NULL && !$result->EOF) {
			$this->allCount = $result->fields[0];
			mysql_free_result($result);
			break;
		}
	}


	public function getLastUpdate() {

		if($this->searchMode == "solr") {
			$this->getLastUpdateSOLR();

		} elseif($this->searchMode == "sql") {
			$this->getLastUpdateSQL();
		}
	}


	// TODO: need to test for no connection found?
	public function getLastUpdateSOLR() {

		global $conf;
		$solrQuery = $this->SOLRquery . "&sort=updated desc&rows=1";
		$solrQuery = str_replace(" ", "%20", $solrQuery);
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $solrQuery . "&wt=json");
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_VERBOSE, 1);
		curl_setopt($ch, CURLOPT_PORT, $this->SOLRport);

		$temp = json_decode(curl_exec($ch));
		curl_close($ch);

  		if ($temp->response->numFound == 0) {
			$this->lastUpdated = '0001-01-01 01:01:01';
                } else {
			$date = new DateTime($temp->response->docs[0]->updated);
			$this->lastUpdated = $date->format("Y-m-d H:i:s");
		}
	}


	private function getLastUpdateSQL() {
		global $conf;

		$mysqli = new mysqli( $conf["db_host"], $conf["db_user"], $conf["db_pass"], $conf["db_name"], $conf["db_port"] );

		$this->pageStart = 0;
		$this->perPage = 1;

		$proc = "CALL PLSearch('$this->searchTerm', '$this->statusString', '$this->genderString', '$this->ageString', '$this->hospitalString', '$this->incident', '$this->sortBy', $this->pageStart, $this->perPage)";

		$res = $mysqli->multi_query( "$proc; SELECT @allCount;" );

                $this->lastUpdated = '0001-01-01 01:01:01';
		if($res) {
			$results = 0;
			$c = 0;
			do {
				if($result = $mysqli->store_result()) {
					if($c == 0) {
						while ($row = $result->fetch_assoc()) {
							$this->lastUpdated = $row["updated"];
						}
					}
					$result->close();
					if($mysqli->more_results()) {
						$c += 1;
					}
				}
			} while($mysqli->more_results() && $mysqli->next_result());
		}
		$mysqli->close();

		$date = new DateTime($this->lastUpdated);
		$this->lastUpdated = $date->format('Y-m-d H:i:s');
	}


	public function executeSOLRQuery() {

		$this->getSOLRallCount();  // there has to be a way to include this in the 1 query, still looking
		$this->getSOLRFacetCount(); // (PL-234) any way to avoid doing a separate query?

		if($this->mode == "true" && $this->perPage != "-1") {
			$this->SOLRquery .= "&start=" . $this->pageStart . "&rows=" . $this->perPage;
		} else {
			$this->SOLRquery .= "&rows=2000"; // max number of rows returned is 2000
		}

		if($this->sortBy != "") {
			$this->SOLRquery .= "&sort=" . $this->sortBy . ",score desc";
		}

		$this->SOLRquery = str_replace(" ", "%20", $this->SOLRquery);

		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $this->SOLRquery . "&wt=json"); // ensure the json version is called
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_VERBOSE, 1);
		curl_setopt($ch, CURLOPT_PORT, $this->SOLRport);

		$this->SOLRjson = curl_exec($ch);
		curl_close($ch);

		$this->processSOLRjson();
	}


	// ugly but we'd like to have clean json responses.
	private function cleanUpFacets() {

		$temp["child"]         = $this->SOLRfacetResults->{"ageGroup:youth"} + $this->SOLRfacetResults->{"ageGroup:both"};
		$temp["adult"]         = $this->SOLRfacetResults->{"ageGroup:adult"} + $this->SOLRfacetResults->{"ageGroup:both"};
		$temp["otherAge"]      = $this->SOLRfacetResults->{"ageGroup:unknown"};

		$temp["missing"]       = $this->SOLRfacetResults->{"opt_status:mis"};
		$temp["alive"]         = $this->SOLRfacetResults->{"opt_status:ali"};
		$temp["injured"]       = $this->SOLRfacetResults->{"opt_status:inj"};
		$temp["deceased"]      = $this->SOLRfacetResults->{"opt_status:dec"};
		$temp["unknown"]       = $this->SOLRfacetResults->{"opt_status:unk"};
		$temp["found"]         = $this->SOLRfacetResults->{"opt_status:fnd"};

		$temp["male"]          = $this->SOLRfacetResults->{"opt_gender:mal"};
		$temp["female"]        = $this->SOLRfacetResults->{"opt_gender:fml"};
		$temp["complex"]       = $this->SOLRfacetResults->{"opt_gender:cpx"};
		$temp["otherGender"]   = $this->SOLRfacetResults->{"opt_gender:unk"};

		$temp["suburban"]      = $this->SOLRfacetResults->{"hospital:suburban"};
		$temp["nnmc"]          = $this->SOLRfacetResults->{"hospital:wrnmmc"};
		$temp["otherHospital"] = $this->SOLRfacetResults->{"hospital:public"};

		$this->SOLRfacetResults = $temp;
	}


	private function processSOLRjson() {

		global $conf;

		$tempObject = json_decode($this->SOLRjson);

		// set rows found
		$this->numRowsFound = $tempObject->response->numFound;

		// get query time
		$this->SOLRqueryTime = $tempObject->responseHeader->QTime;

		$maxDate = new DateTime('0001-01-01 01:01:01');   // initialize to some old date
		foreach ($tempObject->response->docs as $doc) {
                        // Don't camelcase full_name (PL-273).
			$this->results[] = array(
				'p_uuid' => $doc->p_uuid,
				'encodedUUID'         => $conf['https'].$conf['base_uuid']."edit?puuid=".urlencode($doc->p_uuid),
				'full_name'           => isset($doc->full_name)        ? htmlspecialchars($doc->full_name) : null,
				'given_name'          => isset($doc->given_name)       ? htmlspecialchars($doc->given_name) : null,
				'family_name'         => isset($doc->family_name)      ? htmlspecialchars($doc->family_name) : null,
				'opt_status'          => isset($doc->opt_status)       ? $doc->opt_status : null,
				'imageUrl'            => isset($doc->url_thumb)        ? $doc->url_thumb : null,
				'imageWidth'          => isset($doc->image_width)      ? $doc->image_width : null,
				'imageHeight'         => isset($doc->image_height)     ? $doc->image_height : null,
				'years_old'           => isset($doc->years_old)        ? $doc->years_old : null,
				'minAge'              => isset($doc->minAge)           ? $doc->minAge : null,
				'maxAge'              => isset($doc->maxAge)           ? $doc->maxAge : null,
				'id'                  => isset($doc->personId)         ? $doc->personId : null,
				'statusSahanaUpdated' => isset($doc->updated)          ? str_replace('Z', '', $doc->updated) : null,
				'statusTriage'        => isset($doc->triageCategory)   ? $doc->triageCategory : null,
				'peds'                => isset($doc->peds)             ? $doc->peds : null,
				'orgName'             => isset($doc->orgName)          ? $doc->orgName : null,
				'last_seen'           => isset($doc->last_seen)        ? htmlspecialchars($doc->last_seen) : null,
				'comments'            => isset($doc->comments)         ? strip_tags(htmlspecialchars($doc->comments)) : null,
				'gender'              => isset($doc->opt_gender)       ? $doc->opt_gender : null,
				'hospitalIcon'        => isset($doc->icon_url)         ? $doc->icon_url : null,
				'mass_casualty_id'    => isset($doc->mass_casualty_id) ? $doc->mass_casualty_id : null
			);
		        $date = new DateTime($doc->updated);
			if ($date > $maxDate) {
                         	$maxDate = $date;
                        } 
		}
		$this->lastUpdated = $maxDate->format('Y-m-d H:i:s');
	}

	private function buildSOLRQuery() {

		$this->searchTerm = $this->searchTerm == "" ? "*:*" : $this->fuzzify($this->searchTerm);
		$this->SOLRquery =  $this->SOLRroot."select/?fl=*,score&qt=edismax&q=+".trim(urlencode($this->searchTerm)).$this->SOLRfq;
	}


	private function buildSOLRFilters() {

		// opt_status filters
		$this->SOLRfq = "&fq=opt_status:(*:*";

		if($this->missing != "true")  $this->SOLRfq .= " -mis";
		if($this->alive != "true")    $this->SOLRfq .= " -ali";
		if($this->injured != "true")  $this->SOLRfq .= " -inj";
		if($this->deceased != "true") $this->SOLRfq .= " -dec";
		if($this->unknown != "true")  $this->SOLRfq .= " -unk";
		if($this->found != "true")    $this->SOLRfq .= " -fnd";

		// opt_gender filters
		$this->SOLRfq .= ")&fq=opt_gender:(*:*";

		if($this->male != "true")      $this->SOLRfq .= " -mal";
		if($this->female != "true")    $this->SOLRfq .= " -fml";
		if($this->complex != "true")   $this->SOLRfq .= " -cpx";
		if($this->genderUnk != "true") $this->SOLRfq .= " -unk";

		// years_old filters
		$this->SOLRfq .= ")&fq=ageGroup:(*:*";

		if($this->child != "true")  $this->SOLRfq .= " -youth ";
		if($this->adult != "true")  $this->SOLRfq .= " -adult ";
		if($this->child != "true" && $this->adult != "true") $this->SOLRfq .= " -both ";
		if($this->ageUnk != "true") $this->SOLRfq .= " -unknown";

		// hospital filters
		$this->SOLRfq .= ")&fq=hospital:(*:*";

		if($this->suburban != "true")  $this->SOLRfq .= " -suburban ";
		if($this->nnmc != "true")      $this->SOLRfq .= " -wrnmmc ";
		if($this->otherHosp != "true") $this->SOLRfq .= " -public";

		//incident shortname filter (always applied)
		$this->SOLRfq .= ")&fq=shortname:" . $this->incident;

		//only non-expired records (always applied) (PL-288)
		$this->SOLRfq .= "&fq=-expiry_date:[* TO NOW]";

		// NULL full_name filter if searching for "unknown"
		if ($this->searchUnknown) {
			$this->SOLRfq .= "&fq=-full_name:[* TO *]";
		}

		// Filter only records with or without images?
                if ($this->searchImage === "only") {
			$this->SOLRfq .= "&fq=url_thumb:[* TO *]";

		} else if ($this->searchImage === "none") {
			$this->SOLRfq .= "&fq=-url_thumb:[* TO *]";
		}
	}


	private function getSOLRallCount() {

		$tmpSOLRquery = $this->SOLRroot . "select/?rows=0&q=*:*&fq=shortname:".$this->incident."&fq=-expiry_date:[*%20TO%20NOW]";
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $tmpSOLRquery . "&wt=json"); // ensure the json version is called
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_VERBOSE, 1);
		curl_setopt($ch, CURLOPT_PORT, $this->SOLRport);

		$tempSOLRjson = json_decode(curl_exec($ch));
		curl_close($ch);

		$this->allCount = $tempSOLRjson->response->numFound;
	}


	private function getSOLRFacetCount() {

		$solrQuery =
			$this->SOLRroot
			. "select/?rows=0&qt=edismax&q=+"
			. trim(urlencode($this->searchTerm))
			. "&fq=shortname:" . $this->incident
			. "&fq=-expiry_date:[*%20TO%20NOW]"
			. (strpos($this->SOLRfq, "-full_name")? "&fq=-full_name:[*%20TO%20*]" : '')
			. "&facet=true"
			. "&facet.query=ageGroup:youth&facet.query=ageGroup:adult&facet.query=ageGroup:unknown&facet.query=ageGroup:both"
			. "&facet.query=opt_status:mis&facet.query=opt_status:ali&facet.query=opt_status:inj&facet.query=opt_status:dec&facet.query=opt_status:unk&facet.query=opt_status:fnd"
			. "&facet.query=opt_gender:mal&facet.query=opt_gender:fml&facet.query=opt_gender:unk&facet.query=opt_gender:cpx"
			. "&facet.query=hospital:suburban&facet.query=hospital:wrnmmc&facet.query=hospital:public";

		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $solrQuery . "&wt=json"); // ensure the json version is called
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_VERBOSE, 1);
		curl_setopt($ch, CURLOPT_PORT, $this->SOLRport);

		$tempSOLRjson = json_decode(curl_exec($ch));
		curl_close($ch);

		$this->SOLRfacetResults = $tempSOLRjson->facet_counts->facet_queries;
		$this->cleanUpFacets();
	}


	// Insert fuzzy search operator after each search term (PL-264).
	private function fuzzify($searchTerm) {

		$tempTerm = '';

		// Take care not to fuzzify boolean terms, or terms w/in double-quoted phrases.
		// SOLR does the right thing if you fuzzify nonsensical stuff (e.g. single quoted term).
		$tempArray = explode(" ", $searchTerm);
                $inQuote = false;

		foreach($tempArray as $token) {
			if(strcasecmp($token, 'and') == 0 || strcasecmp($token, 'or') == 0) {
                    		$tempTerm .= $token . " ";
                        } else {
				if(!$inQuote) {
					// Fixme: Right paren? Place ~ inside it.
                			$tempTerm .= $token . "~ ";
				} else {
					$tempTerm .= $token . " ";
				}
			}

			// Process quote flag.
			if($token[0] == '"' && substr($token, -1) != '"') {
				// First character (but not last character) is a quote.
				$inQuote = true;
			} else if (substr($token, -1) == '"') {
				// Last character is a quote.
				$inQuote = false;
			}
		}
		return trim($tempTerm);
        }
}


// testing
// $search = new SearchDB("sql", "sendai2011", "Mike", "true;true;true;true;true;true", "true;true;true", "true;true;true", "true;true;true", "0;25;last_updated;true");
// $search->executeSearch();
// echo "<br />";
// echo count($search->results);

// $search2 = new SearchDB("solr", "sendai2011", "Mi*");
// $search2->executeSearch();
// echo count($search2->results);
// $search->getLastUpdateSOLR();

// echo json_encode($search->results);
// echo json_encode($search2->results);



