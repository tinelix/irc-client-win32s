// parssdlg.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "parssdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParserSettingsDialog dialog


ParserSettingsDialog::ParserSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ParserSettingsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ParserSettingsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ParserSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParserSettingsDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ParserSettingsDialog, CDialog)
	//{{AFX_MSG_MAP(ParserSettingsDialog)
	ON_BN_CLICKED(IDC_SHOW_MSGTIME, OnShowMsgtime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ParserSettingsDialog message handlers

BOOL ParserSettingsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "MS Sans Serif");

	CButton* show_msgtime_checkbox = (CButton*)GetDlgItem(IDC_SHOW_MSGTIME);
	CComboBox* msgtime_pos_combobox = (CComboBox*)GetDlgItem(IDC_TIMESTAMPS_POS);

	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	char show_msgtime_string[80] = {0};
	char msgtime_pos_string[6] = {0};
	char language_string[80] = {0};

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	GetPrivateProfileString("Parser", "ShowMsgTime", "Enabled", show_msgtime_string, MAX_PATH, exe_path);
	GetPrivateProfileString("Parser", "MsgTimePos", "Right", msgtime_pos_string, MAX_PATH, exe_path);
	GetPrivateProfileString("Main", "Language", "", language_string, MAX_PATH, exe_path);

	CString lng_selitemtext_2(language_string);

	GetDlgItem(IDOK)->SetFont(&mainfont);
	GetDlgItem(IDCANCEL)->SetFont(&mainfont);
	GetDlgItem(IDC_PARSER_GROUP)->SetFont(&mainfont);
	GetDlgItem(IDC_SHOW_MSGTIME)->SetFont(&mainfont);
	GetDlgItem(IDC_TIMESTAMPS_POS)->SetFont(&mainfont);
	
	if(strcmp(show_msgtime_string, "Enabled") == 0) {
		show_msgtime_checkbox->SetCheck(1);	
	} else {
		show_msgtime_checkbox->SetCheck(0);
	};

	if(show_msgtime_checkbox->GetCheck() == 1) {
		GetDlgItem(IDC_TIMESTAMPS_POS)->EnableWindow(TRUE);
	} else {
		GetDlgItem(IDC_TIMESTAMPS_POS)->EnableWindow(FALSE);
	};
	
	if(lng_selitemtext_2 == "Russian") {
		GetDlgItem(IDCANCEL)->SetWindowText("Отмена");
		GetDlgItem(IDC_SHOW_MSGTIME)->SetWindowText("Показать временную метку сообщений");
		msgtime_pos_combobox->AddString("слева");
		msgtime_pos_combobox->AddString("справа");
		msgtime_pos_combobox->DeleteString(0);
		msgtime_pos_combobox->SelectString(NULL, "справа");
		SetWindowText("Настройки парсера");
	} else {
		GetDlgItem(IDCANCEL)->SetWindowText("Cancel");
		GetDlgItem(IDC_SHOW_MSGTIME)->SetWindowText("Show message timestamps");
		msgtime_pos_combobox->AddString("on the left");
		msgtime_pos_combobox->AddString("on the right");
		msgtime_pos_combobox->DeleteString(0);
		msgtime_pos_combobox->SelectString(NULL, "on the right");
		SetWindowText("Parser settings");
	};

	if(strcmp(msgtime_pos_string, "Left") == 0) {
		if(lng_selitemtext_2 == "Russian") {
			msgtime_pos_combobox->SelectString(NULL, "слева");
		} else {
			msgtime_pos_combobox->SelectString(NULL, "on the left");
		};
	} else {
		if(lng_selitemtext_2 == "Russian") {
			msgtime_pos_combobox->SelectString(NULL, "справа");
		} else {
			msgtime_pos_combobox->SelectString(NULL, "on the right");
		};
	};

	mainfont.Detach();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ParserSettingsDialog::OnOK() 
{
	CComboBox* msgtime_pos_combobox = (CComboBox*)GetDlgItem(IDC_TIMESTAMPS_POS);
	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "MS Sans Serif");

	CButton* show_msgtime_checkbox = (CButton*)GetDlgItem(IDC_SHOW_MSGTIME);

	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	char show_msgtime_string[80] = {0};
	char msgtime_pos_string[6] = {0};
	char language_string[80] = {0};

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	GetPrivateProfileString("Parser", "ShowMsgTime", "Enabled", show_msgtime_string, MAX_PATH, exe_path);
	GetPrivateProfileString("Parser", "MsgTimePos", "Right", msgtime_pos_string, MAX_PATH, exe_path);
	GetPrivateProfileString("Main", "Language", "", language_string, MAX_PATH, exe_path);

	CString lng_selitemtext_2(language_string);
	
	int pos_index = 0;
	pos_index = msgtime_pos_combobox->GetCurSel();
	if(show_msgtime_checkbox->GetCheck() == 1) {
		WritePrivateProfileString("Parser", "ShowMsgTime", "Enabled", exe_path);
	} else {
		WritePrivateProfileString("Parser", "ShowMsgTime", "Disabled", exe_path);
	};
	if(pos_index == 0) {
		WritePrivateProfileString("Parser", "MsgTimePos", "Left", exe_path);
	} else {
		WritePrivateProfileString("Parser", "MsgTimePos", "Right", exe_path);
	};
	
	CDialog::OnOK();
}

void ParserSettingsDialog::OnShowMsgtime() 
{
	CButton* show_msgtime_checkbox = (CButton*)GetDlgItem(IDC_SHOW_MSGTIME);
	if(show_msgtime_checkbox->GetCheck() == 1) {
		GetDlgItem(IDC_TIMESTAMPS_POS)->EnableWindow(TRUE);
	} else {
		GetDlgItem(IDC_TIMESTAMPS_POS)->EnableWindow(FALSE);
	};		
}
