<%@ page import="org.transport.db.DataAccessManager,
                 org.transport.util.TRANSPORTConstants,
                 java.sql.SQLException,
                 org.transport.business.ConsignmentTO,
                 org.transport.business.ConsignmentItemTO,
                 java.text.Format,
                 java.text.SimpleDateFormat,
                 org.transport.business.User" %>
<%@ page import="org.transport.business.KeyValueDTO" %>
<%@ page import="java.util.*" %>
<%@ page import="java.io.IOException" %>
<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<script language='javascript' src='comman/validate.js'></script>
<script>
//type=1 is full submit
//type = 2 is save
function validate(type)
{
var quantitiyStr = document.form1.quantity.value;

if (type==1)
{
document.form1.submitType.value = "Save";
}
else if (type==2)
{
document.form1.submitType.value = "AddList";
}
else if (type==3)
{
document.form1.submitType.value = "Clear";
}

if (type==2)
{
if (!testNumber(quantitiyStr))
{
alert("please put in a number for quantity");
 return;
}
}
document.form1.submit();
}

</script>

<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>

<body topmargin="0" leftmargin="0">

<jsp:include page="comman/header.inc"></jsp:include>

<form name="form1" action="Add_Request.jsp" method="post">
<input type="hidden" name="submitType"/>

<%
ConsignmentTO consignmentObj;
/*
User user = (User) request.getSession().getAttribute(TRANSPORTConstants.IContextInfoConstants.USER_INFO);
ArrayList errorList = new ArrayList();

if (user==null){
request.getSession().setAttribute(TRANSPORTConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User not authenticated!");
response.sendRedirect("error.jsp");
}*/

boolean isSaveConsignment = false;
boolean isClearConsignment = false;
//save code
String submitType = request.getParameter("submitType");
int consignmentIdParam = Integer.parseInt(request.getParameter("consignmentId"));
String typeParam = request.getParameter("type");
int sourceParam = Integer.parseInt(request.getParameter("source"));
int divisionParam = Integer.parseInt(request.getParameter("division"));
int campParam = Integer.parseInt(request.getParameter("camp"));
int statusParam = Integer.parseInt(request.getParameter("status"));
//Collection itemsParam = request.getParameter("items");
//String userParameter = request.getParameter("user");

//adding the list
String itemParameter = request.getParameter("item");
String quantityParameter = request.getParameter("issuedQty");
String uoMParameter = request.getParameter("UoM");

isSaveConsignment = "Save".equals(submitType);
isClearConsignment = "Clear".equals(submitType);
//set up the validation code here

if (isSaveConsignment)
{
if (consignmentObj==null)
{
    consignmentObj = new ConsignmentTO();
}

consignmentObj.setConsignmentId(consignmentIdParam);
consignmentObj.setType(typeParam);
consignmentObj.setDestination(campParam);
consignmentObj.setSource(sourceParam);
consignmentObj.setStatus(statusParam);
//consignmentObj.setItems(itemsParam);

DataAccessManager dam = new DataAccessManager();
dam.addConsignment(consignmentObj);

//reset the DTobject
consignmentObj = new ConsignmentTO();
//request.getSession().setAttribute(TRANSPORTConstants.IContextInfoConstants.TRANSPORT_DTO, consignmentObj);

}
else if (isClearConsignment)
{
consignmentObj = new ConsignmentTO();
//request.getSession().setAttribute(TRANSPORTConstants.IContextInfoConstants.TRANSPORT_DTO, consignmentObj);
}
else if (consignmentObj==null)
{
consignmentObj = new ConsignmentTO();
//request.getSession().setAttribute(TRANSPORTConstants.IContextInfoConstants.TRANSPORT_DTO, consignmentObj);
}
else //just update from the values
{
//todo check the other fields for nullity as well
consignmentObj.setConsignmentId(consignmentIdParam);
consignmentObj.setType(typeParam);
consignmentObj.setDestination(campParam);
consignmentObj.setSource(sourceParam);
consignmentObj.setStatus(statusParam);

int consignmentID = consignmentObj.getConsignmentId();

ConsignmentItemTO consignmentItemTO = new 
    ConsignmentItemTO(consignmentIDParameter,itemParameter, 
    quantityParameter, uoMParameter , 0, null, null, null);
//items.add(consignmentItemTO);

//clear the params here
quantityParameter = null;
itemParameter =null;
uoMParameter = null;
}
%>

<!--table1--><table width="100%" border="0" cellspacing="0" cellpadding="0">

<tr>
<td>

<!--table11--><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr align="left">
<td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
<td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="Search_Consignment.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search
Request</font></a>&nbsp;&nbsp;</td>
<td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
<td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log
off&nbsp;&nbsp;&nbsp;&nbsp;</font></a></td>
</tr>

<!--/table11--></table>
</td>
</tr>
<tr>
<td>
<!--table12--><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
<%--<td width="134" height="350" valign="top" class="leftMenuBG"><img src="images/spacer.gif" width="160" height="10"></td>--%>
<%-- <td><img src="images/Blank.gif" width="10" height="10"></td><td width="100%">&nbsp;</td>--%>

<!--table121--><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
<td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Add Consignment  </td>
</tr>
<tr>
<td >&nbsp;</td>
<td >&nbsp;</td>
</tr>
<tr>
<td colspan="2">
<!--table1211--><table width="100%" border="0" cellspacing="0" cellpadding="0">
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
<!--/table1211--></table>

</td>
</tr>
<tr>
<td>&nbsp;</td>
<td class="formText">
     <font color="red"> 
     </font>
</td>
</tr>
<tr>
<td colspan="2">
<!--table1212--><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>

<td width="20%" class="formText">&nbsp;</td>
<td colspan="4">
<!--table12121--><table>
<!--/table12121--></table>
</td>
</tr>
<tr>
<td class="formText">&nbsp;Consignment Id</td>
<td colspan="4"><input maxlength="50" type="text" name="consignmentId" class="textBox" width="150" value="
<%=consignmentObj.getConsignmentId()%>" />&nbsp;<small><font color="red">*</font></small> </td>
</tr>
<tr>
<td class="formText">&nbsp;Type </td>
<td colspan="4"><select name="districts" class="textBox">
                   <option selected value="Regular">Regular</option>
                                       <option value="Ad hoc">Ad hoc</option>
                                       <option value="Excess">Excess</option>
                                       </select>&nbsp;<small><font color="red">*</font></small></td>
                                       </tr>

<tr>
<td class="formText">&nbsp;Source</td>
<td colspan="4"><input type="text" name="source" class="textBox" value="
<%=consignmentObj.getSource()%>" />&nbsp;<small><font color="red">*</font></small></td>
</tr>
<tr>
<td>&nbsp;</td>
<td colspan="4">&nbsp;</td>
</tr>

<tr>
<td class="formText">&nbsp;Destination </td>
<td colspan="4"/>

<tr>
<td class="formText">&nbsp;Divisions </td>
<td colspan="4"><select name="districts" class="textBox">
                   <%
                       DataAccessManager dam = new DataAccessManager();
                       Collection divisionList=null;
                       try{
                           divisionList =  dam.getAllDivisions();
                           if(divisionList != null){
                               Iterator ditr = divisionList.iterator();
                               while(ditr.hasNext()){
                                   KeyValueDTO division = (KeyValueDTO) ditr.next();
                                   String divisionCode = division.getDbTableCode();
                                   String divisionvalue = division.getDisplayValue();
                                   if (divisionParam.equals(divisionCode)){
                   %>
                   <option selected value="<%=divisionCode%>"><%=divisionvalue%></option>
                                       <%
                                   }else{
                                       %>
                                       <option value="<%=divisionCode%>"><%=divisionvalue%></option>
                                       <%
                                   }
                               }
                           }
                       }catch(Exception e) {
                           throw new Exception(e);
                       }
                                       %>
                                       </select>&nbsp;</td>

</tr>
<tr>
<td class="formText">&nbsp;Camps </td>
<td colspan="4"><select name="camp" class="textBox">
                   <%
                       DataAccessManager dam = new DataAccessManager();
                       Collection campList=null;
                       try{
                           campList =  dam.getAllCamps();
                           if(campList != null){
                               Iterator ditr = campList.iterator();
                               while(ditr.hasNext()){
                                   KeyValueDTO district = (KeyValueDTO) ditr.next();
                                   String campCode = district.getDbTableCode();
                                   String campvalue = district.getDisplayValue();
                                   if (consignmentObj.getDestination().equals(campCode)){
                   %>
                   <option selected value="<%=campCode%>"><%=campvalue%></option>
                                       <%
                                   }else{
                                       %>
                                       <option value="<%=campCode%>"><%=campvalue%></option>
                                       <%
                                   }
                               }
                           }
                       }catch(Exception e) {
                           throw new Exception(e);
                       }
                                       %>
                                       </select>&nbsp;</td>

</tr>
</tr>

<tr>
<td colspan="5"/>
<tr>

<tr>
<td colspan="5">&nbsp;Items</td>
</tr>

<tr>
<td height="22" class="formText">&nbsp;Item Code</td>
<td colspan="4"><select name="Item Code" class="textBox">
                   <%
                       Collection itemList=null;
                       try{
                           itemList =  dam.getAllItems();
                           if(itemList != null){
                               Iterator citr = itemList.iterator();
                               while(citr.hasNext()){
                                   KeyValueDTO item = (KeyValueDTO) citr.next();
                                   String itemCode = item.getDbTableCode();
                                   String itemvalue = item.getDisplayValue();
                        if (itemParameter.equals(itemCode)){
                           %>
                   <option value="<%=itemCode%>" selected="true"><%=itemvalue%></option>
                   <%
                        }else{
                   %>
                   <option value="<%=itemCode%>"><%=itemvalue%></option>
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
                   <td width="10%" class="formText">Quantity</td>
                   <td width="18%"><input type="text" name="quantity" class="textBox" maxlength="10" value="<%=quantityParameter==null?"":quantityParameter%>"  ></td>
                   <td >&nbsp;</td>
                   <td class="formText">&nbsp;UoM</td>
                   <td colspan="1"><select name="UoM" class="textBox">
                   <%
                       Collection uoMList=null;
                       try{
                           uoMList =  dam.getAllUoM();
                           if(uoMList != null){
                               Iterator pitr = uoMList.iterator();
                               while(pitr.hasNext()){
                                   KeyValueDTO uoMDTO = (KeyValueDTO) pitr.next();
                                   String uoMCode = uoMDTO.getDbTableCode();
                                   String uoMvalue = uoMDTO.getDisplayValue();

                                   if (uoMParameter.equals(uoMCode)){
                                     %>
                                   <option value="<%=uoMCode%>" selected="true"><%=uoMvalue%></option>
                      <%
                                   }else{
                   %>
                                   <option value="<%=uoMCode%>"><%=uoMvalue%></option>
                      <%
                               }
                               }
                           }
                       }catch(Exception e) {
                           throw new Exception(e);
                       }
                      %>
                      </select></td>
                      <td colspan="2" >&nbsp;</td>
                      <td align="right"  ><input name="Submit1" type="button" value="Add to List" class="buttons" onclick="validate(2)" ></td>
</tr>
<!--/table1212--></table>
</td>
                      </tr>
                      <tr>
                      <td>&nbsp;</td>
                      <td colspan="4">&nbsp;</td>
                      </tr>
                      <tr>
                      <td colspan="2">
<%--<div id="Layer1" style="position:auto; left:150px; top:279px; width:100%; height:200px; z-index:1; overflow: auto;overflow-x">--%>
<div id="Layer1" style="position:auto; left:150px; top:279px; width:100%;z-index:1; overflow: auto;overflow-x">
<!--table1213--><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr >
<td class="tableUp">#</td>
<td class="tableUp">Item</td>
<td class="tableUp">Qty</td>
<td class="tableUp">UOM</td>
</tr>


<%
    Collection consignmentItems = consignmentObj.getConsignmentItems();
    Iterator iterator = consignmentItems.iterator();
    ConsignmentItemTO    tempConsignmentItemDto;
    while (iterator.hasNext()) {
        tempConsignmentItemDto =(ConsignmentItemTO) iterator.next();
%>
<tr>
<td class="tableDown"><%=tempConsignmentItemDto.getItemCode()%></td>
<td class="tableDown" nowrap="false" width="200"  ><%=tempConsignmentItemDto.getItemCode()%></td>
<td class="tableDown"><%=tempConsignmentItemDto.getIssuedQty()%></td>
<td class="tableDown"><%=tempConsignmentItemDto.getUoM()%></td>
</tr>
        <%
    }
        %>

<!--/table1213--></table>

</div></td>
</tr>
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
<tr>

<td class="formTitle" colspan="2">
<!--table1214--><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
<td width="73%">&nbsp;</td>
<td width="12%" align="right"><input type="button" name="Submit2" value="Save" class="buttons" onclick="validate(1)" />&nbsp;<input type="button" name="Submit2" value="Clear" class="buttons" onclick="validate(3)" /></td>
</tr>
<!--/table1214--></table>
</td>
</tr>
<tr>
<td colspan="2" class="pageBg">&nbsp;</td>
</tr>
<!--/table121--></table>
</tr>
<!--/table12--></table>
</td>
</tr>
<tr>
<td></td>
</tr>
<!--/table1--></table>
</form>
<jsp:include page="comman/internalfooter.inc"></jsp:include>
<jsp:include page="comman/footer.inc"></jsp:include>

</body>
</html>
