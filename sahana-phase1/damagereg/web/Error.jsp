<!--
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*
-->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
<style type="text/css">
<!--
.style1 {color: #333333}
.style2 {color: #FF3300}
.style3 {color: #999999}
-->
</style>
</head>

<body topmargin="0" leftmargin="0">

<jsp:include page="includes/header.inc"></jsp:include>

 <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">
    <tr>
        <td align="center" > <font size="3" color="red">System Error! Please Contact Administrator.</font></td>
    </tr>

    <tr>
        <td align="center" > <font size="3" color="red"><%
if (request.getParameter("messages") != null)
{
  out.print(request.getParameter("messages"));
}

%></font></td>
    </tr>
<%--    <tr>--%>
<%--<td class="formText" align="center">--%>
<%--       <a href="index.jsp">Assistance Home</a>--%>
<%--</td>--%>
<%--</tr>--%>
 </table>

<p></p>
Go <a href="<%= request.getContextPath() %>/Welcome.jsp">back</a>  to Welcome Page.
<br><br>

<jsp:include page="includes/footer.inc"></jsp:include>

</body>
</html>
