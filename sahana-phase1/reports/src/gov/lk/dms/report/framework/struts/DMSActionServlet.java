package gov.lk.dms.report.framework.struts;

import gov.lk.dms.report.common.ReportEnvironment;

import javax.servlet.ServletException;

import org.apache.struts.action.ActionServlet;

/**
 * <p>
 * <strong>DMSActionServlet</strong>, has extended <code>ActionServlet</code> to allow multiple resource bundles to be
 * loaded for the application.
 * </p>
 *
 * <p>
 * The standard version of <code>DMSActionServlet</code> is configured based on the following servlet initialization
 * parameters, which can be specified in the web application deployment descriptor (<code>/WEB-INF/web.xml</code>) for the
 * application.
 * </p>
 *
 *
 * @author  Thushera Kawdawatta, Jan 03 2005
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $
 * 
 * @class gov.lk.dms.report.framework.struts.DMSActionServlet
 */
public class DMSActionServlet extends ActionServlet {

    /**
     * Initializes the client environment.
     *
     * @throws ServletException when initializing a servlet.
     */
    public void init()
        throws ServletException {
        super.init();

        ReportEnvironment.getInstance();
    }
}