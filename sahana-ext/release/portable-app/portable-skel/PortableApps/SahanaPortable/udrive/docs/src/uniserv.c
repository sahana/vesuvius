// Copyright 2004 - 2007 The Uniform Server Development Team
// Runs a hidden process. Waits till it ends then next one. [windows application]
// Compile with lcc-win32
// version 1.1

#include <windows.h>
#include <stdio.h>

int main( int argc, char *argv[] )
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  if (argc>1) {
	memset(&si, 0, sizeof(si));
//    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW;
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process.
	CreateProcess( NULL,   // No module name (use command line).
        TEXT(argv[1]), // Command line.
        NULL,             // Process handle not inheritable.
        NULL,             // Thread handle not inheritable.
        FALSE,            // Set handle inheritance to FALSE.
        0,                // No creation flags.
        NULL,             // Use parent's environment block.
        NULL,             // Use parent's starting directory.
        &si,              // Pointer to STARTUPINFO structure.
        &pi );             // Pointer to PROCESS_INFORMATION structure.
    // Wait until child process exits.
	if (argc>2) {
      WaitForSingleObject( pi.hProcess, INFINITE );
	  CreateProcess( NULL, TEXT(argv[2]), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi );
	}
    // Close process and thread handles.
    CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
  }
  return 0;
}
