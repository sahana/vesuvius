package org.transport.business;

import java.sql.Date;

/**
 * Copyright 2001-2004 The Apache Software Foundation.
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
public class ConsignmentItemTO {
  
    public ConsignmentItemTO(int consignmentId, String itemCode,
       int issuedQty, String uoM, int acceptedQty, Date expDate, 
       String conversion, String comments)
    {
        this.consignmentId = consignmentId;
        this.itemCode = itemCode;
        this.issuedQty = issuedQty;
        this.UoM = uoM;
        this.expDate = expDate;
        this.acceptedQty = acceptedQty;
        this.conversion = conversion;
        this.comments = comments;
    }
  
    public String getItemCode() {
        return itemCode;
    }

    public void setItemCode(String itemCode) {
        this.itemCode = itemCode;
    }

    public int getConsignmentId() {
        return consignmentId;
    }

    public void setConsignmentId(int consignmentId) {
        this.consignmentId = consignmentId;
    }

    public int getIssuedQty() {
        return issuedQty;
    }

    public void setIssuedQty(int issuedQty) {
        this.issuedQty = issuedQty;
    }

    public String getComments() {
        return comments;
    }

    public void setComments(String comments) {
        this.comments = comments;
    }

    public String getUoM() {
        return UoM;
    }

    public void setUoM(String uoM) {
        UoM = uoM;
    }

    public String getConversion() {
        return conversion;
    }

    public void setConversion(String conversion) {
        this.conversion = conversion;
    }

    public Date getExpDate() {
        return expDate;
    }

    public void setExpDate(Date expDate) {
        this.expDate = expDate;
    }

    public int getAcceptedQty() {
        return acceptedQty;
    }

    public void setAcceptedQty(int acceptedQty) {
        this.acceptedQty = acceptedQty;
    }

    private String itemCode;
    private int consignmentId;
    private String comments;
    private int issuedQty;
    private String UoM;
    private String conversion;
    private Date expDate;
    private int acceptedQty;
}
