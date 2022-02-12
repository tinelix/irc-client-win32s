// setgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "setgdlg.h"
#include "mainwin.h"
#include "parssdlg.h"
#include <locale.h>
#include <stdio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingsDialog dialog


SettingsDialog::SettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SettingsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingsDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SettingsDialog, CDialog)
	//{{AFX_MSG_MAP(SettingsDialog)
	ON_BN_CLICKED(IDC_CHANGE_MSG_FONT, OnChangeMsgFont)
	ON_BN_CLICKED(IDC_PARSER_SETTINGS, OnParserSettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// SettingsDialog message handlers

void SettingsDialog::OnOK() 
{
	char selitemtext[80];
	CComboBox* cb = (CComboBox*)GetDlgItem(IDC_LANGCOMBO1);
	CButton* msg_history_checkbox = (CButton*)GetDlgItem(IDC_SAVE_MSG_HISTORY);
	int selindex = cb->GetCurSel();
	cb->GetLBText(selindex, selitemtext);
	CString lng_selitemtext_2(selitemtext);
	char language_string[80] = {0};
	char msg_history[80] = {0};
	char exe_path[MAX_PATH] = {0};
	char settings_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename
	GetModuleFileName(NULL, settings_path, MAX_PATH); 
	*(strrchr(settings_path, '\\')+1)='\0';
	strcat(exe_path, "settings.ini");	// add settings filename
	if(GetFileAttributes(settings_path) == 1 && GetFileAttributes(exe_path) == 1) {
		MessageBox("The disk may be write protected.", "Warning", MB_OK|MB_ICONEXCLAMATION);
		exit; 
	};

	GetPrivateProfileString("Main", "Language", NULL, language_string, MAX_PATH, settings_path);
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

	if(msg_history_checkbox->GetCheck() == 1) {
		WritePrivateProfileString("Main", "MsgHistory", "Enabled", settings_path);
	} else {
		WritePrivateProfileString("Main", "MsgHistory", "Disabled", settings_path);
	};

	if(lng_selitemtext_2 == "Russian") {
		if (lng_selitemtext_3 == "English") {
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
				file_submenu->AppendMenu(MF_SEPARATOR);
				file_submenu->AppendMenu(MF_STRING, ID_FILE_STATISTICS, "Статистика");
				file_submenu->AppendMenu(MF_SEPARATOR);
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

void SettingsDialog::delsymbs(char *str, int begin, int lng)
{
	for(begin; begin < strlen(str); begin++) {
		*(str + begin) = 0;	
	};			
};

BOOL SettingsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	TCHAR language_string[MAX_PATH] = {0};
	TCHAR msg_history_string[MAX_PATH] = {0};
	
	try {
		GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
		GetPrivateProfileString("Main", "MsgHistory", "Enabled", msg_history_string, MAX_PATH, exe_path);
		CComboBox *language_combo = (CComboBox*)GetDlgItem(IDC_LANGCOMBO1);
		CButton* msg_history_checkbox = (CButton*)GetDlgItem(IDC_SAVE_MSG_HISTORY);
		language_combo->SelectString(NULL, language_string);
		mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
		0, 0, "MS Sans Serif");
		GetDlgItem(IDOK)->SetFont(&mainfont);
		GetDlgItem(IDCANCEL)->SetFont(&mainfont);
		GetDlgItem(IDC_LANGLABEL)->SetFont(&mainfont);
		GetDlgItem(IDC_LANGCOMBO1)->SetFont(&mainfont);
		GetDlgItem(IDC_SAVE_MSG_HISTORY)->SetFont(&mainfont);
		GetDlgItem(IDC_CHANGE_MSG_FONT)->SetFont(&mainfont);
		GetDlgItem(IDC_PARSER_SETTINGS)->SetFont(&mainfont);

		CString lng_selitemtext_2(language_string);
		CString msg_history_string2(msg_history_string);
		
		if (lng_selitemtext_2 == "Russian") {
			GetDlgItem(IDCANCEL)->SetWindowText("Отмена");
            GetDlgItem(IDC_LANGLABEL)->SetWindowText("Язык (Language):");
            GetDlgItem(IDC_SAVE_MSG_HISTORY)->SetWindowText("Сохранять историю сообщений");
			GetDlgItem(IDC_CHANGE_MSG_FONT)->SetWindowText("Сменить шрифт...");
			GetDlgItem(IDC_PARSER_SETTINGS)->SetWindowText("Настройки парсера");
            SetWindowText("Настройки");
		} else {
			GetDlgItem(IDCANCEL)->SetWindowText("Cancel");
            GetDlgItem(IDC_LANGLABEL)->SetWindowText("Language:");
            GetDlgItem(IDC_SAVE_MSG_HISTORY)->SetWindowText("Save messages history");
			GetDlgItem(IDC_CHANGE_MSG_FONT)->SetWindowText("Change font...");
			GetDlgItem(IDC_PARSER_SETTINGS)->SetWindowText("Parser settings");
            SetWindowText("Settings");
		};
		
		if(msg_history_string2 == "Enabled") {
			msg_history_checkbox->SetCheck(1);	
		} else {
			msg_history_checkbox->SetCheck(0);
		};
	} catch(...) {
	
	};	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SettingsDialog::OnChangeMsgFont() 
{	
	try {

		char exe_path[MAX_PATH] = {0};
		char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename
		GetModuleFileName(NULL, exe_path, MAX_PATH);  
		*(strrchr(exe_path, '\\')+1)='\0';
		strcat(exe_path, "settings.ini");	// add settings filename
		LOGFONT logfont;
		CFontDialog fontdlg(&logfont);
		sprintf(logfont.lfFaceName, "Fixedsys");
		logfont.lfHeight = 12;
		logfont.lfItalic = FALSE;
		logfont.lfStrikeOut = FALSE;
		logfont.lfUnderline = FALSE;
		int status = fontdlg.DoModal();
		if(status == IDOK) {
			// Soon you wan't have to change the same font every time.
			msg_font.CreateFontIndirect(&logfont);
			AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS)->SetFont(&msg_font);
			msg_font.Detach();
			char font_value[48] = {0};
			int font_vl_numb = 0;
			font_vl_numb = sprintf(font_value, logfont.lfFaceName);
			HDC hDC = ::GetDC(NULL);
			int font_size = 0;
			font_size = -MulDiv(logfont.lfHeight, 72, GetDeviceCaps(hDC, LOGPIXELSY));
			font_size = (font_size < 0) ? - font_size : font_size;
			::ReleaseDC(NULL, hDC);
			char font_size_str[3] = {0};
			sprintf(font_size_str, "%d", font_size);
			//font_vl_numb += sprintf(font_value + font_vl_numb, ", ");
			//font_vl_numb += sprintf(font_value + font_vl_numb, "%d", font_size);
			WritePrivateProfileString("Main", "MsgFont", font_value, exe_path);
			WritePrivateProfileString("Main", "MsgFontSize", font_size_str, exe_path);
		};
	} catch(...) {
	
	};	
}

void SettingsDialog::OnParserSettings() 
{
	ParserSettingsDialog parser_settings_dlg;
	parser_settings_dlg.DoModal();
	
}
