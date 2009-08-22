<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

function _shn_msg_add_capjs()
{
?>
<script language="JavaScript" type="text/javascript">
    
    form = document.getElementsByName('cap_new')[0];
    rest = document.getElementById('scope_rest');
    rest.style.display  = 'none';
    addr = document.getElementById('scope_addr');
    addr.style.display= 'none';
    cap_note = document.getElementById('cap_note');
    cap_note.style.display= 'none';
    
    function changeId(ogj)
    {
        form = document.getElementsByName('form')[1];
        form.identifier.value = form.status.value+"-"+form.time.value;
    }
    
    function showHideNote(obj)
    {
        cap_note = document.getElementById('cap_note');
        if (obj.value=='Cancel' || obj.value=='Error')
        {
            cap_note.style.display= '';
        }
        else
        {
            cap_note.style.display= 'none';
        }
    }
    
    function changeScope(obj)
    {
        rest = document.getElementById('scope_rest');
        addr = document.getElementById('scope_addr');
        
        if (obj.value=='Restricted')
        {
            rest.style.display  = '';
            addr.style.display= 'none';
        }
        else if (obj.value=='Private')
        {
            rest.style.display  = 'none';
            addr.style.display= '';
        }
        else
        {
            rest.style.display  = 'none';
            addr.style.display= 'none';
        }
    }
    
    function addCategory(val)
    {
        form = document.getElementsByName('cap_new')[0];
        if (form.info_category.value == '')
            form.info_category.value = val;
        else
            form.info_category.value += ',' + val;
    }
    
    function addResponseType(val)
    {
        form = document.getElementsByName('cap_new')[0];
        if (form.info_responseType.value == '')
            form.info_responseType.value = val;
        else
            form.info_responseType.value += ',' + val;
    }
    
    function addUrgency(val)
    {
        form = document.getElementsByName('cap_new')[0];
        if (form.info_urgency.value == '')
            form.info_urgency.value = val;
        else
            form.info_urgency.value += ',' + val;
    }
    
    function addEventCode(valname, val)
    {
        valname = (valname=='')?'null':valname;
        val = (val=='')?'null':val;
        
        form = document.getElementsByName('cap_new')[0];
        if (form.info_eventCode.value == '')
            form.info_eventCode.value = valname + ':' + val;
        else
            form.info_eventCode.value += ' ' + valname + ':' + val;
        
        form.valueName.value = '';
        form.value_val.value = '';
    }
    
    function addParameter(valname, val)
    {
        valname = (valname=='')?'null':valname;
        val = (val=='')?'null':val;
        
        form = document.getElementsByName('cap_new')[0];
        if (form.info_parameter.value == '')
            form.info_parameter.value = valname + ':' + val;
        else
            form.info_parameter.value += ' ' + valname + ':' + val;
        
        form.param_valueName.value = '';
        form.param_value.value = '';
    }
    
    function addResource(resDesc, mimeType, size, uri, derefUri, digest)
    {
        resDesc = (resDesc=='')?'null':resDesc;
        mimeType = (mimeType=='')?'null':mimeType;
        size = (size=='')?'null':size;
        uri = (uri=='')?'null':uri;
        derefUri = (derefUri=='')?'null':derefUri;
        digest = (digest=='')?'null':digest;
        
        form = document.getElementsByName('cap_new')[0];
        if (form.info_resource.value == '')
            form.info_resource.value = resDesc+','+mimeType+','+size+','+uri+','+derefUri+','+digest;
        else
            form.info_resource.value += '\n' + resDesc+','+mimeType+','+size+','+uri+','+derefUri+','+digest;
        
        form.info_resDesc.value = '';
        form.info_mimeType.value = '';
        form.info_size.value = '';
        form.info_uri.value = '';
        form.info_derefUri.value = '';
        form.info_digest.value = '';
    }
    
    function addCoordinates(x, y)
    {
        if (x!='' && y!='' && parseFloat(x) && parseFloat(y))
        {
            form = document.getElementsByName('cap_new')[0];
            if (form.area_poly_list.value == '')
                form.area_poly_list.value = x + ',' + y;
            else
                form.area_poly_list.value += '-' + x + ',' + y;
        }
        
        form.area_pX.value = '';
        form.area_pY.value = '';
    }
    
    function addCircle(x, y, r)
    {
        if (x!='' && y!='' && r!='' && parseFloat(x) && parseFloat(y) && parseFloat(r))
        {
            form = document.getElementsByName('cap_new')[0];
            if (form.area_crl_list.value == '')
                form.area_crl_list.value = x + ',' + y + ',' + r;
            else
                form.area_crl_list.value += '-' + x + ',' + y + ',' + r;
        }
        
        form.area_cX.value = '';
        form.area_cY.value = '';
        form.area_r.value = '';
    }
    
    function addGeocode(vn, v)
    {
        if (vn!='' && v!='')
        {
            form = document.getElementsByName('cap_new')[0];
            if (form.gc_list.value == '')
                form.gc_list.value = vn + ',' + v;
            else
                form.gc_list.value += '-' + vn + ',' + v;
        }
        
        form.gc_vn.value = '';
        form.gc_v.value = '';
    }
    
    function addArea()
    {
    	form = document.getElementsByName('cap_new')[0];
        
        poly    = form.area_poly_list.value;
        circle  = form.area_crl_list.value;
        geo     = form.gc_list.value;
        alt     = form.area_altitude.value;
        ceil    = form.area_ceiling.value;
        
        poly    = (poly=='')?'null':poly;
        circle  = (circle=='')?'null':circle;
        geo     = (geo=='')?'null':geo;
        alt     = (alt=='')?'null':alt;
        ceil    = (ceil=='')?'null':ceil;
        
        if (form.area_areaDesc!='')
        {
            if (form.info_area.value == '')
                form.info_area.value = form.area_areaDesc.value + '//' + poly + '//' + circle + '//' + geo + '//' + alt + '//' + ceil;
            else
                form.info_area.value += '\n' + form.area_areaDesc.value + '//' + poly + '//' + circle + '//' + geo + '//' + alt + '//' + ceil;
        }
        
    }
    
    function clearValue(obj)
    {
        obj.value = '';	
    }
    
//    function load_tab(tab)
//    {
//        if (tab == 'tab1')
//        {
//            tab1 = document.getElementById('tab1');
//            tab1.style.display = '';
//            
//            tab2 = document.getElementById('tab2');
//            tab2.style.display = 'none';
//            
//            tab1 = document.getElementById('tab3');
//            tab1.style.display = 'none';
//        }
//        if (tab == 'tab2')
//        {
//            tab1 = document.getElementById('tab1');
//            tab1.style.display = 'none';
//            
//            tab2 = document.getElementById('tab2');
//            tab2.style.display = '';
//            
//            tab1 = document.getElementById('tab3');
//            tab1.style.display = 'none';
//        }
//        
//        if (tab == 'tab3')
//        {
//            tab1 = document.getElementById('tab1');
//            tab1.style.display = 'none';
//            
//            tab2 = document.getElementById('tab2');
//            tab2.style.display = 'none';
//            
//            tab1 = document.getElementById('tab3');
//            tab1.style.display = '';
//        }
//        
//        if (tab == '')
//        {
//            tab1 = document.getElementById('tab1');
//            tab1.style.display = '';
//            
//            tab2 = document.getElementById('tab2');
//            tab2.style.display = 'none';
//            
//            tab1 = document.getElementById('tab3');
//            tab1.style.display = 'none';
//        }
//        
//    }
//    load_tab('tab1');
</script>
  
<?php
}
