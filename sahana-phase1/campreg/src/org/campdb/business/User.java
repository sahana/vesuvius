package org.campdb.business;


public class User {
    private String userName;
    private String organization;

    public User(String userName, String organization) {
        this.userName = userName;
        this.organization = organization;
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
