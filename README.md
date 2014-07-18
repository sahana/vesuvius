# Sahana Vesuvius


## Vesuvius Overview

Vesuvius is focused on the disaster preparedness and response needs of the medical community, contributing to family reunification and assisting with hospital triage. Vesuvius’s development is led by the US National Library of Medicine as part of the Bethesda Hospitals Emergency Preparedness Partnership to serve area hospitals, medical facilities and jurisdictions with a need to tie intake records with missing/found persons reports submitted by the public.

## Vesuvius Deployments

The US National Library of Medicine (NLM) is using Vesuvius to support disaster preparedness and response in family reunification and hospital triage, enabling capture of photos, exchange of data across facilities for use in US-hospital-focused catastrophic situations.

While their primary mission has been to support the Bethesda Hospitals Emergency Preparedness Partnership (BHEPP), NLM has also supported the public use of the Vesuvius People Locator system for the Haiti earthquake (2010), Christchurch Earthquake (2011), and Japan Earthquake and Tsunami (2011).

A prerelease version of Vesuvius was also used by NLM as part of BHEPP’s October 15, 2009 participation in CMAX 2009 (Combined Multi-Agency eXercise). CMAX is an annual joint civilian-military exercise in the DC area, involving simulated disasters with first responders and medical providers.

## Vesuvius Features

Optimized for family reunification and assisting with hospital triage, Vesuvius’ focuses on:

* Missing Persons Reporting – Contributes to family reunification through multiple means of accepting reports and providing advanced search and filtering capabilities
* Hospital Triage Management: Provides tools to assist in local and remote hospital triage management, including photo capture and electronic notifications of patient intake records to hospitals and the person locator registry.

## Installation Instructions:

### On Windows systems
- Install an Apache server stack. (XAMPP or WAMP is recommended)
- Follow the instructions in the INSTALL file in your checked out code to get a local instance of Vesuvius up and running.
- ```.htaccess``` file:
  - If you are using XAMPP or WAMP, editing your ```apache.conf``` file and enabling mod_rewrite will enable the rewrite module for .htaccess.
  - Editing httpd.conf and setting AllowOverride All in the root folder section will prevent errors.
- You will also need to edit the php.ini in XAMPP or WAMP and set the ```short_open_tags``` option to ```On```. 

### On Linux systems

- Install an Apache server stack. (LAMP)
- Follow the instructions in the ```INSTALL``` file in your checked out code to get a local instance of Vesuvius up and running.
- ```.htaccess``` file:
  - Enable apache2 mod rewrite using the command ```sudo a2enmod rewrite```
  - ```/etc/apache2/apache2.conf``` file needs to have ```AllowOverride``` set to ```All``` under the ```DocumentRoot``` section
- You might also need to edit the php.ini in your Apache PHP installation and set the ```short_open_tags``` option to ```On```. 
