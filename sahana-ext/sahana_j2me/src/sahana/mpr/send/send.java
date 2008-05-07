/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  send.java
 * @date       24 July 2006
 */


package sahana.mpr.send;

import java.io.*;
import javax.microedition.io.*;
import sahana.mpr.forms.*;

/* Author : Sahan C Priyadarshana
 */

public class send {

    String data_to_send;
    HttpConnection connection = null;
    OutputStream os = null;
    InputStream is = null;
    StringBuffer stringBuffer = new StringBuffer();
    String recv_url;

    public String send_Data(String url, String data) {

        data_to_send = data;
        recv_url = url;

        try {

		    String msg = data_to_send;
		    connection = (HttpConnection)Connector.open(recv_url);
		    connection.setRequestMethod(HttpConnection.POST);
		    connection.setRequestProperty("Content-Type","application/x-www-form-urlencoded");
		    connection.setRequestProperty("Content-Length", Integer.toString(msg.length()));

		    os = connection.openOutputStream();
		    os.write(msg.getBytes());
            is = connection.openInputStream();
            byte[] get_data = new byte[(int)connection.getLength()];
            is.read(get_data);
            System.out.println("Response:" + (new String(get_data)));

            stringBuffer.append((new String(get_data)));

		}
        catch(IOException e ) {
	  	    String error="Connection Down!";
	  	    stringBuffer.append(error);
	    }

        finally {
            if(is!= null)
	            try{
	                is.close();
	            }
	            catch (IOException e) {
				}

            if(os != null)
	            try{
	                os.close();
	            }
	            catch (IOException e) {
				}

            if(connection != null)
                try{
	                connection.close();
	            }
	            catch (IOException e) {
	            }
        }

        return stringBuffer.toString();
    }
}