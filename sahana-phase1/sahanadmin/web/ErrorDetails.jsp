<%@ page isErrorPage = "true" %>
<html>
<head>
<title>
ErrorDetails
</title>
</head>
<body>

<%
Throwable t = (Throwable)request.getAttribute("javax.servlet.jsp.jspException");
%>
<p>&nbsp;</p>
<hr color="#000000">
<table width="95%" border="0" align="center" cellpadding="10" cellspacing="0">
  <tr>
    <td><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong>Message:
      </strong>&nbsp;
    <% if (t != null) {

    if (t.getMessage()!=null)
      out.print(t.getMessage());
    else
      out.print("System Error");
   }
   else
      out.print("System Error");
    %>
</font>
    </td>
  </tr>
</table>
<p>
</body>
</html>
