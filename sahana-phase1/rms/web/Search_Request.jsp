<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 java.sql.SQLException,
                 org.erms.business.RequestSearchTO,
                 org.erms.business.RequestSearchCriteriaTO,
                 java.text.Format,
                 java.text.SimpleDateFormat,
                 org.erms.business.User" %>
<%@ page import="org.erms.business.KeyValueDTO" %>
<%@ page import="java.util.*" %>
<%@ page import="java.io.IOException" %>
<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<script language='javascript'
	src='commonControls/popupcal/popcalendar.js'></script>
<link href="comman/style.css" rel="stylesheet" type="text/css">
<script>
function resetForm()
{
	document.form1.submitType.value="CLEAR";
}
</script>
</head>

<body topmargin="0" leftmargin="0">

<jsp:include page="comman/header.inc"></jsp:include>
<form name="form1" action="Search_Request.jsp" method="post">
<input type="hidden" name="submitType"/>

<%
    RequestSearchCriteriaTO requestSearchCriteriaTO = null;
    RequestSearchCriteriaTO temprequestSearchCriteriaTO = null;

    User user =
            (User) request.getSession().getAttribute(
                    ERMSConstants.IContextInfoConstants.USER_INFO);


    if (user == null) {
        request.getSession().setAttribute(
                ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION,
                "User not authenticated!");
        response.sendRedirect("error.jsp");
    }

    DataAccessManager dam = new DataAccessManager();
    ArrayList searchDetails = new ArrayList();

//Sending search details
//TODO: to add functionality to persist data
    if (requestSearchCriteriaTO == null) {
        requestSearchCriteriaTO = new RequestSearchCriteriaTO();
    }
    String mainRequest = request.getParameter(ERMSConstants.ISearchConstants.SEARCH);
    String submitType = request.getParameter("submitType");


    String strOrganization 	= "";
    String strsiteName 		= "";
    String strdistricts 	= "";
    String strcategory 		= "";
    String strsiteArea 		= "";
    String stritem 			= "";
    String strpriority 		= "";
    String strStatus 		= "";


    if (mainRequest == null && submitType !=null && !submitType.equals("CLEAR")){

        strOrganization = request.getParameter("organization");
        strsiteName = request.getParameter("siteName");
        strdistricts = request.getParameter("districts");
        strcategory = request.getParameter("categories");
        stritem = request.getParameter("item");
        strStatus = request.getParameter("status");
        strpriority = request.getParameter("priority");

        temprequestSearchCriteriaTO = new RequestSearchCriteriaTO();
        temprequestSearchCriteriaTO.setOrganization((strOrganization!=null && !strOrganization.equals("select"))?strOrganization:null);
        temprequestSearchCriteriaTO.setSiteName((strsiteName!=null && !strsiteName.equals(""))?strsiteName:null);
        temprequestSearchCriteriaTO.setSiteDistrict((strdistricts != null && !strdistricts.equals("select"))?strdistricts:null);
        temprequestSearchCriteriaTO.setCategory((strcategory!=null && !strcategory.equals("select"))?strcategory:null);
        temprequestSearchCriteriaTO.setItem((stritem != null && !stritem.equals(""))?stritem:null);
        temprequestSearchCriteriaTO.setPriority((strpriority!=null && !strpriority.equals("select"))?strpriority:null);
        temprequestSearchCriteriaTO.setStatus((strStatus!=null && !strStatus.equals("select"))?strStatus:null);

        searchDetails = (ArrayList)dam.searchRequests(temprequestSearchCriteriaTO);
        request.removeAttribute(ERMSConstants.ISearchConstants.SEARCH);

    }
    requestSearchCriteriaTO.setOrganization((strOrganization!=null && !strOrganization.equals("select"))?strOrganization:"");


    requestSearchCriteriaTO.setSiteName(strsiteName!=null?strsiteName:"");
    requestSearchCriteriaTO.setSiteDistrict((strdistricts != null && !strdistricts.equals("select"))?strdistricts:"");
    requestSearchCriteriaTO.setCategory((strcategory!=null && !strcategory.equals("select"))?strcategory:"");
    requestSearchCriteriaTO.setItem(stritem!=null?stritem:"");
    requestSearchCriteriaTO.setPriority((strpriority!=null && !strpriority.equals("select"))?strpriority:"");
    requestSearchCriteriaTO.setStatus(request.getParameter("status")!=null?request.getParameter("status"):"");


    if (searchDetails == null) {
        searchDetails = new ArrayList();
    }
%>


<table width="100%" border="0" cellspacing="0" cellpadding="0">

<tr>
<td>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr align="left">
<td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
<td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="Add_Request.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Add
Request</font></a>&nbsp;&nbsp;</td>
<td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
<td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log
off&nbsp;&nbsp;&nbsp;&nbsp;</font></a></td>
</tr>
</table>
</td>
</tr>
<tr>
<td>						
<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
<!--								<td width="134" height="350" valign="top" class="leftMenuBG"><img
									src="images/spacer.gif" width="160" height="10"></td>-->
								<td >
<table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
<td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Search request  </td>
</tr>
<tr>
<td width="117">&nbsp;</td>
<td width="484">&nbsp;</td>
</tr>
<tr>
<td colspan="2">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
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
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
<tr>
<td colspan="2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>

										<table width="100%" border="0" cellspacing="0" cellpadding="0">
											<tr>
												<td width="20%" class="formText">&nbsp;Organization</td>
												<td colspan="4"><select name="organization" class="textBox">
<option value="select">&lt;select&gt;</option>
 	 										     
<%
                                        Collection organizationList = null;
                                        try {
                                            organizationList = dam.getAllOrganizationNames();
                                            if (organizationList != null) {

                                                Iterator orgItr = organizationList.iterator();

                                                while (orgItr.hasNext()) {
                                                    KeyValueDTO organization = (KeyValueDTO) orgItr.next();
                                                    String orgCode = organization.getDbTableCode();
                                                    String orgName = organization.getDisplayValue();

                                                    if (requestSearchCriteriaTO.getOrganization().equals(orgCode)) {%>
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
												<td class="formText">&nbsp;Requester Name</td>
												<td colspan="4"><input type="text" name="callerName"
													class="textBox"
													value="<%=requestSearchCriteriaTO.getCallerName()==null?"":requestSearchCriteriaTO.getCallerName()%>"></td>
											</tr>
											<tr>
												<td class="formText">&nbsp;Site Name</td>
												<td colspan="4"><input type="text" name="siteName"
													class="textBox"
													value="<%=requestSearchCriteriaTO.getSiteName()==null?"":requestSearchCriteriaTO.getSiteName()%>"></td>
											</tr>
											<tr>
												<td>&nbsp;</td>
												<td colspan="4">&nbsp;</td>
											</tr>
											<tr>
												<td class="formText">&nbsp;Site District</td>
												<td colspan="4"><select name="districts" class="textBox">
<option value="select">&lt;select&gt;</option>
 	 										     
<%
                                        Collection districtList = null;
                                        try {
                                            districtList = dam.getAllDistricts();
                                            if (districtList != null) {
                                                Iterator ditr = districtList.iterator();
                                                while (ditr.hasNext()) {
                                                    KeyValueDTO district = (KeyValueDTO) ditr.next();
                                                    String districtCode = district.getDbTableCode();
                                                    String districtvalue = district.getDisplayValue();
                                                    if (requestSearchCriteriaTO.getSiteDistrict().equals(districtCode)) {%>
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
											</tr>
											<tr>
												<td class="formText">&nbsp;Site Area</td>
												<td colspan="4"><input type="text" name="siteArea"
													class="textBox"
													value="<%=requestSearchCriteriaTO.getSiteArea()==null?"":requestSearchCriteriaTO.getSiteArea()%>">
													</td>
												</tr>
											<tr>
												<td>&nbsp;</td>
												<td colspan="4">&nbsp;</td>
											</tr>
											<tr>
												<td height="22" class="formText">&nbsp;Category</td>
												<td colspan="4"><select name="categories" class="textBox">
<option value="select">&lt;select&gt;</option>

                  							  	<%
                                                        Collection categoryList = null;
                                                        try {
                                                            categoryList = dam.getAllCategories();
                                                            if (categoryList != null) {
                                                                Iterator citr = categoryList.iterator();
                                                                while (citr.hasNext()) {
                                                                    KeyValueDTO category = (KeyValueDTO) citr.next();
                                                                    String categoryCode = category.getDbTableCode();
                                                                    String categoryValue = category.getDisplayValue();
                                                                    if (requestSearchCriteriaTO. getCategory().equals(categoryCode)) {%>
                                                                    <option selected value="<%=categoryCode%>"><%=categoryValue%></option>
													<%} else {%>
                                                    <option value="<%=categoryCode%>"><%=categoryValue%></option>
													<%}
                                                                }
                                                            }
                                                        } catch (Exception e) {
                                                            out.print("Exception occurd " + e);
                                                        }%>
												</select></td>
											</tr>
											<tr>
												<td class="formText">&nbsp;Item</td>
												<td height="25" colspan="4"><input type="text" name="item"
													class="textBox"
													value="<%=requestSearchCriteriaTO.getItem()%>"></td>
											</tr>

											<tr>
												<td class="formText">&nbsp;Priority</td>
												<td colspan="4"><select name="priority" class="textBox">
<option value="select">&lt;select&gt;</option>
											   
													
<%
                                                Collection priorityList = null;
                                                try {
                                                    priorityList = dam.getAllPriorities();
                                                    if (priorityList != null) {
                                                        Iterator pitr = priorityList.iterator();
                                                        while (pitr.hasNext()) {
                                                            KeyValueDTO priorityDTO = (KeyValueDTO) pitr.next();
                                                            String priorityCode = priorityDTO.getDbTableCode();
                                                            String priorityvalue = priorityDTO.getDisplayValue();
                                                            if (requestSearchCriteriaTO. getPriority().equals(priorityCode)) {%>
                                                            <option selected value="<%=priorityCode%>"><%=priorityvalue%></option>
                                                        <%} else {%>
                                                        <option value="<%=priorityCode%>"><%=priorityvalue%></option>
                                                        <%}
                                                        }
                                                    }
                                                } catch (Exception e) {
                                                    throw new Exception(e);
                                                }%>
												</select></td>
											</tr>
											<tr>

												<td class="formText">&nbsp;Status</td>
												<td height="25" colspan="4">
                                                    <select name="status" class="textBox">
                                                    <option value="select">&lt;select&gt;</option>
                                                    <%
                                                        Collection statusList = null;
                                                        try {
                                                            statusList = dam.getAllSearchStatuses();
                                                            if (statusList != null) {
                                                                Iterator pitr = statusList.iterator();
                                                                while (pitr.hasNext()) {
                                                                    KeyValueDTO priorityDTO = (KeyValueDTO) pitr.next();
                                                                    String statusCode = priorityDTO.getDbTableCode();
                                                                    String statusValue = priorityDTO.getDisplayValue();
                                                                    if (requestSearchCriteriaTO. getStatus().equals(statusCode)) {%>
                                                                    <option selected value="<%=statusCode%>"><%=statusValue%></option>
			                                                         <%} else {%>
                                                                    <option value="<%=statusCode%>"><%=statusValue%></option>
			                                                        <%}
                                                                }
                                                            }
                                                        } catch (Exception e) {
                                                            throw new Exception(e);
                                                        }%>


                                                    </select>
												</td>
											</tr>
										</table>
										</td>
									</tr>
									<tr>
										<td class="formText">&nbsp;</td>
										<td height="13">&nbsp;</td>
									</tr>
									<tr class="formTitle">
										<td class="formText">&nbsp;</td>
										<td height="25">
										<table width="100%" border="0" cellspacing="0" cellpadding="0">
											<tr>
												<td width="64%" height="30">&nbsp;</td>
												<td width="14%" align="right"><input type="submit"
													name="submit" value="Search" class="buttons">&nbsp;</td>
												<td width="22%" align="right"><input type="submit"
													name="cancel" value="Reset" onclick="resetForm()" class="buttons">&nbsp;</td>

											</tr>
										</table>
										</td>
									</tr>
									<tr>
										<td class="formText">&nbsp;</td>
										<td height="25">&nbsp;</td>
									</tr>
									<tr>
										<td colspan="2">
										<table width="100%" border="0" cellspacing="0" cellpadding="0">
											<tr class="formTitle">
												<td class="tableUp" width="120" >Item</td>
												<td class="tableUp">Unit</td>
                                                <td class="tableUp">Quantity</td>
												<td class="tableUp">Priority</td>
											    <td class="tableUp">Status</td>
												<td class="tableUp">Site District</td>
												<td class="tableUp">Site Area</td>
												<td class="tableUp">Site Name</td>
												<td class="tableUp">Category</td>
											</tr>
											<%Iterator iterator = searchDetails.iterator();
RequestSearchTO requestSearchTO;
while (iterator.hasNext()) {
	requestSearchTO = (RequestSearchTO) iterator.next();
%>
											<tr>
												<td class="tableDown" nowrap="true" width="120"><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%=requestSearchTO.getItem()%></a></td>
												<td class="tableDown"><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%=requestSearchTO.getUnits()%></a></td>
												<td class="tableDown"><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%=requestSearchTO.getQuantity()%></a></td>
												<td class="tableDown"><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%=requestSearchTO.getPriority()%></a></td>
									     		<td class="tableDown"><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%=requestSearchTO.getStatus()%></a></td>
												<td class="tableDown" align="left" ><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%=requestSearchTO.getSiteDistrict()%></a></td>
                                                <td class="tableDown" align="left"><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%="".equals(requestSearchTO.getSiteArea())?"&nbsp;":requestSearchTO.getSiteArea()%></a></td>
												<td class="tableDown" align="left"><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%=requestSearchTO.getSiteName()!=null?requestSearchTO.getSiteName():""%></a></td>
												<td class="tableDown"><a href="Fulfill_rq.jsp?<%=ERMSConstants.REQUEST_DETAIL_ID + "=" + requestSearchTO.getRequestDetId()%>" style="text-decoration:none"><%=requestSearchTO.getCategory()%></a></td>
											</tr>
											<%}%>
										</table>
										</td>
									</tr>
									<tr>
										<td>&nbsp;</td>
										<td>&nbsp;</td>
									</tr>

									<tr>
										<td colspan="2" class="pageBg">&nbsp;</td>
									</tr>
								</table>
								</td>
							</tr>
						</table>
						</td>
					</tr>
					<tr>
						<td>
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
                                <td class="formText" align="center">
                                        <a href="Welcome.jsp">Request Management Home</a>
                                </td>
                            </tr>
						</table>
						</td>
					</tr>
				</table>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</form>

<jsp:include page="comman/footer.inc"></jsp:include>

</body>
</html>
