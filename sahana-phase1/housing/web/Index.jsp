
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<jsp:useBean id="LoginBean" scope="session" class="tccsol.admin.accessControl.LoginBean"/>
<html>
<head>
<title>:: Sahana :: Housing Registry</title>
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
      <form name="loginForm" action="Welcome.jsp" method="post">

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
<%--                        <% if (errors.size() > 0) {--%>
<%--                            for (Iterator iterator = errors.iterator(); iterator.hasNext();) {--%>
<%--                                String s = (String) iterator.next();--%>
<%--                        %>--%>
                        <tr align="left" >
                        <td height="23" colspan="2" align="center" >
                        <font face="Arial, Helvetica, sans-serif" color="red" size=-2">
<%--                        <li><%=s %></li>--%>
                        </font></td>
                        </tr>
<%--                        <%--%>
<%----%>
<%--                            }--%>
<%--                        %>--%>
<%----%>
<%--                        <% } %>--%>
                        <tr>
                        <td>&nbsp;</td>
                        <td><table width="100%" border="0" cellspacing="2" cellpadding="0">
                        <tr>
                        <td width="34%" class="formText">User Name</td>
                        <td width="66%"><input name="userName" type="text" id="userName" value="<%=LoginBean.getUserName()%>" class="textBox" size="20"></td>
                        </tr>
                        <tr>
                        <td class="formText">Password</td>
                        <td><input name="passwd" type="password" id="passwd"  class="textBox" size="20"></td>
                        </tr>
                        <tr>
                        <td>&nbsp;</td>
                        <td><table width="100" border="0" cellspacing="0" cellpadding="0">
                        <tr>
                        <td>
                        <input name="callAction" type="submit" id="callAction" value="Log in"  class="buttons">
                        <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
                        </td>
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

