<%@ page import="org.campdb.business.CampTO,
                 org.campdb.db.DataAccessManager,
                 org.campdb.util.StringUtil,
                 org.campdb.util.LabelValue,
                 java.util.*,
                 org.campdb.util.CAMPDBConstants,
                 org.campdb.business.User"%>
<jsp:useBean id="newCamp" scope="request" class="org.campdb.business.CampTO" />
<jsp:setProperty name="newCamp" property="*" />
<%
    boolean inserted = false;
    List errors = new LinkedList();
    if (request.getParameter("doInsert") != null) {
        DataAccessManager dataAccessManager = new DataAccessManager();
        errors.addAll(dataAccessManager.validateCampTOforInsert(newCamp));
        System.out.println("ize"+ errors.size());
        if(errors.size()<=0) {
            try {
                dataAccessManager.addCamp(newCamp);
                newCamp.reset();
                inserted = true;
            } catch (Exception e) {
//                errors.add(e.getMessage());
            }
            if(inserted) {
            %>
              <jsp:include page="comman/header.inc"></jsp:include>

             <p align="center" class="formText" >
               <h3 align="center" >You have successfully inserted a camp to the system !!</h3>
             </p>
           <%
             session.invalidate();
          } else {
               response.sendRedirect("error.jsp");
            }
            %>
             </body>
                <jsp:include page="comman/footer.inc"></jsp:include>
            </html>
          <%
            return;
        }

  } else {
        newCamp.reset();
    }
%>




<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>


<title>:: Sahana :: Camp Database</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
<script type="text/javascript">

function validateForm()
{
    if(document.newCamp.campName.value == "")
    {
        alert("Camp Name must have a value");
        document.newCamp.campName.focus();
        return false;
    }

    if(document.newCamp.divisionId.value == "")
    {
        alert("Division Id must be selected");
        document.newCamp.divisionId.focus();
        return false;
    }
    //document.newCamp.doInsert.value="doInsert";
    document.newCamp.submit();
}

function update()
{
var choice = document.newCamp.divisionId.value;
    if(choice == "")
    {
        alert("Division Id must be selected");
        document.newCamp.divisionId.focus();
        return;
    }

<%
    ArrayList divisionInfo = (ArrayList) application.getAttribute("divisionInfo");

%>

<%
    String array = new String();
    for (int i = 0; i < divisionInfo.size(); i++) {
        String s = (String) divisionInfo.get(i);
        array = array + "\"" + s + "\",";

    }
    array = array + "";
%>
var arr = [<%=array%>];
<%--alert(arr[choice]);--%>

document.newCamp.divInfo.value = arr[choice];
}

function showObject(id){
       var obj = document.getElementById(id);
       obj.style.display = "";
    }

    function hideObject(id){
       var obj = document.getElementById(id);
       obj.style.display = "none";
    }


 function clearTextBox(txtBoxId){
       var obj = document.getElementById(txtBoxId);
       obj.value = "";
    }

     function disableTextBox(txtBoxId){
       var obj = document.getElementById(txtBoxId);
       obj.disabled = true;
    }

    function clearAll(){
        clearTextBox("campTotal");
        clearTextBox("campMen");
        clearTextBox("campWomen");
        clearTextBox("campChildren");

    }

    function totalSelected(){
           showObject("totalRow");
           hideObject("menRow");
           hideObject("womenRow");
           hideObject("childRow");
    }

    function breakDownSelected(){
           hideObject("totalRow");
           showObject("menRow");
           showObject("womenRow");
           showObject("childRow");

    }

    function changeTextBoxStatus(){
       var selectedValue = document.newCamp.countSelect;

       if (selectedValue[0].checked){
         totalSelected();
       }else{
          breakDownSelected();
       }

       clearAll();
    }

    function validateTotal()
    {
       if(isNaN(document.newCamp.campTotal.value))
       {
           alert("Please enter integer value");
           document.newCamp.campTotal.focus();
       }
                                                                                                                             
    }

    function validateChildren()
    {
       if(isNaN(document.newCamp.campChildren.value))
       {
           alert("Please enter integer value");
           document.newCamp.campChildren.focus();
           return;
       }
       calcTotal();                                                                                                          
    }

    function validateMen()
    {
       if(isNaN(document.newCamp.campMen.value))
       {
           alert("Please enter integer value");
           document.newCamp.campMen.focus();
           return;
       }
       calcTotal();                                                                                                          
    }

    function validateWomen()
    {
       if(isNaN(document.newCamp.campWomen.value))
       {
           alert("Please enter integer value");
           document.newCamp.campWomen.focus();
           return;
       }
       calcTotal();                                                                                                          
    }
    
    function calcTotal(){
        var menCount =0;
        var womenCount =0;
        var childrenCount =0;
        menCount = parseInt(document.newCamp.campMen.value);

       womenCount = parseInt(document.newCamp.campWomen.value);
       childrenCount = parseInt(document.newCamp.campChildren.value);
       document.newCamp.campTotal.value= menCount+womenCount+childrenCount;

    }

    function warn() {
        if ( (isNaN(document.newCamp.campMen.value)) ||
             (isNaN(document.newCamp.campWomen.value)) ||
             (isNaN(document.newCamp.campChildren.value)) )
             alert('People break up will not be considered.');
    }

</script>
</head>

<body topmargin="0" leftmargin="0">
                               <%
                                   User user = (User) session.getAttribute(CAMPDBConstants.IContextInfoConstants.USER_INFO);
                                   if(user == null){
                                       request.getSession().setAttribute(CAMPDBConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User has not been authenticated. Please login  !!");
                                       response.sendRedirect("error.jsp");
                                   }
                               %>
        <table width="760" border="0" cellspacing="0" cellpadding="0">
        <td height="50" >
      <jsp:include page="comman/header.inc"></jsp:include>
    </td>
        <tr>
        <td>
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr align="left">
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="SearchCamps.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search
                    Camp</font></a>&nbsp;&nbsp;</td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                    <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="LogOff.jsp" style="text-decoration:none"><font color="#000000">Log
                    off&nbsp;&nbsp;&nbsp;&nbsp;</font></a></td>
            </tr>
            </table>

          </td>
          </tr>
        </table>
        <table width="760" border="0" cellspacing="0" cellpadding="0">
             <tr>
               <td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Add Camps  </td>
             </tr>
         </table>


<form name="newCamp" action="InsertCamps.jsp">
    <table cellspacing="4"  >
        <%
            if(errors.size() > 0) {
                newCamp.setNullValsToEmpty();
                for (Iterator iterator = errors.iterator(); iterator.hasNext();) {
                    String error = (String) iterator.next();

         %>
        <tr>
            <td colspan="3"class="formText" ><font color="red"><%=error%></font><br></td>
        </tr>
        <%      }
            }
        %>

        <%
            if(inserted) {
        %>
            <tr>
                <td colspan="3" ><font color="blue" size="-1">successfully inserted values to the database</font><br></td>
            </tr>
        <%
            }
        %>


        <tr>
            <td align="right" valign="top"  class="formText"  >Camp Name</td><td><input type="text" size="20" maxlength="49"  name="campName" class="textBox"  value="<jsp:getProperty name="newCamp" property="campName" />">&nbsp;<small><font color="red">*</font></small></td>
        </tr>

        <%
            // populate the session with the division, district and province info so that jscript can use them
//            List divisionInfo = (List) application.getAttribute("divisionInfo");

        %>
        <tr>
            <td  align="right" valign="top"   class="formText">Division&nbsp;</td>
                <td>
                <select onChange="update();" name="divisionId" class="selectBoxes">
                    <option value="">&lt;Select&gt;</option>
                    <%
                      List divisions = (List) application.getAttribute("divisions");
                        for (Iterator iterator = divisions.iterator(); iterator.hasNext();) {
                            LabelValue division = (LabelValue) iterator.next();
                    %>
                            <option value="<%=division.getValue()%>"><%=division.getLabel()%></option>
                    <%
                        }
                    %>
                </select>&nbsp;<small><font color="red">*</font></small>
                <input size="100" type="text" name="divInfo" readonly="true" style="border:none;" class="textBox"></input>
            </td>

       </tr>
        <tr>
            <td  align="right" valign="top"  class="formText" >Area&nbsp;</td>
               <td>
                 <input type="text" size="20" maxlength="49"  name="areaName" class="textBox"  value="<jsp:getProperty name="newCamp" property="areaName" />">
               </td>
        </tr>

       <tr>
            <td align="right" valign="top"   class="formText">Contact Person</td><td align="left"><input type="text" size="30" class="textBox"  maxlength="99"  name="campContactPerson" value="<jsp:getProperty name="newCamp" property="campContactPerson"/>" /></td>
        </tr>
       <tr>
            <td align="right" valign="top"   class="formText">Contact Number</td><td align="left"><input type="text" class="textBox"  size="15" maxlength="99"  name="campContactNumber" value="<jsp:getProperty name="newCamp" property="campContactNumber" />"/></td>
        </tr>
        <br>
       <tr>
            <td align="right" valign="top"  class="formText" >Accessibility</td><td align="left" valign="top">
                <textarea name="campAccesability"  cols="50" rows="3" class="textBox"><jsp:getProperty name="newCamp" property="campAccesability" /></textarea>
            </td>
        </tr>
       <tr>
            <td align="right" valign="top"   class="formText">Capability</td>
            <td align="left">
                <textarea name="campCapability" cols="50" rows="3" class="textBox"><jsp:getProperty name="newCamp" property="campCapability" /></textarea>
            </td>
        </tr>
       <tr>
            <td align="right" valign="top"  class="formText" >Comment</td>
            <td>
                <textarea name="campComment" cols="50" rows="3" class="textBox"><jsp:getProperty name="newCamp" property="campComment" /></textarea>
            </td>
        </tr>

                <tr>
                    <td  align="right" vAlign="top" class="formText"> Total </td><td><input type="radio" name="countSelect" class="formText" onclick="changeTextBoxStatus();"/></td>
                </tr>
                <tr>
                    <td  align="right" vAlign="top" class="formText">  Break Down </td><td><input type="radio" name="countSelect" class="formText" onclick="changeTextBoxStatus();"/></td>
                </tr>
                <tr id="totalRow" style="display:none" >
                    <td align="right" >Total</td><td align="left" vAlign="top" class="formText" ><input type="text" name="campTotal" class="textBox"  onChange="validateTotal();" value="<%=newCamp.getCampTotal()==null?"":newCamp.getCampTotal()%>" ></input></td>
                </tr>
                <tr id="menRow" style="display:none">
                    <td align="right" >Men :</td><td  align="left" vAlign="top" class="formText"><input type="text" name="campMen" class="textBox" onchange="validateMen();"  value="<%=newCamp.getCampMen()==null?"":newCamp.getCampMen()%>"></input></td>
                </tr>
                <tr id="womenRow" style="display:none">
                    <td align="right" >Women :</td><td align="left" vAlign="top" class="formText"><input type="text" name="campWomen" class="textBox" onchange="validateWomen();"  value="<%=newCamp.getCampWomen()==null?"":newCamp.getCampWomen()%>"></input></td>
                </tr>
                <tr id="childRow" style="display:none">
                     <td align="right" >Children :</td><td align="left" vAlign="top" class="formText"><input type="text" name="campChildren" class="textBox" onchange="validateChildren();"  value="<%=newCamp.getCampChildren()==null?"":newCamp.getCampChildren()%>"></input></td>
                </tr>


         </td>
        </tr>

          <tr>
              <td colspan="2" align="right" vAlign="top">&nbsp;</td>
            </tr>
            <tr>
              <td></td>
              <td>
                <input type="reset" name="reset" value="Clear" class="buttons"/>
                <input type="submit" name="doInsert" value="Add" class="buttons"/>
            </tr>
            <tr>
             <td>

             </td>
            </tr>
    </table>

</form>

  <jsp:include page="comman/footer.inc"></jsp:include>
</body>
</html>

