<%@ page import="java.util.LinkedList,
                 java.util.List,
                 java.text.SimpleDateFormat,
                 java.util.ArrayList,
                 java.util.Iterator,
                 org.housing.landreg.util.LabelValue,
                 org.housing.landreg.db.DataAccessManager,
                 org.sahana.share.db.DBConstants,
                 org.housing.landreg.business.LandTO,
                 org.housing.landreg.util.StringUtil"%>
<jsp:useBean id="newLand" scope="page" class="org.housing.landreg.business.LandTO" />
<jsp:setProperty name="newLand" property="*" />

<%
    if (request.getParameter("landId") == null) {
        response.sendRedirect("SearchLands.jsp");
        return;
    }
    int landID = 0;
    try {
        landID = Integer.parseInt(request.getParameter("landId"));
    } catch (NumberFormatException e) {
        response.sendRedirect("SearchLands.jsp");
        return;
    }
    DataAccessManager dataAccessManager = new DataAccessManager();
    LandTO land = dataAccessManager.searchLand(landID);
    newLand.copyFrom(land);
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>:: Sahana :: Camp Database</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="../comman/style.css" rel="stylesheet" type="text/css">
<script>
//
</script>
</head>

<body topmargin="0" leftmargin="0">

   <jsp:include page="../common/header.inc"></jsp:include>


                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr align="left">
                        <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                        <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="SearchLands.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search Lands</font></a>&nbsp;&nbsp;</td>
                        <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="InsertLand.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Add Land</font></a>&nbsp;&nbsp;</td>

                        <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                        <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="LogOff.jsp" style="text-decoration:none"><font color="#000000">Log
                        off&nbsp;&nbsp;&nbsp;&nbsp;</font></a></td>
                </tr>
                </table>


            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                 <tr>
                   <td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">View Land  </td>
                 </tr>
             </table>

            <table width="80%" border="0">
                <tr>
                    <td vAlign="top" class="tableUp" align="left" colspan="6" rowspan="2" ><b>Land Information</b></td>
                </tr>
                <tr>
                    <td colspan="6" >&nbsp;</td>
                </tr>

                 <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >Land Name </td><td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getLandName())%></td>
                </tr>
                 <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >Description</td><td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getDescription())%></td>
                </tr> <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >Province</td><td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getprovinceName())%></td>
                </tr>
                 <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >District</td><td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getDistrictName())%></td>
                </tr>
                 <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >Division</td><td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getdivisionName())%></td>
                </tr>
                 <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >Area</td><td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getArea())%>
                    &nbsp;&nbsp;<%=StringUtil.returnEmptyForNull(newLand.getMeasurementTypeName())%></td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >Owned By</td><td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getOwnedByName())%></td>
                    <td vAlign="top" class="formText" align="left" >Comments &nbsp;&nbsp;<%=StringUtil.returnEmptyForNull(newLand.getOwnedByComment())%></td>
                </tr>
                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >Term</td><td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getTermName())%></td>
                </tr>

                <tr>
                    <td>&nbsp;</td><td vAlign="top" class="formText" align="left" >GPS Co-ordinates</td>
                    <td colspan="2" ><%=StringUtil.returnEmptyForNull(newLand.getGPS1())%> &nbsp;
                    <%=StringUtil.returnEmptyForNull(newLand.getGPS2())%> &nbsp;
                    <%=StringUtil.returnEmptyForNull(newLand.getGPS3())%> &nbsp;
                    <%=StringUtil.returnEmptyForNull(newLand.getGPS4())%></td>
                </tr>


            </table>
             <table align="center" >
                     <tr>
                        <td class="formText" align="center">
                                <a href="Welcome.jsp">Housing Registry Home</a>
                        </td>
                    </tr>
                </table>

               <jsp:include page="../common/footer.inc"></jsp:include>
</body>
</html>

