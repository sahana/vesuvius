<%@ page language="java" %>

<table width="100%" boder="2">
<tr><td>
 <jsp:include page="../common/header.inc"></jsp:include>
</td></tr>

<tr>
    <td>
        <%= request.getAttribute("requestDetail") %>
    </td>
</tr>

<tr><td>
<hr color="blue" size="2">
 <jsp:include page="../common/footer.inc"></jsp:include>
</td></tr>
</table>
