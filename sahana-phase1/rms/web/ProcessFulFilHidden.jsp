<%@ page import="javax.servlet.http.HttpServletRequest,
                 javax.servlet.http.HttpServletResponse,
                 org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 org.erms.business.*,
                 org.erms.util.FulfilmentModel,
                 java.util.*" %>
<%
    try{
    User user = (User) request.getSession().getAttribute(ERMSConstants.IContextInfoConstants.USER_INFO);
    if (user==null){
        //Nobody should come here without a user
        request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User not authenticated!");
        response.sendRedirect("error.jsp");
    }
    //OK we are authenticated


    FulfilmentModel model = (FulfilmentModel) request.getSession().getAttribute(ERMSConstants.REQUEST_FULFILL_MODEL);

    Collection oldCollection = new ArrayList();
    Collection newCollection = new ArrayList();
    boolean closeRequest = false;




    RequestDetailTO requestDetailObj = model.getRequestDetail();
    RequestFulfillDetailTO fd = null;

    //Gather fulfilemnt information
    Collection fulfilments = model.getFulfilment();
    int totelFulfilment = 0;
    int toteldeliverd = 0;
    int index = 0;
    Iterator it = fulfilments.iterator();

    while(it.hasNext()){
        fd = (RequestFulfillDetailTO)it.next();
        oldCollection.add(fd.createCopy());
        String changedStatus =  request.getParameter("catogories"+index);
        if(changedStatus != null && !changedStatus.equals(fd.getStatus())){
               fd.setStatus(changedStatus);
        }

        index++;
        String value = fd.getQuantity();
        if(value != null && !"withdrawn".equalsIgnoreCase(fd.getStatus().trim())){
            int intValue =  Integer.parseInt (value.trim());
            totelFulfilment = totelFulfilment + intValue;


            if("Delivered".equalsIgnoreCase(fd.getStatus().trim())){
                toteldeliverd = toteldeliverd + intValue;
            }
        }
        newCollection.add(fd.createCopy());
    }


        String status =   request.getParameter("FulfilStatus");
        String quantity = request.getParameter("FulfilQuantity");

        int requestQuantity = requestDetailObj.getQuantity();
        int quantityValue = 0;

        RequestFulfillDetailTO rfdto = null;
        if(quantity != null && quantity.trim().length() != 0){
            quantityValue = Integer.parseInt (quantity.trim());
            toteldeliverd = quantityValue + quantityValue;


            if((quantityValue + totelFulfilment) > requestQuantity){
                model.setMessage("\"Fulfilment Quantitry\" can not be larger than the \"Request Quantity\"" + "("+ totelFulfilment +"+" + quantityValue +") > " + requestQuantity);
                DataAccessManager dam = new DataAccessManager();
                //dam.fulfillRequest(rfdto);
                dam.fulfillRequest(rfdto,oldCollection,newCollection,closeRequest,model.getRequestDetailID());
                response.sendRedirect("Fulfill_rq.jsp");
                return;
            }


            rfdto = new RequestFulfillDetailTO();
            rfdto.setOrgCode(user.getOrgCode());
            rfdto.setOrgName(user.getOrganization());
            rfdto.setStatus(status);
            rfdto.setQuantity(quantity);
            rfdto.setRequestDetailID(model.getRequestDetailID());
//
//            fulfilments.add(rfdto);

        } else{


        }
        System.out.println("VAL" + toteldeliverd + " = "+ requestQuantity);
        if(toteldeliverd >= requestQuantity){
                System.out.println("Request Closed");
                closeRequest = true;
        }


        DataAccessManager dam = new DataAccessManager();
        //dam.fulfillRequest(rfdto);
        dam.fulfillRequest(rfdto,oldCollection,newCollection,closeRequest,model.getRequestDetailID());
       response.sendRedirect("Fulfill_rq.jsp?RequestDetailID="+model.getRequestDetailID());
    }catch(Exception e){
          e.printStackTrace();
          throw e;
    }
%>
