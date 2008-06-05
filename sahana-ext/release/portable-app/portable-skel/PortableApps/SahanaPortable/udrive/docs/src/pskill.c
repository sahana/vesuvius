// Copyright 2004 - 2007 The Uniform Server Development Team
// Kills application
// version 1.1


#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stddef.h>
#include <tlhelp32.h>


enum tagErrorCodes
    {
    ERROR_SYSTEM = 2,
    ERROR_PLATFORM,
    ERROR_USAGE
    };


/*
 * type definition for application-defined callback function
 */
typedef BOOL (CALLBACK *LPCALLBACK)(DWORD, LPTSTR, LPTSTR, LPARAM);


/*
 * callback function for application-defined logic
 * return: TRUE  - to continue enumeration
 *         FALSE - to stop enumeration
 */
BOOL CALLBACK
EnumCallback(DWORD dwProcessID, LPTSTR lpProcessName,
             LPTSTR lpTargetName, LPARAM lParam)
{
    if ( _tcsicmp(lpProcessName, lpTargetName) == 0 )
        if ( (BOOL)lParam )                             // query only
            {
            _tprintf(_T("%s is running.\n"), lpProcessName);
            return FALSE;
            }
        else                                            // kill if matched
            {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,
                                          FALSE, dwProcessID);
            if ( hProcess )
                {
                TerminateProcess(hProcess, (DWORD) -1);
                CloseHandle(hProcess);
                }
            }

    return TRUE;
}


/*
 * exit the current process after printing an optional error message
 */
static void
ErrorExit(LPTSTR lpErrMsg, UINT uExitCode)
{
    if ( lpErrMsg )
        switch ( uExitCode )
            {
            case ERROR_SYSTEM:
                _tprintf(_T("System error: %s\n"), lpErrMsg);
                break;

            case ERROR_USAGE:
                _tprintf(_T("%s\n\n"), lpErrMsg);   // print an extra blank line
                break;                              // above the usage message

            default:
                _tprintf(_T("%s\n"), lpErrMsg);
                break;
            }

    // print usage on usage error regardless of lpErrMsg
    if ( uExitCode == ERROR_USAGE )
        _tprintf(_T("%s\n\n%s\n%s\n"),
                 _T("Usage: pskill <ProcessName> [c]"),
                 _T("      with c - kill the process"),
                 _T("   without c - query only"));

    ExitProcess(uExitCode);
}


/*
 * enumerate processes using PSAPI
 */
static int
EnumPSAPI(LPCALLBACK lpCallback, LPTSTR lpTargetName, LPARAM lParam)
{
    typedef BOOL  (WINAPI *LPEP)(DWORD *, DWORD, DWORD *);
    typedef BOOL  (WINAPI *LPEPM)(HANDLE, HMODULE *, DWORD, LPDWORD);
    typedef DWORD (WINAPI *LPGMBN)(HANDLE, HMODULE, LPTSTR, DWORD);

    LPEP   lpEnumProcesses;
    LPEPM  lpEnumProcessModules;
    LPGMBN lpGetModuleBaseName;

    DWORD aProcesses[1024], cbNeeded, cProcesses, i;
    BOOL  bContinue;

    HINSTANCE hDLL = LoadLibrary("psapi.dll");

    if ( !hDLL )
        ErrorExit(_T("LoadLibrary"), ERROR_SYSTEM);

    lpEnumProcesses = (LPEP)GetProcAddress(hDLL, "EnumProcesses");
    lpEnumProcessModules = (LPEPM)GetProcAddress(hDLL, "EnumProcessModules");
    lpGetModuleBaseName = (LPGMBN)GetProcAddress(hDLL, "GetModuleBaseNameA");

    if ( lpEnumProcesses && lpEnumProcessModules && lpGetModuleBaseName )
        bContinue = lpEnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);
    else
        {
        FreeLibrary(hDLL);
        ErrorExit(_T("GetProcAddress"), ERROR_SYSTEM);
        }

    if ( !bContinue )
        {
        FreeLibrary(hDLL);
        ErrorExit(_T("EnumProcesses"), ERROR_SYSTEM);
        }

    for ( i = 0, cProcesses = cbNeeded / sizeof(DWORD);
          i < cProcesses && bContinue;
          i++ )
        {
        TCHAR szProcessName[MAX_PATH] = "";
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                      FALSE, aProcesses[i]);
        if ( hProcess )
            {
            HMODULE hMod;
            DWORD cbModules;

            // get the process name, which is in the 1st module
            if ( lpEnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbModules) )
                lpGetModuleBaseName(hProcess, hMod, szProcessName, MAX_PATH);

            CloseHandle(hProcess);
            }

        // let the callback function do the application-defined logic
        // regardless of the outcome of OpenProcess
        bContinue = lpCallback(aProcesses[i], szProcessName, lpTargetName, lParam);
        }

    FreeLibrary(hDLL);
    return ( bContinue ) ? 1 : 0;
}


/*
 * enumerate processes using Tool Help
 */
static int
EnumToolHelp(LPCALLBACK lpCallback, LPTSTR lpTargetName, LPARAM lParam)
{
    typedef HANDLE (WINAPI *LPCT32S)(DWORD, DWORD);
    typedef BOOL   (WINAPI *LPP32F)(HANDLE, PROCESSENTRY32 *);
    typedef BOOL   (WINAPI *LPP32N)(HANDLE, PROCESSENTRY32 *);

    LPCT32S lpCreateToolhelp32Snapshot;
    LPP32F  lpProcess32First;
    LPP32N  lpProcess32Next;

    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;
    BOOL bContinue;

    HINSTANCE hDLL = GetModuleHandle("Kernel32.dll");

    if ( !hDLL )
        ErrorExit(_T("GetModuleHandle"), ERROR_SYSTEM);

    lpCreateToolhelp32Snapshot =
        (LPCT32S)GetProcAddress(hDLL, "CreateToolhelp32Snapshot");
    lpProcess32First = (LPP32F)GetProcAddress(hDLL, "Process32First");
    lpProcess32Next  = (LPP32N)GetProcAddress(hDLL, "Process32Next");

    if (lpCreateToolhelp32Snapshot && lpProcess32First && lpProcess32Next )
        hSnapshot = lpCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    else
        ErrorExit(_T("GetProcAddress"), ERROR_SYSTEM);

    if ( hSnapshot == INVALID_HANDLE_VALUE )
        ErrorExit(_T("CreateToolhelp32Snapshot"), ERROR_SYSTEM);

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if ( !lpProcess32First(hSnapshot, &pe32) )
        {
        CloseHandle(hSnapshot);
        ErrorExit(_T("Process32First"), ERROR_SYSTEM);
        }

    do
        {
        LPTSTR lpProcessName;

        // check if the value of szExeFile has been written to the structure
        if ( pe32.dwSize > offsetof(PROCESSENTRY32, szExeFile) )
            {
            lpProcessName = _tcsrchr(pe32.szExeFile, _T('\\'));

            // strip path, if any
            if ( lpProcessName )
                lpProcessName++;
            else
                lpProcessName = pe32.szExeFile;
            }
        else
            lpProcessName = "";

        // let the callback function do the application-defined logic
        // regardless of whether szExeFile can be retrieved or not
        bContinue = lpCallback(pe32.th32ProcessID, lpProcessName,
                               lpTargetName, lParam);

        // reset dwSize as it might have been changed by Process32First/Next
        if ( bContinue )
            pe32.dwSize = sizeof(PROCESSENTRY32);
        else
            break;
        }
    while ( lpProcess32Next(hSnapshot, &pe32) );

    CloseHandle(hSnapshot);
    return ( bContinue ) ? 1 : 0;
}


int
main(int argc, LPTSTR argv[])
{
    BOOL bQueryOnly;
    OSVERSIONINFO osvi;
    int nExitCode;

    switch ( argc )
        {
        case 1:
            ErrorExit(_T("Missing argument(s)."), ERROR_USAGE);

        case 2:
            bQueryOnly = TRUE;
            break;

        case 3:
            if ( _tcsicmp(argv[2], _T("c")) != 0 )
                ErrorExit(_T("Unrecognized option."), ERROR_USAGE);

            bQueryOnly = FALSE;
            break;

        default:
            ErrorExit(_T("Invalid number of arguments."), ERROR_USAGE);
        }

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if ( !GetVersionEx(&osvi) )
        ErrorExit(_T("GetVersionEx"), ERROR_SYSTEM);

    switch ( osvi.dwPlatformId )
        {
        case VER_PLATFORM_WIN32_NT:
            nExitCode = EnumPSAPI((LPCALLBACK)EnumCallback, argv[1], bQueryOnly);
            break;

        case VER_PLATFORM_WIN32_WINDOWS:
            nExitCode = EnumToolHelp((LPCALLBACK)EnumCallback, argv[1], bQueryOnly);
            break;

        case VER_PLATFORM_WIN32s:
            ErrorExit(_T("Win32s is not supported."), ERROR_PLATFORM);

        default:
            ErrorExit(_T("Unknown platform."), ERROR_PLATFORM);
        }

    return nExitCode;
}
