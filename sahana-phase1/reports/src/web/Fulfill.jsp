<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>

<body topmargin="0" leftmargin="0">
<form name="form1" action="" method="post">
<table width="760" border="0" cellspacing="0" cellpadding="0">
<tr>
<td class="border">
<table width="100%" border="0" cellspacing="1" cellpadding="0">
<tr>
<td class="pageBg">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="10" height="24" class="menuBG"><img src="images/spacer.gif" width="10" height="10"></td>
        <td width="110" class="menuBG"><a href="Fulfill.jsp">Fulfill request</a></td>
        <td width="10" class="menuBG"><img src="images/spacer.gif" width="10" height="10"></td>
        <td width="93" class="menuBG"><a href="Add_Request.jsp">Add Request </a></td>
        <td width="10" class="menuBG"><img src="images/spacer.gif" width="10" height="10"></td>
        <td width="459" class="menuBG"><a href="Search_Request.jsp">Search Request</a></td>
        <td width="80" class="menuBG"><a href="Index.jsp">Log off</a></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td><table width="760" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="134" height="350" valign="top" class="leftMenuBG"><img src="images/spacer.gif" width="160" height="10"></td>
        <td width="620"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" colspan="2" class="formTitle">Fulfilling request  </td>
        </tr>
      <tr>
        <td width="117">&nbsp;</td>
        <td width="484">&nbsp;</td>
      </tr>
      <tr>
        <td colspan="2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="19%" class="formText">&nbsp;Organization </td>
            <td width="21%"><input type="text" name="textfield" class="textBox"></td>
            <td width="5%" class="formText">User</td>
            <td width="25%"><input type="text" name="textfield2" class="textBox"></td>
            <td width="5%" class="formText">Date</td>
            <td width="25%"><input type="text" name="textfield3" class="textBox"></td>
          </tr>
        </table></td>
        </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td colspan="2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="20%" class="formText">&nbsp;Request Date</td>
            <td colspan="4"><table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="16%"><input type="text" name="txtMDate1" class="textBox" id="txtMDate1">
                </td>
                <td width="82%"><img src="Images/calendar.gif" onClick="popUpCalendar(this, document.getElementById('txtMDate1'), 'mm/dd/yyyy')" width="18" height="17"></td>
              </tr>
            </table></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Caller Name</td>
            <td colspan="4"><input type="text" name="textfield5" class="textBox"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Caller Contact</td>
            <td colspan="4"><input type="text" name="textfield6" class="textBox"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Caller Address</td>
            <td colspan="4"><input type="text" name="textfield7" class="textBox"></td>
          </tr>
          <tr>
            <td>&nbsp;</td>
            <td colspan="4">&nbsp;</td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Site Name</td>
            <td colspan="4"><input type="text" name="textfield42" class="textBox"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Site District </td>
            <td colspan="4"><select name="select" class="textBox">
			<option>Select</option>
            </select></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Site Area</td>
            <td colspan="4"><input type="text" name="textfield44" class="textBox"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Comments </td>
            <td colspan="4"><input type="text" name="textfield45" class="textBox"></td>
          </tr>
          <tr>
            <td>&nbsp;</td>
            <td colspan="4">&nbsp;</td>
          </tr>
          <tr>
            <td height="22" class="formText">&nbsp;Category</td>
            <td colspan="4">
              <select name="select2" class="textBox">
			  <option>Select</option>
              </select>
           </td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Item</td>
            <td colspan="4"><input type="text" name="textfield4" class="textBox"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Units</td>
            <td width="17%"><input type="text" name="textfield452" class="textBox"></td>
            <td width="10%" align="center" class="formText">Quantity</td>
            <td width="18%"><input type="text" name="textfield453" class="textBox"></td>
	    <td width="35%"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Priority</td>
            <td height="25" colspan="4"><select name="select3" class="textBox">
			<option>Select</option>
            </select></td>
          </tr>
        </table></td>
        </tr>
       <tr>
            <td>&nbsp;</td>
            <td colspan="4">&nbsp;</td>
          </tr>
      <tr>
        <td colspan="2"><div id="Layer1" style="position:auto; left:150px; top:279px; width:100%; height:200px; z-index:1; overflow: auto;overflow-x">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr class="formTitle">
    <td height="25" class="formText">&nbsp;Org Code</td>
    <td class="formText">Orga Name</td>
    <td class="formText">OrgContact</td>
    <td class="formText">Quatity</td>
    <td class="formText">Status</td>
    </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td><select name="select8" class="textBox">
      <option>select</option>
    </select></td>
    </tr>
</table>

</div></td>
        </tr>
      <tr>
        <td class="formText">&nbsp;Service Status</td>
        <td width="484"><select name="select9" class="textBox">
          <option>Select</option>
        </select></td>
      </tr>
      <tr>
        <td class="formText">&nbsp;Service Quantity</td>
        <td height="25"><input type="text" name="textfield8" class="textBox"></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>

        <td class="formTitle" colspan="2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="73%" height="30">&nbsp;</td>
            <td width="15%" align="right"><input type="submit" name="Submit2" value="Submit" class="buttons"></td>
            <td width="12%" align="right"><input type="submit" name="Submit3" value="Cancel" class="buttons">&nbsp;</td>
          </tr>
        </table></td>
      </tr>
      <tr>
        <td colspan="2" class="pageBg">&nbsp;</td>
        </tr>
    </table></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td><table width="760" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td class="statusBar">&nbsp;</td>
      </tr>
    </table></td>
  </tr>
</table>
</td>
</tr>
</table>
</td>
</tr>
</table>
</form>
</body>
</html>
