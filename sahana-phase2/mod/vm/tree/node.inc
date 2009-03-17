<?php

/**
 * Defines a Node class, which make up a Tree. This class is intended
 * for use and display with the Tree and Node classes (and related subclasses) 
 * classes in javascript
 */
 
class Node
{
    /*
     * Instance Variables
     */
     
    public $parent;
    public $children;
    
    public $name;
    public $type;
    public $extra_info;
    public $depth;
    
    /**
     * Constructs a Node object.
     *
     * @param $name         the name of this node, which should be unique for all Nodes of this tree
     * @param $type         the type of javascript Node (Node, CheckboxNode, etc.)
     * @param $extra_info   any extra information to be associated with this Node
     */
    
    function __construct($name, $type='', $extra_info=array())
    {
        $this->parent = null;
        $this->children = array();
        
        $this->name = $name;
        
        if(strcasecmp($type, 'CheckboxNode') == 0)
            $this->type = 'CheckboxNode';
        else
            $this->type = 'Node';
            
        $this->extra_info = $extra_info;
        $this->depth = 0;
    }
    
    /**
     * Adds a child to this node
     *
     * @param $child    a reference to the child Node to add
     */
     
    function addChild($child)
    {
        $this->children[] = &$child;
        $child->parent = &$this;
        $child->depth = $this->depth + 1;
    }
}