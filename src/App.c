#include <windows.h>
#include "Globals.h"
#include "MainWnd.h"
#include "Resource.h"
#include <winsock.h>

/* Global instance handle */
HINSTANCE g_hInstance = NULL;
WSADATA WSAData;

/* Our application entry point */
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  HWND hWnd;
  HACCEL hAccelerators;
  MSG msg; 
  int status;

  /* Assign global HINSTANCE */
  g_hInstance = hInstance; 

  /* Register our main window class, or error */
  if (!hPrevInstance && !RegisterMainWindowClass())
  {
    FatalAppExit(0, "Window class registration failed.");
    return 0;
  }

  /* Create our main window, or error */
  if (!(hWnd = CreateMainWindow()))
  {
  	FatalAppExit(0, "Window creating failed.");
    return 0;
  }

  /* Load accelerators */
  hAccelerators = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));

  /* Show main window and force a paint */
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  status = WSAStartup(MAKEWORD(1,1), &WSAData);
  if(status != 0) {
  	FatalAppExit(0, "WinSock initialization failed. Application cannot be started.");
    return 0;
  } 

  /* Main message loop */
  while (GetMessage(&msg, NULL, 0, 0) > 0)
  {
    if (!TranslateAccelerator(hWnd, hAccelerators, &msg) && !IsDialogMessage(hWnd, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int)msg.wParam;
}

void QuitApp() {
	WSACleanup(WSAData);
}
