<%@ page import="javax.servlet.http.HttpServletRequest,
                 javax.servlet.http.HttpServletResponse,
                 org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 org.erms.business.*,
                 org.erms.util.FulfilmentModel,
                 java.util.*,
                 tccsol.admin.accessControl.LoginBean" %>
<%
    try{
    LoginBean lbean = (LoginBean)session.getAttribute("LoginBean");
    if (lbean==null){
        throw new Exception("Please login with a valid username and password");
    }
    User user = new  User(lbean.getUserName(),lbean.getOrgId(),lbean.getOrgName());

    //OK we are authenticated


    FulfilmentModel model = (FulfilmentModel) request.getSession().getAttribute(ERMSConstants.REQUEST_FULFILL_MODEL);

    Collection oldCollection = new ArrayList();
    Collection newCollection = new ArrayList();
    String requestDetailstatus = null;

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

            if(quantityValue != 0 && fulfilments.isEmpty()){
               requestDetailstatus = "InProgress";
            }

            if("Delivered".equalsIgnoreCase(status.trim())){
                toteldeliverd = toteldeliverd + quantityValue;
            }

            if((quantityValue + totelFulfilment) > requestQuantity){
                model.setMessage("\"Fulfillment Quantity\" can not be larger than the \"Request Quantity\"" + "("+ totelFulfilment +"+" + quantityValue +") > " + requestQuantity);
                DataAccessManager dam = new DataAccessManager();
                //dam.fulfillRequest(rfdto);
                dam.fulfillRequest(rfdto,oldCollection,newCollection,status,model.getRequestDetailID());
                response.sendRedirect("Fulfill_rq.jsp");
                return;
            }


            rfdto = new RequestFulfillDetailTO();
            rfdto.setOrgCode(user.getOrgCode());
            rfdto.setOrgName(user.getOrganization());
            rfdto.setStatus(status);
            rfdto.setQuantity(quantity);
            rfdto.setRequestDetailID(model.getRequestDetailID());
        } else{


        }
        System.out.println("VAL" + toteldeliverd + " = "+ requestQuantity);
        if(toteldeliverd >= requestQuantity){
                System.out.println("Request Closed");
                requestDetailstatus = "Closed";
        }


        DataAccessManager dam = new DataAccessManager();
        //dam.fulfillRequest(rfdto);
        dam.fulfillRequest(rfdto,oldCollection,newCollection,requestDetailstatus,model.getRequestDetailID());
       response.sendRedirect("Fulfill_rq.jsp?RequestDetailID="+model.getRequestDetailID());
    }catch(Exception e){
          e.printStackTrace();
          throw e;
    }
%>
