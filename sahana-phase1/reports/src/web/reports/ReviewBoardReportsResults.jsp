<%@ page language="java" %>
<%@ page import="java.util.Iterator"%>
<%@ taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles" %>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>

<%@ page import = "java.util.*" %>
<html>
<head>
</head>
<table width="100%" boder="2">

<tr>
  <th bgcolor="blue"><%= session.getAttribute("type") %> Reports</th>
</tr>
<ul>
<%

java.util.List list = (java.util.List) session.getAttribute("reportsList");

Iterator i=list.iterator();

while( i.hasNext() )  {
  String name= (String) i.next();
%>
<tr>
<td> <li><a href="../review-reports/<%= name %>" target="_blank"><%= name %></a></li></td>
</tr>
<%
  } // end loop
%>
</ul>
</table>
</html>
