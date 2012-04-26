<?
/**
 * @name         Interactive Notification Wall (Search)
 * @version      21
 * @package      inw
 * @author       Merwan Rodriguez <rodriguezmer@mail.nih.gov>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */

if (isset($_GET['l'])) {
    $l = $_GET['l'];
} else {
    $l = "en";
}
if ($l != "en" && $l != "fr" && $l != "ht" && $l != "sp") {
    $l = "en";
}

// English
if ($l == "en") {
	define("TITLE_STRING",    "Chile Earthquake People Locator");
	define("ONE_LINER",       "A beta project of the U.S. National Library of Medicine");
	define("TWO_LINER",       "Lister Hill National Center for Biomedical Communications");
	define("HOME",            "Home");
	define("HOW_DO_I_REPORT", "How do I report?");
	define("HOW_DO_I_USE",    "How do I use this site?");
	define("WHAT_NOW",        "For a person below: What do I do now?");
	define("RESOURCES",       "Additional Resources");
	define("CONTACT_ABOUT",   "Contact/About Us");
	define("ALIVE_AND_WELL",  "Alive and Well");
	define("MISSING",         "Missing");
	define("FOUND",           "Found");
	define("INJURED",         "Injured");
	define("DECEASED",        "Deceased");
	define("GENDER",          "Gender");
	define("MALE",            "Male");
	define("FEMALE",          "Female");
	define("OTHER_UNKNOWN",   "Unknown");
	define("AGE",             "Age");
	define("ADULT",           "Adult");
	define("UNKNOWN",         "Unknown");
	define("SEARCH",          "Search");
	define("CLEAR",           "Clear");
	define("PAUSE",           "Pause");
	define("PLAY",            "Play");
	define("DEFAULT_SEARCH",  "Enter a name...");
	define("SEARCHING",       "Searching...");
	define("MATCHES_FROM",   "matches from");
	define("TOTAL_RECORDS",   "total records");
	define("DEFAULT_STATUS_LINE_2A", "Notice: Submission of information is voluntary. All submitted information will be made publicly available.");
	define("DEFAULT_STATUS_LINE_2B", "OMB NO: 0925-0612 EXPIRATION DATE: 7/31/2010");
	define("DEFAULT_STATUS_LINE_2C", "Public reporting burden for this collection of information is estimated to average 0.08 hours per response. This estimate includes the time for reviewing instructions, gathering, and entering data. An agency may not conduct or sponsor, and a person is not required to respond to, a collection of information unless it displays a currently valid OMB control number. Send comments regarding this burden estimate or any other aspect of this collection of information, including suggestions for reducing this burden, to: NIH, Project Clearance Branch, 6705 Rockledge Drive, MSC 7974, Bethesda, MD 20892-7974, ATTN: PRA (0925-0612). Do not return the completed form to this address.");

	define("DEFAULT_STATUS_MOUSE", "Move your mouse over an image to see more detailed information about the person here.");
	define("STATUS_NO_MATCHES_FOUND", "No matches found.");
	define("STATUS_LINE1_NAME", "Name");
	define("STATUS_LINE1_INFOLINE", "Email Subject Line");
	define("STATUS_LINE1_STATUS", "Status");
	define("STATUS_LINE1_LOCATION", "Location");
	define("STATUS_LINE2_WHEN", "When Reported"); // was Reported at
	define("STATUS_LINE2_ID", "ID");
	define("STATUS_LINE2_COMMENTS", "Comments");


// French
} else if ($l == "fr") {
	define("TITLE_STRING",    "Recherche de victimes du s&eacute;isme en Ha&iuml;ti");
	define("ONE_LINER",       "Un projet b&ecirc;ta de la biblioth&egrave;que nationale de m&eacute;decine aux &Eacute;tats-Unis");
	define("TWO_LINER",       "(U.S. National Library of Medicine - Lister Hill National Center for Biomedical Communications)");  // Don't bother translating LHNCBC here
	define("HOME",            "Accueil");
	define("HOW_DO_I_REPORT", "Comment signaler une victime?");
	define("HOW_DO_I_USE",    "Comment utiliser ce Site?");
	define("WHAT_NOW",        "For a person below: What do I do now?"); // TO DO
	define("RESOURCES",       "Autres Ressources");
	define("CONTACT_ABOUT",   "Contactez-nous/Qui sommes nous?");
	define("MISSING",         "Disparu");
	define("ALIVE_AND_WELL",  "En vie");
	define("FOUND",           "Trouv&eacute;");
	define("INJURED",         "Bless&eacute;");
	define("DECEASED",        "D&eacute;c&eacute;d&eacute;");
	define("GENDER",          "Sexe");
	define("MALE",            "Masculin");
	define("FEMALE",          "F&eacute;minin");
	define("OTHER_UNKNOWN",   "Inconnu");
	define("AGE",             "&Acirc;ge");
	define("ADULT",           "Adulte");
	define("UNKNOWN",         "Inconnu");
	define("SEARCH",          "Rechercher");
	define("CLEAR",           "Effacer");
	define("PAUSE",           "Pause");
	define("PLAY",            "Lire");
	define("DEFAULT_SEARCH",  "Nom et/ou pr&eacute;nom...");
	define("SEARCHING",       "Recherche...");
	define("MATCHES_FROM",    "r&eacute;sultats provenant d&rsquo;un total de");
	define("TOTAL_RECORDS",   "signalements");
	define("DEFAULT_STATUS_LINE_2A", "Avis: Les informations sont recueillies sur la base du volontariat. Toute information soumise sera rendue publique.");
	define("DEFAULT_STATUS_LINE_2B", "OMB NB: 0925-0612 DATE D&rsquo;EXPIRATION DATE: 7/31/2010");
	define("DEFAULT_STATUS_LINE_2C", "Le co&ucirc;t de cette collecte d&rsquo;information est estim&eacute; en moyenne &agrave; 0.08 heures par r&eacute;ponse.
	Cette estimation tient compte du temps n&eacute;cessaire Ã  la consultation des instructions, &agrave; la collecte et &agrave; la soumission des donn&eacute;es.
	Aucune collecte d&rsquo;information ne peut &ecirc;tre effectu&eacute;e ou parrain&eacute;e par un organisme,
	et aucun individu ne peut &ecirc;tre sollicit&eacute; pour une telle collecte sans l&rsquo;obtention d&rsquo;un num&eacute;ro de contr&ocirc;le ORB en cours de validit&eacute;.
	Tout commentaire concernant cette estimation de co&ucirc;t ou tout autre aspect de la collecte d&rsquo;information (y compris des suggestions de r&eacute;ductions des co&ucirc;t) &agrave; :&nsp;
	NIH, Project Clearance Branch, 6705 Rockledge Drive, MSC 7974, Bethesda, MD 20892-7974, ATTN: PRA (0925-0612).
	Ne pas envoyer de formulaire d&rsquo;information &agrave; cette adresse.");
	define("DEFAULT_STATUS_MOUSE", "Passer la souris sur une image pour obtenir des informations sur la personne photographi&eacute;e.");
	define("STATUS_NO_MATCHES_FOUND", "Aucun r&eacute;sultat trouv&eacute;.");
	define("STATUS_LINE1_NAME", "Nom et/ou Pr&eacute;nom");
	define("STATUS_LINE1_INFOLINE", "Sujet d&rsquo;un Courriel");
	define("STATUS_LINE1_STATUS", "Statut");
	define("STATUS_LINE1_LOCATION", "Position");
	define("STATUS_LINE2_WHEN", "Date et Heure du Signalement");
	define("STATUS_LINE2_ID", "Num&eacute;ro d&rsquo;Identification");
	define("STATUS_LINE2_COMMENTS", "Commentaires");

  //SPANISH
} else if ($l == "sp") {
	define("TITLE_STRING",    "Buscador de Personas: Terremoto en Chile");
	define("ONE_LINER",       "Un proyecto beta de la Biblioteca Nacional de Medicina de EE.UU.");
	define("TWO_LINER",       "Lister Hill National Center for Biomedical Communications");
	define("HOME",            "Inicio");
	define("HOW_DO_I_REPORT", "¿C&oacute;mo puedo informar?");
	define("HOW_DO_I_USE",    "¿C&oacute;mo se usa este sitio?");
	define("WHAT_NOW",        "Para una persona a continuaci&oacute;n: ¿Qu&eacute; hago ahora?");
	define("RESOURCES",       "Recursos Adicionales");
	define("CONTACT_ABOUT",   "Cont&aacute;ctenos. ¿Qui&eacute;nes somos?");
	define("ALIVE_AND_WELL",  "Vivo y Bien");
	define("MISSING",         "Desaparecido");
	define("FOUND",           "Encontrado");
	define("INJURED",         "Herido");
	define("DECEASED",        "Fallecido");
	define("GENDER",          "Sexo");
	define("MALE",            "Macho");
	define("FEMALE",          "Hembra");
	define("OTHER_UNKNOWN",   "Desconocido");
	define("AGE",             "Edad");
	define("ADULT",           "Adulto");
	define("UNKNOWN",         "Desconocido");
	define("SEARCH",          "B&uacute;squeda");
	define("CLEAR",           "Limpiar");
	define("PAUSE",           "Pausa");
	define("PLAY",            "Iniciar");
	define("DEFAULT_SEARCH",  "Ingresar un nombre...");
	define("SEARCHING",       "Buscando...");
	define("MATCHES_FROM",    "coincidentes de");
	define("TOTAL_RECORDS",   "registro(s)");
	define("DEFAULT_STATUS_LINE_2A", "Aviso: Presentaci&oacute;n de la informaci&oacute;n es voluntaria. Toda la informaci&oacute;n presentada se har&aacute; disponible al p&uacute;blico.");
	define("DEFAULT_STATUS_LINE_2B", "OMB NO: 0925-0612 FECHA DE VENCIMIENTO: 7/31/2010");
	define("DEFAULT_STATUS_LINE_2C", "La carga p&uacute;blica para la recopilaci&oacute;n de informaci&oacute;n se estima en un promedio de 0,08 horas por respuesta. Esta estimaci&oacute;n incluye el tiempo para revisar las instrucciones, la recolecci&oacute;n y la entrada de datos. Una agencia no puede realizar o patrocinar, y una persona no est&aacute; obligada a responder a, una colecci&oacute;n de informaci&oacute;n a menos que muestre un n&uacute;mero de control OMB en vigor. Enviar comentarios sobre esta estimaci&oacute;n de tiempo o cualquier otro aspecto de esta recopilaci&oacute;n de informaci&oacute;n, incluidas sugerencias para reducir esta carga, a: NIH, Project Clearance Branch, 6705 Rockledge Drive, MSC 7974, Bethesda, MD 20892-7974, Atenci&oacute;n: PRA (0925 -0612). No devuelva el formulario completo a esta direcci&oacute;n.");
	define("DEFAULT_STATUS_MOUSE", "Mueva el puntador sobre una imagen para ver informaci&oacute;n m&aacute;s detallada acerca de la persona aquí.");
	define("STATUS_NO_MATCHES_FOUND", "No se econtraron resultados.");
	define("STATUS_LINE1_NAME", "Nombre");
	define("STATUS_LINE1_INFOLINE", "Asunto");
	define("STATUS_LINE1_STATUS", "Estado");
	define("STATUS_LINE1_LOCATION", "Ubicaci&oacute;n");
	define("STATUS_LINE2_WHEN", "&iquest;Cuando se reporto?"); // was Reported at
	define("STATUS_LINE2_ID", "ID");
	define("STATUS_LINE2_COMMENTS", "Commentarios");


// end spanish
}

define("L", $l);
