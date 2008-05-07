/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  GetHttp.java
 * @date       24 July 2006
 */


package sahana.rms.net;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.io.*;
import javax.microedition.io.*;
import java.util.*;

/* Authors : Kasun T Karunanayake
 */

public class GetHttp extends Thread {
    private String url;
    private StringBuffer data;
    private Network network; 
 
    public GetHttp(String url,Network nw) {	
    	network=nw;
	    this.url=url;
	    data = new StringBuffer();
    }   

    public void run() {
        try	{
	        getViaHttpConnection(url);
	    } catch (Exception e) {
	        network.getData(data);
	    }
    }
  
    void getViaHttpConnection(String url) throws Exception {
        HttpConnection c = null;
        InputStream is = null;
        OutputStream os = null;
        int rc,counter=0;
	
            try {
                c = (HttpConnection)Connector.open(url);
                rc = c.getResponseCode();
                if (rc != HttpConnection.HTTP_OK) {
                throw new IOException("HTTP response code: " + rc);
            }
            is = c.openInputStream();            
            String type = c.getType();
            System.out.println("Displaying the Type...........................");
	        System.out.println(type);
            
	        /* Get the length and process the data*/
            int len = (int)c.getLength();
            int ch;
                while ((ch = is.read()) != -1) {       
                	counter++;
		            data.append((char)ch);
                }
	            if((ch = is.read()) == -1) {
	            	throw new Exception(data.toString());
	            }
            } catch (ClassCastException e) {
             	throw new IllegalArgumentException("Not an HTTP URL");
            } finally {
                if (is != null)
                    is.close();
                if (os != null)
                    os.close();
                if (c != null)
                    c.close();
            }
    }
}