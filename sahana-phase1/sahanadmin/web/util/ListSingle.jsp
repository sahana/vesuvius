<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="ListSBean" scope="session" class="tccsol.util.ListSingleBean"/>

<html>
<head>
<title>HRIS</title>
</head>
<body bgcolor="#FFFFFF">
<%
int length = 10;  //The maximum number to be displayed in one page
if (request.getAttribute("messages")!=null)
{
    java.util.Vector v = (java.util.Vector) request.getAttribute("messages");

    for(int i=0;i<v.size();i++)
    {
%><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
    <%=v.elementAt(i)%></font></li>
<%
    }//end of for loop
}//end of if

    java.util.Vector ms = ListSBean.retrieveList(ListSBean.getTitles(), ListSBean.getSqlStat(), ListSBean.getType());
    if (ms != null)
    {
    if (ms.size() > 0)
    {
      for(int i=0;i<ms.size();i++)
      {
%><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <%=ms.elementAt(i)%></font></li>
<%
      }//end of for loop
    }
    }//end of if
%>

<form action="/sahanaadmin/listsingleservlet" name="frmList" method="post">
<br>  <p align="center"><input type="hidden" name="url" id="url" value="<%=ListSBean.getUrl()%>">
<font size="2" face="Verdana, Arial, Helvetica, sans-serif">
    <strong><u><%=ListSBean.getType()%> Records</u><br><br>[ Select from List ]</strong></font></p>
 <input type="hidden" readonly name="IdVal" id="IdVal" value="<%=ListSBean.getId()%>">
 <input name="nmVal" id="nmVal" type="hidden" value="<%=ListSBean.getName()%>">
    <table width="89%" border="0" cellspacing="0" cellpadding="0" align="center">
    <%
      java.util.Vector titles = ListSBean.getTitles();
      java.util.Vector vals = ListSBean.getValues();

      long nRows = vals.size();
      int nCols = titles.size();
      int start = 0;
      long last = 0;

    if (nRows > 0)
    {
      if (request.getParameter("page") != null);
        ListSBean.setPageVal(Integer.parseInt(request.getParameter("page")));

      if (ListSBean.getPageVal() == 0)
        ListSBean.setPageVal(1);

      start = (ListSBean.getPageVal() - 1) * length;

      last = start + length;
      if (last > nRows)
        last = nRows;
 } %>
      <tr>
        <td colspan="2"><div align="right"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <%=(start + 1)%> to <%=last%> of <%=nRows%> Records
        </font></strong></div></td> </tr></table>
    <br>
  <table width="89%" border="0" align="center" cellpadding="3" cellspacing="5">
    <%
    if (nRows > 0)
    {
      int cnt = 0;
      java.util.Vector vRow = new java.util.Vector();

      %>
    <tr>
      <TH> <div align="left"></div></TH>
      <%
      for(int i=0;i<nCols;i++)
      {
    %>
      <TH> <div align="left"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <%=titles.elementAt(i)%> </font> </TD>
          <% } %>
        </div></tr>
    <tr>
      <TD colspan="<%=nCols+1%>"> <hr noshade color="#000000"> </TD>
    </tr>
    <%
    for (int i=start; i<nRows; i++)
    {
      cnt++;
      if (cnt == length + 1) {
          break;
      }

      vRow = tccsol.util.Utility.splitString((String)vals.elementAt(i), '|');
   %>
    <tr>
      <td><div align="right">
          <%
      //Always retrieve the Id 1st and the name 2nd & then what ever you want
      String str = vRow.elementAt(0) + "|" + vRow.elementAt(1);

      if (titles.size() > 2)
       str = str + "|" + vRow.elementAt(2);

      if (titles.size() > 3)
       str = str + "|" + vRow.elementAt(3);

      if (titles.size() > 4)
       str = str + "|" + vRow.elementAt(4);


      //if there are more than 2 columns then send the 3rd column as well
      //Only 3 column composite keys Ex: Mutual Exchange

      %>
          <input type="radio" name="lst" value="<%=str%>">
        </div></td>
      <%
      for(int j=0;j<nCols;j++)
      {
  %>
      <td><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <%=vRow.elementAt(j)%></font></td>
      <%
      }  //End of for loop with 'j'
    %>
    </tr>
    <%
      }  //End of for loop with 'i'
      }  //End of if
    %>
    <tr>
      <TD colspan="<%=nCols+1%>"> <hr noshade color="#000000"> </TD>
    </tr>
    <tr>
      <td colspan="<%=nCols+1%>"><div align="center">
          <input type="submit" name="callAction" id="callAction" value="  Add  ">
          <input name="Reset" type="reset" id="Reset" value=" Reset ">
          <input type="submit" name="callAction" id="callAction" value="  Back  ">
        </div></td>
    </tr>
    <tr>
      <td colspan="<%=nCols+1%>"><div align="right">
          <% long pages = nRows / length;
          if ((nRows % length) > 0)
            pages++;

          for (int i=1; i<=pages; i++) {
       %>
          <a href="/sahanaadmin/util/ListSingle.jsp?page=<%=i%>"><%=i%></a>
          <%  }  %>
        </div></td>
    </tr>
  </table>
  <input type="hidden" name="num" id="num" value="<%=nRows%>">
  <input type="hidden" name="listType" id="listType" value="<%=ListSBean.getType()%>">
  </form>
</body>
</html>
