package org.erms.util;

import org.erms.business.RequestTO;
import org.erms.business.RequestDetailTO;

import java.util.Collection;

public class FulfilmentModel {
    private String message;

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public Collection getFulfilment() {
        return fulfilment;
    }

    public void setFulfilment(Collection fulfilment) {
        this.fulfilment = fulfilment;
    }

    public RequestTO getRequest() {
        return request;
    }

    public void setRequest(RequestTO request) {
        this.request = request;
    }

    public RequestDetailTO getRequestDetail() {
        return requestDetail;
    }

    public void setRequestDetail(RequestDetailTO requestDetail) {
        this.requestDetail = requestDetail;
    }

    public int getQuanttiy() {
        return quanttiy;
    }

    public void setQuanttiy(int quanttiy) {
        this.quanttiy = quanttiy;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    private Collection fulfilment;
    private RequestTO request;
    private RequestDetailTO requestDetail;
    private int quanttiy;
    private String status;
    private String requestDetailID;

    public String getRequestDetailID() {
        return requestDetailID;
    }

    public void setRequestDetailID(String requestDetailID) {
        this.requestDetailID = requestDetailID;
    }

}
