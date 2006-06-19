<?php
/* $Id; */

/**Child library for  CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera
* 
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

ob_start();

@$link_id = mysql_connect("localhost", "root", "") or die("Connection Failed"); 
$select_db = mysql_select_db("sahana",$link_id) or die("Connection Failed"); 
//$btngender=$_REQUEST['btngender'];
$buttongender = $_GET['bg'];
$opt_gender = $_GET['ge'];

if($buttongender=="Deselect")
{
$opt_gender="m";
}

$bcstatus1='yes';
$bcstatus2='yes';
$has_birthcertificate=$_GET['bc'];
if($has_birthcertificate=='')
{
$has_birthcertificate='';
$bcstatus1='no';
$bcstatus2='lost';

}
$buttonagegroup=$_GET['ba'];
$opt_age_group=$_GET['ag'];

$min=-1;
$max=99;
$registeredinschool=$_GET['crs'];
if($registeredinschool!='1')
$registeredinschool="0";


if($buttonagegroup=="Deselect")
{
//$opt_age_group="";
$min=0;
$max=99;

}
else if($opt_age_group=="chi")
{
$min=10;
$max=14;
}
else if($opt_age_group=="you")
{
$min=15;
$max=18;
}
else if($opt_age_group=="unk")
{
$min=0;
$max=4;
}

else if($opt_age_group=="inf")
{
$min=5;
$max=9;
}
else if($opt_age_group=="inf")
{
$min=19;
$max=99;
}



$buttondateregistered=$_GET['br'];
if($buttondateregistered=="Deselect")
{
$opt_year='';
$opt_month='';
$opt_date='';
$date='';

}
else
{
$opt_year=$_GET['year'];

$opt_month=$_GET['bm'];
$opt_date= $_GET['ad'];
$date=$opt_year.'-'.$opt_month.'-'.$opt_date;

}



$is_aftersunamischool=$_GET['atsu'];
$is_beforesunamischool=$_GET['btsu'];

$btncenter=$_GET['bcen'];
if($btncenter=="Deselect")
$center_name='';
else
$center_name=$_GET['cn'];

$has_lost_parents=$_GET['lp'];

if($has_lost_parents=='')
{
$has_lost_parents='0';
$is_alive='';

}
else
{
$is_alive='0';


}
if($btncenter=="Deselect")
{
$center_name="";
}


$button_description=$_GET['btndes'];
$child_fname=$_GET['nch'];
$child_lname=$_GET['nfm'];

if($button_description=="Deselect")
{
$child_fname="";
$child_lname="";
}

//$has_lost_parents=$_GET['lp'];

$has_disabilities=$_GET['disab'];
$q1=$_GET['q1'];
$q2=$_GET['q2'];
$q3=$_GET['q3'];
$q4=$_GET['q4'];
$q5=$_GET['q5'];
$q6=$_GET['q6'];
$q7=$_GET['q7'];
$q8=$_GET['q8'];
$q9=$_GET['q9'];
$q10=$_GET['q10'];
$q11=$_GET['q11'];
$q12=$_GET['q12'];
$q13=$_GET['q13'];
$q14=$_GET['q14'];
$q15=$_GET['q15'];
$q16=$_GET['q16'];
$q17=$_GET['q17'];
$q18=$_GET['q18'];

if($has_disabilities=='')
$has_disabilities='0';
if($q1=='')
$q1='';
if($q2=='')
$q2='';
if($q3=='')
$q3='';
if($q4=='')
$q4='';
if($q5=='')
$q5='';
if($q6=='')
$q6='';
if($q7=='')
$q7='';
if($q8=='')
$q8='';
if($q9=='')
$q9='';
if($q10=='')
$q10='';
if($q11=='')
$q11='';
if($q12=='')
$q12='';
if($q13=='')
$q13='';
if($q14=='')
$q14='';
if($q15=='')
$q15='';
if($q16=='')
$q16='';
if($q17=='')
$q17='';
if($q18=='')
$q18='';

$iq1=$_GET['iq1'];
$iq2=$_GET['iq2'];
$iq3=$_GET['iq3'];
$iq4=$_GET['iq4'];
$iq5=$_GET['iq5'];
$iq6=$_GET['iq6'];
$iq7=$_GET['iq7'];

if($iq1=='')
$iq1='';

if($iq2=='')
$iq2='';

if($iq3=='')
$iq3='';

if($iq4=='')
$iq4='';

if($iq5=='')
$iq5='';

if($iq6=='')
$iq6='';

if($iq7=='')
$iq7='';

function get_option_description($option_code)
{

$query="select option_description from field_options where option_code='{$option_code}'";
$result = mysql_query($query); 
$row1 = mysql_fetch_array($result)  ;

return $row1[0];
}





$q1="select distinct p.p_uuid from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt,child_education edu,
child_family_data cfd,child_health cth,child_behaviour cbh,child_properties cp,child_reporter crp
 where p.p_uuid=pd.p_uuid and pd.p_uuid=itp.p_uuid
and itp.p_uuid=pdt.p_uuid and pdt.p_uuid=edu.p_uuid and cfd.p_uuid=edu.p_uuid and cth.p_uuid=cfd.p_uuid
and cth.p_uuid=cbh.p_uuid  and cbh.p_uuid=cp.p_uuid and cp.p_uuid=crp.p_uuid and (pdt.bc_status like '%{$bcstatus1}%' or pdt.bc_status like '%{$bcstatus2}%')
and pdt.age>={$min} and pdt.age<={$max} and pd.opt_gender like '%{$opt_gender}%' and 
 p.full_name like '%{$child_lname}%' and p.l10n_name like '%{$child_fname}%'

 and pdt.is_reg_in_school like '%{$registeredinschool}%' and pdt.center_code like '%{$center_name}%' and 
   edu.was_gng_to_school_tsunami like '%{$is_beforesunamischool}%' 
	 	 and is_gng_to_school_now like '%{$is_aftersunamischool}%' and ((cfd.relationship_to_child='mot'
  and cfd.relation_is_alive like '%{$is_alive}%') or (cfd.relationship_to_child='fat' and cfd.relation_is_alive like '%{$is_alive}%')) 
and cth.is_disabled like '%{$has_disabilities}%' and cbh.question1 like '%{$q1}%' and cbh.question2 like '%{$q2}%' and cbh.question3 like '%{$q3}%'
	and cbh.question4 like '%{$q4}%' and cbh.question5 like '%{$q5}%' and cbh.question6 like '%{$q6}%' and cbh.question7 like '%{$q7}%' and cbh.question8 like '%{$q8}%'
	and cbh.question9 like '%{$q9}%' and cbh.question10 like '%{$q10}%' and cbh.question11 like '%{$q11}%' and cbh.question12 like '%{$q12}%'
	and cbh.question13 like '%{$q13}%' and cbh.question14 like '%{$q14}%' and cbh.question15 like '%{$q15}%' 
and cbh.question16 like '%{$q16}%' and cbh.question17 like '%{$q17}%' and cbh.question18 like '%{$q18}%'
and cp.beating like '%{$iq1}%' and cp.sexual_abuse like '%{$iq2}%' and cp.neglecting like '%{$iq3}%'
and  cp.tdh_followup like '%{$iq4}%' and cp.child_trafficing like '%{$iq5}%' and cp.domestic_violence like '%{$iq6}%' and cp.drink_alcohol like '%{$iq7}%'
and crp.date_of_reg like '%{$date}%'"; 






$result = mysql_query($q1); 
$num_rows = mysql_num_rows($result); 
if($num_rows==0)
$csv_output="\tNo Matching Records For the Selected Query"."\015\012";
else
{
$relation='';
for($i=0;$i<10;$i++)
$relation.="\t\tRelationship\tRelationName\tRelationAlive\tRelationAge\tLivingWithChild\tProfession\tLocation\tInCenter\tReginSchool\tIsOfficialFostering\tDiedInTsunami\tReportedMissing\tReasonToLivewith";

$csv_output="\t".$num_rows."\t"."Records Found for the Query".$is_aftersunamischool."\015\012";
$csv_output .= "\015\012";
$count=0;
$csv_output .="\t\tChild Personal Details\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChildReporterDetails\t\t\t\t\t\t\t\t\tChild Family Status\t\t\t\t\t\t\t\t\tChildEducationDetails\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChildHealthDetails\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChildBehaviourDetails\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChildProperties\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tChildRelationDetails";
$csv_output .= "\015\012";
$csv_output .= "\015\012";
$csv_output .= "ChildCode\tCenter Code\tFirst Name\tLastName\tFamilyName\tDOB\tPlaceofBirth\tPresentResidence\tComingFrom\tBirthCertificate\tBCNumber\tAge\tGender\tMaritalStatus\tCountry\tReligion\tRace\tRegisteredInSchool\t\tRep Full Name\tDate of Reg\tRepRelation\tRepAddress\tRepPhone\tRepEmail\tDate Interviewd\t\tPresentFamilyStatus\tReasonforNtBkingPrehouse\tHasSufficientIncome\tFamilyDetails\tSpecialMaterialsNeeded\tDetailsMaterial\tDuring Tsunami Situation\t\tWasGngToSchoolBeforeTsunami\tSchoolName\tIfNoWhy\tLevel Tsunami\tIsGngToSchoolNow\tSchoolName\tIfNoWhy\tLevel Now\tGoing To Tution now\tGoing To Religious School now\tGoing to Temple or Mosque Now\tBestFriendName\tReginCenter\tbestFriendName\tReginCenter\t\tHasMentalPhysicalDisability\tExplanation\tGotAssistance\tExplanation\tPhysicallyAffected\tExplanation\tHeadaches\tNauseaFeels\tEyeProblems\tRashes\tAchesPanes\tVommitingThrowingUp\tChildseenbydoctor\tBeforeTsunamiHaschronic\tExplain\tChildSeriouslyInjured\tExplain\tOperatedLast12months\tExplain\tPresentHealthStillEffected\t\tSpontaneousAnswerGvnBy\tHaveDifficultyInLeavingHouse\tProblemsinRemembering\tHaveSleepDificulties\tLostAppetite\tHaveRecurrentDreams\tdifficltyincontrollingemotions\tMoreAffraidofStrangers\tAfraidofAnotherTsnami\tShowSignsofLestInterested\tNeverwanttotalk\tBeingMoreAggressive\tWithdrawnorShy\tLookSad\tSeemDistracted\tPlayingrembertsunami\tHasTsunamiPictures\tSeekMoreAttention\tFamilyReceivedSupport\tWho\tHasImprovement\t\tBeating\tSexualAbuse\tNeglecting\tChildTrafficing\tDomesticviolence\tDrinkAlcohol\tTDHFollowup\tOther".$relation;
//\t\tRelationship\tRelationName\tRelationAlive\tRelationAge\tLivingWithChild\tProfession\tLocation\tInCenter\tReginSchool\tIsOfficialFostering\tDiedInTsunami\tReportedMissing\tReasonToLivewith"; 

$csv_output .= "\015\012";
while($row= mysql_fetch_array($result)) { 

//$csv_output .= "\015\012";
      
		$id=	$row[0];
$count++;
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid and p.p_uuid={$id}";
$result1 = mysql_query($query1); 
 

	$row1 = mysql_fetch_array($result1)  ;
			$csv_output .= $row1[0]."\t".$row1[20]."\t".$row1[3]."\t".$row1[1]."\t".$row1[2]."\t".$row1[7]."\t".$row1[22]
	."\t".$row1[23]."\t".$row1[24]."\t".get_option_description($row1[26])."\t".$row1[17]."\t".$row1[21]."\t".get_option_description($row1[14])."\t".get_option_description($row1[13])."\t".get_option_description($row1[10])
	."\t".get_option_description($row1[12])."\t".get_option_description($row1[11])."\t".(($row1[28]=='1')?'Yes':'No');
	;
   // $csv_output .= "\015\012";

$csv_output .= "\t";
$query2="select * from person_uuid p,child_reporter f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$result2 = mysql_query($query2); 
 
//$csv_output .= "\015\012";

$row2 = mysql_fetch_array($result2); 
	$csv_output .= "\t".$row2[7]."\t".$row2[8]."\t".$row2[9]."\t".$row2[10]."\t".$row2[11]."\t".$row2[12]
	."\t".$row2[13]	;

$csv_output .= "\t";




$query4="select * from person_uuid p,child_family_status f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$result4 = mysql_query($query4); 
 
//$csv_output .= "\015\012";

$row4 = mysql_fetch_array($result4); 
	$csv_output .= "\t".get_option_description($row4[7])."\t".get_option_description($row4[8])."\t".(($row4[10]==1)?'Yes':'No')."\t".$row4[11]."\t".(($row4[12]==1)?'Yes':'No')."\t".$row4[13]
	."\t".get_option_description($row4[14])	;

$csv_output .= "\t";


$query5="select * from person_uuid p,child_education f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$result5 = mysql_query($query5); 
 
//$csv_output .= "\015\012";

$row5 = mysql_fetch_array($result5); 
	$csv_output .= "\t".(($row5[7]==1)?'Yes':'No')."\t".$row5[8]."\t".$row5[10]."\t".$row5[9]."\t".(($row5[11]==1)?'Yes':'No')."\t".$row5[12]
	."\t".$row5[14]."\t".$row5[13]."\t".(($row5[15]==1)?'Yes':'No')."\t".(($row5[16]==1)?'Yes':'No')."\t".(($row5[17]==1)?'Yes':'No')."\t".$row2[18]."\t".(($row5[20]==1)?'Yes':'No')."\t".$row5[19]."\t".(($row5[21]==1)?'Yes':'No')	;
	//t$csv_output .= "\015\012";


$csv_output .= "\t";



$query6="select * from person_uuid p,child_health f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$result6 = mysql_query($query2); 
 
//$csv_output .= "\015\012";

$row6 = mysql_fetch_array($result6); 
	$csv_output .= "\t".(($row6[7]==1)?'Yes':'No')."\t".$row6[8]."\t".(($row6[9]==1)?'Yes':'No')."\t".$row2[10]."\t".(($row2[11]==1)?'Yes':'No')."\t".$row6[12]
	."\t".(($row6[15]==1)?'Yes':'No')."\t".(($row6[16]==1)?'Yes':'No')."\t".(($row6[17]==1)?'Yes':'No')."\t".(($row6[18]==1)?'Yes':'No')."\t".(($row6[19]==1)?'Yes':'No')."\t".(($row6[20]==1)?'Yes':'No')."\t".(($row6[21]==1)?'Yes':'No')."\t".(($row6[22]==1)?'Yes':'No')."\t".$row6[23]
	."\t".(($row6[24]==1)?'Yes':'No')."\t".$row6[25]."\t".(($row6[26]==1)?'Yes':'No')."\t".$row6[27]."\t".(($row6[28]==1)?'Yes':'No')	;

$csv_output .= "\t";


$query7="select * from person_uuid p,child_behaviour f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$result7 = mysql_query($query7); 
 
//$csv_output .= "\015\012";

$row7 = mysql_fetch_array($result7); 
	$csv_output .= "\t".$row7[7]."\t".(($row7[8]==1)?'Yes':'No')."\t".(($row7[25]==1)?'Yes':'No')."\t".(($row7[10]==1)?'Yes':'No')."\t".(($row7[9]==1)?'Yes':'No')."\t".(($row7[12]==1)?'Yes':'No')
	."\t".(($row7[14]==1)?'Yes':'No')."\t".(($row7[11]==1)?'Yes':'No')."\t".(($row7[16]==1)?'Yes':'No')."\t".(($row7[13]==1)?'Yes':'No')."\t".(($row7[18]==1)?'Yes':'No')."\t".(($row7[15]==1)?'Yes':'No')."\t".(($row7[20]==1)?'Yes':'No')."\t".(($row7[17]==1)?'Yes':'No')."\t".(($row7[22]==1)?'Yes':'No')
	."\t".(($row7[19]==1)?'Yes':'No')."\t".(($row7[23]==1)?'Yes':'No')."\t".(($row7[24]==1)?'Yes':'No')."\t".(($row7[26]==1)?'Yes':'No')."\t".$row7[28]."\t".(($row7[27]==1)?'Yes':'No')	;


$csv_output .= "\t";

$query8="select * from person_uuid p,child_properties f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$result8 = mysql_query($query8); 
 
//$csv_output .= "\015\012";

$row8 = mysql_fetch_array($result8); 
	$csv_output .= "\t".(($row8[7]==1)?'Yes':'No')."\t".(($row8[8]==1)?'Yes':'No')."\t".(($row8[9]==1)?'Yes':'No')."\t".(($row8[10]==1)?'Yes':'No')."\t".(($row8[11]==1)?'Yes':'No')."\t".(($row8[12]==1)?'Yes':'No')."\t".(($row8[13]==1)?'Yes':'No')."\t".$row8[14]	;
	//$csv_output .= "\015\012";


$csv_output .= "\t";


$query3="select * from person_uuid p,child_family_data f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$result3 = mysql_query($query3); 
 

while($row3 = mysql_fetch_array($result3)){ 
	$csv_output .= "\t".get_option_description($row3[8])."\t".$row3[9]."\t".(($row3[10]==1)?'Yes':'No')."\t".(($row3[11]=='-1')?'':$row3[11])."\t".(($row3[12]==1)?'Yes':'No')."\t".$row3[13]
	."\t".$row3[14]	."\t".(($row3[15]==1)?'Yes':'No')	."\t".(($row3[3]==1)?'Yes':'No')	."\t".(($row3[17]==1)?'Yes':'No')	."\t".(($row3[18]==1)?'Yes':'No')	."\t".(($row3[19]==1)?'Yes':'No')."\t".$row3[20]	;
$csv_output .= "\t";
	
}


$csv_output .= "\015\012";




}
}




   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  





?>