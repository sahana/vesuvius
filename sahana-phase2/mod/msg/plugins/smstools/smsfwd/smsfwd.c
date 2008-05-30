/*
 * Daemon to Send SMSTools Received Files to Sahana Server
 *
 * Dependent on libcurl
 * To compile:	cc -o smsfwd smsfwd.c -l curl
 * To run: ./shn_sms_daemon
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 * Sahana - http://sahana.sourceforge.net
 * 
 * @author   	J P Fonseka <jo@respere.com>
 * @copyright  	Respere - http://respere.com/
 * @version 	$Id: smsfwd.c,v 1.2 2008-05-30 00:29:53 franboon Exp $
 * @package 	Sahana - http://sahana.lk/
 * @subpackage  messaging   
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 * @todo use GNU autocof to make the code portable
 * @todo move the conf values to a file
 *
 * */

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <curl/curl.h>


#define DAEMON_NAME "smsfwd"
#define RUN_AS_USER "smsd"
#define LOCK_FILE   "/var/lock/sahanasms.lock"
#define LOG_FILE    "/var/log/sahanasms.log"
#define RECEIVE_DIR "/var/spool/sms/incoming"
#define URL "localhost/index.php?mod=msg&act=receive_message&stream=text&plugin=smstools"

int remove_file=0;

void log_message(message)char *message;{
	FILE *logfile;
	logfile=fopen(LOG_FILE,"a");
	if(!logfile) return;
	fprintf(logfile,"%s\n",message);
	fclose(logfile);
}

void signal_handler(sig)int sig;{
	switch(sig) {
	case SIGHUP:
		log_message("hangup signal catched");
		break;
	case SIGTERM:
		log_message("terminate signal catched");
		exit(0);
		break;
	}
}

void daemonize(){
	int pid,sid,lfp,i;
	char str[10];
	if(getppid()==1) return; /* already a daemon */

	pid=fork();
	if (pid < 0) {
		syslog( LOG_ERR, "unable to fork daemon, code=%d (%s)", errno, strerror(errno) );
		exit(1);
	}
	/* If we got a good PID, then we can exit the parent process. */
	if (pid > 0) {
	        exit(0);
	}

	/* child (daemon) continues */
        /* Create a new SID for the child process */
        sid = setsid();
        if (sid < 0) {
                /* Log the failure */
                exit(1);
        }

	for (i=getdtablesize();i>=0;--i) close(i); /* close all descriptors */
	i=open("/dev/null",O_RDWR); dup(i); dup(i); /* handle standart I/O */
	umask(027); /* set newly created file permissions */
	chdir(RECEIVE_DIR); /* change running directory */
	lfp=open(LOCK_FILE,O_RDWR|O_CREAT,0640);
	if (lfp<0){
		syslog( LOG_ERR, "unable to open lock file " LOCK_FILE );
		exit(1); /* can not open */
	}

	if (lockf(lfp,F_TLOCK,0)<0){
		syslog( LOG_NOTICE,  DAEMON_NAME " is already running");
		exit(0); /* can not lock */
	}
	/* first instance continues */
	sprintf(str,"%d\n",getpid());
	write(lfp,str,strlen(str)); /* record pid to lockfile */


	signal(SIGCHLD,SIG_IGN); /* ignore child */
	signal(SIGTSTP,SIG_IGN); /* ignore tty signals */
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGHUP,signal_handler); /* catch hangup signal */
	signal(SIGTERM,signal_handler); /* catch kill signal */
}

void loadconf(){
	/* open the conf file */
	
	/*loop through the file for conf values */

	/* load the conf values for internal structures */
}

char *trim_left( char *szSource ){
	char *pszBOS = 0;
	// Set pointer to character before terminating NULL
	pszBOS = szSource;
	// iterate backwards until non '_' is found
	while(*pszBOS == ' ')
		*pszBOS++;
	return pszBOS;
}


size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp){
	printf("{%s}", buffer);
	if(strcmp(buffer,"received")==0)
		remove_file=1;
	return size;
}

int read_message_file(filename)char *filename;{
	FILE *fp;
	int i=0;
	char line[300],get[1024],url[2048],*esurl,*s;
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(!curl) {
		log_message("Unable to open curl connection");
		return 1; 
	}
	strcpy(get,"");
	if(chdir(RECEIVE_DIR)){
		log_message("Unable to change to receive directory.");
		return 1;
	}

	if ((fp = fopen ( filename,"r")) == NULL){
		log_message(strcpy("File could not be opened : ",filename));
		return 1;
	}
	// for safty look the file while reading
	// loop through the file and read the content line by line
	while(fgets(line,256,fp)!=NULL){
		s=strtok(line, ":");
		if( strcmp(s,"\n") == 0){
			strcat(get,"&message=");
			break;
		}
                strcat(get,"&");strcat(get,s);strcat(get,"=");
		s=strtok( NULL, "\n" );
		if(s!=NULL){
			s=trim_left(s);
			esurl=curl_easy_escape( curl , s , 0);
			strcat(get,esurl);
		}
	}
	while(fgets(line,256,fp)!=NULL){
		esurl=curl_easy_escape( curl , line , 0);
		strcat(get,esurl);
	}
	//close the file since we have finished reading
	if (fclose(fp) != 0){
		log_message("File did not exist.");
	}	
	strcpy(url,"http://" URL);
	strcat(url,get);
	printf("\n\n%s\n",url);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	res = curl_easy_perform(curl);
	/* always cleanup */
	curl_easy_cleanup(curl);

	//if the remove file flag is set to 1 remove the received file
	if(remove_file)
		remove(filename);
}


void received_dir(){
	int count,i;
	struct direct **files;
	int file_select();
 
	printf("Current Working Directory = %s\n",RECEIVE_DIR);
	count =  scandir(RECEIVE_DIR, &files, file_select, NULL);
 
	/* If no files found, make a non-selectable menu item */
	if(count <= 0){
		printf("No files in this directory\n");
		return;
	}
	printf("Number of files = %d\n",count);
	for (i=1;i<count+1;++i){
		read_message_file(files[i-1]->d_name);
	}
}

int file_select(struct direct *entry){
	if ((strcmp(entry->d_name, ".") == 0) ||(strcmp(entry->d_name, "..") == 0))
		return 0;
	else
		return 1;
}

main(){
	/* Initialize the logging interface */
	openlog( DAEMON_NAME, LOG_PID, LOG_LOCAL5 );
	syslog( LOG_INFO, "starting" );

//	daemonize();

	while(1){
		sleep(2); /* run */
		received_dir();
	}

	/* Finish up */
	syslog( LOG_NOTICE, "terminated" );
	closelog();
	return 0;
}

/* EOF */

