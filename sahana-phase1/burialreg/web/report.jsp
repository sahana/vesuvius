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
<table width="100%">
       <tr><td>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr align="left" background="images/BannerBG.jpg">
             <td class="statusBar" background="images/BannerBG.jpg" >
              <a href="AddBurialGround.jsp"><font color="#000000">&nbsp;&nbsp;Add Burial Site Record</font></a>&nbsp;&nbsp;
               <font color="#000000">Logged in as <%=user.getUserName()%> of <%=user.getOrganization()%></font></font>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
               <a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log off&nbsp;&nbsp;&nbsp;&nbsp;
             </td>
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
              %>
       <tr><td>
            <table width="100%" border="1" cellspacing="0" cellpadding="0">
                <tr >
                    <td class="tableUp" align="left" width="7.5%">Burial Ground Code</td>
                    <td class="tableUp" align="left" width="7.5%">Province</td>
                    <td class="tableUp" align="left" width="7.5%">Division</td>
                    <td class="tableUp" align="left" width="7.5%">District</td>
                    <td class="tableUp" align="left" width="7.5%">Area</td>
                    <td class="tableUp" align="left" width="40%">Site Description</td>
                    <td class="tableUp" align="left" width="7.5%">Burial Total</td>
                    <td class="tableUp" align="left" width="7.5%">Authority Person Name</td>
                    <td class="tableUp" align="left" width="7.5%">Authority Name</td>
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
                               + "provinceCode="+site.getProvinceCode() + "&"
                               + "districtCode="+site.getDistrictCode() + "&"
                               + "divisionCode="+site.getDivisionCode() + "&"
                               + "area="+site.getArea()+ "&"
                               + "siteDescription="+site.getSitedescription()+ "&"
                               + "burialdetail="+site.getBurialdetail()+ "&"
                               + (site.getGpsLongitude()==null?"":("gpsLongitude="+site.getGpsLongitude()+ "&"))
                               + (site.getGpsLattitude()==null?"":("gpsLattitude="+site.getGpsLattitude()+ "&"))
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
                    <td class="tableData" align="left"> <%=site.getProvinceCode()==null?"&nbsp;":dam.getProvince(site.getProvinceCode())%></td>
                    <td class="tableData" align="left"> <%=site.getDivisionCode()==null?"&nbsp;":dam.getDiviosion(site.getDivisionCode())%></td>
                    <td class="tableData" align="left"> <%=site.getDistrictCode()==null?"&nbsp;":dam.getDistrict(site.getDistrictCode())%></td>
                    <td class="tableData" align="left"> <%=site.getArea()==null?"&nbsp;":site.getDistrictCode()%></td>
                    <td class="tableData" align="left"> <%=s1%></td>
                    <td class="tableData" align="left"><%=site.getBodyCountTotal()%></td>
                    <td class="tableData" align="left"> <%=site.getAuthorityPersonName()%></td>
                    <td class="tableData" align="left"> <%=site.getAuthorityName()%></td>
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