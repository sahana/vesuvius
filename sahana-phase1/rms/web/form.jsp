<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>:: ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<link href="comman/style.css" rel="stylesheet" type="text/css">
</head>

<body>

<table width="760" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td class="formBG"><table width="550" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" colspan="2" class="formTitle">Fulfilling request  </td>
        </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td colspan="2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="15%" class="formText">&nbsp;Organization </td>
            <td><input type="text" name="textfield" class="textBox"></td>
            <td class="formText">User</td>
            <td><input type="text" name="textfield2" class="textBox"></td>
            <td class="formText">Date</td>
            <td><input type="text" name="textfield3" class="textBox"></td>
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
            <td width="15%" class="formText">&nbsp;Request Date</td>
            <td colspan="4"><table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="16%"><input type="text" name="txtMDate1" class="textBox" id="txtMDate1">
                </td>
                <td width="82%"><img src="Images/calendar.gif" onClick="popUpCalendar(this, document.getElementById('txtMDate1'), 'mm/dd/yyyy')" width="18" height="17"></td>
              </tr>
            </table></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Requester Name</td>
            <td colspan="4"><input type="text" name="textfield5" class="textBox"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Requester Contact</td>
            <td colspan="4"><input type="text" name="textfield6" class="textBox"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Requester Address</td>
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
            <td class="formText">&nbsp;Site district </td>
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
            <td width="9%" align="center" class="formText">Quantity</td>
            <td width="19%"><input type="text" name="textfield453" class="textBox"></td>
            <td width="39%"><input type="submit" name="Submit" value="Add to List" class="buttons"></td>
          </tr>
          <tr>
            <td class="formText">&nbsp;Priority</td>
            <td colspan="4"><select name="select3" class="textBox">
			<option>Select</option>
            </select></td>
          </tr>
        </table></td>
        </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td colspan="2"><div id="Layer1" style="position:auto; left:150px; top:279px; width:100%; height:200px; z-index:1; overflow: auto;overflow-x">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td><input type="text" name="textfield8" class="textBox"></td>
    <td><input type="text" name="textfield82" class="textBox"></td>
    <td><input type="text" name="textfield83" class="textBox"></td>
    <td><input type="text" name="textfield84" class="textBox"></td>
    <td><input type="text" name="textfield85" class="textBox"></td>
    <td><input type="text" name="textfield86" class="textBox"></td>
    <td><input type="text" name="textfield87" class="textBox"></td>
  </tr>
</table>

</div></td>
        </tr>
      <tr>

        <td class="formTitle" colspan="2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="73%" height="30">&nbsp;</td>
            <td width="27%" align="right"><input type="submit" name="Submit2" value="Submit" class="buttons">&nbsp;</td>
          </tr>
        </table></td>
      </tr>
      <tr>
        <td colspan="2" class="pageBg">&nbsp;</td>
        </tr>
    </table></td>
  </tr>
</table>

<jsp:include page="comman/footer.inc"></jsp:include>

</body>
</html>
