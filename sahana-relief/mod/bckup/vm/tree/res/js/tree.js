/*
 * A class to define a Tree, which is simply a container of Nodes
 */

//Instance variables

Tree.prototype.id;                  //the id of this tree
Tree.prototype.next_node_id;        //the id for the next node in this tree
Tree.prototype.nodes;               //an array of nodes that make up this tree
Tree.prototype.root;                //a reference to the root node of this tree
Tree.prototype.img_dir;             //the directory where images are stored for this tree
Tree.prototype.ie;                  //true if the current browser is IE, false otherwise

//Static variables

Tree.next_tree_id = 0;              //the id for the next tree
Tree.trees = new Array();           //an array of all tree objects

/**
 * Constructs a Tree object
 *
 * @param dir the directory that contains the necessary images
 */

function Tree(dir)
{
    //set up important instance variables

    this.id = Tree.next_tree_id;
    Tree.trees[this.id] = this;
    Tree.next_tree_id += 1;
    this.next_node_id = 0;
    this.nodes = new Array();
    this.img_dir = dir;
    this.ie = navigator.appName.indexOf('Microsoft') != -1;
}

/**
 * Creates a root Node and appends it to the correct HTML tag. Also creates
 * two buttons to expand or collapse all nodes and appends them to that HTML tag
 * as well.
 *
 * @param root the root Node
 * @param append_id the id of the HTML tag to append the tree to
 */

Tree.prototype.setRoot = function(append_id, root)
{
    var dom_parent = document.getElementById(append_id);

    //first create and append the expand and collapse buttons

    var expand = document.createElement('input');
    expand.setAttribute('type', 'button');
    expand.setAttribute('value', 'Expand All');
    expand.style.marginRight = '5px';
    expand.style.marginBottom = '15px';
    expand.style.cursor = 'pointer';
    expand.style.backgroundColor = 'black';
    expand.style.color = 'white';
    expand.style.border = '1px solid #404040';

    if(this.ie)
        eval("expand.attachEvent('onclick', function(e) {var tmp = Tree.getTree('" + this.id + "'); Tree.expandAll(tmp.root, '" + this.id + "', true); Node.repaint(tmp.root, tmp);});");
    else
        eval("expand.addEventListener('click', function(e) {var tmp = Tree.getTree('" + this.id + "'); Tree.expandAll(tmp.root, '" + this.id + "', true); Node.repaint(tmp.root, tmp);}, false);");

    var collapse = document.createElement('input');
    collapse.setAttribute('type', 'button');
    collapse.setAttribute('value', 'Collapse All');
    collapse.style.cursor = 'pointer';
    collapse.style.marginBottom = '15px';
    collapse.style.backgroundColor = 'black';
    collapse.style.color = 'white';
    collapse.style.border = '1px solid #404040';

    if(this.ie)
        eval("collapse.attachEvent('onclick', function(e) {var tmp = Tree.getTree('" + this.id + "'); Tree.expandAll(tmp.root, '" + this.id + "', false); Node.repaint(tmp.root, tmp);});");
    else
        eval("collapse.addEventListener('click', function(e) {var tmp = Tree.getTree('" + this.id + "'); Tree.expandAll(tmp.root, '" + this.id + "', false); Node.repaint(tmp.root, tmp);}, false);");

    dom_parent.appendChild(expand);
    dom_parent.appendChild(collapse);

    //now set and append the root

    this.root = root;
    this.root.depth = 0;
    this.root.h_bar.style.border = '0 solid white';

    var actual_tree = document.createElement('div');
    actual_tree.style.display = 'block';
    actual_tree.appendChild(this.root.dom_node);
    dom_parent.appendChild(actual_tree);
}

/**
 * Returns a Tree object based on its id
 *
 * @param id the id of the tree to find
 */

Tree.getTree = function(id)
{
    return Tree.trees[id];
}

/**
 * Recursively expands or collapses a node and all of its children
 *
 * @param node      - the Node to begin from
 * @param tree_id   - the id of the Tree that node belongs to
 * @param expand    - true to expand, false to collapse
 * @return void
 */

Tree.expandAll = function(node, tree_id, expand)
{
    if(node.expanded != expand)
        Node.toggleChildren(node.id, tree_id, false);

    for(var i = 0; i < node.children.length; i++)
    {
        Tree.expandAll(node.children[i], tree_id, expand);
    }

}

/**
 * Traverses this tree and expands all parent Nodes of each CheckboxNode that is
 * checked.
 *
 * @param node	- the Node to begin traversing from
 * @return void
 */

Tree.prototype.expandParentsOfCheckedAux = function(node)
{
    if(node.checkboxNode != null)
    {
        if(node.checked == true)
            node.expandParents();
        node.checkParents();
    }

    for(var i = 0; i < node.children.length; i++)
    {
        this.expandParentsOfCheckedAux(node.children[i]);
    }
}

/**
 * Traverses this tree and expands all parent Nodes of each CheckboxNode that is
 * checked.
 *
 * @return void
 */

Tree.prototype.expandParentsOfChecked = function()
{
        this.expandParentsOfCheckedAux(this.root);
}

/**
 * Checks the integrity of the tree and marks all checkboxes if their CheckboxNode is
 * marked. Necessary for IE.
 *
 * @param node the node to begin traversing from
 * @return void
 */

Tree.checkTree = function(node)
{
    if(node.checkboxNode != null)
    {
        if(node.checked == true)
            node.box.checked = true;
    }

    for(var i = 0; i < node.children.length; i++)
    {
        Tree.checkTree(node.children[i]);
    }
}