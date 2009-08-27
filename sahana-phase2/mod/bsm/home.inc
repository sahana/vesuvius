<h1 align="center"><?php print _("Biosurveillance Module"); ?> </h1>
    <div class="info"><?=_("Module is geared for recording and detecting diseases by analysisng the case data over geographical or temporal spread,
     curretly for the human species but extendible to other species like animals and crops (future work). The User Interfaces are particitioned in to
    managment of entities, detection analysis for disease surveillance, and stadnrad periodic reports");?></div><br/><br/>
     <h2><?=_("Synopsis of the entities, their relevance, and relationship ");?></h2>
    <table>
    <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=location'.'">'._("Location").'</a>';?></td>
        <td><?=_("Each person, facility, case, and service can be tagged with a location for geospatial analysis. Locations are grouped categorically
                (e.g. Health location structure, Governance location structure, Judicial location structure) and by type (e.g. National, Provincial,
                Ditrict, Divisional, Tribunal, etc) with a hierarchical chain defining the parent and child relationships. ");?>
        </td></tr>
    <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=service'.'">'._("Service").'</a>';?></td>
        <td><?=_("Especially Healt Care Workers and Facilities are associated with providing services such as at the time of detecting a significan disease
                a hospital (facility) reporting to the Medical Officer of Health who intern is assigned the task of verifying the detected notifiabledisease
                and inspecting the patient residence. These services (or tasks) can be monotored through the service sub module.");?>
    </td></tr>
        <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=person'.'">'._("Person").'</a>';?></td>
        <td><?=_("Typically there are two categories of persons: Healthcare Workers and Patients (or if used for animals:
            Healthcare Workers + Vetenarians, and Animal Patients. The module allows the implementers to define the 
            categories and the associated types for each category at will.");?><br/></td></tr>
     <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=facility'.'">'._("Facility").'</a>';?></td>
        <td><?=_("Hospitals, Clinic, Laboratories, Maternity Homes, etc are defined as facilities. Cases, Persons, and Services are associated with Facilities.
                The user may define the facility types (General Hospital, District Hospital, etc as well as identify the address and contact details of a Facility.
                When recording a case the user may identfy the facility the case was reported. Thereby, allowing follow up of the case if required.");?>
        </td></tr>
    <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=disease'.'">'._("Diagnosis").'</a>';?></td>
        <td><?=_("Diagnosis is the prociess of identifying the disease of a subject based on the presented syndrome (symptoms and signs). This section provides the user
                with the interfaces to define the diseases and assocaited signs, symptoms, and causality factors. When constructing a case the user has the option of defining
                the disease and signs but mandetorily identify the symptoms presented by the patient regardless of a diagnosis.");?>
        </td></tr>
     <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=cases'.'">'._("Cases").'</a>';?></td>
        <td><?=_("A patient will report their symptoms to a physician who will record the signs and diagnose the disease, if possible. This historic information is recorded
                as a case associated with a facility, location, person along with medical diagnosis disease and syndrome information. Each case may be assigned a series of services
                such as visiting the patient residence, laboratory testing, periodic care procedures, etc.");?>
        </td></tr>
     </table>


