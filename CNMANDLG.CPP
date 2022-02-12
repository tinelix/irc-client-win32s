// cnmandlg.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "cnmandlg.h"
#include "entertxt.h"
#include "mainwin.h"
#include <locale.h>

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
	char realname[80];
	char quit_msg[256];
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
	ON_BN_CLICKED(IDC_CHANGE_PROFILE_BTN, OnChangeProfileBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ConnectionManagerDialog::delsymbs(char *str, int begin, int lng)
{
	for(begin; begin < strlen(str); begin++) {
		*(str + begin) = 0;	
	};
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
	if (GetFileAttributes(exe_path) == 1) {
	}; 
	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	char language_string[MAX_PATH] = {0};

	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "MS Sans Serif");
	GetDlgItem(IDC_LANGLABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_LANGCOMBO1)->SetFont(&mainfont);
	GetDlgItem(IDC_PROFILES_GROUP)->SetFont(&mainfont);
	GetDlgItem(IDC_PROFILELIST)->SetFont(&mainfont);
	GetDlgItem(IDC_ADD_PROFILE_BTN)->SetFont(&mainfont);
	GetDlgItem(IDC_CONNECT_PROFILE_BTN)->SetFont(&mainfont);
	GetDlgItem(IDC_CHANGE_PROFILE_BTN)->SetFont(&mainfont);
	GetDlgItem(IDC_DELETE_PROFILE_BTn)->SetFont(&mainfont);
	GetDlgItem(IDOK)->SetFont(&mainfont);
	GetDlgItem(IDCANCEL)->SetFont(&mainfont);

	try {
	char settings[32768] = {0};
	int settings_int = 1;
	int settings_section_index = 0;
	try {
	GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
	} catch(CFileException* cfe) {
		exit;	
	};
	CComboBox *language_combo = (CComboBox*)GetDlgItem(IDC_LANGCOMBO1);
	CListBox *profiles_cb = (CListBox*)GetDlgItem(IDC_PROFILELIST);
	language_combo->SelectString(NULL, language_string);
	try 
	{	
		CStdioFile settings_file;
		try {
			if(settings_file.Open(exe_path, CFile::modeReadWrite)) {
				settings_file.Read(settings, 32767);
			} else {
				if (settings_file.Open(exe_path, CFile::modeReadWrite | CFile::modeCreate)) {
					settings_file.Read(settings, 32767);
				} else {
					exit;
				};
			}
		} catch(CFileException* cfe) {
			language_combo->SelectString(NULL, "English");
			exit;
		};

		CString settings_str(settings);

		BOOL IsSection;
		CString section;
		
		for(int i = 0; i < strlen(settings_str); i++)
		{
			CString settings_symbol(settings[i]);
			settings_symbol.Right(i);
			if (settings_symbol.Find("]") != -1) {
				IsSection = FALSE;
				if (section.IsEmpty() == FALSE && section != "Main" && section != "Parser") {
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
	catch(CException exception)
	{
	};

    
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ConnectionManagerDialog::OnAddProfileClicked() 
{
	EnterTextDlg edittext;
	edittext.DoModal();
	char selitemtext[80];
	char section[800];
	char port[5];
	char port_to_str[20];
	char nicknames[80]; 
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename
	char settings[32768] = {0};
	GetModuleFileName(NULL, exe_path, MAX_PATH);
	CListBox *profiles_cb = (CListBox*)GetDlgItem(IDC_PROFILELIST);
	int selindex = profiles_cb->GetCurSel(); 
	*(strrchr(exe_path, '\\')+1)='\0';
	strcat(exe_path, "settings.ini");	// add settings filename
	try 
	{	
		int profiles_count = profiles_cb->GetCount();
		for (int index = 0; index < profiles_count; index++) {
		 	profiles_cb->DeleteString(index);
		};
		CStdioFile settings_file;
		try {
			if(settings_file.Open(exe_path, CFile::modeReadWrite)) {
				settings_file.Read(settings, 32767);
			} else {
				if (settings_file.Open(exe_path, CFile::modeReadWrite | CFile::modeCreate)) {
					settings_file.Read(settings, 32767);
				} else {
					exit;
				};
			}
		} catch(CFileException* cfe) {
			exit;
		};

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
}

void ConnectionManagerDialog::OnConnectProfileClicked() 
{
	MainWindow* mainwin = (MainWindow*)GetParent();
	IRCClient* application = (IRCClient*)AfxGetApp();
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
	*(strrchr(exe_path, '\\')+1)='\0';
	strcat(exe_path, "settings.ini");	// add settings filename
	PARAMETERS profile_params;
	profile_cb->GetText(selindex, selitemtext);
	GetPrivateProfileString(selitemtext, "Server", "", profile_params.server, 256, exe_path);
	GetPrivateProfileString(selitemtext, "Port", "", port, 5, exe_path);
	GetPrivateProfileString(selitemtext, "Nickname", "", profile_params.nickname, 80, exe_path);
	GetPrivateProfileString(selitemtext, "Realname", "", profile_params.realname, 80, exe_path);
	GetPrivateProfileString(selitemtext, "QuitMessage", "", profile_params.quit_msg, 256, exe_path);
	if(strlen(profile_params.realname) == 0) {
		sprintf(profile_params.realname, "Member");
	};
	if(strlen(profile_params.quit_msg) == 0) {
		sprintf(profile_params.quit_msg, "Tinelix IRC Client ver. %s (%s) for Win32s", application->app_version, application->release_date);
		WritePrivateProfileString(selitemtext, "QuitMessage", profile_params.quit_msg, exe_path);
	};
	profile_params.port = atoi(port);
	GetDlgItem(IDC_CONNECT_PROFILE_BTN)->EnableWindow(FALSE);
		 
	mainwin->CreateConnectionThread(profile_params);
	OnCancel();	
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
	char settings_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename
	GetModuleFileName(NULL, exe_path, MAX_PATH);
	GetModuleFileName(NULL, settings_path, MAX_PATH);
	*(strrchr(exe_path, '\\')+1)='\0';
	*(strrchr(settings_path, '\\')+1)='\0';
	strcat(exe_path, "settings.ini");	// add settings filename
	if(GetFileAttributes(settings_path) == 1 && GetFileAttributes(exe_path) == 1) {
		MessageBox("The disk may be write protected.", "Warning", MB_OK|MB_ICONEXCLAMATION);
	};
	GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, settings_path);
	CString lng_selitemtext_3(language_string);
	CMenu *eng_mainmenu;
	CMenu *rus_mainmenu;
	CMenu *file_submenu;
	CMenu *help_submenu;
	CMenu *view_submenu;
	eng_mainmenu = new CMenu;
	rus_mainmenu = new CMenu;
	file_submenu = new CMenu;
	help_submenu = new CMenu;
	view_submenu = new CMenu;

	if(lng_selitemtext_2 == "Russian") {
		if (lng_selitemtext_3 != "Russian") {
			char msgboxtext[360];
			int msgbox;
			int text_parts;
			text_parts = sprintf(msgboxtext, "Do you really want to change the language? Russian text may be incorrect on some Windows versions.\n\n");
			text_parts+= sprintf(msgboxtext + text_parts, "Вы действительно хотите сменить язык? Текст на русском языке может быть некорректен на некоторых версиях Windows.");
			msgbox = MessageBox((char*)msgboxtext, "Warning", MB_YESNO|MB_ICONEXCLAMATION);
			if (msgbox == IDYES) {
				WritePrivateProfileString("Main", "Language", "Russian", settings_path);
			};
			if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {

			} else {
				file_submenu->CreatePopupMenu();
				file_submenu->AppendMenu(MF_STRING, ID_FILE_CONNECT, "Подключиться...");
				file_submenu->AppendMenu(MF_STRING, ID_FILE_QUIT, "Выход");
				view_submenu->CreatePopupMenu();
				view_submenu->AppendMenu(MF_STRING, ID_VIEW_SETTINGS, "Настройки");
				help_submenu->CreatePopupMenu();
				help_submenu->AppendMenu(MF_STRING, ID_HELP_ABOUT, "О программе...");
				rus_mainmenu->CreateMenu();
				rus_mainmenu->AppendMenu(MF_STRING | MF_POPUP, (UINT)file_submenu->m_hMenu, "Файл");
            	rus_mainmenu->AppendMenu(MF_STRING | MF_POPUP, (UINT)view_submenu->m_hMenu, "Вид");
				rus_mainmenu->AppendMenu(MF_STRING | MF_POPUP, (UINT)help_submenu->m_hMenu, "Справка");
				GetParent()->SetMenu(rus_mainmenu);
			};
		} else {
			WritePrivateProfileString("Main", "Language", "Russian", settings_path);
		};
	} else {
		WritePrivateProfileString("Main", "Language", "English", settings_path);
		setlocale(LC_ALL, "English");
		if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {

		} else {
			eng_mainmenu->LoadMenu(IDR_MAINMENU);
			GetParent()->SetMenu(eng_mainmenu);
		};
	};

	delete(eng_mainmenu);
	delete(rus_mainmenu);
	delete(file_submenu);
	delete(view_submenu);
	delete(help_submenu);

	CDialog::OnOK();
}

void ConnectionManagerDialog::OnSelchangeProfilelist() 
{
	if (IsConnected == FALSE) {
		GetDlgItem(IDC_CONNECT_PROFILE_BTN)->EnableWindow(TRUE);
	};
	GetDlgItem(IDC_CHANGE_PROFILE_BTN)->EnableWindow(TRUE);	
}

void ConnectionManagerDialog::OnChangeProfileBtn() 
{
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	char language_string[MAX_PATH] = {0};
	GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
	CString lng_selitemtext_2(language_string);

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


void ConnectionManagerDialog::SetConnectionState(BOOL value) 
{
	IsConnected = value;
}
