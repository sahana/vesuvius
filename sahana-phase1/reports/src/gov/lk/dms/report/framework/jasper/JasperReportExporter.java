package gov.lk.dms.report.framework.jasper;

import gov.lk.dms.report.common.DBManager;
import gov.lk.dms.report.common.ReportEnvironment;
import gov.lk.dms.report.dao.VEDDao;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JasperExportManager;
import net.sf.jasperreports.engine.JasperManager;
import net.sf.jasperreports.engine.JasperPrint;
import net.sf.jasperreports.engine.JasperReport;
import net.sf.jasperreports.engine.export.JRHtmlExporter;
import net.sf.jasperreports.engine.export.JRHtmlExporterParameter;

/**
 * 
 * @author  Thushera P. Kawdawatta.
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $
 *  
 */
public class JasperReportExporter {

    private static final String JASPER_FILE_EXT = ".jasper";

    /*
     * Overriden Method.
     * 
     * @see java.lang.Object#clone()
     */
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    private static final String HTML_REPORT_SUFFIX = "_report.html";

    private static final String PDF_REPORT_SUFFIX = "_report.pdf";

    private static String sReportLocation = null;

    private static String sOutputLocation = null;

    private static Map sReports = new HashMap(10);

    private static final String US_ASCII = "US-ASCII";

    private static JasperReportExporter sInstance;

    private JasperReportExporter() {
    }
    
    public static void flushCache() {
        synchronized(sReports) {
            sReports.clear();
            sReports = new HashMap(10);
        }
    }
    
    public static JasperReportExporter getInstance() {

        if (sInstance == null) {
            sInstance = new JasperReportExporter();
            sReportLocation = System.getProperty("report.home");
            sOutputLocation = System.getProperty("output.home");
        }

        return sInstance;
    }

    public static void main(String[] args) {
        JasperReportExporter test = getInstance();
        ReportEnvironment.getInstance();
    }

    /**
     * Compiles the ticket template to a <code>JasperReports</code> format.
     * 
     * @param fileName -
     *            Name of the ticket template
     * 
     * @return Compiled template as a <code>JasperReport</code>
     * 
     * @throws Exception
     *             if the compiling fails
     */
    private JasperReport compileReport(String fileName) throws Exception {
        //System.out.println("compileReport");
        JasperReport jasperReport = (JasperReport) sReports.get(fileName);

        if (jasperReport == null) {
            //System.out.println("Load reports fresh");
            jasperReport = JasperManager.loadReport(getReportTemplate(fileName));
            sReports.put(fileName, jasperReport);
        }

        return jasperReport;
    }

    /**
     * Fetches the ticket template by the provided file name.
     * 
     * @param fileName -
     *            Name of the ticket template
     * 
     * @return Fetched report template as a <code>InputStream</code>
     */
    private InputStream getReportTemplate(String fileName) throws Exception {

        FileInputStream reportTemplate = null;
        String reportFileName = sReportLocation + File.separator + fileName;

        reportTemplate = new FileInputStream(reportFileName);

        return reportTemplate;
    }

    private Connection getConnection() {
        return DBManager.getInstance().getConnection();
    }

    private void closeConnection(Connection conn) {
        try {
            conn.close();
            //System.out.println("Conn Closed X");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    
    private JasperReport getJasperReport(String template) {
        JasperReport jasperReport = null;

        try {
            jasperReport = compileReport(template + JASPER_FILE_EXT);
        } catch (Exception e2) {
            e2.printStackTrace();
        }

        return jasperReport;
    }

    private JasperPrint getJasperPrint(JasperReport report, Map properties) {
        JasperPrint jasperPrint = null;

        try {
            jasperPrint = JasperManager.fillReport(report, properties, getConnection());
        } catch (JRException e3) {
            e3.printStackTrace();
        }

        return jasperPrint;
    }

    private JasperPrint getJasperPrint(String templateName, Map properties) {
        JasperPrint jasperPrint = null;
        
        Connection conn = getConnection();
        
        try {
            jasperPrint = JasperManager.fillReport(getJasperReport(templateName), properties, conn);
        } catch (JRException e3) {
            e3.printStackTrace();
        } finally {
            closeConnection(conn);
        }

        return jasperPrint;
    }

    public void generateHTMLReport(String templateName, Map reportParameters) {
        JasperPrint jasperPrint = getJasperPrint(templateName, reportParameters);
        String outFile = sOutputLocation + "/" + templateName + HTML_REPORT_SUFFIX;

        try {
            JasperExportManager.exportReportToHtmlFile(jasperPrint, outFile);
        } catch (JRException e) {
            e.printStackTrace();
        }
    }

    public void generatePDFReport(String templateName, Map reportParameters) {

        JasperPrint jasperPrint = getJasperPrint(templateName, reportParameters);
        String outFile = "./reports/" + templateName + PDF_REPORT_SUFFIX;

        try {
            JasperExportManager.exportReportToPdfFile(jasperPrint, outFile);
        } catch (JRException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public InputStream writeHTMLReport(String templateName, Map reportParameters) {
        JasperPrint jasperPrint = getJasperPrint(templateName, reportParameters);
        ByteArrayOutputStream baos = new ByteArrayOutputStream(9600);
        String outFile = "c:/" + templateName + HTML_REPORT_SUFFIX;

        JRHtmlExporter he = new JRHtmlExporter();

        try {
            he.setParameter(JRHtmlExporterParameter.JASPER_PRINT, jasperPrint);
            he.setParameter(JRHtmlExporterParameter.OUTPUT_STREAM, baos);
            he.setParameter(JRHtmlExporterParameter.IS_OUTPUT_IMAGES_TO_DIR, new Boolean(false));
            he.setParameter(JRHtmlExporterParameter.IS_REMOVE_EMPTY_SPACE_BETWEEN_ROWS, new Boolean(true));
            he.setParameter(JRHtmlExporterParameter.IS_USING_IMAGES_TO_ALIGN, new Boolean(false));
            he.setParameter(JRHtmlExporterParameter.IS_WHITE_PAGE_BACKGROUND, new Boolean(false));

            he.exportReport();
        } catch (JRException e) {
            e.printStackTrace();
        }

        try {
            FileOutputStream fout = new FileOutputStream(outFile, false);
            fout.write(baos.toByteArray());
            fout.close();
        } catch (FileNotFoundException e1) {
            e1.printStackTrace();
        } catch (IOException e1) {
            e1.printStackTrace();
        }

        return new ByteArrayInputStream(baos.toByteArray());
    }

    public OutputStream getHTMLStream(String templateName, Map reportParameters) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream(9600);
        JasperPrint jasperPrint = getJasperPrint(templateName, reportParameters);
        JRHtmlExporter he = new JRHtmlExporter();

        try {
            he.setParameter(JRHtmlExporterParameter.JASPER_PRINT, jasperPrint);
            he.setParameter(JRHtmlExporterParameter.OUTPUT_STREAM, baos);
            he.setParameter(JRHtmlExporterParameter.IS_OUTPUT_IMAGES_TO_DIR, new Boolean(false));
            he.setParameter(JRHtmlExporterParameter.IS_REMOVE_EMPTY_SPACE_BETWEEN_ROWS, new Boolean(true));
            he.setParameter(JRHtmlExporterParameter.IS_USING_IMAGES_TO_ALIGN, new Boolean(false));
            he.setParameter(JRHtmlExporterParameter.IS_WHITE_PAGE_BACKGROUND, new Boolean(false));

            he.exportReport();
        } catch (JRException e) {
            e.printStackTrace();
        }

        return baos;
    }
}

