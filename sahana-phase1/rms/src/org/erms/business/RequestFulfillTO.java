package org.erms.business;



/**

 * Created by IntelliJ IDEA.

 * User: Roshanp

 * Date: Dec 31, 2004

 * Time: 3:24:58 AM

 * To change this template use File | Settings | File Templates.

 */

public class RequestFulfillTO {



    private String requestDetailID;

    private String organization;

    private String serviceQuantity;

    private String status;

    private String fulfillID;



    /**

     * @return

     */

    public String getRequestDetailID() {

        return requestDetailID;

    }



    /**

     * @param requestDetailID

     */

    public void setRequestDetailID(String requestDetailID) {

        this.requestDetailID = requestDetailID;

    }



    /**

     * @return

     */

    public String getOrganization() {

        return organization;

    }



    /**

     * @param organization

     */

    public void setOrganization(String organization) {

        this.organization = organization;

    }



    public String getServiceQuantity() {

        return serviceQuantity;

    }



    /**

     * @param serviceQuantity

     */

    public void setServiceQuantity(String serviceQuantity) {

        this.serviceQuantity = serviceQuantity;

    }



    /**

     * @return

     */

    public String getStatus() {

        return status;

    }



    /**

     * @param status

     */

    public void setStatus(String status) {

        this.status = status;

    }
  public String getFulfillID() {
    return fulfillID;
  }
  public void setFulfillID(String fulfillID) {
    this.fulfillID = fulfillID;
  }
     public RequestFulfillTO(){}

    public RequestFulfillTO(String requestDetailID, String organization, String serviceQuantity, String status, String fulfillID) {
        this.requestDetailID = requestDetailID;
        this.organization = organization;
        this.serviceQuantity = serviceQuantity;
        this.status = status;
        this.fulfillID = fulfillID;
    }

    public Object createCopy() throws CloneNotSupportedException {
        RequestFulfillTO req = new RequestFulfillTO(requestDetailID, organization,  serviceQuantity,  status,  fulfillID);
        return req;    //To change body of overridden methods use File | Settings | File Templates.
    }
}

