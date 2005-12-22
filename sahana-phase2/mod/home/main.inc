<?PHP

function shn_home_view()
{ ?>

        <p><b>You called the home view action </b></p>
        <p> This is a call to view in home</p>

<?php
}

function shn_home_default()
{ ?>

    <div id="home">
    <h2>Welcome to the Sahana FOSS Disaster Management System</h2>
<!--        <img src="theme/default/img/home_pic1.png" align="left" /> -->
        <p>Sahana is an integrated set of pluggable, web based disaster management applications that provide solutions to large-scale humanitarian problems in the aftermath of a disaster. These applications and problems they address are as follows:</p>
	<ul>
	<li><b>Missing Person Registry</b> <br/>Helping to reduce trauma by effectively finding missing persons </li>
	<li><b>Organization Registry</b> <br/>Coordinating and balancing the distribution of relief organizations in the affected areas and connecting relief groups allowing them to operate as one </li>
	<li><b>Request Management System</b> <br/>Registering and Tracking all incoming requests for support and relief upto fullfilment and helping donors connect to relief requirements </li>
	<li><b>Camp Registry</b><br/>Tracking the location and numbers of victims in the various camps and temporary shelters setup all around the affected area </li>
	</ul>
    <p>For more detail see the Sahana <a href="http://www.sahana.lk">Website</a> and <a href="http://www.linux.lk/~chamindra/docs/Sahana-Brochure.pdf">Brochure</a>.
	</p>
    </div>    
    
<?php
}

?>

