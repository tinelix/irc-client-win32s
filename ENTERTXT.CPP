// entertxt.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "entertxt.h"
#include "profmnp.h"
#include "profcnp.h"
#include "proftabs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EnterTextDlg dialog


EnterTextDlg::EnterTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(EnterTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(EnterTextDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void EnterTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EnterTextDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EnterTextDlg, CDialog)
	//{{AFX_MSG_MAP(EnterTextDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void EnterTextDlg::delsymbs(char *str, int begin, int lng)
{
	while(*(str + begin++) = (str + begin + lng)[MAX_PATH]);
};

void EnterTextDlg::SetSettingProfileState(BOOL value) 
{
	setting_profile = value;
};

void EnterTextDlg::SetProfileName(char* name) 
{
	CString profname(name);
	sprintf(profilename, "%s", profname);
};

/////////////////////////////////////////////////////////////////////////////
// EnterTextDlg message handlers

void EnterTextDlg::OnOK() 
{
	ProfileMainPage profilemain;
	ProfileConnectionPage profileconn;
	if (setting_profile != TRUE) {
		GetDlgItem(IDC_ENTERTEXTEDIT)->GetWindowText(profilename, 80);
		char nickname[80] = {0};
		profilemain.SetCurrentNickname(nickname);
	} else {
		char nickname[80] = {0};
		GetDlgItem(IDC_ENTERTEXTEDIT)->GetWindowText(nickname, 80);
		profilemain.SetCurrentNickname(nickname);
	};
	CString profname(profilename);
	profilemain.SetProfileName(profilename);
	ProfileTabs settingsDlg("Profile settings");
	settingsDlg.AddPage(&profilemain);
	settingsDlg.AddPage(&profileconn);
	settingsDlg.Create(NULL, WS_CHILD|WS_VISIBLE);
	CRect rectWnd;
	GetWindowRect(rectWnd);
	SetWindowPos(settingsDlg.GetPage(0), 0, 0,
	rectWnd.Width() + 100,
	rectWnd.Height(),
	SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	CDialog::OnOK();
	int prof_settings_result = settingsDlg.DoModal();
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename
	GetModuleFileName(NULL, exe_path, MAX_PATH);  
	EnterTextDlg::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename
	strcat(exe_path, "\\settings");	// add settings filename
	if(prof_settings_result == IDOK && profname != "") {
		WritePrivateProfileString(profname, "Nicknames", profilemain.currnickname, exe_path);
		WritePrivateProfileString(profname, "Password", profilemain.password, exe_path);
		WritePrivateProfileString(profname, "Realname", profilemain.realname, exe_path);
		WritePrivateProfileString(profname, "Server", profileconn.server, exe_path);
		char port_to_str[5] = {0};
		sprintf(port_to_str, "%d", profileconn.port);
		WritePrivateProfileString(profname, "Port", port_to_str, exe_path);
	};	
}

BOOL EnterTextDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	EnterTextDlg::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings");	// add settings filename

	char language_string[MAX_PATH] = {0};
	
	try {
		GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);

		CString lng_selitemtext_2(language_string);
		if (lng_selitemtext_2 == "Russian") {
			if (setting_profile != TRUE) {
				GetDlgItem(IDC_ENTERTEXTLABEL)->SetWindowText("Имя профиля:");	
			} else {
				GetDlgItem(IDC_ENTERTEXTLABEL)->SetWindowText("Введите никнейм:");
			};
			SetWindowText("Введите текст"); 
			GetDlgItem(IDCANCEL)->SetWindowText("Отмена");
		} else {
			if (setting_profile != TRUE) {
				GetDlgItem(IDC_ENTERTEXTLABEL)->SetWindowText("Profile name:");	
			} else {
				GetDlgItem(IDC_ENTERTEXTLABEL)->SetWindowText("Enter the nickname:");
			};
			SetWindowText("Enter the text");
			GetDlgItem(IDCANCEL)->SetWindowText("Cancel");
		};
	}
	catch(...) 
	{};
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
