/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  ViewPledgesResults.java
 * @date       24 July 2006
 */


package sahana.rms.pledges.gui.view;

import sahana.rms.db.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.rms.*;
import java.util.*;
import java.io.*;
import javax.microedition.io.*;

/* Authors : Michelle Narangoda
 */

public class ViewPledgesResults implements CommandListener {
    private Display display;
    private TextBox screen;
    private Form backscreen;
    private TextField donerId;
    private Command backCommand,submitCommand,newCommand;

    public ViewPledgesResults (Display dis , Form main ,String sb) {
        display=dis;
        backscreen=main;
        
        /*Initialize commands*/
        backCommand=new Command("Back",Command.BACK,2);
        
        String strResult=sb;
	    screen=new TextBox("Display Doner Info","Searching\n"+strResult,500,TextField.ANY);
        
	    /*Adding and initializing GUI components*/       
        screen.addCommand(backCommand);
        
        /*Adding Listeners to the formidDonerInfo*/
        screen.setCommandListener(this);

        display.setCurrent(screen);
      }

    public void commandAction(Command c,Displayable s) {  
        String donerInfoString="";
        String pledgeInfoString="";

        if (c==backCommand) {
      	    display.setCurrent(backscreen);
        }        
        
        if (c==submitCommand) {
            /*Variables for store data in data store*/
            String varName = donerId.getString();
	        System.out.println(varName);
	    }

        if (c==newCommand) {
            /*Variables for store data in data store*/
            String varName = donerId.getString();
	        System.out.println(varName);
	    }
    }
}
