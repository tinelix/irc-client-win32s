#ifndef CONNMDLG_H
#define CONNMDLG_H

#include <windows.h>

/* Dialog procedure for our "about" dialog */
BOOL CALLBACK ConnManDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

/* Show our "about" dialog */
void ShowConnManDialog(HWND owner);

void SetConnManUiFont(HWND hWnd);

#endif
