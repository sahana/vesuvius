<%@ page language="java" %>
<%@ taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles" %>

<table boder="0">
<tr>
<td>
<%= session.getAttribute("project-risks-results") %>
</td>
</tr>

<tr>
<td>
<%= session.getAttribute("project-actions-results") %>
</td>
</tr>

<tr>
<td>
<%= session.getAttribute("project-reviews-results") %>
</td>
</tr>

</table>

