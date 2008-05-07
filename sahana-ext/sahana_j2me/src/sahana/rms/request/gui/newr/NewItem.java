/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  NewItem.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.newr;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.rms.*;
import java.io.*;
import sahana.mpr.send.*;
import sahana.rms.db.*;

/* Authors : Kasun T Karunanayake
 */

public class NewItem implements CommandListener {
	
	private Form form;
	private Form backscreen;
	private Display display;
	private ChoiceGroup category;
	private ChoiceGroup item;
	private TextField quantity;
	private ChoiceGroup priority;
	private String networkData,stringSecond,url,data;
	private Command back,next;
	private int primaryId;

	public NewItem(Display dis , Form frm,String strData,int primaryId) {

		this.display = dis;
		this.primaryId=primaryId;
		stringSecond=strData;
		backscreen = frm;
		form  = new Form("New Item");
		category	= new ChoiceGroup("Category   :      " ,Choice.POPUP);
		category.append("Food" , null);
		category.append("Medicine" , null);
		category.append("Test" , null);
		category.append("Blankets" , null);

		int cat = category.getSelectedIndex();
		item	= new ChoiceGroup("Item   :      " ,Choice.POPUP);

		if ( cat == 0 ) {
			item.append("Dry Food" , null);
			item.append("Test" , null);
			item.append("Rice" , null);
		} else if ( cat == 1 ) {
			item.append("Paracetamol" , null);
		} else if ( cat == 2 ) {
			item.append("Test" , null);
		} else if ( cat == 3 ) {
			item.append("Cotton" , null);
		}
		
		quantity = new TextField("Quantity" , "" , 150 , TextField.ANY);
		priority	= new ChoiceGroup("Priority   :      " ,Choice.POPUP);
		priority.append("Immediate" , null);
		priority.append("Moderate" , null);
		priority.append("Low Priority" , null);
		back  = new Command("Back" , Command.BACK , 1);
		next  = new Command("Next" , Command.OK, 1);

		form.append(category);
		form.append(item);
		form.append(quantity);
		form.append(priority);
		form.addCommand(back);
		form.addCommand(next);
		form.setCommandListener(this);

		display.setCurrent(form);
	}

	public void commandAction(Command command , Displayable displayable) {
		if (command == back) {
			display.setCurrent(backscreen);
		}
		
		if (command == next) {
			String ItemCategory 	= category.getString(category.getSelectedIndex());
			String Item 			= item.getString(item.getSelectedIndex());
			String ItemQuantity 	= quantity.getString();
			String ItemPriority 	= priority.getString(priority.getSelectedIndex());
				
			if (ItemQuantity.equals("")) {
				Alert alert = new Alert("ERROR" , "         OOOOPS !! PLEASE ENTER ALL THE\n         DETAILS !!" , null ,AlertType.ERROR );
			    display.setCurrent(alert);
			} else {
				try {
					RecordStoreHandler rsh=new RecordStoreHandler();
					data=stringSecond+"&catagory="+ItemCategory+"&item="+Item+"&quantity="+ItemQuantity+"&type="+ItemPriority;
					rsh.openRecordStore("RequestPrimayRecordStore","RequestSecondaryRecordStore");
					int addno =rsh.addSecondaryRecord(primaryId,data);
					System.out.println(addno);
				} catch (Exception e) {					
				}

				url = "http://localhost:8080/date/next.jsp?" ;/*+stringfirst + stringSecond;*/

				new Thread(new Runnable() {
					public void run() {
						try{
							send snd = new send();
							String value = snd.send_Data(url , data);
							
							System.out.println(value);
						} catch(Exception e) {								
						}
						}}).start();
			}
		}
	}
}