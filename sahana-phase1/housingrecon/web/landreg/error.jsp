<%@ page import="org.housing.landreg.util.DBConnectionConstants"%>
<%@ page isErrorPage="true" %>

<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>

<body>
 <jsp:include page="../common/header.inc"/>

 <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">
    <tr>
        <td align="center" > <font size="3" color="red">An error has occured!</font></td>
    </tr>
    <%
               // String errorDescription = (String) request.getSession().getAttribute(DBConnectionConstants.IContextInfoConstants.ERROR_DESCRIPTION);
               // if(errorDescription != null){
        %>
    <tr>
        <!--<td align="center" > <font size="3" color="red"><=errorDescription%></font></td>-->
    </tr>
    <%
      //}
        if(exception != null){
    %>


    <tr>
        <td align="center" >Message : <%=exception.getMessage()%></td>
    </tr>
    <%
   exception.printStackTrace();
        }
    %>
    <tr>
        <td align="center" >&nbsp;</td>
    </tr>
    <tr>
<td class="formText" align="center">
       <a href="Index.jsp">Land Registery Home</a>
</td>
</tr>
 </table>
 <jsp:include page="../common/footer.inc"/>
</body>