<?php
/**
 * Lib rs javascript
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/**
 * This function contain a javascript that submits the content of mod_select. this is called by the function _show_mod_select_form() in sample.inc
 * @access public
 * @return void
 */
function shn_sample_change_form_js()
{
?>
<script type="text/javascript">
    function changeform()
    {
    var x=document.mod_select.mod_name.options[document.mod_select.mod_name.selectedIndex].value;
    if(x!='none')
        {
        document.mod_select.submit();
        }
    }
</script>
<?php
}

/**
 * This function contain a javascript that submits the content of sample_rep_form. this is called by the function shn_rs_sample_report() in sample.inc
 * @access public
 * @return void
 */
function shn_sample_change_action_js()
{
?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.sample_rep_form.submit();
         return;
    }
</script>
<?php
}

/**
 * This function contain a javascript that submits the content of sample_rep_form. this is called by the function shn_rs_search_type_select() in 	search.inc
 * @access public
 * @return void
 */
function shn_rs_search_cat_js()
{
?>
<script type="text/javascript">
    function changeform()
    {
 var x=document.rep_search.search_rep_chart.options[document.rep_search.search_rep_chart.selectedIndex].value;
	
  if(x!='none')
        {
        document.rep_search.submit();
        }
    }
</script>
<?php
}
//Dynamic reports javascript functions

function _shn_rs_dnd_table(){
?>
<script>
	dojo.require("dojo.event.*");
dojo.require("dojo.dnd.*");



// submitting form with filled $_POST['table']
function dropTable(){
	document.myForm.table.value = checkContainer("kontener2", 1);
	document.myForm.submit();
}


// submitting form with filled $_POST['fields']
function submitFields(){
	document.myForm.fields.value = checkContainer("kontener4", 10);
	document.myForm.submit();

}




function initDnd() {
// variable needed to get back to ogiginal background color in all themes
	var bgCol;
	dojo.declare("dojo.dnd.DestDropElem",dojo.dnd.HtmlDropTarget,{
		onDragOver: function(e) {
			// domNode is the drop target we're over
			bgCol = this.domNode.style.backgroundColor;
			this.domNode.style.backgroundColor = "#dedede";
			return dojo.dnd.HtmlDropTarget.prototype.onDragOver.apply(this, arguments);
		},
		onDragOut: function(e) {
			// this.domNode is the drop target we're leaving
			this.domNode.style.backgroundColor = bgCol;
			return dojo.dnd.HtmlDropTarget.prototype.onDragOut.apply(this, arguments);
		},
		onDropEnd: function(e) {
			if(dojo.byId("kontener1"))
				dropTable();
      // Call the superclass method to do the actual dropping
      return dojo.dnd.HtmlDropTarget.prototype.onDrop.apply(this, arguments);
		}
	});

	dojo.declare("dojo.dnd.DestDropBack",dojo.dnd.HtmlDropTarget,{
		onDragOver: function(e) {
			// domNode is the drop target we're over
			bgCol = this.domNode.style.backgroundColor;
			this.domNode.style.backgroundColor = "#dedede";
			return dojo.dnd.HtmlDropTarget.prototype.onDragOver.apply(this, arguments);
		},
		onDragOut: function(e) {
			// this.domNode is the drop target we're leaving
			this.domNode.style.backgroundColor = bgCol;
			return dojo.dnd.HtmlDropTarget.prototype.onDragOut.apply(this, arguments);
		}
	});

//make those containers a valid drop targets if they exist:
	var dt1 = dojo.byId("kontener1")?(new dojo.dnd.DestDropBack(dojo.byId("kontener1"), ["li1"])):null;
	var dt2 = dojo.byId("kontener2")?(new dojo.dnd.DestDropElem(dojo.byId("kontener2"), ["li1"])):null;
	var dt3 = dojo.byId("kontener3")?(new dojo.dnd.DestDropBack(dojo.byId("kontener3"), ["li2"])):null;
	var dt4 = dojo.byId("kontener4")?(new dojo.dnd.DestDropElem(dojo.byId("kontener4"), ["li2"])):null;

//creates drag sources enclosed in "kontener1", they will be marked by dojo as "li1"
	dragSources("kontener1", 1);

//creates drag sources enclosed in "kontener3", they will be marked by dojo as "li2"
	dragSources("kontener3", 2);
}


dojo.addOnLoad(initDnd);
</script>
<?php
}
function _shn_rs_lib_dnd(){
?>
<script>
// create drag sources from all li tags enclosed in cont
// cont - container name (html tag id)
// num - extention for HtmlDropTarget idenitier (here will be e.g. "li1"="li"+1)
function dragSources(cont, num){
	if(dojo.byId(cont)){
		var dl = dojo.byId(cont);	
		var lis = dl.getElementsByTagName("li");
		for(x=0; x<lis.length; x++)
			new dojo.dnd.HtmlDragSource(lis[x], "li"+num);
	}
}



// checks for li tags in container (cont variable), max is maximum elements
function checkContainer(cont, max){
	dl = dojo.byId(cont)?dojo.byId(cont):null;
	if (dl != null){
		lis = dl.getElementsByTagName("li");
		var arr = new Array();
		if(lis.length < max)
			max = lis.length
		for(x=0; x<max; x++)
			arr[x] = lis[x].id;
	}
	return arr = arr?arr:null;
}
</script>
<?php
}
function _shn_rs_dnd_multiple_table(){
?>
<script>
dojo.require("dojo.event.*");
dojo.require("dojo.dnd.*");


function dropTable(){
	document.myForm.table.value = checkContainer("kontener2", 5);
	document.myForm.fields.value = checkContainer("kontener4", 15);
	document.myForm.submit();
}


function submitFields(){	
	document.myForm.table.value = checkContainer("kontener2", 5);
	document.myForm.fields.value = checkContainer("kontener4", 15);
	document.myForm.crt.value = "true";
	document.myForm.submit();	
}


function dropBackTable(){
	var tables = checkContainer("kontener2", 5);
	var fields1 = checkContainer("kontener4", 15);
	var arr;
	var i = 0;
	var tab = tables.join(",");
	var fields2 = new Array();
	for(x=0; x<fields1.length; x++){
		arr = fields1[x].split(".");
		if(tab.match(arr[0]))
			fields2[i++] = fields1[x];
	}
	document.myForm.table.value = tables;
	document.myForm.fields.value = fields2;
	document.myForm.submit();
}



function initDnd() {
// variable needed to get back to ogiginal background color in all themes
	var bgCol;
	dojo.declare("dojo.DestDropTargetGo",dojo.dnd.HtmlDropTarget,{
		onDragOver: function(e) {
			// domNode is the drop target we're over
			bgCol = this.domNode.style.backgroundColor;
			this.domNode.style.backgroundColor = "#dedede";
			return dojo.dnd.HtmlDropTarget.prototype.onDragOver.apply(this, arguments);
		},
		onDragOut: function(e) {
			// this.domNode is the drop target we're leaving
			this.domNode.style.backgroundColor = bgCol;
			return dojo.dnd.HtmlDropTarget.prototype.onDragOut.apply(this, arguments);
		},
		onDropEnd: function(e) {
			dropTable();
      // Call the superclass method to do the actual dropping
      return dojo.dnd.HtmlDropTarget.prototype.onDropEnd.apply(this, arguments);
		}
	});

	dojo.declare("dojo.DestDropTargetBack",dojo.dnd.HtmlDropTarget,{
		onDragOver: function(e) {
			// domNode is the drop target we're over
			bgCol = this.domNode.style.backgroundColor;
			this.domNode.style.backgroundColor = "#dedede";
			return dojo.dnd.HtmlDropTarget.prototype.onDragOver.apply(this, arguments);
		},
		onDragOut: function(e) {
			// this.domNode is the drop target we're leaving
			this.domNode.style.backgroundColor = bgCol;
			return dojo.dnd.HtmlDropTarget.prototype.onDragOut.apply(this, arguments);
		},
		onDropEnd: function(e) {
			dropBackTable();
      // Call the superclass method to do the actual dropping
      return dojo.dnd.HtmlDropTarget.prototype.onDropEnd.apply(this, arguments);
		}
	});

	dojo.declare("dojo.dnd.DestDropBack",dojo.dnd.HtmlDropTarget,{
		onDragOver: function(e) {
			// domNode is the drop target we're over
			bgCol = this.domNode.style.backgroundColor;
			this.domNode.style.backgroundColor = "#dedede";
			return dojo.dnd.HtmlDropTarget.prototype.onDragOver.apply(this, arguments);
		},
		onDragOut: function(e) {
			// this.domNode is the drop target we're leaving
			this.domNode.style.backgroundColor = bgCol;
			return dojo.dnd.HtmlDropTarget.prototype.onDragOut.apply(this, arguments);
		}
	});

	var dt1 = dojo.byId("kontener1")?(new dojo.DestDropTargetBack(dojo.byId("kontener1"), ["li1"])):null;
	var dt2 = dojo.byId("kontener2")?(new dojo.DestDropTargetGo(dojo.byId("kontener2"), ["li1"])):null;
	var dt3 = dojo.byId("kontener3")?(new dojo.DestDropTargetGo(dojo.byId("kontener3"), ["li2"])):null;
	var dt4 = dojo.byId("kontener4")?(new dojo.dnd.DestDropBack(dojo.byId("kontener4"), ["li2"])):null;

//creates drag sources enclosed in first variable, they will be marked by dojo as "li"+second variable
	dragSources("kontener1", 1);
	dragSources("kontener2", 1);
	dragSources("kontener3", 2);
	dragSources("kontener4", 2);

}

dojo.addOnLoad(initDnd);
</script>
<?php
}
