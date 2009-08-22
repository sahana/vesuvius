<?php
/**
 * Defines a Tree class for use and display with the Tree and Node
 * classes (and related subclasses) in javascript
 */

/*
 * Define some global variables
 */

global $tree_next_id;
$tree_next_id = 0;              //the ID of the next tree to display

class Tree
{

    /*
     * Declare instance variables
     */

    public $res_dir;    //the directory where all resources for the javascript classes are stored
    public $root;       //a reference to the root of this tree

    /**
     * Constructs a Tree object.
     *
     * @param $node_type    the types of nodes in this tree (Node, CheckboxNode, etc.)
     */

    public function __construct($res_dir)
    {
        $this->res_dir = $res_dir;
    }

    /**
     * Sets the root of this tree
     *
     * @param $root     the root of the tree
     */

    public function setRoot($root)
    {
        $this->root = $root;
    }

    /**
     * A helper function for display(), this function recursively displays a Node and
     * all of its children Nodes in a very plain manner
     *
     * @param $node     the Node to begin displaying from
     */

    private function displayPlainAux($node)
    {
        for($i = 0; $i < $node->depth; $i++)
            echo "     ";
        echo $node->name."<br />";

        foreach($node->children as $child)
        {
            if($child != null)
                $this->displayPlainAux($child);
        }
    }

    /**
     * A helper function for display(), this function recursively displays a Node and
     * all of its children Nodes using javascript
     *
     * @param $node     the Node to begin displaying from
     */

    private function displayJavascriptAux($node)
    {
        $nl = "\r\n";

        $depth = $node->depth;
        $name = $node->name;

        if($node->type == 'CheckboxNode')
        {
        	$checked = (isset($node->extra_info['checked']) && ($node->extra_info['checked'] == true))?'true':'false';
            echo "var tmp{$depth} = new CheckboxNode('{$name}', {$node->extra_info['input_name']}, tree_tmp.id, $checked);".$nl;
        }
        else
            echo "var tmp{$depth} = new Node('{$name}', tree_tmp.id);".$nl;

        if($depth > 0)
            echo "tmp".($depth - 1).".addChild(tmp{$depth});".$nl;

        foreach($node->children as $child)
        {
            if($child != null)
                $this->displayJavascriptAux($child);
        }
    }

    /**
     * Displays this Tree
     *
     * @param $js_before    javascript code to add before displaying the tree
     * @param $js_after     javascript code to add after displaying the tree
     * @return void
     */

    public function display($js_before='', $js_after='')
    {
        $nl = "\r\n";

        if(count($this->root->children) != 0)
        {
	        global $tree_next_id;

	        echo '<div id="tree'.$tree_next_id.'">'.$nl;
	        echo '<script type="text/javascript">'.$nl;

	        echo $js_before;
	        echo "var tree_tmp = new Tree('".TREE_IMAGE_PATH."');".$nl;

	        $this->displayJavascriptAux($this->root);
	        echo "tree_tmp.setRoot('tree{$tree_next_id}', tmp0);".$nl;
	        echo $js_after;

	        echo "</script>".$nl;
	        echo "</div>".$nl;

	        $tree_next_id++;
        }
        else
        {
        	echo "(Empty)<br />";
        }
    }

    /**
     * A helper function for findNode(), this function recursively searches for
     * a Node starting from the Node given to it
     *
     * @param $node     the Node to begin searching from
     * @param $name     the name of the Node to look for
     * @return the Node if found, null if not found
     */

    public function findNodeAux($node, $name)
    {
        if(strcasecmp($node->name, $name) == 0)
            return $node;

        foreach($node->children as $child)
        {
            if($child != null)
            {
                $result = $this->findNodeAux($child, $name);

                if($result != null)
                    return $result;
            }
        }

        return null;
    }

    /**
     * Finds a Node based on its name
     *
     * @param $name     the name of the Node to find
     * @return the Node if found, null if not found
     */

    public function findNode($name)
    {
        return $this->findNodeAux($this->root, $name);
    }
}
/**
 * shn_shn_text_vm_display_js()
 * This lets us use Sahana's 'stream' functionality to output our javascript without requiring the
 * 'mod' directory be web-accessible.
 * Sahana automatically calls this, according to the shn_[stream]_[mod]_[act]() naming convention.
 */
function shn_text_vm_display_js() {
	$file = TREE_DIR.'res/js/'.$_GET['js'];
	if(file_exists($file)) {
		header('Content-Type: application/x-javascript');
		readfile($file);
	} else {
		die('404 not found');
	}
}
/**
 * shn_image_vm_tree_image()
 * This lets us use Sahana's 'stream' functionality to display the tree images without requiring the
 * 'mod' directory be web-accessible.
 * Sahana automatically calls this, according to the shn_[stream]_[mod]_[act]() naming convention.
 */
function shn_image_vm_tree_image() {
	header('Content-Type: image/png');
	switch($_GET['img']) {
		case 'plus':
			$file = 'plus.png';
		break;
		case 'minus':
			$file = 'minus.png';
		break;
		default:
			$file = 'blank.png';
	}
	readfile(TREE_DIR.'res/img/' . $file);
}


