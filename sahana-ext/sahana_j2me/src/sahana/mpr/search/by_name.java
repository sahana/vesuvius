/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  by_name.java
 * @date       24 July 2006
 */


package sahana.mpr.search;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.lang.String;
import sahana.mpr.send.*;

/* Author : Sahan C Priyadarshana
 */

public class by_name implements CommandListener{

public Display dis;
public Form backscreen,frm,form;
public final static Command cmd_Exit = new Command("Back", Command.STOP, 1);
public final static Command cmd_Ok = new Command("Ok", Command.SCREEN, 2);
public String url,key_word;
public TextField txt,key;


public by_name(Display dis,Form fm)
{
    this.dis=dis;
    backscreen=fm;
 	frm = new Form("By Name");
	dis.setCurrent(frm);

}

public void create()
{
	key = new TextField("Enter Any Name", "", 20, TextField.ANY);

 	frm.append(key);
 	frm.addCommand(cmd_Ok);
	frm.setCommandListener(this);
	frm.addCommand(cmd_Exit);
	frm.setCommandListener(this);

}


public void commandAction(Command c, Displayable s)
{
	 if(c==cmd_Exit)
	 {
	  dis.setCurrent(backscreen);

    }

	  else if (c == cmd_Ok)
	  {
		key_word = "key="+key.getString();
		url = "http://localhost:8080/sahana_php/mpr/get_key.php";

		new Thread(new Runnable() {
	                        public void run() {
								try{
									send send_obj = new send();
									String value = send_obj.send_Data(url,key_word);
									txt = new TextField("Search Result", value , 1024, TextField.ANY);
									frm.append(txt);
									dis.setCurrent(frm);
								}catch(Exception e){}
								  }}).start();
	  }

 }

}