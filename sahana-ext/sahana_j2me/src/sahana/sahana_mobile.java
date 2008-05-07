/**
 * Sahana J2ME Client
 *
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @authors    Kasun T Karunanayaka
 *             Michelle Narangoda
 *             Pradeep D Senanayaka
 *             Muguntha Ramachandran
 *             Thayalan Gugathashan
 *             Sahan C Priyadarshana
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  sahana_mobile.java
 * @version    0.1
 * @date       24 July 2006
 */

package sahana;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;
import sahana.rms.*;
import sahana.mpr.*;
import sahana.cr.*;



public class sahana_mobile extends MIDlet implements CommandListener {

    protected Command okCommand = new Command("Ok", Command.OK, 1);
    protected Command exitCommand = new Command("Exit", Command.STOP, 1);
    protected Command backCommand = new Command("Back", Command.BACK, 1);
    protected Display display;
    protected List list,choice;
    protected String ri,rt,url;
    protected Form fm,form,mem_form;
    protected TextField memory;


    public sahana_mobile() {
        list = new List("Sahana Disaster Management System", Choice.IMPLICIT);
        list.append("Missing Person Registry",null);
        list.append("Camps Registry",null);
        list.append("Request Management System",null);
        list.append("Memory Test",null);
        list.setCommandListener(this);

        Runtime runtime = Runtime.getRuntime();
	    runtime.gc();
	    long free = runtime.freeMemory();
	    ri = "\nTotal Memory : "+runtime.totalMemory();
	    rt= "\nFree Memory : " + free ;

        display = Display.getDisplay(this);
    }

    public void startApp() {
        display.setCurrent(list);
    }

    public void pauseApp() {
	    list = null;
	}

    public void destroyApp(boolean unconditional) {
	    notifyDestroyed();
	}

    public void commandAction(Command c, Displayable s) {
        try {
            if (c == List.SELECT_COMMAND) {
                if (s.equals(list)) {
                    switch ( ( (List) s).getSelectedIndex()) {

                    case 0:
         	  	        Mpr mpr = new Mpr(display,list);
         	  	        break;

                    case 1:
              	        Cr cr = new Cr(display,list);
              	        break;

                    case 2:
        	  	        Rms rms = new Rms(display,list);
        	  	        break;

        	        case 3:
        	  	        memory = new TextField("", ri+rt, 50, TextField.ANY);
				        mem_form = new Form("Memory Status");
		    	        mem_form.append(memory);
				        mem_form.addCommand(backCommand);
				        mem_form.setCommandListener(this);
				        display.setCurrent(mem_form);
              	        break;

                    }
                }
            }
        }
        catch (Exception e) {
    }

        if(c == exitCommand) {
	        destroyApp(true);
        }

	    if(c == backCommand) {
	        display.setCurrent(list);
  	    }
    }
}

