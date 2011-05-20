<?php

class SearchDB
{
	public	$incident, 
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
	
	private $whereClause,
	
			$whereClausePrecise,
			$whereClauseBroad,
			$whereClauseSoundex,
			
			$SOLRfq,
	
			$fromClause,
			
			$SOLRroot = "http://archivestage:8984/solr/lpf/",
			
			$SOLRquery,
			
			$db,
			$conf;
			
		
	
	/**
	 *  Constructor
	 *
	 * Params: $searchMode = "solr" or "sql"
			   $sStatus = "missing;alive;injured;deceased;unknown"
	 *  	   $sPageControls = "pageStart;perPage;sortBy;mode"
	 *         $sGender = gender imploded
	 *	   	   $sAge = age imploded
	 *	
	 *///
	public function SearchDB($searchMode, $incident, $searchTerm, $sStatus = "true;true;true;true;true;true", $sGender="true;true;true", $sAge="true;true;true", $sHospital="true;true;true", $sPageControls="0;-1;;true") {  
		$this->incident = $incident;
		$toReplace = array(",", ".", "/", "\\", "?", "!", "~", "@", "$", "%", "^", "&", "*", "(", ")", "+", "-"); 
		$this->searchTerm = str_replace($toReplace, "", $searchTerm);
		
		$this->setStatusFilters($sStatus);
		$this->setPageControls($sPageControls);
		$this->setGenderFilters($sGender);
		$this->setAgeFilters($sAge);
		$this->setHospitalFilters($sHospital);
					
		$this->numRowsFound = -1;
		$this->searchMode = $searchMode;
		
		if ( $searchMode == "sql" ) {
			$this->sortBy = str_replace("+", " ", $this->sortBy);
			$this->buildFromClause();
			$this->buildWhereClause();
			$this->buildMainQuery();
		} else if ( $searchMode == "solr" ) {
			global $conf;
			$this->SOLRroot = $conf["SOLR_root"];
			$this->SOLRport = $conf["SOLR_port"];
			$this->buildSOLRFilters();
			$this->buildSOLRQuery();
			$this->getSOLRallCount();  // there has to be a way to include this in the 1 query, still looking
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
		$this->mode      = $tempArray[3];
	}
	
	private function setGenderFilters($sGender) {
		$tempArray = explode(";", $sGender);

		$this->male      = $tempArray[0];
		$this->female    = $tempArray[1];
		$this->genderUnk = $tempArray[2];
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
		if ($this->missing == "true")
			$this->statusString .= "mis;";
		
		if ($this->alive == "true") 
			$this->statusString .= "ali;";
		
		if ($this->injured == "true") 
			$this->statusString .= "inj;";
		
		if ($this->deceased == "true")
			$this->statusString .= "dec;";
		
		if ($this->unknown == "true") 
			$this->statusString .= "unk;";	

                $this->genderString = "";
		if ($this->male == "true")
			$this->genderString .= "mal;";
		if ($this->female == "true")
			$this->genderString .= "fml;";
		if ($this->genderUnk == "true")
			$this->genderString .= "unk;";

		$this->ageString = "";
		if ($this->child == "true")
			$this->ageString .= "child;";
		if ($this->adult == "true")
			$this->ageString .= "adult;";
		if ($this->ageUnk == "true")
			$this->ageString .= "unknown;";
			
		$this->hospitalString = "";
		if ( $this->suburban == "true" )
			$this->hospitalString .= "suburban;";
		if ( $this->nnmc == "true" )
			$this->hospitalString .= "nnmc;";
		if ( $this->otherHosp == "true" )
			$this->hospitalString .= "other;";
		
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
		if ( $this->searchMode == "solr" )
			$this->executeSOLRQuery();
		elseif ( $this->searchMode == "sql")
			$this->executeSQLQuery();
	}
		
	private function executeSQLQuery() {

		global $conf;
		
		//echo $proc;
		$mysqli = new mysqli( $conf["db_host"], $conf["db_user"], $conf["db_pass"], $conf["db_name"], $conf["db_port"] ); 
		if ( $this->mode != "true" ) {
			$this->pageStart = 0;
			$this->perPage = 2000;
		}
		
		$proc = "CALL PLSearch('$this->searchTerm', '$this->statusString', '$this->genderString', '$this->ageString', '$this->hospitalString', '$this->incident', '$this->sortBy', $this->pageStart, $this->perPage)";
		echo $proc;
		$res = $mysqli->multi_query( "$proc; SELECT @allCount;" ); 

		//print_r($res);
		if( $res ) {
			$results = 0;
			$c = 0;
			do {
				if ($result = $mysqli->store_result()) {
				  if ( $c == 0 ) {
						while ($row = $result->fetch_assoc()) { 
							$encodedUUID = base64_encode($row["p_uuid"]);
							$this->results[] = array('p_uuid'=>$row["p_uuid"], 
									'encodedUUID'=>$encodedUUID,
									'full_name'=>$row["full_name"], 
									'opt_status'=>str_replace("\"", "", $row["opt_status"]),
									'imageUrl'=>$row["url_thumb"], 
									'imageWidth'=>$row["image_width"], 
									'imageHeight'=>$row["image_height"], 
									'age_group'=>$row["age_group"], 
									'statusSahanaUpdated'=>$row["updated"], 
									'last_seen'=>$row["last_seen"], 
									'comments'=>strip_tags($row["comments"]),
									'gender' => $row["opt_gender"],
									'hospitalIcon' => $row["icon_url"]);
						}
					/*} elseif ( $c == 1 ) { // rows found
						while( $row = $result->fetch_row() )
							foreach( $row as $cell ) 
								$this->numRowsFound = $cell;
					} elseif ( $c == 2 ) { // total rows*/
					} 
				  
					$result->close();
					if( $mysqli->more_results() ) $c += 1;					
				} 
			} while( $mysqli->more_results() && $mysqli->next_result() ); 
		} 
		$mysqli->close(); 
	}
	
	public function getSQLAllCount() {
		$qRC = "SELECT COUNT(p.p_uuid) FROM person_uuid p JOIN incident i ON p.incident_id = i.incident_id WHERE i.shortname = '$this->incident' ;";
		$result = $this->db->Execute($qRC);
		while (!$result == NULL && !$result->EOF) {
			$this->allCount = $result->fields[0];
			mysql_free_result($result);
			break;
		}
		echo $this->allCount;
	}

	public function getLastUpdate() {
		if ( $this->searchMode == "solr" )
			$this->getLastUpdateSOLR();
		elseif ( $this->searchMode == "sql" )
			$this->getLastUpdateSQL();
	}
	
	// TODO: need to test for no connection found?
        public function getLastUpdateSOLR() {
		global $conf;
		$solrQuery = $conf["SOLRroot"] . "select/?fl=*,score+desc&q=+" 
					 . trim(urlencode($this->searchTerm)) . "~" //for fuzzy search
					 . $this->SOLRfq . "&sort=updated+desc&rows=1";
	
		$ch = curl_init(); 
                curl_setopt($ch, CURLOPT_URL, $solrQuery . "&wt=json"); // ensure the json version is called
                curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); 
                curl_setopt($ch, CURLOPT_VERBOSE, 1);
		curl_setopt($ch, CURLOPT_PORT, $this->SOLRport);
		
		$temp = json_decode(curl_exec($ch)); 
                curl_close($ch);      		
		
		$date = new DateTime($temp->response->docs[0]->updated);
		$this->lastUpdated = $date->format('m/d/y @ g:i:s A');
	}
	
	
	private function getLastUpdateSQL() {
		/*global $conf;
		$mysqli = new mysqli( $conf["db_host"], $conf["db_user"], $conf["db_pass"], $conf["db_name"], $conf["db_port"] ); // "archivestage.nlm.nih.gov", "mrodriguez", "xdr5XDR%", "pltest3" );
		$query = 	"SELECT DATE_FORMAT(MAX(t.updated), '%m/%e/%y @ %l:%i:%s %p') as updated FROM (
						SELECT
								`a`.`p_uuid`       AS `p_uuid`,
								`a`.`full_name`    AS `full_name`,
								`a`.`given_name`   AS `given_name`,
								`a`.`family_name`  AS `family_name`,
						`b`.`updated`,
								(CASE WHEN `b`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk') OR `b`.`opt_status` IS NULL THEN 'unk' ELSE `b`.`opt_status` END) AS `opt_status`,
								(CASE WHEN `c`.`opt_gender` NOT IN ('mal', 'fml') OR `c`.`opt_gender` IS NULL THEN 'unk' ELSE `c`.`opt_gender` END) AS `opt_gender`,
								(CASE WHEN CAST(`c`.`years_old` AS UNSIGNED) < 18 THEN 'child' WHEN CAST(`c`.`years_old` AS UNSIGNED) >= 18 THEN 'adult' ELSE 'unknown' END) as `age_group`,
								`i`.`image_height` AS `image_height`,
								`i`.`image_width`  AS `image_width`,
								`i`.`url_thumb`    AS `url_thumb`,
								(CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END)  AS `hospital`,
								(CASE WHEN (`h`.`hospital_uuid` = -(1)) THEN NULL ELSE `h`.`icon_url` END) AS `icon_url`,
								`inc`.`shortname`  AS `shortname`
						   FROM `person_uuid` `a`
						   JOIN `person_status` `b`          ON (`a`.`p_uuid` = `b`.`p_uuid` AND `b`.`isVictim` = 1)
					  LEFT JOIN `image` `i`                  ON `a`.`p_uuid` = `i`.`x_uuid`
						   JOIN `person_details` `c`         ON `a`.`p_uuid` = `c`.`p_uuid`
						   JOIN `incident` `inc`             ON `inc`.`incident_id` = `a`.`incident_id`
					  LEFT JOIN `hospital` `h`               ON `h`.`hospital_uuid` = `a`.`hospital_uuid`
					) as t
					  WHERE INSTR(?, t.opt_status)
						AND INSTR(?, t.opt_gender)
						  AND INSTR(?, t.age_group)
						  AND INSTR(?, t.hospital)
						AND t.`shortname` = ?
					  AND (t.full_name like CONCAT('%', ?, '%') OR t.given_name SOUNDS LIKE ? OR t.family_name SOUNDS LIKE ?);";
		
		if ( $stmt = $mysqli->prepare($query) ) {
			$stmt->bind_param("ssssssss", $this->statusString, $this->genderString, $this->ageString,
											 $this->hospitalString, $this->incident, $this->searchTerm,
											 $this->searchTerm, $this->searchTerm);
			
			$stmt->execute();
			$stmt->bind_result($updated);
					   
			while ($stmt->fetch()) {
				$this->lastUpdated = $updated;
			}
		} else {
			printf("Prepared Statement Error: %s\n", $mysqli->error);
		}
		
		$stmt->close();
		$mysqli->close();*/
	}

	
	
	public function executeSOLRQuery() {
        $ch = curl_init(); 
        curl_setopt($ch, CURLOPT_URL, $this->SOLRquery . "&wt=json"); // ensure the json version is called
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); 
        curl_setopt($ch, CURLOPT_VERBOSE, 1);
		curl_setopt($ch, CURLOPT_PORT, $this->SOLRport);
		
		$this->SOLRjson = curl_exec($ch); 
        curl_close($ch);      		
		
		$this->processSOLRjson();
	}
	
	// ugly but I'd like to have clean json responses.
	private function cleanUpFacets() {
		$temp["child"] = $this->SOLRfacetResults->{"years_old:[0 TO 17]"};
		$temp["adult"] = $this->SOLRfacetResults->{"years_old:[18 TO *]"};
		$temp["otherAge"] = $this->SOLRfacetResults->{"years_old:\-1"};
		
		$temp["missing"] = $this->SOLRfacetResults->{"opt_status:mis"};
		$temp["alive"] = $this->SOLRfacetResults->{"opt_status:ali"};
		$temp["injured"] = $this->SOLRfacetResults->{"opt_status:inj"};
		$temp["deceased"] = $this->SOLRfacetResults->{"opt_status:dec"};
		$temp["unknown"] = $this->SOLRfacetResults->{"opt_status:unk"};
		$temp["found"] = $this->SOLRfacetResults->{"opt_status:fnd"};
		
		$temp["male"] = $this->SOLRfacetResults->{"opt_gender:mal"};
		$temp["female"] = $this->SOLRfacetResults->{"opt_gender:fml"};
		$temp["otherGender"] = $this->SOLRfacetResults->{"opt_gender:unk"};
		
		$temp["suburban"] = $this->SOLRfacetResults->{"hospital:sh"};
		$temp["nnmc"] = $this->SOLRfacetResults->{"hospital:nnmc"};
		$temp["otherHospital"] = $this->SOLRfacetResults->{"hospital:public"};
		
		$this->SOLRfacetResults = $temp;
	}
	
	private function processSOLRjson() {
		$tempObject = json_decode($this->SOLRjson);

		// set rows found
		$this->numRowsFound = $tempObject->response->numFound;
		
		//take care of facet queries
		$this->SOLRfacetResults = $tempObject->facet_counts->facet_queries;
		$this->cleanUpFacets();

		// get query time
		$this->SOLRqueryTime = $tempObject->responseHeader->QTime;
		
		foreach ($tempObject->response->docs as $doc) {
			$date = new DateTime($doc->updated);
			//date_sub($date, date_interval_create_from_date_string('4 hours'));
			$this->results[] = array('p_uuid' => $doc->p_uuid, 
				 'encodedUUID' => base64_encode($doc->p_uuid),
				   'full_name' => isset($doc->full_name) ? $doc->full_name : null, 
				  'opt_status' => isset($doc->opt_status) ? $doc->opt_status : null,
				    'imageUrl' => isset($doc->url_thumb) ? $doc->url_thumb : null, 
				  'imageWidth' => isset($doc->image_width) ? $doc->image_width : null, 
				 'imageHeight' => isset($doc->image_height) ? $doc->image_height : null, 
				   'years_old' => isset($doc->years_old) ? $doc->years_old : null, 
						  'id' => isset($doc->personId) ? $doc->personId : null, 
		 'statusSahanaUpdated' => isset($doc->updated) ? str_replace('Z', '', $doc->updated) : null,
				'statusTriage' => isset($doc->triageCategory) ? $doc->triageCategory : null, 
						'peds' => isset($doc->peds) ? $doc->peds : null, 
					 'orgName' => isset($doc->orgName) ? $doc->orgName : null, 
				   'last_seen' => isset($doc->last_seen) ? $doc->last_seen : null, 
				    'comments' => isset($doc->comments) ? strip_tags($doc->comments) : null, 
					  'gender' => isset($doc->opt_gender) ? $doc->opt_gender : null,
			    'hospitalIcon' => isset($doc->icon_url) ? $doc->icon_url : null);
		}
	}
	
	private function buildSOLRQuery() {
		$this->SOLRquery = 
                    $this->SOLRroot . "select/?fl=*,score&qt=dismax&q=+" . trim(urlencode($this->searchTerm)) //. "~" //for fuzzy search [commented out for dismax]
                                    . $this->SOLRfq
                                    . "&facet=true" //&facet.field=opt_status&facet.field=years_old&facet.field=opt_gender&facet.field=hospital&facet.missing=true"
                                    . "&facet.query=years_old:[0 TO 17]&facet.query=years_old:[18 TO *]&facet.query=years_old:\-1"
                                    . "&facet.query=opt_status:mis&facet.query=opt_status:ali&facet.query=opt_status:inj&facet.query=opt_status:dec&facet.query=opt_status:unk&facet.query=opt_status:fnd"
                                    . "&facet.query=opt_gender:mal&facet.query=opt_gender:fml&facet.query=opt_gender:unk"
                                    . "&facet.query=hospital:sh&facet.query=hospital:nnmc&facet.query=hospital:public";
							

								
		if ( $this->mode == "true" && $this->perPage != "-1" )
			$this->SOLRquery .= "&start=" . $this->pageStart . "&rows=" . $this->perPage;
		else 
			$this->SOLRquery .= "&rows=2000"; // max number of rows returned is 2000
			
		if ( $this->sortBy != "" )
			$this->SOLRquery .= "&sort=" . $this->sortBy . ",score desc";
			
		$this->SOLRquery = str_replace(" ", "%20", $this->SOLRquery);			

	}
	
	private function buildSOLRFilters() {
		// opt_status filters
		$this->SOLRfq = "&fq=opt_status:(*:*";
		if ($this->missing != "true")
			$this->SOLRfq .= " -mis";
		if ($this->alive != "true") 
			$this->SOLRfq .= " -ali"; 
		if ($this->injured != "true") 
			$this->SOLRfq .= " -inj"; 
		if ($this->deceased != "true")
			$this->SOLRfq .= " -dec"; 
		if ($this->unknown != "true") 
			$this->SOLRfq .= " -unk"; 
		if ($this->found != "true") 
			$this->SOLRfq .= " -fnd"; 
		
		// opt_gender filters
		$this->SOLRfq .= ")&fq=opt_gender:(*:*";
		if ($this->male != "true") 
			$this->SOLRfq .= " -mal"; 
		if ($this->female != "true") 
			$this->SOLRfq .= " -fml"; 
		if ($this->genderUnk != "true")  
			$this->SOLRfq .= " -unk"; 
		
		// years_old filters
		$this->SOLRfq .= ")&fq=years_old:(*:*";	
		if ($this->child != "true")
			$this->SOLRfq .= " -[0 TO 17] ";
		if ($this->adult != "true")
			$this->SOLRfq .= " -[18 TO *] ";		
		if ($this->ageUnk != "true")
			$this->SOLRfq .= " -\-1";		
		
		// hospital filters
		$this->SOLRfq .= ")&fq=hospital:(*:*";
		if ( $this->suburban != "true" )
			$this->SOLRfq .= " -sh ";
		if ( $this->nnmc != "true" )
			$this->SOLRfq .= " -nnmc ";
		if ( $this->otherHosp != "true" )
			$this->SOLRfq .= " -public";
		
		//incident shortname filter (always applied)
		$this->SOLRfq .= ")&fq=shortname:(" . $this->incident . ")";
	}
	
	private function getSOLRallCount() {
		$tmpSOLRquery = $this->SOLRroot . "select/?q=*:*&fq=shortname:(" . $this->incident . ")";
		$ch = curl_init(); 
        curl_setopt($ch, CURLOPT_URL, $tmpSOLRquery . "&wt=json"); // ensure the json version is called
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); 
        curl_setopt($ch, CURLOPT_VERBOSE, 1);
		curl_setopt($ch, CURLOPT_PORT, $this->SOLRport);
		
		$tempSOLRjson = json_decode(curl_exec($ch)); 
        curl_close($ch);      
		
		$this->allCount = $tempSOLRjson->response->numFound;
		//echo $this->allCount;
	}
}


// testing
//   $search = new SearchDB("sql", "sendai2011", "Mike", "true;true;true;true;true;true", "true;true;true", "true;true;true", "true;true;true", "0;25;last_updated;true");
//   $search->executeSearch();
//   echo count($search->results);
  
   // $search2 = new SearchDB("sql", "sendai2011", "Mike", "true;true;true;true;true;true", "true;true;true", "true;true;true", "true;true;true", "25;25;updated desc;true");
   // $search2->executeSearch();
  // echo count($search2->results);
 // $search->getLastUpdateSOLR();
	
// echo json_encode($search->results);

// echo json_encode($search2->results);
  

 
 

?>
