package org.erms.business;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: </p>
 *
 * @author not attributable
 * @version 1.0
 */

public class RequestFulfillDetailTO {

    public String getOrgCode() {
        return orgCode;
    }

    public void setOrgCode(String orgCode) {
        this.orgCode = orgCode;
    }

    public String getOrgName() {
        return orgnName;
    }

    public void setOrgName(String orgName) {
        this.orgnName = orgName;
    }

    public String getOrgContact() {
        return orgContact;
    }

    public void setOrgContact(String orgContact) {
        this.orgContact = orgContact;
    }

    public String getQuantity() {
        return quantity;
    }

    public void setQuantity(String quantity) {
        this.quantity = quantity;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
  public String getFulfillID() {
    return fulfillID;
  }
  public void setFulfillID(String fulfillID) {
    this.fulfillID = fulfillID;
  }

    private String orgCode;
    private String orgnName;
    private String orgContact;
    private String quantity;
    private String status;
    private String fulfillID;
    private String requestDetailID;

    public String getRequestDetailID() {
        return requestDetailID;
    }

    public void setRequestDetailID(String requestDetailID) {
        this.requestDetailID = requestDetailID;
    }

    public Object createCopy() throws CloneNotSupportedException {
        RequestFulfillDetailTO req = new RequestFulfillDetailTO( orgCode,  orgnName,  orgContact,  quantity,  status,  fulfillID,  requestDetailID);
        return req;
    }

    public RequestFulfillDetailTO(){}

    public RequestFulfillDetailTO(String orgCode, String orgnName, String orgContact, String quantity, String status, String fulfillID, String requestDetailID) {
        this.orgCode = orgCode;
        this.orgnName = orgnName;
        this.orgContact = orgContact;
        this.quantity = quantity;
        this.status = status;
        this.fulfillID = fulfillID;
        this.requestDetailID = requestDetailID;

        System.out.println("orgCode = " + orgCode);
        System.out.println("orgnName = " + orgnName);
        System.out.println("orgContact = " + orgContact);
        System.out.println("quantity = " + quantity);
        System.out.println("status = " + status);
        System.out.println("fulfillID = " + fulfillID);
        System.out.println("requestDetailID = " + requestDetailID);
    }
}
