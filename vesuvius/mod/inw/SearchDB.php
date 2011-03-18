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
	public function SearchDB($searchMode, $incident, $searchTerm, $sStatus = "true;true;true;true;true", $sGender="true;true;true", $sAge="true;true;true", $sHospital="true;true;true", $sPageControls="0;-1;;true") {  
		$this->incident = $incident;
		$this->searchTerm = $searchTerm;
		
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
			$this->initDBConnection();
			
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
		
		$this->parseSearchTermsBroad();
		$this->parseSearchTermsSoundex();
		$this->parseSearchTermsPrecise();
	}
	
	private function buildFiltersClause() {
		//$this->whereClause .= " ( 1 = 0 ";
		$this->statusString = "";
		if ($this->missing == "true")
			$this->statusString .= "mis;";
			//$this->whereClause .= " OR opt_status = 'mis'";
		if ($this->alive == "true") 
			$this->statusString .= "ali;";
			//$this->whereClause .= " OR opt_status = 'ali'"; 
		if ($this->injured == "true") 
			$this->statusString .= "inj;";
			//$this->whereClause .= " OR opt_status = 'inj'"; 
		if ($this->deceased == "true")
			$this->statusString .= "dec;";
			//$this->whereClause .= " OR opt_status = 'dec'"; 
		if ($this->unknown == "true") 
			$this->statusString .= "unk;";	
			//$this->whereClause .= " OR opt_status = 'unk' OR opt_status IS NULL"; 
		
		//$this->whereClause .= ") AND ( 1 = 0 ";
		$this->genderString = "";
		if ($this->male == "true")
			$this->genderString .= "mal;";
			//$this->whereClause .= " OR opt_gender = 'mal'";
		if ($this->female == "true")
			$this->genderString .= "fml;";
			//$this->whereClause .= " OR opt_gender = 'fml'";
		if ($this->genderUnk == "true")
			$this->genderString .= "unk;";
			//$this->whereClause .= " OR (opt_gender <> 'mal' AND opt_gender <> 'fml' OR opt_gender IS NULL)";		
		
		//$this->whereClause .= ") AND ( 1 = 0 ";	
		$this->ageString = "";
		if ($this->child == "true")
			$this->ageString .= "child;";
			//$this->whereClause .= " OR CAST(years_old AS UNSIGNED) < 18 ";
		if ($this->adult == "true")
			//$this->whereClause .= " OR CAST(years_old AS UNSIGNED) >= 18 ";		
			$this->ageString .= "adult;";
		if ($this->ageUnk == "true")
			$this->ageString .= "unknown;";
			//$this->whereClause .= " OR CONVERT(years_old, UNSIGNED INTEGER) IS NULL";		
			
		//$this->whereClause .= ") AND ( 1 = 0 ";
		$this->hospitalString = "";
		if ( $this->suburban == "true" )
			$this->hospitalString .= "suburban;";
			//$this->whereClause .= " OR hospital = 'sh' ";
		if ( $this->nnmc == "true" )
			$this->hospitalString .= "nnmc;";
			//$this->whereClause .= " OR hospital = 'nnmc' ";
		if ( $this->otherHosp == "true" )
			$this->hospitalString .= "other;";
			//$this->whereClause .= " OR (hospital <> 'sh' AND hospital <> 'nnmc' OR hospital IS NULL) ";
		
		//$this->whereClause .= " ) ";
		//$this->whereClause .= " AND shortname = '" . $this->incident . "'";
	}
	
	private function buildMainQuery() {
		$this->mainQ = "SELECT * " . $this->fromClause . " WHERE ";
	}
	
	private function parseSearchTermsBroad() {
		if ( strlen($this->searchTerm) > 0 ) {
			$toReplace = array(";", ";", ",", ".", "<", ">", "?", ":", "'", "\"", "`", "~", "!", "@", "#", "$", "%", ":");	
			str_replace($toReplace, " ", $this->searchTerm);	
			$terms = explode(" ", $this->searchTerm);
			for ($i = 0; $i < count($terms); $i++) {
				$this->whereClauseBroad .= $i > 0 ? " OR " : " ( ";
				if (strlen($terms[$i]) >= 2) {
					$this->whereClauseBroad .= " full_name like '".$terms[$i]."%' or full_name like '% ".$terms[$i]."%' or full_name like '%,".$terms[$i]."' or full_name like '%.".$terms[$i]."'";
					$this->whereClauseBroad .= " OR given_name sounds like '".$terms[$i]."'" ;
					$this->whereClauseBroad .= " OR family_name sounds like '".$terms[$i]."'" ;
				}
			}
			$this->whereClauseBroad .= " ) AND ";
		}
		
		$this->whereClauseBroad .= $this->whereClause;
	}
	
	private function parseSearchTermsSoundex() {
		if ( strlen($this->searchTerm) > 0 ) {
			$toReplace = array(";", ";", ",", ".", "<", ">", "?", ":", "'", "\"", "`", "~", "!", "@", "#", "$", "%", ":");	
			str_replace($toReplace, " ", $this->searchTerm);	

			if ( strlen($this->searchTerm) > 0 ) {
				$this->whereClauseSoundex .= " (full_name SOUNDS LIKE '" . $this->searchTerm . "') AND ";
			}
		}
		$this->whereClauseSoundex .= $this->whereClause;
	}

	private function parseSearchTermsPrecise() {
		$toReplace = array(";", ";", ",", ".", "<", ">", "?", ":", "'", "\"", "`", "~", "!", "@", "#", "$", "%", ":");	
		str_replace($toReplace, " ", $this->searchTerm);	
		if ( strlen($this->searchTerm) > 0 ) {
			$this->whereClausePrecise .= " (full_name = '" . $this->searchTerm . "') AND ";
		}
		
		$this->whereClausePrecise .= $this->whereClause;
	}	
	
	// kinda redudant now because of the view, but this might change later.
	private function buildFromClause() {
		$this->fromClause =  "FROM person_search";
	}
	
	private function getResultsCount() {
		$qRC = "SELECT count(*) FROM (" . $this->mainQ . $this->whereClausePrecise . " UNION " . 
				$this->mainQ . $this->whereClauseBroad . " UNION " . 
				$this->mainQ . $this->whereClauseSoundex . ") as t";

		 //echo $qRC;
		$result = $this->db->Execute($qRC);
		while (!$result == NULL && !$result->EOF) {
			$this->numRowsFound = $result->fields[0];
			mysql_free_result($result);
			break;
		}
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
		$mysqli = new mysqli( $conf["db_host"], $conf["db_user"], $conf["db_pass"], $conf["db_name"], $conf["db_port"] ); // "archivestage.nlm.nih.gov", "mrodriguez", "xdr5XDR%", "pltest3" );
		/*$query = "SELECT SQL_CALC_FOUND_ROWS * FROM (
					SELECT
							`a`.`p_uuid`       AS `p_uuid`,
							`a`.`full_name`    AS `full_name`,
							`a`.`given_name`   AS `given_name`,
							`a`.`family_name`  AS `family_name`,
							(CASE WHEN `b`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk') OR `b`.`opt_status` IS NULL THEN 'unk' ELSE `b`.`opt_status` END) AS `opt_status`,
					DATE_FORMAT(b.updated, '%m/%e/%y @ %l:%i:%s %p') as updated,
							(CASE WHEN `c`.`opt_gender` NOT IN ('mal', 'fml') OR `c`.`opt_gender` IS NULL THEN 'unk' ELSE `c`.`opt_gender` END) AS `opt_gender`,
							(CASE WHEN CAST(`c`.`years_old` AS UNSIGNED) < 18 THEN 'child' WHEN CAST(`c`.`years_old` AS UNSIGNED) >= 18 THEN 'adult' ELSE 'unknown' END) as `age_group`,
							`i`.`image_height` AS `image_height`,
							`i`.`image_width`  AS `image_width`,
							`i`.`url_thumb`    AS `url_thumb`,
							`e`.`comments`     AS `comments`,
							`e`.`last_seen`    AS `last_seen`,
							(CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END)  AS `hospital`,
							(CASE WHEN (`h`.`hospital_uuid` = -(1)) THEN NULL ELSE `h`.`icon_url` END) AS `icon_url`,
							`inc`.`shortname`  AS `shortname`
					   FROM `person_uuid` `a`
					   JOIN `person_status` `b`          ON (`a`.`p_uuid` = `b`.`p_uuid` AND `b`.`isVictim` = 1)
				  LEFT JOIN `image` `i`                  ON `a`.`p_uuid` = `i`.`x_uuid`
					   JOIN `person_details` `c`         ON `a`.`p_uuid` = `c`.`p_uuid`
				  LEFT JOIN `person_missing` `e`         ON `a`.`p_uuid` = `e`.`p_uuid`
					   JOIN `incident` `inc`             ON `inc`.`incident_id` = `a`.`incident_id`
				  LEFT JOIN `hospital` `h`               ON `h`.`hospital_uuid` = `a`.`hospital_uuid`
				) as t
				  WHERE INSTR(?, t.opt_status)
					AND INSTR(?, t.opt_gender)
					  AND INSTR(?, t.age_group)
					  AND INSTR(?, t.hospital)
					AND t.`shortname` = ?
				  AND t.full_name like CONCAT('%', ?, '%')
				 ORDER BY CASE WHEN t.full_name like CONCAT(?, ' %') THEN 0
						   WHEN t.full_name like CONCAT(?, '%') THEN 1
						   WHEN t.full_name like CONCAT('% ', ?, '%') THEN 2
						   ELSE 3
						  END,
						  ?
				LIMIT ?, ?;";
		
		if ( $stmt = $mysqli->prepare($query) ) {
			$stmt->bind_param("ssssssssssii", $this->statusString, $this->genderString, $this->ageString,
											 $this->hospitalString, $this->incident, $this->searchTerm,
											 $this->searchTerm, $this->searchTerm, $this->searchTerm,
											 $this->sortBy, $this->pageStart, $this->perPage);
			
			$stmt->execute();
			$stmt->bind_result($p_uuid, $full_name, $given_name, $family_name, $opt_status, $updated, 
					   $opt_gender, $age_group, $image_height, $image_width, $url_thumb, $comments, $last_seen,
					   $hospital, $icon_url, $shortname);
					   
			while ($stmt->fetch()) {
				$encodedUUID = base64_encode($p_uuid);
				$this->results[] = array('p_uuid'=>$p_uuid, 
						'encodedUUID'=>$encodedUUID,
						'full_name'=>$full_name, 
						'opt_status'=>str_replace("\"", "", $opt_status),
						'imageUrl'=>$url_thumb, 
						'imageWidth'=>$image_width, 
						'imageHeight'=>$image_height, 
						'age_group'=>$age_group, 
						'statusSahanaUpdated'=>$updated, 
						'last_seen'=>$last_seen, 
						'comments'=>strip_tags($comments),
						'gender' => $opt_gender,
						'hospitalIcon' => $icon_url);
			}
		} else {
			printf("Prepared Statement Error: %s\n", $mysqli->error);
		}
		
		$stmt->close();
		$mysqli->close();
		
		$this->numRowsFound = 500;
		$this->allCount = 10000;
		
		//echo "<pre>";
		//print_r( $this->results );
		//echo "</pre>";
		*/
		
		$proc = "CALL PLSearch('$this->searchTerm', '$this->statusString', '$this->genderString', '$this->ageString', '$this->hospitalString', '$this->incident', '$this->sortBy', $this->pageStart, $this->perPage, @rowsFound, @allCount)";

		//$res = $mysqli->multi_query( $proc ); //CALL $proc; SELECT @rowsFound; SELECT @totalRows;" ); 
		$res = $mysqli->multi_query( "$proc; SELECT @rowsFound; SELECT @allCount;" ); 

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
//									'last_seen'=>$row["last_seen"], 
//									'comments'=>strip_tags($row["comments"]),
									'gender' => $row["opt_gender"],
									'hospitalIcon' => $row["icon_url"]);
						}
					} elseif ( $c == 1 ) { // rows found
						while( $row = $result->fetch_row() )
							foreach( $row as $cell ) 
								$this->numRowsFound = $cell;
					} elseif ( $c == 2 ) { // total rows
						while( $row = $result->fetch_row() )
							foreach( $row as $cell ) 
								$this->allCount = $cell;
					}
				  

					$result->close();
					if( $mysqli->more_results() ) $c += 1;					
				} 
			} while( $mysqli->more_results() && $mysqli->next_result() ); 
		} 
		$mysqli->close(); 
		
		//echo "<pre>";
		//print_r($this->results);
		//echo "</pre>";
		
		/*$q = "SELECT DATE_FORMAT(t.updated, '%m/%e/%y @ %l:%i:%s %p') as updated,
						 p_uuid,
						 full_name, 
						 given_name,
						 family_name,
						 opt_status,
						 opt_gender,
						 years_old,
						 image_height,
						 image_width,
						 url_thumb,
						 comments,
						 last_seen,
						 icon_url,
						 shortname,
						 hospital 
					FROM person_search as t";

		if ( $this->sortBy != "" )
			$q .= " ORDER BY " . $this->sortBy;	
		
		if ( $this->mode == "true" && $this->perPage != "-1" )
			$q .= " LIMIT " . $this->pageStart . ", " . $this->perPage;
*/
/*
		$q = "SELECT SQL_CALC_FOUND_ROWS * FROM (
			  SELECT DISTINCT
				`a`.`p_uuid`       AS `p_uuid`,
				`a`.`full_name`    AS `full_name`,
				(CASE WHEN `b`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk') OR `b`.`opt_status` IS NULL THEN 'unk' ELSE `b`.`opt_status` END) AS `opt_status`,
				`b`.`updated` 	   AS `updated`,
				(CASE WHEN `c`.`opt_gender` NOT IN ('mal', 'fml') OR `c`.`opt_gender` IS NULL THEN 'unk' ELSE `c`.`opt_gender` END) AS `opt_gender`,
				(CASE WHEN CAST(`c`.`years_old` AS UNSIGNED) < 18 THEN 'child' WHEN CAST(`c`.`years_old` AS UNSIGNED) >= 18 THEN 'adult' ELSE 'unknown' END) as `age_group`,
				`i`.`image_height` AS `image_height`,
				`i`.`image_width`  AS `image_width`,
				`i`.`url_thumb`    AS `url_thumb`,
				`e`.`comments`     AS `comments`,
				`e`.`last_seen`    AS `last_seen`,
				(CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END)  AS `hospital`,
				(CASE WHEN (`h`.`hospital_uuid` = -(1)) THEN NULL ELSE `h`.`icon_url` END) AS `icon_url`,
				`inc`.`shortname`  AS `shortname`
			   FROM `person_uuid` `a`
			   JOIN `person_status` `b`          ON (`a`.`p_uuid` = `b`.`p_uuid` AND `b`.`isVictim` = 1)
		  LEFT JOIN `image` `i`                  ON `a`.`p_uuid` = `i`.`x_uuid`
			   JOIN `person_details` `c`         ON `a`.`p_uuid` = `c`.`p_uuid`
		  LEFT JOIN `person_missing` `e`         ON `a`.`p_uuid` = `e`.`p_uuid`
			   JOIN `resource_to_incident` `rti` ON `a`.`p_uuid` = `rti`.`x_uuid`
			   JOIN `incident` `inc`             ON `inc`.`incident_id` = `rti`.`incident_id`
		  LEFT JOIN `person_to_hospital` `pth`   ON `a`.`p_uuid` = `pth`.`p_uuid`
		  LEFT JOIN `hospital` `h`               ON `pth`.`hospital_uuid` = `h`.`hospital_uuid`
		) as t
		  WHERE INSTR('$this->statusString', t.opt_status)
			AND INSTR('$this->genderString', t.opt_gender)
			  AND INSTR('$this->ageString', t.age_group)
			  AND INSTR('$this->hospitalString', t.hospital)
			AND t.`shortname` = '$this->incident'
		  AND t.full_name like CONCAT('%', '$this->searchTerm', '%')
		 ORDER BY CASE WHEN t.full_name like CONCAT('$this->searchTerm', ' %') THEN 0
				   WHEN t.full_name like CONCAT('$this->searchTerm', '%') THEN 1
				   WHEN t.full_name like CONCAT('% ', '$this->searchTerm', '%') THEN 2
				   ELSE 3
				  END,";
				  
		if ( $this->sortBy != "" )
			$q .= $this->sortBy;	
		
		if ( $this->mode == "true" && $this->perPage != "-1" )
			$q .= " LIMIT " . $this->pageStart . ", " . $this->perPage;				  
*/
		//echo $q;

		/*$result = $this->db->Execute($q);
		//$this->numRowsFound = 1000;
		//$this->allCount = 1000;
		
		
			 echo "<pre>";
			 print_r( $result );
			 echo "</pre>";		
		while (!$result == NULL && !$result->EOF) {

			 $encodedUUID = base64_encode($result->fields["p_uuid"]);
			 $this->results[] = array('p_uuid'=>$result->fields["p_uuid"], 
					 'encodedUUID'=>$encodedUUID,
					 'full_name'=>$result->fields["full_name"], 
					 'opt_status'=>str_replace("\"", "", $result->fields["opt_status"]),
					 'imageUrl'=>$result->fields["url_thumb"], 
					 'imageWidth'=>$result->fields["image_width"], 
					 'imageHeight'=>$result->fields["image_height"], 
					 'age_group'=>$result->fields["age_group"], 
					 'statusSahanaUpdated'=>$result->fields["updated"], 
					 'last_seen'=>$result->fields["last_seen"], 
					 'comments'=>strip_tags($result->fields["comments"]),
					 'gender' => $result->fields["opt_gender"],
					 'hospitalIcon' => $result->fields["icon_url"]);
			 $result->MoveNext();
		}
		mysql_free_result($result);

		$this->getResultsCount();
		$this->getTotalResults();*/
	}

	public function getLastUpdate() {
		if ( $this->searchMode == "solr" )
			$this->getLastUpdateSOLR();
		elseif ( $this->searchMode == "sql" )
			$this->getLastUpdateSQL();
	}
	
	public function getLastUpdateSOLR() {
		global $conf;
		$solrQuery = $conf["SOLRroot"] . "select/?fl=*,score&q=*:*%20" 
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
		$this->lastUpdated = $date->format('m/d/y @ g:m:s A');
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
		
		//echo $this->SOLRjson;
	}
	
	// ugly but I'd like to have clean json responses.
	private function cleanUpFacets() {
		$temp["child"] = $this->SOLRfacetResults->{"years_old:[0 TO 17]"};
		$temp["adult"] = $this->SOLRfacetResults->{"years_old:[18 TO *]"};
		$temp["otherAge"] = $this->SOLRfacetResults->{"years_old:(-[* TO *])"};
		
		$temp["missing"] = $this->SOLRfacetResults->{"opt_status:mis"};
		$temp["alive"] = $this->SOLRfacetResults->{"opt_status:ali"};
		$temp["injured"] = $this->SOLRfacetResults->{"opt_status:inj"};
		$temp["deceased"] = $this->SOLRfacetResults->{"opt_status:dec"};
		$temp["unknown"] = $this->SOLRfacetResults->{"opt_status:unk"};
		
		$temp["male"] = $this->SOLRfacetResults->{"opt_gender:mal"};
		$temp["female"] = $this->SOLRfacetResults->{"opt_gender:fml"};
		$temp["otherGender"] = $this->SOLRfacetResults->{"opt_gender:(-mal AND -fml)"};
		
		$temp["suburban"] = $this->SOLRfacetResults->{"hospital:sh"};
		$temp["nnmc"] = $this->SOLRfacetResults->{"hospital:nnmc"};
		$temp["otherHospital"] = $this->SOLRfacetResults->{"hospital:(-[* TO *])"};
		
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
			$this->results[] = array('p_uuid' => $doc->p_uuid, 
				 'encodedUUID' => base64_encode($doc->p_uuid),
				   'full_name' => isset($doc->full_name) ? $doc->full_name : null, 
				  'opt_status' => isset($doc->opt_status) ? $doc->opt_status : null,
				    'imageUrl' => isset($doc->url_thumb) ? $doc->url_thumb : null, 
				  'imageWidth' => isset($doc->image_width) ? $doc->image_width : null, 
				 'imageHeight' => isset($doc->image_height) ? $doc->image_height : null, 
				   'years_old' => isset($doc->years_old) ? $doc->years_old : null, 
						  'id' => isset($doc->personId) ? $doc->personId : null, 
		 'statusSahanaUpdated' => $doc->updated ? $date->format('m/d/y @ g:m:s A') : null, 
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
		$this->SOLRquery = $this->SOLRroot . "select/?fl=*,score&q=*:*%20" . trim(urlencode($this->searchTerm)) . "~" //for fuzzy search
							. $this->SOLRfq
							. "&facet=true" //&facet.field=opt_status&facet.field=years_old&facet.field=opt_gender&facet.field=hospital&facet.missing=true"
							. "&facet.query=years_old:[0 TO 17]&facet.query=years_old:[18 TO *]&facet.query=years_old:(-[* TO *])"
							. "&facet.query=opt_status:mis&facet.query=opt_status:ali&facet.query=opt_status:inj&facet.query=opt_status:dec&facet.query=opt_status:unk"
							. "&facet.query=opt_gender:mal&facet.query=opt_gender:fml&facet.query=opt_gender:(-mal AND -fml)"
							. "&facet.query=hospital:sh&facet.query=hospital:nnmc&facet.query=hospital:(-[* TO *])";
							

								
		if ( $this->mode == "true" && $this->perPage != "-1" )
			$this->SOLRquery .= "&start=" . $this->pageStart . "&rows=" . $this->perPage;
		else 
			$this->SOLRquery .= "&rows=1000"; // max number of rows is 1000
			
		if ( $this->sortBy != "" )
			$this->SOLRquery .= "&sort=" . $this->sortBy . ",score desc";
			
		$this->SOLRquery = str_replace(" ", "%20", $this->SOLRquery);			
	
	 //echo "FROM buildSOLRQuery() :: <BR />$this->SOLRquery <BR/><BR/>";
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
		
		// opt_gender filters
		$this->SOLRfq .= ")&fq=opt_gender:(*:*";
		if ($this->male != "true")
			$this->SOLRfq .= " -mal";
		if ($this->female != "true")
			$this->SOLRfq .= " -fml";
		if ($this->genderUnk != "true")
			$this->SOLRfq .= " (mal OR fml)"; //show only mal or fml
		
		// years_old filters
		$this->SOLRfq .= ")&fq=years_old:(*:*";	
		if ($this->child != "true")
			$this->SOLRfq .= " -[0 TO 17] ";
		if ($this->adult != "true")
			$this->SOLRfq .= " -[18 TO *] ";		
		if ($this->ageUnk != "true")
			$this->SOLRfq .= " [* TO *]";		
		
		// hospital filters
		$this->SOLRfq .= ")&fq=hospital:(*:*";
		if ( $this->suburban != "true" )
			$this->SOLRfq .= " -sh ";
		if ( $this->nnmc != "true" )
			$this->SOLRfq .= " -nnmc ";
		if ( $this->otherHosp != "true" )
			$this->SOLRfq .= " [* TO *]";
		
		//incident shortname filter (always applied)
		$this->SOLRfq .= ")&fq=shortname:(" . $this->incident . ")";
	}
	
	private function getSOLRallCount() {
		$tmpSOLRquery = $this->SOLRroot . "select/?q=*:*&fq=shortname:(" . $this->incident . ")";
		//echo $tmpSOLRquery;
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
  $search = new SearchDB("solr", "christchurch", "", "true;true;true;true;true", "true;true;true", "true;true;true", "true;true;true", "0;25;opt_status+desc;true");
  $search->executeSearch();
 // $search->getLastUpdateSOLR();
	
// echo json_encode($search->results);

// echo json_encode($search2->results);
  
  
 
 

?>