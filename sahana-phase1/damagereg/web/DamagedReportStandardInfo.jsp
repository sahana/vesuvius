<!--
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*
* Authors: Viraj S, Upendra H, Chamath E
-->
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<%@ taglib uri="/WEB-INF/sahana.tld" prefix="sahana" %>

    <script language="JavaScript" type="text/JavaScript">

        function setRelocateValue(objCheck) {
           if (objCheck.checked) {
              objCheck.value = "1";
           } else {
              objCheck.value = "0";
           }
        }

    </script>

    <tr>
      <td class=formText width="20%"><strong>Damage / Impact Details</strong></td>
      <td>&nbsp;</td>
    </tr>
    <tr>
     <td class=formText width="20%" height="19">Contact Person Name</td>
     <td height="19">
        <input class=textBox size="61" name="contactPersonName"
            value="<bean:write name="damageReportObject" property="contactPersonName" scope="session" ignore="true" />">
        &nbsp;<small><font color=red>*</font></small>
     </td>
    </tr>
    <tr><td height="1"></td><td height="1"></td>
    </tr>
    <tr>
     <td class=formText height="19">Contact Person NIC/Passport</td>
     <td height="19">
        <input class=textBox size="61" name="contactPersonId"
            value="<bean:write name="damageReportObject" property="contactPersonId" scope="session" ignore="true" />">
        &nbsp;<small><font color=red>*</font></small>
     </td>
    </tr>
    <tr><td height="1"></td><td height="1"></td>
    </tr>

    <tr>
      <td width="20%" class="formText">Damage Description</td>
      <td>
        <sahana:SahanaReferenceDropdown
            showDamageType="true"
            name="damageTypeCode"
            styleClass="selectBoxes"
            defaultValue="default" />
         <small><font color=red>*</font></small>
      </td>
    </tr>
    <!-- reset values from damageReport bean if available -->
    <script language="JavaScript" type="text/JavaScript">
       setSelectStatus(document.form1.damageTypeCode,'<bean:write name="damageReportObject" property="damageTypeCode" scope="session" ignore="true" />');
    </script>

    <tr><td height="1"></td><td height="1"></td>
    </tr>
    <tr>
     <td class=formText height="19">Total Damaged Estimated Value</td>&nbsp;
     <td height="19">
        <input class=textBox size="61" name="estimatedDamageValue"
            value="<bean:write name="damageReportObject" property="estimatedDamageValue" scope="session" ignore="true" />">
        &nbsp;<small><font color=red>*</font></small>
     </td>
    </tr>
    <tr><td height="1"></td><td height="1"></td>
    </tr>
    <tr>
     <td class="formText" height="19">No. of Person Affected </td>
     <td height="19">
        <input class=textBox name="numberPersonsAffected"
            value="<bean:write name="damageReportObject" property="numberPersonsAffected" scope="session" ignore="true" />" size="9" >
     </td>
    </tr>

    <tr>
      <td class=formText height="20">Is Relocated? </td>
      <td height="20"><small>
         <input type="checkbox" name="isRelocate" onClick="setRelocateValue(this)" >Yes </small>
      </td>
    </tr>
    <logic:present name="damageReportObject">
       <logic:equal value="true" name="damageReportObject" property="isRelocate" scope="session" >
            <!-- reset values from damageReport bean if available -->
            <script language="JavaScript" type="text/JavaScript">
               document.form1.isRelocate.checked=true;
               setRelocateValue(document.form1.isRelocate);
            </script>
       </logic:equal>
    </logic:present>

    <tr>
      <td height="1"></td><td height="1"></td>
    </tr>