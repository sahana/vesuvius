<?php
	/**
	 *
	 * PHP version 5
	 *
	 * LICENSE: This source file is subject to LGPL license
	 * that is available through the world-wide-web at the following URI:
	 * http://www.gnu.org/copyleft/lesser.html
	 *
	 * @package    Sahana - http://sahana.sourceforge.net
	 * @author     Kethees <sdkethees@gmail.com>
	 * @copyright  Lanka Software Foundation - http://www.opensource.lk
	 */

	include_once $global['approot']. '/3rd/php-ofc-library/open_flash_chart_object.php';
	include_once $global['approot'] .'/3rd/php-ofc-library/open-flash-chart.php';
	
	/**
	 * Function to include open flash chart
	 */
	
	function shn_draw_chart($width, $height, $data_file_url)
	{
	    $base = 'res/ofc/';
	    open_flash_chart_object($width, $height,$data_file_url,true,$base);
	}



