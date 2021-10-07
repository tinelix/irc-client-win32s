// profmnp.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "profmnp.h"
#include "proftabs.h"
#include "entertxt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProfileMainPage property page

IMPLEMENT_DYNCREATE(ProfileMainPage, CPropertyPage)

ProfileMainPage::ProfileMainPage() : CPropertyPage(ProfileMainPage::IDD)
{
	//{{AFX_DATA_INIT(ProfileMainPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ProfileMainPage::~ProfileMainPage()
{
}

void ProfileMainPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProfileMainPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProfileMainPage, CPropertyPage)
	//{{AFX_MSG_MAP(ProfileMainPage)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_NICKNAMES, OnSelchangeNicknames)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_PASSWORD, OnChangePassword)
	ON_WM_SETCURSOR()
	ON_EN_CHANGE(IDC_REALNAME, OnChangeRealname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ProfileMainPage message handlers

int ProfileMainPage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void ProfileMainPage::delsymbs(char *str, int begin, int lng)
{
	while(*(str + begin++) = (str + begin + lng)[MAX_PATH]);
};

BOOL ProfileMainPage::OnInitDialog() 
{
	
	SetModified(TRUE);

	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	ProfileMainPage::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings.ini");	// add settings filename

	TCHAR language_string[MAX_PATH] = {0};

	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "MS Sans Serif");
	GetDlgItem(IDC_PROFNAME_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_NICKNAMES_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_PASSWORD_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_REALNAME_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_CLEAR_BUTTON)->SetFont(&mainfont);
	GetDlgItem(IDC_PROFNAME)->SetFont(&mainfont);
	GetDlgItem(IDC_NICKNAMES)->SetFont(&mainfont);
	GetDlgItem(IDC_PASSWORD)->SetFont(&mainfont);
	GetDlgItem(IDC_REALNAME)->SetFont(&mainfont);

	try {
		if(m_hWnd != NULL) {
			GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);

			CString lng_selitemtext_2(language_string);
			CComboBox* nick_cb = (CComboBox*)GetDlgItem(IDC_NICKNAMES);
			if (currnickname == NULL) {
				nick_cb->AddString("");
			} else {
				TRACE(currnickname);
				nick_cb->InsertString(0, currnickname);
				GetDlgItem(IDC_CLEAR_BUTTON)->EnableWindow(TRUE);
			};
			if (lng_selitemtext_2 == "Russian") {
				GetDlgItem(IDC_PROFNAME_LABEL)->SetWindowText("Имя профиля:");
				GetDlgItem(IDC_NICKNAMES_LABEL)->SetWindowText("Никнеймы:");
				GetDlgItem(IDC_PASSWORD_LABEL)->SetWindowText("Пароль:");
				GetDlgItem(IDC_REALNAME_LABEL)->SetWindowText("Настоящее имя:");
				GetDlgItem(IDC_CLEAR_BUTTON)->SetWindowText("Очистить");
				nick_cb->InsertString(1,"Изменить никнейм...");
			} else {
				GetDlgItem(IDC_PROFNAME_LABEL)->SetWindowText("Profile name:");
				GetDlgItem(IDC_NICKNAMES_LABEL)->SetWindowText("Nicknames:");
				GetDlgItem(IDC_PASSWORD_LABEL)->SetWindowText("Password:");
				GetDlgItem(IDC_REALNAME_LABEL)->SetWindowText("Realname:");
				GetDlgItem(IDC_CLEAR_BUTTON)->SetWindowText("Clear");
				nick_cb->InsertString(1, "Change nickname...");
			};
			//GetDlgItem(IDC_ENTERTEXTEDIT)->SetWindowText(&profilename);
		};
	} 
	catch(...)
	{
		MessageBox("Error reading INI file.", "Error", MB_OK|MB_ICONSTOP);
	};

	if (profilename != NULL && m_hWnd != NULL) {
		GetDlgItem(IDC_PROFNAME)->SetWindowText(profilename);
	};

	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ProfileMainPage::OnSize(UINT nType, int cx, int cy) 
{
	
	CPropertyPage::OnSize(nType, cx, cy);
		
}

void ProfileMainPage::SetProfileName(LPCSTR name) 
{
	if(name) {
		sprintf(profilename, "%s", name);
	};
};

void ProfileMainPage::SetCurrentNickname(LPCSTR nick) 
{
	if(nick) {
		sprintf(currnickname, "%s", nick);
	};
};

void ProfileMainPage::SetPassword(LPCSTR passw) 
{
	if(passw) {
		sprintf(password, "%s", passw);
	};
};

void ProfileMainPage::SetRealname(LPCSTR realn) 
{
	if(realn) {
		sprintf(realname, "%s", realn);
	};
};

void ProfileMainPage::OnSelchangeNicknames() 
{
	char nickname[80];
	CComboBox* nick_cb = (CComboBox*)GetDlgItem(IDC_NICKNAMES);
	int selindex = nick_cb->GetCurSel();
	if (selindex == 1) {
		EnterTextDlg entertxtdlg;
		entertxtdlg.SetSettingProfileState(TRUE);
		sprintf(entertxtdlg.profilename, "%s", profilename);
		GetParent()->DestroyWindow();
		entertxtdlg.DoModal();
	};
	nick_cb->GetLBText(selindex, nickname);
	SetCurrentNickname(nickname);	
}


void ProfileMainPage::OnClose() 
{
	// in future alpha versions.
	CPropertyPage::OnClose();
}

void ProfileMainPage::OnChangePassword() 
{
	char passw[20] = {0};
	CEdit* passw_cb = (CEdit*)GetDlgItem(IDC_PASSWORD);
	passw_cb->GetWindowText(passw, 20);
	sprintf(password, "%s", passw);
}

void ProfileMainPage::OnChangeRealname() 
{
	char realnm[160] = {0};
	CEdit* passw_cb = (CEdit*)GetDlgItem(IDC_REALNAME);
	passw_cb->GetWindowText(realnm, 160);
	sprintf(realname, "%s", realnm);	
}
