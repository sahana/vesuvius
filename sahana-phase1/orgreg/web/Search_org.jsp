<%@ page import="java.util.Collection,
                 java.util.Iterator,
                 org.erms.business.RequestDetailTO,
                 java.util.List,
                 org.erms.db.DataAccessManager,
                 org.erms.business.OrganizationTO,
                 org.erms.db.DBConstants"%>
 <%--
Created by IntelliJ IDEA.
User: Ajith
Date: Jan 2, 2005
Time: 9:34:24 AM
To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head><title>:: Sahana Organization Registry ::</title></head>
<link href="comman/style.css" rel="stylesheet" type="text/css">
<body>

<jsp:include page="comman/header.inc"></jsp:include>


<table width="760" border="0" cellspacing="0" cellpadding="0">
<tr>
<td class="border">
<table width="100%" border="0" cellspacing="1" cellpadding="0">
<tr>
<td class="pageBg">

<table width="100%" border="0" cellspacing="0" cellpadding="0">
    <tr >
    <td class="tableUp">Organization Name</td>
    <td class="tableUp">Organization Address</td>
    <td class="tableUp">Organization Contact Number</td>
    <td class="tableUp">Orgnization Email Address</td>
    <td class="tableUp">Country of Origin</td>
    <td class="tableUp">Facilities available</td>
    <td class="tableUp">Working areas</td>
 </tr>


<%
    List requestDetails = new DataAccessManager().getAllOrganizations();
    OrganizationTO orgTo;
    for (int i = 0; i < requestDetails.size(); i++) {
        orgTo = (OrganizationTO) requestDetails.get(i);
%>
<tr>
<%--<td class="tableDown"><a href="EditOrganization.jsp?OrgCode=<%=orgTo.getOrgCode()%>"><%=orgTo.getOrgName()%></a></td>--%>
<td class="tableDown"><%=orgTo.getOrgName()%></td>
<td class="tableDown"><%=orgTo.getOrgAddress()%></td>
<td class="tableDown"><%=orgTo.getContactNumber()%></td>
<td class="tableDown"><%=orgTo.getEmailAddress()%></td>
<td class="tableDown"><%=orgTo.getCountryOfOrigin()%></td>
<td class="tableDown"><%=orgTo.getFacilitiesAvailable()%></td>
<td class="tableDown"><%=orgTo.getWorkingAreas()%></td>
</tr>
 <%
    }
 %>



</table></td>
</tr>
<tr>
<td class="formText" align="center">
       <a href="Index.jsp">Organization Registry Home</a>
</td>
</tr>
</table>
</td>
</tr>
</table>

<jsp:include page="comman/footer.inc"></jsp:include>

</body>
</html>