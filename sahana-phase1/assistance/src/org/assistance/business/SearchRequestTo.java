package org.assistance.business;

import java.sql.Date;

/**
 * Created by IntelliJ IDEA.
 * User: hemapani
 * Date: Jan 6, 2005
 * Time: 12:19:56 PM
 * To change this template use File | Settings | File Templates.
 */
public class SearchRequestTo {
    private Date requestDateFrom;
    private Date requestDateTo;
    private String agancy;
    private String partners;

    public Date getRequestDateFrom() {
        return requestDateFrom;
    }

    public void setRequestDateFrom(Date requestDateFrom) {
        this.requestDateFrom = requestDateFrom;
    }

    public Date getRequestDateTo() {
        return requestDateTo;
    }

    public void setRequestDateTo(Date requestDateTo) {
        this.requestDateTo = requestDateTo;
    }

    public String getAgancy() {
        return agancy;
    }

    public void setAgancy(String agancy) {
        this.agancy = agancy;
    }

    public String getPartners() {
        return partners;
    }

    public void setPartners(String partners) {
        this.partners = partners;
    }
}
