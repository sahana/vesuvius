<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.business.User,
                 tccsol.admin.accessControl.LoginBean,
                 java.sql.Connection"%>
 <%--
  Created by IntelliJ IDEA.
  User: Deepal Jayasinghe
  Date: Jan 11, 2005
  Time: 2:02:29 PM
  To change this template use File | Settings | File Templates.
--%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<jsp:useBean id="user" scope="request" class="org.erms.business.User" />
<jsp:setProperty name="user" property="*" />
<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
<script>
//
</script>
</head>

<body topmargin="0" leftmargin="0">
<jsp:include page="comman/header.inc"></jsp:include>

<%
    DataAccessManager dataAccessManager = new DataAccessManager();
    String password = null;
    if (request.getParameter("Submit") == null) {  //data comes from the database
        if (request.getParameter("orgCode") == null) {
            response.sendRedirect("Search_org.jsp");
            return;
        }
        String orgCode = "";
        orgCode = request.getParameter("orgCode");
        session.setAttribute("orgCode",request.getParameter("orgCode"));
        user = dataAccessManager.getUser(orgCode);
        password = user.getPassword();
    } else {
        String userName =user.getUserName();
        password = user.getPassword();
        String action = (String) session.getAttribute("action");
        user = dataAccessManager.getUser((String)session.getAttribute("orgCode"));

        if (user.getPassword().equals(password) && user.getUserName().equalsIgnoreCase(userName)){

            tccsol.admin.accessControl.LoginBean lbean = new tccsol.admin.accessControl.LoginBean();
            lbean.setUserName(user.getUserName());
            tccsol.sql.DBConnection econ = new tccsol.sql.DBConnection();
            Connection c = econ.getConnection();
            String value = econ.getValue(c, user.getUserName(), "tblUserRoles", "RoleId", "UserName", 'S');
            try{
                lbean.setRoleId(Long.parseLong(value));
            }catch(NumberFormatException e){
                throw new Exception("you don't have permission to do this operation");
            }
            econ.closeConnection();
            lbean.setOrgId(user.getOrganization());
            lbean.setValid(true);
            session.setAttribute("LoginBean", lbean);
            new tccsol.admin.accessControl.AuditLog().logEntry(user.getUserName(), "4", "Login"); //Organization reg is module no. 4
            response.sendRedirect("Registration.jsp?action="+action+ "&orgCode=" + (String)session.getAttribute("orgCode") +"&isEdit=Y");
         } else {
           %>
                <h2 class="formText" align="center" ><font size="2">Invalid Username / Password. Please <a href="Logging.jsp">Try Again</a></font></h2>
             </body>
           <jsp:include page="comman/footer.inc"></jsp:include>
         </html>

      <%
             return;
         }
    }

%>
<form name="logging" action="Logging.jsp" method="post">
          <%
              session.setAttribute("action", request.getParameter("action"));
          %>
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
          <tr>
            <td>&nbsp;</td>
            <td><table width="100%" border="0" cellspacing="2" cellpadding="0">
              <tr>
                <td width="34%" class="formText">User Name</td>
                <td width="66%"><input name="userName" type="text" class="textBox" size="20"></td>
              </tr>
              <tr>
                <td class="formText">Password</td>
                <td><input name="password" type="password" class="textBox" size="20" > </td>
              </tr>
              <tr>
                <td>&nbsp;</td>
                <td><table width="100" border="0" cellspacing="0" cellpadding="0">
                  <tr>
                    <td><input type="submit" name="Submit" value="Log in" class="buttons"></td>
                  </tr>
                </table>                  <label>
                </label></td>
              </tr>
            </table></td>
          </tr>
          <tr>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
          </tr>
        </table></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td>

    </td>
  </tr>
</table>
</td>
</tr>
</table>
</td>
</tr>
</table>
</form>

<jsp:include page="comman/footer.inc"></jsp:include>

</body>
</html>
