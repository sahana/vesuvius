<%@ page import="org.erms.util.ERMSConstants"%>
 <%--
  Created by IntelliJ IDEA.
  User: Ajith
  Date: Jan 1, 2005
  Time: 12:36:52 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<html>
  <head><title>:: Sahana ::</title></head>
  <link href="comman/style.css" rel="stylesheet" type="text/css">
  <body>

  <%
      //clear the session
      request.getSession().invalidate();

      //sending back to home
      response.sendRedirect("/index.html");
  %>

    <jsp:include page="comman/header.inc"/>

   <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">
    <tr>
        <td align="center" class="formText"> You have succesfully logged off</td>
    </tr>
    <tr>
        <td align="center" class="formText">&nbsp;</td>
    </tr>
    <tr>
        <td align="center" class="formText" ><a href="Index.jsp">Click here</a> to login again</td>
    </tr>
 </table>
 <jsp:include page="comman/footer.inc"/>

  </body>
</html>