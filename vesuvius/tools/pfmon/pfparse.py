# pfparse.py
# Author: Owen Royall-Kahin (oroyallkahin@gmail.com)

# Reads off of a person finder feed, saves the data into a database,
# and sends out an email if any new items are added to the feed.

####### Imports #######

import sys, re, shutil, smtplib, urllib, datetime
import elementtree.ElementTree as ET
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

####### Constants #######

WORKING_DIR = './'
CONFIG = WORKING_DIR + "pfparse.conf"
CURRENT_FEED = WORKING_DIR + "current.xml"
FEED_HISTORY = WORKING_DIR + "history.txt"
LOG = WORKING_DIR + "pfparse.log"
COMMASPACE = ', '
ME = "owen.royall-kahin@nih.gov"
SMTP_SERVER = "mailfwd.nih.gov"
LANGUAGE = "en"
ns = '{http://www.w3.org/2005/Atom}'
gns = '{http://schemas.google.com/personfinder/2011}'

####### Globals #######

repo_url = "http://caveofdoom.dyndns.org/other.xml"
recipients = [] #["oroyallkahin@gmail.com", "owen.royall-kahin@nih.gov"]

####### Procedures #######


def load_conf(filename):
  # modify globals with values in pfparse.conf
  file = open(filename)
  for line in file:
    if line[0] == "#":
      pass
    else:
      items = line.split("=")
      if items[0] == "url":
        global repo_url
        repo_url = items[1]
      elif items[0] == "storage":
        db = items[1].strip()
      elif items[0] == "recipients":
        global recipients
        recipients = items[1].strip().split(",")



# Timestamp log as event occurs, takes an optional message
def log(message="None"):
  
  # Initialize list to contain file lines, contains latest entry
  log_list = [str(datetime.datetime.now()) + " -Message: " +  str(message) + "\n"]
  
  try:
    # Attempt to open file
    log_file = open(LOG, "r")
    
    # Dump file contents into a list
    for line in list(log_file):
      log_list.append(line)
  
  except IOError as e:
    if e.errno == 2:
      pass
    else:
      raise Exception("Error accessing log file for reading. Reason: ", e)
  
  try:
    # Update the log file with the new contents
    log_file = open(LOG, "w")
    log_file.writelines(log_list)
    log_file.close()
    
  except Exception as e:
    raise Exception("Error accessing log file for writing. Reason: ", e)
    
  
def add_to_history():
  # Rotate feed file
  history_list = list(open(CURRENT_FEED))
  
  try:
    # Attempt to open history file
    history_file = open(FEED_HISTORY, "r")
    
    for line in history_file:
      history_list.append(line)
    
  except IOError as e:
    if e.errno == 2:
      pass
    else:
      raise Exception("Error accessing history feed for reading. Reason: ", e)
  
  try:
    # Update the feed history file.
    history_file = open(FEED_HISTORY, "w")
    history_file.writelines(history_list)
    history_file.close()
  except Exception as e:
    raise Exception("Error accessing history feed for writing. Reason: ", e)
  
# Return a set of english titles and identifiers from a feed in the form (title, key name)
# Input feeds must be in the form of an ElementTree
def get_titles(feed):
  eset = set([])
  
  # These are not needed if they are not expected to change.
  # Both the Google Schema and Atom namespace are listed at the top.
  # Get Atom XML tag 
  #ns = re.match("{.*}", feed.getroot().tag).group()

  # Get the Google Schema tag
  #gns = re.match("{.*}", repo.tag).group()
  
  
  for element in list(feed.getroot()):
    for title in element.findall(ns+'content/'+gns+'repo/'+gns+'title'):
      titlestr = title.items()
      if titlestr[0][1] == LANGUAGE:
        s = (title.text, \
element.find(ns+'id').text.split('http://google.org/personfinder/')[1])
        eset.add(s)
        break

  # Returns this set. 
  # Note that this will ignore events without posted <LANGUAGE> titles
  return eset
  

# Takes in ???
def send_email(new_entries = ["Blank"], removed_entries = ['removed']):
  msg = MIMEMultipart('alternative')
  msg['To'] = COMMASPACE.join(recipients)
  msg['From'] = ME
  msg['Subject'] = "Email Notification of PF Change"
  msg.preamble = "preamble - pf has been changed"
  msg.epilogue = "epilogue"
  
  plain = "This is a test message."
  html = """\
<html>
  <head></head>
  <body>
  <p>Hello,
  <br>This is a test message that indicates the PF feed has been changed.
  <br>The events below are in the form (title, key name)
  <br>New Feeds:<br>
""" + \
COMMASPACE.join("Title: "+entry[0] + \
", Key: "+entry[1] for entry in list(new_entries)) + \
"""
<br>Removed Feeds:<br> 
""" + \
COMMASPACE.join("Title: "+entry[0] + \
", Key: "+entry[1] for entry in list(removed_entries)) + \
"""
  </p>
  </body>
</html>
"""

  # for each item in the entry's getiterator() print tag and text
  msg.attach(MIMEText(plain, 'plain'))
  msg.attach(MIMEText(html, 'html'))
  s = smtplib.SMTP(SMTP_SERVER)
  
  s.sendmail(ME, recipients, msg.as_string())
  s.close()
  


def main():
  # Runs main program loop. 
  try:
    # Load config settings
    load_conf(CONFIG)
    
    # get feed
    new_file_path = urllib.urlretrieve(repo_url)[0]
    new = ET.parse(open(new_file_path))
    old = ET.parse(CURRENT_FEED)
    new_entries = list(get_titles(new) - get_titles(old))
    removed_entries = list(get_titles(old) - get_titles(new))
    # Check for differences
    if (new_entries or removed_entries):
      # New content detected;
      
      # Log the event
      log(new_entries)
      
      #Rotate history files
      add_to_history()
      
      # Update 'current' definitions, currently disabled for testing purposes
      #shutil.move(new_file_path, CURRENT_FEED)
      
      # Notifier options
      # Send email
      send_email(new_entries, removed_entries)
    
      # possibly update PL for a new event
      return 0
  
    return 1
  except Exception as e: # Should also except url errors, expat errors
    print "An error has occurred: ", e
    return 1
    
  return 0

if __name__ == '__main__':
  exit(main())
