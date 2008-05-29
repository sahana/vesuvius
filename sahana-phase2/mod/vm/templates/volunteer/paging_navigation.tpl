{if $use_post}
	<input type="hidden" id="rpp" name="rpp" value="{$rpp}" />
{/if}

<center>
	{php}
	global $global;
	require_once($global['approot'].'inc/lib_form.inc');
	{/php}

	_("Page")
	{$page}/{$last}
	:

	{if $page!=1}
		{if $use_post}
			<input type="submit" name="page" value="1" />
		{else}
			<b><a href="<?php echo $url?>&amp;page=<?php echo $page-1;?>&amp;rpp=<?php echo $rpp;?>" title="_("Go to Previous Page")">_("Previous")</a></b>
			<b><a href="<?php echo $url?>&amp;page=1&amp;rpp=<?php echo $rpp;?>" title="_("Go to First Page")?>">_("1")</a></b>
		{/if}
	{/if}


	{if $start > 1}
	    &#8230; {* ellipsis *}
	{/if}

	<?php
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
	?>

	{if $end < $last}
	    &#8230; {* ellipsis *}
	{/if}

	{if $page != $last}
		{if $use_post}
			<input type="submit" name="page" value="{$last}" />
		{else}
			<b><a href="<?php echo $url?>&amp;page=<?php echo $last ?>&amp;rpp=<?php echo $rpp;?>" title="<?php echo _('Go to Last Page')?>"><?php echo $last?></a></b>
			<b><a href="<?php echo $url?>&amp;page=<?php echo $page+1?>&amp;rpp=<?php echo $rpp;?>" title="<?php echo _('Go to Next Page')?>"><?php echo _('Next')?></a></b>
		{/if}
	{/if}

	<?php
		$rpp_options = array('3' => '3', '5' => '5','10'=>'10','20'=>'20','30'=>'30','40'=>'40','50'=>'50','100'=>'100','1000000'=>'All');
	?>

	&nbsp;
	&nbsp;
	_("Records per page")
	{if $use_post}
		<select onChange="document.getElementById('rpp').setAttribute('value', this.value);">
	{else}
		<select onChange="window.location = '{$url}&amp;rpp=' + this.value">
	{/if}
		{foreach $rpp_options as $key => $value}
			<option value="{$key}" <?php if($rpp == $key) echo 'selected'; ?>>{$value}</option>
		{/foreach}
	</select>

	{if $use_post}
		<input type="submit" value="_("Update")" />
	{/if}
</center>