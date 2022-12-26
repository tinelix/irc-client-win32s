#include "ConnMDlg.h"   
#include "ETextDlg.h"
#include "Globals.h"
#include "Resource.h" 
#include <string.h>

char ini_path[256];

BOOL CALLBACK ConnManDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  { 
    case WM_COMMAND:
    {
      WORD id = wParam;

      switch (id)
      {
        case IDOK: {
          EndDialog(hwndDlg, id);
          return TRUE;
        }
        case IDC_CREATE_PROFILE_BTN: {
          ShowEnterTextDialog(hwndDlg, "profile_name");
          return TRUE;               
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

void ShowConnManDialog(HWND owner)
{
  HWND hWnd = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_CONNMANDIALOG), owner, ConnManDialogProc);
  SetConnManUiFont(hWnd);
}

void SetConnManUiFont(HWND hWnd) {
  HFONT defaultFont; 
  LOGFONT fontAttrib;                                             
  int main_settings_index; 
  HWND listBoxHwnd = GetDlgItem(hWnd, IDC_PROFILELIST);
  defaultFont = (HFONT)CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
   	 OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
     "Helv");
  GetModuleFileName(g_hInstance, ini_path, 256);
  *(strrchr(ini_path, '\\')+1) = '\0';
  strcat(ini_path, "*.ini");

  if(LOBYTE(LOWORD(GetVersion())) >= 3 && HIBYTE(LOWORD(GetVersion())) >= 1) {
    // Windows 3.0 moment
  	DlgDirList(hWnd, ini_path, IDC_PROFILELIST, IDC_PROFILELIST, 0);            
  }
  // Next... 
  
  main_settings_index = SendMessage(listBoxHwnd, LB_FINDSTRING, 0, (LPARAM)"client.ini");
  if(main_settings_index >= 0) {
  	 SendMessage(listBoxHwnd, LB_DELETESTRING, main_settings_index, 0);
  };
  SendDlgItemMessage(hWnd, IDC_PROFILELIST, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hWnd, IDOK, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hWnd, IDC_CREATE_PROFILE_BTN, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hWnd, IDC_CONNECT_BTN, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hWnd, IDC_EDIT_PROFILE_BTN, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hWnd, IDC_DELETE_PROFILE_BTN, WM_SETFONT, (WPARAM)defaultFont, TRUE);
}
