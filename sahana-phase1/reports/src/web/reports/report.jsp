<%@ page language="java" %>

<html>
<head>
    <title>:: Sahana :: Reports</title>
    <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body topmargin="0" leftmargin="0">

<jsp:include page="../common/header.inc"></jsp:include>

<table width="100%" boder="0">

<tr>
    <td>
        <%= request.getAttribute("ReportsData") %>
    </td>
</tr>

<tr><td>
    <button name="buttonBack" onClick="javascript:history.back(-1)">
        <img src="./images/back-button.gif" border="0">
    </button>
</td></tr>

<tr><td>
<hr color="blue" size="2">
 <jsp:include page="../common/footer.inc"></jsp:include>
</td></tr>
</table>

</body>
</html>
