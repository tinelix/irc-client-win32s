// proftabs.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "proftabs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProfileTabs

IMPLEMENT_DYNAMIC(ProfileTabs, CPropertySheet)

ProfileTabs::ProfileTabs(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

ProfileTabs::ProfileTabs(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

ProfileTabs::~ProfileTabs()
{
}


BEGIN_MESSAGE_MAP(ProfileTabs, CPropertySheet)
	//{{AFX_MSG_MAP(ProfileTabs)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ProfileTabs::delsymbs(char *str, int begin, int lng)
{
	while(*(str + begin++) = (str + begin + lng)[MAX_PATH]);
};

/////////////////////////////////////////////////////////////////////////////
// ProfileTabs message handlers

int ProfileTabs::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetDlgItem(ID_HELP)->ShowWindow(SW_HIDE);

	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	ProfileTabs::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings.ini");	// add settings filename

	TCHAR language_string[MAX_PATH] = {0};
	
	try {
		GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);

		mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
		0, 0, "MS Sans Serif");
		GetDlgItem(IDOK)->SetFont(&mainfont);
		GetDlgItem(IDCANCEL)->SetFont(&mainfont);
		GetDlgItem(ID_APPLY_NOW)->SetFont(&mainfont);
		GetDlgItem(ID_HELP)->SetFont(&mainfont);

		CString lng_selitemtext_2(language_string);
		if (lng_selitemtext_2 == "Russian") {
			GetDlgItem(IDCANCEL)->SetWindowText("Отмена");
			GetDlgItem(ID_APPLY_NOW)->SetWindowText("Применить");
			GetDlgItem(ID_HELP)->SetWindowText("Справка");
		} else {
			GetDlgItem(IDCANCEL)->SetWindowText("Cancel");
			GetDlgItem(ID_APPLY_NOW)->SetWindowText("Apply");
			GetDlgItem(ID_HELP)->SetWindowText("Help");
		};
	} 
	catch(...)
	{
		MessageBox("Error reading INI file.", "Error", MB_OK|MB_ICONSTOP);
	};
		
	return 0;
}

void ProfileTabs::OnClose() 
{
		
	CPropertySheet::OnClose();
}
