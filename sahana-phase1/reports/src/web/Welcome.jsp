<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 org.erms.business.User"%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
<title>:: Sahana ::</title>
<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>
<body>

<jsp:include page="comman/header.inc"></jsp:include>
    <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">
   <%
       DataAccessManager dataAccessManager = new DataAccessManager();
       String username = request.getParameter("userName");
       String password = request.getParameter("password");

       User user = null;
       try {
           user = dataAccessManager.loginSuccess(username, password);
       } catch (Exception e) {
           e.printStackTrace();
           request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION, "Problem with validating login information " );
           response.sendRedirect("error.jsp");
       }
       if( !"".equals(username) && user != null) {
           request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.USER_INFO, user);
   %>

      <tr>
            <td width="134" valign="top"><img src="images/imgloginrqstms.jpg" width="302" height="200" border="0"></td>
            <td valign="top" bgcolor="#D8E9FD">
           <table width="760" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="34%" class="formText" >&nbsp;</td>
                <td width="66%"  >&nbsp;</td>
              </tr>
              <tr>
              <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                <td  nowrap class="formText" align="left" ><strong><a href="Add_Request.jsp" style="text-decoration:none"  class="style1">Add Request</a></strong> </td>
                </tr>
                <tr>
              <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                
                <td  nowrap class="formText" align="left" ><strong><a href="Search_Request.jsp?<%=ERMSConstants.ISearchConstants.SEARCH_REQUEST%>" style="text-decoration:none"  class="style1">Search Request</a></strong> </td>
                </tr>
<%--                <tr>--%>
<%--                <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>--%>
<%--                <td  nowrap class="formText" align="left"><strong><a href="Logoff.jsp" style="text-decoration:none"  class="style1">LogOff</a></strong></td>--%>
<%--                </tr>--%>

<%--Needs to invalidate the session. So have to go to log off first--%>
                <tr>
                <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                <td  nowrap class="formText" align="left"><strong><a href="Logoff.jsp" style="text-decoration:none"  class="style1">Home</a></strong></td>
                </tr>
              </table>

<%--              <tr>--%>
<%--                <td class="formText">&nbsp;</font></td>--%>
<%--                <td >&nbsp;</td>--%>
<%--              </tr>--%>
<%--              <tr>--%>
<%--                <td class="formText"><font size="2"><a href="Add_Request.jsp">Add Request </a><font></font></td>--%>
<%--                <td >&nbsp;</td>--%>
<%--              </tr>--%>
<%--           <tr>--%>
<%--               <td class="formText"><font size="2"><a href="Search_Request.jsp">Search Request</a></font></td>--%>
<%--                <td class="formText"><font size="2">Search Request</font></td>--%>
<%--                <td >&nbsp;</td>--%>
<%--              </tr><tr>--%>
<%--              <td class="formText"><font size="2"><a href="Logoff.jsp">Log off</a><font></td>--%>
<%--                <td >&nbsp;</td>--%>
<%--              </tr>--%>
             <%
           }else{  %>
                <tr>
                <td class="formText" align="center" ><font size="2">Invalid Username / Password. Please <a href="Index.jsp">Try Again</a></font></td>
                <td >&nbsp;</td>
              </tr>
      <%
       }
      %>
      </table>

      <jsp:include page="comman/footer.inc"></jsp:include>
      </body>
</html>