<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 java.sql.SQLException,
                 java.text.Format,
                 java.text.SimpleDateFormat,
                 org.erms.business.*,
                 org.sahana.share.utils.KeyValueDTO" %>
<%@ page import="org.erms.business.OrganizationRegistrationTO" %>
<%@ page import="java.util.*" %>
<%@ page import="java.io.IOException" %>

<jsp:useBean id="newOffer" scope="session" class="org.erms.business.Offer" />
<jsp:setProperty name="newOffer" property="*" />

<jsp:useBean id="tempNewOffer" scope="page" class="org.erms.business.Offer" />
<jsp:setProperty name="tempNewOffer" property="*" />

<%
    request.setAttribute("turl", "Welcome.jsp");
    request.setAttribute("modNo", "2");
    request.setAttribute("accessLvl", "ADD");
%>
<%@include file="/admin/accessControl/AccessControl.jsp" %>

<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<script language='javascript' src='comman/validate.js'></script>
<script>

//type=1 is full submit
//type = 2 is save
function validate(type){
    var quantitiyStr = document.form1.quantity.value;
    var eqValueStr = document.form1.eqValue.value;

    if (type==1){
         document.form1.submitType.value = "Save";
    }else if (type==2){
      document.form1.submitType.value = "AddList";
    }else if (type==3){
       document.form1.submitType.value = "Clear";
    }

    if (type==2){
        if (!testNumber(quantitiyStr)){
            alert("please put in a number for quantity");
         return;
        }

    }
    document.form1.submit();

}

  function loadOrgInfo(){

   var selectedOrgCode = document.form1.orgCode.value;

   document.hiddenForm.orgCode.value = selectedOrgCode;
   document.hiddenForm.submit();

  }

  function selectEntityType(){

   var selectedEntity = document.form1.offeringEntityType.value;

   document.hiddenForm2.offeringEntityType.value = selectedEntity;
   document.hiddenForm2.submit();

  }

  function selectTarget(){

   var selectedEntity = document.form1.targetSpecific.value;

   document.hiddenForm3.targetSpecific.value = selectedEntity;
   document.hiddenForm3.submit();

  }
     selectTarget


</script>

<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>

<body topmargin="0" leftmargin="0">

<jsp:include page="comman/header.inc"></jsp:include>

<form name="form1" action="Add_offer.jsp" method="post">
<input type="" name="submitType"/>

<%


    LoginBean userBean = (LoginBean) session.getAttribute("LoginBean");

    ArrayList errorList = new ArrayList();

    //if (user==null){
    //    request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User not authenticated!");
       // response.sendRedirect("error.jsp");
    //}

    boolean isSaveOffer = false;
    boolean isClearOffer = false;
    boolean isAddList = false;

    String submitType = request.getParameter("submitType");

    //String userParameter = request.getParameter("user");


     //adding the list
    String quantityParameter = request.getParameter("quantity");
    String catogoriesParameter = request.getParameter("category");
    String unitsParameter = request.getParameter("unit");
    String itemParameter = request.getParameter("item");
    String targetAreaParameter = request.getParameter("targetArea");

    String entityTypeParameter =       request.getParameter("offeringEntityType"); 
    String individualParameter = request.getParameter("offeringIndividual"); 




    isSaveOffer = "Save".equals(submitType);
    isClearOffer = "Clear".equals(submitType);
    isAddList = "AddList".equals(submitType);
    //set up the validation code here

    if (isSaveOffer){
        if (newOffer==null){
            newOffer = new Offer();
        }

        //validate the params
        if(newOffer.getOfferingEntityType().equalsIgnoreCase("Individual")) {
            String individualName = newOffer.getOfferingIndividual();
            if(individualName ==null || individualName.trim().length()<=0)
              errorList.add("Individual Name required");
        }

        if (newOffer.getItem()==null || newOffer.getItem().trim().length()<=0)
            errorList.add("Item is required");


        if (newOffer.getTargetSpecific()==null || newOffer.getTargetSpecific().equalsIgnoreCase("Yes")){
            String target = newOffer.getTargetArea();
            if(target ==null || target.trim().length()<=0 || target.equalsIgnoreCase(""))
            {
                errorList.add("Target Area is required");
            }
        }
        if (newOffer.getOfferDetails().isEmpty())
            errorList.add("The List should not be empty");

        if (errorList.isEmpty()) { //this means no errors
            DataAccessManager dam = new DataAccessManager();
            if(newOffer.getTargetSpecific().equalsIgnoreCase("No")){
                   dam.addOffer(newOffer,"user.getUserName()",false);
            }else{
                   dam.addOffer(newOffer,"user.getUserName()",true);
            }
            //reset the DTobject

             request.getSession().removeAttribute("newOffer");
             newOffer = new Offer();
            // newOffer.clear();
                                         
        }

    }else if (isClearOffer){
        request.getSession().removeAttribute("newOffer");
        newOffer = new Offer();
        //newOffer.clear();
      // request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.REQUEST_DTO, newOffer);

    }else if (newOffer==null){
        request.getSession().removeAttribute("newOffer");
        newOffer = new Offer();
        //request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.REQUEST_DTO, newOffer);
    }else{
        //just update from the values
        //if (contactNameParameter!=null && contactNumberParameter!=null) {//todo check the other fields for nullity as well
          if(quantityParameter !=null) {
            int quantity  = 0;

            try {
                quantity = Integer.parseInt("".equals(quantityParameter)?"0":quantityParameter==null?"0":quantityParameter);
              
            } catch (NumberFormatException e) {
                errorList.add("quantity should be a number!");
            }

            if (errorList.isEmpty()){
              OfferDetail requestDetailTO = new OfferDetail(null, null,catogoriesParameter, unitsParameter, quantity, itemParameter ,targetAreaParameter);
              newOffer.addOfferDetails(requestDetailTO);

                quantityParameter = null;
                catogoriesParameter = null;
                unitsParameter = null;
                itemParameter = null;
            }
          }   
        //}

    }


   if(!newOffer.getOrgCode().equalsIgnoreCase("")) {
       DataAccessManager dam = new DataAccessManager();
       OrganizationRegistrationTO orgTo = dam.findOrganizatinByCode(newOffer.getOrgCode());

       newOffer.setContactName(orgTo.getContactPerson());
       newOffer.setContactAddress(orgTo.getOrgAddress());
       newOffer.setEmailAddress(orgTo.getEmailAddress());
       newOffer.setContactNumber(orgTo.getContactNumber());
   }



%>

<table width="100%" border="0" cellspacing="0" cellpadding="0">

<tr>
<td>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr align="left">
<td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
<td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="Search_Offer.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search
Offer</font></a>&nbsp;&nbsp;</td>
<td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
<td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log
off&nbsp;&nbsp;&nbsp;&nbsp;</font></a></td>
</tr>
</table>
</td>
</tr>
<tr>
<td><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
<%--<td width="134" height="350" valign="top" class="leftMenuBG"><img src="images/spacer.gif" width="160" height="10"></td>--%>
<%-- <td><img src="images/Blank.gif" width="10" height="10"></td><td width="100%">&nbsp;</td>--%>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
<td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Add Offer  </td>
</tr>
<tr>
<td >&nbsp;</td>
<td >&nbsp;</td>
</tr>
<tr>
<td colspan="2">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
<!--  -->
<%
    Format formatter = new SimpleDateFormat("yyyy-MM-dd");
    String formattedDate = formatter.format(new java.util.Date());
%>
<tr>

<td colspan="2" class="formText"><strong>Organization : <%=userBean.getOrgName()%> &nbsp;&nbsp;User : <%=userBean.getUserName()%> &nbsp;&nbsp;Date : <%=formattedDate%></strong></td>
</tr>
<tr>
<td class="formText">&nbsp;</td>
<td class="formText">&nbsp;</td>
</tr>
<!-- -->
</table>

</td>
</tr>
<tr>
<td>&nbsp;</td>
<td class="formText"><%
    if (!errorList.isEmpty()){
%> <font color="red"> Please correct the following errors <%
        for (int i = 0; i < errorList.size(); i++) {
%><li><%= errorList.get(i).toString()%></li>
          <%
        }
          %>
          </font>
      <%
    }

      %></td>
</tr>
<tr>
<td colspan="2">
<table width="100%" border="0" cellspacing="0" cellpadding="0">

<tr>
                 <td class="formText">&nbsp;Offering Entity Type</td>

                 <td colspan="4"><select name="offeringEntityType" onchange="selectEntityType();"    class="textBox">

                 <option <%=newOffer.getOfferingEntityType().equalsIgnoreCase("Individual")?"selected=\"true\"":""%> value="Individual">Individual</option>
                 <option <%=newOffer.getOfferingEntityType().equalsIgnoreCase("Organization")?"selected=\"true\"":"" %> value="Organization">Organization</option>

                 </select></td>

</tr>

<tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>


                <tr>

<%
    if(newOffer.getOfferingEntityType().equalsIgnoreCase("Organization")) {
%>

<tr>

<td width="20%" class="formText">&nbsp;Organization</td>
<td colspan="4">

<select name="orgCode" class="textBox" onchange="loadOrgInfo();" >
<option value="">&lt;select&gt;</option>

<%
                                        Collection organizationList = null;
                                        try {
                                            DataAccessManager dam = new DataAccessManager();
                                            organizationList = dam.getAllOrganizationNames();
                                            if (organizationList != null) {

                                                Iterator orgItr = organizationList.iterator();

                                                while (orgItr.hasNext()) {
                                                    KeyValueDTO organization = (KeyValueDTO) orgItr.next();
                                                    String orgCode = organization.getDbTableCode();
                                                    String orgName = organization.getDisplayValue();

                                                    if (newOffer.getOrgCode().equals(orgCode)) {%>
                                                    <option selected value="<%=orgCode%>"><%=orgName%></option>
                                                                                        <%} else {%>
                                                                                        <option value="<%=orgCode%>"><%=orgName%></option>
                                                                                     <%}
                                                }
                                            }
                                        } catch (Exception e) {
                                            out.print("Exception occurd " + e);
                                        }%>

									</select></td>
</tr>
<tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
<tr>
<td width="20%" class="formText">&nbsp;Contact Name</td>
<td colspan="4"><input maxlength="50" type="text" name="contactName" class="textBox" width="150" readonly="true" value="<%=newOffer.getConatactName()%>" />&nbsp;<!--<small><font color="red">*</font></small> </td>  -->
</tr>

<%
    }else { 
%>
  <tr>
<td width="20%" class="formText">&nbsp;Individual Name</td>
<td colspan="4"><input type="text" name="offeringIndividual" class="textBox" value="
<%=newOffer.getOfferingIndividual()%>" />&nbsp;<!--<small><font color="red">*</font></small></td>   -->
</tr>

<%
    }
%>

<tr>
<tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
 <td width="20%" class="formText">&nbsp;Contact Number</td>
 <td colspan="4"><input maxlength="50" type="text" name="contactNumber" class="textBox" width="150" <%=newOffer.getOfferingEntityType().equalsIgnoreCase("Organization")?"readonly=\"true\"":""%> value="
 <%=newOffer.getContactNumber()%>" />&nbsp;</td> <!--<small><font color="red">*</font></small>           -->



 </tr>
 <tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
<tr>
<tr>
<td width="20%" class="formText">&nbsp;Email Address</td>
<td colspan="4"><input type="text" name="emailAddress" <%=newOffer.getOfferingEntityType().equalsIgnoreCase("Organization")?"readonly=\"true\"":""%> class="textBox" value="
<%=newOffer.getEmailAddress()%>" />&nbsp;<!--<small><font color="red">*</font></small></td>   -->
</tr>
<tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
<tr>
<td width="20%" class="formText">&nbsp;Contact Address</td>
<td colspan="4"><textarea name="contactAddress"  class="textBox" cols="50"<%=newOffer.getOfferingEntityType().equalsIgnoreCase("Organization")?"readonly=\"true\"":""%>> <%=newOffer.getContactAddress()%></textarea>
&nbsp;<!--<small><font color="red">*</font></small></td>  -->
</tr>
<tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
<tr>
<td width="20%" class="formText">&nbsp;Description</td>
<td colspan="4"><textarea name="description" cols="50" rows="4" class="textBox"><%=newOffer.getDescription()%></textarea>
</td>
</tr>
<tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
<tr>
<td width="20%" class="formText">&nbsp;Time Frame</td>
<td colspan="4"><input type="text" name="timeFrame" class="textBox" value="<%=newOffer.getTimeFrame()%>" />&nbsp;<small><font color="red"></font></small></td>
</tr>
<tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
<tr>
<td width="20%" class="formText">&nbsp;Equivalent Value</td>
<td colspan="4"><input type="text" name="eqValue" class="textBox" value="<%=newOffer.getEqValue()%>" />&nbsp;<!--<small><font color="red">*</font></small></td> -->
</tr>
 <tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
<tr>
<td width="20%"height="22" class="formText">&nbsp;Category</td>
<td colspan="4"><select name="category" class="textBox">
                   <%
                       Collection catogoryList=null;
                       try{
                           DataAccessManager dam = new DataAccessManager();
                           catogoryList =  dam.getAllCategories();
                           if(catogoryList != null){
                               Iterator citr = catogoryList.iterator();
                               while(citr.hasNext()){
                                   KeyValueDTO catogory = (KeyValueDTO) citr.next();
                                   String catogoryCode = catogory.getDbTableCode();
                                   String catogoryvalue = catogory.getDisplayValue();
                           if (newOffer.getCategory().equalsIgnoreCase(catogoryCode)){
                           %>
                   <option value="<%=catogoryCode%>" selected="true"><%=catogoryvalue%></option>
                   <%
                        }else{
                   %>
                   <option value="<%=catogoryCode%>"><%=catogoryvalue%></option>
                   <%
                        }
                               }
                           }
                       }catch(Exception e) {
                           throw new Exception(e);
                       }
                   %>
                   </select></td>

                   </tr>
                   <tr>
                    <td>&nbsp;</td>
                    <td colspan="2">&nbsp;</td>
                    </tr>
                   <tr>
                   <td class="formText">&nbsp;Item</td>
                   <td colspan="4">
                   <textarea name="item"  class="textBox" cols="50" ><%=newOffer.getItem()%></textarea>&nbsp;<small><font color="red">*</font></small></td>
                   </td>
                   </tr>
                   <tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>
                   <tr>
                   <td class="formText">&nbsp;Units</td>
                   <td width="17%" colspan="4" ><input type="text" name="unit" class="textBox" value="<%=newOffer.getUnit()%>" />&nbsp;<small><font color="red">*</font></small></td>
                   </tr>
                   <tr>
                    <td colspan="7"><hr/></td>
                    </tr>
                <tr>
                <td>&nbsp;</td>
                <td colspan="2">&nbsp;</td>
                </tr>
                   <tr>
                   <td width="10%" class="formText">Quantity</td>
                   <td width="18%"><input type="text" name="quantity" class="textBox" maxlength="10" value="<%=newOffer.getQuantity()%>"></td>
                   <td width="35%">&nbsp;</td>
                   </tr>
                 <tr>
                <td>&nbsp;</td>
                <td colspan="2">&nbsp;</td>
                </tr>
                <tr>
                 <td class="formText">&nbsp;Specify Target Area</td>

                 <td colspan="4"><select name="targetSpecific"  class="textBox">

                 <option <%=newOffer.getTargetSpecific().equalsIgnoreCase("Yes")?"selected=\"true\"":""%> value="Yes">Yes</option>
                 <option <%=newOffer.getTargetSpecific().equalsIgnoreCase("No")?"selected=\"true\"":"" %> value="No">No</option>
                 </select></td>

                </tr>
                <tr>
<td>&nbsp;</td>
<td colspan="2">&nbsp;</td>
</tr>


                <tr>
				<td width="20%" class="formText">&nbsp;Target Area</td>
				<td colspan="4"><select name="targetArea" class="textBox">
                <option value="">&lt;select&gt;</option>
                                <%
                                        Collection districtList = null;
                                        try {
                                            DataAccessManager dam = new DataAccessManager();
                                            districtList = dam.getAllDistricts();
                                            if (districtList != null) {

                                                Iterator ditr = districtList.iterator();

                                                while (ditr.hasNext()) {
                                                    KeyValueDTO district = (KeyValueDTO) ditr.next();
                                                    String districtCode = district.getDbTableCode();
                                                    String districtvalue = district.getDisplayValue();
                                                    if (newOffer.getTargetArea().equals(districtCode)) {%>
                                                    <option selected value="<%=districtCode%>"><%=districtvalue%></option>
                                                                                        <%} else {%>
                                                                                        <option value="<%=districtCode%>"><%=districtvalue%></option>
                                                                                        <%}
                                                }
                                            }
                                        } catch (Exception e) {
                                            out.print("Exception occurd " + e);
                                        }
                                                    %>



												</select></td>

                                                <td colspan="2" >&nbsp;</td>
                                                <td align="right"  ><input name="Submit1" type="button" value="Add to List" class="buttons" onclick="validate(2)" ></td>

											</tr>


                      </table></td>
                      </tr>
                      <tr>
                      <td>&nbsp;</td>
                      <td colspan="4">&nbsp;</td>
                      </tr>
                      <tr>
                      <td colspan="2">
<%--<div id="Layer1" style="position:auto; left:150px; top:279px; width:100%; height:200px; z-index:1; overflow: auto;overflow-x">--%>
<div id="Layer1" style="position:auto; left:150px; top:279px; width:100%;z-index:1; overflow: auto;overflow-x">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr >
<td class="tableUp">Category</td>
<td class="tableUp">Item</td>
<td class="tableUp">Unit</td>
<td class="tableUp">Quantity</td>
<td class="tableUp">Target Area</td>
</tr>


<%
    Collection offerDet = newOffer.getOfferDetails();
    Iterator iterator = offerDet.iterator();
    OfferDetail    tempOfferDetailDto=null;
    while (iterator.hasNext()) {
        tempOfferDetailDto =(OfferDetail) iterator.next();
%>
<tr>
<td class="tableDown"><%=tempOfferDetailDto.getCategory()%></td>
<td class="tableDown" nowrap="false" width="200"  ><%=tempOfferDetailDto.getItem()%></td>
<td class="tableDown"><%=tempOfferDetailDto.getUnit()%></td>
<td class="tableDown"><%=tempOfferDetailDto.getQuantity()%></td>
<td class="tableDown"><%=tempOfferDetailDto.getTargetArea()%></td>
</tr>
        <%
    }
        %>

</table>

</div></td>
</tr>
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
<tr>

<td class="formTitle" colspan="2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
<td width="73%">&nbsp;</td>
<td width="12%" align="right"><input type="button" name="Submit2" value="Save" class="buttons" onclick="validate(1)" />&nbsp;<input type="button" name="Submit2" value="Clear" class="buttons" onclick="validate(3)" /></td>
</tr>
</table></td>
</tr>
<tr>
<td colspan="2" class="pageBg">&nbsp;</td>
</tr>
</table>
</tr>
</table></td>
</tr>
<tr>
<td></td>
</tr>
</table>
</td>
</tr>
</table>
</td>
</tr>
</table>
</form>

<form method="POST" action="Add_offer.jsp" name="hiddenForm">
        <input type="hidden" name="orgCode" value=""/>
</form>

<form method="POST" action="Add_offer.jsp" name="hiddenForm2">
        <input type="hidden" name="offeringEntityType" value=""/>
</form>


<form method="POST" action="Add_offer.jsp" name="hiddenForm3">
        <input type="hidden" name="targetSpecific" value=""/>
</form>


<jsp:include page="comman/internalfooter.inc"></jsp:include>
<jsp:include page="comman/footer.inc"></jsp:include>

</body>
</html>

