<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="ListBean" scope="session" class="tccsol.util.ListBean"/>

<html>
<head>
<title>SAGT HRIS</title>

<SCRIPT language="JavaScript">

  //Submit the page number links
  function submitform(pg)
  {
     document.frmList.action = "/sahanaadmin/listservlet?page="+ pg +"&callAction=Next";
     document.frmList.method = "post";
     document.frmList.submit();
  }


  //To uncheck the Fields
  function uncheck(elm)
  {
    dml=document.forms['frmList'];
    var str = "";
    var len = dml.elements.length;
    var i=0;
    var flg = 0;
    for(i=0; i<len; i++)
    {
      if ((dml.elements[i].name==elm) && (dml.elements[i].checked==0)){
        str = dml.elements[i].value;
        flg = 1;
        break;
      }
    }

    if (flg == 1) {
        removeFromList(str)
    }
  }

  //To Check all or uncheck all
  function SetChecked(val)
  {
    dml=document.forms['frmList'];
    var i=0;
    var len = dml.elements.length;
    for(i=0 ; i<len; i++)
    {
      if (dml.elements[i].name.indexOf('lst') == 0) {
        dml.elements[i].checked=val;

        if (val == 0)
        {
          var str = dml.elements[i].value;

          //Remove from List
          removeFromList(str)
        }
      }
    }
  }

  function removeFromList(str)
  {
      var ids = document.frmList.valIds.value;
      var nms = document.frmList.valNms.value;

      //Got the ID & Name
      var id = str.substring(0, str.indexOf("|"));
      var nm = str.substring(str.indexOf("|") + 1, str.length);

      if (ids.indexOf(id) >= 0)
      {
        var fh = ids.substring(0, ids.indexOf(id));
        var lh = ids.substring((ids.indexOf(id) + id.length + 1), ids.length);
        document.frmList.valIds.value = fh + lh;

        fh = nms.substring(0, nms.indexOf(nm));
        lh = nms.substring((nms.indexOf(nm) + nm.length + 1), nms.length);
        document.frmList.valNms.value = fh + lh;
      }
  }

</SCRIPT>

</head>
<body bgcolor="#FFFFFF">
<%
int length = 10;  //The maximum number to be displayed in one page
long last = 0;
String emNames = "";
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

    java.util.Vector ms = ListBean.retrieveList(ListBean.getTitles(), ListBean.getSqlStat(), ListBean.getType());
    if (ms != null)
    {
      for(int i=0;i<ms.size();i++)
      {
%><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <%=ms.elementAt(i)%></font></li>
<%
      }//end of for loop
    }//end of if

  java.util.Vector titles = ListBean.getTitles();
  java.util.Vector vals = ListBean.getValues();

  long nRows = vals.size();
  int nCols = titles.size();
  int start = 0;

  //Values passed by the hyper links - query string values
  if (request.getParameter("page") != null);
    ListBean.setPageVal(Integer.parseInt(request.getParameter("page")));

  if (ListBean.getPageVal() == 0)
    ListBean.setPageVal(1);
%>

<form action="/sahanaadmin/listservlet" name="frmList" method="post">
<br>
  <p align="center"><input type="hidden" name="url" id="url" value="<%=ListBean.getUrl()%>">
  <font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  <strong><u><%=ListBean.getType()%> Records</u><br><br> [ Select from List ]</strong></font></p>

<%
    if (nRows > 0)
    {
      start = (ListBean.getPageVal() - 1) * length;

      last = start + length;
      if (last > nRows)
        last = nRows;

      java.util.Vector vRow = new java.util.Vector();
      int cnt = 0;
      %>
  <table width="89%" border="0"align="center" cellpadding="3" cellspacing="5">
    <tr>
      <TD colspan="<%=nCols+1%>"> <b><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <div align="right"><%=(start + 1)%> to <%=last%> of <%=nRows%> Records</font></b></div> </TD>
    </tr>
  <%
    if (ListBean.getId().trim().length() > 0) { %>
    <tr>
      <td colspan="4"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">Selected
        <%=ListBean.getType()%>(s) </font></tr>
    <tr>
      <td colspan="4"><div align="left"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <textarea readonly name="valIds" id="valIds" cols="75"><%=ListBean.getId()%></textarea>
          </font></div></td></tr>
    <tr>
      <td colspan="4">&nbsp;</td></tr>
    <%} else {%>
    <input readonly name="valIds" id="valIds" type="hidden" size="90" value="<%=ListBean.getId()%>">
    <% } %>
    <input readonly name="valNms" id="valNms" type="hidden" size="90" value="<%=ListBean.getNm()%>">
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
    for (int i=start; i<nRows; i++) {
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
      %>
          <input type="checkbox" name="lst<%=i%>" onclick="uncheck('lst<%=i%>')" value="<%=str%>" <% if (ListBean.getId().indexOf((String)vRow.elementAt(0)) >= 0) {
        out.print("checked");
        } %>>
        </div></td>
      <%
      for(int j=0;j<nCols;j++)
      {
  %>
      <td><font size="2" face="Verdana, Arial, Helvetica, sans-serif"> <%=vRow.elementAt(j)%></font></td>
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
          <input type="submit" name="callAction" id="callAction" value="   Add   ">
          <input name="Reset" type="reset" id="Reset" value="  Reset  ">
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
          <a href="javascript: submitform('<%=i%>');"><%=i%></a>
          <%  }  %>
        </div></td>
    </tr>
    <tr> <td colspan="<%=nCols+1%>">
    <div align="right">
      <a href="javascript:SetChecked(1)">
      <font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      Check All</font></a>
      <a href="javascript:SetChecked(0)">
      <font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      Clear All</font></a></div> </td>
    </tr>
  </table>
  <input type="hidden" name="num" id="num" value="<%=nRows%>">

  <% String tls = "";
    if (ListBean.getTitles().size() > 0) {
      for (int i=0; i<ListBean.getTitles().size(); i++)
        tls = tls + ListBean.getTitles().elementAt(i) + "|";
    }
  %>
  <input type="hidden" name="titles" id="titles" value="<%=tls%>">
  <input type="hidden" name="sqls" id="sqls" value="<%=ListBean.getSqlStat()%>">
  <input type="hidden" name="ftype" id="ftype" value="<%=ListBean.getType()%>">
  <input type="hidden" name="backUrl" id="backUrl" value="<%=ListBean.getBackUrl()%>">
  </form>
</body>
</html>
