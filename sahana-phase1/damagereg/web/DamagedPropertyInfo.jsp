<!--
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*
* Authors: Viraj S, Upendra H, Chamath E
-->
<%@ page language="java" import="org.damage.common.selectionhierarchy.ClassificationBrowser,
                                 java.util.Stack,
                                 org.damage.common.Globals,
                                 org.damage.db.persistence.InsuranceCompanyDAO,
                                 java.util.Iterator,
                                 org.damage.util.Tools" %>

<%@include file="/admin/accessControl/AccessControl.jsp" %>

<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<%@ taglib uri="/WEB-INF/sahana.tld" prefix="sahana" %>

<script language='javascript' src='common/scripts.js'></script>

<script language="JavaScript" type="text/JavaScript">

    function setDataTable(objCheck) {
       objTable = document.getElementById("InsuranceTable");

       if (objCheck.checked) {
          objTable.style.display = "";
          objCheck.value = "1";
       } else {
          objTable.style.display = "none";
          objCheck.value = "0";
       }
    }

</script>

<jsp:include page="SahanaLocations.jsp"></jsp:include>

<table cellspacing=0 cellpadding=0 width="100%" border=0 >

       <tr>
         <td colspan=2>
           <table cellspacing=0 cellpadding=0 width="100%" border=0>
             <tbody>
               <tr>
                 <td colspan=2 align="center"><font color='#000099'><b>
                 <%= Tools.getCurrentClassificationPath(request) %>
                 </b></font>
                 </td>
               </tr>
               <tr>
                 <td class=formText>&nbsp;</td>
                 <td class=formText>&nbsp;</td>
               </tr>

             </tbody>
           </table>
         </td>
       </tr>
   <tr>
 <td class=formTitle background=images/HeaderBG.jpg colspan=2
   height=25>Property Information</td>
</tr>
<tr>
 <td colspan=2>
	 <table cellspacing=0 cellpadding=0 width="100%" border=0>
	 <tbody>
	 <tr>
	 		 <td class=formText width="20%">&nbsp;</td>
	 		 <td>&nbsp;</td>
	   </tr>
	   <tr>
		 <td class=formText width="20%"><strong>Property Owner Details</strong></td>
		 <td>&nbsp;</td>
	   </tr>
	   <tr><td></td><td></td>
	   </tr>
	   <tr><td></td><td></td>
	   </tr>
	   <tr>
		 <td class=formText>Owner NIC/Passport ID</td>
		 <td>
			 <input class=textBox name="ownerPersonRef"
                value="<bean:write name="damagePropertyObject" property="ownerPersonRef" scope="session" ignore="true" />"
                size="30" >
			 &nbsp;<small><font
		   color=red>*</font></small>
		 </td>
	   </tr>
	   <tr><td></td><td></td>
	   </tr>
	   <tr>
		 <td class=formText>Owner Name </td>
		 <td>
			 <input class=textBox name="ownerName"
                value="<bean:write name="damagePropertyObject" property="ownerName" scope="session" ignore="true" />"
                size="30" >
			 &nbsp;<small><font color=red>*</font></small>
		 </td>
	   </tr>
	   <tr><td></td><td></td>
	   </tr>
	   <tr>
		 <td class=formText>Owner Address</td>
		  <td>
			 <textarea class=textBox name="ownerAddress" cols=50
                rows="2"><bean:write name="damagePropertyObject" property="ownerAddress" scope="session" ignore="true" /></textarea>
            <small><font color=red>*</font></small>
		  </td>
	   </tr>
	   <tr><td></td><td></td>
	   </tr>
	   <tr><td></td><td></td>
	   <tr><td></td><td></td>
	   </tr>
	   <tr><td></td><td></td>
	   </tr>
	   <tr><td class="formText"><strong>Property Location</strong></td><td></td>
	   </tr>
	   <tr><td></td><td></td>
	   </tr>
	   <tr>
		   <td align="left" class="formText" type="submit">Province </td>
		   <td vAlign="top" >
                            <sahana:SahanaReferenceDropdown
                                showLocations="true"
                                name="caseProvinceCode"
                                styleClass="selectBoxes"
                                onChangeJS="listDistrict();"
                                defaultValue="default" />
                        &nbsp;<small><font color="red">*</font></small>
		   </td>
	  </tr>
	  <tr><td></td><td></td>
	  </tr>
	  <tr>
		  <td  align="left" class="formText" type="submit">District </td>
		  <td vAlign="top" >
			<select name="caseDistrictId" class="selectBoxes" onchange="listDivisions();" >
				<option value="default">&lt;Select&gt;</option>
			</select>
            &nbsp;<small><font color="red">*</font></small>
		   </td>
	  </tr>
	  <tr><td></td><td></td>
	  </tr>
	  <tr>
	    <td  align="left" class="formText" type="submit">Division </td>
	    <td vAlign="top" >
		 <select name="caseDivisionId" class="selectBoxes" onChange="listGSDivisions();">
			<option value="default">&lt;Select&gt;</option>
	     </select>
	    </td>
	  </tr>
	  <tr>
		 <td  align="left" class="formText" type="submit">GS Division </td>
		 <td valign="top" >
			<select name="caseGSDivisionId" class="selectBoxes"  >
				<option selected="true" value="deafult">&lt;select&gt;</option>
			</select>
		 </td>
	   </tr>

        <!-- reset values from damageReport bean if available -->
        <script language="JavaScript" type="text/JavaScript">
           setSelectStatus(document.form1.caseProvinceCode,'<bean:write name="damagePropertyObject" property="locationProvince" scope="session" ignore="true" />');
           listDistrict();
           setSelectStatus(document.form1.caseDistrictId,'<bean:write name="damagePropertyObject" property="locationDistrict" scope="session" ignore="true" />');
           listDivisions();
           setSelectStatus(document.form1.caseDivisionId,'<bean:write name="damagePropertyObject" property="locationDivision" scope="session" ignore="true" />');
           listGSDivisions();
           setSelectStatus(document.form1.caseGSDivisionId,'<bean:write name="damagePropertyObject" property="locationGSDivision" scope="session" ignore="true" />');
        </script>


	   <tr>
		 <td class=formText>Property Location Address</td>
		 <td>
			 <textarea class=textBox name="propertyAddress" cols=50
                rows="2"><bean:write name="damagePropertyObject" property="propertyAddress" scope="session" ignore="true" /></textarea>
            <small><font color=red>*</font></small>
		  </td>
	   </tr>
	   <tr><td>&nbsp;</td><td>&nbsp;</td>
	   </tr>

	   <tr>
		 <td class=formText>Is Insured? </td>
		 <td>
		   <input type="checkbox" name="isInsured" onClick="setDataTable(this)" value="checkbox">
		   <small> Yes </small>
		 </td>
	   </tr>

	   <tr><td>&nbsp;</td><td>&nbsp;</td>
	   </tr>

	   <tr style="Display:none" id="InsuranceTable">
			<!-- Hidden variable -->
		   <td colspan=2 >
			   <div id=Layer1 style="Z-INDEX: 1; LEFT: 150px; OVERFLOW: auto; WIDTH: 100%; TOP: 279px">

			   <table cellspacing=0 cellpadding=0 width="100%" border=0>
				 <tbody>
				   <tr>
					 <td colspan="2" class="formText" height="16"><hr></td>
				   </tr>
				   <tr>
					 <td class="formText" width="20%" height="13"><strong>Insurance Details</strong></td>
					 <td  height="13"></td>
				   </tr>
				   <tr><td height="1"></td>
					 <td height="1"></td>
				   </tr>

				   <tr>
					 <td class="formText" height="19">Insurance Company Name </td>
					 <td colspan=4>
                         <sahana:SahanaReferenceDropdown
                            showInsuranceCompany="true"
                            name="insuranceCompany"
                            styleClass="textBox"
                            defaultValue="default" />
					 </td>
				   </tr>
                    <!-- reset values from damageReport bean if available -->
                    <script language="JavaScript" type="text/JavaScript">
                       setSelectStatus(document.form1.insuranceCompany,'<bean:write name="damagePropertyObject" property="insuranceCompany" scope="session" ignore="true" />');
                    </script>

				   <tr><td height="1"></td>
					 <td height="1"></td>
				   </tr>
				   <tr>
					  <td class="formText" height="19">Insurance Policy No. </td>
					  <td height="19">
					  <input class=textBox name="insurencePolicy"
                        value="<bean:write name="damagePropertyObject" property="insurencePolicy" scope="session" ignore="true" />"
                        size="30" >
                      &nbsp;<small><font color="red">*</font></small>
					  </td>
				   </tr>
				   <tr><td  height="1"></td>
					 <td height="1"></td>
				   </tr>
				   <tr>
					  <td class="formText" height="17">Insured Value </td>
					  <td height="17">
					  <input class=textBox name="insurenceValue"
                        value="<bean:write name="damagePropertyObject" property="insurenceValue" scope="session" ignore="true" />"
                        size="30" >
                      &nbsp;<small><font color="red">*</font></small>
					  </td>
				   </tr>
				   <tr>
					 <td>&nbsp;</td>
					 <td>&nbsp;</td>
				   </tr>
				 </tbody>
			   </table>
			   </div>
		   </td>
	   </tr>

       <logic:present name="damagePropertyObject">
           <logic:equal value="true" name="damagePropertyObject" property="isInsured" scope="session" >
                <!-- reset values from damageReport bean if available -->
                <script language="JavaScript" type="text/JavaScript">
                   document.form1.isInsured.checked=true;
                   setDataTable(document.form1.isInsured);
                </script>
           </logic:equal>
       </logic:present>

	 </tbody>
   </table>
 </td>
</tr>
</table>
