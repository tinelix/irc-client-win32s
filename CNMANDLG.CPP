// cnmandlg.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "cnmandlg.h"
#include "entertxt.h"
#include "mainwin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ConnectionManagerDialog dialog

struct PARAMETERS 
{
	char server[256];
	char nickname[80];
	int port;
	HWND hwnd;
};

ConnectionManagerDialog::ConnectionManagerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ConnectionManagerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ConnectionManagerDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ConnectionManagerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ConnectionManagerDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ConnectionManagerDialog, CDialog)
	//{{AFX_MSG_MAP(ConnectionManagerDialog)
	ON_BN_CLICKED(IDC_ADD_PROFILE_BTN, OnAddProfileClicked)
	ON_BN_CLICKED(IDC_CONNECT_PROFILE_BTN, OnConnectProfileClicked)
	ON_LBN_SELCHANGE(IDC_PROFILELIST, OnSelchangeProfilelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ConnectionManagerDialog::delsymbs(char *str, int begin, int lng)
{
	while(*(str + begin++) = (str + begin + lng)[MAX_PATH]);
};

INT ConnectionManagerDialog::GetCountLines(LPCSTR str)
{
	return 0;
};

/////////////////////////////////////////////////////////////////////////////
// ConnectionManagerDialog message handlers

BOOL ConnectionManagerDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	ConnectionManagerDialog::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings");	// add settings filename

	char language_string[MAX_PATH] = {0};
	
	try {
	char settings[32768] = {0};
	int settings_int = 1;
	int settings_section_index = 0;
	
	GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
	CComboBox *language_combo = (CComboBox*)GetDlgItem(IDC_LANGCOMBO1);
	CListBox *profiles_cb = (CListBox*)GetDlgItem(IDC_PROFILELIST);
	language_combo->SelectString(NULL, language_string);
	try 
	{	
		CStdioFile settings_file;
		if(settings_file.Open(exe_path, CFile::modeReadWrite)) {
			settings_file.Read(settings, 32767);
		} else {
			settings_file.Open(exe_path, CFile::modeReadWrite | CFile::modeCreate);
			settings_file.Read(settings, 32767);
		}

		CString settings_str(settings);

		BOOL IsSection;
		CString section;
		
		for(int i = 0; i < strlen(settings_str); i++)
		{
			CString settings_symbol(settings[i]);
			settings_symbol.Right(i);
			if (settings_symbol.Find("]") != -1) {
				IsSection = FALSE;
				if (section.IsEmpty() == FALSE && section != "Main") {
					profiles_cb->AddString(section);
				};
				section = "";
			};
			if (IsSection == TRUE) {
				section += settings_symbol;
			};
			if (settings_symbol.Find("[") != -1) {
				IsSection = TRUE;
			};	
		};
	}
	catch(...)
	{
		TRACE("Error creating file");
	};

	CString lng_selitemtext_2(language_string);
	if (lng_selitemtext_2 == "Russian") {
		GetDlgItem(IDC_LANGLABEL)->SetWindowText("Язык (Language)");
		GetDlgItem(IDC_PROFILES_GROUP)->SetWindowText("Профили");
		GetDlgItem(IDC_ADD_PROFILE_BTN)->SetWindowText("Добавить");
		GetDlgItem(IDC_CHANGE_PROFILE_BTN)->SetWindowText("Изменить");
		GetDlgItem(IDC_CONNECT_PROFILE_BTN)->SetWindowText("Подключиться");
		GetDlgItem(IDC_DELETE_PROFILE_BTn)->SetWindowText("Удалить");
		GetDlgItem(IDCANCEL)->SetWindowText("Отмена");
		SetWindowText("Первоначальная настройка клиента");
	} else {
		GetDlgItem(IDC_LANGLABEL)->SetWindowText("Language");
		GetDlgItem(IDC_PROFILES_GROUP)->SetWindowText("Profiles");
		GetDlgItem(IDC_ADD_PROFILE_BTN)->SetWindowText("Add");
		GetDlgItem(IDC_CHANGE_PROFILE_BTN)->SetWindowText("Change");
		GetDlgItem(IDC_CONNECT_PROFILE_BTN)->SetWindowText("Connect");
		GetDlgItem(IDC_DELETE_PROFILE_BTn)->SetWindowText("Delete");
		GetDlgItem(IDCANCEL)->SetWindowText("Cancel");
		SetWindowText("Initial client setup");
	};
	//GetPrivateProfileSectionNames(sections, 32767, exe_path);
	//profiles_cb->AddString(sections);
	} 
	catch(...)
	{
	};

    
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ConnectionManagerDialog::OnAddProfileClicked() 
{
	EnterTextDlg edittext;
	edittext.DoModal();
}

void ConnectionManagerDialog::OnConnectProfileClicked() 
{
	MainWindow mainwin;
	char selitemtext[80];
	char section[800];
	char port[5];
	char port_to_str[20];
	char nicknames[80]; 
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename
	GetModuleFileName(NULL, exe_path, MAX_PATH);
	CListBox* profile_cb = (CListBox*)GetDlgItem(IDC_PROFILELIST);
	int selindex = profile_cb->GetCurSel(); 
	ConnectionManagerDialog::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename
	strcat(exe_path, "\\settings");	// add settings filename
	PARAMETERS params;
	profile_cb->GetText(selindex, selitemtext);
	GetPrivateProfileString(selitemtext, "Server", "", params.server, 256, exe_path);
	GetPrivateProfileString(selitemtext, "Port", "", port, 5, exe_path);
	GetPrivateProfileString(selitemtext, "Nicknames", "", params.nickname, 80, exe_path);
	params.port = atoi(port);
		 
	mainwin.CreateConnectionThread(params);	
}

void ConnectionManagerDialog::OnOK() 
{
	char selitemtext[80];
	CComboBox* cb = (CComboBox*)GetDlgItem(IDC_LANGCOMBO1);
	int selindex = cb->GetCurSel();
	cb->GetLBText(selindex, selitemtext);
	CString lng_selitemtext_2(selitemtext);
	char language_string[80] = {0};
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename
	GetModuleFileName(NULL, exe_path, MAX_PATH);  
	ConnectionManagerDialog::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename
	strcat(exe_path, "\\settings");	// add settings filename
	GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
	CString lng_selitemtext_3(language_string);
	CMenu *mainmenu;

	if(lng_selitemtext_2 == "Russian") {
		if (lng_selitemtext_3 != "Russian") {
			char msgboxtext[360];
			int msgbox;
			int text_parts;
			text_parts = sprintf(msgboxtext, "Do you really want to change the language? Russian text may be incorrect on some Windows versions.\n\n");
			text_parts+= sprintf(msgboxtext + text_parts, "Вы действительно хотите сменить язык? Текст на русском языке может быть некорректен на некоторых версиях Windows.");
			msgbox = MessageBox((char*)msgboxtext, "Warning", MB_YESNO|MB_ICONEXCLAMATION);
			if (msgbox == IDYES) {
				WritePrivateProfileSection("Main", "Language=Russian", exe_path);
			};
		} else {
			WritePrivateProfileSection("Main", "Language=Russian", exe_path);
		};
	} else {
		WritePrivateProfileSection("Main", "Language=English", exe_path);
	};

	CDialog::OnOK();
}

void ConnectionManagerDialog::OnSelchangeProfilelist() 
{
	GetDlgItem(IDC_CONNECT_PROFILE_BTN)->EnableWindow(TRUE);	
}
