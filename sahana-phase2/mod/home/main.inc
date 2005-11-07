<?PHP

function shn_home_view()
{ ?>

        <p><b>You called the home view action </b></p>
        <p> This is a call to view in home</p>

<?php
}

function shn_home_default()
{ ?>

    <h1 align="center">Welcome to the Sahana Home Page</h1>
    <div id="resulthome">
        <img src="theme/default/img/home_pic1.png" align="left" />
		<img src="theme/default/img/home_pic2.png" align="right" />
        <p>Sahana is an Open Source disaster management system that handles missing/displaced persons, organisation management, camp management, assistance trading system, etc during a disaster situation.</p>
        <p>It was initial built to support relief operations during the Dec 2004 Asian Tsunami.</p>
    </div>    
    
<?php
}

?>

