<?PHP

function shn_home_view()
{ ?>

        <p><b>You called the home view action </b></p>
        <p> This is a call to view in home</p>

<?php
}

function shn_home_default()
{ ?>

    <h1 align="center">Welcome to Sahana</h1>
    <div id="home">
<!--        <img src="theme/default/img/home_pic1.png" align="left" /> -->
        <p>Sahana is an Open Source disaster management system that handles the following key problems during a disaster:
	<ul>
	<li>Efficiently posting and finding missing persons. <br/> (use the <b>Missing Person Registry</b>)</li>
	<li>Coordinating and balancing the distribution of relief organizations in the affected areas and connecting relief groups allowing them to operate as one <br/> (use the <b>Organization Registry</b>)</li>
	<li>Registering and Tracking all incoming requests for support and relief upto fullfilment and helping donors connect to relief requirements <br/> (use the <b>Request Management System</b>)</li>
	<li>Tracking the location and numbers of victims in the various camps and temporary shelters setup all around the affected area <br/> (use the <b>Camp Registry</b>)</li>
	</ul>
	</p>
    </div>    
    
<?php
}

?>

