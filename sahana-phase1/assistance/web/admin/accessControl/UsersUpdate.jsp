<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="UsersBean" scope="session" class="tccsol.admin.accessControl.UsersBean"/>

<html>
<head>
<title>Access Control - Admin</title>

<script LANGUAGE="JavaScript">
    function transferRoles(from, to)
    {
      fromList = eval('document.frmUsersUpd.' + from);
      toList = eval('document.frmUsersUpd.' + to);

      var sel =false;

      if (fromList.options[0] != null)
      {
          var current = fromList.options[0];
          if(current.value.length == 0)
          {
              if (from == 'leftRoles')
                alert ('There are no roles to be added');
              else
                alert ('There are no roles to be deselected');
              return;
          }
      }
      else
      {
          if (from == 'leftRoles')
            alert ('There are no roles to be added');
          else
            alert ('There are no roles to be deselected');
          return;
      }

      for(i=0;i<fromList.options.length;i++)
      {
        var current = fromList.options[i];

        if(current.selected)
        {
          sel = true;

          txt = current.text;
          val = current.value;
          toList.options[toList.length]=new Option(txt,val);
          fromList.options[i]=null;
          i--;

          //Clear the first blank
          var fst = toList.options[0];
          var v = fst.value;
          if(v.length == 0)
             toList.options[0]=null;
        }
      }

      if(!sel)
      {
          if (from == 'leftRoles')
            alert ('You must select atleast one role to be added');
          else
            alert ('You must select atleast one role to be deselected');
      }
    }


    function transferAllRoles(from, to)
    {
      fromList = eval('document.frmUsersUpd.' + from);
      toList = eval('document.frmUsersUpd.' + to);

      var sel =false;
      for(i=0;i<fromList.options.length;i++)
      {
            var current = fromList.options[i];
            txt = current.text;
            val = current.value;

            if (val.length > 0)
            {
              sel =true;
              toList.options[toList.length]=new Option(txt,val);
              fromList.options[i]=null;
              i--;
              var fst = toList.options[0];
              var v = fst.value;
              if(v.length == 0)
                 toList.options[0]=null;
            }
      }

      if(!sel)
      {
          if (from == 'leftRoles')
            alert ('There are no roles to be added');
          else
            alert ('There are no roles to be deselected');
      }
    }

  //Submit the for when insert is clicked
  function submitform()
  {
      fromList = eval('document.frmUsersUpd.leftRoles');
      toList = eval('document.frmUsersUpd.rightRoles');

      var ltxt = '';
      var lval = '';
      for(i=0;i<fromList.options.length;i++)
      {
            var current = fromList.options[i];
            if (current.value.length > 0)
            {
              ltxt = ltxt + current.text + '|';
              lval = lval + current.value + '|';
            }
      }

      var rtxt = '';
      var rval = '';
      for(i=0;i<toList.options.length;i++)
      {
            var current = toList.options[i];
            if (current.value.length > 0)
            {
              rtxt = rtxt + current.text + '|';
              rval = rval + current.value + '|';
            }
      }

     document.frmUsersUpd.action = "/hris/usersservlet?callAction=Update Record&lIds="+ lval +"&lNms=" + ltxt + "&rIds="+ rval +"&rNms=" + rtxt;
     document.frmUsersUpd.method = "post";
     document.frmUsersUpd.submit();
  }
</SCRIPT>
</head>
<body bgcolor="#FFFFFF">
<%
if (request.getAttribute("messages")!=null)
{
    java.util.Vector v = (java.util.Vector) request.getAttribute("messages");
    if (v.size() > 0)
    {
    for(int i=0;i<v.size();i++)
    {
%><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
    <%=v.elementAt(i)%>
    </font></li>
<%
    }//end of for loop
    }
}//end of if

if (UsersBean.getUpdCnt() == 1)
{
  UsersBean.getAllRoles("U");
  if (UsersBean.getMessages() !=null)
  {
      java.util.Vector v = UsersBean.getMessages();
      if (v.size() > 0)
      {
      for(int i=0;i<v.size();i++)
      {
  %><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <%=v.elementAt(i)%>
      </font></li>
  <%
      }//end of for loop
      }
  }//end of if
}
%>

<form action="/hris/usersservlet" name="frmUsersUpd" method="post">
<br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  <strong><u>System Users - Update</u></strong></font></p>
    <br>
  <table width="94%" border="0" cellspacing="4" cellpadding="0">
    <tr>
      <td colspan="3"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      &nbsp;&nbsp;&nbsp;&nbsp;
      The fields marked with * cannot be updated. Replace the old value with the new one to update the rest.</font></td>
    </tr>
    <tr>
      <td colspan="3"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">&nbsp;</font></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Employee Id: </font></div></td>
      <td width="23%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="text" readonly name="empId" id="empId" value="<%=UsersBean.getEmpId()%>">&nbsp;*
        </font></td>
      <td width="30%"></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          User Name: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="text" name="userName" id="userName" value="<%=UsersBean.getUserName()%>">
        </font></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Password: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="password" name="pass1" id="pass1" value="">
        </font></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Confirm Password: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="password" name="pass2" id="pass2" value="">
        </font></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
       Existing Roles: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <textarea readonly cols="40" name="oldRoles" id="oldRoles"><%=UsersBean.getOldRole()%></textarea>&nbsp;*
        </font></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td colspan="2">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      &nbsp;&nbsp;&nbsp;&nbsp;User Roles:
      <br>&nbsp;&nbsp;&nbsp;
      (Only roles which have not been assigned to the user already will be listed)
      <br>
      </font></td>
    </tr>
    <tr>
      <td colspan="3">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="36%"><div align="right"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">All
                User Roles</font></strong></div></td>
            <td width="4%">&nbsp;</td>
            <td width="20%">&nbsp;</td>
            <td width="3%">&nbsp;</td>
            <td width="37%"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">Selected
              Roles</font></strong></td>
          </tr>
          <tr>
            <td rowspan="5">
          <div align="right">
                <select name="leftRoles" size="7" multiple id="leftRoles">
                  <%
                if (UsersBean.getRoleIds().size() > 0)
                {
                  for (int i=0; i<UsersBean.getRoleIds().size(); i++)
                  {
                      out.println("<option value=\"" + UsersBean.getRoleIds().elementAt(i) + "\">"
                        + UsersBean.getRoles().elementAt(i) + "</option>");
                  }
                }
                else
                  out.println("<option>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option>");
               %>
                </select>
              </div></td>
            <td>&nbsp;</td>
            <td> <div align="center">
                <input name="bAdd" type="button" id="bAdd" onclick="transferRoles('leftRoles', 'rightRoles')" value="    &gt;    ">
              </div></td>
            <td>&nbsp;</td>
            <td rowspan="5"> <select name="rightRoles" size="7" multiple id="rightRoles">
                <%
                if (UsersBean.getSelRoleIds().size() > 0)
                {
                  for (int i=0; i<UsersBean.getSelRoleIds().size(); i++)
                  {
                      out.println("<option value=\"" + UsersBean.getSelRoleIds().elementAt(i)
                        + "\">" + UsersBean.getSelRoles().elementAt(i) + "</option>");
                  }
                }
                else
                  out.println("<option>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option>");
                %>
              </select>
              </td>
          </tr>
          <tr>
            <td>&nbsp;</td>
            <td><div align="center">
                <input name="bAddAll" type="button" id="bAddAll" onclick="transferAllRoles('leftRoles', 'rightRoles')" value="   &gt;&gt;   ">
              </div></td>
            <td>&nbsp;</td>
          </tr>
          <tr>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
          </tr>
          <tr>
            <td>&nbsp;</td>
            <td><div align="center">
                <input name="bRem" type="button" onclick="transferRoles('rightRoles', 'leftRoles')" id="bRem" value="    &lt;    ">
              </div></td>
            <td>&nbsp;</td>
          </tr>
          <tr>
            <td>&nbsp;</td>
            <td><div align="center">
                <input name="bRemAll" type="button" onclick="transferAllRoles('rightRoles', 'leftRoles')" id="bRemAll" value="   &lt;&lt;   ">
              </div></td>
            <td>&nbsp;</td>
          </tr>
        </table></td>
    </tr>
    <tr>
      <td colspan="3">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      &nbsp;&nbsp;&nbsp;&nbsp;To select more than one role, hold down the Control/Shift key while you click
      </font></td>
    </tr>
    <tr>
      <td colspan="3">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3"><div align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <input name="callAction" type="button" id="callAction" value="Update Record" onclick="submitform()">
          <input name="Reset" type="reset" id="Reset" value="Reset">
          <input name="callAction" type="submit" id="callAction" value="Back">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          <input type="hidden" name="oldUserName" id="oldUserName" value="<%=UsersBean.getOldUserName()%>">
          </font></div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%
if (UsersBean != null)
  UsersBean.closeDBConn();
%>
</body>
</html>