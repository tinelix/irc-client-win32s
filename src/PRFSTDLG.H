#ifndef PRFSTDLG_H
#define PRFSTDLG_H

#include <windows.h>


/* Dialog procedure for our "about" dialog */
BOOL CALLBACK ProfileSettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

long CALLBACK PagesComboProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/* Show our "about" dialog */
void ShowProfileSettingsDialog(HWND owner, char _profile_name[]);  

void SetProfileSettingsUiFont(HWND hwndParent, HWND hWnd, char* page_name);

#endif
