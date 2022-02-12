// entertxt.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "entertxt.h"

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
	for(begin; begin < strlen(str); begin++) {
		*(str + begin) = 0;	
	};
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
	GetDlgItem(IDC_ENTERTEXTEDIT)->GetWindowText(profilename, 79);
	
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);
	
	IRCClient* application = (IRCClient*)AfxGetApp();  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	char language_string[MAX_PATH] = {0};
	GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
	CString lng_selitemtext_2(language_string);

	char quit_msg[256];
	
	sprintf(quit_msg, "Tinelix IRC Client ver. %s (%s) for Win32s", application->app_version, application->release_date);

	WritePrivateProfileString(profilename, "Nickname", "", exe_path);
	WritePrivateProfileString(profilename, "Password", "", exe_path);
	WritePrivateProfileString(profilename, "Realname", "", exe_path);
	WritePrivateProfileString(profilename, "Server", "", exe_path);
	WritePrivateProfileString(profilename, "Port", "", exe_path);
	WritePrivateProfileString(profilename, "QuitMessage", quit_msg, exe_path);

	CDialog::OnOK();

	if((UINT)ShellExecute(NULL, "open", "notepad.exe", exe_path, NULL, SW_SHOWNORMAL) <= 32) {
		try {
			if(lng_selitemtext_2 == "Russian") {
				MessageBox("Блокнот не найден. Воспользуйтесь другим редактором для изменения данного конфигурационного файла.", "Ошибка", MB_OK | MB_ICONSTOP);
			} else {
				MessageBox("Notepad not found. Use another editor to modify this configuration file.", "Error", MB_OK | MB_ICONSTOP);
			};
		} catch(...) {
		
		};
	};	
}

BOOL EnterTextDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	EnterTextDlg::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "settings.ini");	// add settings filename

	char language_string[MAX_PATH] = {0};

	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "MS Sans Serif");
	GetDlgItem(IDC_ENTERTEXTLABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_ENTERTEXTEDIT)->SetFont(&mainfont);
	GetDlgItem(IDOK)->SetFont(&mainfont);
	GetDlgItem(IDCANCEL)->SetFont(&mainfont);
	
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
