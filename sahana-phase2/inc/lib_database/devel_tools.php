<?php
function var_dump_nice($var)
{
	ob_start();
        var_dump($val);
        $output =  '<pre>'.htmlspecialchars(ob_get_contents()).'</pre>';
        ob_end_clean();
        echo $output;
}
function echo_done()
{
	return '<b><font color="green">Done</font></b><br>';
}
?>
