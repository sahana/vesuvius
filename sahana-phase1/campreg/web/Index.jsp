<%@ page import="org.campdb.db.DataAccessManager,
                 java.util.List,
                 java.util.LinkedList,
                 org.campdb.business.User,
                 org.campdb.util.CAMPDBConstants,
                 java.util.Iterator"%>
   <%
       List errors = new LinkedList();
       if (request.getParameter("doLogin") != null) {
           DataAccessManager dataAccessManager = new DataAccessManager();
           String username = request.getParameter("userName");
           String password = request.getParameter("password");
           if (username == null || username.trim().length() <= 0) {
               errors.add("Username is required.");
           }
           if (password == null || password.trim().length() <= 0) {
               errors.add("Password is required.");
           }
           if (errors.size() <= 0) {
               User user = null;
               try {
                   user = dataAccessManager.loginSuccess(username, password);
                   if (user == null) {
                       errors.add("Invalid UserName/Password");
                   }
               } catch (Exception e) {
                   errors.add("Database error. Try later.");
                   e.printStackTrace(System.err);
               }
               if (errors.size() <= 0) {
                   session.setAttribute(CAMPDBConstants.IContextInfoConstants.USER_INFO, user);
                   pageContext.forward("Welcome.jsp");
               }
           }
       }
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


<table width="100%" border="0">
<tr>

<td height="50" >
      <jsp:include page="comman/header.inc"></jsp:include>
      </td>

      </tr>
      <tr>
      <td height="100%" align="left" valign="top">
      <form name="loginForm" action="Index.jsp" method="post">

      <table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
      <td class="border">
      <table width="100%" border="0" cellspacing="1" cellpadding="0">
      <tr>
      <td class="pageBg">
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
      <td>&nbsp;</td>
      </tr>
      <tr>
      <td>
      </td>
      </tr>
      <tr>
      <td><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
      <td width="134" valign="top"><img src="images/imgLogin.jpg" width="302" height="200" border="0"></td>
      <td valign="top" bgcolor="#D8E9FD">
      <table width="100%" border="0" cellpadding="0" cellspacing="0">
      <tr align="left" >
      <td height="23" colspan="2" background="images/BannerBG.jpg"><font face="Arial, Helvetica, sans-serif"><strong>&nbsp;&nbsp;User
      Login</strong></font></td>
      </tr>
                        <% if (errors.size() > 0) {
                            for (Iterator iterator = errors.iterator(); iterator.hasNext();) {
                                String s = (String) iterator.next();
                        %>
                        <tr align="left" >
                        <td height="23" colspan="2" align="center" >
                        <font face="Arial, Helvetica, sans-serif" color="red" size=-2">
                        <li><%=s %></li>
                        </font></td>
                        </tr>
                        <%

                            }
                        %>

                        <% } %>
                        <tr>
                        <td>&nbsp;</td>
                        <td><table width="100%" border="0" cellspacing="2" cellpadding="0">
                        <tr>
                        <td width="34%" class="formText">User Name</td>
                        <td width="66%"><input tabindex="0"   name="userName" type="text" class="textBox" size="20"></td>
                        </tr>
                        <tr>
                        <td class="formText">Password</td>
                        <td><input name="password" type="password" class="textBox" size="20"></td>
                        </tr>
                        <tr>
                        <td>&nbsp;</td>
                        <td><table width="100" border="0" cellspacing="0" cellpadding="0">
                        <tr>
                        <td><input type="submit" name="doLogin" value="Log in" class="buttons"></td>
                        </tr>
                        <!-- register link -->
                        <tr>
                        <td class="formText">If you are a new user <a href="/orgreg/Registration.jsp"> Click here </a>to register </td>
                        <td>&nbsp;</td>
                        </tr>
                        <!-- end of register link -->
                        </table>

<label>
                        </label></td>
                        </tr>
                        </table></td>
                        </tr>
                        </table></td>
                        </tr>
                        </table></td>
                        </tr>
                        </table>
                        </td>
                        </tr>
                        </table>
                        </td>
                        </tr>
                        </table>
                        </form>
                        </td>
                        </tr>
                  <tr>
                        <td>
      <jsp:include page="comman/footer.inc"></jsp:include>
      </td>
      </tr>
      </table>
</body>
</html>

