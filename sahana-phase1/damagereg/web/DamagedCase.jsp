<!--
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*
* Authors: Viraj S, Upendra H, Chamath E
-->
<%@ page language="java" import="org.damage.business.DamageReport,
                                 org.damage.common.selectionhierarchy.TreeElement,
                                 org.damage.business.DamageCase,
                                 org.damage.util.SessionUtils,
                                 org.damage.common.Globals,
                                 java.util.Set,
                                 java.util.Iterator,
                                 org.damage.common.selectionhierarchy.ClassificationBrowser"  %>

<%@include file="/admin/accessControl/AccessControl.jsp" %>

<%@ taglib uri="/WEB-INF/sahana.tld" prefix="sahana" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>

<jsp:useBean id="errorList" scope="session" class="java.util.ArrayList" />

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>

<title>:: Sahana ::</title>

<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">

<script language='javascript' src='common/popcalendar.js'></script>
<script language='javascript' src='common/dtree.js'></script>
<script language='javascript' src='common/scripts.js'></script>

<link href="common/style.css" rel="stylesheet" type="text/css">
<link href="common/dtree.css" rel="stylesheet" type="text/css">

<script language="JavaScript" type="text/JavaScript">

    var focusSet=false;
    function validateForm() {
       var allOk = true;
       var focusObj;

       clearErrorMsg('errormessage');

       if (document.form1.reportedDate.value == "") {
          displayText('errormessage', "Please enter the Report Date.");
          setFocusObj(document.form1.reportedDate);
          allOk = false;
       }

       if (document.form1.damageDate.value == "") {
          displayText('errormessage', "Please enter the Damaged Date.");
          setFocusObj(document.form1.damageDate);
          allOk = false;
       }

       if (document.form1.causeOfDamage.value == "") {
          displayText('errormessage', "Cause of Damage can't be empty.");
          setFocusObj(document.form1.causeOfDamage);
          allOk = false;
       }

       if (document.form1.reporterNicPassportId.value == "") {
          displayText('errormessage', "Reporter NIC/Passport No. can't be empty.");
          setFocusObj(document.form1.reporterNicPassportId);
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

       if (document.form1.institutionId.options[document.form1.institutionId.selectedIndex].value == "default") {
          displayText('errormessage', "Please select Authorization Institution.");
          setFocusObj(document.form1.institutionId);
          allOk = false;
       }

       if (document.form1.authOfficerId.value == "") {
          displayText('errormessage', "Authorization Officer Name can't be empty.");
          setFocusObj(document.form1.authOfficerId);
          allOk = false;
       }

       if (document.form1.referenceNumber.value == "") {
          displayText('errormessage', "Authorization Officer Reference Number can't be empty.");
          setFocusObj(document.form1.referenceNumber);
          allOk = false;
       }

       return allOk;
    }

    function goToIndexPage() {
       location.href = "<%= request.getContextPath() %>/Welcome.jsp";
    }

    function updateCaseData() {
       if (validateForm) {
           document.form1.action="damagedCaseUpdateAction.do";
           return true;
       }
       else return false;
    }

    function checkSelNode() {
       if (!validateForm())
          return false;

       if (document.form1.propertyTypeID.value == "") {
          alert("Please select a Property Type to continue.");
          clearErrorMsg('errormessage');
          return false;
       }

       return true;
    }

    var erMsg = "<div class ='error'><strong>Please correct the following errors!</strong></div>";
    function displayText(errorDivision, msgText) {
       var agt = navigator.userAgent.toLowerCase();
       var NS6 = ((agt.indexOf('netscape6') > 0) && (document.getElementById)) ?
          true: false;

       erMsg += "<div class ='error'>" + msgText + "</div>";

       if (NS6) {
          document.getElementById(errorDivision).innerHTML = erMsg;
       } else {
          document.all[errorDivision].innerHTML = erMsg;
       }
    }

    function clearErrorMsg(errorDivision) {
       var agt = navigator.userAgent.toLowerCase();
       var NS6 = ((agt.indexOf('netscape6') > 0) && (document.getElementById)) ?
          true: false;

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

    function clearForm()
    {
        document.form1.reset();

       // clear default values
       document.form1.reportedDate.value="";
       document.form1.damageDate.value="";
       document.form1.causeOfDamage.value="";
       document.form1.reporterName.value="";
       document.form1.reporterTelNo.value="";
       document.form1.reporterAddress.value="";
       document.form1.reporterNicPassportId.value="";
       document.form1.authOfficerId.value="";
       document.form1.referenceNumber.value="";

    }

 </script>

 <jsp:include page="SahanaLocations.jsp"></jsp:include>

</head>


<body topmargin="0" leftmargin="0"  >

<jsp:include page="includes/header.inc"></jsp:include>

<form name="form1" method="post" action="damagedCaseAction.do">

<table cellspacing=0 cellpadding=0 width="100%" border=0>
  <tbody>
    <tr>
      <td colspan="2">
     <table cellspacing=0 cellpadding=0 width="100%" border=0>
          <tbody>
            <tr align=left>
              <td class=statusBar nowrap background=images/BannerBG.jpg>
                   <img src="images/Tab.gif">
               </td>
              <td class=statusBar nowrap background=images/BannerBG.jpg>
                   <a style="TEXT-DECORATION: none"
                     href="http://relief.cno.gov.lk/erms/Search_Request.jsp">
                     <font color=#000000>&nbsp;&nbsp;Search Request</font>
                   </a>&nbsp;&nbsp;
               </td>
              <td class=statusBar nowrap background=images/BannerBG.jpg>
                  <img src="images/Tab.gif">
               </td>
              <td class=statusBar align=right
                  background=images/BannerBG.jpg bgcolor=#000099 height=23>
                  <a style="TEXT-DECORATION: none"
                  href="http://relief.cno.gov.lk/erms/Logoff.jsp">
                  <font color=#000000>Log off&nbsp;&nbsp;&nbsp;&nbsp;</font>
                  </a>
               </td>
            </tr>

          </tbody>
         </table></td>
    </tr>



    <tr>
      <td colspan=2 class="formText">&nbsp;</td>
    </tr>
    <tr>
      <td colspan=2><strong>Organization : Lanka
                           Software Foundation &nbsp;&nbsp;User : sanjiva
                           &nbsp;&nbsp;Date : 2005-01-20</strong></td>
    </tr>
    <tr>
      <td colspan=2 class="formText">&nbsp;</td>
    </tr>
    <tr>
      <td id="errormessage" colspan=2>&nbsp;</td>
    </tr>
    <tr>
      <td colspan=2 class="formText">&nbsp;</td>
    </tr>



    <tr>
      <td class=formTitle background=images/HeaderBG.jpg colspan=2
                 height=25>Damaged Properties - Case Information</td>
    </tr>

    <tr>

      <td width="35%">&nbsp;</td>
      <td >&nbsp;</td>
    </tr>

    <tr>

      <td colspan=2></td>
    </tr>






  <tr>


      <td class="formText"><strong>Case Detail</strong></td>
    <td>&nbsp;</td>
  </tr>




  <tr>


    <td colspan=2>
                 <table cellspacing=0 cellpadding=0 width="100%" border=0>


        <tbody>
          <tr>

            <td class=formText width="20%">Reported Date	</td>
            <td>    <input class=textBox name="reportedDate" readonly="true" value="<bean:write name="damageCaseObject" property="reportedDate" scope="session" ignore="true" />" size="20">
                      &nbsp;<small><font color="red">*</font></small>
                              <img src="images/calendar.gif" onClick="popUpCalendar(this, document.getElementById('reportedDate'), 'yyyy-mm-dd')" width="18" height="17"/>
             </td>
          </tr>


          <tr>


            <td class=formText>Damage Occurrence Date </td>
            <td>
                           <input class=textBox name="damageDate" readonly="true" value="<bean:write name="damageCaseObject" property="damageDate" scope="session" ignore="true" />" size="20" />
                      &nbsp;<small><font color="red">*</font></small>

                               <img src="images/calendar.gif" onClick="popUpCalendar(this, document.getElementById('damageDate'), 'yyyy-mm-dd')" width="18" height="17"/>
                            </td>
          </tr>


          <tr>



            <td class=formText>Cause of Damage </td>
            <td>
                          <input class=textBox size="75" name="causeOfDamage" value="<bean:write name="damageCaseObject" property="causeOfDamage" scope="session" ignore="true" />">
                          &nbsp;<small><font color=red>*</font></small>
                       </td>
          </tr>
                   </table>
  <tr>


    <td colspan=2>
                       <hr>
                       </td>
  </tr>


  <tr>


    <td class="formText"><strong>Reporter Detail</strong></td>
    <td>&nbsp;</td>
  </tr>



  <tr>


    <td colspan="2">
                  <table cellspacing=0 cellpadding=0 width="100%" border=0>


        <tbody>


          <tr>


            <td width="20%" class="formText">Reporter NIC /Passport No. </td>
            <td>
                          <input class=textBox name=reporterNicPassportId value="<bean:write name="damageCaseObject" property="reporterNicPassportId" scope="session" ignore="true" />" size="30">
                         &nbsp;<small><font color=red>*</font></small>
                       </td>
          </tr>


          <tr>


            <td class="formText">Reporter Name </td>
            <td>
                          <input class=textBox name=reporterName value="<bean:write name="damageCaseObject" property="reporterName" scope="session" ignore="true" />" size="30">
                       </td>
          </tr>


          <tr>


            <td class="formText">Reporter Phone Number </td>
            <td >
                          <input class=textBox name=reporterTelNo value="<bean:write name="damageCaseObject" property="reporterTelNo" scope="session" ignore="true" />" size="30">
                       </td>
          </tr>


          <tr>


            <td class="formText">Reporter Address </td>
            <td>
                          <textarea class=textBox name=reporterAddress cols=50 rows="2"><bean:write name="damageCaseObject" property="reporterAddress" scope="session" ignore="true" /></textarea>
                       </td>
          </tr>


          <tr>



            <td class="formText">&nbsp;</td>
            <td>&nbsp;</td>
          </tr>


          <tr>
              <td align="left" class="formText" type="submit">Province </td>
              <td valign="top" >
                            <sahana:SahanaReferenceDropdown
                                showLocations="true"
                                name="caseProvinceCode"
                                styleClass="selectBoxes"
                                onChangeJS="listDistrict();"
                                defaultValue="default" />
                          &nbsp;<small><font color=red>*</font></small>
              </td>
            </tr>


            <tr>


              <td  align="left" class="formText" type="submit">District </td>
              <td valign="top" >
							<select name="caseDistrictId" class="selectBoxes" onChange="listDivisions();" disabled >
                              <option value="default" selected>&lt;select&gt;</option>
							</select>
                          &nbsp;<small><font color=red>*</font></small>
						   </td>
            </tr>


            <tr>


              <td  align="left" class="formText" type="submit">Division </td>
              <td valign="top" >
						<select name="caseDivisionId" class="selectBoxes" onChange="listGSDivisions();" disabled >
                              <option value="default" selected>&lt;select&gt;</option>
 					    </select>
					   </td>
            </tr>


            <tr>


              <td  align="left" class="formText" type="submit">GS Division </td>
              <td valign="top" >
                          <select name="caseGSDivisionId" class="selectBoxes" disabled >
                              <option value="default" selected>&lt;select&gt;</option>
                          </select>
                          <input type="hidden" name="reporterLocation" value=""/>
                         </td>
            </tr>


          </tbody>

                            <!-- reset values from damageCase bean if available -->
                            <script language="JavaScript" type="text/JavaScript">
                               setSelectStatus(document.form1.caseProvinceCode,'<bean:write name="damageCaseObject" property="reporterProvince" scope="session" ignore="true" />');
                               listDistrict();
                               setSelectStatus(document.form1.caseDistrictId,'<bean:write name="damageCaseObject" property="reporterDistrict" scope="session" ignore="true" />');
                               listDivisions();
                               setSelectStatus(document.form1.caseDivisionId,'<bean:write name="damageCaseObject" property="reporterDivision" scope="session" ignore="true" />');
                               listGSDivisions();
                               setSelectStatus(document.form1.caseGSDivisionId,'<bean:write name="damageCaseObject" property="reporterGSDivision" scope="session" ignore="true" />');
                            </script>


              </table>
    <tr>


      <td colspan=2>
                         <hr>
                         </td>
    </tr>



    <tr>


    <td class="formText"><strong>Authorization Details</strong>
                       </td>
    <td>&nbsp;</td>
  </tr>



  <tr>


    <td colspan="2">
             <table cellspacing=0 cellpadding=0 width="100%" border=0>


          <tbody>


            <tr>


              <td width="20%" class="formText">Institution </td>
              <td>
                  <sahana:SahanaReferenceDropdown
                      showInstitutions="true"
                      name="institutionId"
                      styleClass="selectBoxes"
                      defaultValue="default" />
                   <small><font color=red>*</font></small>
                    <!-- reset values from damageCase bean if available -->
                    <script language="JavaScript" type="text/JavaScript">
                       setSelectStatus(document.form1.institutionId,'<bean:write name="damageCaseObject" property="institutionId" scope="session" ignore="true" />');
                    </script>
               </td>
            </tr>


            <tr>


              <td class="formText">Officer </td>
              <td>
                          <input name="authOfficerId" class="textBox" size="50" value="<bean:write name="damageCaseObject" property="authOfficerId" scope="session" ignore="true" />"> <small><font color=red>*</font></small>
                       </td>
            </tr>


            <tr>


              <td class="formText">Ref. Number </td>
              <td>
                          <input class="textBox" name="referenceNumber" value="<bean:write name="damageCaseObject" property="referenceNumber" scope="session" ignore="true" />" size="30" >
                       <small><font color=red>*</font></small>
               </td>
            </tr>





          </tbody>
                 </table>

                 </td></tr>

  <tr>
    <td height="50" colspan="2" align=left>
                &nbsp;&nbsp;<input class="buttons" type="button" value="   Clear Data   "   name=clear onClick="clearForm();">
       </td>
  </tr>




  <tr>

    <td  background="images/HeaderBG.jpg">&nbsp;</td>
    <td  class=formTitle height=25 align="left" background="images/HeaderBG.jpg" >Please Select Property Type
            </td>
  </tr>


  <tr>


    <td>&nbsp;</td>
    <td>
          <br>

          <div align="left" class="boder" id="Layer1" style="height:250px; width:300px; z-index:1; overflow: auto;">

              <script type="text/javascript">
                  <!--
                  <sahana:SelectionHierarchyTree />
                  //-->
              </script>

              </div></td>
  </tr>
  <tr>
    <td>	<input type="hidden" name="propertyTypeID" value="" ></td>
    <td align="left" height="30" id="tdPath">&nbsp;</td>
  </tr>
  <tr align="center">
    <td height="30" colspan=2 >
      <input class="buttons" type="submit" value="    Next Page  &gt;&gt;"   name=Submit242 onClick="javascript:return checkSelNode();">
      <br><br>
    </td>
  </tr>


  <tr>
    <td class=formTitle background=images/HeaderBG.jpg colspan=2
                 height=25>Damaged Property Reports </td>
  </tr>
  <tr>
    <td height="5" colspan=2>&nbsp; </td>
  </tr>
  <tr>
      <td class=pageBg colspan=2>
          <div id=Layer1 style="Z-INDEX: 1; OVERFLOW: auto; WIDTH: 100%;">
          <table width="100%" border=0 cellpadding=0 cellspacing=0 class="boder">
            <tbody>
              <tr>
                <td  width="20%" height="20" class=tableUp>Property Type</td>
                <td  width="20%" height="20" class=tableUp>Location</td>
                <td  width="20%" height="20" class=tableUp>Severity</td>
                <td  width="20%" height="20" class=tableUp>Est. Damage Value</td>
                <td  height="20" class=tableUp>Operations</td>
              </tr>

              <logic:present name="reportObject">

                  <logic:iterate id="row" name="reportObject" property="currentReport" >
                        <bean:define id="col" name="row"  type="java.util.Hashtable"/>
                        <tr class="formText">
                            <td height="20"><%= col.get("Property Type") %></td>
                            <td height="20"><%= col.get("Location") %></td>
                            <td height="20"><%= col.get("Severity") %></td>
                            <td height="20"><%= col.get("Estimated Damage Value") %></td>
                            <td height="20">
                              <a href="damagedDetailEditAction.do?ReportId=<%=col.get("ReportId")%>">Edit</a>&nbsp;&nbsp;<a>|</a>&nbsp;&nbsp;
                              <a href="damagedDetailRemoveAction.do?ReportId=<%=col.get("ReportId")%>">Remove</a>&nbsp;&nbsp;
                            </td>
                        </tr>
                  </logic:iterate>

              </logic:present>

            </tbody>
          </table>
        </div></td>
    </tr>


  <tr>
    <td height="50" colspan="2" align=center>
              <logic:present name="reportObject">
                <input class="buttons2" type="submit" value="   Save   " name=Submit24 onClick="return updateCaseData()">
              </logic:present>
              <logic:notPresent name="reportObject">
                <input class="buttons2" type="button" value="   Save   " name="Submit24" disabled>
              </logic:notPresent>
              &nbsp;&nbsp;
              <input class="buttons2" onClick="goToIndexPage()" type="button" value="  Cancel  "  name="clearCase">
       </td>
  </tr>



  <tr>
    <td colspan="2" align=center>&nbsp;</td>
  </tr>

  </tbody>

</table>
 </form>
<jsp:include page="includes/footer.inc"></jsp:include>

</body>
</html>
