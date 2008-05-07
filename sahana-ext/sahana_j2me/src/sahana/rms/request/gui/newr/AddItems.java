/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  AddItems.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.newr;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.rms.*;
import java.io.*;

/* Authors : Kasun T Karunanayake
 */

public class AddItems implements CommandListener{

	private Display display;
	private Form form;
	private ChoiceGroup category;
	private TextField item;
	private TextField units;
	private TextField quantity;
	private List backscreen;
	private ChoiceGroup priority;
	private Command save;
	private Command back;
 
	public AddItems(Display dis , String details , List main) {

		this.display = dis;
		backscreen = main;		
		form  = new Form("Add Items");
		category	= new ChoiceGroup("Category   :      " ,Choice.POPUP);
		category.append("Blanket Shelter" , null);
		category.append("Medical Drugs" , null);
		category.append("Food & Nutrition" , null);
		category.append("Other" , null);

		item	= new TextField("Item" , "" , 150 , TextField.ANY);
		units	= new TextField("Units" , "" , 50 , TextField.ANY);
		quantity	= new TextField("Quantity" , "" , 100 , TextField.ANY);
		priority	= new ChoiceGroup("Priority    :       " ,Choice.POPUP);

		priority.append(" Immediate  ( < 1 week )" , null);
		priority.append(" Medium      ( < 1 mon )" , null);
		priority.append(" Long term  ( 1-3 mon )" , null);

		form.append(category);
		form.append(item);
		form.append(units);
		form.append(quantity);
		form.append(priority);

		save  = new Command("Save" , Command.SCREEN , 1);
		back  = new Command("Back" , Command.BACK , 2);

		form.addCommand(save);
		form.addCommand(back);
		form.setCommandListener(this);

		display.setCurrent(form);
	}

	public void commandAction(Command command , Displayable displayable) {
		if ( command == back ) {
			display.setCurrent(backscreen);
	    } else if ( command == save ) {

	    	/*   try{

            mainstore = RecordStore.openRecordStore("Main" , true);
            firstrecordenumeration = mainstore.enumerateRecords( null , null , false );
            if (firstrecordenumeration.hasNextElement());// if there are records search the enumeration
              //secondrecordenumeration = secondarystore.enumerateRecords( null , null , false );
               //if (secondrecordenumeration.hasNextElement());//if there are records then seacrch and see whether a match ,,, if so add the quantity to it
                   //else {
            	else  { // if no records in the main recordstore
               	alert = new Alert("ok","ok",null,AlertType.WARNING);
	            byte[] main = details.getBytes();
               	mainstore.addRecord( main , 0 , main.length );
               	alert = new Alert("ok","added record",null,AlertType.WARNING);
               	seconderystore = RecordStore.openRecordStore("Seconday" , true);
               	byte[] secondery ;
               
               ByteArrayOutputStream secondOutputStream = new ByteArrayOutputStream();
               DataOutputStream secondOutputDataStream = new DataOutputStream(secondOutputStream);
               secondOutputDataStream.writeUTF(category.getString(category.getSelectedIndex())+";"+item.getString()+";"+units.getString()+";"+priority.getSelectedIndex());
               secondOutputDataStream.writeInt(Integer.parseInt(quantity.getString()));
               secondOutputDataStream.flush();
               secondery = secondOutputStream.toByteArray();
               seconderystore.addRecord(secondery , 0 , secondery.length);
               secondOutputStream.reset();
               secondOutputStream.close();
               secondOutputDataStream.close();          
			}//end else
            //byte[] input = details.getBytes();
            //mainstore.add
            //alert = new Alert("Not Error : " ,"created recordstore",null,AlertType.WARNING);
            display.setCurrent(alert);
         	}//end try
         	catch(Exception error){
            alert = new Alert("Error : " , error.toString(),null,AlertType.WARNING);
            display.setCurrent(alert);
         	}*/

	    }
	}
}
