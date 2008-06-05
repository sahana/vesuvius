// Copyright 2004 - 2007 The Uniform Server Development Team
// UniController Application, Starts and Stop server components.
// version 1.1

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <shellapi.h>
#include "unicontrollerres.h"


#define APPNAME			"UniController"
#define APPVERSION		"1.0Beta"
#define CORENAME			"The Uniform Server" //Editted
#define AUTHOR			"The Uniform Server Development Team" //Editted
#define URL				"http://www.uniformserver.com" //Editted

#define BTN_STARTSERVER        1
#define BTN_STOPSERVER		 2
#define EDT_MESSAGE	   	 3

#pragma comment(lib,"shell32.lib")



LRESULT CALLBACK WndProc( HWND hWnd , UINT message , WPARAM wParam , LPARAM lParam)
{
    switch(message){
    case WM_COMMAND:
        if(LOWORD(wParam)==BTN_STARTSERVER || LOWORD(wParam)==IDM_START){
			char string[256], buff1[256];
            GetDlgItemText(hWnd, EDT_MESSAGE, string, 256);
			if(string[0] == 'b' || string[0] == 'B') {
			    MessageBox(hWnd, "Cannot Start Server: Invalid Drive - B", APPNAME ,MB_OK);
				break;
			}
		    if((string[0] >= 'a' && string[0] <= 'z') || (string[0] >= 'A' && string[0] <= 'Z')){
			sprintf(buff1, "Server_start.bat %c mysql 0 0", string[0]);
			system(buff1);
            MessageBox(hWnd, "Server is running! \nplease visit http://localhost:<port>/", APPNAME ,MB_OK);
			}
			else {
				MessageBox(hWnd, "Cannot Start Server: Invalid Drive", APPNAME ,MB_OK);
				break;
			}
        }
		if(LOWORD(wParam)==BTN_STOPSERVER || LOWORD(wParam)==IDM_STOP){
			system("Stop.bat");
            MessageBox(hWnd, "Server has been stopped", APPNAME ,MB_OK);
        }
		if(LOWORD(wParam)==IDM_EXIT){
			PostQuitMessage(WM_QUIT);
		}
		if(LOWORD(wParam)==IDM_ABOUT){
			char str[1024];
			sprintf(str, "%s - %s \n\n%s \n%s \n%s", APPNAME, APPVERSION, CORENAME, AUTHOR, URL);
			MessageBox(hWnd, str, APPNAME ,MB_OK);
		}
		if(LOWORD(wParam)==IDM_UNICENTER){
			ShellExecute(NULL, "open", "http://center.uniformserver.com/?_r=menu", "", "", SW_SHOWNORMAL);
		}
		if(LOWORD(wParam)==IDM_HOME){
			ShellExecute(NULL, "open", "http://www.uniformserver.com/?_r=menu", "", "", SW_SHOWNORMAL);
		}
		//Newly Added
		if(LOWORD(wParam)==IDM_FORUM){
			ShellExecute(NULL, "open", "http://forum.uniformserver.com/?_r=menu", "", "", SW_SHOWNORMAL);
		} 
		if(LOWORD(wParam)==IDM_WIKI){
			ShellExecute(NULL, "open", "http://wiki.uniformserver.com/?_r=menu", "", "", SW_SHOWNORMAL);
		}
		//End
		if(LOWORD(wParam)==IDM_BUG){
			ShellExecute(NULL, "open", "http://sourceforge.net/tracker/?group_id=53691&atid=471253", "", "", SW_SHOWNORMAL);
		}
        break;
    }
    return DefWindowProc(hWnd,message,wParam,lParam);
}

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, INT nCmdShow)
{

    // Create A Window Class Structure
    WNDCLASSEX wc;
    wc.cbClsExtra = 0;
    wc.cbSize = sizeof(wc);
    wc.cbWndExtra = 0;
    wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
    wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK));
    wc.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK));
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = "Uni";
    wc.lpszMenuName = MAKEINTRESOURCE(IDMAINMENU);;
    wc.style = CS_VREDRAW|CS_HREDRAW|CS_OWNDC;

    // Register Window Class
    RegisterClassEx(&wc);

    // Create a Window
    HWND hWnd = CreateWindowEx(0,
        "Uni", "UniController 1.0Beta",
        WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, 100,100,400,200,
        NULL,NULL,wc.hInstance,0);

    // Create a label
    HWND text = CreateWindowEx(0,
        "STATIC", "Welcome to UniController!",
        WS_CHILD|WS_VISIBLE, 10,10,250,20,
        hWnd,NULL,NULL,0);

    // Create a label
    HWND lblDrive = CreateWindowEx(0,
        "STATIC", "Drive Letter [A Or C-Z]",
        WS_CHILD|WS_VISIBLE, 10,40,170,40,
        hWnd,NULL,NULL,0);

    HWND editDrive = CreateWindowEx(0,
    	  "EDIT", "W",
    	  WS_CHILD|WS_VISIBLE|WS_BORDER, 220,40,100,20,
    	  hWnd,(HMENU)EDT_MESSAGE,NULL,0);

    // Create a label
    HWND lblServer = CreateWindowEx(0,
        "STATIC", "Uniform Server Core",
        WS_CHILD|WS_VISIBLE, 10,80,70,40,
        hWnd,NULL,NULL,0);

    //Editted Start to Server Start
    HWND btnStart = CreateWindowEx(0,
        "BUTTON", "Server Start",
        WS_CHILD|WS_VISIBLE, 100,80,100,20,
        hWnd,(HMENU)BTN_STARTSERVER,NULL,0);

    //Editted Stop to Server Stop
    HWND btnStop = CreateWindowEx(0,
        "BUTTON", "Server Stop",
        WS_CHILD|WS_VISIBLE, 220,80,100,20,
        hWnd,(HMENU)BTN_STOPSERVER,NULL,0);

    ShowWindow(hWnd,SW_SHOW);

    // Message Loop
    MSG msg;
    while(GetMessage(&msg,hWnd,0,0)>0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


