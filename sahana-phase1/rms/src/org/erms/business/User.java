package org.erms.business;


public class User {
    private String userName;
    private String organization;
    private String orgCode;

    public User(String userName, String organization) {
        this.userName = userName;
        this.organization = organization;
    }

    public String getOrgCode() {
        return orgCode;
    }

    public void setOrgCode(String orgCode) {
        this.orgCode = orgCode;
    }

    /**
     * @return
     */
    public String getUserName() {
        return userName;
    }

    /**
     * @param string
     */
    public void setUserName(String string) {
        userName = string;
    }

    /**
     * @return
     */
    public String getOrganization() {
        return organization;
    }

    /**
     * @param string
     */
    public void setOrganization(String string) {
        organization = string;
    }

}
