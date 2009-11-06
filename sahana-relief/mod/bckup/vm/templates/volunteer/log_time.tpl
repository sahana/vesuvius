<h1>Log Time for {$info.full_name} on {$pos_title} for {$proj_name}</h1>
<form action="?mod=vm&amp;act=volunteer&amp;vm_action=process_log_time" method="post">
	<input type="hidden" name="mod" value="vm" />
	<input type="hidden" name="act" value="volunteer" />
	<input type="hidden" name="vm_action" value="process_log_time" />
	<input type="hidden" name="p_uuid" value="{$p_uuid}" />
	<input type="hidden" name="pos_id" value="{$pos_id}" />
	<div>
		<div style="display: table;">
		<h3>Start</h3>
		_("Date:") <input type="text" name="startDate" value="{$nowDate}" size="10" />
		_("Time:") <input type="text" name="startTime" value="{$startTime}" size="10" />
		</div>
		<div style="display: table;">
		<h3>End</h3>
		_("Date:") <input type="text" name="endDate" value="{$nowDate}" size="10" />
		_("Time:") <input type="text" name="endTime" id="endTime" value="" size="10" />
		[<a href="#" onClick="
			var now = new Date();
			var hours = now.getHours();
			var minutes = now.getMinutes();
			var ampm = hours >= 12? 'pm':'am';

			if(hours == 0)
				hours = 12;
			else if(hours > 12)
				hours -= 12;

			if(minutes < 10)
				minutes = '0' + minutes;

			nowTime = hours + ':' + minutes + ' ' + ampm;
			document.getElementById('endTime').value = nowTime;">_("now")</a>]<br />
		_("or # hours:") <input type="text" name="numHours" size="3" />
		</div>
	</div>
	<input type="submit" value="Log time" />
	<input type="button" value="cancel" onClick="history.go(-1);" />
</form>
