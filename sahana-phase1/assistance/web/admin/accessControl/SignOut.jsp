<%@ page language="java" errorPage="/ErrorDetails.jsp" %>

<html>
<head>
<title>SAGT - HRIS</title>
<META HTTP-EQUIV=Refresh CONTENT="2; URL=/hris/index.html">
</head>

<body bgcolor="#FFFFFF">
<form action="" name="frmSignOut" method="post">
<img src="/hris/images/sagt-1_01.gif" width="100%" height="75">
<table width="100%" border="0" cellspacing="0" cellpadding="4">
  <tr>
    <td bgcolor="#C10000">
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td>
          <%
              //To display the current date in desired format
              //----------------------------------------------
              java.util.GregorianCalendar cal = new java.util.GregorianCalendar();
              cal.setTime(new java.util.Date());

              int dayNo = cal.get(java.util.Calendar.DAY_OF_WEEK);
              String day = "";

              int monthNo = cal.get(java.util.Calendar.MONTH) + 1;  //depending on version of java this (+1) must be included/excluded
              String month = "";

              int mDayNo = cal.get(java.util.Calendar.DAY_OF_MONTH);

              int year = cal.get(java.util.Calendar.YEAR);

              switch (monthNo) {
                  case 1:{ month = "January";
                            break;
                         }
                  case 2:{ month = "February";
                            break;
                         }
                  case 3:{ month = "March";
                            break;
                         }
                  case 4:{ month = "April";
                            break;
                         }
                  case 5:{ month = "May";
                            break;
                         }
                  case 6:{ month = "June";
                            break;
                         }
                  case 7:{ month = "July";
                            break;
                         }
                  case 8:{ month = "August";
                            break;
                         }
                  case 9:{ month = "September";
                            break;
                         }
                  case 10:{ month = "October";
                            break;
                         }
                  case 11:{ month = "November";
                            break;
                         }
                  case 12:{ month = "December";
                            break;
                         }
              }

              switch (dayNo) {
                  case 1:{ day = "Sunday";
                            break;
                         }
                  case 2:{ day = "Monday";
                            break;
                         }
                  case 3:{ day = "Tuesday";
                            break;
                         }
                  case 4:{ day = "Wednesday";
                            break;
                         }
                  case 5:{ day = "Thursday";
                            break;
                         }
                  case 6:{ day = "Friday";
                            break;
                         }
                  case 7:{ day = "Saturday";
                            break;
                         }
              }

             String date = day + ", " + month + " " + mDayNo + ", " + year;
          %>
          <div align="right"><strong><font color="#FFFFFF" size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <% out.print(date); %></font></strong></div></td>
        </tr>
      </table></td>
  </tr>
  <tr>
    <td bgcolor="#C10000">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td></td>
        </tr>
      </table></td>
  </tr>
</table>
<br>
  <font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  <h5>You have successfully signed out of the system</h5>
  </font>
  <p>&nbsp;</p>
  <p><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><a href="/hris/index.html">Home</a></strong></font>
  </p>
</form>
</body>
</html>