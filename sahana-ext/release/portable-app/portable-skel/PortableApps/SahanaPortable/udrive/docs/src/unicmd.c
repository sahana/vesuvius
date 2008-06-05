// Copyright 2004 - 2007 The Uniform Server Development Team
// File: unicmd.c
// Author: Deepak Thukral
// Date: 12/20/2006
// Usage: [FILE].exe start/stop [start options: DRIVE LETTER(char), MY SQL(string = mysql)]
// version 0.1

// Include Headers
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stddef.h>
// End include headers

// Start Server funtion. Arguments required (drive letter and mysql option)
int startServer(char drive, int opt)
{
	if(tolower(drive) == 'b' || tolower(drive) < 97 || tolower(drive) >122){
		printf("Invalid Drive Letter, plese choose [A-Z] exculding drive B");
		return 1;
	}
	drive = toupper(drive);
	char buff1[100];
	char buff2[100];
	sprintf(buff1, "Server_start.bat %c mysql 0 0", drive);
	sprintf(buff2, "Server_start.bat %c", drive);
	if(opt)
		system(buff1);
	else
		system(buff2);
	return 0;
}

// Stop Server
int stopServer(int a)
{
	system("Stop.bat");
	return 0;
}

// Print Usage
void printUsage(int a){
	printf("Usage:\n unicmd.exe start [start options: w(drive letter), mysql]\n e.g\n unicmd.exe start w mysql\n unicmd.exe stop");
	return;
}

// Main
int main(int argc, char *argv[])
{

  //Check arguments
  if(argc < 2 || argc > 4) {printUsage(1);return 0;}
  if(_tcsicmp(argv[1],"start") && _tcsicmp(argv[1],"stop")){printUsage(1);return 0;}

  //Start is supplied
  if(_tcsicmp(argv[1],"start") == 0){
	  int excode;

	  if(argc == 2){
	  	excode = startServer('w', 0);
		if(!excode)printf("Uniform Server has started successfully.");
  	  	return 0;
		}

	  if(argc == 3){
		excode = startServer(argv[2][0], 0);
		if(!excode)printf("Uniform Server has started successfully.");
  	    return 0;
		}

	  else{
		 if(argv[3] == "mysql")
		 	excode = startServer(argv[2][0], 1);
		else
			excode = startServer(argv[2][0], 0);
		}

	  if(!excode)printf("Uniform Server has started successfully.");
  	  return 0;
	}

  // Stop is supplied
  if(_tcsicmp(argv[1],"stop") == 0){
	  int excode = stopServer(1);
	  if(!excode)printf("Uniform Server has stopped successfully.");
  	  return 0;
	}
  return 0;
}



