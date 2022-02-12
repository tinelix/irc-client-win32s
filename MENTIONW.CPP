// mentionw.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "mentionw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MentionWindow dialog


MentionWindow::MentionWindow(CWnd* pParent /*=NULL*/)
	: CDialog(MentionWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(MentionWindow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MentionWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MentionWindow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MentionWindow, CDialog)
	//{{AFX_MSG_MAP(MentionWindow)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MentionWindow message handlers

LRESULT MentionWindow::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == WM_USER_MENTION) {
		char exe_path[MAX_PATH] = {0};
		char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

		GetModuleFileName(NULL, exe_path, MAX_PATH);  

		*(strrchr(exe_path, '\\')+1)='\0';

		strcat(exe_path, "settings.ini");	// add settings filename

		TCHAR language_string[MAX_PATH] = {0};

		mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
			0, 0, "MS Sans Serif");
		HDC hDC = ::GetDC(NULL);
		int font_height = -MulDiv(11, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		titlefont.CreateFont(font_height, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
			0, 0, "MS Sans Serif");
		GetDlgItem(IDC_TITLE)->SetFont(&titlefont);
		titlefont.Detach();
		GetDlgItem(IDC_MENTIONED_MSG)->SetFont(&mainfont);
		GetDlgItem(IDC_OPEN)->SetFont(&mainfont);
		GetDlgItem(IDCANCEL)->SetFont(&mainfont);
		mainfont.Detach();
		MENTIONED_MSG* mentioned_message = (MENTIONED_MSG*)lParam;
		try {
			char mentioner_title[512] = {0};
			GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);

			CString lng_selitemtext_2(language_string);
			if(lng_selitemtext_2 == "Russian") {
				sprintf(mentioner_title, "%s упомянул(a) вас", mentioned_message->mentioner);
				GetDlgItem(IDC_TITLE)->SetWindowText(mentioner_title);
				GetDlgItem(IDC_MENTIONED_MSG)->SetWindowText(mentioned_message->message);
				GetDlgItem(IDC_OPEN)->SetWindowText("Открыть");
				GetDlgItem(IDCANCEL)->SetWindowText("Закрыть");
			} else {
				sprintf(mentioner_title, "%s mentioned you", mentioned_message->mentioner);
				GetDlgItem(IDC_TITLE)->SetWindowText(mentioner_title);
				GetDlgItem(IDC_MENTIONED_MSG)->SetWindowText(mentioned_message->message);
				GetDlgItem(IDC_OPEN)->SetWindowText("Open");
				GetDlgItem(IDCANCEL)->SetWindowText("Close");
			}
		} catch(...) {
		};
		int screen_width = GetSystemMetrics(SM_CXSCREEN);
		int screen_height = GetSystemMetrics(SM_CYSCREEN);
		ShowWindow(SW_SHOW);
		DWORD winver = GetVersion();
		if(LOBYTE(LOWORD(winver)) >= 4) {
			SetWindowPos(NULL, screen_width - 368, screen_height - 120, 338, 100, SWP_SHOWWINDOW);
		} else if(LOBYTE(LOWORD(winver)) >= 6 && HIBYTE(LOWORD(winver)) >= 1) {
			SetWindowPos(NULL, screen_width - 408, screen_height - 120, 338, 100, SWP_SHOWWINDOW);
		} else {
			SetWindowPos(NULL, screen_width - 358, screen_height - 120, 338, 100, SWP_SHOWWINDOW);
		};
	};
		
	return CDialog::WindowProc(message, wParam, lParam);
}

void MentionWindow::OnOpen() 
{
	ShowWindow(SW_HIDE);
	GetParent()->ShowWindow(SW_RESTORE);
	GetParent()->SetForegroundWindow();	
}
