package gov.lk.dms.report.framework.struts;

import gov.lk.dms.report.framework.jasper.JasperReportExporter;

import java.io.OutputStream;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.actions.DispatchAction;

/**
 * 
 * @author  Thushera P. Kawdawatta.
 * @version $Revision: 1.2 $, $Date: 2005-01-20 05:40:18 $
 *  
 */
public abstract class ReportDispatcherAction extends DispatchAction {

    private static DateFormat timestampFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    public interface Mapping {

        static final String SUCCESS = "success";

        /** Default forward mapping values for a failure mapping when attempt to invoke the specified method. */
        static final String FAILURE = "failure";
    }

    /**
     *  
     */
    public final ActionForward execute(ActionMapping mapping, ActionForm form, HttpServletRequest request,
                    HttpServletResponse response) throws Exception {
        

        //System.out.println("report template = " + mapping.getParameter());
        
        return doAction(mapping, form, request, response);
    }
    
    /**
     * 
     * @param mapping
     * @param form
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public abstract ActionForward doAction(ActionMapping mapping, ActionForm form, HttpServletRequest request,
                    HttpServletResponse response) throws Exception;

    /**
     * 
     * @param mapping
     * @param properties
     */
    protected void generateHTMLReport(ActionMapping mapping, Map properties) {
        JasperReportExporter expoter = JasperReportExporter.getInstance();
        String template = mapping.getParameter();

        if (template != null || template != "") {
            System.out.println("Initiate generate HTML for " + template);
            expoter.generateHTMLReport(template, properties);
        } else {
            System.out.println("No TEMPLATE defined, ignore generating HTML");
        }
    }

    /**
     * 
     * @param mapping
     */
    protected void generateHTMLReport(ActionMapping mapping) {
        generateHTMLReport(mapping, null);
    }

    protected OutputStream getHTMLStream(ActionMapping mapping, Map properties) {
        String template = mapping.getParameter();

        return getHTMLStream(template, properties);
    }

    protected OutputStream getHTMLStream(String template, Map properties) {
        JasperReportExporter expoter = JasperReportExporter.getInstance();
        OutputStream os = null;

        if (template != null || template != "") {
            System.out.println("Initiate generate HTML for " + template);
            os = expoter.getHTMLStream(template, properties);
        } else {
            System.out.println("No TEMPLATE defined, ignore generating HTML");
        }

        return os;
    }

    protected String getOutputHome() {
        return System.getProperty("output.home");
    }

}