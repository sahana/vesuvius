<%@ page language="java" errorPage="/ErrorDetails.jsp"%>

<html>
<head>
<title>Admin</title>
</head>
<body bgcolor="#FFFFFF">
<br>
<H5><font face="Verdana, Arial, Helvetica, sans-serif">Access Control </font></h5>
<hr noshade color="#000000">
<%
if (request.getAttribute("messages")!=null)
{
    java.util.Vector v = (java.util.Vector) request.getAttribute("messages");
    if (v.size() > 0)
    {
    for(int i=0;i<v.size();i++)
    {
%><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
    <%=v.elementAt(i)%></font></li>
<%
    }//end of for loop
    }
}//end of if
%>
</body>
</html>
