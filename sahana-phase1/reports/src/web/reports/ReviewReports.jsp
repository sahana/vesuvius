<%@ page language="java" %>
<%@ taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles" %>
<!-- <%=request.getParameter("type")%> -->
<tiles:insert definition="<%=request.getParameter("type")%>" flush="true" />
