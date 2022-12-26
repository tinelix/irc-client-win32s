#include "AboutDlg.h"  
#include "ETextDlg.h"
#include "Globals.h"
#include "MainWnd.h" 
#include "ConnMDlg.h"
#include "Resource.h"
#include "Commdlg.h"
#include "IRCClnt.h"
#include <winsock.h>

/* Main window class and title */
static const char MainWndClass[] = "Main Window";
           
BOOL file_opened;           
char ini_path[];
char nicknames[256];
char password[20];
char realname[256];
char server[256];
char port[5];
int recv_status;
char sock_buffer[4096] = {0};
char fulltext_buffer[65535];

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if(msg == WM_COMMAND) {
      WORD id = wParam;

      switch (id)
      {
        case ID_ABOUT:
        {
          ShowAboutDialog(hWnd);
          return 0;
        }
        case ID_CONNECT:
        {
          if(file_opened == FALSE) {
          	MessageBox(hWnd, "First you need to open the profile file.", "Tinelix IRC", MB_ICONASTERISK|MB_OK);
          } else {
          	CreateConnectionSession(server, port, hWnd);
          }
          return 0;
        }  
        case ID_NEW_PROFILE:
        {
          ShowEnterTextDialog(hWnd, "profile_name");
          return 0;
        } 
        case ID_OPEN_PROFILE:
        {
          OPENFILENAME ofn;
          char fileTitle[256];
          memset(&ofn, 0, sizeof(OPENFILENAME)); 
          ofn.lStructSize = sizeof(OPENFILENAME);            
          ofn.hwndOwner = hWnd;
          ofn.lpstrFilter = "Profile file (*.ini; *.cfg)\0*.ini;*.cfg\0All files\0*.*\0";
          ofn.nFilterIndex = 1;
          ofn.lpstrFile = ini_path;
          ofn.nMaxFile = 256;
          ofn.Flags = OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
          if(GetOpenFileName(&ofn)) { 
          	 file_opened = TRUE;
             sprintf(ini_path, "%s", ofn.lpstrFile);
          	 GetPrivateProfileString("Main", "Nicknames", "", nicknames, 256, ofn.lpstrFile);
    		 GetPrivateProfileString("Main", "Password", "", password, 20, ofn.lpstrFile);
    		 GetPrivateProfileString("Main", "Realname", "", realname, 256, ofn.lpstrFile);
    		 GetPrivateProfileString("Connection", "Server", "", server, 256, ofn.lpstrFile);
    	     GetPrivateProfileString("Connection", "Port", "", port, 5, ofn.lpstrFile);
          };
          return 0;
        }
        case IDOK:
        case IDCANCEL:
        {
          DestroyWindow(hWnd);
          return 0;
        }
        }
    } else if(msg == WM_SYSCOMMAND) {
      WORD id = wParam;

      switch (id)
      {
        /* Show "about" dialog on about system menu item */
        case ID_ABOUT:
        {
          ShowAboutDialog(hWnd);
          return 0;
        }
      }
    } else if(msg == WM_CREATE) {
      HWND dummyWnd;
      RECT rect;

      dummyWnd = CreateWindowEx(0, "STATIC", "STATIC", 0, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, NULL, NULL, g_hInstance,
                                NULL);
      GetWindowRect(dummyWnd, &rect);
      DestroyWindow(dummyWnd);

      SetWindowPos(hWnd, 0, rect.left, rect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

      return 0;
    } else if(msg == WM_SOCKMSG) {
        	recv_status = recv((SOCKET)wParam, (char*)&sock_buffer, 4095, 0);
        	if(recv_status == SOCKET_ERROR) {
        		int error_code = WSAGetLastError();
        		if(error_code != 10035) { 
	        		char error_msg_text[512];
	        		sprintf(error_msg_text, "Socket error: %d", WSAGetLastError());
	        		MessageBox(hWnd, error_msg_text, "Error", MB_OK|MB_ICONSTOP);
        		} else {
        			Sleep(100);
        		} 
        	} else {
				GetWindowText(GetDlgItem(hWnd, IDC_MSGINPUT_EDIT), fulltext_buffer, 32768);
				sprintf(fulltext_buffer, "%s%s", fulltext_buffer, sock_buffer);
        		SetWindowText(GetDlgItem(hWnd, IDC_MSGINPUT_EDIT), fulltext_buffer);
        	}                                                              
        	SetWindowText(hWnd, "Tinelix IRC Client | Connected");
        	if(recv_status == 0) {
        		MessageBox(hWnd, "Connection lost.", "Tinelix IRC", MB_OK|MB_ICONASTERISK);
        		closesocket((SOCKET)wParam);
        	}
    } else if(msg == WM_DESTROY) { 
      QuitApp();
      PostQuitMessage(0);
      return 0;
    }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL RegisterMainWindowClass()
{
  
  WNDCLASS wc;

  wc.style         = 0;
  wc.lpfnWndProc   = &MainWndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = DLGWINDOWEXTRA;
  wc.hInstance     = g_hInstance;
  wc.hIcon         = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_APPICON));
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = MainWndClass;

  return (RegisterClass(&wc)) ? TRUE : FALSE;
}

HWND CreateMainWindow()
{
  HWND hWnd = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, NULL);

  if (hWnd)
  {   
    HMENU hMenu; 
    HMENU hSysMenu;
    hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_APPMENU));
    hSysMenu = GetSystemMenu(hWnd, FALSE);
    InsertMenu(hSysMenu, 5, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
    InsertMenu(hSysMenu, 6, MF_BYPOSITION, ID_ABOUT, "About...");
    SetMenu(hWnd, hMenu);
    SetWindowText(hWnd, AppName);
  }

  return hWnd;
}
