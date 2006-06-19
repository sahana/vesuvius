<script language="JavaScript">


function controlbutton(buttonname,componentname)
{
//alert('bname.name');
if(componentname.disabled)
{
componentname.disabled=false;

buttonname.value='Select';

}
else
{
componentname.disabled=true;

buttonname.value='Deselect';
}
}


</script>
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

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function shn_cps_query_results()
{
global $conf;
$server= $conf['servername'] ;
$btngender=$_POST['btngender'];
$opt_gender=$_POST['opt_gender'];

$chkbirth=$_POST['chkbirth'];

$btnagegroup=$_POST['btnagegroup'];
$opt_age_group=$_POST['opt_age_group'];
$chkcrs=$_POST['chkcrs'];

$btndatereg=$_POST['btndatereg'];
$opt_year=$_POST['opt_year'];
$opt_month=$_POST['opt_month'];
$opt_date=$_POST['opt_date'];
$chksatsu=$_POST['y'];
$chksbefsu=$_POST['x'];
//print 'val is'.$chksatsu.$chksbefsu; 
$btncenter=$_POST['btncenter'];
$opt_child_center_names=$_POST['opt_child_center_names'];
$chk_lost_parents=$_POST['chklostparents'];
$btndes=$_POST['btndes'];
$nch=$_POST['nch'];
$nfm=$_POST['nfm'];



$chkdisability=$_POST['chkdisability'];
$q1=$_POST['q1'];
$q2=$_POST['q2'];
$q3=$_POST['q3'];
$q4=$_POST['q4'];
$q5=$_POST['q5'];
$q6=$_POST['q6'];
$q7=$_POST['q7'];
$q8=$_POST['q8'];
$q9=$_POST['q9'];
$q10=$_POST['q10'];
$q11=$_POST['q11'];
$q12=$_POST['q12'];
$q13=$_POST['q13'];
$q14='1';//todo remove q14 column
$q15=$_POST['q15'];
$q16=$_POST['q16'];
$q17=$_POST['q17'];
$q18=$_POST['q18'];

$iq1=$_POST['iq1'];
$iq2=$_POST['iq2'];
$iq3=$_POST['iq3'];
$iq4=$_POST['iq4'];
$iq5=$_POST['iq5'];
$iq6=$_POST['iq6'];
$iq7=$_POST['iq7'];
//$iq8=$_POST['iq8'];

//print 'gender is'.$opt_gender;



$text='bg='.$btngender.'&ge='.$opt_gender.'&bc='.$chkbirth.'&ba='.
$btnagegroup.'&ag='.$opt_age_group.'&crs='.$chkcrs.'&br='.$btndatereg.'&bm='.$opt_month.'&bd='.$opt_date.
'&atsu='.$chksatsu.'&btsu='.$chksbefsu.'&bcen='.$btncenter.'&cn='.$opt_child_center_names.'&lp='.$chk_lost_parents.
'&btndes='.$btndes.'&nch='.$nch.'&nfm='.$nfm.'&disab='.$chkdisability.'&q1='.$q1.'&q2='.$q2
.'&q3='.$q3.'&q4='.$q4.'&q5='.$q5.'&q6='.$q6.'&q7='.$q7.'&q8='.$q8.'&q9='.$q9.'&q10='.$q10.'&q11='.$q11
.'&q12='.$q12.'&q13='.$q13.'&q14='.$q14.'&q15='.$q15.'&q16='.$q16.'&q17='.$q17.'&iq1='.$iq1.'&iq2='.$iq2

.'&iq3='.$iq3.'&iq4='.$iq4.'&iq5='.$iq5.'&iq6='.$iq6.'&iq7='.$iq7.'&year='.$opt_year.'&q18='.$q18;




?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/view_excel.php?<?php print $text?>">View Excel</a>
<?php


}


function getdatafrom($sql)
{
global $global;
$db = $global['db'];

$res1 = $db->Execute($sql);
$record_count=$res1->RecordCount();


while(!$res1->EOF)
{
$childhealth[$i][$j++]=$res1->fields[5];//childcode
$childhealth[$i][$j++]=$res1->fields[6];//center_code
$childhealth[$i][$j++]=($res1->fields[7]==1)?'Yes':'No';//
$childhealth[$i][$j++]=($res1->fields[9]==1)?'Yes':'No';//
$childhealth[$i][$j++]=($res1->fields[11]==1)?'Yes':'No';//
$childhealth[$i][$j++]=($res1->fields[13]==1)?'Yes':'No';//
$childhealth[$i][$j++]=($res1->fields[15]==1)?'Yes':'No';//
$i++;
$j=0;
$res1->MoveNext();
}
}


function shn_cps_query_view()
{

shn_form_fopen("queryview",null);

shn_form_fsopen("Query View");

shn_form_hidden(array('seq'=>'res'));

?>






<table border='5'>
  <tr>
    <td>
  
   
      <button name="btngender" foreground=green onclick=controlbutton(btngender,opt_gender)> Select</button></p>
  
	  </td>

    <td>
      <?php
		  shn_form_opt_select("opt_gender","Gender");
		 ?>
		
    </td>
    <td >
    
    
     
     <?php 
     shn_form_checkbox("Child have birth Certificate",chkbirth,'',array('value'=>1));
     ?>
		
		  <p>&nbsp;</td>
  </tr>
  
  
   <tr>
    <td>
    
      <button name="btnagegroup" onclick="controlbutton(btnagegroup,opt_age_group)">Select</button></p>
    
    </td>
 
    <td>
    
      <?php
       shn_form_opt_select("opt_age_group","Age Group");
      ?>
       </td>
    <td>
     <?php 
     shn_form_checkbox("Child Registered in School",chkcrs,'',array('value'=>1));
     ?>
    </td>
  </tr>
  
  
  
  
  
  
  <tr>
  
    <td>
          <button name="btndatereg" onclick="controlbutton(btndatereg,opt_month),controlbutton(btndatereg,opt_date),controlbutton(btndatereg,opt_year)">Select</button></p>
        </td>
   
    <td>
    
        <?php
        shn_form_label('Date registered','');
       print "<br/>";
       shn_form_opt_select("opt_year","Year&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp  ");
       print "<br/>";
			 shn_form_opt_select("opt_month","Month&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp  ");
       print "<br/>";
       shn_form_opt_select("opt_date","DateofMonth&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
      ?>
    
    
    </td>
    <td >
      
      <?php 
     shn_form_checkbox("Child Attending school before tsunami",x,'',array('value'=>1));
     shn_form_checkbox("Child Attending school after tsunami",y,'',array('value'=>1));
    // shn_form_checkbox("Child Registered in School",chkcrs,'',array('value'=>1));
     //shn_form_checkbox("xChild Registered in School",x,'',array('value'=>1));
     
		 ?>
        </td>
  </tr>
  
  
  <tr>
    <td >
   <p>
      <button name="btncenter" onclick="controlbutton(btncenter,opt_child_center_names)">Select</button></p>
    
    </td>
        <td >
    
    
      <?php
      shn_form_opt_select("opt_child_center_names","Child Center&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
      ?>
    
    </td>
    <td>
     <?php 
     shn_form_checkbox("Child lost his parents",chklostparents,'',array('value'=>1));
     ?>
    </td>
  </tr>
  
  
  <tr>
    <td>
    
      <button name="btndes" onclick="controlbutton(btndes,nch),controlbutton(btndes,nfm)">Select</button></p>
    
    </td>
   
    <td width=50%>
    
      <?php
       shn_form_label('Description','');
       shn_form_text('Name of the child&nbsp&nbsp&nbsp','nch','size="30"');
       shn_form_text('Name of the Family','nfm','size="30"');
       
      
      ?>

    </td>
    <td width=50%>
     <?php 
     shn_form_checkbox("Child with disability",chkdisability,'',array('value'=>1));
     
     
     ?>
		</td>
  </tr>
  
  
 <tr>
    <td>
   <p>Child with mantel upset?</p>
	 
	   </td>
    
    <td>
     <?php
		 shn_form_checkbox("Have difficulty leaving the house",q1,'',array('value'=>1));
     shn_form_checkbox("Show signs of losing appetite",q2,'',array('value'=>1));
     shn_form_checkbox("Have more sleep difficulties",q3,'',array('value'=>1));
     shn_form_checkbox("Show signs of being afraid of strangers",q4,'',array('value'=>1));
    shn_form_checkbox("Have recurrent dreams",q5,'',array('value'=>1));
     shn_form_checkbox("Less interested in education",q6,'',array('value'=>1));
     shn_form_checkbox("Difficult to Control emotions",q7,'',array('value'=>1));
     
     shn_form_checkbox("Show signs of aggression",q8,'',array('value'=>1));
     
		 ?>
    
    </td>
    <td>
    <?php
    shn_form_checkbox("Afraid of another tsunami",q9,'',array('value'=>1));
     shn_form_checkbox("Often cry and look sad",q10,'',array('value'=>1));
     shn_form_checkbox("Never want to talk",q11,'',array('value'=>1));
     shn_form_checkbox("Playing or acting on Tsunami",q12,'',array('value'=>1));
     shn_form_checkbox("Seem more shy",q13,'',array('value'=>1));
    // shn_form_checkbox("Avoid talking on tsunami",q14,'',array('value'=>1));
     shn_form_checkbox("Often distracted",q15,'',array('value'=>1));
     shn_form_checkbox("Have tsunami pictures in mind",q16,'',array('value'=>1));
     shn_form_checkbox("Seek more attentions from adults",q17,'',array('value'=>1));
     
     shn_form_checkbox("Have more problems in concentrating or remembering",q18,'',array('value'=>1));
		 ?>
    </td>
  </tr>
   
  
   <tr>
    <td >
       
  <p>Child with specific issues</p>
     
		 
   
	 
	  
    </td>
   <td>
    <?php
    shn_form_checkbox("Seems to be a beeting child",iq1,'',array('value'=>1));
     shn_form_checkbox("Is victim of sexualabuse",iq2,'',array('value'=>1));
     shn_form_checkbox("Seems to be a neglecting child",iq3,'',array('value'=>1));
     shn_form_checkbox("TDH to follow up",iq4,'',array('value'=>1));
    
     
		 ?>

        </td>
    <td>
        <?php
        
    shn_form_checkbox("Victim of child traficcing",iq5,'',array('value'=>1));
    shn_form_checkbox("Victim of domestic violence",iq6,'',array('value'=>1));
    shn_form_checkbox("Drink Alcohol",iq7,'',array('value'=>1));
     
		 ?>

    </td>
  </tr>  
    <tr>
    <td>

   
		</td>
    <td>
       
	<B> <?php shn_form_submit("View Data");?></B>
	&nbsp	&nbsp	 	&nbsp	&nbsp
		<B></B>	    
				</td>
    <td>
 

	  



    </td>
  </tr>
    
</table>



  <?php
shn_form_close();
}
?>

