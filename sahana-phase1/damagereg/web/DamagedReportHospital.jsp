<!--
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*
* Authors: Viraj S, Upendra H, Chamath E
-->
<%@include file="/admin/accessControl/AccessControl.jsp" %>

<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<%@ taglib uri="/WEB-INF/sahana.tld" prefix="sahana" %>

<jsp:useBean id="errorList" scope="session" class="java.util.ArrayList" />

 <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
 <html>
 <head>

 <title>:: Sahana ::</title>
 <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">

 <script language='javascript' src='common/popcalendar.js'></script>
 <script language='javascript' src='common/scripts.js'></script>
 <script language='javascript' src='common/dtable.js'></script>


 <link href="common/style.css" rel="stylesheet" type="text/css">

 <script language="JavaScript" type="text/JavaScript">

	var focusSet = false;
	function validateForm() {
	   var allOk = true;

	   clearErrorMsg('errormessage');

	   if (document.form1.ownerPersonRef.value == "") {
	      displayText('errormessage', "Please enter the Property Owner NIC/Passport.");
	      setFocusObj(document.form1.ownerPersonRef);
	      allOk = false;
	   }

	   if (document.form1.ownerName.value == "") {
	      displayText('errormessage', "Please enter the Property Owner Name.");
	      setFocusObj(document.form1.ownerName);
	      allOk = false;
	   }

	   if (document.form1.ownerAddress.value == "") {
	      displayText('errormessage', "Please enter the Property Owner Address.");
	      setFocusObj(document.form1.ownerAddress);
	      allOk = false;
	   }

	   if (document.form1.propertyAddress.value == "") {
	      displayText('errormessage', "Please enter the Property Address.");
	      setFocusObj(document.form1.propertyAddress);
	      allOk = false;
	   }

	   if (document.form1.caseProvinceCode.options[document.form1.caseProvinceCode.selectedIndex].value == "default") {
	      displayText('errormessage', "Please select Province.");
	      setFocusObj(document.form1.caseProvinceCode);
	      allOk = false;
	   }

	   if (document.form1.caseDistrictId.options[document.form1.caseDistrictId.selectedIndex].value == "default") {
	      displayText('errormessage', "Please select District.");
	      setFocusObj(document.form1.caseDistrictId);
	      allOk = false;
	   }

	   <%--
	   if (document.form1.caseDivisionId.options[document.form1.caseDivisionId.selectedIndex].value == "default") {
	      displayText('errormessage', "Please select Division !");
	      setFocusObj(document.form1.caseDivisionId);
	   }

	   if (document.form1.reporterLocation.options[document.form1.reporterLocation.selectedIndex].value == "default") {
	      displayText('errormessage', "Please select GSDivision !");
	      setFocusObj(document.form1.reporterLocation);
	   }
	   --%>

	   if (document.form1.isInsured.value == "1") {
	      if (document.form1.insuranceCompany.options[document.form1.insuranceCompany.selectedIndex].value == "default") {
		 displayText('errormessage', "Please select Insurance Company.");
		 setFocusObj(document.form1.insuranceCompany);
		 allOk = false;
	      }

	      if (document.form1.insurencePolicy.value == "") {
		 displayText('errormessage', "Insurence Policy can't be empty.");
		 setFocusObj(document.form1.insurencePolicy);
		 allOk = false;
	      }

	      if (!isNumeric(document.form1.insurenceValue)) {
		 displayText('errormessage', "Please enter number for Insurence Value.");
		 setFocusObj(document.form1.insurenceValue);
		 allOk = false;
	      }
	   }

	   if (document.form1.contactPersonName.value == "") {
	      displayText('errormessage', "Contact Person Name can't be empty.");
	      setFocusObj(document.form1.contactPersonName);
	      allOk = false;
	   }

	   if (document.form1.contactPersonId.value == "") {
	      displayText('errormessage', "Contact Person NIC/Passport can't be empty.");
	      setFocusObj(document.form1.contactPersonId);
	      allOk = false;
	   }

	   if (document.form1.damageTypeCode.options[document.form1.damageTypeCode.selectedIndex].value == "default") {
	      displayText('errormessage', "Please select Damage Description.");
	      setFocusObj(document.form1.damageTypeCode);
	      allOk = false;
	   }

	   if (!isNumeric(document.form1.estimatedDamageValue)) {
	      displayText('errormessage', "Please enter number for Total Damaged Estimated Value.");
	      setFocusObj(document.form1.estimatedDamageValue);
	      allOk = false;
	   }

	   if (document.form1.numberPersonsAffected.value != "") {
	      if (!isNumeric(document.form1.numberPersonsAffected)) {
		 displayText('errormessage', "Please enter number for No. of Person Affected.");
		 setFocusObj(document.form1.numberPersonsAffected);
		 allOk = false;
	      }
	   }

	   if (document.form1.hospitalName.value == "") {
	      displayText('errormessage', "Hospital Name can't be empty.");
	      setFocusObj(document.form1.hospitalName);
	      allOk = false;
	   }

	   if (document.form1.summaryFacility.value == "") {
	      displayText('errormessage', "Summary of Damage can't be empty.");
	      setFocusObj(document.form1.summaryFacility);
	      allOk = false;
	   }

	   if (document.form1.summaryStatus.value == "") {
	      displayText('errormessage', "Current Status can't be empty.");
	      setFocusObj(document.form1.summaryStatus);
	      allOk = false;
	   }

	   return allOk;
	}

	var erMsg = "<div class ='error'><strong>Please correct the following errors!</strong></div>";
	function displayText(errorDivision, msgText) {
	   var agt = navigator.userAgent.toLowerCase();
	   var NS6 = ((agt.indexOf('netscape6') > 0) && (document.getElementById)) ? true: false;

	   erMsg += "<div class ='error'>" + msgText + "</div>";

	   if (NS6) {
	      document.getElementById(errorDivision).innerHTML = erMsg;
	   } else {
	      document.all[errorDivision].innerHTML = erMsg;
	   }
	}

	function clearErrorMsg(errorDivision) {

	   var agt = navigator.userAgent.toLowerCase();
	   var NS6 = ((agt.indexOf('netscape6') > 0) && (document.getElementById)) ? true: false;

	   if (NS6) {
	      document.getElementById(errorDivision).innerHTML = "&nbsp;";
	   } else {
	      document.all[errorDivision].innerHTML = "&nbsp;";
	   }

	   erMsg = "<div class ='error'><strong>Please correct the following errors!</strong></div>";
	   focusSet = false;
	}

	function setFocusObj(elem) {
	   if (focusSet == false) {
	      elem.focus();
	      focusSet = true;
	   }
	}

    function addDropdownDataToTable() {
       var listObj = document.form1.lstFacilityRecon.options[document.form1.lstFacilityRecon.selectedIndex];

       if (listObj.value=="default") {
          alert("Please select valid Category!");
          return ;
       }

       if (dynaTable.isLabelExist(listObj.text)) {
          alert("Category is already entered!");
          return ;
       }

       if (!isNumeric(document.form1.txtEstCost)) {
          alert("Please enter valid cost!");
          return ;
       }

       dynaTable.setDataToColumnTextType(0, '', '');
       dynaTable.setDataToColumnTextType(1, listObj.text, '');
       dynaTable.setDataToColumnFormType(2, 'hidden', 'reconstructionFacilityName', '', listObj.text, '21');
       dynaTable.setDataToColumnFormType(3, 'text', 'reconstructionEstimatedCost', 'textBox',
          document.form1.txtEstCost.value, '31');
       dynaTable.setLabelRowId(2);
       dynaTable.addNewRow();
    }

    function addCustomDataToTable() {

       if (document.form1.txtOtherFacilityRecon.value == "") {
          alert("Please enter valid Category!");
          return ;
       }

       if (dynaTable.isLabelExist(document.form1.txtOtherFacilityRecon.value)) {
          alert("Category is already entered!");
          return ;
       }

       if (!isNumeric(document.form1.txtOtherEstCost)) {
          alert("Please enter valid cost!");
          return ;
       }

       dynaTable.setDataToColumnTextType(0, '', '');
       dynaTable.setDataToColumnTextType(1, document.form1.txtOtherFacilityRecon.value, '');
       dynaTable.setDataToColumnFormType(2, 'hidden', 'reconstructionFacilityName', '',
          document.form1.txtOtherFacilityRecon.value, '21');
       dynaTable.setDataToColumnFormType(3, 'text', 'reconstructionEstimatedCost', 'textBox',
          document.form1.txtOtherEstCost.value, '31');
       dynaTable.setLabelRowId(2);
       dynaTable.addNewRow();
    }

    var dynaTable;
    function initOnload() {
       dynaTable = new DynamicTable('dynaTable', document.getElementById('tblData'));

      <logic:present name="damageReportDetailObject">
      <logic:iterate id="row" name="damageReportDetailObject" property="damageDetailHospitalEstimatedCosts" >
        <bean:define id="col" name="row"  type="org.damage.business.DamageDetailHospitalEstimatedCost"/>
        document.form1.txtOtherFacilityRecon.value="<%= col.getBudgetDescription() %>";
        document.form1.txtOtherEstCost.value="<%= col.getEstimatedValue() %>";
        addCustomDataToTable();
      </logic:iterate>
      </logic:present>

    }

 </script>


 <jsp:include page="includes/headerReport.inc"></jsp:include>

 </head>

 <body topmargin="0" leftmargin="0" onLoad="javascript:initOnload();" >

 <form name="form1" method="post" action="damagedDetailUpdateAction.do">

           <table>
               <tr>
                  <td id="errormessage" colspan=2>&nbsp;</td>
               </tr>
           </table>
	        <!-- Include JSP for Property Information  -->

            <jsp:include page="DamagedPropertyInfo.jsp"></jsp:include>

           <table cellspacing=0 cellpadding=0 width="100%" border=0>
             <tbody>
               <tr>
                 <td class=formTitle background=images/HeaderBG.jpg colspan=2
                   height=25>Damaged Report - Hospital</td>
               </tr>
               <tr>
                 <td colspan=2>
                   <table cellspacing=0 cellpadding=0 width="100%" border=0 height="408">
                     <tbody>

                       <!-- Include JSP for Basic Report Information  -->

                       <jsp:include page="DamagedReportStandardInfo.jsp"></jsp:include>

                       <tr>
                         <td colspan=2 height="16">
                         <hr>
                         </td>
                       </tr>
                       <tr><td height="1"></td><td height="1"></td>
                       </tr>
                       <tr>
                         <td class="formText" height="13"><strong>Current
                         Details</strong></td>
                         <td height="13"></td>
                       </tr>
                       <tr><td height="1"></td><td height="1"></td>
                       </tr>
                       <tr><td height="1"></td><td height="1"></td>
                       </tr>
                               <tr>
                         <td class="formText" height="30">Hospital Name</td>
                         <td height="30">
                            <input type="text" class=textBox name="hospitalName"
                                value="<bean:write name="damageReportDetailObject" property="hospitalName" scope="session" ignore="true" />">
                            <small><font color=red>*</font></small>
                         </td>
                               </tr>
                               <tr>
                         <td class="formText" height="30">Summary of&nbsp; Damage </td>
                         <td height="30">
                            <textarea class=textBox name="summaryFacility" cols=61
                                rows="2"><bean:write name="damageReportDetailObject" property="summaryFacility" scope="session" ignore="true" /></textarea>
                                <small><font color=red>*</font></small>
                         </td>
                               </tr>
                       <tr><td height="1"></td><td height="1"></td>
                       </tr>

                       <tr>
                         <td class="formText" height="30">Current Status</td>
                         <td height="30">
                            <textarea class=textBox name="summaryStatus" cols=61
                                rows="2"><bean:write name="damageReportDetailObject" property="summaryStatus" scope="session" ignore="true" /></textarea>
                            <small><font color=red>*</font></small>
                         </td>
                       </tr>

                     <tr>
                         <td colspan=2 height="16">
                         <hr>
                         </td>
                     </tr>
                   <tr>

                <td colspan=2 height="16"><table width="100%">

                     <tr>
                              <td width="20%" height="13" class=formText><strong>Reconstruction
                         Details</strong>
                         </td>
                              <td width="25%" >&nbsp;
                         </td>
                              <td width="10%" >&nbsp;
                         </td>
                              <td width="20%" >&nbsp;
                         </td>
                              <td >&nbsp;
                         </td>
                     </tr>
                     <tr>

                        <td class="formText" height="19">Facility of Reconstruction
                        </td>
                        <td><sahana:DamageCustomTextDropdown
                                name="lstFacilityRecon"
                                styleClass="textBox"
                                onChangeJS="document.form1.txtEstCost.value='';"
                                defaultValue="default"
                                customString="reconstruction"/>
                        </td>
                              <td class="formText" height="19">Estimated Cost
                        </td>
                              <td height="19">
                            <input name="txtEstCost" class=textBox size="31" value="">
                        </td>
                              <td align=left height="19">
                            <input name="button" type="button" class="buttons" onClick="addDropdownDataToTable()" value="Add">
                        </td>
                     </tr>

                     <tr>

                              <td class="formText" height="21" >Other Facility of Reconstruction
                        </td>
                              <td height="21" >

                           <input name="txtOtherFacilityRecon" class=textBox size="31" value="">
                        </td>
                              <td class="formText" height="21">Estimated Cost
                        </td>
                              <td height="21" >
                            <input name="txtOtherEstCost" class=textBox size="31" value="">
                        </td>
                              <td align=left height="21">
                            <input class=buttons onClick="addCustomDataToTable()" type=button value="Add"   name=Submit232>
                        </td>
                     </tr>

                   </table>
                   </td>
                   </tr>

                    <tr valign="top">
                    <td colspan=2 >
                        <br>
						<table id="tblData" width="50%" border="0" cellpadding="0" cellspacing="0">
                            <tr>
                              <td width="1%" >&nbsp;</td>
                              <td width="60%" align="center" class="tableUp"><strong>Facility of Reconstruction</strong></td>
                              <td width="37%" align="center" valign="middle" class="tableUp"><strong>Estimated Cost</strong></td>
                              <td align="center" valign="middle" class="tableUp">&nbsp;</td>
                            </tr>
                        </table>
                        <br>
                      </td>
                     </tr>

		      <tr>
                         <td colspan=2 height="16">
                         <hr>
                         </td>
                     </tr>

                     <tr>
                         <td class=formText height="21">&nbsp;</td>
                         <td height="21">

                             <tr>
                               <td height="50" colspan="2" align=center>
                         			   		<input class="buttons2" type="submit" value="   Update   "  onClick="javascript:return validateForm();" name=Submit24>
                                         &nbsp;&nbsp;
                                         <input class="buttons2" onClick="location.href='damagedDetailCancelAction.do'" type="button" value="  Cancel  "  name="cancel">
                                  </td>
                             </tr>
                        </td>
                     </tr>

                     </tbody>
                   </table>
                  </td>
               </tr>
             </tbody>

   </table>
 </form>

 <jsp:include page="includes/footer.inc"></jsp:include>

 </body>
 </html>