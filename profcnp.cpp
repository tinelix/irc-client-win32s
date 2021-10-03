// profcnp.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "profcnp.h"
#include <stdio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProfileConnectionPage property page

IMPLEMENT_DYNCREATE(ProfileConnectionPage, CPropertyPage)

ProfileConnectionPage::ProfileConnectionPage() : CPropertyPage(ProfileConnectionPage::IDD)
{
	//{{AFX_DATA_INIT(ProfileConnectionPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ProfileConnectionPage::~ProfileConnectionPage()
{
}

void ProfileConnectionPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProfileConnectionPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProfileConnectionPage, CPropertyPage)
	//{{AFX_MSG_MAP(ProfileConnectionPage)
	ON_EN_CHANGE(IDC_SERVER, OnChangeServer)
	ON_EN_CHANGE(IDC_PORT, OnChangePort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ProfileConnectionPage::delsymbs(char *str, int begin, int lng)
{
	while(*(str + begin++) = (str + begin + lng)[MAX_PATH]);
};

/////////////////////////////////////////////////////////////////////////////
// ProfileConnectionPage message handlers

void ProfileConnectionPage::OnChangeServer() 
{
	GetDlgItem(IDC_SERVER)->GetWindowText(server, 80);
	TRACE(server);	
}

void ProfileConnectionPage::OnChangePort() 
{
	char port_str[5];
	GetDlgItem(IDC_PORT)->GetWindowText(port_str, 5);
	for(int i = 0; i < strlen(port_str); i++) {
		if(!isdigit(port_str[i])) {
			MessageBox("The 'Port' value should only contain number.", "Invalid value", MB_OK|MB_ICONSTOP);
			i = strlen(port_str);
			GetDlgItem(IDC_PORT)->SetWindowText("");
		};
	};
	port = atoi(port_str);	
}

BOOL ProfileConnectionPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	SetModified(TRUE);

	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "MS Sans Serif");
	GetDlgItem(IDC_SERVER_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_PORT_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_ENCODING_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_SERVER)->SetFont(&mainfont);
	GetDlgItem(IDC_PORT)->SetFont(&mainfont);
	GetDlgItem(IDC_ENCODING)->SetFont(&mainfont);

	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	ProfileConnectionPage::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings");	// add settings filename

	TCHAR language_string[MAX_PATH] = {0};
	
	try {
		GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
		
		CString lng_selitemtext_2(language_string);
		
		if (lng_selitemtext_2 == "Russian") {
			GetDlgItem(IDC_SERVER_LABEL)->SetWindowText("Сервер:");
			GetDlgItem(IDC_PORT_LABEL)->SetWindowText("Порт:");
			GetDlgItem(IDC_ENCODING_LABEL)->SetWindowText("Кодировка:");
		} else {
			GetDlgItem(IDC_SERVER_LABEL)->SetWindowText("Server:");
			GetDlgItem(IDC_PORT_LABEL)->SetWindowText("Port:");
			GetDlgItem(IDC_ENCODING_LABEL)->SetWindowText("Encoding:");
		};
	} catch(...) {

	};
				
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
