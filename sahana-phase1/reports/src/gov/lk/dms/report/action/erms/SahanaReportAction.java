package gov.lk.dms.report.action.erms;

import gov.lk.dms.report.framework.struts.ReportDispatcherAction;

import java.io.OutputStream;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * 
 * @author  Thushera P. Kawdawatta.
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $
 * 
 * @class gov.lk.dms.report.action.erms.ERMSDetailAction
 *  
 */
public class SahanaReportAction extends ReportDispatcherAction {

    /*
     * Overriden Method.
     * 
     * @see com.virtusa.framework.struts.ReportDispatcherAction#doAction(org.apache.struts.action.ActionMapping,
     *      org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest,
     *      javax.servlet.http.HttpServletResponse)
     */
    public ActionForward doAction(ActionMapping mapping, ActionForm form, HttpServletRequest request,
                    HttpServletResponse response) throws Exception {

        //generateHTMLReport(mapping);
        String reportName = request.getParameter("report");
        OutputStream os = getHTMLStream(reportName, null);
        
        request.getSession().setAttribute("ReportsData", os.toString());
        request.setAttribute("ReportsData", os.toString());
        
        return mapping.findForward(Mapping.SUCCESS);
    }
}