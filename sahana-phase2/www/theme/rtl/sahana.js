//function used to expand or collaps the mod_sub_menu.
function switchLogin(from,to){
	var fromBlock=document.getElementById(from).style;
	var toBlock=document.getElementById(to).style;
	fromBlock.display='none';
	toBlock.display='block';
}

//function used to hide/show a DIV
function switchMode(from,to,mode_var,new_value){
	var mode_tmp=document.getElementsByName("mode");
	var fromBlock=document.getElementById(from).style;
	var toBlock=document.getElementById(to).style;
	fromBlock.display='none';
	toBlock.display='block';
	mode_tmp[0].value=new_value;

}
//function used to expand or collaps the mod_sub_menu.
function expand(id,el){
	var menu=document.getElementById(id).style;
	if(menu.display=='block')
	{
         el.className='smopen';
		menu.display='none';
        removeMenu(id);
	} 
	else{
        el.className='smclose';
		menu.display='block';
        addMenu(id);	
	}
}

function changeClass(el){
    var a=el.parentNode.getElementsByTagName('a');
    a[0].className='smclose';
}
//function used to show the mod sub menus in startup
function showMem(){
    var list=getMenuList();
    var el;
    for (var i=0;i<list.length;i++){
        if(list[i]=='')continue;
    //        alert(list[i]);
        el=document.getElementById(list[i]);
        if(el)
        {
            //el.className='smclose';
            changeClass(el);
            el.style.display='block';
        }
        else
            removeMenu(list[i]);
    }
}

function addMenu(id)
{
    var list=getMenuList();
    var st='';
    for (var i=0;i<list.length;i++){
        if(list[i]==id||list[i]=='')continue;
        st=st+list[i]+"|";
    }
    st=st+id;
    //alert(st);
    document.cookie = "menulist="+st+" ; path=/";    
}

function removeMenu(id)
{
    var list=getMenuList();
    var st='';
    for (var i=0;i<list.length;i++){
        if(list[i]==id||list[i]=='')continue;
        st=st+list[i]+"|";
    }
    //alert(st);
    document.cookie = "menulist="+st+" ; path=/";
}

function getMenuList()
{
    var nameEQ = "menulist=";
    var namelist="";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++)
    {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) 
        namelist=c.substring(nameEQ.length,c.length);
    }
    return namelist.split('|');
}

