<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 java.sql.SQLException,
                 org.erms.business.RequestTO,
                 org.erms.business.RequestDetailTO,
                 java.text.Format,
                 java.text.SimpleDateFormat,
                 org.erms.business.User,
                 org.erms.util.FulfilmentModel" %>
<%@ page import="org.erms.business.*" %>
<%@ page import="org.erms.db.*" %>
<%@ page import="java.util.*" %>
<%@ page import="java.io.IOException" %>

<html>
	<head>
		<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<script language='javascript' src='comman/validate.js'></script>

<link href="comman/style.css" rel="stylesheet" type="text/css">
<script>
    function validate(){
        var quantitiyStr = document.form1.FulfilQuantity.value;
<%--        if (!testNumber(quantitiyStr)){--%>
<%--            alert("please put in a number for quantity");--%>
<%--            return false;--%>
<%--        } else{--%>
            document.form1.submit();
<%--            return true;--%>
<%--        }--%>
    }
</script>

<%
			DataAccessManager dam = new DataAccessManager();
			RequestTO requestObj = null;
			Collection requestFulfillTOs = null;

            //Is he authenticated
		   	User user = (User) request.getSession().getAttribute(ERMSConstants.IContextInfoConstants.USER_INFO);
		    if (user==null){
		    	//Nobody should come here without a user
		   	    request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User not authenticated!");
		       	response.sendRedirect("error.jsp");
		    }
			//OK we are authenticated

            FulfilmentModel model = (FulfilmentModel) request.getSession().getAttribute(ERMSConstants.REQUEST_FULFILL_MODEL);
            if(model == null){
                model = new FulfilmentModel();
                request.getSession().setAttribute(ERMSConstants.REQUEST_FULFILL_MODEL,model);
                String requestDetailID = (String)request.getParameter(ERMSConstants.REQUEST_DETAIL_ID);
                model.setRequestDetailID(requestDetailID);

                List list =	dam.getRequest(requestDetailID);
                if(list == null || list.size() != 2){
                    request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION, "list return by dam.getRequest(requestID) is wrong");
                    response.sendRedirect("error.jsp");
                }

                requestObj = (RequestTO)list.get(0);
                //RequestFulfillTO
                requestFulfillTOs = (Collection)list.get(1);



                if(requestObj == null){
                    //We can come here only via the Serach if the Request Object not found
                    request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION,"Request come via a Serch, so Request object can not be Null");
                    response.sendRedirect("error.jsp");
                }
                model.setRequest(requestObj);
                request.getSession().setAttribute(ERMSConstants.REQUEST_OBJECT,requestObj);

                model.setFulfilment(requestFulfillTOs);
                request.getSession().setAttribute(ERMSConstants.REQUEST_FULFIL_INFO,requestFulfillTOs);
//                Collection reqDetails = requestObj.getRequestDetails();
//                Iterator it = reqDetails.iterator();
            }else{
                 requestObj = model.getRequest();
                 requestFulfillTOs = model.getFulfilment();
            }
		%>
	</head>
	
	<body topmargin="0" leftmargin="0">
		
		<jsp:include page="comman/header.inc"></jsp:include>

		<form name="form1" action="ProcessFulFilHidden.jsp" method="post" >

        <!--- table 1 ------>
        <table width="760" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td>
                    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                        <tr align="left">
                            <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                            <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="Search_Request.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search
                                        Request</font></a>&nbsp;&nbsp;</td>
                            <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>

                            <td width="19%"  height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar" > <font color="#000000">Logged in <%=user.getUserName()%> of <%=user.getOrganization()%></font></font></td>

                            <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log
                                        off&nbsp;&nbsp;&nbsp;&nbsp;</font></a>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
            <tr>
                <td align="center" >
                    <font color="red" >
                        <%
                            if(model.getMessage() != null){
                                     %>
                                        <h2><%=model.getMessage()%></h2>
                                     <%
                            }
                        %>
                    </font>
                </td>
            </tr>
       </table>


            <table width="760" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td>
                    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                        <tr>
                         <td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">FulFill Request</td>
                        </tr>
                        <tr>
                            <td width="117">&nbsp;</td>
                            <td width="484">&nbsp;</td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td>&nbsp;</td>
                        </tr>
                    </table>
                 </td>
              </tr>
              <tr>
                 <td>
              </table>

       <!-- Request information ---->
       <table>
            <tr>
                <td>
                <table>
                    <tr>
                        <td><b>Request Information</b></td>
                    </tr>
                    <tr>
                        <td colspan="2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                                <tr>
                                    <td width="40%" class="formText">&nbsp;Request Date</td>
                                    <td width="40%">
                                            <input type="text" name="item" class="textBox" disabled="true"  value="<%=requestObj.getRequestedDate()%>">
                                    </td>
                                </tr>
                                <tr  >
                                    <td align="center" width="40" class="formText">&nbsp;Caller Name</td>
                                    <td colspan="4"><input type="text" name="item" class="textBox"  disabled="true" value="<%=requestObj.getCallerName()%>"></td>
                                </tr>
                                <tr>
                                    <td class="formText" width="40%">&nbsp;Caller Contact</td>
                                    <td colspan="4"><input type="text" name="item" class="textBox"  disabled="true" value="<%=requestObj.getCallerContactNumber()%>"></td>
                                </tr>
                                <tr>
                                    <td class="formText">&nbsp;Caller Address</td>
                                    <td colspan="4"><input type="text" name="item" class="textBox"  disabled="true" value="<%=requestObj.getCallerAddress()%>"></td>
                                </tr>
                                <tr>
                                    <td>&nbsp;</td>
                                    <td colspan="4">&nbsp;</td>
                                </tr>
                                <tr>
                                    <td class="formText">&nbsp;Site Name</td>
                                    <td colspan="4"><input type="text" name="item" class="textBox"  disabled="true" value="<%=requestObj.getSiteName()%>"></td>
                                </tr>
                                <tr>
                                    <td class="formText">&nbsp;Site District </td>

                                    <%
                                    //////////////////// find the district
                                    String disctrictName = null;
                                         Collection districtList=null;
                                             districtList =  dam.getAllDistricts();
                                             if(districtList != null){
                                                 Iterator ditr = districtList.iterator();
                                                 while(ditr.hasNext()){
                                                     KeyValueDTO district = (KeyValueDTO) ditr.next();
                                                     String districtCode = district.getDbTableCode();
                                                     String districtvalue = district.getDisplayValue();
                                                     if (requestObj.getSiteDistrict().equals(districtCode)){
                                                        disctrictName = districtvalue;
                                                        break;
                                                     }
                                                 }
                                     %>
                                        <td colspan="4"><input type="text" name="item" class="textBox"  disabled="true" value="<%=disctrictName%>"></td>
                                    </tr>
                                    <tr>
                                        <td class="formText">&nbsp;Site Area</td>
                                        <td colspan="4"><input type="text" name="item" class="textBox"  disabled="true" value="<%=requestObj.getSiteArea()%>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;</td>
                                        <td colspan="4">&nbsp;</td>
                                    </tr>


                            </table>
                            </td>
                            <td>

<!---- - Table 2--------------->

                    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                        <%
                            Collection requestDetails = requestObj.getRequestDetails();
                            Iterator iterator = requestDetails.iterator();
                            RequestDetailTO  tempRequestDetailDto = null;



                            ArrayList prs = new ArrayList(dam.getAllPriorities());

                            if (iterator.hasNext()) {
                                tempRequestDetailDto =(RequestDetailTO) iterator.next();
                                request.getSession().setAttribute(ERMSConstants.REQUEST_DETAIL_OBJECT,tempRequestDetailDto);
                                model.setRequestDetail(tempRequestDetailDto);
                                String priority = null;
                                for(int i = 0;i<prs.size();i++){
                                    KeyValueDTO key = (KeyValueDTO)prs.get(i);
                                    if(key.getDbTableCode().equals(tempRequestDetailDto.getPriority())){
                                            priority =  key.getDisplayValue();
                                    }
                                }
                        %>
                        <tr >
                            <td class="formText">Category</td>
                            <td><input type="text" name="category" class="textBox"  disabled="true" value="<%=tempRequestDetailDto.getCategoryName()%>"/></td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td colspan="4">&nbsp;</td>
                        </tr>

                        <tr>
                            <td class="formText">Item</td>
                            <td style="text-decoration:none" ><%=tempRequestDetailDto.getItem()%></td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td colspan="4">&nbsp;</td>
                        </tr>

                        <tr>
                            <td class="formText">Unit</td>
                            <td><input type="text" name="unit" class="textBox"  disabled="true" value="<%=tempRequestDetailDto.getUnit()%>"/></td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td colspan="4">&nbsp;</td>
                        </tr>
                        <tr>
                            <td class="formText">Quantity</td>
                            <td><input type="text" name="quantity" class="textBox"  disabled="true" value="<%=tempRequestDetailDto.getQuantity()%>"/></td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td colspan="4">&nbsp;</td>
                        </tr>
                        <tr>
                            <td class="formText">Priority</td>
                            <td><input type="text" name="prority" class="textBox"  disabled="true" value="<%=priority%>"/></td>
                        </tr>
                </table>

                    </td>
                </tr>

           </table>

                <br>
                <br>
                <hr>
                    <table>
                           <tr><td><b>Fulfilment informations</b></td></tr>

                            <tr >
                                <td class="tableUp">Organization</td>
                                <td class="tableUp">Service Quantity</td>
                                <td class="tableUp">Unit</td>
                                <td class="tableUp">Status</td>
                            </tr>



                            <%
                                }
                                Iterator it = requestFulfillTOs.iterator();
                                while(it.hasNext()){
                                        RequestFulfillDetailTO fulfilTo = (RequestFulfillDetailTO)it.next();
                             %>
                                        <tr>
                                            <td class="tableDown"><%=fulfilTo.getOrgName()%></td>
                                            <td class="tableDown"><%=fulfilTo.getQuantity()%></td>
                                            <td class="tableDown"><%=tempRequestDetailDto.getUnit()%></td>
                                            <td>

                            <%
                                        if(user.getOrganization().equals(fulfilTo.getOrgName())){
                            %>

                                            <select name="catogories" class="textBox">
                                                <%
                                                    Collection statusList  =  dam.getAllStatuses();
                                                        if(statusList != null){
                                                            Iterator citr = statusList.iterator();
                                                            while(citr.hasNext()){
                                                                KeyValueDTO key =(KeyValueDTO)citr.next();;
                                                                String status  = key.getDisplayValue();
                                                                if(fulfilTo.getStatus().equals(status)){
                                                %>
                                                        <option selected="true" value="<%=status%>"><%=status%></option>
                                                <%
                                                                }else{
                                                %>
                                                        <option value="<%=status%>"><%=status%></option>

                                                <%
                                                         }
                                                    }
                                                }
                                                %>
                                            </select>
                        <%
                                        }else{
                           %>
                                                   <input type="text" name="FulfilQuantity"  disabled="true" class="textBox" value="<%=fulfilTo.getStatus()%>"/>
                             <%
                                        }
                              %>
                                            </td>
                                        </tr>

                                <%
                                    }
                            %>

                        <%

                                }
                        %>
                        <tr height="3">
                            <td colspan="5"/>
                        </tr>
                    </table>




                 <br/>
                <hr/>
                <table>
                        <tr><td><b>New Fulfilment informations</b></td></tr>
                            <tr>
                                <td class="formText">&nbsp;Quantity</td>
                                <td colspan="4"><input type="text" name="FulfilQuantity" class="textBox" value="" ></td>
                            </tr>
                            <tr>
                                <td class="formText">Status</td>
                                <td>
                                    <select name="FulfilStatus" class="textBox">
                                        <%
                                            Collection statusList =null;
                                                try{
                                                    statusList =  dam.getAllStatuses();
                                                }catch(Exception e){
                                                        e.printStackTrace();

                                                }

                                                if(statusList != null){
                                                    Iterator citr = statusList.iterator();
                                                    while(citr.hasNext()){
                                                        System.out.println("JMP IN");
                                                        KeyValueDTO key =(KeyValueDTO)citr.next();;
                                                        String status  = key.getDisplayValue();
                                        %>
                                                <option value="<%=status%>"><%=status%></option> <%
                                            }
                                        }
                                        %>
                                    </select>
                                </td>
                            </tr>
                        </table>


                <table>
				<tr>
					<td class="formTitle" colspan="2">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td width="73%" height="30">&nbsp;</td>
                                  <td width="12%" align="right"><input type="button" name="Submit2" value="Save" onclick="validate()" >&nbsp;</td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td colspan="2" class="pageBg">&nbsp;</td>
				</tr>

                <tr>
                    <td>
                        <table width="760" border="0" cellspacing="0" cellpadding="0">
                            <tr>
                                <td class="statusBar">&nbsp;</td>
                            </tr>
                        </table>
                    </td>
                </tr>
			</table>
</form>
</body>
</html>
