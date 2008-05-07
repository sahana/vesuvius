/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  MidSendRecords.java
 * @date       24 July 2006
 */

package sahana.cr.add_camp;

import javax.microedition.rms.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.io.*;
import java.lang.String;
import javax.microedition.io.*;
import sahana.mpr.message.*;

/* Author : Pradeep Senanayaka
 */

public class MidSendRecords {
    public Form sendForm;
    public Alert alert;
    public RecordStore record_store;
    public RecordEnumeration record_enum;
    public byte[] send_array;
    public String rec_send;
    public HttpConnection con = null;
    public String str_url , get_data;
    public OutputStream out_stream = null;
    public InputStream in_stream = null;
    public StringBuffer st_buff = new StringBuffer();
    public Display display;

    public MidSendRecords(Display disp , Form form , RecordEnumeration r_enum , RecordStore r_store , byte[] array) {
        sendForm = form;
        display  = disp;
        record_enum = r_enum;
        record_store = r_store;
        send_array = array;
    }

    public void sendRecords() {
        try{
            while(record_enum.hasNextElement()) {
                send_array = record_enum.nextRecord();
                int i = send_array.length;
                rec_send = new String(send_array,2,i-2);
                String append_url ="http://localhost:8080/sahana_php/cr/get.php?campName="+rec_send;
                get_data = this.sendRecordData(append_url);
                System.out.println(rec_send);
                System.out.println("\n");

	    }
                message mid_res = new message(display , sendForm , rec_send);

        }

        catch (Exception e) {
            System.out.println(e);
        }
    }

    public String sendRecordData(String input) {
        String get_str = input;
            try {
 	            con = (HttpConnection)Connector.open(get_str);
	            con.setRequestMethod(HttpConnection.GET);
	            con.setRequestProperty("User-Agent","Profile/MIDP-2.0 Confirguration/CLDC-1.0");
	            con.setRequestProperty("Content-Language" , "en-CA");
	            con.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
	            out_stream = con.openOutputStream();
	            in_stream = con.openDataInputStream();
	            int ch;
	                while ((ch = in_stream.read()) != -1) {
	  	                st_buff.append((char) ch);
     	            }
            }

            catch(IOException e ) {

                String error="Connection cannot be established!" + "\n" + "Go back and save it in your phone";
                st_buff.append(error);
            }
            finally {

            if(in_stream!= null)
	            try {
	                in_stream.close();
	            }
	            catch (IOException e) {
			    }

            if(out_stream != null)
                try {
	                out_stream.close();
	            }
                catch (IOException e) {
			    }

            if(con != null)
	            try {
	                con.close();
	            }
	            catch (IOException e) {
			    }

    }

           return st_buff.toString();

    }

     public void sendStore() {
         new Thread(new Runnable() {
	         public void run() {
                 sendRecords();
             }

         }).start();

    }

}
