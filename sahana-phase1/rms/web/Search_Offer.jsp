<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 java.sql.SQLException,
                 org.erms.business.RequestSearchTO,
                 org.erms.business.OfferSearchCriteriaTO,
                 org.erms.business.OfferSearchTO,
                 java.text.Format,
                 java.text.SimpleDateFormat,
                 org.erms.business.User,
                 org.sahana.share.utils.KeyValueDTO" %>
<%@ page import="java.util.*" %>
<%@ page import="java.io.IOException" %>

<jsp:useBean id="newOfferSearch" scope="page" class="org.erms.business.OfferSearchCriteriaTO" />
<jsp:setProperty name="newOfferSearch" property="*" />
<jsp:useBean id="offerSearchCriteriaTO" scope="session" class="org.erms.business.OfferSearchCriteriaTO" />
<jsp:setProperty name="offerSearchCriteriaTO" property="*" />

<%
    request.setAttribute("turl", "Welcome.jsp");
    request.setAttribute("modNo", "2");
    request.setAttribute("accessLvl", "SEARCH");
%>
<%@include file="/admin/accessControl/AccessControl.jsp" %>


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

function searchForm()
{
	document.form1.submitType.value="SEARCH";

}


function selectEntityType(){

   var selectedEntity = document.form1.offeringEntityType.value;

   document.hiddenForm.offeringEntityType.value = selectedEntity;
   document.hiddenForm.submit();

  }






</script>
</head>

 <!--  document.form1.offeringEntityType.value="";
    document.form1.orgCode.value="";
    document.form1.targetArea.value="";
    document.form1.category.value="";
    document.form1.item.value="";
-->

<body topmargin="0" leftmargin="0">

<jsp:include page="comman/header.inc"></jsp:include>
<form name="form1" action="Search_Offer.jsp" method="post">
<input type="hidden" name="submitType"/>

<%
    //OfferSearchCriteriaTO offerSearchCriteriaTO = null;
    OfferSearchCriteriaTO temprequestSearchCriteriaTO = null;
    LoginBean userBean = (LoginBean) session.getAttribute("LoginBean");

    //checking the authentication
   //User user = (User) request.getSession().getAttribute(ERMSConstants.IContextInfoConstants.USER_INFO);

    //if (user == null) {
      //  request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION,"User not authenticated!");
        //response.sendRedirect("error.jsp");
    //}

    DataAccessManager dam = new DataAccessManager();
    ArrayList searchDetails = new ArrayList();

//Sending search details
//TODO: to add functionality to persist data
    if (offerSearchCriteriaTO == null) {
        offerSearchCriteriaTO = new OfferSearchCriteriaTO();
    }

    String submitType = request.getParameter("submitType");


    if (submitType !=null && submitType.equals("SEARCH")){  //mainRequest != null &&

        temprequestSearchCriteriaTO = new OfferSearchCriteriaTO();

        temprequestSearchCriteriaTO.setOrgCode(newOfferSearch.getOrgCode());
        temprequestSearchCriteriaTO.setTargetArea(newOfferSearch.getTargetArea());
        temprequestSearchCriteriaTO.setCategory(newOfferSearch.getCategory());
        temprequestSearchCriteriaTO.setItem(newOfferSearch.getItem());
        temprequestSearchCriteriaTO.setOfferingEntityType(newOfferSearch.getOfferingEntityType());
        temprequestSearchCriteriaTO.setOfferingIndividual(newOfferSearch.getOfferingIndividual());

        searchDetails = (ArrayList)dam.searchOffers(temprequestSearchCriteriaTO);
        request.removeAttribute(ERMSConstants.ISearchConstants.SEARCH);

    }

     offerSearchCriteriaTO.setOrgCode(newOfferSearch.getOrgCode());
     offerSearchCriteriaTO.setTargetArea(newOfferSearch.getTargetArea());
     offerSearchCriteriaTO.setCategory(newOfferSearch.getCategory());
     offerSearchCriteriaTO.setItem(newOfferSearch.getItem());
     offerSearchCriteriaTO.setOfferingEntityType(newOfferSearch.getOfferingEntityType());
     offerSearchCriteriaTO.setOfferingIndividual(newOfferSearch.getOfferingIndividual());

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
<td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="Add_offer.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Add
Offer</font></a>&nbsp;&nbsp;</td>
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
<td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Search offer  </td>
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
<td colspan="2" class="formText"><strong>Organization : <%=userBean.getOrgName()%> &nbsp;&nbsp;User : &nbsp<%=userBean.getUserName()%> &nbsp;&nbsp;Date : <%=formattedDate%></strong></td>
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
                                                          <td class="formText" align="right" >&nbsp;Offering Entity Type &nbsp;</td>

                                                          <td colspan="4"><select name="offeringEntityType" onchange="selectEntityType();"    class="textBox">
                                                                                                                  <option <%=offerSearchCriteriaTO.getOfferingEntityType().equalsIgnoreCase("Individual")?"selected=\"true\"":""%> value="Individual">Individual</option>
                                                          <option <%=newOfferSearch.getOfferingEntityType().equalsIgnoreCase("Organization")?"selected=\"true\"":""%> value="Organization">Organization</option>
                                                          </select></td>

                                         </tr>


                                         <%
                                             if(offerSearchCriteriaTO.getOfferingEntityType().equalsIgnoreCase("Individual")) {
                                         %>

                                         <tr>
                                            <td class="formText" align="right" >&nbsp;Contact Name &nbsp;</td>
                                            <td colspan="4"><input maxlength="50" type="text" name="offeringIndividual" class="textBox" width="150" value="<%=offerSearchCriteriaTO.getOfferingIndividual()%>" />&nbsp;<!--<small><font color="red">*</font></small> </td>  -->
                                            </tr>

                                         <%
                                             } else {
                                         %>


											<tr>
												<td class="formText" align="right" >&nbsp;Organization &nbsp;</td>
												<td colspan="4"><select name="orgCode" class="textBox">
                                            <option value="">&lt;select&gt;</option>



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

                                                    if (offerSearchCriteriaTO.getOrgCode().equals(orgCode)) {%>
                                                    <option selected value="<%=orgCode%>"><%=orgName%></option>
                                                                                        <%} else {%>
                                                                                        <option value="<%=orgCode%>"><%=orgName%></option>
                                                                                        <%}
                                                }
                                            }
                                        } catch (Exception e) {
                                            out.print("Exception occurd " + e);
                                        }%>

												</select></td></tr>
                                        <%
                                             }
                                        %>






											<tr>
												<td class="formText" align="right" >&nbsp;Target Area &nbsp;</td>
												<td colspan="4"><select name="targetArea" class="textBox">
<option value="">&lt;select&gt;</option>

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
                                                    if (offerSearchCriteriaTO.getTargetArea().equals(districtCode)) {%>
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

												<td>&nbsp;</td>
												<td colspan="4">&nbsp;</td>
											</tr>
											<tr>
												<td height="22" class="formText" align="right" >&nbsp;Category &nbsp;</td>
												<td colspan="4"><select name="category" class="textBox">
                                           <option value="">&lt;select&gt;</option>

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
                                                                    if (offerSearchCriteriaTO. getCategory().equals(categoryCode)) {%>
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
												<td class="formText" align="right" >&nbsp;Item &nbsp;</td>
												<td height="25" colspan="4"><input type="text" name="item"
													class="textBox"
													value="<%=offerSearchCriteriaTO.getItem()%>"></td>
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
													name="submit" value="Search" onclick="searchForm()"  class="buttons">&nbsp;</td>
												<td width="22%" align="right"><input type="reset"
													name="cancel" value="Reset" onclick="resetForm()" class="buttons">&nbsp;</td>

											</tr>
										</table>
										</td>
									</tr>
									<tr>
										<td class="formText">&nbsp;</td>
										<td height="25">&nbsp;</td>
									</tr>

<%
                                                if(submitType != null  && searchDetails.isEmpty()){
                                            %>

                                                 <tr>
                                                    <td align="center" ><h3>There were no results found for specified search criteria</h3></td>
                                                 </tr>
                                                <tr>
                                                    <td class="formText">&nbsp;</td>
                                                    <td height="25">&nbsp;</td>
                                                </tr>

                                              <%
                                                }else{
%>

									<tr>
										<td colspan="2">
										<table width="100%" border="0" cellspacing="0" cellpadding="0">
											<tr class="formTitle">
												<td class="tableUp" width="120" >Item</td>
												<td class="tableUp">Unit</td>
                                                <td class="tableUp">Quantity</td>
												<td class="tableUp">Category</td>
                                                <td class="tableUp">Organization/Individual</td>
												<td class="tableUp">Target Area</td>
                                                <td class="tableUp">Time Frame</td>
                                                <td class="tableUp">Equivalent value</td>

											</tr>
                                              <%
                                                Iterator iterator = searchDetails.iterator();
                                                System.out.println(searchDetails.size());
OfferSearchTO offerSearchTO;
while (iterator.hasNext()) {
	offerSearchTO = (OfferSearchTO) iterator.next();

%>
											<tr>
												<td class="tableDown" nowrap="true" width="120"><a style="text-decoration:none"><%=offerSearchTO.getItem()%></a></td>
												<td class="tableDown"><a  style="text-decoration:none"><%=offerSearchTO.getUnit()%></a></td>
												<td class="tableDown"><a  style="text-decoration:none"><%=offerSearchTO.getQuantity()%></a></td>
												<td class="tableDown"><a  style="text-decoration:none"><%=offerSearchTO.getCategory()%></a></td>
									     		<td class="tableDown"><a  style="text-decoration:none"><%=(offerSearchTO.getOfferingIndividual().equalsIgnoreCase("") || offerSearchTO.getOfferingIndividual()==null) ? offerSearchTO.getOrgCode():offerSearchTO.getOfferingIndividual() %></a></td>

                                                <td class="tableDown" align="left" ><a  style="text-decoration:none"><%=(offerSearchTO.getTargetArea().equalsIgnoreCase("") || offerSearchTO.getTargetArea()==null)?"N/A":offerSearchTO.getTargetArea()%></a></td>
                                                <td class="tableDown" align="left" ><a  style="text-decoration:none"><%=offerSearchTO.getTimeFrame()%></a></td>
                                                 <td class="tableDown" align="left" ><a  style="text-decoration:none"><%=offerSearchTO.getEqValue()%></a></td>

											</tr>
											<%}%>
										</table>
										</td>
									</tr>
                              <%} %>


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

<form method="POST" action="Search_Offer.jsp" name="hiddenForm">
        <input type="hidden" name="offeringEntityType" value=""/>
</form>



<jsp:include page="comman/footer.inc"></jsp:include>

</body>
</html>
