<%--<%@ page import="org.erms.util.ERMSConstants"%>--%>
<%@ page isErrorPage="true" %>

<html>
<head>
<title>:: Housing ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>

<body>
 <jsp:include page="common/header.inc"/>

 <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">
    <%
        exception.printStackTrace();
    %>
    <tr>
        <td align="center" > <font size="3" color="red">An error has occured!</font></td>
    </tr>
    <tr>
        <td align="center" >Message : <%=exception.getMessage()%></td>
    </tr>
    <tr>
        <td align="center" >&nbsp;</td>
    </tr>
    <tr>
<td class="formText" align="center">
       <a href="Index.jsp">Organization Registry Home</a>
</td>
</tr>
 </table>
 <jsp:include page="common/footer.inc"/>
</body>