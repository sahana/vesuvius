<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright		Lanka Software Foundation - http://www.opensource.lk
* @package		
* @subpackage	
* @tutorial		
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

function _shn_msg_add_capjs()
{
?>
<script language="JavaScript" type="text/javascript">
    
    form = document.getElementsByTagName('form')[1];
    form.restriction.disabled=true;
    form.addresses.disabled=true;
    
    function changeScope(obj)
    {
    	    form = document.getElementsByTagName('form')[1];
            
        if (obj.value=='Restricted')
        {
            form.restriction.disabled=false;
            form.addresses.disabled=true;
        }
        else if (obj.value=='Private')
        {
            form.restriction.disabled=true;
            form.addresses.disabled=false;
        }
        else
        {
        	    form.restriction.disabled=true;
            form.addresses.disabled=true;
        }
    }
    
    function addCategory(val)
    {
        form = document.getElementsByTagName('form')[1];
        if (form.info_category.value == '')
            form.info_category.value = val;
        else
            form.info_category.value += ',' + val;
    }
    
    function addResponseType(val)
    {
        form = document.getElementsByTagName('form')[1];
        if (form.info_responseType.value == '')
            form.info_responseType.value = val;
        else
            form.info_responseType.value += ',' + val;
    }
    
    function addUrgency(val)
    {
        form = document.getElementsByTagName('form')[1];
        if (form.info_urgency.value == '')
            form.info_urgency.value = val;
        else
            form.info_urgency.value += ',' + val;
    }
    
    function addEventCode(valname, val)
    {
        valname = (valname=='')?'null':valname;
        val = (val=='')?'null':val;
        
        form = document.getElementsByTagName('form')[1];
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
        
        form = document.getElementsByTagName('form')[1];
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
        
        form = document.getElementsByTagName('form')[1];
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
            form = document.getElementsByTagName('form')[1];
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
            form = document.getElementsByTagName('form')[1];
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
            form = document.getElementsByTagName('form')[1];
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
    	    form = document.getElementsByTagName('form')[1];
        
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
</script>
  
<?php
}
?>