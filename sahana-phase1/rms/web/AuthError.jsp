<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="common/style.css" rel="stylesheet" type="text/css">
</head>

<body>
 <jsp:include page="comman/header.inc"/>

 <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">
    <tr>
        <td align="center" > <font size="3" color="red">An error has occured!</font></td>
    </tr>

    <tr>
        <td align="center" > <font size="3" color="red"><% if (request.getParameter("messages") != null)
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
<jsp:include page="comman/footer.inc"/>
</body>