package org.erms.business;

import java.util.Collection;

/**
 * Created by IntelliJ IDEA.
 * User: hemapani
 * Date: Jan 6, 2005
 * Time: 5:49:02 PM
 * To change this template use File | Settings | File Templates.
 */
public class RequestInfo {
    private RequestTO request;
    private Collection services;

    public RequestTO getRequest() {
        return request;
    }

    public void setRequest(RequestTO request) {
        this.request = request;
    }

    public Collection getServices() {
        return services;
    }

    public void setServices(Collection services) {
        this.services = services;
    }
}
