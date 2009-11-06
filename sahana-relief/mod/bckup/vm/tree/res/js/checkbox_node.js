/**
 * This class defines a Node within a tree with a checkbox
 */

CheckboxNode.prototype = new Node;      //inherit all attributes and methods from the Node class
CheckboxNode.prototype.box;             //this node's checkbox node
CheckboxNode.prototype.checked;         //whether or not this node has been checked
CheckboxNode.prototype.checkboxNode;    //a value to tell whether this Node is a CheckboxNode or not
                                        //if this value is null, it is not a CheckBoxNode

/**
 * Does the actual work for constructing a Node object with a checkbox.
 *
 * @param display   -the text to display for the node
 * @param name      - the name of the checkbox
 * @param tree_id   - the ID of the tree that this node is a part of
 * @param is_checked	- true if the node is initially checked, false otherwise
 */

CheckboxNode.prototype.constructCheckboxNode = function(display, name, tree_id, is_checked)
{
    //first construct a Node

    this.constructNode(display, tree_id);

    //now create a checkbox

    this.box = document.createElement('input');
    this.box.setAttribute('type', 'checkbox');

    if(name == null)
        this.box.setAttribute('name', "tree" + this.tree_id + "_node" + this.id);
    else
        this.box.setAttribute('name', name);

    this.box.setAttribute('value', 'on');
    this.box.style.marginRight = '10px';

    if(this.tree_ref.ie)
    {
        eval("this.box.attachEvent('onclick', function(e) {CheckboxNode.updateChecks(" + this.id + ", " + this.tree_id + ");});");
        eval("this.text_node.attachEvent('onclick', function(e) {CheckboxNode.updateChecks(" + this.id + ", " + this.tree_id + ");});");
    }
    else
    {
        eval("this.box.addEventListener('click', function(e) {CheckboxNode.updateChecks(" + this.id + ", " + this.tree_id + ");}, false);");
        eval("this.text_node.addEventListener('click', function(e) {CheckboxNode.updateChecks(" + this.id + ", " + this.tree_id + ");}, false);");
    }

	this.text_node.style.cursor = 'pointer';
	this.checkboxNode = 'yes';
    this.mark(is_checked);

    //add the checkbox to this DOM node's node container and check it if necessary

    this.node_container.insertBefore(this.box, this.text_node);
}

/**
 * Constructs a CheckboxNode object, which is a Node with a checkbox.
 *
 * @param display   - the text to display for the node
 * @param name      - the name of the checkbox
 * @param tree_id   - the ID of the tree that this node is a part of
 * @param is_checked	- true if the node is initially checked, false otherwise
 */

function CheckboxNode(display, name, tree_id, is_checked)
{
    this.constructCheckboxNode(display, name, tree_id, is_checked);
}

/**
 * Marks this CheckboxNode to be checked or unchecked.
 *
 * @param checked - true to check it, false otherwise
 * @return void
 */

CheckboxNode.prototype.mark = function(checked)
{
    //mark the CheckboxNode only if it's a CheckboxNode

    if(this.checkboxNode == null)
        return;

    this.checked = checked;
    this.box.checked = checked;
}

/**
 * Marks this CheckboxNode and all of its children to be checked or unchecked
 *
 * @param checked   - true to check all children, false to uncheck all children
 * @return void
 */

CheckboxNode.prototype.markSubTree = function(checked)
{
    for(var i = 0; i < this.children.length; i++)
    {
        if(this.children[i].checkboxNode != null)
            this.children[i].markSubTree(checked);
    }

    this.mark(checked);
}

/**
 * Unchecks all parent checkmarks of this CheckboxNode
 *
 * @return void
 */

CheckboxNode.prototype.uncheckParents = function()
{
    var node = this.parent_node;
    while(node != null && node.checkboxNode != null)
    {
        node.mark(false);
        node = node.parent_node;
    }
}

/**
 * Checks to see if all children of this CheckboxNode are checked.
 *
 * @return true if all children are checked, false if not.
 *         note: - if this node has no children, true is returned
 *               - false may be returned if this node is not a CheckboxNode
 */

CheckboxNode.prototype.allChildrenChecked = function()
{
    if(this.checkboxNode == null)
        return false;

    for(var i = 0; i < this.children.length; i++)
    {
        if(this.children[i].checkboxNode != null)
        {
            if(!this.children[i].checked)
                return false;
        }
    }
    return true;
}

/**
 * Checks all parent checkmarks of this CheckboxNode only if all children are checked
 *
 * @return void
 */

CheckboxNode.prototype.checkParents = function()
{
    var node = this.parent_node;

    while(node != null)
    {
        if(node.checkboxNode == null)
            return;

        if(node.allChildrenChecked())
            node.mark(true);
        else
            return;

        node = node.parent_node;
    }
}

/**
 * If checked:
 *       - unmarks the check
 *       - unmarks all child checkmarks
 *       - unmarks any parent checkmarks if checked
 * If unchecked:
 *       - marks the check
 *       - marks all child checkmarks
 *       - marks any parent checkmarks if all of its children are checked
 *
 * @param id        - the id of the node to perform this on
 * @param tree_id   - the id of the tree that this node is a part of
 * @return void
 */

CheckboxNode.updateChecks = function(id, tree_id)
{
    var tree = Tree.getTree(tree_id);
    var node = Node.getNodeById(id, tree_id);
    if(node != false && tree != null)
    {
        node.markSubTree(!node.checked);

        if(!node.checked)
            node.uncheckParents();
        else
            node.checkParents();
    }
}
