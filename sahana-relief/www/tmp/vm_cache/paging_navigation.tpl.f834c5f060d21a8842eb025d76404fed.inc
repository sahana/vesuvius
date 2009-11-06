<?php if($use_post) { ?>
	<input type="hidden" id="rpp" name="rpp" value="<?php echo($rpp); ?>" />
<?php } ?>

<center>
	<?php 
	global $global;
	require_once($global['approot'].'inc/lib_form.inc');
	 
 echo _("Page"); 
 echo($page); ?>/<?php echo($last); ?>
	:

	<?php if($page!=1) { 
 if($use_post) { ?>
			<input type="submit" name="page" value="1" />
		<?php } else { ?>
			<b><a href="<?php echo $url?>&amp;page=<?php echo $page-1;?>&amp;rpp=<?php echo $rpp;?>" title="<?php echo _("Go to Previous Page"); ?>"><?php echo _("Previous"); ?></a></b>
			<b><a href="<?php echo $url?>&amp;page=1&amp;rpp=<?php echo $rpp;?>" title="<?php echo _("Go to First Page"); ?>?>"><?php echo _("1"); ?></a></b>
		<?php } 
 } 
 if($start > 1) { ?>
	    &#8230; 
	<?php } 

	// This loop calculates and displays a range of page links (or buttons) based
	//  on the starting page and ending page, e.g., 50 51 52 53 54 55 56 57 58 59 60
	// The current page link is marked in red and is inactive. All others are either
	// numbers used as links (GET) or submit buttons with page number as label (POST).
	for($i = $start; $i <= $end; $i++) {
	    if($i == $page) {
	        echo "<span class='red'>".$i."</span>";
	    } else if($i == 1 || $i == $last) {
	    	continue;
	    } else {
	    	if($use_post) {
	    		?>
	    		<input type="submit" name="page" value="<?php echo $i; ?>" />
	    		<?php
	    	} else {
				?>
				<a href="<?php echo $url?>&amp;page=<?php echo $i?>&amp;rpp=<?php echo $rpp;?>" title="<?php echo _('Go to Page No ').$i?>"><?php echo $i?></a>
				<?php
			}
	    }
	}
	
 if($end < $last) { ?>
	    &#8230; 
	<?php } 
 if($page != $last) { 
 if($use_post) { ?>
			<input type="submit" name="page" value="<?php echo($last); ?>" />
		<?php } else { ?>
			<b><a href="<?php echo $url?>&amp;page=<?php echo $last ?>&amp;rpp=<?php echo $rpp;?>" title="<?php echo _('Go to Last Page')?>"><?php echo $last?></a></b>
			<b><a href="<?php echo $url?>&amp;page=<?php echo $page+1?>&amp;rpp=<?php echo $rpp;?>" title="<?php echo _('Go to Next Page')?>"><?php echo _('Next')?></a></b>
		<?php } 
 } 

		$rpp_options = array('3' => '3', '5' => '5','10'=>'10','20'=>'20','30'=>'30','40'=>'40','50'=>'50','100'=>'100','1000000'=>'All');
	?>

	&nbsp;
	&nbsp;
	<?php echo _("Records per page"); 
 if($use_post) { ?>
		<select onChange="document.getElementById('rpp').setAttribute('value', this.value);">
	<?php } else { ?>
		<select onChange="window.location = '<?php echo($url); ?>&amp;rpp=' + this.value">
	<?php } 
 foreach($rpp_options as $key => $value) { ?>
			<option value="<?php echo($key); ?>" <?php if($rpp == $key) echo 'selected'; ?>><?php echo($value); ?></option>
		<?php } ?>
	</select>

	<?php if($use_post) { ?>
		<input type="submit" value="<?php echo _("Update"); ?>" />
	<?php } ?>
</center>