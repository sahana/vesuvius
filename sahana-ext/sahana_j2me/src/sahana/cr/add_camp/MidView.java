/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  MidView.java
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

public class MidView implements CommandListener {
    public Command commandBack;
    public byte[] btarray;
    public RecordStore record;
    public RecordEnumeration rec_enum;
    public Display display_view;
    public Form form_view,backform;
    public StringItem stritem;
    public String page;

    public MidView(byte[] array , RecordStore recordstore , Display display_rec , Form disform , RecordEnumeration rec_enumerate) {
        rec_enum = rec_enumerate;
        commandBack = new Command("BACK", Command.BACK, 1);
        backform = disform;
        display_view = display_rec;
        btarray = array;
        record = recordstore;
        form_view = new Form("The Information Stored");
        form_view.addCommand(commandBack);
        form_view.setCommandListener(this);
    }

    public void viewRec() {
        try {
	        while(rec_enum.hasNextElement()) {
                btarray = rec_enum.nextRecord();
                int i = btarray.length;
                page = new String(btarray,2,i-2);
                form_view.append(new StringItem("",page));
                form_view.append(new StringItem(""," "));
                System.out.println(page);
                System.out.println("\n");

		   }
               display_view.setCurrent(form_view);
       }

	   catch (Exception e) {
           System.out.println(e);
       }
    }

    public void commandAction(Command c, Displayable displayable) {
        if (c == commandBack) {
            display_view.setCurrent(backform);
        }
    }
}
