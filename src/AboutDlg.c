#include "AboutDlg.h"
#include "Globals.h"
#include "Resource.h"

/* Dialog procedure for our "about" dialog */
BOOL CALLBACK AboutDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_COMMAND:
    {
      WORD id = wParam;

      switch (id)
      {
        case IDOK:
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

/* Show our "about" dialog */
void ShowAboutDialog(HWND owner)
{ 
  HWND hWnd = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_ABOUTDIALOG), owner, AboutDialogProc);
  if(hWnd) {
    HWND appNameHwnd = GetDlgItem(hWnd, IDC_APPNAME);  
    SetAboutUiFont(hWnd);
    SetWindowText(appNameHwnd, AppName);
    ShowWindow(hWnd, SW_SHOW);
  }
}

void SetAboutUiFont(HWND hWnd) {
   HFONT defaultFont; 
   LOGFONT fontAttrib;
   defaultFont = (HFONT)CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
   	 OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
     "Helv");  
    
  SendDlgItemMessage(hWnd, IDOK, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hWnd, IDC_CORYRIGHT, WM_SETFONT, (WPARAM)defaultFont, TRUE);
  SendDlgItemMessage(hWnd, IDC_GITHUB_LINK, WM_SETFONT, (WPARAM)defaultFont, TRUE);
}
