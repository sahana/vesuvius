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
 * @author Thushera P. Kawdawatta.
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $
 * 
 * @class gov.lk.dms.report.action.erms.ERMSDetailAction
 *  
 */
public class ERMSDetailAction extends ReportDispatcherAction {

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
        OutputStream os = getHTMLStream(mapping, null);

        request.getSession().setAttribute("requestDetail", os.toString());
        
        return mapping.findForward(Mapping.SUCCESS);
    }
    
    private String getHTMLCode() {
        StringBuffer buf = new StringBuffer();
        
        buf.append("<html>");
        buf.append("<head>");
		buf.append("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">");
		buf.append("<style type=\"text/css\">");
		buf.append("a {text-decoration: none}");
		buf.append("</style>");
		buf.append("</head>");

		buf.append("<body>");

		buf.append("<div align=\"center\">");
		buf.append("This is Events body");
		buf.append("</div>");
		buf.append("</body>");
		buf.append("</html>");
		
		return buf.toString();                                                                                
    }

}