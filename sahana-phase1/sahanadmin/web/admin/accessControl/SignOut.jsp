<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<%
if(true){
session.invalidate();
java.util.Vector v = new java.util.Vector();
v.add("Signed out...from admin");
request.setAttribute("messages", v);
request.getRequestDispatcher("/admin/accessControl/Login1.jsp").forward(request,response);
return;
}
%>
