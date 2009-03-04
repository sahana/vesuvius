<?php

/**
 * Social Network Administrative Section
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    shana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * sn
 * @access public
 * @return void
 * 
 */

include_once $global['approot'].'mod/sn/admin_home.inc';

//admin nome page
function shn_sn_ad_default(){
    
   echo "<h2><center>"._t("Social Network Administrative Section")."</center></h2>";
   echo "<br>";
   shn_sn_ad_adminmenu();
   echo "<br>";
   shn_sn_ad_home();
   
}

//admin main menu
function shn_sn_ad_adminmenu() {
 
    global $global;
    $module = $global['module'];
    // Create the module menuj
    shn_tabmenu_open(_t());
    
    shn_tabmenu_item("ad_manage_groups", _t("Groups"));
    shn_tabmenu_item("ad_manage_roles", _t("Roles"));
    //shn_tabmenu_item("ad_manage_users", _t("User Management"));
    shn_tabmenu_item("ad_manage_forums", _t("Forums"));
        
    shn_tabmenu_close();
}

//main manu for group
function shn_sn_ad_groups_adminmenu(){
    shn_tabmenu_open(_t());
    
    shn_tabmenu_item("ad_default", _t("Administrator Home"));
    shn_tabmenu_item("ad_view_category", _t("View Category"));
    shn_tabmenu_item("ad_create_category", _t("Create New Category"));
    shn_tabmenu_item("ad_edit_category", _t("Edit Category"));
    shn_tabmenu_item("ad_delete_category", _t("Delete Category"));
    shn_tabmenu_item("ad_view_groups_info", _t("View Groups information"));
    shn_tabmenu_item("ad_create_groups", _t("Create New Groups"));
    shn_tabmenu_item("ad_edit_groups_info", _t("Edit Groups Information"));
    shn_tabmenu_item("ad_delete_groups", _t("Delete Groups"));
    shn_tabmenu_item("ad_view_users_groups_request", _t("View Users Groups Request"));
    shn_tabmenu_item("ad_add_group_note", _t("Add/Delete Notices to Groups"));
            
    shn_tabmenu_close();
}

//manage groups manu & page
function shn_sn_ad_manage_groups(){
    
    echo "<h2><center>"._t("Manage Groups of Social Network")."</center></h2>";
    echo "<br>";
    shn_sn_ad_groups_adminmenu();
    
    echo "<br>";
    echo "<h4>"._t("Features Include in admin/group admin")."</h4>";
    echo "<ul>";
    echo "<li>"._t("Make groups based on decease condition or disaster insidents")."</li>";
    echo "<li>"._t("View groups information")."</li>";
    echo "<li>"._t("Edit groups information")."</li>";
    echo "<li>"._t("Delete groups")."</li>";
    echo "<li>"._t("Add user to groups")."</li>";
    echo "<li>"._t("Delete users form group")."</li>";
    echo "<li>"._t("Add notices to groups")."</li>";
    echo "<li>"._t("Delete notices from groups")."</li>"; 
    echo "</ul>";
    
}

//main menu for roles mamagement
function shn_sn_ad_roles_adminmenu(){
    shn_tabmenu_open(_t());
    
    shn_tabmenu_item("ad_default", _t("administrator Home"));
    shn_tabmenu_item("ad_view_roles_info", _t("View Roles information"));
    shn_tabmenu_item("ad_search_people_module", _t("Assing / Re-Assing Roles to Social Network Users"));
    shn_tabmenu_item("ad_search_people_forum", _t("Assing / Re-Assing Roles to Forum Users"));
    shn_tabmenu_item("ad_search_people_group", _t("Assing / Re-Assing Roles to Group Users"));
    //shn_tabmenu_item("ad_approove_req", _t("View Users Roles Request"));
                
    shn_tabmenu_close();
    
}

//manage roles menu and page
function shn_sn_ad_manage_roles(){
    
    echo "<h2><center>"._t("Manage Roles of Social Network")."</center></h2>";
    echo "<br>";
    shn_sn_ad_roles_adminmenu();
    
    echo "<br>";
    echo "<h4>"._t("Features Include in admin/SN admin")."</h4>";
    echo "<ul>";
    echo "<li>"._t("Make New Roles")."</li>";
    echo "<li>"._t("View roles information")."</li>";
    echo "<li>"._t("Assing roles to users")."</li>";
    echo "<li>"._t("Edit rolse information")."</li>";
    echo "<li>"._t("Assing roles to users")."</li>";
    echo "<li>"._t("Ressing rolse from users")."</li>";
    echo "<li>"._t("View users request")."</li>"; 
    echo "</ul>";
    
}

//main menu for user mamagement
function shn_sn_ad_manage_users_adminmenu(){
    shn_tabmenu_open(_t());
    
    shn_tabmenu_item("ad_default", _t("administrator Home"));
    shn_tabmenu_item("ad_view_users_profile", _t("View/Delete Users Profile"));
    shn_tabmenu_item("ad_add_notices_to_users", _t("Add Notices to Users"));
                    
    shn_tabmenu_close();
    
}

//manage users menu and page
function shn_sn_ad_manage_users(){
    
    echo "<h2><center>"._t("Manage Users of Social Network")."</center></h2>";
    echo "<br>";
    shn_sn_ad_manage_users_adminmenu();
    
    echo "<br>";
    echo "<h4>"._t("Features Include in admin/SN admin")."</h4>";
    echo "<ul>";
    echo "<li>"._t("View/Delete users profile")."</li>";
    echo "<li>"._t("Add Notices to User")."</li>"; 
    echo "</ul>";
    
}

//main menu for forum
function shn_sn_ad_manage_forums_adminmenu(){
    shn_tabmenu_open(_t());
    
    shn_tabmenu_item("ad_default", _t("administrator Home"));
    shn_tabmenu_item("ad_view_current_forums", _t("View Current Forums"));
    shn_tabmenu_item("ad_create_new_forums", _t("Create New Forums"));
    shn_tabmenu_item("ad_edit_forums", _t("Edit Forums"));
    shn_tabmenu_item("ad_delete_forums", _t("Delete Forums"));
    shn_tabmenu_item("ad_post_to_forum", _t("Post by admin/Delete Users Post"));
    shn_tabmenu_item("ad_add_forum_note", _t("Add/Delete Notices"));
  
    shn_tabmenu_close();
    
}

//manage roles menu and page
function shn_sn_ad_manage_forums(){
    
    echo "<h2><center>"._t("Manage forums of Social Network")."</center></h2>";
    echo "<br>";
    shn_sn_ad_manage_forums_adminmenu();
    
    echo "<br>";
    echo "<h4>"._t("Features Include in admin/SN admin")."</h4>";
    echo "<ul>";
    echo "<li>"._t("View current forums")."</li>";
    echo "<li>"._t("Create new forums")."</li>";
    echo "<li>"._t("Edit forums")."</li>";
    echo "<li>"._t("Add notices")."</li>";
    echo "<li>"._t("Delete notices")."</li>";
    echo "<li>"._t("Post by admin")."</li>";
    echo "<li>"._t("Delete users post")."</li>"; 
    echo "</ul>";
    
}

//..................................Groups management.......................................................

//view categoty
function shn_sn_ad_view_category(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("View Category Types of Social Network")."</center></h2>";

    shn_form_fopen('ad_create_category_cr','sn',$form_opts);
    shn_form_hidden(array('category_id'=>$category_id));

    shn_form_fsopen(_t("Available Category Types")); ?>
    <div class="info"><?= _t("These are the available category types ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_category";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    $note_query = "SELECT category_id,category_name,parent_id,level FROM sn_category";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("Category")."</th> <th>"._t("Category Type")."</th> <th>"._t("Immediate Parent")."</th></tr>";
    while($row=$rs->FetchRow()){
        $category_id = $row["category_id"];
        $category_name = $row["category_name"];
        $parent_id = $row["parent_id"];
        $level = $row["level"];
        echo "<tr>";
        
        if($level=="0"){
            echo "<td>".$category_name."</td>";
            echo "<td>"._t("Main Category")."</td>";
            echo "<td>"._t("No Perant")."</td>";
        }else{
            echo "<td>".$category_name."</td>";
            echo "<td>"._t("Sub Category")."</td>";
           
             $query = "SELECT category_name FROM sn_category WHERE category_id=?";
             $res = $db->Execute($query,array($parent_id));
             $parent_category_name=$res->fields["category_name"];
              echo "<td>".$parent_category_name."</td>";
        }   
        
        echo "</tr>";
       
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_view_category','First',$stream=null,$params=array('category_id'=>$category_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_category','&lt',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_category',($i+1),$stream=null,$params=array('category_id'=>$category_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_category','&gt',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_category','Last',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}
    


//function for create new catrgory
function shn_sn_ad_create_category(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Create Category Types for Social Network")."</center></h2>";

    shn_form_fopen('ad_create_category_cr','sn',$form_opts);
    shn_form_hidden(array('category_id'=>$category_id));

    shn_form_fsopen(_t("Available Category Types")); ?>
    <div class="info"><?= _t("These are the available category types ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_category";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=5;

    $note_query = "SELECT category_id,category_name,parent_id,level FROM sn_category";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("Category")."</th> <th>"._t("Category Type")."</th> <th>"._t("Immediate Parent")."</th></tr>";
    while($row=$rs->FetchRow()){
        $category_id = $row["category_id"];
        $category_name = $row["category_name"];
        $parent_id = $row["parent_id"];
        $level = $row["level"];
        echo "<tr>";
        
        if($level=="0"){
            echo "<td>".$category_name."</td>";
            echo "<td>"._t("Main Category")."</td>";
            echo "<td>"._t("No Perant")."</td>";
        }else{
            echo "<td>".$category_name."</td>";
            echo "<td>"._t("Sub Category")."</td>";
           
             $query = "SELECT category_name FROM sn_category WHERE category_id=?";
             $res = $db->Execute($query,array($parent_id));
             $parent_category_name=$res->fields["category_name"];
              echo "<td>".$parent_category_name."</td>";
        }   
        
        echo "</tr>";
       
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_create_category','First',$stream=null,$params=array('category_id'=>$category_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_category','&lt',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_category',($i+1),$stream=null,$params=array('category_id'=>$category_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_category','&gt',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_category','Last',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();

    shn_form_fsopen(_t("Information for New Category"));
    
    $options = array('sub'=>_t('Sub Category'),'main'=>_t('Main Category'));
    shn_form_select($options,_t("Category Type"),'sn_category_type','onchange="hide_category(options[selectedIndex].value,\'category_div\')"','');
    
    ?> <div id="category_div"> <?php 
    $stored_group = _shn_sn_get_stored_category();
    shn_form_multi_select('sn_available_category', $stored_group,'Available Category','','length=100%');
    ?> </div> <?php 
    
    shn_form_text(_t('Category Name'),'sn_category_name','');
   
    shn_form_fsclose();
    
    shn_form_submit(_t("Create Category"),'name="create_category"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups','Group admin Panel',$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    ?>
 <script type="text/javascript">

      function hide_category(value,div_id){
               
           if(value=='main'){
                document.getElementById("category_div").style.visibility = "hidden";
      
           } else{
                
                document.getElementById("category_div").style.visibility = "visible";
           }     
       }        
          
</script>

<?php 
    
}

//create new category
function shn_sn_ad_create_category_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $sn_category_type = $_REQUEST["sn_category_type"];
     $sn_available_category = $_REQUEST["sn_available_category"];
     $sn_category_name = $_REQUEST["sn_category_name"];
     
     $query = "SELECT level FROM sn_category WHERE category_id=?";
     $res = $db->Execute($query,array($sn_available_category));
     $level = $res->fields["level"];
     
     $category_id = shn_create_uuid('sn_category');
     
   if(isset($_REQUEST['create_category'])){
        if( $sn_category_type=="main"){
            
            $errors = array();
            if($_REQUEST["sn_category_name"]==null){
                add_error(_t("Please fill category name"));
                unset($_POST);
                shn_sn_ad_create_category();
            }
            else{
                $sql = "INSERT INTO sn_category(category_id,category_name,level) VALUES (?,?,?)";
                $res = $db->Execute($sql,array($category_id,$sn_category_name,'0'));
                shn_sn_ad_view_category();
            }
        }
        if( $sn_category_type=="sub"){
            
            $errors = array();
            if($_REQUEST["sn_category_name"]==null OR $_REQUEST["sn_available_category"]==null){
                add_error(_t("Please fill category name & available category"));
                 unset($_POST);
                 shn_sn_ad_create_category();
            }
            else{
            
                foreach($sn_available_category as $parent_id){
                $sql = "INSERT INTO sn_category(category_id,category_name,parent_id,level) VALUES (?,?,?,?)";
                $res = $db->Execute($sql,array($category_id,$sn_category_name,$parent_id,$level+1));
                }
                 shn_sn_ad_view_category();
            }
        }
    }
    else{
        shn_sn_ad_manage_groups();
    }    
}

//edit categoty information
function shn_sn_ad_edit_category(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Edit Category Types of Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('category_id'=>$category_id));

    shn_form_fsopen(_t("Available Category Types")); ?>
    <div class="info"><?= _t("These are the available category types ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_category";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    $note_query = "SELECT category_id,category_name,parent_id,level FROM sn_category";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("Category")."</th> <th>"._t("Category Type")."</th> <th>"._t("Immediate Parent")."</th> <th></th></tr>";
    while($row=$rs->FetchRow()){
        $category_id = $row["category_id"];
        $category_name = $row["category_name"];
        $parent_id = $row["parent_id"];
        $level = $row["level"];
        echo "<tr>";
        
        if($level=="0"){
            echo "<td>".$category_name."</td>";
            echo "<td>"._t("Main Category")."</td>";
            echo "<td>"._t("No Perant")."</td>";
            echo "<td>";
            shn_acl_secure_hyperlink('sn','ad_edit_category_confirm',_t('Edit'),$stream=null,$params=array('category_id'=>$category_id),$text_opts='');
            echo "</td>";
        
        }else{
            echo "<td>".$category_name."</td>";
            echo "<td>"._t("Sub Category")."</td>";
           
             $query = "SELECT category_name FROM sn_category WHERE category_id=?";
             $res = $db->Execute($query,array($parent_id));
             $parent_category_name=$res->fields["category_name"];
             echo "<td>".$parent_category_name."</td>";
             echo "<td>";
             shn_acl_secure_hyperlink('sn','ad_edit_category_confirm',_t('Edit'),$stream=null,$params=array('category_id'=>$category_id),$text_opts='');
             echo "</td>";
        }   
        
        echo "</tr>";
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_edit_category','First',$stream=null,$params=array('category_id'=>$category_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_category','&lt',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_category',($i+1),$stream=null,$params=array('category_id'=>$category_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_category','&gt',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_category','Last',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//confirm edit category
function shn_sn_ad_edit_category_confirm(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $category_id = $_REQUEST["category_id"];
   
    echo "<h2><center>"._t("Edit Category Information of Social Network")."</center></h2>";

    shn_form_fopen('ad_edit_categoty_cr','sn',$form_opts);
    shn_form_hidden(array('category_id'=>$category_id));

    shn_form_fsopen(_t("Edit Category Detail"));
    
    shn_form_text(_t('Category Name'),'sn_category_name','');
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Edit"),'name="edit_category_info"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//edit category cr
function shn_sn_ad_edit_categoty_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $category_id = $_REQUEST["category_id"];
     $category_name = $_REQUEST["sn_category_name"];
                      
       if(isset($_REQUEST['edit_category_info'])){
            
           $errors = array();
           if($_REQUEST["sn_category_name"]==null){
           add_error(_t("Please fill category name"));
            shn_sn_ad_edit_category();
           }
           else{
           $sql = "UPDATE sn_category SET category_name=? WHERE category_id=? ";
           $res = $db->Execute($sql,array($category_name,$category_id));
           shn_sn_ad_edit_category();
           }    
       }
        else{
             shn_sn_ad_edit_category();
       }    
}

//delete categoty information
function shn_sn_ad_delete_category(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("delete Category Types of Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('category_id'=>$category_id));

    shn_form_fsopen(_t("Available Category Types")); ?>
    <div class="info"><?= _t("These are the available category types ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_category";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    $note_query = "SELECT category_id,category_name,parent_id,level FROM sn_category";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("Category")."</th> <th>"._t("Category Type")."</th> <th>"._t("Immediate Parent")."</th> <th></th></tr>";
    while($row=$rs->FetchRow()){
        $category_id = $row["category_id"];
        $category_name = $row["category_name"];
        $parent_id = $row["parent_id"];
        $level = $row["level"];
        echo "<tr>";
        
        if($level=="0"){
            echo "<td>".$category_name."</td>";
            echo "<td>"._t("Main Category")."</td>";
            echo "<td>"._t("No Perant")."</td>";
            echo "<td>";
            
            $q1 = "SELECT COUNT(*) AS c FROM sn_category WHERE parent_id=?";
            $r1 = $db->Execute($q1,array($category_id));
            $count=$r1->fields['c'];
            
            $q2 = "SELECT COUNT(*) AS c1 FROM sn_groups WHERE category_id=?";
            $r2 = $db->Execute($q2,array($category_id));
            $count1=$r2->fields['c1'];
            if($count>0 OR $count1>0){
                 echo _t("This category have one or more sub categories or, <br> This category used one or more group/s ");
      
            }else{
                
                shn_acl_secure_hyperlink('sn','ad_delete_category_confirm',_t('Delete'),$stream=null,$params=array('category_id'=>$category_id),$text_opts='');
            }
            echo "</td>";
        
        }else{
            echo "<td>".$category_name."</td>";
            echo "<td>"._t("Sub Category")."</td>";
           
             $query = "SELECT category_name FROM sn_category WHERE category_id=?";
             $res = $db->Execute($query,array($parent_id));
             $parent_category_name=$res->fields["category_name"];
             echo "<td>".$parent_category_name."</td>";
             echo "<td>";
             
             $q1 = "SELECT COUNT(*) AS c FROM sn_category WHERE parent_id=?";
             $r1 = $db->Execute($q1,array($category_id));
             $count=$r1->fields['c'];
             
             $q2 = "SELECT COUNT(*) AS c1 FROM sn_groups WHERE category_id=?";
             $r2 = $db->Execute($q2,array($category_id));
             $count1=$r2->fields['c1'];
             if($count>0 OR $count1>0){
                 echo _t("This category have one or more sub categories or, <br> This category used one or more group/s ");
      
             }else{
                
                shn_acl_secure_hyperlink('sn','ad_delete_category_confirm',_t('Delete'),$stream=null,$params=array('category_id'=>$category_id),$text_opts='');
             }
             echo "</td>";
        }   
        
        echo "</tr>";
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_delete_category','First',$stream=null,$params=array('category_id'=>$category_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_category','&lt',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_category',($i+1),$stream=null,$params=array('category_id'=>$category_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_category','&gt',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_category','Last',$stream=null,$params=array('category_id'=>$category_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//delete category confirm
function shn_sn_ad_delete_category_confirm(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $category_id = $_REQUEST["category_id"];
   
    echo "<h2><center>"._t("Delete Confirm Category Information of Social Network")."</center></h2>";

    shn_form_fopen('ad_delete_category_cr','sn',$form_opts);
    shn_form_hidden(array('category_id'=>$category_id));

    echo "<p>"._t("Are you sure you need to delete the following category?. <br/> <br/><em>Note that all information of category will be deleted!</em>")."</p><br/>";
    shn_form_fsopen(_t("Delete Category Detail"));
    
    $query = "SELECT category_name FROM sn_category WHERE category_id=?";
    $res = $db->Execute($query,array($category_id));
    $category_name= $res->fields["category_name"];
    
        echo "<table border=2>";
        echo "<tr><th>"._t("Category Name")."</th></tr>";
        echo "<tr>";
        echo "<td>".$category_name."</td>";
        echo "</tr>";
        echo "</table><br><br>";
        
    shn_form_fsclose();
        
    shn_form_submit(_t("Delete"),'name="delete_category"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//delete category cr
function shn_sn_ad_delete_category_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $category_id = $_REQUEST["category_id"];
                 
     if(isset($_REQUEST['delete_category'])){
            
        $query = "DELETE FROM sn_category WHERE category_id=?";
        $res = $db->Execute($query,array($category_id));
        shn_sn_ad_delete_category();
          
     }else{
        
        shn_sn_ad_delete_category();
        
     }    
}

//function for view group information
function shn_sn_ad_view_groups_info(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("View Groups in Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id));

    shn_form_fsopen(_t("Available Groups")); ?>
    <div class="info"><?= _t("These are the available groups ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_groups";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=15;

    $note_query = "SELECT group_name,description FROM sn_groups ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("group Name")."</th><th>"._t("Description")."</th></tr>";
    while($row=$rs->FetchRow()){
        $group_name = $row["group_name"];
        $description = $row["description"];
        echo "<tr>";
        echo "<td>".$group_name."</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
      
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_view_groups_info','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_groups_info','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_groups_info',($i+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_groups_info','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_groups_info','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
}

//function for create new groups
function shn_sn_ad_create_groups(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Create Groups for Social Network")."</center></h2>";

    shn_form_fopen('ad_create_groups_cr','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id));

    shn_form_fsopen(_t("Available Groups")); ?>
    <div class="info"><?= _t("These are the available groups ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_groups";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=5;

    $note_query = "SELECT group_name,description FROM sn_groups ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("group Name")."</th><th>"._t("Description")."</th></tr>";
    while($row=$rs->FetchRow()){
        $group_name = $row["group_name"];
        $description = $row["description"];
        echo "<tr>";
        echo "<td>".$group_name."</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
      
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_create_groups','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_groups','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_groups',($i+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_groups','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_groups','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();

    shn_form_fsopen(_t("Information for New Group"));
        
    shn_form_text(_t('Group Name'),'sn_group_name','');
    
    $category_query = "SELECT category_id,category_name,parent_id,level FROM sn_category WHERE level=0";
    $rs = $db->Execute($category_query);
    $options = array();
    while($row=$rs->FetchRow()){
        $category_id = $row["category_id"];
        $category_name = $row["category_name"];
        $parent_id = $row["parent_id"];
        $level = $row["level"];
        
        $options[$category_id] = $category_name;
        $sub_cats  = _shn_sn_get_sub_categories($category_id);
        $options = array_merge($options,$sub_cats);
    }
   // $options =_shn_sn_get_stored_category();
    shn_form_select($options,_t("Category"),'sn_category','','');
       
    shn_form_textarea(_t('Description'),'sn_group_description','');
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Create Group"),'name="create_group"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

function _shn_sn_get_sub_categories($category_id){
    global $global;
    $db = $global['db'];
    //$db->debug = true;
    $opts = array();
    $res = $db->Execute("SELECT category_id,category_name,level FROM sn_category WHERE parent_id=? ORDER BY category_id",array($category_id));
    while($row=$res->FetchRow()){
        $tmpstr = '';
        for($i=0;$i<$row['level'];$i++){
            $tmpstr .= '&nbsp;&nbsp;';
        }
        $opts[$row['category_id']] = $tmpstr.$row['category_name']; 
        $sub_opts = _shn_sn_get_sub_categories($row['category_id']);
        $opts = array_merge($opts,$sub_opts);
    }
    return $opts;
}
 
//create new group
function shn_sn_ad_create_groups_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $category_id = $_REQUEST["sn_category"];
     $group_name = $_REQUEST["sn_group_name"];
     $description = $_REQUEST["sn_group_description"];
     $sn_available_groups = $_REQUEST["sn_available_groups"];
     
     $group_id = shn_create_uuid('sn_group');
     //echo "<br>".$group_id;
         
   if(isset($_REQUEST['create_group'])){
    
       $q="SELECT COUNT(*) AS c FROM sn_groups WHERE group_name=?";
       $rs = $db->Execute($q,array($group_name));
       $count=$rs->fields['c'];
       if($count>0){
            
            add_error(_t("This group name is all redye exist"));
            shn_sn_ad_create_new_roles();
       }else{  
                    
           $errors = array();
           if($_REQUEST["sn_group_name"]==null OR $_REQUEST["sn_group_description"]==null OR $_REQUEST["sn_category"]==null){
           add_error(_t("Please fill group name, group type & description"));
           shn_sn_ad_create_groups();
           }
           else{
           $sql = "INSERT INTO sn_groups(group_id,group_name,description,category_id) VALUES (?,?,?,?)";
           $res = $db->Execute($sql,array($group_id,$group_name,$description,$category_id));
           shn_sn_ad_view_groups_info();
           }
       }  
   }
    else{
        shn_sn_ad_manage_groups();
    }    
}

//function for edit group info
function shn_sn_ad_edit_groups_info(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Edit Groups Information of Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id));

    shn_form_fsopen(_t("Available Groups")); ?>
    <div class="info"><?= _t("These are the available groups ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_groups";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    $note_query = "SELECT group_id,group_name,description FROM sn_groups ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("group Name")."</th><th>"._t("Description")."</th> <th></th> </tr>";
    while($row=$rs->FetchRow()){
        $group_id = $row["group_id"];
        $group_name = $row["group_name"];
        $description = $row["description"];
        echo "<tr>";
        echo "<td>".$group_name."</td>";
        echo "<td>".$description."</td>";
        
        echo "<td>";
        shn_acl_secure_hyperlink('sn','ad_edit_groups_info_confirm',_t('Edit'),$stream=null,$params=array('group_id'=>$group_id),$text_opts='');
        echo "</td></tr>";
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_edit_groups_info','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_groups_info','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_groups_info',($i+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_groups_info','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_groups_info','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
}

//confirm edit group
function shn_sn_ad_edit_groups_info_confirm(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $group_id = $_REQUEST["group_id"];
   
    echo "<h2><center>"._t("Edit Groups Information of Social Network")."</center></h2>";

    shn_form_fopen('ad_edit_groups_info_cr','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id));

    shn_form_fsopen(_t("Edit Group Detail"));
    
    shn_form_text(_t('Group Name'),'sn_group_name','');
    shn_form_textarea(_t('Description'),'sn_group_description','');
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Edit"),'name="edit_group_info"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//edit group cr
function shn_sn_ad_edit_groups_info_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $group_id = $_REQUEST["group_id"];
     $group_name = $_REQUEST["sn_group_name"];
     $description = $_REQUEST["sn_group_description"];
                 
       if(isset($_REQUEST['edit_group_info'])){
            
           $errors = array();
           if($_REQUEST["sn_group_name"]==null OR $_REQUEST["sn_group_description"]==null){
           add_error(_t("Please fill group name & description"));
           shn_sn_ad_edit_groups_info_confirm();
           }
           else{
           $sql = "UPDATE sn_groups SET group_name=?, description=? WHERE group_id=? ";
           $res = $db->Execute($sql,array($group_name,$description,$group_id));
           shn_sn_ad_edit_groups_info();
           }    
       }
        else{
            shn_sn_ad_edit_groups_info();
       }    
}

//delete groups
function shn_sn_ad_delete_groups(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Delete Groups of Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id));

    shn_form_fsopen(_t("Available Groups")); ?>
    <div class="info"><?= _t("These are the available groups ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_groups";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    $note_query = "SELECT group_id,group_name,description FROM sn_groups ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("group Name")."</th><th>"._t("Description")."</th> <th></th> </tr>";
    while($row=$rs->FetchRow()){
        $group_id = $row["group_id"];
        $group_name = $row["group_name"];
        $description = $row["description"];
        echo "<tr>";
        echo "<td>".$group_name."</td>";
        echo "<td>".$description."</td>";
        echo "<td>";
        
            $q1 = "SELECT COUNT(*) AS c FROM sn_group_role WHERE group_id=?";
            $r1 = $db->Execute($q1,array($group_id));
            $count=$r1->fields['c'];
            if($count>0){
                echo "This group is used one or more user";
                
            }else{
                
                shn_acl_secure_hyperlink('sn','ad_delete_groups_confirm',_t('Delete'),$stream=null,$params=array('group_id'=>$group_id),$text_opts='');
            }
        echo "</td></tr>";
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_delete_groups','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_groups','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_groups',($i+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_groups','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_groups','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
} 

//delete group confirm
function shn_sn_ad_delete_groups_confirm(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $group_id = $_REQUEST["group_id"];
   
    echo "<h2><center>"._t("Delete Confirm Group Information of Social Network")."</center></h2>";

    shn_form_fopen('ad_delete_groups_cr','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id));

    echo "<p>"._t("Are you sure you need to delete the following Group?. <br/> <br/><em>Note that all information of group will be deleted!</em>")."</p><br/>";
    shn_form_fsopen(_t("Delete Group Detail"));
    
    $query = "SELECT group_name, description FROM sn_groups WHERE group_id=?";
    $res = $db->Execute($query,array($group_id));
    $group_name= $res->fields["group_name"];
    $description= $res->fields["description"];
    
        echo "<table border=2>";
        echo "<tr><th>"._t("group Name")."</th><th>"._t("Description")."</th></tr>";
        echo "<tr>";
        echo "<td>".$group_name."</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
        echo "</table><br><br>";
        
    shn_form_fsclose();
        
    shn_form_submit(_t("Delete"),'name="delete_group"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//delete group cr
function shn_sn_ad_delete_groups_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $group_id = $_REQUEST["group_id"];
                 
     if(isset($_REQUEST['delete_group'])){
            
        $query = "DELETE FROM sn_groups WHERE group_id=?";
        $res = $db->Execute($query,array($group_id));
        shn_sn_ad_delete_groups();
          
     }else{
        
        shn_sn_ad_delete_groups();
        
     }    
}

function shn_sn_ad_add_group_note(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Add Notices to Groups")."</center></h2>";

    shn_form_fopen('ad_add_group_note_cr','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id));

    shn_form_fsopen(_t("Available Group Notices")); ?>
    <div class="info"><?= _t("These are the available group notices.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_group_note";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=5;

    $note_query = "SELECT g.group_id, g.group_name, gn.note_id, gn.date, gn.subject, gn.note FROM sn_groups g JOIN sn_group_note gn ON g.group_id=gn.group_id ORDER BY note_id DESC";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    
    echo "<ul>";
    while($row=$rs->FetchRow()){
        $group_id = $row["group_id"];
        $group_name = $row["group_name"];
        $note_id = $row["note_id"];
        $subject = $row["subject"];
        $date = $row["date"];
        $note = $row["note"];
        echo "<li> Group Name :".$group_name." Date :".$date."</li>";
        echo "<li> Subject :".$subject."</li>";
        echo "<li> Nitice :".$note."</li>";
        shn_acl_secure_hyperlink('sn','ad_edit_group_note','Edit',$stream=null,$params=array('group_id'=>$group_id,'note_id'=>$note_id),$text_opts='');
        echo "&nbsp &nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_group_note','Delete',$stream=null,$params=array('group_id'=>$group_id,'note_id'=>$note_id),$text_opts='');
        echo "<hr>";
    }
    echo "</ul>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_add_group_note','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_group_note','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_group_note',($i+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_group_note','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_group_note','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_form_fsopen(_t('Add Notices'));
    
    $stored_groups = _shn_sn_get_stored_groups();
    shn_form_multi_select('sn_available_group', $stored_groups,'Available Forums','','length=100%');
    
    shn_form_text(_t('subject'),'subject','');
    shn_form_wysiwyg(_t('New Notices'), 'sn_note' , array('value'=>$note));

    shn_form_fsclose();
    
    shn_form_submit(_t("Add"),'name="add_note"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
	
}

function shn_sn_ad_add_group_note_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $sn_available_group = $_REQUEST["sn_available_group"];
    $subject = $_REQUEST["subject"];
    $note = $_REQUEST["sn_note"];
    $date=date("Y-m-d");
    $note_id = shn_create_uuid('sn_group_note');
    
    if(isset($_REQUEST['add_note'])){
        if($_REQUEST["subject"]==null OR  $_REQUEST["sn_note"]==null){
        	add_error("please fill the subject and note");
        	shn_sn_ad_add_group_note();
        }else{
        	foreach($sn_available_group as $group_id){
            $sql = "INSERT INTO sn_group_note(note_id,group_id,subject,date,note) VALUES (?,?,?,?,?)";
            $res = $db->Execute($sql,array($note_id,$group_id,$subject,$date,$note));
        	}
        	unset($_POST);
            add_confirmation(_t("Note was added successfully."));
            shn_sn_ad_manage_groups();  
        }
                 
    }else{
        shn_sn_ad_manage_groups();
    }
}

function shn_sn_ad_edit_group_note(){
	global $global;
    $db = $global['db'];
    
    $group_id = $_REQUEST["group_id"];
    $note_id = $_REQUEST["note_id"];
    
    echo "<h2><center>"._t("Edit Notices of Groups")."</center></h2>";

    shn_form_fopen('ad_edit_group_note_cr','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id,'note_id'=>$note_id));

    shn_form_fsopen(_t("Edit notices")); 
   
    $note_query = "SELECT g.group_id, g.group_name, gn.note_id, gn.date, gn.subject, gn.note FROM sn_groups g JOIN sn_group_note gn ON g.group_id=gn.group_id WHERE gn.note_id=?";
    $rs = $db->Execute($note_query,array($note_id));
    
    echo "<ul>";
        $group_id = $rs->fields["group_id"];
        $group_name = $rs->fields["group_name"];
        $note_id = $rs->fields["note_id"];
        $subject = $rs->fields["subject"];
        $date = $rs->fields["date"];
        $note = $rs->fields["note"];
        echo "<li> Group Name :".$group_name." Date :".$date."</li>";
        echo "<li> Subject :".$subject."</li>";
        echo "<li> Nitice :".$note."</li>";
       
    echo "</ul>";
    shn_form_fsclose();
    
    shn_form_fsopen(_t('Edit Notices'));
        
    shn_form_text(_t('subject'),'subject','',array('value'=>$subject));
    shn_form_wysiwyg(_t('New Notices'), 'sn_note' , array('value'=>$note));

    shn_form_fsclose();
    
    shn_form_submit(_t("Edit"),'name="edit_note"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    	
}

function shn_sn_ad_edit_group_note_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $group_id = $_REQUEST["group_id"];
    $note_id = $_REQUEST["note_id"];
    $subject = $_REQUEST["subject"];
    $note = $_REQUEST["sn_note"];
        
    if(isset($_REQUEST['edit_note'])){
        if($_REQUEST["subject"]==null OR  $_REQUEST["sn_note"]==null){
            add_error("please fill the subject and note");
            shn_sn_ad_edit_group_note();
        }else{
            
            $sql = " UPDATE sn_group_note SET subject=?, note=? WHERE group_id=? AND note_id=?";
            $res = $db->Execute($sql,array($subject,$note,$group_id,$note_id));
           
            unset($_POST);
            add_confirmation(_t("Note was updated successfully."));
             shn_sn_ad_add_group_note();  
        }
                 
    }else{
        shn_sn_ad_add_group_note();
    }
	
}

function shn_sn_ad_delete_group_note(){
	global $global;
    $db = $global['db'];
    
    $group_id = $_REQUEST["group_id"];
    $note_id = $_REQUEST["note_id"];
    
    echo "<h2><center>"._t("Delete Notices of Groups")."</center></h2>";

    shn_form_fopen('ad_delete_group_note_cr','sn',$form_opts);
    shn_form_hidden(array('group_id'=>$group_id,'note_id'=>$note_id));

    shn_form_fsopen(_t("Delete notices")); 
    echo "<p>"._t("Are you sure you need to delete the following Notices?. <br/> <br/><em>Note that all information of Notices will be deleted!</em>")."</p><br/>";
    
    $note_query = "SELECT g.group_id, g.group_name, gn.note_id, gn.date, gn.subject, gn.note FROM sn_groups g JOIN sn_group_note gn ON g.group_id=gn.group_id WHERE gn.note_id=?";
    $rs = $db->Execute($note_query,array($note_id));
    
    echo "<ul>";
        $group_id = $rs->fields["group_id"];
        $group_name = $rs->fields["group_name"];
        $note_id = $rs->fields["note_id"];
        $subject = $rs->fields["subject"];
        $date = $rs->fields["date"];
        $note = $rs->fields["note"];
        echo "<li> Group Name :".$group_name." Date :".$date."</li>";
        echo "<li> Subject :".$subject."</li>";
        echo "<li> Nitice :".$note."</li>";
       
    echo "</ul>";
    shn_form_fsclose();
        
    shn_form_submit(_t("Delete"),'name="delete_note"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_groups',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
	
}

function shn_sn_ad_delete_group_note_cr(){
	global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $group_id = $_REQUEST["group_id"];
    $note_id = $_REQUEST["note_id"];
           
    if(isset($_REQUEST['delete_note'])){
        
            $sql = "DELETE FROM sn_group_note WHERE group_id=? AND note_id=?";
            $res = $db->Execute($sql,array($group_id,$note_id));
           
            unset($_POST);
            add_confirmation(_t("Note was deleted successfully."));
            shn_sn_ad_add_group_note();  
                 
    }else{
        shn_sn_ad_add_group_note();
    }
}

//........................Roles Mannagement...........................................................

//function for view role infomation
function shn_sn_ad_view_roles_info(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("View Roles Information of Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('role_id'=>$role_id));

    shn_form_fsopen(_t("Available Roles")); ?>
    
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_roles";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    echo "<div class=\"info\">"._t("These are the available Roles ditails for the users.")."</div>";
    
    $note_query = "SELECT role_name,description FROM sn_roles WHERE role_category='sn' ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("Role Name")."</th><th>"._t("Description")."</th></tr>";
    while($row=$rs->FetchRow()){
        $role_name = $row["role_name"];
        $description = $row["description"];
        echo "<tr>";
        echo "<td>".$role_name."</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
      }
    echo "</table>";
    echo "<br><br>";
    
    echo "<div class=\"info\">"._t("These are the available Roles ditails for the forum users.")."</div>";
    
    $note_query = "SELECT role_name,description FROM sn_roles WHERE role_category='forum' ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("Role Name")."</th><th>"._t("Description")."</th></tr>";
    while($row=$rs->FetchRow()){
        $role_name = $row["role_name"];
        $description = $row["description"];
        echo "<tr>";
        echo "<td>".$role_name."</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
       
    }
    echo "</table>";
    echo "<br><br>";
    
    echo "<div class=\"info\">". _t("These are the available Roles ditails for the group users.")."</div>";
    
    $note_query = "SELECT role_name,description FROM sn_roles WHERE role_category='group' ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border=2>";
    echo "<tr><th>"._t("Role Name")."</th><th>"._t("Description")."</th></tr>";
    while($row=$rs->FetchRow()){
        $role_name = $row["role_name"];
        $description = $row["description"];
        echo "<tr>";
        echo "<td>".$role_name."</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
       
    }
    echo "</table>";
    
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_view_roles_info','First',$stream=null,$params=array('role_id'=>$role_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_roles_info','&lt',$stream=null,$params=array('role_id'=>$role_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_roles_info',($i+1),$stream=null,$params=array('role_id'=>$role_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_roles_info','&gt',$stream=null,$params=array('role_id'=>$role_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_roles_info','Last',$stream=null,$params=array('role_id'=>$role_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_acl_secure_hyperlink('sn','ad_manage_roles',_t('Roles admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//serch people for assing role
function shn_sn_ad_search_people_forum(){
    echo "<h2><center>"._t("Search Registered Users of Social Network")."</center></h2>";
    
    shn_form_fopen('ad_search_people_forum_cr','sn',array('req_message'=>false));
    shn_form_fsopen("Search & Finding Registered Users");
    shn_form_text(_t('Name'),'person_name','',array('req'=>false));
    shn_form_fsclose();
    shn_form_submit(_t("Search"),' name="search" ');
    shn_form_fclose();
    
}

function shn_sn_ad_search_people_forum_cr(){
    global $global;
    include_once($global['approot'].'inc/lib_image.inc');
    $db = $global['db'];
    //$db->debug = true;
    shn_sn_ad_search_people_forum();
    echo "<br/><hr/>";
    $name = $_REQUEST['person_name'];
    $count = $db->Execute("SELECT COUNT(*) as c FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid WHERE (full_name LIKE '%".$name."%' OR family_name LIKE '%".$name."%')");
    $count = $count->fields['c'];
    $query = "SELECT pu.*,pd.* FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid WHERE (full_name LIKE '%".$name."%' OR family_name LIKE '%".$name."%') ";
    $rpp = 10;
    $page = isset($_REQUEST['page'])?$_REQUEST['page']:1;
    $res = $db->SelectLimit($query,$rpp,$rpp*($page-1));
    if($res->RecordCount()==0){
        echo "<div><em>"._t("No records found.")."</em></div><hr/>";
    }
    while($row = $res->FetchRow()){

        echo "<div>";
        echo "<img src='index.php?mod=sn&act=view_img&stream=image&x_uuid=".$row['p_uuid']."&rand=".substr(md5(rand(0,2500)),0,5)."' border='0' widhth='50' height='50'/>";
        echo "<br/>";
        echo "<em>".$row['full_name']." ".$row['family_name']."</em><br/>";
        shn_form_fopen('ad_add_roles_to_forum_users','sn',array('req_message'=>false));
        shn_form_hidden(array('p_uuid'=>$row['p_uuid'],'full_name'=>$row['full_name'],'family_name'=>$row['family_name']));
        
        shn_form_submit(_t('Add Role'));
        shn_form_fclose();
        echo "</div><hr/>";
    }
    if($count > 0){
        echo "<span>"._t("Page : ");
        for($i=1;$i<=(($count%$rpp)==0?($count/$rpp):(($count/$rpp)+1));$i++){
            shn_acl_secure_hyperlink('sn','ad_search_people_cr',$i,'',array('page'=>$i,'person_name'=>$name,'search'=>'search'));
            echo "&nbsp;&nbsp;";
        }
        echo "</span>";
    }

}

//add roles to user 
function shn_sn_ad_add_roles_to_forum_users(){
    global $global;
    $db = $global['db'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $full_name = $_REQUEST["full_name"];
    
    echo "<h2><center>"._t("Assing Role of Forums")."</center></h2>";
    
    shn_form_fopen('ad_add_roles_to_forum_users_cr','sn',array('req_message'=>false));
    shn_form_hidden(array('p_uuid'=>$p_uuid));

    $q="SELECT full_name FROM person_uuid WHERE p_uuid=?";
    $rs = $db->Execute($q,array($p_uuid));
    $full_name=$rs->fields['full_name'];
    
    shn_form_fsopen("Current Roles of :".$full_name );
    
    $query = "SELECT pu.full_name, r.role_name, r.role_id, f.forum_name FROM sn_forum_role ur JOIN person_uuid pu ON ur.user_id=pu.p_uuid JOIN sn_roles r ON r.role_id=ur.role_id JOIN sn_forums f ON f.forum_id=ur.forum_id WHERE pu.p_uuid=? ";
    $res = $db->Execute($query,$p_uuid);
    echo "<table border=1>";
    echo "<tr><th>"._t("Role Name")."</th> <th>"._t("Forum Name")."</th> <th></th></tr>";
    while($row=$res->FetchRow()){
        $role_name = $row["role_name"];
        $forum_name = $row["forum_name"];
        echo "<tr>";
        echo "<td>".$role_name."</td>";
        echo "<td>".$forum_name."</td>";
        echo "<td>";
        shn_acl_secure_hyperlink('sn','ad_delete_roles_from_forum_users',_t('Delete Role'),$stream=null,$params=array('role_id'=>$row["role_id"],'p_uuid'=>$p_uuid),$text_opts='');
        echo "</td>";
        echo "</tr>";
       
    }
    echo "</table>";
    shn_form_fsclose();
    
    shn_form_fsopen("Assing New Role to User");
    
     
    $stored_forums = _shn_sn_get_stored_forums();
    shn_form_multi_select('sn_available_forum', $stored_forums,_t('Available Forums'),'','length=100%');
    
    $stored_role = _shn_sn_get_stored_forum_role();
    shn_form_multi_select('sn_available_role', $stored_role,_t('Available Roles'),'','length=100%');
       
    shn_form_fsclose();
    
    shn_form_submit(_t("Add"),'name="add_role"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    
    shn_form_fclose();
    shn_acl_secure_hyperlink('sn','ad_manage_roles',_t('Role admin Panel'),$stream=null,$params=array(),$text_opts='');
        
}

//add role to sn_user_role
function shn_sn_ad_add_roles_to_forum_users_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $sn_available_role = $_REQUEST["sn_available_role"];
    $sn_available_forum = $_REQUEST["sn_available_forum"];
    
    if(isset($_REQUEST['add_role'])){
    	
        foreach($sn_available_role as $role_id){
        $q="SELECT COUNT(*) AS c FROM sn_forum_role WHERE role_id=? AND user_id=?";
        $rs = $db->Execute($q,array($role_id,$p_uuid));
        $count=$rs->fields['c'];
        }
        if($count=='0' && $role_id!="f1"){   
            
            foreach($sn_available_forum as $forum_id){
            foreach($sn_available_role as $role_id){
            $sql = "INSERT INTO sn_forum_role(role_id,forum_id,user_id) VALUES (?,?,?)";
            $res = $db->Execute($sql,array($role_id,$forum_id,$p_uuid));
            }
            }
            add_confirmation(_t("Role was added successfully."));
            shn_sn_ad_manage_roles();
        }    
        else if($count=='0' && $role_id=="f1"){
        	
            $query = "SELECT forum_id FROM sn_forums ";
		    $res = $db->Execute($query);
		    foreach($res as $row){
		      $forum_id_1 = $row["forum_id"];

	            foreach($sn_available_role as $role_id){
	            $sql = "INSERT INTO sn_forum_role(role_id,forum_id,user_id) VALUES (?,?,?)";
	            $res = $db->Execute($sql,array($role_id,$forum_id_1,$p_uuid));
	            }	            		        
		    }
		        add_confirmation(_t("Role was added successfully."));  
		        shn_sn_ad_manage_roles();  
        }else{
            
            add_error(_t("This role already assigned this user for this forum"));
            shn_sn_ad_add_roles_to_forum_users();
        }
                
    }else{
        shn_sn_ad_manage_roles();
    }
}

//delete rolse form users confirme
function shn_sn_ad_delete_roles_from_forum_users(){
    global $global;
    $db = $global['db'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $role_id = $_REQUEST["role_id"];
     
    echo "<h2><center>"._t("Ressing Rolse from Users of Social Network")."</center></h2>";

    shn_form_fopen('ad_delete_roles_from_forum_users_cr','sn',$form_opts);
    shn_form_hidden(array('p_uuid'=>$p_uuid,'role_id'=>$role_id));
    
    shn_form_fsopen("Ressing Rolse from Users");
    
    $query2 = "SELECT r.role_name,pu.full_name FROM sn_forum_role ur JOIN sn_roles r ON ur.role_id=r.role_id JOIN person_uuid pu ON pu.p_uuid=ur.user_id WHERE ur.role_id=? AND ur.user_id=?";
    $res2 = $db->Execute($query2,array($role_id,$p_uuid));
    $role_name=$res2->fields["role_name"];
    $full_name=$res2->fields["full_name"];
    echo "<p>"._t("Are you sure you need to delete the role called <strong>").$role_name._t(" </strong>from the <strong>").$full_name._t("</strong>");
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Delete"),'name="delete_role"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    shn_form_fclose();
    
}

//delete rolse form users from database
function shn_sn_ad_delete_roles_from_forum_users_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
     
    $p_uuid = $_REQUEST["p_uuid"];
    $role_id = $_REQUEST["role_id"];
             
    if(isset($_REQUEST['delete_role'])){
         
       $query = "DELETE FROM sn_forum_role WHERE role_id=? AND user_id=?";
       $res = $db->Execute($query,array($role_id,$p_uuid));
       
       add_confirmation(_t("Role was deleted successfully."));
       shn_sn_ad_add_roles_to_forum_users();
          
    }else{
        
       shn_sn_ad_add_roles_to_forum_users();
    }       
}

// serch people for group
function shn_sn_ad_search_people_group(){
    echo "<h2><center>"._t("Search Registered Users of Social Network")."</center></h2>";
    
    shn_form_fopen('ad_search_people_group_cr','sn',array('req_message'=>false));
    shn_form_fsopen("Search & Finding Registered Users");
    shn_form_text(_t('Name'),'person_name','',array('req'=>false));
    shn_form_fsclose();
    shn_form_submit(_t("Search"),' name="search" ');
    shn_form_fclose();
    
}

function shn_sn_ad_search_people_group_cr(){
    global $global;
    include_once($global['approot'].'inc/lib_image.inc');
    $db = $global['db'];
    //$db->debug = true;
    shn_sn_ad_search_people_forum();
    echo "<br/><hr/>";
    $name = $_REQUEST['person_name'];
    $count = $db->Execute("SELECT COUNT(*) as c FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid WHERE (full_name LIKE '%".$name."%' OR family_name LIKE '%".$name."%')");
    $count = $count->fields['c'];
    $query = "SELECT pu.*,pd.* FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid WHERE (full_name LIKE '%".$name."%' OR family_name LIKE '%".$name."%') ";
    $rpp = 10;
    $page = isset($_REQUEST['page'])?$_REQUEST['page']:1;
    $res = $db->SelectLimit($query,$rpp,$rpp*($page-1));
    if($res->RecordCount()==0){
        echo "<div><em>"._t("No records found.")."</em></div><hr/>";
    }
    while($row = $res->FetchRow()){

        echo "<div>";
        echo "<img src='index.php?mod=sn&act=view_img&stream=image&x_uuid=".$row['p_uuid']."&rand=".substr(md5(rand(0,2500)),0,5)."' border='0' widhth='50' height='50'/>";
        echo "<br/>";
        echo "<em>".$row['full_name']." ".$row['family_name']."</em><br/>";
        shn_form_fopen('ad_add_roles_to_group_users','sn',array('req_message'=>false));
        shn_form_hidden(array('p_uuid'=>$row['p_uuid'],'full_name'=>$row['full_name'],'family_name'=>$row['family_name']));
        
        shn_form_submit(_t('Add Role'));
        shn_form_fclose();
        echo "</div><hr/>";
    }
    if($count > 0){
        echo "<span>"._t("Page : ");
        for($i=1;$i<=(($count%$rpp)==0?($count/$rpp):(($count/$rpp)+1));$i++){
            shn_acl_secure_hyperlink('sn','ad_search_people_cr',$i,'',array('page'=>$i,'person_name'=>$name,'search'=>'search'));
            echo "&nbsp;&nbsp;";
        }
        echo "</span>";
    }

}

//add roles to user 
function shn_sn_ad_add_roles_to_group_users(){
    global $global;
    $db = $global['db'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $full_name = $_REQUEST["full_name"];
    
    shn_form_fopen('ad_add_roles_to_group_users_cr','sn',array('req_message'=>false));
    shn_form_hidden(array('p_uuid'=>$p_uuid));

    $q="SELECT full_name FROM person_uuid WHERE p_uuid=?";
    $rs = $db->Execute($q,array($p_uuid));
    $full_name=$rs->fields['full_name'];
    
    shn_form_fsopen("Current Roles of :".$full_name );
    
    $query = "SELECT pu.full_name, r.role_name, r.role_id, g.group_name FROM sn_group_role gr JOIN person_uuid pu ON gr.user_id=pu.p_uuid JOIN sn_roles r ON r.role_id=gr.role_id JOIN sn_groups g ON g.group_id=gr.group_id WHERE pu.p_uuid=? ";
    $res = $db->Execute($query,$p_uuid);
    echo "<table border=1>";
    echo "<tr><th>"._t("Group Name")."</th> <th>"._t("Role of Group")."</th> <th></th></tr>";
    while($row=$res->FetchRow()){
        $role_name = $row["role_name"];
        $group_name = $row["group_name"];
        $full_name = $row["full_name"];
        
        echo "<tr>";
        echo "<td>".$role_name."</td>";
        echo "<td>".$group_name."</td>";
        echo "<td>";
        shn_acl_secure_hyperlink('sn','ad_delete_roles_from_group_users',_t('Delete Role'),$stream=null,$params=array('role_id'=>$row["role_id"],'p_uuid'=>$p_uuid),$text_opts='');
        echo "</td>";
        echo "</tr>";
       
    }
    echo "</table>";
    shn_form_fsclose();
    
    shn_form_fsopen("Assing New Role to User");
    
     
    $stored_groups = _shn_sn_get_stored_groups();
    shn_form_multi_select('sn_available_group', $stored_groups,_t('Available Groups'),'','length=100%');
    
    $stored_role = _shn_sn_get_stored_group_role();
    shn_form_multi_select('sn_available_role', $stored_role,_t('Available Roles'),'','length=100%');
       
    shn_form_fsclose();
    
    shn_form_submit(_t("Add"),'name="add_role"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    
    shn_form_fclose();
    shn_acl_secure_hyperlink('sn','ad_manage_roles',_t('Role admin Panel'),$stream=null,$params=array(),$text_opts='');
        
}

//add role to sn_user_role
function shn_sn_ad_add_roles_to_group_users_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $sn_available_role = $_REQUEST["sn_available_role"];
    $sn_available_group = $_REQUEST["sn_available_group"];
    
    if(isset($_REQUEST['add_role'])){
        
        foreach($sn_available_role as $role_id){
        $q="SELECT COUNT(*) AS c FROM sn_group_role WHERE role_id=? AND user_id=?";
        $rs = $db->Execute($q,array($role_id,$p_uuid));
        $count=$rs->fields['c'];
        }
        if($count=='0'  && $role_id!="g1"){   
            
            foreach($sn_available_group as $group_id){
            foreach($sn_available_role as $role_id){
            	
            $sql = "INSERT INTO sn_group_role(role_id,group_id,user_id) VALUES (?,?,?)";
            $res = $db->Execute($sql,array($role_id,$group_id,$p_uuid));
            }
            }
            add_confirmation(_t("Role was added successfully."));
            //shn_sn_ad_manage_roles();
            shn_sn_ad_add_roles_to_group_users();
        }
        else if($count=='0'  && $role_id=="g1"){
        	
        	$query = "SELECT group_id FROM sn_groups ";
            $res = $db->Execute($query);
            foreach($res as $row){
            $group_id_1 = $row["group_id"];
        	
	            foreach($sn_available_role as $role_id){
	            $sql = "INSERT INTO sn_group_role(role_id,group_id,user_id) VALUES (?,?,?)";
	            $res = $db->Execute($sql,array($role_id,$group_id_1,$p_uuid));
	            }
            }
        	add_confirmation(_t("Role was added successfully."));
            //shn_sn_ad_manage_roles();
            shn_sn_ad_add_roles_to_group_users();
            
        }else{	
            add_error("This role already assigned this user for this group");
            shn_sn_ad_add_roles_to_group_users();
            
        }
                
    }else{
        shn_sn_ad_manage_roles();
    }
}

//delete rolse form users confirme
function shn_sn_ad_delete_roles_from_group_users(){
    global $global;
    $db = $global['db'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $role_id = $_REQUEST["role_id"];
     
    echo "<h2><center>"._t("Ressing Rolse from Users of Social Network")."</center></h2>";

    shn_form_fopen('ad_delete_roles_from_group_users_cr','sn',$form_opts);
    shn_form_hidden(array('p_uuid'=>$p_uuid,'role_id'=>$role_id));
    
    shn_form_fsopen("Ressing Rolse from Users");
    
    $query2 = "SELECT r.role_name,pu.full_name FROM sn_group_role gr JOIN sn_roles r ON gr.role_id=r.role_id JOIN person_uuid pu ON pu.p_uuid=gr.user_id WHERE gr.role_id=? AND gr.user_id=?";
    $res2 = $db->Execute($query2,array($role_id,$p_uuid));
    $role_name=$res2->fields["role_name"];
    $full_name=$res2->fields["full_name"];
    echo "<p>"._t("Are you sure you need to delete the role called <strong>").$role_name._t(" </strong>from the <strong>").$full_name._t("</strong>");
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Delete"),'name="delete_role"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    shn_form_fclose();
    
}

//delete rolse form users from database
function shn_sn_ad_delete_roles_from_group_users_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
     
    $p_uuid = $_REQUEST["p_uuid"];
    $role_id = $_REQUEST["role_id"];
      
    if(isset($_REQUEST['delete_role'])){
         
       $query = "DELETE FROM sn_group_role WHERE role_id=? AND user_id=?";
       $res = $db->Execute($query,array($role_id,$p_uuid));
       
       add_confirmation(_t("Role was deleted successfully."));
       shn_sn_ad_add_roles_to_group_users();
          
    }else{
        
       shn_sn_ad_add_roles_to_group_users();
    }       
}

// serch people for module
function shn_sn_ad_search_people_module(){
    echo "<h2><center>"._t("Search Registered Users of Social Network")."</center></h2>";
    
    shn_form_fopen('ad_search_people_module_cr','sn',array('req_message'=>false));
    shn_form_fsopen("Search & Finding Registered Users");
    shn_form_text(_t('Name'),'person_name','',array('req'=>false));
    shn_form_fsclose();
    shn_form_submit(_t("Search"),' name="search" ');
    shn_form_fclose();
    
}

function shn_sn_ad_search_people_module_cr(){
    global $global;
    include_once($global['approot'].'inc/lib_image.inc');
    $db = $global['db'];
    //$db->debug = true;
    shn_sn_ad_search_people_forum();
    echo "<br/><hr/>";
    $name = $_REQUEST['person_name'];
    $count = $db->Execute("SELECT COUNT(*) as c FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid WHERE (full_name LIKE '%".$name."%' OR family_name LIKE '%".$name."%')");
    $count = $count->fields['c'];
    $query = "SELECT pu.*,pd.* FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid WHERE (full_name LIKE '%".$name."%' OR family_name LIKE '%".$name."%') ";
    $rpp = 10;
    $page = isset($_REQUEST['page'])?$_REQUEST['page']:1;
    $res = $db->SelectLimit($query,$rpp,$rpp*($page-1));
    if($res->RecordCount()==0){
        echo "<div><em>"._t("No records found.")."</em></div><hr/>";
    }
    while($row = $res->FetchRow()){

        echo "<div>";
        echo "<img src='index.php?mod=sn&act=view_img&stream=image&x_uuid=".$row['p_uuid']."&rand=".substr(md5(rand(0,2500)),0,5)."' border='0' widhth='50' height='50'/>";
        echo "<br/>";
        echo "<em>".$row['full_name']." ".$row['family_name']."</em><br/>";
        shn_form_fopen('ad_add_roles_to_module_users','sn',array('req_message'=>false));
        shn_form_hidden(array('p_uuid'=>$row['p_uuid'],'full_name'=>$row['full_name'],'family_name'=>$row['family_name']));
        
        shn_form_submit(_t('Add Role'));
        shn_form_fclose();
        echo "</div><hr/>";
    }
    if($count > 0){
        echo "<span>"._t("Page : ");
        for($i=1;$i<=(($count%$rpp)==0?($count/$rpp):(($count/$rpp)+1));$i++){
            shn_acl_secure_hyperlink('sn','ad_search_people_cr',$i,'',array('page'=>$i,'person_name'=>$name,'search'=>'search'));
            echo "&nbsp;&nbsp;";
        }
        echo "</span>";
    }

}

//add roles to user 
function shn_sn_ad_add_roles_to_module_users(){
    global $global;
    $db = $global['db'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $full_name = $_REQUEST["full_name"];
    
    shn_form_fopen('ad_add_roles_to_module_users_cr','sn',array('req_message'=>false));
    shn_form_hidden(array('p_uuid'=>$p_uuid));

    shn_form_fsopen("Current Roles of User:");
    
    $query = "SELECT pu.full_name, r.role_name, r.role_id FROM sn_module_role mr JOIN person_uuid pu ON mr.user_id=pu.p_uuid JOIN sn_roles r ON r.role_id=mr.role_id ";
    $res = $db->Execute($query);
    echo "<table border=1>";
    echo "<tr><th>"._t("User Name")."</th> <th>"._t("Role Name")."</th> <th></th></tr>";
    while($row=$res->FetchRow()){
        $role_name = $row["role_name"];
        $full_name = $row["full_name"];
        
        echo "<tr>";
        echo "<td>".$full_name."</td>";
        echo "<td>".$role_name."</td>";
        echo "<td>";
        shn_acl_secure_hyperlink('sn','ad_delete_roles_from_module_users',_t('Delete Role'),$stream=null,$params=array('role_id'=>$row["role_id"],'p_uuid'=>$p_uuid),$text_opts='');
        echo "</td>";
        echo "</tr>";
       
    }
    echo "</table>";
    shn_form_fsclose();
    
    shn_form_fsopen("Assing New Role to User");
        
    $stored_role = _shn_sn_get_stored_module_role();
    shn_form_multi_select('sn_available_role', $stored_role,_t('Available Roles'),'','length=100%');
       
    shn_form_fsclose();
    
    shn_form_submit(_t("Add"),'name="add_role"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    
    shn_form_fclose();
    shn_acl_secure_hyperlink('sn','ad_manage_roles',_t('Role admin Panel'),$stream=null,$params=array(),$text_opts='');
        
}

//add role to sn_user_role
function shn_sn_ad_add_roles_to_module_users_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $sn_available_role = $_REQUEST["sn_available_role"];
       
    if(isset($_REQUEST['add_role'])){
        
        foreach($sn_available_role as $role_id){
        $q="SELECT COUNT(*) AS c FROM sn_module_role WHERE role_id=? AND user_id=?";
        $rs = $db->Execute($q,array($role_id,$p_uuid));
        $count=$rs->fields['c'];
        }
        if($count=='0'){   
                        
            foreach($sn_available_role as $role_id){
            $sql = "INSERT INTO sn_module_role(role_id,user_id) VALUES (?,?)";
            $res = $db->Execute($sql,array($role_id,$p_uuid));
            }
            
            add_confirmation(_t("Role was added successfully."));
            shn_sn_ad_add_roles_to_module_users();
        }else{
            
            add_error("This role already assigned this user for this module");
            shn_sn_ad_add_roles_to_module_users();
        }
                
    }else{
        shn_sn_ad_manage_roles();
    }
}

//delete rolse form users confirme
function shn_sn_ad_delete_roles_from_module_users(){
    global $global;
    $db = $global['db'];
    
    $p_uuid = $_REQUEST["p_uuid"];
    $role_id = $_REQUEST["role_id"];
     
    echo "<h2><center>"._t("Ressing Rolse from Users of Social Network")."</center></h2>";

    shn_form_fopen('ad_delete_roles_from_module_users_cr','sn',$form_opts);
    shn_form_hidden(array('p_uuid'=>$p_uuid,'role_id'=>$role_id));
    
    shn_form_fsopen("Ressing Rolse from Users");
    
    $query2 = "SELECT r.role_name,pu.full_name FROM sn_module_role gr JOIN sn_roles r ON gr.role_id=r.role_id JOIN person_uuid pu ON pu.p_uuid=gr.user_id WHERE gr.role_id=? AND gr.user_id=?";
    $res2 = $db->Execute($query2,array($role_id,$p_uuid));
    $role_name=$res2->fields["role_name"];
    $full_name=$res2->fields["full_name"];
    echo "<p>"._t("Are you sure you need to delete the role called <strong>").$role_name._t(" </strong>from the <strong>").$full_name._t("</strong>");
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Delete"),'name="delete_role"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    shn_form_fclose();
    
}

//delete rolse form users from database
function shn_sn_ad_delete_roles_from_module_users_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
     
    $p_uuid = $_REQUEST["p_uuid"];
    $role_id = $_REQUEST["role_id"];
      
    if(isset($_REQUEST['delete_role'])){
         
       $query = "DELETE FROM sn_module_role WHERE role_id=? AND user_id=?";
       $res = $db->Execute($query,array($role_id,$p_uuid));
       
       add_confirmation(_t("Role was deleted successfully."));
       shn_sn_ad_add_roles_to_module_users();
          
    }else{
        
       shn_sn_ad_add_roles_to_module_users();
    }       
}

//view user request
function shn_sn_ad_approove_req(){
	
	
}

function shn_sn_ad_approove_req_cr(){
    
    
}
//............................User Management...................................................

//view delete user
function shn_sn_ad_view_users_profile(){
	
	
}

function shn_sn_ad_delete_users_profile_cr(){
    
    
}

//add notices to users
function shn_sn_ad_add_notices_to_users(){
	
	
}

function shn_sn_ad_add_notices_to_users_cr(){
    
    
}

//...........................Forum Management.....................................................

//view available forums
function shn_sn_ad_view_current_forums(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Available Forums for Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id));

    shn_form_fsopen(_t("Available Forums")); ?>
    <div class="info"><?= _t("These are the available forums ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_forums";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    $note_query = "SELECT forum_name,description,dis_id FROM sn_forums ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border = 2>";
    echo "<tr><th>"._t("Forum Name")."</th><th>"._t("Description")."</th> </tr>";
    while($row=$rs->FetchRow()){
        $forum_name = $row["forum_name"];
        $description = $row["description"];
        $dis_id = $row["dis_id"];
        echo "<tr>";
        echo "<td>".$forum_name."</td>";
        echo "<td>".$description."</td>";
     
        /*$query2 = "SELECT dis_name,med_name FROM dsm_diseases WHERE dis_id=?";
        $res2 = $db->Execute($query2,array($dis_id));
        $dis_name=$res2->fields["dis_name"];
        $med_name=$res2->fields["med_name"];
        
        if($dis_id=="common"){
        echo "<td>".$dis_id."</td>";
        }else{
        echo "<td>".$dis_name."(".$med_name.")</td>";
        }*/
        echo "</tr>";
    
       /* echo "<td>";
        shn_acl_secure_hyperlink('sn','_edit_groups_info','Edit',$stream=null,$params=array('group_id'=>$group_id),$text_opts='');
        echo "</td></tr>";*/
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_view_current_forums','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_current_forums','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_current_forums',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_current_forums','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_view_current_forums','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//create new forums
function shn_sn_ad_create_new_forums(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Create Forums for Social Network")."</center></h2>";

    shn_form_fopen('ad_create_forums_cr','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id));

    shn_form_fsopen(_t("Available Forums")); ?>
    <div class="info"><?= _t("These are the available forums ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_forums";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=5;

    $note_query = "SELECT forum_name,description FROM sn_forums ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border = 2>";
    echo "<tr><th>"._t("Forum Name")."</th><th>"._t("Description")."</th></tr>";
    while($row=$rs->FetchRow()){
        $forum_name = $row["forum_name"];
        $description = $row["description"];
        echo "<tr>";
        echo "<td>".$forum_name."</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
        
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_create_new_forums','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_new_forums','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_new_forums',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_new_forums','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_create_new_forums','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();

    shn_form_fsopen(_t("Information for New forum"));
    
    shn_form_text(_t('Forum Name'),'sn_forum_name','');
    shn_form_textarea(_t('Description'),'sn_forum_description','');
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Create Forum"),'name="create_forum"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_forums','Forum admin Panel',$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//create new group
function shn_sn_ad_create_forums_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     //$forum_type = $_REQUEST["sn_forum_type"];
     $forum_name = $_REQUEST["sn_forum_name"];
     $description = $_REQUEST["sn_forum_description"];
     //$available_diseases = $_REQUEST["sn_available_diseases"];
     
     $forum_id = shn_create_uuid('sn_forum');
     //echo "<br>".$group_id;
     
     if(isset($_REQUEST['create_forum'])){
        
        $q="SELECT COUNT(*) AS c FROM sn_forums WHERE forum_name=?";
        $rs = $db->Execute($q,array($forum_name));
        $count=$rs->fields['c'];
        if($count>0){
            
            add_error(_t("This forum name is all redye exist"));
            shn_sn_ad_create_new_forums();
        }else{
                       
            $errors = array();
            if($_REQUEST["sn_forum_name"]==null OR $_REQUEST["sn_forum_description"]==null){
                
                add_error(_t("Please fill forum name & description"));
                shn_sn_ad_create_new_forums();
            }else{
                
                $sql = "INSERT INTO sn_forums(forum_id,forum_name,description) VALUES (?,?,?)";
                $res = $db->Execute($sql,array($forum_id,$forum_name,$description));
                shn_sn_ad_view_current_forums();
            }
       }
        
     }else{
        shn_sn_ad_manage_forums();
    } 
   /*if(isset($_REQUEST['create_forum'])){
        
        $q="SELECT COUNT(*) AS c FROM sn_forums WHERE forum_name=?";
        $rs = $db->Execute($q,array($forum_name));
        $count=$rs->fields['c'];
        if ($count>0){
            add_error(_t("This forum name is all redye exist"));
            shn_sn_ad_create_new_forums();
        }else{
            if($forum_type=="common"){
                
                $errors = array();
                if($_REQUEST["sn_forum_name"]==null OR $_REQUEST["sn_forum_description"]==null){
                    add_error(_t("Please fill forum name & description"));
                    shn_sn_ad_create_new_forums();
                }
                else{
                    $sql = "INSERT INTO sn_forums(forum_id,forum_name,description,dis_id) VALUES (?,?,?,?)";
                    $res = $db->Execute($sql,array($forum_id,$forum_name,$description,'common'));
                    shn_sn_ad_view_current_forums();
                }
            }
            if($forum_type=="by_disease"){
                
                $errors = array();
                if($_REQUEST["sn_forum_name"]==null OR $_REQUEST["sn_forum_description"]==null){
                    add_error(_t("Please fill forum name & description"));
                    shn_sn_ad_create_new_forums();
                }
                else{
                
                    foreach($available_diseases as $dis_id){
                    $sql = "INSERT INTO sn_forums(forum_id,forum_name,description,dis_id) VALUES (?,?,?,?)";
                    $res = $db->Execute($sql,array($forum_id,$forum_name,$description,$dis_id));
                    }
                    shn_sn_ad_view_current_forums();
                }
            }
        }
    }
    else{
        shn_sn_ad_manage_forums();
    }    */
}

//edit available forums
function shn_sn_ad_edit_forums(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Edit Forums Information of Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id));

    shn_form_fsopen(_t("Available Forums")); ?>
    <div class="info"><?= _t("These are the available forums ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_forums";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    $note_query = "SELECT forum_id,forum_name,description,dis_id FROM sn_forums ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border = 2>";
    echo "<tr><th>"._t("Forum Name")."</th><th>"._t("Description")."</th> <th></th></tr>";
    while($row=$rs->FetchRow()){
        $forum_id = $row["forum_id"];
        $forum_name = $row["forum_name"];
        $description = $row["description"];
        $dis_id = $row["dis_id"];
        echo "<tr>";
        echo "<td>".$forum_name."</td>";
        echo "<td>".$description."</td>";
     
        /*$query2 = "SELECT dis_name,med_name FROM dsm_diseases WHERE dis_id=?";
        $res2 = $db->Execute($query2,array($dis_id));
        $dis_name=$res2->fields["dis_name"];
        $med_name=$res2->fields["med_name"];
        
        if($dis_id=="common"){
        echo "<td>".$dis_id."</td>";
        }else{
        echo "<td>".$dis_name."(".$med_name.")</td>";
        }*/

        echo "<td>";
        shn_acl_secure_hyperlink('sn','ad_edit_forum_info_confirm',_t('Edit'),$stream=null,$params=array('forum_id'=>$forum_id),$text_opts='');
        echo "</td></tr>";
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_edit_forums','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_forums','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_forums',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_forums','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_edit_forums','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
}

//edit role confirm
function shn_sn_ad_edit_forum_info_confirm(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $forum_id = $_REQUEST["forum_id"];
   
    echo "<h2><center>"._t("Edit Forum Information of Social Network")."</center></h2>";

    shn_form_fopen('ad_edit_forum_info_cr','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id));

    shn_form_fsopen(_t("Edit Forum Detail"));
    
    shn_form_text(_t('Forum Name'),'sn_forum_name','');
    shn_form_textarea(_t('Description'),'sn_forum_description','');
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Edit"),'name="edit_forum_info"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
        
}

//edit forums cr
function shn_sn_ad_edit_forum_info_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $forum_id = $_REQUEST["forum_id"];
     $forum_name = $_REQUEST["sn_forum_name"];
     $description = $_REQUEST["sn_forum_description"];
                 
       if(isset($_REQUEST['edit_forum_info'])){
            
           $errors = array();
           if($_REQUEST["sn_forum_name"]==null OR $_REQUEST["sn_forum_description"]==null){
           add_error(_t("Please fill forum name & description"));
           shn_sn_ad_edit_forum_info_confirm();
           }
           else{
           $sql = "UPDATE sn_forums SET forum_name=?, description=? WHERE forum_id=? ";
           $res = $db->Execute($sql,array($forum_name,$description,$forum_id));
           shn_sn_ad_Edit_forums();
           }    
       }
        else{
            shn_sn_ad_edit_forums();
       }    
} 

//delete available forums
function shn_sn_ad_delete_forums(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Delete Forums Information of Social Network")."</center></h2>";

    shn_form_fopen('','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id));

    shn_form_fsopen(_t("Available Forums")); ?>
    <div class="info"><?php echo _t("These are the available forums ditails.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_forums";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=20;

    $note_query = "SELECT forum_id,forum_name,description,dis_id FROM sn_forums ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border = 2>";
    echo "<tr><th>"._t("Forum Name")."</th><th>"._t("Description")."</th> <th></th></tr>";
    while($row=$rs->FetchRow()){
        $forum_id = $row["forum_id"];
        $forum_name = $row["forum_name"];
        $description = $row["description"];
        $dis_id = $row["dis_id"];
        echo "<tr>";
        echo "<td>".$forum_name."</td>";
        echo "<td>".$description."</td>";
     
        /*$query2 = "SELECT dis_name,med_name FROM dsm_diseases WHERE dis_id=?";
        $res2 = $db->Execute($query2,array($dis_id));
        $dis_name=$res2->fields["dis_name"];
        $med_name=$res2->fields["med_name"];
        
        if($dis_id=="common"){
        echo "<td>".$dis_id."</td>";
        }else{
        echo "<td>".$dis_name."(".$med_name.")</td>";
        }*/
        
        echo "<td>";
            $q1 = "SELECT COUNT(*) AS c FROM sn_user_forum WHERE forum_id=?";
            $r1 = $db->Execute($q1,array($forum_id));
            $count=$r1->fields['c'];
            if($count>0){
                echo "This forum is assinged to one or more user/s";
                
            }else{
                
                shn_acl_secure_hyperlink('sn','ad_delete_forums_confirm',_t('Delete'),$stream=null,$params=array('forum_id'=>$forum_id),$text_opts='');
            }
        echo "</td></tr>";
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_delete_forums','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_forums','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_forums',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_forums','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_forums','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
}

//delete forum confirm
function shn_sn_ad_delete_forums_confirm(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $forum_id = $_REQUEST["forum_id"];
   
    echo "<h2><center>"._t("Delete Confirm Forum Information of Social Network")."</center></h2>";

    shn_form_fopen('ad_delete_forums_cr','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id));

    echo "<p>"._t("Are you sure you need to delete the following forum?. <br/> <br/><em>Note that all information of forum will be deleted!</em>")."</p><br/>";
    shn_form_fsopen(_t("Delete Forum Detail"));
    
    $query = "SELECT forum_name, description FROM sn_forums WHERE forum_id=?";
    $res = $db->Execute($query,array($forum_id));
    $forum_name= $res->fields["forum_name"];
    $description= $res->fields["description"];
    
        echo "<table border=2>";
        echo "<tr><th>"._t("Forum Name")."</th><th>"._t("Description")."</th></tr>";
        echo "<tr>";
        echo "<td>".$forum_name."</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
        echo "</table><br><br>";
        
    shn_form_fsclose();
        
    shn_form_submit(_t("Delete"),'name="delete_forum"');
    shn_form_submit(_t("Cancel"),'name="cancel"');

    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

//delete forum cr
function shn_sn_ad_delete_forums_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $forum_id = $_REQUEST["forum_id"];
                 
     if(isset($_REQUEST['delete_forum'])){
            
        $query = "DELETE FROM sn_forums WHERE forum_id=?";
        $res = $db->Execute($query,array($forum_id));
        shn_sn_ad_delete_forums();
          
     }else{
        
        shn_sn_ad_delete_forums();
        
     }    
}

// post to forum
function shn_sn_ad_post_to_forum(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    echo "<h2><center>"._t("List of Forums")."</center></h2>";
    
    shn_form_fopen('','sn',array('req_message'=>false));
    shn_form_hidden(array('user_id'=>$_SESSION["user_id"],'full_name'=>$full_name));
       
    shn_form_fsopen(_t("List of Forums"));
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_forums";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=10;
    
    $note_query = "SELECT forum_id, forum_name, description FROM sn_forums";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table border = 2>";
    echo "<tr><th>"._t("Forum Name")."</th><th>"._t("Description")."</th> </tr>";
    while($row=$rs->FetchRow()){
        $forum_id = $row["forum_id"];
        $forum_name = $row["forum_name"];
        $description = $row["description"];
        $dis_id = $row["dis_id"];
        echo "<tr>";
        echo "<td>";
        shn_acl_secure_hyperlink('sn','ad_view_forum',$forum_name,$stream=null,$params=array('forum_id'=>$forum_id),$text_opts='');
        echo "</td>";
        echo "<td>".$description."</td>";
        echo "</tr>";
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_post_to_forum','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_post_to_forum','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_post_to_forum',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_post_to_forum','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_post_to_forum','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
   
}

function shn_sn_ad_view_forum(){
    global $global;
    $db=$global['db'];
    
    $forum_id = $_REQUEST['forum_id'];
    
    $query = "SELECT forum_name, description FROM sn_forums WHERE forum_id=?";
    $res = $db->Execute($query,array($forum_id));
    $forum_name= $res->fields["forum_name"];
    
    $q="SELECT COUNT(*) AS c FROM sn_forum_topic WHERE forum_id=?";
    $rs = $db->Execute($q,array($forum_id));
    $count=$rs->fields['c'];
    
    if($count=='0'){
    
        echo "<h2><center>"._t("Create New Topic to Forum &nbsp::").$forum_name."</center></h2>";
    
        shn_form_fopen('ad_create_topic_cr','sn',array('req_message'=>false));
    
        shn_form_fsopen(_t('Create New Topic'));
        shn_form_hidden(array('forum_id'=>$forum_id));
        
        shn_form_text(_('Topic'),'topic');
            
        shn_form_fsclose();
    
        shn_form_submit(_t("Create Topic"),'name="create_topic"');
        shn_form_submit(_t("Cancel"),'name="cancel"');
        
        echo "<br><br>";
        shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
        shn_form_fclose();
        
        
        
    }
    else{
        
        echo "<h2><center>"._t("Current Topic of Forum&nbsp::").$forum_name."</center></h2>";
    
        shn_form_fopen('ad_create_topic_cr','sn',array('req_message'=>false));
    
        shn_form_fsopen(_t('Current Topic'));
        shn_form_hidden(array('forum_id'=>$forum_id));
        
        $page=0;
        if(isset($_REQUEST['page'])){
            $page=$_REQUEST['page'];
    
        }
        
        $q="SELECT COUNT(*) AS c FROM sn_forum_topic WHERE forum_id=?";
        $rs = $db->Execute($q,array($forum_id));
        $count=$rs->fields['c'];
        $rpp=10;
                   
        $query = "SELECT topic_id, topic FROM sn_forum_topic WHERE forum_id=?";
        $res = $db->SelectLimit($query,$rpp,$page*$rpp,array($forum_id));
        
        echo "<table border = 2>";
        echo "<tr><th>"._t("Topic")."</th> <th></th></tr>";
        while($row=$res->FetchRow()){
        $topic_id = $row["topic_id"];
        $topic = $row["topic"];
        
        echo "<tr>";
        echo "<td>";
        shn_acl_secure_hyperlink('sn','ad_add_post',$topic,$stream=null,$params=array('topic_id'=>$topic_id,'forum_id'=>$forum_id),$text_opts='');
        echo "</td>";
        echo "<td>";
        shn_acl_secure_hyperlink('sn','ad_delete_topic','Delete Topic',$stream=null,$params=array('topic_id'=>$topic_id,'forum_id'=>$forum_id),$text_opts='');
        echo "</td></tr>";
        }
        echo "</table>";
        echo "<br>";
        $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
        if($page>0){
            shn_acl_secure_hyperlink('sn','ad_view_forum','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
            echo "&nbsp";
            shn_acl_secure_hyperlink('sn','ad_view_forum','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
        }
        for($i=0;$i<$page_count;$i++){
            echo "&nbsp";
            shn_acl_secure_hyperlink('sn','ad_view_forum',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
            echo "&nbsp";
        }
        if($page<($page_count-1)){
            echo "&nbsp";
            shn_acl_secure_hyperlink('sn','ad_view_forum','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
            echo "&nbsp";
            shn_acl_secure_hyperlink('sn','ad_delete_topic','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
        }
    
        shn_form_fsclose();
        
        shn_form_fsopen(_t('Create New Topic'));
        shn_form_hidden(array('forum_id'=>$forum_id));
        
        shn_form_text(_('Topic'),'topic');
            
        shn_form_fsclose();
        
        shn_form_submit(_t("Create Topic"),'name="create_topic"');
        shn_form_submit(_t("Cancel"),'name="cancel"');

        echo "<br><br>";
        shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
        shn_form_fclose();
    }
    
}

function shn_sn_ad_create_topic_cr(){
    global $global;
    $db=$global['db'];
    
    $forum_id = $_REQUEST['forum_id'];
    $topic = $_REQUEST['topic'];
    
    $topic_id = shn_create_uuid('sn_topic');
    
    if(isset($_REQUEST['create_topic'])){
        
        $sql = "INSERT INTO sn_forum_topic(forum_id,user_id,topic_id,topic) VALUES (?,?,?,?)";
        $res = $db->Execute($sql,array($forum_id,$_SESSION["user_id"],$topic_id,$topic));
        shn_sn_ad_view_forum();
    
    }else{
        
         shn_sn_ad_view_forum();
    }
}

//delete topic
function shn_sn_ad_delete_topic(){
    global $global;
    $db=$global['db'];
    
    $forum_id = $_REQUEST['forum_id'];
    $topic_id = $_REQUEST['topic_id'];
    
    echo "<h2><center>"._t("Delete Topic")."</center></h2>";

    shn_form_fopen('ad_delete_topic_cr','sn',array('req_message'=>false));

    shn_form_fsopen(_t('Delete topic'));
    shn_form_hidden(array('forum_id'=>$forum_id,'topic_id'=>$topic_id));
    
    $query2 = "SELECT topic FROM sn_forum_topic WHERE topic_id=?";
    $res2 = $db->Execute($query2,array($topic_id));
    $topic=$res2->fields["topic"];
    echo "<p>"._t("Are you sure you need to delete this topic : ".$topic."?. <br/> <br/><em>Note that all information of this topic will be deleted!</em>")."</p><br/>";
    
    shn_form_fsclose();

    shn_form_submit(_t("Delete"),'name="delete_topic"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    
    shn_form_fclose();
}

function shn_sn_ad_delete_topic_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     //$forum_id = $_REQUEST['forum_id'];
     $topic_id = $_REQUEST['topic_id'];
                 
     if(isset($_REQUEST['delete_topic'])){
            
        $query = "DELETE FROM sn_forum_topic WHERE topic_id=?";
        $res = $db->Execute($query,array($topic_id));
        
        $query2 = "DELETE FROM sn_forum_post WHERE topic_id=?";
        $res2 = $db->Execute($query2,array($topic_id));
        
        shn_sn_ad_view_forum();
          
     }else{
        
        shn_sn_ad_view_forum();
        
     }    
}

function shn_sn_ad_add_post(){
    global $global;
    $db=$global['db'];
    
    $forum_id = $_REQUEST['forum_id'];
    $topic_id = $_REQUEST['topic_id'];
    
    $query = "SELECT forum_name, description FROM sn_forums WHERE forum_id=?";
    $res = $db->Execute($query,array($forum_id));
    $forum_name= $res->fields["forum_name"];
    
    $query = "SELECT topic FROM sn_forum_topic WHERE topic_id=?";
    $res = $db->Execute($query,array($topic_id));
    $topic= $res->fields["topic"];
    
    echo "<h2><center>"._t("Add Post to Forum &nbsp::").$forum_name."&nbsp,"._t("Under the Topic ::").$topic."</center></h2>";

    shn_form_fopen('ad_add_post_cr','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id,'topic_id'=>$topic_id));

    shn_form_fsopen(_t("Availabl Post")); 
    $page=5;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    
    $q="SELECT COUNT(*) AS c FROM sn_forum_post WHERE topic_id=?";
    $rs = $db->Execute($q,array($topic_id));
    $count=$rs->fields['c'];
    $rpp=3;

    $query = "SELECT user_id, post_id, post,date FROM sn_forum_post WHERE topic_id=? ORDER BY post_id DESC";
    $rs = $db->SelectLimit($query,$rpp,$page*$rpp,array($topic_id));
    
    echo "<ul>";
    while($row=$rs->FetchRow()){  
            $query = "SELECT pu.full_name FROM person_uuid pu JOIN sn_forum_post fp ON pu.p_uuid=fp.user_id WHERE fp.user_id=?";
        $res = $db->Execute($query,array($row['user_id']));
        $full_name= $res->fields["full_name"];

        $query2 = "SELECT role_id FROM sn_forum_role WHERE user_id=?";
        $res2 = $db->Execute($query2,array($_SESSION["user_id"]));
        $role_id= $res2->fields["role_id"];

            echo "<li><div>Post by &nbsp: ".$full_name."  When the &nbsp: ".$row['date']."</div></li>";
            echo "<li><div>".$row['post']."</div></li>";
            echo "<br>";
            shn_acl_secure_hyperlink('sn','ad_edit_post','Edit',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'post_id'=>$row['post_id']),$text_opts='');
            echo"&nbsp &nbsp";
            shn_acl_secure_hyperlink('sn','ad_delete_post','Delete',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'post_id'=>$row['post_id']),$text_opts='');
            echo "<br><hr>";
    }
    echo "</ul>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_add_post','First',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_post','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_post',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_post','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_post','Last',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_form_fsopen(_t('Add New Post'));
    
    shn_form_wysiwyg(_t('New Post'), 'sn_post',array('value'=>$post));
    
    shn_form_fsclose();
   
    shn_form_submit(_t("Reply"),'name="post"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Forum admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

function shn_sn_ad_add_post_cr(){
    global $global;
    $db=$global['db'];
    
    $forum_id = $_REQUEST['forum_id'];
    $topic_id = $_REQUEST['topic_id'];
    $post = $_REQUEST['sn_post'];
    
    $post_id = shn_create_uuid('sn_post');
    $date=date("Y-m-d");
    
    if(isset($_REQUEST['post'])){
        
        if($_POST['sn_post']==null){
                add_error(_t("Please type the post"));
                shn_sn_ad_add_post();
        }else{
            $sql = "INSERT INTO sn_forum_post(forum_id,user_id,topic_id,post_id,date,post) VALUES (?,?,?,?,?,?)";
            $res = $db->Execute($sql,array($forum_id,$_SESSION["user_id"],$topic_id,$post_id,$date,$post));
            shn_sn_ad_view_forum();
        } 
    }    
    else{   

        shn_sn_ad_post_to_forum();
    }
}

//edit post
function shn_sn_ad_edit_post(){
	global $global;
    $db=$global['db'];
    
    $forum_id = $_REQUEST['forum_id'];
    $topic_id = $_REQUEST['topic_id'];
    $post_id = $_REQUEST['post_id'];
   
    echo "<h2><center>"._t("Edit Post")."</center></h2>";

    shn_form_fopen('ad_edit_post_cr','sn',array('req_message'=>false));

    shn_form_fsopen(_t('Edit Post'));
    shn_form_hidden(array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'post_id'=>$post_id));
    
    $query2 = "SELECT post FROM sn_forum_post WHERE post_id=?";
    $res2 = $db->Execute($query2,array($post_id));
    $post=$res2->fields["post"];
    echo "<p>"._t("Are you sure you need to delete this post:<br> ").$post;
    
    shn_form_fsclose();

    shn_form_fsopen(_t('Edit Post'));

    shn_form_wysiwyg(_t('New Post'), 'sn_post' , array('value'=>$post));

    shn_form_fsclose();
    
    shn_form_submit(_t("Edit"),'name="edit_post"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    
    shn_form_fclose();
		
}

function shn_sn_ad_edit_post_cr(){
    global $global;
    $db=$global['db'];

    $forum_id = $_REQUEST['forum_id'];
    $topic_id = $_REQUEST['topic_id'];
    $post_id = $_REQUEST['post_id'];
    $post = $_REQUEST['sn_post'];
    
    if(isset($_REQUEST['edit_post'])){
    	
	    if($_POST['sn_post']==null){
	        add_error(_t("Please type the post"));
	        shn_sn_ad_edit_post();
	    }else{
	        $sql = "UPDATE sn_forum_post SET post=? WHERE forum_id=? AND topic_id=? AND post_id=?";
	        $res = $db->Execute($sql,array($post,$forum_id,$topic_id,$post_id));
	        shn_sn_ad_add_post();
	        
	    }
    }else{
    	
    	shn_sn_ad_add_post();
    }
}

//delete post
function shn_sn_ad_delete_post(){
    global $global;
    $db=$global['db'];
    
    $forum_id = $_REQUEST['forum_id'];
    $topic_id = $_REQUEST['topic_id'];
    $post_id = $_REQUEST['post_id'];
    
    echo "<h2><center>"._t("Delete Post")."</center></h2>";

    shn_form_fopen('ad_delete_post_cr','sn',array('req_message'=>false));

    shn_form_fsopen(_t('Delete post'));
    shn_form_hidden(array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'post_id'=>$post_id));
    
    $query2 = "SELECT post FROM sn_forum_post WHERE post_id=?";
    $res2 = $db->Execute($query2,array($post_id));
    $post=$res2->fields["post"];
    echo "<p>"._t("Are you sure you need to delete this post :<br>").$post;
    
    shn_form_fsclose();

    shn_form_submit(_t("Delete"),'name="delete_post"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    
    shn_form_fclose();
}

function shn_sn_ad_delete_post_cr(){
     global $global;
     $db = $global['db'];
     $module = $global['module'];
     
     $post_id = $_REQUEST['post_id'];
                 
     if(isset($_REQUEST['delete_post'])){
            
        $query = "DELETE FROM sn_forum_post WHERE post_id=?";
        $res = $db->Execute($query,array($post_id));
                
        shn_sn_ad_add_post();
     }else{
        
        shn_sn_ad_add_post();
     }    
}

function shn_sn_ad_add_forum_note(){
    global $global;
    $db = $global['db'];
    
    echo "<h2><center>"._t("Add Notices to Forums")."</center></h2>";

    shn_form_fopen('ad_add_forum_note_cr','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id));

    shn_form_fsopen(_t("Available Notices")); ?>
    <div class="info"><?= _t("These are the available forum notices.");?></div>
    <?php
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM sn_forum_note";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=5;

    $note_query = "SELECT g.forum_id, g.forum_name, gn.note_id, gn.date, gn.subject, gn.note FROM sn_forums g JOIN sn_forum_note gn ON g.forum_id=gn.forum_id ORDER BY note_id DESC";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    
    echo "<ul>";
    while($row=$rs->FetchRow()){
        $forum_id = $row["forum_id"];
        $forum_name = $row["forum_name"];
        $note_id = $row["note_id"];
        $subject = $row["subject"];
        $date = $row["date"];
        $note = $row["note"];
        echo "<li> Group Name :".$forum_name." Date :".$date."</li>";
        echo "<li> Subject :".$subject."</li>";
        echo "<li> Nitice :".$note."</li>";
        shn_acl_secure_hyperlink('sn','ad_edit_forum_note','Edit',$stream=null,$params=array('forum_id'=>$forum_id,'note_id'=>$note_id),$text_opts='');
        echo "&nbsp &nbsp";
        shn_acl_secure_hyperlink('sn','ad_delete_forum_note','Delete',$stream=null,$params=array('forum_id'=>$forum_id,'note_id'=>$note_id),$text_opts='');
        echo "<hr>";
    }
    echo "</ul>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('sn','ad_add_forum_note','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_forum_note','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_forum_note',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_forum_note','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('sn','ad_add_forum_note','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
    
    shn_form_fsopen(_t('Add Notices'));
    
    $stored_forums = _shn_sn_get_stored_forums();
    shn_form_multi_select('sn_available_forum', $stored_forums,'Available Forums','','length=100%');
    
    shn_form_text(_t('subject'),'subject','');
    shn_form_wysiwyg(_t('New Notices'), 'sn_note' , array('value'=>$note));

    shn_form_fsclose();
    
    shn_form_submit(_t("Add"),'name="add_note"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

function shn_sn_ad_add_forum_note_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $sn_available_forum = $_REQUEST["sn_available_forum"];
    $subject = $_REQUEST["subject"];
    $note = $_REQUEST["sn_note"];
    $date=date("Y-m-d");
    $note_id = shn_create_uuid('sn_forum_note');
    
    if(isset($_REQUEST['add_note'])){
        if($_REQUEST["subject"]==null OR  $_REQUEST["sn_note"]==null){
            add_error("please fill the subject and note");
            shn_sn_ad_add_forum_note();
        }else{
            foreach($sn_available_forum as $forum_id){
            $sql = "INSERT INTO sn_forum_note(note_id,forum_id,subject,date,note) VALUES (?,?,?,?,?)";
            $res = $db->Execute($sql,array($note_id,$forum_id,$subject,$date,$note));
            }
            unset($_POST);
            add_confirmation(_t("Note was added successfully."));
            shn_sn_ad_manage_forums();  
        }
                 
    }else{
        shn_sn_ad_manage_forums();
    }
}

function shn_sn_ad_edit_forum_note(){
    global $global;
    $db = $global['db'];
    
    $forum_id = $_REQUEST["forum_id"];
    $note_id = $_REQUEST["note_id"];
    
    echo "<h2><center>"._t("Edit Notices of Groups")."</center></h2>";

    shn_form_fopen('ad_edit_forum_note_cr','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id,'note_id'=>$note_id));

    shn_form_fsopen(_t("Edit notices")); 
   
    $note_query = "SELECT g.forum_id, g.forum_name, gn.note_id, gn.date, gn.subject, gn.note FROM sn_forums g JOIN sn_forum_note gn ON g.forum_id=gn.forum_id WHERE gn.note_id=?";
    $rs = $db->Execute($note_query,array($note_id));
    
    echo "<ul>";
        $forum_id = $rs->fields["forum_id"];
        $forum_name = $rs->fields["forum_name"];
        $note_id = $rs->fields["note_id"];
        $subject = $rs->fields["subject"];
        $date = $rs->fields["date"];
        $note = $rs->fields["note"];
        echo "<li> Group Name :".$forum_name." Date :".$date."</li>";
        echo "<li> Subject :".$subject."</li>";
        echo "<li> Nitice :".$note."</li>";
       
    echo "</ul>";
    shn_form_fsclose();
    
    shn_form_fsopen(_t('Edit Notices'));
        
    shn_form_text(_t('subject'),'subject','',array('value'=>$subject));
    shn_form_wysiwyg(_t('New Notices'), 'sn_note' , array('value'=>$note));

    shn_form_fsclose();
    
    shn_form_submit(_t("Edit"),'name="edit_note"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
        
}

function shn_sn_ad_edit_forum_note_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $forum_id = $_REQUEST["forum_id"];
    $note_id = $_REQUEST["note_id"];
    $subject = $_REQUEST["subject"];
    $note = $_REQUEST["sn_note"];
        
    if(isset($_REQUEST['edit_note'])){
        if($_REQUEST["subject"]==null OR  $_REQUEST["sn_note"]==null){
            add_error("please fill the subject and note");
            shn_sn_ad_edit_forum_note();
        }else{
            
            $sql = " UPDATE sn_forum_note SET subject=?, note=? WHERE forum_id=? AND note_id=?";
            $res = $db->Execute($sql,array($subject,$note,$forum_id,$note_id));
           
            unset($_POST);
            add_confirmation(_t("Note was updated successfully."));
             shn_sn_ad_add_forum_note();  
        }
                 
    }else{
        shn_sn_ad_add_forum_note();
    }
    
}

function shn_sn_ad_delete_forum_note(){
    global $global;
    $db = $global['db'];
    
    $forum_id = $_REQUEST["forum_id"];
    $note_id = $_REQUEST["note_id"];
    
    echo "<h2><center>"._t("Delete Notices of Groups")."</center></h2>";

    shn_form_fopen('ad_delete_forum_note_cr','sn',$form_opts);
    shn_form_hidden(array('forum_id'=>$forum_id,'note_id'=>$note_id));

    shn_form_fsopen(_t("Delete notices")); 
    echo "<p>"._t("Are you sure you need to delete the following Notices?. <br/> <br/><em>Note that all information of Notices will be deleted!</em>")."</p><br/>";
    
    $note_query = "SELECT g.forum_id, g.forum_name, gn.note_id, gn.date, gn.subject, gn.note FROM sn_forums g JOIN sn_forum_note gn ON g.forum_id=gn.forum_id WHERE gn.note_id=?";
    $rs = $db->Execute($note_query,array($note_id));
    
    echo "<ul>";
        $forum_id = $rs->fields["forum_id"];
        $forum_name = $rs->fields["forum_name"];
        $note_id = $rs->fields["note_id"];
        $subject = $rs->fields["subject"];
        $date = $rs->fields["date"];
        $note = $rs->fields["note"];
        echo "<li> Group Name :".$forum_name." Date :".$date."</li>";
        echo "<li> Subject :".$subject."</li>";
        echo "<li> Nitice :".$note."</li>";
       
    echo "</ul>";
    shn_form_fsclose();
        
    shn_form_submit(_t("Delete"),'name="delete_note"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    echo "<br><br>";
    shn_acl_secure_hyperlink('sn','ad_manage_forums',_t('Group admin Panel'),$stream=null,$params=array(),$text_opts='');
    shn_form_fclose();
    
}

function shn_sn_ad_delete_forum_note_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $forum_id = $_REQUEST["forum_id"];
    $note_id = $_REQUEST["note_id"];
           
    if(isset($_REQUEST['delete_note'])){
        
            $sql = "DELETE FROM sn_forum_note WHERE forum_id=? AND note_id=?";
            $res = $db->Execute($sql,array($forum_id,$note_id));
           
            unset($_POST);
            add_confirmation(_t("Note was deleted successfully."));
            shn_sn_ad_add_forum_note();  
                 
    }else{
        shn_sn_ad_add_forum_note();
    }
}