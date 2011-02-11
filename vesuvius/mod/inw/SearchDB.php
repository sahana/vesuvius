<?php

class SearchDB
{
	public	$incident, 
			$searchTerm,
			
			$pageStart, 
			$perPage, 
			$sortBy, 
			$mode,

			$missing, 
			$alive, 
			$injured,
			$deceased,
			$unknown,
			
			$male,
			$female,
			$genderUnk,
			
			$child,
			$adult,
			$ageUnk,
			
			$suburban,
			$nnmc,
			$otherHosp,
			
			$results,
			$numRowsFound,
			$allCount,
			$lastUpdated;
	
	private $whereClause,
	
			$whereClausePrecise,
			$whereClauseBroad,
			$whereClauseSoundex,
	
			$fromClause,
			
			$db;
		
	
	/**
	 *  Constructor
	 *
	 * Params: $sStatus = "missing;alive;injured;deceased;unknown"
	 *  	   $sPageControls = "$pageStart;$perPage;$sortBy;$mode"
	 *         $sGender = gender imploded
	 *	   	   $sAge = age imploded
	 *	
	 *///
	public function SearchDB($incident, $searchTerm, $sStatus = "true;true;true;true;true", $sGender="true;true;true", $sAge="true;true;true", $sHospital="true;true;true", $sPageControls="0;-1;;true") {  
		
		$this->incident = $incident;
		$this->searchTerm = $searchTerm;
		
		$this->setStatusFilters($sStatus);
		$this->setPageControls($sPageControls);
		$this->setGenderFilters($sGender);
		$this->setAgeFilters($sAge);
		$this->setHospitalFilters($sHospital);
		
		
		
		$this->numRowsFound = -1;
		
		$this->buildFromClause();
		$this->buildWhereClause();
		$this->buildMainQuery();
		
		$this->initDBConnection();
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
		$this->whereClause .= " ( 1 = 0 ";
		if ($this->missing == "true")
			$this->whereClause .= " OR opt_status = 'mis'";
		if ($this->alive == "true") 
			$this->whereClause .= " OR opt_status = 'ali'"; 
		if ($this->injured == "true") 
			$this->whereClause .= " OR opt_status = 'inj'"; 
		if ($this->deceased == "true")
			$this->whereClause .= " OR opt_status = 'dec'"; 
		if ($this->unknown == "true") 
			$this->whereClause .= " OR opt_status = 'unk' OR opt_status IS NULL"; 
		
		$this->whereClause .= ") AND ( 1 = 0 ";
		if ($this->male == "true")
			$this->whereClause .= " OR opt_gender = 'mal'";
		if ($this->female == "true")
			$this->whereClause .= " OR opt_gender = 'fml'";
		if ($this->genderUnk == "true")
			$this->whereClause .= " OR (opt_gender <> 'mal' AND opt_gender <> 'fml' OR opt_gender IS NULL)";		
		
		$this->whereClause .= ") AND ( 1 = 0 ";	
		if ($this->child == "true")
			$this->whereClause .= " OR CAST(years_old AS UNSIGNED) < 18 ";
		if ($this->adult == "true")
			$this->whereClause .= " OR CAST(years_old AS UNSIGNED) >= 18 ";		
		if ($this->ageUnk == "true")
			$this->whereClause .= " OR CONVERT(years_old, UNSIGNED INTEGER) IS NULL";		
			
		$this->whereClause .= ") AND ( 1 = 0 ";
		if ( $this->suburban == "true" )
			$this->whereClause .= " OR hospital = 'sh' ";
		if ( $this->nnmc == "true" )
			$this->whereClause .= " OR hospital = 'nnmc' ";
		if ( $this->otherHosp == "true" )
			$this->whereClause .= " OR (hospital <> 'sh' AND hospital <> 'nnmc' OR hospital IS NULL) ";
		
		$this->whereClause .= " ) ";
		$this->whereClause .= " AND shortname = '" . $this->incident . "'";
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
		
		
		$q = "SELECT DATE_FORMAT(t.updated, '%m/%e/%y @ %l:%i:%s %p') as updated,
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
					FROM (" . $this->mainQ . $this->whereClausePrecise .  
				 " UNION " . $this->mainQ . $this->whereClauseSoundex . 
				 " UNION " . $this->mainQ . $this->whereClauseBroad . ") as t";

		if ( $this->sortBy != "" )
			$q .= " ORDER BY " . $this->sortBy;	
		
		if ( $this->mode == "true" && $this->perPage != "-1" )
			$q .= " LIMIT " . $this->pageStart . ", " . $this->perPage;

		$result = $this->db->Execute($q);

		while (!$result == NULL && !$result->EOF) {
			$encodedUUID = base64_encode($result->fields["p_uuid"]);
			$this->results[] = array('p_uuid'=>$result->fields["p_uuid"], 
					'encodedUUID'=>$encodedUUID,
					'full_name'=>$result->fields["full_name"], 
					'opt_status'=>str_replace("\"", "", $result->fields["opt_status"]),
					'imageUrl'=>$result->fields["url_thumb"], 
					'imageWidth'=>$result->fields["image_width"], 
					'imageHeight'=>$result->fields["image_height"], 
					'years_old'=>$result->fields["years_old"], 
					'id'=>$result->fields["personId"], 
					'statusSahanaUpdated'=>$result->fields["updated"], 
					'statusTriage'=>$result->fields["triageCategory"], 
					'peds'=>$result->fields["peds"], 
					'orgName'=>$result->fields["orgName"], 
					'last_seen'=>$result->fields["last_seen"], 
					'comments'=>strip_tags($result->fields["comments"]),
					'gender' => $result->fields["opt_gender"],
					'hospitalIcon' => $result->fields["icon_url"]);
			$result->MoveNext();
		}
		mysql_free_result($result);

		$this->getResultsCount();
		$this->getTotalResults();
	}

	public function getLastUpdate() {
		$q = "SELECT DATE_FORMAT(MAX(t.updated), '%m/%e/%y @ %l:%i:%s %p') as updated
				FROM (" . $this->mainQ . $this->whereClausePrecise . " UNION " . $this->mainQ . $this->whereClauseSoundex . " UNION " . $this->mainQ . $this->whereClauseBroad . ") as t ";
		$result = $this->db->Execute($q);
		while (!$result == NULL && !$result->EOF) {
			$this->lastUpdated = $result->fields[0];
			$result->MoveNext();
		}
		
		mysql_free_result($result);
	}

	
}


// testing
 // $search = new SearchDB("cmax2009", "", "true;true;true;true;true", "true;true;true", "true;true;true", "true;true;true");
 // $search->getLastUpdate();
 // echo $search->lastUpdated;
 
 //echo $search->lastUpdated;
 //echo $search->numRowsFound;
?>