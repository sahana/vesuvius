/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  MidDel.java
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

public class MidDel implements CommandListener{
	public byte[] array_del;
    public RecordEnumeration record_num = null;
    public TextField delete_what;
    public Form go_form,delform;
    public RecordStore record;
    public Command commandBack , delCommand;
    public Display display_form;
    public String str,str_del,sub;
    public int i,k;
    public int[] set_array,int_array;
    public Alert alert;

    public MidDel(RecordStore recordstore , Form form , Display dis_del , RecordEnumeration rece_num , byte[] array_byts , int[] i_array ){

        set_array = i_array;
        array_del = array_byts;
        record_num = rece_num;
        display_form = dis_del;
        commandBack = new Command("BACK", Command.BACK, 1);
        delCommand = new Command("Delete Record", Command.SCREEN, 2);

        go_form = form;
        record = recordstore;
        delform = new Form("Delete Stored Information");

        delete_what=new TextField("Enter the record ID", "", 2, TextField.NUMERIC);
        delform.append(delete_what);

        delform.addCommand(commandBack);
        delform.setCommandListener(this);

        delform.addCommand(delCommand);
	  	delform.setCommandListener(this);

        display_form.setCurrent(delform);

    }

    public void delrecords() {

        str_del = delete_what.getString();
        k = Integer.parseInt(str_del);

            try {
		        int j = 0;
                    while(record_num.hasNextElement()) {
                        int_array = new int[record.getNumRecords()];
                        int id = record_num.nextRecordId();
                        int_array[j] = id;
                            if(int_array[j] == k) {
                                i = k;
                            }
                        j++;
                    }
                record.deleteRecord(i);
                alert = new Alert("Deleted" , "Successfully Deleted!" , null , null);
                alert.setTimeout(Alert.FOREVER);
                display_form.setCurrent(alert);
                display_form.setCurrent(go_form);
            }
            catch(RecordStoreException e) {
		        e.printStackTrace();
		    }

    }

    public void commandAction(Command c, Displayable displayable) {
        if (c == commandBack) {
            display_form.setCurrent(go_form);
        }

        if(c == delCommand) {
           this.delrecords();
        }
    }
}
