<?php
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );
// needed to seperate the ISO number from the language file constant _ISO
$iso = split( '=', _ISO );
// xml prolog
echo '<?xml version="1.0" encoding="'. $iso[1] .'"?' .'>';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<?php 

// Find out how many sides are there early

$left_width = 0;
$right_width = 0;
$sides = 0;
if (mosCountModules("left")) {
	$sides++;
	$left_width = 20;
}
if (mosCountModules("right")) {
	$sides++;
	$right_width = 20;
}
$middle_width = 100 - $left_width - $right_width;

?>

	<head>
	<?php mosShowHead(); ?>
	<?php
	if ( $my->id ) {
		        initEditor();
	}
	?>

	<meta http-equiv="Content-Type" content="text/html; <?php echo _ISO; ?>" />
	<link href="<?php echo $mosConfig_live_site;?>/templates/tsunami/css/template_css.css" rel="stylesheet" type="text/css"/> 
	</head>
	
<body>

<div id="container">

<table width="100%" border="0" cellspacing="0" cellpadding="0" height="49">
        <tr> 
          <td height="49"><a href="<?php echo $mosConfig_live_site;?>/index.php" class="banner"><img src="<?php echo $mosConfig_live_site;?>/templates/tsunami/css/gov.gif" border="0"></a></td>
          <td align="right" height="49"><img src="<?php echo $mosConfig_live_site;?>/templates/tsunami/css/cnologog.gif"></td>
        </tr>
    </table>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr><td background="<?php echo $mosConfig_live_site;?>/blue.png"><img src="<?php echo $mosConfig_live_site;?>/blue.png" height="2" width="1"></td></tr>
</table>

<table id="content-body" cellspacing="10">	<!-- content-body -->
<tr>

	<?php if (mosCountModules( "left" )) { ?>
	<td id="left" width="<?=$left_width?>%" valign="top">
	<?php mosLoadModules ( 'left', -2 ); ?>
	</td>
	<?php } // end if ?>

	<td id="middle-content" width="<?=$middle_width?>%" valign="top">

		<table>

		<?php if (mosCountModules( "top" )) { ?>
		<!-- top -->
		<tr>
		<td id="top-section"><?php mosLoadModules ( 'top', -1 ); ?></td>
		</tr>
		<?php } // end if ?>

		<tr><td><?php mosMainBody(); ?></td></tr>

		<tr>
		<td id="bottom-section"><?php mosLoadModules ( 'bottom' , -2 ); ?></td>
		</tr>

		</table>
	</td>

	<?php if ( mosCountModules( "right" ) ) { ?>
	<td id="right" width="<?=$right_width?>%" valign="top">
	<?php mosLoadModules ( 'right', -2 ); ?>
	</td>
	<?php } // end if ?>

	</tr>
	</table>

</div>			<!-- / container -->

<div id="footer">	<!-- footer -->
Powered by
<a href="http://httpd.apache.org">Apache</a>, 
<a href="http://www.mysql.com">MySQL</a>,
<a href="http://www.php.net">PHP</a> and
<a href="http://www.mamboserver.com">Mambo</a> on
<a href="http://www.debian.org">Debian</a>
<a href="http://www.gnu.org">GNU</a>/<a href="http://www.kernel.org/">Linux</a>
</div>			<!-- / footer -->



</body>

</html>
