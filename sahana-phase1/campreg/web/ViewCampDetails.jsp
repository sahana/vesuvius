<%@ page import="org.campdb.business.CampTO,
                 org.campdb.db.DataAccessManager,
                 org.campdb.util.StringUtil,
                 org.campdb.business.User,
                 org.campdb.util.CAMPDBConstants,
                 java.util.Iterator,
                 java.util.List,
                 org.campdb.business.CampHistoryTO"%>


<%
    if (request.getParameter("campId") == null) {
        response.sendRedirect("SearchCamps.jsp");
        return;
    }
    int campID = 0;
    try {
        campID = Integer.parseInt(request.getParameter("campId"));
    } catch (NumberFormatException e) {
        response.sendRedirect("SearchCamps.jsp");
        return;
    }
    DataAccessManager dataAccessManager = new DataAccessManager();
    CampTO camp = dataAccessManager.searchCamp(campID);
    List historyList = dataAccessManager.getHistory(camp);
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>:: Sahana :: Camp Database</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
<script>
//
</script>
</head>

<body topmargin="0" leftmargin="0">
   <%  User user = (User) session.getAttribute(CAMPDBConstants.IContextInfoConstants.USER_INFO);
       if(user == null){
         request.getSession().setAttribute(CAMPDBConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User has not been authenticated. Please login  !!");
         response.sendRedirect("error.jsp");
        }
    %>
   <jsp:include page="comman/header.inc"></jsp:include>


                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr align="left">
                        <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                        <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="SearchCamps.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search
                        Camp</font></a>&nbsp;&nbsp;</td>
                        <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="InsertCamps.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Add
                        Camp</font></a>&nbsp;&nbsp;</td>

                        <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                        <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="LogOff.jsp" style="text-decoration:none"><font color="#000000">Log
                        off&nbsp;&nbsp;&nbsp;&nbsp;</font></a></td>
                </tr>
                </table>


            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                 <tr>
                   <td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Camp Details  </td>
                 </tr>
             </table>

            <table width="80%" border="0">
                <tr>
                    <td vAlign="top" class="tableUp" align="left" colspan="6" rowspan="2" ><b>Location Information</b></td>
                </tr>
                <tr>
                    <td colspan="6" >&nbsp;</td>
                </tr>

                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >CampId</td><td colspan="4" ><%=StringUtil.returnEmptyForNull(camp.getCampId())%></td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left">Camp Name</td><td colspan="4"><%=StringUtil.returnEmptyForNull(camp.getCampName())%></td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left">Province</td><td colspan="4"><%=StringUtil.returnEmptyForNull(camp.getProvienceName())%></td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left">District</td><td colspan="4"><%=StringUtil.returnEmptyForNull(camp.getDistrictName())%></td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left">Division</td><td colspan="4"><%=StringUtil.returnEmptyForNull(camp.getDivionName())%></td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left">Area</td><td colspan="4"><%=StringUtil.returnEmptyForNull(camp.getAreaName())%></td>
                </tr>

                <tr>
                    <td colspan="6">&nbsp;</td>
                </tr>

                <tr>
                    <td vAlign="top" class="tableUp" align="left" colspan="6" rowspan="2"><b>Contact Information</b></td>
                </tr>
                <tr>
                    <td colspan="6">&nbsp;</td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left">Conatct Person</td><td colspan="4"><%=StringUtil.returnEmptyForNull(camp.getCampContactPerson())%></td>
                </tr>
               <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left">Contact Number</td><td colspan="4"><%=StringUtil.returnEmptyForNull(camp.getCampContactNumber())%></td>
                </tr>
                <tr>
                    <td colspan="6">&nbsp;</td>
                </tr>
                <tr>
                    <td vAlign="top" class="tableUp" align="left" colspan="6"><b>People Information</b></td>
                </tr>

                                        <tr>
                                            <td class="tableUp" align="left" >Number of Families</td>
                                            <td class="tableUp" align="left">Number of Men</td>
                                            <td class="tableUp" align="left">Number of Women</td>
                                            <td class="tableUp" align="left">Number of Children</td>
                                            <td class="tableUp" align="left">Total </td>
                                            <td class="tableUp" align="left">Date</td>
                                        </tr>
                                        <%
                                            int count = historyList.size();
                                            for (int i = 0; i < count; i++) {
                                                CampHistoryTO historyTo = (CampHistoryTO) historyList.get(i);

                                            %>

                                     <tr>
                                            <td class="tableDown" align="left"><%=StringUtil.returnEmptyForNull(historyTo.getCampFamily())%></td>
                                            <td class="tableDown" align="left"><%=StringUtil.returnEmptyForNull(historyTo.getCampMen())%></td>
                                            <td class="tableDown" align="left"><%=StringUtil.returnEmptyForNull(historyTo.getCampWomen())%></td>
                                            <td class="tableDown" align="left"><%=StringUtil.returnEmptyForNull(historyTo.getCampChildren())%></td>
                                            <td class="tableDown" align="left"><%=StringUtil.returnEmptyForNull(historyTo.getCampTotal())%> </td>
                                            <td class="tableDown" align="left"><%=historyTo.getUpdateDate()%></td>
                                        </tr>

                                        <%  }%>


                <tr>
                    <td vAlign="top" class="tableUp" align="left" colspan="6" ><b>General Information</b></td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left">Accessability</td><td  colspan="4" valign="top" ><%=StringUtil.returnEmptyForNull(camp.getCampAccesability())%></td>
                </tr>
               <tr>
                    <td >&nbsp;</td><td vAlign="top" class="formText" align="left">Capability</td><td  colspan="4"  valign="top"><%=StringUtil.returnEmptyForNull(camp.getCampCapability())%></td>
                </tr>
               <tr>
                    <td>&nbsp;</td><td vAlign="top"  rowspan="2" class="formText" align="left"  >Comment  </td><td colspan="4" valign="top"><%=StringUtil.returnEmptyForNull(camp.getCampComment())%></td>
                </tr>
                 <tr>
                    <td colspan="6">&nbsp;</td>
                </tr>
                <tr>
                    <td colspan="6">&nbsp;</td>
                </tr>
            </table>
             <table align="center" >
                     <tr>
                        <td class="formText" align="center">
                                <a href="Welcome.jsp">Camp Registry Home</a>
                        </td>
                    </tr>
                </table>

               <jsp:include page="comman/footer.inc"></jsp:include>
</body>
</html>

