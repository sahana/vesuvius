<%@ page language="java" %>
<%@ taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles" %>

<table width="100%" boder="2">
<tr>
<td>
<%= session.getAttribute("last-engfocus-results") %>
</td>
</tr>

<tr>
<td>
<%= session.getAttribute("last-engfocus-summary-results") %>
</td>
</tr>

