<%@ page import="java.util.Collection,
								 java.util.Iterator,
								 javax.servlet.http.HttpServletRequest,
     						 javax.servlet.http.HttpServletResponse,
                 org.erms.db.DataAccessManager,
								 org.erms.util.ERMSConstants,
                 org.erms.business.*,
                 org.erms.util.FulfilmentModel" %>
<%
        User user = (User) request.getSession().getAttribute(ERMSConstants.IContextInfoConstants.USER_INFO);
        if (user==null){
            //Nobody should come here without a user 
            request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User not authenticated!");
            response.sendRedirect("error.jsp");
        }
        //OK we are authenticated


       FulfilmentModel model = (FulfilmentModel) request.getSession().getAttribute(ERMSConstants.REQUEST_FULFILL_MODEL);

        RequestTO requestObj = model.getRequest();
        RequestDetailTO requestDetailObj = model.getRequestDetail();


        //Gather fulfilemnt information
        Collection fulfilments = model.getFulfilment();
        int totelFulfilment = 0;
        Iterator it = fulfilments.iterator();
        while(it.hasNext()){
            RequestFulfillDetailTO fd = (RequestFulfillDetailTO)it.next();
            String value = fd.getQuantity();
            if(value != null && !"withdrawn".equals(fd.getStatus())){
                totelFulfilment = totelFulfilment + Integer.parseInt (value.trim());
            }
        }

        //TODO calculate the list of changed status


        String status =   request.getParameter("FulfilStatus");
        String quantity = request.getParameter("FulfilQuantity");
        if(quantity != null && quantity.trim().length() != 0){
            int requestQuantity = requestDetailObj.getQuantity();
            int quantityValue = Integer.parseInt (quantity.trim());

            RequestFulfillDetailTO rfdto = new RequestFulfillDetailTO();
            rfdto.setOrgCode(user.getOrgCode());
            rfdto.setOrgName(user.getUserName());
            rfdto.setStatus(status);
            rfdto.setQuantity(quantity);
            fulfilments.add(rfdto);

            if((quantityValue + totelFulfilment) <= requestQuantity){
                   if((quantityValue + totelFulfilment) == requestQuantity){
                        //TODO
                   }
                    RequestFulfillTO fulfil = new RequestFulfillTO();
                    fulfil.setOrganization(user.getOrgCode());
                    fulfil.setRequestDetailID(requestDetailObj.getRequestDetailID());
                    fulfil.setServiceQuantity(quantity);
                    fulfil.setStatus(status);
                    DataAccessManager dam = new DataAccessManager();
                    dam.fulfillRequest(fulfil);

                    //TODO reditrect to right place
                    response.sendRedirect("Search_Request.jsp");

            }  else {
                 model.setMessage("the Fulfilment Quantitry is too large than the request Quantity" + "("+ quantityValue +"+" + totelFulfilment+") > " + requestQuantity);
                 response.sendRedirect("Fulfill_rq.jsp");
            }
        } else{
                 response.sendRedirect("Fulfill_rq.jsp");
        }
%>
