<%@ page import="tccsol.admin.accessControl.LoginBean"%>
<%
           //catch all exceptions including runtime exeptions
           LoginBean bean = null;
           String url = "";

           try
           {
             //populating the bean with request data
              bean = new LoginBean();
              bean.setUserName("sanjiva");
              bean.setPassword("foo");

              bean.isValidUser();
              session.setAttribute("LoginBean", bean);

            }//end try block
            catch(Throwable t)
            {
               out.print("oops.org! :-)");
            }

%>

<html>

<head>
    <script language="javascript"/>
    function go()
    {
        location.href="<%= request.getContextPath() %>/Welcome.jsp";
    }
    </script>
</head>

<body>

    <form>

    <table>
    <tr align="center">


      <td height="30" colspan=2 >
        <input class="buttons" type="button" value="    Login to Damage Registry  &gt;&gt;"   name=Submit242 onClick="javascript:go();">
        <br><br>
      </td>
    </tr>

    </table>

  </form>

</body>
</html>
