<%@ page import="org.burial.db.DataAccessManager,
                 org.burial.business.UserTO,
                 org.burial.util.Constants,
                 org.burial.util.Constants"%>
<html>
<head>
<title>:: Sahana ::</title>
<link href="common/style.css" rel="stylesheet" type="text/css">
</head>
<body>

<jsp:include page="common/header.inc"></jsp:include>
    <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">
     <%

         boolean isAuthenticated = false;
         String username = request.getParameter("userName");
         String password = request.getParameter("password");

         if (request.getSession()==null){
             throw new Exception("Session expired!");
         }else if(request.getSession().getAttribute(Constants.USER_INFO)!=null){
             //user is already logged in. Do nothing
             isAuthenticated = true;
         }else {
             DataAccessManager dataAccessManager = DataAccessManager.getInstance();
              UserTO user = null;
             try {
                 user = dataAccessManager.loginSuccess(username, password);
             } catch (Exception e) {
                 throw new Exception("Problem in validating user");
             }
             if( !"".equals(username) && user != null) {
                 request.getSession().setAttribute(Constants.USER_INFO, user);
                 isAuthenticated = true ;
             }else{
                 isAuthenticated = false;
             }
         }

       if (isAuthenticated){
   %>
      <tr>
            <td width="134" valign="top"><img src="images/imgLoginAssistance.jpg" width="302" height="200" border="0"></td>
            <td valign="top" bgcolor="#D8E9FD">
           <table width="760" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="34%" class="formText" >&nbsp;</td>
                <td width="66%"  >&nbsp;</td>
              </tr>
              <tr>
              <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                <td  nowrap class="formText" align="left" ><strong><a href="AddBurialGround.jsp" style="text-decoration:none"  class="style1">Add Burial Ground</a></strong> </td>
                </tr>
                <tr>
              <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>

                <td  nowrap class="formText" align="left" ><strong><a href="report.jsp" style="text-decoration:none"  class="style1">Search</a></strong> </td>
                </tr>
              </table>
      <% }else{  %>
                <tr>
                <td class="formText" align="center" ><font size="2">Invalid Username / Password. Please <a href="index.jsp">Try Again</a></font></td>
                <td >&nbsp;</td>
              </tr>
      <% } %>
      </table>
      <jsp:include page="common/footer.inc"></jsp:include>
      </body>
</html>