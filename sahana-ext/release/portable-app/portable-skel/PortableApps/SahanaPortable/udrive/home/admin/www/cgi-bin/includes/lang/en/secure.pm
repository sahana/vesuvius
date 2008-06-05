package secure;

# If you want to disable security check - comment the following lines with #.

if (($ENV{HTTP_REFERER}!~/^http[s]?:\/\/localhost\/apanel/)&&($ENV{HTTP_REFERER}!~/^http[s]?:\/\/127\.0\.0\.\d+\/apanel/)){
	print "
	<div id=\"main\">
	<h2>&#187; Security Alert!</h2>
	<h3>Possible Attack</h3>
	<p>
	HTTP_REFERER is not localhost, but '<b>".$ENV{HTTP_REFERER}."</b>'.
	<br />
	<br /> 
	To disable this warning go: /home/admin/www/cgi-bin/includes/lang/en/secure.pm
	<p>
	</div>"; 

require footer;

exit;
};

return 1;