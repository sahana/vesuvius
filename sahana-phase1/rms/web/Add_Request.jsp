<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 java.sql.SQLException,
                 org.erms.business.RequestTO,
                 org.erms.business.RequestDetailTO,
                 java.text.Format,
                 java.text.SimpleDateFormat,
                 org.erms.business.User,
                 org.sahana.share.utils.KeyValueDTO" %>
<%@ page import="java.util.*" %>
<%@ page import="java.io.IOException" %>
<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<script language='javascript' src='comman/validate.js'></script>
<%--<script>--%>
<%--</script>--%>

<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>

<body topmargin="0" leftmargin="0">
 <%
    request.setAttribute("turl", "Welcome.jsp");
    request.setAttribute("modNo", "2");
    request.setAttribute("accessLvl", "ADD");
%>
<%@include file="/admin/accessControl/AccessControl.jsp" %>

<jsp:include page="comman/header.inc"></jsp:include>

<form name="form1" action="Add_Request.jsp" method="post">
<input type="hidden" name="submitType"/>

<%
    final String DELETE_FROMLIST = "DELETE_FROM_LIST";





    RequestTO requestObj = (RequestTO) request.getSession().getAttribute(ERMSConstants.IContextInfoConstants.REQUEST_DTO);

    String deleteID = (String)request.getParameter(DELETE_FROMLIST);
    if(deleteID!= null){
        requestObj.removeRequestDetails(Integer.parseInt(deleteID));
    }

//    User user = (User) request.getSession().getAttribute(ERMSConstants.IContextInfoConstants.USER_INFO);
    LoginBean lbean = (LoginBean)session.getAttribute("LoginBean");
    User user = new  User(lbean.getUserName(),lbean.getOrgId());
    user.setOrganization(lbean.getOrgName());
    ArrayList errorList = new ArrayList();

    if (user==null){
        request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User not authenticated!");
        response.sendRedirect("error.jsp");
    }

    boolean isSaveRequest = false;
    boolean isClearRequest = false;
    //save code
    String submitType = request.getParameter("submitType");
    String callerNameParameter = request.getParameter("callerName");
    String callerContactParameter = request.getParameter("callerContact");
    String CallerAddressParameter = request.getParameter("callerAddress");
    String SiteNameParameter = request.getParameter("siteName");
    String siteAreaParameter = request.getParameter("siteArea");
    String districtParameter = request.getParameter("districts");
    String userParameter = request.getParameter("user");
    String requestDateParameter = request.getParameter("requestDate");
    String descriptionParameter = request.getParameter("description"); //not required
    String siteTypeParameter =  request.getParameter("siteType");
    String siteContactParameter =  request.getParameter("siteContact");


    //adding the list
    String quantityParameter = request.getParameter("quantity");
    String priorityParameter = request.getParameter("priorities");
    String catogoriesParameter = request.getParameter("catogories");
    String unitsParameter = request.getParameter("units");
    String itemParameter = request.getParameter("item");

    isSaveRequest = "Save".equals(submitType);
    isClearRequest = "Clear".equals(submitType);
    //set up the validation code here

    if (isSaveRequest){
        if (requestObj==null){
            requestObj = new RequestTO();
        }

        //validate the params
        if (callerNameParameter==null || callerNameParameter.trim().length()<=0)
            errorList.add("Requester name is required");
        if (callerContactParameter==null || callerContactParameter.trim().length()<=0)
            errorList.add("Requester Contact is required");
        if (CallerAddressParameter==null || CallerAddressParameter.trim().length()<=0)
            errorList.add("Requester Address is required");
        if (SiteNameParameter==null || SiteNameParameter.trim().length()<=0)
            errorList.add("Site name is required");
        if (districtParameter==null || districtParameter.trim().length()<=0)
            errorList.add("District is required");
        if (requestObj.getRequestDetails().isEmpty())
            errorList.add("The List should not be empty");


        requestObj.setCallerName(callerNameParameter);
        requestObj.setCallerContactNumber(callerContactParameter);
        requestObj.setCallerAddress(CallerAddressParameter);
        requestObj.setSiteName(SiteNameParameter);
        requestObj.setSiteArea(siteAreaParameter);
        requestObj.setSiteDistrict(districtParameter);
        requestObj.setUser(userParameter);
        requestObj.setOrgCode(user.getOrgCode());
        requestObj.setDescription(descriptionParameter);

        //Date is in yyyy-mm-dd format
        String[] dateValues = requestDateParameter.split("-");
        Calendar cal = new GregorianCalendar(Integer.parseInt(dateValues[0]),
                Integer.parseInt(dateValues[1])-1,
                Integer.parseInt(dateValues[2])
        );

        java.sql.Date requestDateObj = new java.sql.Date(cal.getTime().getTime());
        requestObj.setRequestedDate(requestDateObj);

        if (errorList.isEmpty()) { //this means no errors
            DataAccessManager dam = new DataAccessManager();
            dam.addRequest(requestObj);

            //reset the DTobject
            requestObj = new RequestTO();
            request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.REQUEST_DTO, requestObj);
        }

    }else if (isClearRequest){
        requestObj = new RequestTO();
        request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.REQUEST_DTO, requestObj);
    }else if (requestObj==null){
        requestObj = new RequestTO();
        request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.REQUEST_DTO, requestObj);
    }else{
        //just update from the values
        if (callerContactParameter!=null && callerNameParameter!=null) {//todo check the other fields for nullity as well
            requestObj.setCallerName(callerNameParameter);
            requestObj.setCallerContactNumber(callerContactParameter);
            requestObj.setCallerAddress(CallerAddressParameter);
            requestObj.setSiteName(SiteNameParameter);
            requestObj.setSiteDistrict(districtParameter);
            requestObj.setSiteArea(siteAreaParameter);
            requestObj.setUser(userParameter);
            requestObj.setDescription(descriptionParameter);
            requestObj.setSiteType(siteTypeParameter);
            requestObj.setSiteContact(siteContactParameter);

            String requestID = requestObj.getRequestID();

            //Date is in yyyy-mm-dd format
            String[] dateValues = requestDateParameter.split("-");
            Calendar cal = new GregorianCalendar(Integer.parseInt(dateValues[0]),
                    Integer.parseInt(dateValues[1])-1,
                    Integer.parseInt(dateValues[2])
            );

            java.sql.Date requestDateObj = new java.sql.Date(cal.getTime().getTime());
            requestObj.setRequestedDate(requestDateObj);

            int quantity  = 0;

            try {
                quantity = Integer.parseInt("".equals(quantityParameter)?"0":quantityParameter==null?"0":quantityParameter);
            } catch (NumberFormatException e) {
                errorList.add("quantity should be a number!");
            }

            if (unitsParameter==null || unitsParameter.trim().length()<=0)
                errorList.add("unitsParameter should not be empty!");
            if (itemParameter==null || itemParameter.trim().length()<=0)
                errorList.add("itemParameter should not be empty!");

            if (errorList.isEmpty()){
                RequestDetailTO requestDetailTO = new RequestDetailTO(null, requestID,catogoriesParameter, null, unitsParameter, quantity, itemParameter, priorityParameter);
                requestObj.addRequestDetails(requestDetailTO);

                //clear the params here
                quantityParameter = null;
                priorityParameter =null;
                catogoriesParameter = null;
                unitsParameter = null;
                itemParameter = null;
            }
        }

    }



%>
<table width="100%" border="0" cellspacing="0" cellpadding="0">

<tr>
<td>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr align="left">
<td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
<td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="Search_Request.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search
Request</font></a>&nbsp;&nbsp;</td>
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
<td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Add request  </td>
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
<td colspan="2" class="formText"><strong>Organization : <%=user.getOrganization()%> &nbsp;&nbsp;User : <%=user.getUserName()%> &nbsp;&nbsp;Date : <%=formattedDate%></strong></td>
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

<td width="20%" class="formText">&nbsp;Request Date</td>
<td colspan="4">
<table>
<tr>
<td width="16%">
<input type="text" name="requestDate" class="textBox" readonly="true" id="txtMDate1" value="<%=requestObj.getRequestedDate()%>" />&nbsp;<small><font color="red">*</font></small>
</td>
<td width="82%"><img src="images/calendar.gif" onClick="popUpCalendar(this, document.getElementById('txtMDate1'), 'yyyy-mm-dd')" width="18" height="17"/></td>
</tr>
</table>
</td>
</tr>
<tr>
<td class="formText">&nbsp;Requester Name</td>
<td colspan="4"><input maxlength="50" type="text" name="callerName" class="textBox" width="150" value="
<%=requestObj.getCallerName()%>" />&nbsp;<small><font color="red">*</font></small> </td>
</tr>
<tr>
<td class="formText">&nbsp;Requester Contact</td>
<td colspan="4"><input type="text" name="callerContact" class="textBox" value="
<%=requestObj.getCallerContactNumber()%>" />&nbsp;<small><font color="red">*</font></small></td>
</tr>
<tr>
<td class="formText">&nbsp;Requester Address</td>
<td colspan="4"><textarea name="callerAddress"  class="textBox" cols="50" ><%=requestObj.getCallerAddress()%></textarea>
&nbsp;<small><font color="red">*</font></small></td>
</tr>
<tr>
<td>&nbsp;</td>
<td colspan="4">&nbsp;</td>
</tr>
<tr>
<td class="formText">&nbsp;Site Name</td>
<td colspan="4"><input type="text" name="siteName" class="textBox" value="
<%=requestObj.getSiteName()%>"/>&nbsp;<small><font color="red">*</font></small><img src="images/question.gif" width="20" height="20" alt="Enter the Common Name Given to the Site"/></td>

</tr>
<tr>
<td class="formText">&nbsp;Site District </td>
<td colspan="4"><select name="districts" class="textBox">
                   <%
                       DataAccessManager dam = new DataAccessManager();
                       Collection districtList=null;
                       try{
                           districtList =  dam.getAllDistricts();
                           if(districtList != null){
                               Iterator ditr = districtList.iterator();
                               boolean isSelected = false;
                               while(ditr.hasNext()){
                                   KeyValueDTO district = (KeyValueDTO) ditr.next();
                                   String districtCode = district.getDbTableCode();
                                   String districtvalue = district.getDisplayValue();



                                   if (requestObj.getSiteDistrict().equals(districtCode)){
                                       isSelected = true;
                   %>
                                        <option selected="true" value="<%=districtCode%>"><%=districtvalue%></option>
                                       <%
                                   }else{
                                       %>
                                       <option value="<%=districtCode%>"><%=districtvalue%></option>
                                       <%
                                   }
                               }
                               if(!isSelected){ %>
                                    <option selected="true" value="deafult">&lt;select&gt;</option>

                               <% }
                           }
                       }catch(Exception e) {
                           throw new Exception(e);
                       }
                                       %>
                                       </select>&nbsp;<small><font color="red">*</font></small><img src="images/question.gif" width="20" height="20" alt="Enter the district to which the site belongs"/></td>
                                       </tr>
                                       <tr>
                                       <td class="formText">&nbsp;Site Address</td>
                                       <td colspan="4"><input type="text" name="siteArea" class="textBox" value="<%=
                                           requestObj.getSiteArea()
                                       %>" />&nbsp;<small><font color="red">*</font></small></td>
                                       </tr>

<tr>
    <td>
          &nbsp;Site Type
    </td>
        <!---- TODO Ajth ayya --->
    <td>
        <%
            Iterator sites = dam.getAllSiteTypes().iterator();
        %>
        <select name = "siteType" class="textBox">
            <%
                String siteTypeCode = null;
                String siteType = null;
                boolean isSelected = false;
                while(sites.hasNext()){
                    KeyValueDTO keyVpair = (KeyValueDTO)sites.next();
                    siteTypeCode = keyVpair.getDbTableCode();
                    siteType = keyVpair.getDisplayValue();
             %>
                <%
                    if(siteTypeCode.equals(requestObj.getSiteType())){
                        isSelected = true;
                %>
                        <option selected="false"  value="<%=siteTypeCode%>"><%=siteType%></option>
                <% }else{ %>
                       <option selected="false"  value="<%=siteTypeCode%>"><%=siteType%></option>
                <% }
                }
                if(!isSelected){
                   %>
                     <option selected="true" value="deafult">&lt;select&gt;</option>
                   <%
                }
            %>
        </select>
        <img src="images/question.gif" width="20" height="20" alt="Select one of the four types listed"/>

    </td>
</tr>

<tr>
    <td>
          &nbsp;Site Contract
    </td>
    <!---- TODO Ajth ayya --->
    <td>
          <input type="text" name="siteContact" class="textBox" value="<%=
                                           requestObj.getSiteContact()
                                       %>" />
    </td>
</tr>
<tr>
    <td>
          &nbsp;
    </td>
</tr>


<tr>
<td class="formText">&nbsp;Additional Comments</td>
<td colspan="4"><textarea name="description" cols="50" rows="4" class="textBox"><%=requestObj.getDescription()%></textarea>
</td>
</tr>
<tr>
<td colspan="5"><hr/></td>
</tr>
<tr>
<td height="22" class="formText">&nbsp;Category</td>
<td colspan="4"><select name="catogories" class="textBox">
                   <%
                       Collection catogoryList=null;
                       try{
                           catogoryList =  dam.getAllCategories();
                           if(catogoryList != null){
                               Iterator citr = catogoryList.iterator();
                               isSelected = false;
                               while(citr.hasNext()){
                                   KeyValueDTO catogory = (KeyValueDTO) citr.next();
                                   String catogoryCode = catogory.getDbTableCode();
                                   String catogoryvalue = catogory.getDisplayValue();
                        if (catogoryCode.equals(catogoriesParameter)){
                            isSelected = true;
                           %>
                   <option value="<%=catogoryCode%>" selected="true"><%=catogoryvalue%></option>
                   <%
                        }else{
                   %>
                   <option value="<%=catogoryCode%>"><%=catogoryvalue%></option>
                   <%
                        }
                               }
                               if(!isSelected){
                                     %>
                                       <option selected="true" value="deafult">&lt;select&gt;</option>
                                     <%
                               }
                           }
                       }catch(Exception e) {
                           throw new Exception(e);
                       }
                   %>
                   </select></td>
                   </tr>
                   <tr>
                   <td class="formText">&nbsp;Item</td>
                   <td colspan="4">
                   <textarea name="item"  class="textBox" cols="50" ><%=itemParameter==null?"":itemParameter%></textarea>

                   </td>
                   </tr>
                   <tr>
                   <td class="formText">&nbsp;Units</td>
                   <td width="17%" colspan="4" ><input type="text" name="units" class="textBox" value="<%=unitsParameter==null?"":unitsParameter%>" /></td>
                   </tr>
                   <tr>
                   <td width="10%" class="formText">Quantity</td>
                   <td width="18%"><input type="text" name="quantity" class="textBox" maxlength="10" value="<%=quantityParameter==null?"":quantityParameter%>"  ></td>
                   <td width="35%">&nbsp;</td>
                   </tr>
                   <tr>
                   <td class="formText">&nbsp;Priority</td>
                   <td colspan="1"><select name="priorities" class="textBox">
                   <%
                       Collection priorityList=null;
                       try{
                           priorityList =  dam.getAllPriorities();
                           if(priorityList != null){
                               Iterator pitr = priorityList.iterator();
                               isSelected = false;
                               while(pitr.hasNext()){
                                   KeyValueDTO priorityDTO = (KeyValueDTO) pitr.next();
                                   String priorityCode = priorityDTO.getDbTableCode();
                                   String priorityvalue = priorityDTO.getDisplayValue();

                                   if (priorityCode.equals(priorityParameter)){
                                       isSelected = true;
                                     %>
                                   <option value="<%=priorityCode%>" selected="true"><%=priorityvalue%></option>
                      <%
                                   }else{
                   %>
                                   <option value="<%=priorityCode%>"><%=priorityvalue%></option>
                      <%
                               }
                               }
                               if(!isSelected){ %>
                                   <option selected="true" value="deafult">&lt;select&gt;</option>
                               <% }
                           }
                       }catch(Exception e) {
                           throw new Exception(e);
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
<td class="tableUp">Priority</td>
</tr>


<%
    Vector requestDetails = requestObj.getRequestDetails();
    Iterator iterator = requestDetails.iterator();
    RequestDetailTO    tempRequestDetailDto;
    for(int i = 0;i<requestDetails.size();i++){
        tempRequestDetailDto =(RequestDetailTO) requestDetails.get(i);
%>
<tr>
<td class="tableDown"><%=dam.getCategoryName(tempRequestDetailDto.getCategory())%></td>
<td class="tableDown" nowrap="false" width="200"  ><%=tempRequestDetailDto.getItem()%></td>
<td class="tableDown"><%=tempRequestDetailDto.getUnit()%></td>
<td class="tableDown"><%=tempRequestDetailDto.getQuantity()%></td>
<td class="tableDown"><%=dam.getPriorityName(tempRequestDetailDto.getPriority())%></td>
<td class="tableDown"><a href="Add_Request.jsp?<%=DELETE_FROMLIST+"="+String.valueOf(i)%>">remove</a></td>
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
<jsp:include page="comman/internalfooter.inc"></jsp:include>
<jsp:include page="comman/footer.inc"></jsp:include>

</body>
</html>
