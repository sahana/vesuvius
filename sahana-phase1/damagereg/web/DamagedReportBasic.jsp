<!--
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*
* Authors: Viraj S, Upendra H, Chamath E
-->
<%@include file="/admin/accessControl/AccessControl.jsp" %>

 <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
 <html>
 <head>
 <title>:: Sahana ::</title>
 <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">

 <script language='javascript' src='common/popcalendar.js'></script>
 <script language='javascript' src='common/scripts.js'></script>

 <link href="common/style.css" rel="stylesheet" type="text/css">

 <script language="JavaScript" type="text/JavaScript">

    var focusSet=false;
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
          allOk = false;
       }

       if (document.form1.reporterLocation.options[document.form1.reporterLocation.selectedIndex].value == "default") {
          displayText('errormessage', "Please select GSDivision !");
          setFocusObj(document.form1.reporterLocation);
          allOk = false;
       }
       --%>

       if (document.form1.propertyAddress.value == "") {
          displayText('errormessage', "Please enter the Property Address.");
          setFocusObj(document.form1.propertyAddress);
          allOk = false;
       }

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

        if (document.form1.numberPersonsAffected.value!="") {
            if (!isNumeric(document.form1.numberPersonsAffected)) {
               displayText('errormessage', "Please enter number for No. of Person Affected.");
               setFocusObj(document.form1.numberPersonsAffected);
               allOk = false;
            }
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
       focusSet=false;
    }

    function setFocusObj(elem)
    {
        if (focusSet==false) {
            elem.focus();
            focusSet=true;
        }
    }

 </script>

 <jsp:include page="includes/headerReport.inc"></jsp:include>

 </head>

 <body topmargin="0" leftmargin="0" >

 <form name="form1" method="post" action="damagedDetailUpdateAction.do">

   <table>
       <tr>
          <td id="errormessage" colspan=2>&nbsp;</td>
       </tr>
   </table>

   <table cellspacing=0 cellpadding=0 width="100%" border=0 height="565">
     <tbody>

       <tr>
         <td height="505">

	        <!-- Include JSP for Property Information  -->

            <jsp:include page="DamagedPropertyInfo.jsp"></jsp:include>

           <table cellspacing=0 cellpadding=0 width="100%" border=0>
             <tbody>
               <tr>
                 <td class=formTitle background="images/HeaderBG.jpg" colspan=2
                   height=25>Damaged Report - Basic</td>
               </tr>

               <tr>
                 <td colspan=2>
                   <table cellspacing=0 cellpadding=0 width="100%" border=0>
                     <tbody>

                       <!-- Include JSP for Basic Report Information  -->

                       <jsp:include page="DamagedReportStandardInfo.jsp"></jsp:include>


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

         </td>
       </tr>

     </tbody>
   </table>

 </form>

 <jsp:include page="includes/footer.inc"></jsp:include>

 </body>
 </html>