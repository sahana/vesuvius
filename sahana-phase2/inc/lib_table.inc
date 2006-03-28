<?php
/**
* Sahana XHTML Table Library
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    framework
* @subpackage presentation
* @tutorial   comming soon!
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_html_table($body, $head = null, $foot = null, $attributes = null, $caption = null )
{
    _shn_html_table_open($attributes, $caption);

    if ($head!= null)
        shn_html_addthead($head);

    shn_html_addtbody($body);

    if ($foot != null)
        shn_html_addthead($foot);

    _shn_html_table_close();
}

function shn_html_addtbody($rows)
{
    _shn_html_tbody_open();

    foreach ($rows as $row)
    {
        shn_html_addtr($row);
    }

    _shn_html_tbody_close();
}

function shn_html_addthead($rows)
{
    _shn_html_thead_open();

    foreach ($rows as $row)
    {
        shn_html_addtr($row);
    }

    _shn_html_thead_close();
}

function shn_html_addtfoot($rows)
{
    _shn_html_tfoot_open();

    foreach ($rows as $row)
    {
        shn_html_addtr($row);
    }

    _shn_html_tfoot_close();
}

function shn_html_addtr($cols)
{
    _shn_html_tr_open();

    foreach ($cols as $col)
    {
        shn_html_addtd($col);
    }

    _shn_html_tr_close();
}

function shn_html_addtd($data, $colspan = null, $rowspan = null, $scope = null)
{
    $str_attr = '';

    if(isset($colspan))
        $str_attr .= 'colspan="' . $colspan . '" ';

    if(isset($rowspan))
        $str_attr .= 'rowspan="' . $rowspan . '" ';

    if($scope == 'row' || $scope == 'col')
        $str_attr .= 'scope="' . $scope . '" ';

?>
            <td <?=$str_attr?>><?=$data?></td>
<?php
}

function shn_html_addth($data, $colspan = null, $rowspan = null, $scope = null)
{
    $str_attr = '';

    if(isset($colspan))
        $str_attr .= 'colspan="' . $colspan . '" ';

    if(isset($rowspan))
        $str_attr .= 'rowspan="' . $rowspan . '" ';

    if($scope == 'row' || $scope == 'col')
        $str_attr .= 'scope="' . $scope . '" ';

?>
            <th <?=$str_attr?>><?=$data?></th>
<?php
}



function _shn_html_table_open($attributes = null,$caption = null)
{
    $str_attr = '';

    if(isset($attributes['id']))
        $str_attr .= ' id="' . $attributes['id'] . '"';

    if(isset($attributes['class']))
        $str_attr .= ' class="' . $attributes['class'] . '"';

    if(isset($attributes['summary']))
        $str_attr .= ' summary="' . $attributes['summary'] . '"';

?>
    <table<?=$str_attr?>>
<?php
    if (isset($caption))
    {
?>
        <caption><?=$caption?></caption>
<?php
    }
}

function _shn_html_table_close()
{
?>
    </table>
<?php
}

function _shn_html_thead_open()
{
?>
        <thead>
<?php
}

function _shn_html_thead_close()
{
?>
        </thead>
<?php
}

function _shn_html_tbody_open()
{
?>
        <tbody>
<?php
}

function _shn_html_tbody_close()
{
?>
        </tbody>
<?php
}

function _shn_html_tfoot_open()
{
?>
        <tfoot>
<?php
}

function _shn_html_tfoot_close()
{
?>
        </tfoot>
<?php
}



function _shn_html_tr_open()
{
?>
        <tr>
<?php
}


function _shn_html_tr_close()
{
?>
        </tr>
<?php
}

?>
