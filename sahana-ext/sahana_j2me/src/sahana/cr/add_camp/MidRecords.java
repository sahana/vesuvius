/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  MidRecords.java
 * @date       24 July 2006
 */

package sahana.cr.add_camp;

import javax.microedition.rms.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.io.*;
import java.lang.String;

/* Author : Pradeep Senanayaka
 */

public class MidRecords {
    public int[] int_array;
    public String[] arrayas;
    public RecordStore rec = null;
    public RecordEnumeration recenum = null;
    public byte[] bytearray;
    public String string;
    public String st1,st2,st3,st4,st5,st6,st7,st8,st9,st10,st11,st12,st13,st14,st15,st16,st17;
    public Display display;
    public Form formadd;
    public int i;
    public Alert alert;

    public MidRecords(Display disp , Form form) {
        formadd = form;
            try {
		        rec = RecordStore.openRecordStore("MOBILED",true);
                recenum = rec.enumerateRecords(null, null,false);
                display = disp;
            }
            catch(Exception er) {
                System.out.println(er);
            }
    }

    public void saveRec(String[] arraysave) {
        try {
            String[] strarray = arraysave;
            ByteArrayOutputStream output = new ByteArrayOutputStream();
            DataOutputStream dataout = new DataOutputStream(output);

            int q = rec.getNextRecordID();

            st1  = strarray[0];
            st2  = strarray[1];
            st3  = strarray[2];
            st4  = strarray[3];
            st5  = strarray[4];
            st6  = strarray[5];
            st7  = strarray[6];
            st8  = strarray[7];
            st9  = strarray[8];
            st10 = strarray[9];
            st11 = strarray[10];
            st12 = strarray[11];
            st13 = strarray[12];
            st14 = strarray[13];
            st15 = strarray[14];
            st16 = strarray[15];

            string = st1+"/"+st2+"/"+st3+"/"+st4+"/"+st5+"/"+st6+"/"+st7+"/"+st8+"/"+st9+"/"+st10+"/"+st11+"/"+st12+"/"+st13+"/"+st14+"/"+st15+"/"+st16+"/"+"Rec-ID:-"+q;

	        dataout.writeUTF(string);
	        dataout.flush();
	        bytearray = output.toByteArray();
	        rec.addRecord(bytearray,0,bytearray.length);

            output.reset();
            output.close();
            dataout.close();

            alert = new Alert("Saved" , "Successfully Saved!" , null , null);
            alert.setTimeout(Alert.FOREVER);
            display.setCurrent(alert);

        }
        catch (Exception e) {
            System.out.println(e);
        }
    }


    public void viewRecords() {
        MidView midview = new MidView(bytearray , rec , display , formadd , recenum);
        midview.viewRec();
    }

    public void delRec() {
        MidDel middel = new MidDel(rec , formadd , display , recenum , bytearray , int_array);
    }

    public void sendRec() {
        MidSendRecords send_rec = new MidSendRecords(display , formadd , recenum , rec , bytearray);
        send_rec.sendStore();
    }
}
