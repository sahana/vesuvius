/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  NewLocation.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.newr;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.rms.*;
import java.io.*;

/* Authors : Kasun T Karunanayake
 */ 

public class NewLocation implements CommandListener {

	private Form form;
	private Display display;
	private TextField location_name;
	private TextField location_id;
	private TextField type;
	private TextField code;
	private TextField address;
	private TextField gis;
	private Command addlocation;
	private String fullString;
	private int primaryId;

	public NewLocation(Display dis,int primaryId) {
		this.display = dis;
		this.primaryId=primaryId;
		form  = new Form("New Location");
		location_name	= new TextField("Location Name" , "" , 100 , TextField.ANY);
		location_id	= new TextField("Location ID" , "" , 100 , TextField.ANY);
		type	= new TextField("Type" , "" , 100 , TextField.ANY);
		code	= new TextField("Code" , "" , 100 , TextField.ANY);
		address	= new TextField("Address" , "" , 100 , TextField.ANY);
		gis	= new TextField("GIS" , "" , 100 , TextField.ANY);
		addlocation  = new Command("Add Location" , Command.SCREEN , 1);

		form.append(location_name);
		form.append(location_id);
		form.append(type);
		form.append(code);
		form.append(address);
		form.append(gis);

		form.addCommand(addlocation);
		form.setCommandListener(this);

		display.setCurrent(form);
	}

	public void commandAction(Command command , Displayable displayable) {
		if ( command == addlocation ) {
			String name = this.location_name.getString();
			String id = this.location_id.getString();
			String type = this.type.getString();
			String code  = this.code.getString();
			String add  = this.address.getString();
			String gis  = this.gis.getString();

				if ( name.equals("") && id.equals("") && code.equals("") && type.equals("") && add.equals("")){
					Alert alert = new Alert("ERROR" , "         OOOOPS !! PLEASE ENTER ALL THE\n         DETAILS !!" , null ,AlertType.ERROR );
					display.setCurrent(alert);
				}
			
			fullString="name="+name+"&id="+id+"&type"+type+"&address"+add+"&gis"+add+"&gis"+gis;
			NewItem ni = new NewItem(display,form,fullString,primaryId);
		}
	}
}