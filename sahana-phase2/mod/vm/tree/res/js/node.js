/**
 * A class to describe a Node in a Tree
 */


/*
 * General Node properties that can change the look of the tree
 */

Node.border = '1px dotted #C0C0C0';     //the style of the horizontal and vertical tracing lines
Node.offset = 40;                       //the relative offset in (pixels) between parent and children nodes

/*
 * DOM node information
 */

Node.prototype.dom_node;        //this DOM node
Node.prototype.node_container;  //this DOM node's container that contains all DOM nodes
Node.prototype.h_bar;           //this Node's horizontal bar
Node.prototype.v_bar;           //this Node's vertical bar
Node.prototype.img;             //this node's image node
Node.prototype.text_node;       //this DOM node's text display item


/*
 * More info for this Node, its parent, its children, and its Tree
 */

Node.prototype.id;              //a unique identifier for this node in the tree
Node.prototype.parent_node;     //this node's parent
Node.prototype.tree_id;         //the id of the tree that this node is a part of
Node.prototype.tree_ref;        //a reference to the tree object that this node is a part of
Node.prototype.children;        //an array containing all children
Node.prototype.expanded;        //true if children are shown, false otherwise
Node.prototype.depth;           //the depth of this node (0 for root, 1 for root's children, etc.)


/**
 * Does the actual constructing of a Node object.
 *
 * @param display the text to display for the node
 * @param tree_id the ID of the tree that this node is a part of
 */

Node.prototype.constructNode = function(display, tree_id)
{
    //Set up the default values for a new Node

    this.children = Array();
    this.expanded = false;
    this.checked = false;
    this.tree_id = tree_id;
    this.tree_ref = Tree.getTree(tree_id);
    this.id = this.tree_ref.next_node_id;
    this.tree_ref.next_node_id += 1;

    //Create a 'DIV' tag to represent the node on the screen

    this.dom_node = document.createElement('div');
    this.dom_node.style.position = 'relative';
    this.dom_node.style.paddingTop = '5px';
    this.dom_node.style.paddingBottom = '5px';
    this.dom_node.style.left = Node.offset + 'px';

    if(this.tree_ref.ie)
        this.dom_node.style.display = 'block';
    else
        this.dom_node.style.display = 'table-cell';

    //Create the horizontal bar

    this.h_bar = document.createElement('div');
    this.h_bar.style.borderTop = Node.border;
    this.h_bar.style.display = 'block';
    this.h_bar.style.height = '1px';
    this.h_bar.style.width = Node.offset + 'px';
    this.h_bar.style.overflow = 'hidden';
    this.h_bar.style.position = 'absolute';
    this.h_bar.style.whiteSpace = 'pre';
    this.h_bar.style.fontFamily = 'arial';
    this.h_bar.style.fontSize = '10px';
    this.h_bar.style.top = '9px';
    this.h_bar.style.left = (-Node.offset + 5 ) + 'px';
    this.h_bar.appendChild(document.createTextNode('                                                    '));

    //Create the vertical bar

    this.v_bar = document.createElement('div');
    this.v_bar.style.margin = '0 0 0 0';
    this.v_bar.style.padding = '0 0 0 0';
    this.v_bar.style.position = 'absolute';
    this.v_bar.style.left = '5px';
    this.v_bar.style.top = '5px';
    this.v_bar.style.width = '1px';
    this.v_bar.style.display = 'none';                //assume hidden to begin with
    this.v_bar.style.borderLeft = Node.border;

    //Create the image

    this.img = document.createElement('img');
    this.img.setAttribute('src', this.tree_ref.img_dir + 'blank');
    this.img.style.position = 'relative';
    this.img.style.paddingRight = '10px';

    //Create the text node

    this.text_node = document.createElement('span');
    this.text_node.appendChild(document.createTextNode(display));

    //Add the image and the text in that order to the node container and
    //then add the node container to this node

    this.node_container = document.createElement('div');
    this.node_container.appendChild(this.h_bar);
    this.node_container.appendChild(this.v_bar);
    this.node_container.appendChild(this.img);
    this.node_container.appendChild(this.text_node);
    this.node_container.style.position = 'relative';
    this.dom_node.appendChild(this.node_container);

    //Add this node to the tree's list of nodes

    this.tree_ref.nodes[this.id] = this;
}

/**
 * Constructor for the Node class
 *
 * @param display the text to display for the node
 * @param tree_id the ID of the tree that this node is a part of
 */

function Node(display, tree_id)
{
    /*
     * First we must check to see if javascript is automatically calling
     * this constructor when we inherit this class. If so, we must return
     * because we want to call the constructor ourselves.
     */

    if(tree_id == null)
        return;

    //construct the Node

    this.constructNode(display, tree_id);
}

/**
 * Gets a Node object by its ID
 *
 * @param id        - the node id to look for
 * @param tree_id   - the tree's node to look within
 * @return the Node object
 */

Node.getNodeById = function(id, tree_id)
{
    return Tree.getTree(tree_id).nodes[id];
}

/**
 * Adds a child to this Node, also appending it to this Node's DOM node
 *
 * @param child     - the Node object to add
 * @return void
 */

Node.prototype.addChild = function(child)
{
    if(this.children.length == 0)
    {
        this.img.style.cursor = 'pointer';
        this.img.setAttribute('src', this.tree_ref.img_dir + 'plus');
        if(this.tree_ref.ie)
            eval("this.img.attachEvent('onclick', function(e) {var tmp = Tree.getTree('"+this.tree_id+"'); Node.toggleChildren('" + this.id + "', '" + this.tree_id + "', false); Node.repaint(tmp.root, tmp);});");
        else
            eval("this.img.addEventListener('click', function(e) {var tmp = Tree.getTree('"+this.tree_id+"'); Node.toggleChildren('" + this.id + "', '" + this.tree_id + "', false); Node.repaint(tmp.root, tmp);}, false);");
    }
    this.children[this.children.length] = child;
    this.dom_node.appendChild(child.dom_node);
    child.parent_node = this;
    child.depth = this.depth + 1;

    //make the child hidden by default

    child.dom_node.style.display = 'none';

}

/**
 * This function recursively hides the node passed to it as well as all
 * of its children nodes. It is intended for use as a helper function
 * for the Node.prototype.hide() function
 *
 * @param node  - the current node to recur on and hide
 * @return void
 */

Node.hideAux = function(node)
{
    for(var i = 0; i < node.children.length; i++)
    {
        Node.hideAux(node.children[i]);
    }

    node.dom_node.style.display = 'none';
}

/**
 * Hides all of this Node's children
 *
 * @return void
 */

Node.prototype.hide = function()
{
    for(var i = 0; i < this.children.length; i++)
    {
        Node.hideAux(this.children[i]);
    }
}

/**
 * This function recursively shows the node passed to it and all of its children, only if
 * a node is expanded. It is intended for use as a helper function for the Node.prototype.show()
 * function.
 *
 * @param node  - the node to hide
 * @return void
 */

Node.show = function(node)
{
    //show the current node

    if(node.tree_ref.ie)
        node.dom_node.style.display = 'block';
    else
        node.dom_node.style.display = 'table';

    //recur

    if(node.expanded)
    {
        for(var i = 0; i < node.children.length; i++)
        {
            Node.show(node.children[i]);
        }
    }
}

/**
 * Repaints all of the tracing lines of a node and all of its descendants, which really
 * only means resizing and showing or hiding only the vertical bar.
 *
 * @param node  - the node to begin repainting from
 * @param tree  - the tree that is being repainted
 * @return void
 */

Node.repaint = function(node, tree)
{
    if(node.expanded)
    {
        var last_y;

        for(var i = 0; i < node.children.length; i++)
        {
            Node.repaint(node.children[i], tree);
            if(i == (node.children.length - 1))
            {
                last_y = node.children[i].getY();
            }
        }

        node.v_bar.style.display = 'block';
        node.v_bar.style.height = ((last_y + 15) - (node.getY() + 10)) + 'px';
    }
    else
    {
        node.v_bar.style.display = 'none';
    }
}



/**
 * Shows all children of this Node
 *
 * @return void
 */

Node.prototype.show = function()
{
    for(var i = 0; i < this.children.length; i++)
    {
        Node.show(this.children[i]);
    }
}

/**
 * Toggles showing and hiding a node
 *
 * @param id        - the id of the parent node whose chlidren to hide
 * @param tree_id   - the id of the tree that this node belongs to
 * @param repaint	- true to repaint the tree's lines, false to hold off
 * @return void
  */

Node.toggleChildren = function(id, tree_id, repaint)
{
    var tree = Tree.getTree(tree_id);
    var node = Node.getNodeById(id, tree_id);
    if(node != false && tree != null)
    {
        if(node.children.length > 0)
        {
            for(var i = 0; i < node.children.length; i++)
            {
                if(node.expanded)
                    node.hide();
                else
                    node.show();
            }

            if(node.expanded)
                node.img.setAttribute('src', tree.img_dir + 'plus');
            else
                node.img.setAttribute('src', tree.img_dir + 'minus');

            node.expanded = !node.expanded;
        }
    }

	if(repaint)
	{
    	Node.repaint(tree.root, tree);
    }
}

/**
 * Expands all parents of this Node
 *
 * @return void
 */

Node.prototype.expandParents = function()
{
    var node = this.parent_node;
    while(node != null)
    {
        if(node.expanded != true)
        Node.toggleChildren(node.id, this.tree_id, true);

        node = node.parent_node;
    }
}

/**
 * Gets the x-value of the coordinates of this Node's dom node's position
 *
 * @return the x-value
 */

Node.prototype.getX = function()
{
    var node = this;
    var result = 0;
    while(node != null)
    {
        result += node.dom_node.offsetLeft;
        node = node.parent_node;
    }
    return result;
}

/**
 * Gets the y-value of the coordinates of this Node's dom node's position
 *
 * @return the y-value
 */

Node.prototype.getY = function()
{
    var node = this;
    var result = 0;
    while(node != null)
    {
        result += node.dom_node.offsetTop;
        node = node.parent_node;
    }
    return result;
}

