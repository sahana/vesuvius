<%@ page import="org.burial.db.DataAccessManager,
                 org.burial.util.Constants,
                 org.burial.business.UserTO,
                 java.util.List,
                 java.util.Iterator,
                 java.util.Collection,
                 org.burial.business.BurialSiteDetailTO"%><html>
<head>
<title>:: Sahana ::</title>
<link href="common/style.css" rel="stylesheet" type="text/css">
<%
            DataAccessManager dam =  DataAccessManager.getInstance();
            //Is he authenticated
		   	UserTO user = (UserTO) request.getSession().getAttribute(Constants.USER_INFO);
		    if (user==null){
		    	//Nobody should come here without a user
		   	    request.getSession().setAttribute(Constants.ERROR_DESCRIPTION, "User not authenticated!");
		       	response.sendRedirect("error.jsp");
		    }
%>
</head>
<body>

<jsp:include page="common/header.inc"></jsp:include>
<%--    <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">--%>
<%--      <tr>--%>
<%--            <td width="134" valign="top"><img src="images/imgLoginAssistance.jpg" width="302" height="200" border="0"></td>--%>
<%--            <td valign="top" bgcolor="#D8E9FD">--%>
<%--      </tr>--%>
<%--    </table>--%>
<%--    <h2>Reports Goes Here</h2>--%>
<table width="100%">
       <tr><td>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr align="left" background="images/BannerBG.jpg">
             <td class="statusBar" background="images/BannerBG.jpg" >
              <a href="AddBurialGround.jsp"><font color="#000000">&nbsp;&nbsp;Add Burial Site Record</font></a>&nbsp;&nbsp;
               <font color="#000000">Logged in as <%=user.getUserName()%> of <%=user.getOrganization()%></font></font>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
               <a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log off&nbsp;&nbsp;&nbsp;&nbsp;
             </td>
<%--                <td class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>--%>
<%--                <td class="statusBar"  background="images/BannerBG.jpg" bgcolor="#000099"><a href="AddOfferAssistance.jsp"><font color="#000000">&nbsp;&nbsp;Add Assitance Offers</font></a>&nbsp;&nbsp;</td>--%>
<%--                <td class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>--%>
<%----%>
<%--                <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar" > <font color="#000000">Logged in <%=user.getUserName()%> of <%=user.getOrganization()%></font></font></td>--%>
<%----%>
<%--                <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log--%>
<%--                            off&nbsp;&nbsp;&nbsp;&nbsp;</font></a>--%>
<%--                </td>--%>
            </tr>
       </table>
       </td></tr>

        <!--- Banner is in ------>
       <tr><td>
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                 <td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">View All Sites</td>
                </tr>
                <tr>
                    <td width="117">&nbsp;</td>
                    <td width="484">&nbsp;</td>
                </tr>
                <tr>
                    <td>&nbsp;</td>
                    <td>&nbsp;</td>
                </tr>
              </table>
          </td></tr>

              <%
                  Collection offers = dam.getAllSites();
                  Iterator iterator = offers.iterator();
                  BurialSiteDetailTO site = null;

//                      private String provinceCode;
//                      private String districtCode;
//                      private String divisionCode;
//                      private String area;
//
//                      private String sitedescription;
//                      private String burialdetail;
//                      private int bodyCountTotal;
//                      private int bodyCountMmen;
//
//                      private int bodyCountWomen;
//                      private int bodyCountChildren;
//                      private int gpsLattitude;
//                      private int gpsLongitude;
//
//                      private String authorityPersonName;
//                      private String authorityName;
//                      private String authorityPersonRank;
//                      private String authorityReference;

              %>
       <tr><td>
            <table width="100%" border="1" cellspacing="0" cellpadding="0">
                <tr >
                    <td class="tableUp" align="center" width="7.5%">&nbsp;Burial Ground Code</td>
                    <td class="tableUp" align="left" width="7.5%"> &nbsp;Province</td>
                    <td class="tableUp" align="left" width="7.5%"> &nbsp;Devision</td>
                    <td class="tableUp" align="left" width="7.5%"> &nbsp;Destrict</td>
                    <td class="tableUp" align="left" width="7.5%"> &nbsp;Area</td>
                    <td class="tableUp" align="left" width="40%"> &nbsp;Site Description</td>
                    <td class="tableUp" align="center" width="7.5%"> &nbsp;Burial Totel</td>
                    <td class="tableUp" align="center" width="7.5%"> &nbsp;Authority Person Name</td>
                    <td class="tableUp" align="center" width="7.5%"> &nbsp;Authority Name</td>
              </tr>

              <%
                  while (iterator.hasNext()) {
                      site =  (BurialSiteDetailTO)iterator.next();
                 String s1= site.getSitedescription();
                 if (s1 == null)
                    s1 = "&nbsp;";
                 else
                    if (s1.length() > 100)
                        s1= s1.subSequence(0, 100)+"...";
              %>

                <tr>
                    <td class="tableData" align="left">
                    <%
                       String url ="AddBurialGround.jsp?"
                               + "province="+site.getProvinceCode() + "&"
                               + "district="+site.getDistrictCode() + "&"
                               + "division="+site.getDivisionCode() + "&"
                               + "area="+site.getArea()+ "&"
                               + "site="+site.getSitedescription()+ "&"
                                + "burialdetail="+site.getBurialdetail()+ "&"
                               + "gpsLongitude="+site.getGpsLongitude()+ "&"
                               + "gpsLattitude="+site.getGpsLattitude()+ "&"
                               + "bodyCountTotal="+site.getBodyCountTotal()+ "&"
                               + "bodyCountMmen="+site.getBodyCountMmen()+ "&"
                               + "bodyCountWomen="+site.getBodyCountWomen()+ "&"
                               + "bodyCountChildren="+site.getBodyCountChildren()+ "&"
                               + "authorityPersonName="+site.getAuthorityPersonName()+ "&"
                               + "authorityName="+site.getAuthorityName()+ "&"
                               + "authorityPersonRank="+site.getAuthorityPersonRank()+ "&"
                               + "authorityReference="+site.getAuthorityReference();

                    %>
                        <a href="<%=url%>"><%=site.getBurialSiteCode()%></a>
                    </td>
                    <td class="tableData" align="left"> <%=dam.getProvince(site.getProvinceCode())%></td>
                    <td class="tableData" align="left"> <%=dam.getDiviosion(site.getDivisionCode())%></td>
                    <td class="tableData" align="left"> <%=dam.getDistrict(site.getDistrictCode())%></td>
                    <td class="tableData" align="left"> <%=site.getArea()%></td>
                    <td class="tableData" align="left"> <%=s1%></td>
                    <td class="tableData" align="center"> <%=site.getBodyCountTotal()%></td>
                    <td class="tableData" align="left"> <%=site.getAuthorityPersonName()%></td>
                    <td class="tableData" align="left"> <%=site.getAuthorityName()%></td>
<%--                    <td class="tableData" align="left">--%>
<%--                        <%--%>
<%--                            if(site.getAuthorityName().equals(user.getOrgCode())){%>--%>
<%--                                <a href="AddOfferAssistance.jsp?<%=org.burial.util.Constants.EDIT%>=<%=addOfferAssistanceTO.getId()%>" style="text-decoration:none"  class="style1">Edit</a>--%>
<%--                            <%}--%>
<%--                            else{ %>--%>
<%--                                <a href="AddOfferAssistance.jsp?<%=org.assistance.Constants.VIEW%>=<%=addOfferAssistanceTO.getId()%>" style="text-decoration:none"  class="style1">View</a>--%>
<%--                            <%}--%>
<%--                        %>--%>
<%--                    </td>--%>
              </tr>

              <%
                  }
              %>

        </table>
        </td></tr>
</table>
      <jsp:include page="common/welcomefooter.inc"></jsp:include>
      <jsp:include page="common/footer.inc"></jsp:include>

</body>
</html>