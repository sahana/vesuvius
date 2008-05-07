/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  Mpr.java
 * @date       24 July 2006
 */

package sahana.mpr;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import java.io.*;
import sahana.mpr.rms.*;
import sahana.mpr.forms.*;

/* Authors : Sahan C Priyadarshana
 *           Thayalan Gugathashan
 */

public class Mpr implements CommandListener {

    public Command backCommand = new Command("Back", Command.BACK, 1);
    public Display display;
    public List first,choice,backscreen;
    public Image icon=null;
    public String ri,rt,url;
    public ChoiceGroup search_selection= null;
    public TemplateRecordStore dbs;
    public Form fm,form;
    public String currentScreen;


    public Mpr(Display d, List l) {

        display = d;
        backscreen = l;

        first = new List("Missing Person Registry", Choice.IMPLICIT);
        first.append("Report a Missing Person",icon); //form
        first.append("Search People",icon);
        first.setCommandListener(this);
        first.addCommand(backCommand);
        first.setCommandListener(this);
        display.setCurrent(first);

    }

    public void commandAction(Command c, Displayable s) {
        try {
            if (c == List.SELECT_COMMAND) {
                if (s.equals(first)) {
                    switch ( ( (List) s).getSelectedIndex()) {
                        case 0:
		                    form_1 f_1 = new form_1(display,first);
		                    f_1.CreateForm();
              	            break;

                        case 1:
            	            search_Form search_obj = new search_Form(display,first);
            	            search_obj.create();
                            break;
                    }
                }
            }
        }
        catch (Exception e) {
        }

            if(c == backCommand) {
		        display.setCurrent(backscreen);
	        }
    }
}

