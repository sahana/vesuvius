#!/usr/bin/perl

require header;
require secure;

print <<ENDDD;
      <script language="JavaScript">
      <!--
      window.location = '../../../../start.php';
      // -->
      </script>
      </p>
      </div>
ENDDD

#===MPG=== Perl just runs it no problem

exec '/usr/local/apache2/bin/Apache.exe -k restart';

require footer;

exit;