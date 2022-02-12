// TLX_IRC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "mainwin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IRCClient

BEGIN_MESSAGE_MAP(IRCClient, CWinApp)
	//{{AFX_MSG_MAP(IRCClient)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IRCClient construction

IRCClient::IRCClient()
{
}

void delsymbs(char *str, int begin, int lng)
{
	while(*(str + begin++) = (str + begin + lng)[MAX_PATH]);
};

/////////////////////////////////////////////////////////////////////////////
// The one and only IRCClient object

IRCClient theApp;

/////////////////////////////////////////////////////////////////////////////
// IRCClient initialization

BOOL IRCClient::InitInstance()
{
	// Standard initialization

   	TCHAR exe_path[MAX_PATH] = {0};
	TCHAR settings_path[MAX_PATH] = {0};
	TCHAR* exe_name = "TLX_IRC.EXE"; // EXE filename
	char language_string[80] = {0};

	GetModuleFileName(NULL, exe_path, MAX_PATH);
	GetModuleFileName(NULL, settings_path, MAX_PATH); 

	*(strrchr(settings_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	GetPrivateProfileString("Main", "Language", "English", language_string, 80, exe_path);
	CString language_string_2(language_string);
	
	if (language_string_2 == "" || !language_string_2) {
		WritePrivateProfileSection("Main", "Language=English", settings_path);  // write to 'settings' file
	};

	Enable3dControls();
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	MainWindow dlg;
	sprintf(app_version, "0.1.12 Beta");
	sprintf(release_date, "2022-02-12");
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
