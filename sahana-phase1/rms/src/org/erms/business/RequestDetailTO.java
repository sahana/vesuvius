package org.erms.business;


public class RequestDetailTO {
    private String requestDetailID;
    private String requestID;
    private String category;
    private String description;
    private String unit;
    private int quantity;
    private String item;
    private String priority;
    private String categoryName;
    private String status;

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getCategoryName() {
        return categoryName;
    }

    public void setCategoryName(String categoryName) {
        this.categoryName = categoryName;
    }

    public RequestDetailTO() {
    }

    public RequestDetailTO(String requestDetailID, String requestID, String category, String description, String unit, int quantity, String item, String priority) {
        this.requestDetailID = requestDetailID;
        this.requestID = requestID;
        this.category = category;
        this.description = description;
        this.unit = unit;
        this.quantity = quantity;
        this.item = item;
        this.priority = priority;
    }

    public String getRequestDetailID() {
        return requestDetailID;
    }

    public void setRequestDetailID(String requestDetailID) {
        this.requestDetailID = requestDetailID;
    }

    public String getRequestID() {
        return requestID;
    }

    public void setRequestID(String requestID) {
        this.requestID = requestID;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getUnit() {
        return unit;
    }

    public void setUnit(String unit) {
        this.unit = unit;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public String getItem() {
        return item;
    }

    public void setItem(String item) {
        this.item = item;
    }

    public String getPriority() {
        return priority;
    }

    public void setPriority(String priority) {
        this.priority = priority;
    }

}
