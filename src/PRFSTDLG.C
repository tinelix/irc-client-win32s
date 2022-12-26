#include "PrfStDlg.h"
#include "Globals.h"
#include "Resource.h" 
#include <windows.h>
#include <string.h>

HWND pageViewerHwnd;
HWND parentHwnd;
WNDPROC prstPagesCallback;
char ini_path[256]; 
char profile_name[8];
char current_page[32];   

BOOL CALLBACK ProfileSettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_COMMAND:
    {
      WORD id = wParam;

      switch (id)
      {
        case IDOK:
        {
	        if(!strcmp(current_page, "main")) {
				char nicknames[256];
				char password[20];
				char realname[256];
				HWND editText = GetDlgItem(pageViewerHwnd, IDC_NICKNAMES_EDIT);
	          	GetWindowText(editText, nicknames, 256);
	          	editText = GetDlgItem(pageViewerHwnd, IDC_PASSWORD_EDIT);
	          	GetWindowText(editText, password, 20);
	          	editText = GetDlgItem(pageViewerHwnd, IDC_REALNAME_EDIT);
	          	GetWindowText(editText, realname, 20);
	          	WritePrivateProfileString("Main", "Nicknames", nicknames, ini_path);
	  			WritePrivateProfileString("Main", "Password", password, ini_path);
	  			WritePrivateProfileString("Main", "Realname", realname, ini_path); 		
			} else if(!strcmp(current_page, "connection")) {
			    char server[256];
				char port[5];
				HWND editText = GetDlgItem(pageViewerHwnd, IDC_PROFILE_SERVER_EDIT);
	          	GetWindowText(editText, server, 256);
	          	editText = GetDlgItem(pageViewerHwnd, IDC_PROFILE_PORT_EDIT);
	          	GetWindowText(editText, port, 5);
	          	WritePrivateProfileString("Main", "Server", server, ini_path);
	  			WritePrivateProfileString("Main", "Port", port, ini_path);
			}
        }
        case IDCANCEL:
        {
          EndDialog(hwndDlg, id);
          return TRUE;
        }
      }
      break;
    }
    case WM_INITDIALOG:
    {
      return TRUE;
    }
  }

  return FALSE;
} 

LRESULT CALLBACK PrStPagesComboProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if(uMsg == WM_COMMAND) {
		WORD id = wParam;
	    if(id == 1000) {
	    	char debug_str[40];
	    	int index = SendMessage(hWnd, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
		    if(!strcmp(current_page, "main")) {
				char nicknames[256];
				char password[20];
				char realname[256];
				HWND editText = GetDlgItem(pageViewerHwnd, IDC_NICKNAMES_EDIT);
	          	GetWindowText(editText, nicknames, 256);
	          	editText = GetDlgItem(pageViewerHwnd, IDC_PASSWORD_EDIT);
	          	GetWindowText(editText, password, 20);
	          	editText = GetDlgItem(pageViewerHwnd, IDC_REALNAME_EDIT);
	          	GetWindowText(editText, realname, 20);
	          	WritePrivateProfileString("Main", "Nicknames", nicknames, ini_path);
	  			WritePrivateProfileString("Main", "Password", password, ini_path);
	  			WritePrivateProfileString("Main", "Realname", realname, ini_path); 		
			} else if(!strcmp(current_page, "connection")) {
			    char server[256];
				char port[5];
				HWND editText = GetDlgItem(pageViewerHwnd, IDC_PROFILE_SERVER_EDIT);    
	          	GetWindowText(editText, server, 256);
	          	editText = GetDlgItem(pageViewerHwnd, IDC_PROFILE_PORT_EDIT);
	          	GetWindowText(editText, port, 5);
	          	WritePrivateProfileString("Main", "Server", server, ini_path);
	  			WritePrivateProfileString("Main", "Port", port, ini_path);
			}
			EndDialog(pageViewerHwnd, 0);
			if(index == 0) {
				pageViewerHwnd = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_PCONN_STGSPAGE), parentHwnd, NULL);
	  			ShowWindow(pageViewerHwnd, SW_SHOWNORMAL);
	  			SetProfileSettingsUiFont(hWnd, pageViewerHwnd, "connection"); 
	  		} else {
	  			pageViewerHwnd = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_PMAIN_STGSPAGE), parentHwnd, NULL);
	  			ShowWindow(pageViewerHwnd, SW_SHOWNORMAL);
	  			SetProfileSettingsUiFont(hWnd, pageViewerHwnd, "main"); 
	  		} 
		}
	}
    return CallWindowProc(prstPagesCallback, hWnd, uMsg, wParam, lParam);
}

void ShowProfileSettingsDialog(HWND owner, char _profile_name[])
{    
	int ini_path_length = 0;
    sprintf(profile_name, _profile_name);
	GetModuleFileName(g_hInstance, ini_path, 256);
	*(strrchr(ini_path, '\\')+1) = '\0';
	strcat(ini_path, profile_name);
	strcat(ini_path, ".ini"); 
	if(_access(ini_path, 0) != 0) {
			  WritePrivateProfileString("Main", "Nicknames", "", ini_path);
			  WritePrivateProfileString("Main", "Password", "", ini_path);
			  WritePrivateProfileString("Main", "Realname", "", ini_path); 
			  WritePrivateProfileString("Connection", "Server", "", ini_path);
			  WritePrivateProfileString("Connection", "Port", "6667", ini_path);
	}  
	if((LOBYTE(LOWORD(GetVersion())) == 3 && HIBYTE(LOWORD(GetVersion())) >= 10) 
	  	|| LOBYTE(LOWORD(GetVersion())) > 3) {
		HWND hWnd = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_PROFILESETTINGSDIALOG), owner, ProfileSettingsDialogProc);
		parentHwnd = hWnd;

		  if(hWnd) {
		  	pageViewerHwnd = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_PMAIN_STGSPAGE), hWnd, NULL);
		  	ShowWindow(hWnd, SW_SHOW);
		  	ShowWindow(pageViewerHwnd, SW_SHOWNORMAL);
		  	SetProfileSettingsUiFont(hWnd, pageViewerHwnd, "main"); 
		  	prstPagesCallback = (WNDPROC) SetWindowLong((HWND)GetDlgItem(hWnd, IDC_PAGESCOMBO), GWL_WNDPROC, (long)&PrStPagesComboProc);
		  	UpdateWindow(pageViewerHwnd);                                                   
		  } else {
		  	MessageBox(hWnd, "Something wen\'t wrong", "Error", MB_ICONSTOP|MB_OK);
		  } 
	} else {
	  char msg_text[512];
	  sprintf(msg_text, "Profile created at: %s. Use a text editor.", ini_path); 
	  MessageBox(NULL, msg_text, "Tinelix IRC", MB_ICONASTERISK|MB_OK);
	}
}  

void SetProfileSettingsUiFont(HWND hwndParent, HWND hWnd, char* page_name) {
  HFONT defaultFont; 
  LOGFONT fontAttrib; 
  char Pages[2][20] = {
  	"Main", "Connection"  
  };
  int i = 0;                                                               
  sprintf(current_page, page_name);
  defaultFont = (HFONT)CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
   	 OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
     "Helv");
  SendDlgItemMessage(hwndParent, IDOK, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hwndParent, IDCANCEL, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hwndParent, IDC_PAGESCOMBO, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  for(i = 0; i < 2; i++) {
  	SendMessage((HWND)GetDlgItem(hwndParent, IDC_PAGESCOMBO), CB_ADDSTRING, (WPARAM) 0, (LPARAM) Pages[i]);
  }
  SendMessage((HWND)GetDlgItem(hwndParent, IDC_PAGESCOMBO), CB_SETCURSEL, (WPARAM) 1, (LPARAM) 0);
  if(!strcmp(page_name, "main")) {
    char nicknames[256];
  	char password[20];
  	char realname[256];
  	HWND editText; 
  	SendDlgItemMessage(hWnd, IDC_PROFILE_NAME_LABEL, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_PROFILE_NAME_EDIT, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_NICKNAMES_LABEL, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_NICKNAMES_EDIT, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_PASSWORD_LABEL, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_PASSWORD_EDIT, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_REALNAME_LABEL, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_REALNAME_EDIT, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	GetPrivateProfileString("Main", "Nicknames", "", nicknames, 256, ini_path);
    GetPrivateProfileString("Main", "Password", "", password, 20, ini_path);
    GetPrivateProfileString("Main", "Realname", "", realname, 256, ini_path);
    editText = GetDlgItem(hWnd, IDC_PROFILE_NAME_EDIT);
    SetWindowText(editText, profile_name); 
    editText = GetDlgItem(hWnd, IDC_NICKNAMES_EDIT);
    SetWindowText(editText, nicknames);
    editText = GetDlgItem(hWnd, IDC_PASSWORD_EDIT); 
    SetWindowText(editText, password); 
    editText = GetDlgItem(hWnd, IDC_REALNAME_EDIT); 
    SetWindowText(editText, realname);
  } else if(!strcmp(page_name, "connection")) {
    char server[256];
  	char port[5];
  	HWND editText;
  	SendDlgItemMessage(hWnd, IDC_PROFILE_SERVER_LABEL, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_PROFILE_SERVER_EDIT, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_PROFILE_PORT_LABEL, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	SendDlgItemMessage(hWnd, IDC_PROFILE_PORT_EDIT, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  	GetPrivateProfileString("Connection", "Server", "", server, 256, ini_path);
    GetPrivateProfileString("Connection", "Port", "", port, 5, ini_path);
    editText = GetDlgItem(hWnd, IDC_PROFILE_SERVER_EDIT); 
    SetWindowText(editText, server);
    editText = GetDlgItem(hWnd, IDC_PROFILE_PORT_EDIT);  
    SetWindowText(editText, port);
  }
}
