/*--------------------------------------------------|
| DynamicTable 1.0                                  |
|---------------------------------------------------|
| Copyright (c) 2005 Chamath Edirisuriya            |
|                    Upendra Haputantry             |
|                                                   |
| This script can be used freely as long as all     |
| copyright messages are intact.                    |
|                                                   |
| Updated: 18.02.2005                               |
|--------------------------------------------------*/

// object constructor
function DynamicTable(name, tblObj) {

   // define object's properties
   this.name = name;
   this.table = tblObj;
   this.labelId = 0;
   this.itemLabels = "|";
   this.columnArray = new Array();
   this.labelArray = new Array();
   this.ftype;
   this.fname;
   this.fclassName;
   this.fvalue;
   this.fsize;
   this.tclassName;
   this.tvalue;

   // attach object's methods
   this.setDataToColumnFormType = setDataToColumnFormType;
   this.setDataToColumnTextType = setDataToColumnTextType;
   this.setLabelRowId = setLabelRowId;
   this.isLabelExist = isLabelExist;
   this.addNewRow = addNewRow;
   this.removeRow = removeRow;
}

// define object's methods

function setDataToColumnFormType(id, type, name, className, value, size) {

   var e = document.createElement('input');
   e.setAttribute('type', type);
   e.setAttribute('name', name + this.table.rows.length);
   e.setAttribute('value', value);
   e.setAttribute('size', size);
   if (this.fclassName != '')
      e.className = className;

   this.columnArray[id] = e;
}

function setDataToColumnTextType(id, value, className) {

   var e = document.createTextNode(value);
   if (className != '')
      e.className = className;
   this.columnArray[id] = e;
}


function setLabelRowId(id) {
   this.labelId = id;

}

function isLabelExist(label) {
   return (this.itemLabels.indexOf("|" + label.toUpperCase() + "|") >  - 1);
}

function addNewRow() {

   var lastRow = this.table.rows.length;

   var iteration = lastRow;
   var row = this.table.insertRow(lastRow);
   row.setAttribute('id', 'dynamicRow' + iteration);
   for (var i = 0; i < this.columnArray.length; i++) {
      var cell = row.insertCell(i);
      cell.appendChild(this.columnArray[i]);
   }

   // remove button
   var cell = row.insertCell(this.columnArray.length);
   var e0 = document.createElement("div");
   e0.innerHTML = "<a href=\"javascript:" + this.name + ".removeRow('dynamicRow" + iteration +
      "')\"><img src='images/IcoDell.gif' border ='0'></a>";
   cell.appendChild(e0);

   // label data
   var lblData = this.columnArray[this.labelId].value.toUpperCase();
   this.labelArray[iteration] = lblData;
   this.itemLabels += lblData + "|";

}

function removeRow(objId) {

   var objRow = document.getElementById(objId);
   var id = objRow.rowIndex;

   myString = new String(this.itemLabels);
   if (myString.indexOf(this.labelArray[id]) !=  - 1) {
      this.itemLabels = myString.replace(this.labelArray[id], "*");
      for (var i = 0; i < this.labelArray.length; i++) {
         if (i > id) {
            this.labelArray[i - 1] = this.labelArray[i];
         }
      }
      this.labelArray.pop();
   }
   this.table.deleteRow(id);
}