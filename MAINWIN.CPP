// mainwin.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "mainwin.h"
#include "cnmandlg.h"
#include "setgdlg.h"

#include <stdio.h>
#include <iostream.h>
#include <winsock.h>
#include <process.h>
#include <direct.h>
#include <locale.h>
#include <afxtempl.h>
#include <conio.h>

#pragma comment(lib, "wsock32.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

SOCKET sock;
HINSTANCE parserLib;

typedef void (WINAPI *cfunc) ();
typedef void (WINAPI *ParseMessage)(char*, char*[], char*, BOOL, char*);
typedef void (WINAPI *ParseNamesMessage)(char*, char*[], char*[], char*[], char*[], BOOL);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	CFont mainfont;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void delsymbs(char *str, int begin, int lng);

friend class MainWindow;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int status;

void CAboutDlg::delsymbs(char *str, int begin, int lng)
{
	for(begin; begin < strlen(str); begin++) {
		*(str + begin) = 0;	
	};
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog()
{

	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	TCHAR language_string[MAX_PATH] = {0};
	
	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "MS Sans Serif");
	GetDlgItem(IDC_WIN32S_EDITION)->SetFont(&mainfont);
	GetDlgItem(IDC_TECHINFO)->SetFont(&mainfont);
	GetDlgItem(IDC_WINVER_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_WINVER)->SetFont(&mainfont);
	GetDlgItem(IDC_LICENSE_NOTIFICATION)->SetFont(&mainfont);
	GetDlgItem(IDC_COPYRIGHT)->SetFont(&mainfont);
	GetDlgItem(IDOK)->SetFont(&mainfont);
	GetDlgItem(IDC_GITHUB_REPO_LINK)->SetFont(&mainfont);
	IRCClient* application = (IRCClient*)AfxGetApp();
	char app_name[32768];
	sprintf(app_name, "Tinelix IRC Client %s", application->app_version);
	GetDlgItem(IDC_APPNAME)->SetWindowText(app_name);

	try {
		GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);

		CString lng_selitemtext_2(language_string);
		if(lng_selitemtext_2 == "Russian") {
			SetWindowText("О программе Tinelix IRC Client");
			GetDlgItem(IDC_WIN32S_EDITION)->SetWindowText("для Win32s");
			GetDlgItem(IDC_TECHINFO)->SetWindowText("Техническая информация");
			GetDlgItem(IDC_WINVER_LABEL)->SetWindowText("Версия Windows:");
			GetDlgItem(IDC_LICENSE_NOTIFICATION)->SetWindowText("Это свободное программное обеспечение с"
			" открытым исходным кодом, распространяемое с условиями GNU General Public License 3.0. Прочитайте"
			" на сайте https://www.gnu.org/licenses/gnu-3.0-ru.html или смотрите файл LICENSE.TXT.\n\nБЕЗ КАКИХ-ЛИБО"
			" ГАРАНТИЙ, ВКЛЮЧАЯ КОММЕРЧЕСКУЮ ЦЕННОСТЬ.");			
		} else {
			SetWindowText("About Tinelix IRC Client");
			GetDlgItem(IDC_WIN32S_EDITION)->SetWindowText("for Win32s");
			GetDlgItem(IDC_TECHINFO)->SetWindowText("Technical Information");
			GetDlgItem(IDC_WINVER_LABEL)->SetWindowText("Windows version:");
			GetDlgItem(IDC_LICENSE_NOTIFICATION)->SetWindowText("Windows version:");
			GetDlgItem(IDC_LICENSE_NOTIFICATION)->SetWindowText("This is free software with open source,"
			" distributed under the terms of the GNU General Public License 3.0. Read"
			" on https://www.gnu.org/licenses/gnu-3.0.html or watch LICENSE.TXT file.\n\nWITHOUT ANY"
			" WARRANTY, NOT EVEN FOR MERCHANTABILITY.");
		};
	} catch(...) {
	};
	
	char winver_info[400];
	
	if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
	
		int winver = GetVersion();
		sprintf(winver_info, "%d.%d with Win32s", LOBYTE(LOWORD(winver)), 
		HIBYTE(LOWORD(winver)));
		GetDlgItem(IDC_WINVER)->SetWindowText(winver_info);	
	} else {
		int winver = GetVersion();
		sprintf(winver_info, "%d.%d with fully Win32", LOBYTE(LOWORD(winver)), 
		HIBYTE(LOWORD(winver)));
		GetDlgItem(IDC_WINVER)->SetWindowText(winver_info);	
	};	
	
	CDialog::OnInitDialog();
	CenterWindow();
	
	// TODO: Add extra about dlg initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// MainWindow dialog

MainWindow::MainWindow(CWnd* pParent /*=NULL*/)
	: CDialog(MainWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(MainWindow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINFRAME);
}

void MainWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MainWindow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(MainWindow, CDialog)
	//{{AFX_MSG_MAP(MainWindow)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_CONNECT, OnConnectClicked)
	ON_MESSAGE(WM_SOCKET_MESSAGE, MessageOutput)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_QUIT, OnFileQuitClicked)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAboutClicked)
	ON_EN_CHANGE(IDC_MSGTEXT, OnChangeMsgText)
	ON_BN_CLICKED(IDC_SENDMSG, OnSendmsg)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_SETTINGS, OnViewSettings)
	ON_CBN_SELCHANGE(IDC_JOINED_CHANNELS, OnSelchangeJoinedChannels)
	ON_COMMAND(ID_FILE_STATISTICS, OnFileStatistics)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MainWindow::delsymbs(char *str, int begin, int lng)
{
	for(begin; begin < strlen(str); begin++) {
		*(str + begin) = 0;	
	};
};



/////////////////////////////////////////////////////////////////////////////
// MainWindow message handlers

BOOL MainWindow::OnInitDialog()
{
CDialog::OnInitDialog();
	CenterWindow();

	sended_bytes_count = 0;
	recieved_bytes_count = 0;
	
	stats_dlg = new StatisticsDialog;
	stats_dlg->Create(StatisticsDialog::IDD, this);

    mention_wnd = new MentionWindow;
	mention_wnd->Create(MentionWindow::IDD, this);

	sprintf(channel, "(None)");

	IRCClient* application = (IRCClient*)AfxGetApp();

	char dll_path[MAX_PATH] = {0};

	GetModuleFileName(NULL, exe_path, MAX_PATH);
	GetModuleFileName(NULL, dll_path, MAX_PATH);

	*(strrchr(exe_path, '\\')+1)='\0';
	*(strrchr(dll_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename
	strcat(dll_path, "parser.dll");


	TRACE("Tinelix IRC Client ver. %s (%s)\r\nCopyright © 2021-2022 Dmitry Tretyakov (aka. Tinelix)\r\n"
	"https:/github.com/tinelix/irc-client-for-win32s\r\n\r\n", application->app_version, application->release_date);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	CMenu* pSysMenu = (CMenu*)malloc(sizeof(CMenu));
	pSysMenu = GetSystemMenu(FALSE);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	};
	char font_string[48] = {0};
	int font_size = 9;
	HDC hDC = ::GetDC(NULL);
	GetPrivateProfileString("Main", "MsgFont", "Fixedsys", font_string, 48, exe_path);
	font_size = GetPrivateProfileInt("Main", "MsgFontSize", 8, exe_path);
	int font_height = 0;
	font_height = -MulDiv(font_size, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	font.CreateFont(font_height, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0,
	0, 0, font_string);
	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0,
	0, 0, "MS Sans Serif");
	AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS)->SetFont(&font);
	AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_MSGTEXT)->SetFont(&mainfont);
	AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SENDMSG)->SetFont(&mainfont);
	AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_JOINED_CHANNELS)->SetFont(&mainfont);
	IsConnected = FALSE;
	if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
		SetWindowText("Tinelix IRC Client (Win32s)");
	} else {
		SetWindowText("Tinelix IRC Client");
	};

	

	if(!(GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3)) {
		parserLib = (HINSTANCE)malloc(sizeof(HINSTANCE));
		parserLib = LoadLibrary(dll_path);
		if(parserLib) {
			TRACE("PARSER.DLL loaded.\r\n");
		};
	};

	TCHAR language_string[MAX_PATH] = {0};
	CMenu* mainmenu;

	WSADATA WSAData;
	char szTemp[80];

	int status = (WSAStartup(MAKEWORD(1,1), &WSAData));

	//try {
		GetPrivateProfileString("Main", "Language", "", language_string, MAX_PATH, exe_path);

		CString lng_selitemtext_2(language_string);
		if (lng_selitemtext_2 == "Russian") {
			GetDlgItem(IDC_SENDMSG)->SetWindowText("Отправить");
			if (status == 0) {
				TRACE("Winsock initialed.\r\n");
    		}
    		else {
				MessageBox("WinSock не может быть инициализирован.", "Ошибка", MB_OK|MB_ICONSTOP);
    		};
			if (GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
				MessageBox("Обработка строк через библиотеку \"PARSER.DLL\" работает только в Windows NT/9x. Запуск "
                "данной библотеки в Win32s может привести к вылету программы.", "Ошибка", MB_OK);
				FreeLibrary(parserLib);
			};
			setlocale(LC_ALL, "Russian");
			mainmenu = (CMenu*)malloc(sizeof(CMenu));
			mainmenu->m_hMenu = NULL;
			mainmenu->CreateMenu();
			CMenu* file_submenu = (CMenu*)malloc(sizeof(CMenu));
			file_submenu->m_hMenu = NULL;
			file_submenu->CreatePopupMenu();
			file_submenu->AppendMenu(MF_STRING, ID_FILE_CONNECT, "Подключиться...");
			file_submenu->AppendMenu(MF_SEPARATOR);
			file_submenu->AppendMenu(MF_STRING, ID_FILE_STATISTICS, "Статистика");
			file_submenu->AppendMenu(MF_SEPARATOR);
			file_submenu->AppendMenu(MF_STRING, ID_FILE_QUIT, "Выход");
			CMenu* view_submenu = (CMenu*)malloc(sizeof(CMenu));
			view_submenu->m_hMenu = NULL;
			view_submenu->CreatePopupMenu();
			view_submenu->AppendMenu(MF_STRING, ID_VIEW_SETTINGS, "Настройки");
			CMenu* help_submenu = (CMenu*)malloc(sizeof(CMenu));
			help_submenu->m_hMenu = NULL;
			help_submenu->CreatePopupMenu();
			help_submenu->AppendMenu(MF_STRING, ID_HELP_ABOUT, "О программе...");
			mainmenu->AppendMenu(MF_STRING | MF_POPUP, (UINT)file_submenu->m_hMenu, "Файл");
            mainmenu->AppendMenu(MF_STRING | MF_POPUP, (UINT)view_submenu->m_hMenu, "Вид");
			mainmenu->AppendMenu(MF_STRING | MF_POPUP, (UINT)help_submenu->m_hMenu, "Справка");
			SetMenu(mainmenu);
		} if (lng_selitemtext_2 == "English") {
			GetDlgItem(IDC_SENDMSG)->SetWindowText("Send");
			if (status == 0) {
				TRACE("WinSock initialed.\r\n");
    		}
    		else {
				MessageBox("WinSock cannot be initialed.", "Error", MB_OK|MB_ICONSTOP);
    		};
			if (GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
				MessageBox("String parsing through the \"PARSER.DLL\" library works only in Windows NT or 9x. Running "
                 "this library in Win32s may cause the program to crash.", "Error", MB_OK);
				FreeLibrary(parserLib);
			};
			setlocale(LC_ALL, "English");
			mainmenu = (CMenu*)malloc(sizeof(CMenu));
			mainmenu->LoadMenu(IDR_MAINMENU);
			SetMenu(mainmenu);
		} if (lng_selitemtext_2 == "") {
			GetDlgItem(IDC_SENDMSG)->SetWindowText("Send");
			if (status == 0) {
				TRACE("Winsock initialed.\r\n");
    		}
    		else {
				MessageBox("WinSock cannot be initialed.", "Error", MB_OK|MB_ICONSTOP);
    		};
			if (GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
				MessageBox("String parsing through the \"PARSER.DLL\" library works only in Windows NT or 9x. Running "
                 "this library in Win32s may cause the program to crash.", "Error", MB_OK);
				FreeLibrary(parserLib);
			};
			setlocale(LC_ALL, "English");
			mainmenu = (CMenu*)malloc(sizeof(CMenu));
			mainmenu->LoadMenu(IDR_MAINMENU);
			SetMenu(mainmenu);
			WritePrivateProfileString("Main", "Language", "English", exe_path);
			WritePrivateProfileString("Main", "MsgHistory", "Enabled", exe_path);
		};

		MoveWindow(40, 40, 600, 360);

	//}
	//catch(...)
	//{
		//MessageBox("Error reading INI file.", "Error", MB_OK|MB_ICONSTOP);
	//};

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void MainWindow::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void MainWindow::OnPaint() 
{


	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR MainWindow::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int MainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;	
	return 0;
}

void MainWindow::OnConnectClicked() 
{
	ConnectionManagerDialog connman;
	connman.SetConnectionState(IsConnected);
	int connman_modal = connman.DoModal();
	if(connman_modal =- IDOK) {
		IRC_STATS irc_stats;
		irc_stats.sended_bytes = sended_bytes_count;
		irc_stats.recieved_bytes = recieved_bytes_count;
		stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
	};
	
}

void MainWindow::ConnectionFunc(HWND hwnd, struct MainWindow::PARAMETERS params) 
{
	char exe_path[MAX_PATH] = {0};
	char h_pch[MAX_PATH] = {0};
	char h_pch2[MAX_PATH] = {0};
	char h_fch[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename
	GetModuleFileName(NULL, exe_path, MAX_PATH);
	MainWindow* mainwin = (MainWindow*)AfxGetApp()->GetMainWnd();
	*(strrchr(exe_path, '\\')+1)='\0';
	strcat(exe_path, "settings.ini");
	char msg_history_string[80];
	char language_string[80];
	GetPrivateProfileString("Main", "MsgHistory", "Enabled", msg_history_string, 80, exe_path);
	GetPrivateProfileString("Main", "Language", "", language_string, 80, exe_path);
	CString msg_history_string2(msg_history_string);
	CString language_string2(language_string);
	char history_path[MAX_PATH] = {0};
	char server[256];
	sprintf(server, "%s", params.server);
	char realname[80];
	sprintf(realname, "%s", params.realname);
	char connecting_msgb[100];
	int port = params.port;
	GetModuleFileName(NULL, history_path, MAX_PATH);
	*(strrchr(history_path, '\\')+1)='\0';
	strcat(history_path, "\\history");	// add history filename
	if (server == NULL || server == "" || server == " ")
	{
	  	if(language_string2 == "Russian") {
			MessageBox("Не указан адрес сервера.", "Ошибка", MB_OK|MB_ICONSTOP);
		} else {
			MessageBox("Not specified server address.", "Error", MB_OK|MB_ICONSTOP);
		};
		return;
	};
	if (port == NULL || port == 0)
	{
		if(language_string2 == "Russian") {
			MessageBox("Не указан порт сервера.", "Ошибка", MB_OK|MB_ICONSTOP);
		} else {
			MessageBox("Not specified server port.", "Error", MB_OK|MB_ICONSTOP);
		};
		return;
	};

	char* connecting_msg;
	connecting_msg = "Trying connecting to %s:%d...\n";
	TRACE(connecting_msg, &server, port);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN client_param;
	hostent* host;
	if (sock == SOCKET_ERROR) {
		if(language_string2 == "Russian") {
			char error_msg[32768];
			sprintf(error_msg, "Не удалось запустить WinSock с кодом ошибки: %d", WSAGetLastError());
			MessageBox(error_msg, "Ошибка", MB_OK|MB_ICONSTOP);
		} else {
			char error_msg[32768];
			sprintf(error_msg, "Could not start WinSock with error code: %d", WSAGetLastError());
			MessageBox(error_msg, "Error", MB_OK|MB_ICONSTOP);
		};
		return;
	};

	client_param.sin_family = AF_INET;
	connecting_msg = "Getting IP address...\n";
	TRACE0(connecting_msg);
	host = gethostbyname(server);
	if (host) {
		client_param.sin_addr.s_addr = inet_addr((char*)inet_ntoa(**(in_addr**)host->h_addr_list));
	}
	else
	{
		if(language_string2 == "Russian") {
			MessageBox("Не удалось получить IP-адрес для этого имени хоста.", "Ошибка", MB_OK|MB_ICONSTOP);
		} else {
			MessageBox("Failed to get the IP address for this hostname.", "Error", MB_OK|MB_ICONSTOP);
		};
		return;
	};
	client_param.sin_port = htons(port);
	connecting_msg = "Connecting...\n";
	TRACE(connecting_msg);
	int status;
	status = connect(sock, (SOCKADDR*)&client_param, sizeof(client_param));
	if (status == SOCKET_ERROR || status == INVALID_SOCKET) {
		if(language_string2 == "Russian") {
			char error_msg[32768];
			sprintf(error_msg, "Не удалось запустить WinSock с кодом ошибки: %d", WSAGetLastError());
			MessageBox(error_msg, "Ошибка", MB_OK|MB_ICONSTOP);
		} else {
			char error_msg[32768];
			sprintf(error_msg, "Could not start WinSock with error code: %d", WSAGetLastError());
			MessageBox( error_msg, "Error", MB_OK|MB_ICONSTOP);
		};
		return;
	};
	try {
		mainwin->IsConnected = TRUE;
	} catch(...) {

	};
	char sock_buffer[32768];
	char listing[32768];
	char listing_file[32768];
	char previous_listing[32768];
	char previous_listing_file[32768];

	char window_title[384];
	sprintf(window_title, "Tinelix IRC Client | %s", params.server);
	if(msg_history_string2 == "Enabled") {
		GetModuleFileName(NULL, h_pch, MAX_PATH);
		mainwin->delsymbs(h_pch, strlen(h_pch) - strlen(exe_name) - 1, strlen(h_pch) - strlen(exe_name) - 1); // deleting EXE filename
		DWORD winver = GetVersion();
		strcat(h_pch, "\\HISTORY");
		GetModuleFileName(NULL, h_pch2, MAX_PATH);
		mainwin->delsymbs(h_pch2, strlen(h_pch2) - strlen(exe_name), strlen(h_pch2) - strlen(exe_name) - 1); // deleting EXE filename
		strcat(h_pch2, "HISTORY");
		char current_time_ch[9];
		time_t current_time = time(NULL);
		strftime(current_time_ch, 9, "%y_%m_%d", localtime(&current_time));
		strcat(h_pch2, "\\");
		strcat(h_pch2, current_time_ch);	// add history filename
		sprintf(mainwin->history_path, "%s", h_pch);
		sprintf(mainwin->history_path2, "%s", h_pch2);
		char info_msg[120];
		int create_dir_status = CreateDirectory(h_pch, NULL);

		if(create_dir_status != 0 || GetLastError() == ERROR_ALREADY_EXISTS) {
			int create_dir_status_2 = CreateDirectory(h_pch2, NULL);
			if(create_dir_status_2 != 0 || GetLastError() == ERROR_ALREADY_EXISTS) {
				strcat(h_fch, h_pch2);
				strftime(current_time_ch, 9, "%H_%M_%S", localtime(&current_time));
				strcat(h_fch, "\\");
				strcat(h_fch, current_time_ch);
				strcat(h_fch, ".txt");
				sprintf(mainwin->history_file, "%s", h_fch);
			} if(GetLastError() == ERROR_PATH_NOT_FOUND || GetLastError() == ERROR_ACCESS_DENIED
				 || GetLastError() == ERROR_WRITE_PROTECT) {
				if(language_string2 == "Russian") {
                    char err_msg[8192];
                    char err_description[320];
                    if(GetLastError() == ERROR_PATH_NOT_FOUND) {
                        sprintf(err_description, "Путь не найден");
                    } if (GetLastError() == ERROR_ACCESS_DENIED) {
                        sprintf(err_description, "Доступ запрещен");
                    } if (GetLastError() == ERROR_WRITE_PROTECT) {
                        sprintf(err_description, "Данные защищены от записи");
                    };
                    sprintf(err_msg,"Ошибка создании папки: %s\r\nКод ошибки: %d (%s)", mainwin->history_path2, GetLastError(),
                            err_description);
                    MessageBox(err_msg, "Ошибка", MB_OK|MB_ICONSTOP);
                } else {
                    char err_msg[4096];
                    char err_description[320];
                    if(GetLastError() == ERROR_PATH_NOT_FOUND) {
                        sprintf(err_description, "Path not found");
                    } if (GetLastError() == ERROR_ACCESS_DENIED) {
                        sprintf(err_description, "Access denied");
                    } if (GetLastError() == ERROR_WRITE_PROTECT) {
                        sprintf(err_description, "Data is write-protected");
                    };
                    sprintf(err_msg,"Error creating folder: %s\r\nError code: %d (%s)", mainwin->history_path2, GetLastError(),
                            err_description);
                    MessageBox( err_msg, "Error", MB_OK|MB_ICONSTOP);
                };
			};

		} if(GetLastError() == ERROR_PATH_NOT_FOUND || GetLastError() == ERROR_ACCESS_DENIED
			 || GetLastError() == ERROR_WRITE_PROTECT) {
			if(language_string2 == "Russian") {
                    char err_msg[8192];
                    char err_description[320];
                    if(GetLastError() == ERROR_PATH_NOT_FOUND) {
                        sprintf(err_description, "Путь не найден");
                    } if (GetLastError() == ERROR_ACCESS_DENIED) {
                        sprintf(err_description, "Доступ запрещен");
                    } if (GetLastError() == ERROR_WRITE_PROTECT) {
                        sprintf(err_description, "Данные защищены от записи");
                    };
                    sprintf(err_msg,"Ошибка создании папки: %s\r\nКод ошибки: %d (%s)", mainwin->history_path, GetLastError(),
                            err_description);
                    MessageBox(err_msg, "Ошибка", MB_OK|MB_ICONSTOP);
            } else {
                    char err_msg[4096];
                    char err_description[320];
                    if(GetLastError() == ERROR_PATH_NOT_FOUND) {
                        sprintf(err_description, "Path not found");
                    } if (GetLastError() == ERROR_ACCESS_DENIED) {
                        sprintf(err_description, "Access denied");
                    } if (GetLastError() == ERROR_WRITE_PROTECT) {
                        sprintf(err_description, "Data is write-protected");
                    };
                    sprintf(err_msg,"Error creating folder: %s\r\nError code: %d (%s)", mainwin->history_path, GetLastError(),
                            err_description);
                    MessageBox(err_msg, "Error", MB_OK|MB_ICONSTOP);
                };
		};
	};

	AfxGetApp()->GetMainWnd()->SetWindowText(window_title);

	int WSAAsync = WSAAsyncSelect(sock, AfxGetApp()->GetMainWnd()->GetSafeHwnd(), WM_SOCKET_MESSAGE, FD_READ | FD_CLOSE);
	if (WSAAsync > 0) {
		if(language_string2 == "Russian") {
			char error_msg[32768];
			sprintf(error_msg, "Не удалось запустить WinSock с кодом ошибки: %d", WSAGetLastError());
			MessageBox(error_msg, "Ошибка", MB_OK|MB_ICONSTOP);
		} else {
			char error_msg[32768];
			sprintf(error_msg, "Could not start WinSock with error code: %d", WSAGetLastError());
			MessageBox(error_msg, "Error", MB_OK|MB_ICONSTOP);
		};
		return;
	};
	char ident_sending[400];
	int ident_sending_parts;
	ident_sending_parts = sprintf(ident_sending, "USER %s ", params.nickname);
	ident_sending_parts += sprintf(ident_sending + ident_sending_parts, "%s ", params.nickname);
	ident_sending_parts += sprintf(ident_sending + ident_sending_parts, "%s :", params.nickname);
	ident_sending_parts += sprintf(ident_sending + ident_sending_parts, "%s\r\n", params.realname);
	status = send(sock, ident_sending, strlen(ident_sending), 0);
	IRC_STATS irc_stats;
	sended_bytes_count = sended_bytes_count + status;
	irc_stats.sended_bytes = sended_bytes_count;
	irc_stats.recieved_bytes = recieved_bytes_count;
	mainwin->stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
	char nick_sending[400];
	int nick_sending_parts;
	nick_sending_parts = sprintf(nick_sending, "NICK %s\n", params.nickname);
	AfxGetMainWnd()->GetDlgItem(IDC_MSGTEXT)->EnableWindow(TRUE);
	status = send(sock, nick_sending, strlen(nick_sending), 0);
	mainwin->sended_bytes_count = mainwin->sended_bytes_count + status;
	irc_stats.sended_bytes = sended_bytes_count;
	irc_stats.recieved_bytes = recieved_bytes_count;
	mainwin->stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);

}

void MainWindow::CreateConnectionThread(PARAMETERS profile_params) 
{
	HWND hwnd;
	hwnd = m_hWnd;
	char change_font[100];
	sprintf(params.server, "%s", profile_params.server);
	sprintf(params.nickname, "%s", profile_params.nickname);
	sprintf(params.server, "%s", profile_params.server);
	sprintf(params.quit_msg, "%s", profile_params.quit_msg);
	params.port = profile_params.port;
	ConnectionFunc(hwnd, profile_params);

}


void MainWindow::OnClose() 
{
	WSACleanup();
	//cfunc FreeArray;
	//FreeArray = (cfunc)GetProcAddress((HMODULE)parserLib, "FreeArray");
	//FreeArray();
	TRACE("Quiting...\r\n");
	FreeLibrary(parserLib);
	TRACE("Shutting down library...\r\n");	
	CDialog::OnClose();
}

void MainWindow::OnTimer(UINT event)
{
	
};

LRESULT MainWindow::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename
	
	TCHAR language_string[MAX_PATH] = {0};
	TCHAR msg_history_string[MAX_PATH] = {0};
	TCHAR show_msgtime_string[MAX_PATH] = {0};
	TCHAR msgtime_pos_string[MAX_PATH] = {0};
	//try {
		if(message == WM_SOCKET_MESSAGE) {
				GetPrivateProfileString("Parser", "ShowMsgTime", "Enabled", show_msgtime_string, MAX_PATH, exe_path);
				GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
				GetPrivateProfileString("Main", "MsgHistory", "Enabled", msg_history_string, MAX_PATH, exe_path);
				GetPrivateProfileString("Parser", "MsgTimePos", "Right", msgtime_pos_string, MAX_PATH, exe_path);
				CString lng_selitemtext(language_string);
				CString msg_history_string2(msg_history_string);
				int status;
				char sock_buffer[32768] = {0};
				status = recv((SOCKET)wParam, (char*) &sock_buffer, 32767, 0);
				if (status == SOCKET_ERROR) {
					char error_msg[100];
					if(lng_selitemtext == "Russian") {
						sprintf(error_msg, "Ошибка сокета: %d", WSAGetLastError());
						MessageBox(error_msg, "Ошибка", MB_OK|MB_ICONSTOP);
					} else {
						sprintf(error_msg, "Socket error: %d", WSAGetLastError());
						MessageBox(error_msg, "Error", MB_OK|MB_ICONSTOP);
					};
					try {
						if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
							AfxGetApp()->GetMainWnd()->SetWindowText("Tinelix IRC Client (Win32s)");
						} else {
							AfxGetApp()->GetMainWnd()->SetWindowText("Tinelix IRC Client");
						};
						IsConnected = FALSE;
					} catch(...) {

					};
					exit;
				};
				IRC_STATS irc_stats;
				recieved_bytes_count = recieved_bytes_count + status;
				irc_stats.sended_bytes = sended_bytes_count;
				irc_stats.recieved_bytes = recieved_bytes_count;
				stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
				if (status == 0) {
					if(lng_selitemtext == "Russian") {
						MessageBox("Соединение потеряно.", "Информация", MB_OK|MB_ICONINFORMATION);
					} else {
						MessageBox("Connection lost.", "Information", MB_OK|MB_ICONINFORMATION);
					};
					closesocket(sock);
					if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
						AfxGetApp()->GetMainWnd()->SetWindowText("Tinelix IRC Client (Win32s)");
					} else {
						AfxGetApp()->GetMainWnd()->SetWindowText("Tinelix IRC Client");
					};
					IsConnected = FALSE;
					exit;
				};
				char listing[32768] = {0};
				char previous_listing[32768] = {0};
				int sp;
				AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS)->GetWindowText(previous_listing, 32767);
				if(previous_listing == NULL) {
				};
				sp = sprintf(listing, "%s", previous_listing);
				CString sock_buffer_str;
				char pong_msg[400];
				int string_index = 0;
				int array_index_2 = 0;
				char nwline[32768];
				char* parsed_msg;
				char* parsed_msg_list;
				parsed_msg_list = (char*)malloc(sizeof(char) * 32768);
				char* nw_token;
				CArray<CString, CString> new_line_splitter;
				while(AfxExtractSubString(sock_buffer_str, sock_buffer, string_index, '\n'))
				{
					new_line_splitter.Add(sock_buffer_str);
					++string_index;
				};
				CString pong;
				nw_token = strtok(sock_buffer, "\r\n");										   
				while(nw_token != NULL) {
					new_line_splitter[array_index_2++] = nw_token;
					nw_token = strtok(NULL, "\r\n");
				};

				int parsed_msg_index = 0;

                for (int i = 0; i < new_line_splitter.GetSize(); i++) {
					pong = "";
					//TRACE("LINE: %s\r\n", new_line_splitter[i]);
					if (new_line_splitter[i].Left(4) == "PING") {
						int pong_index;
						sprintf(pong_msg, "PONG %s\r\n", new_line_splitter[i].Right(strlen(new_line_splitter[i]) - 5));
						status = send((SOCKET)wParam, pong_msg, strlen(pong_msg), 0);
						pong = pong_msg;
						i = new_line_splitter.GetSize();
					} else {
						if(parserLib == NULL) {
							if(i >= new_line_splitter.GetSize() - 1) {
								parsed_msg_index += sprintf(parsed_msg_list + parsed_msg_index, "%s", new_line_splitter[i]);
							} else {
								parsed_msg_index += sprintf(parsed_msg_list + parsed_msg_index, "%s\r\n", new_line_splitter[i]);
							};
						} else {	
							char* unparsed_msg;
							char* unparsed_names_msg;
							char** parsing_array;
							char** owners_array;
							char** operators_array;
							char** members_array;
							unparsed_msg = (char*)calloc(sizeof(char), 32768 + 1);
							unparsed_names_msg = (char*)calloc(sizeof(char), 32768 + 1);
							parsed_msg = (char*)calloc(sizeof(char), 32768 + 1);
							parsing_array = (char**)calloc(sizeof(char*), 32768 + 1);
							for (int array_index = 0; array_index < sizeof(parsing_array); array_index++) {
								parsing_array[array_index] = (char*)calloc(sizeof(char), 32768 + 1);
							};
							sprintf(unparsed_msg, "%s", new_line_splitter[i]);
							sprintf(unparsed_names_msg, "%s", new_line_splitter[i]);
							ParseMessage ParseMsg;
							ParseNamesMessage ParseNamesMsg;
							ParseMsg = (ParseMessage)GetProcAddress((HMODULE)parserLib, "ParseMessage");
							ParseNamesMsg = (ParseNamesMessage)GetProcAddress((HMODULE)parserLib, "ParseNamesMessage");
							try {
								if(strcmp(show_msgtime_string, "Enabled") == 0) {
									if(strcmp(msgtime_pos_string, "Left") == 0) {
										ParseMsg(unparsed_msg, parsing_array, parsed_msg, FALSE, "left");
									} else {
										ParseMsg(unparsed_msg, parsing_array, parsed_msg, FALSE, "right");
									};
								} else {
									ParseMsg(unparsed_msg, parsing_array, parsed_msg, FALSE, "noshow");
								};
								CString p_msg(parsed_msg);
								if(strcmp(parsing_array[1], "353") == 0) {
									owners_array = (char**)calloc(sizeof(char*), 32768 + 1);
									operators_array = (char**)calloc(sizeof(char*), 32768 + 1);
									members_array = (char**)calloc(sizeof(char*), 32768 + 1);
									parsed_msg_index += sprintf(parsed_msg_list + parsed_msg_index, "");
									ParseNamesMsg(unparsed_names_msg, parsing_array, owners_array, operators_array, members_array, FALSE);
								} else if(strcmp(parsing_array[1], "PRIVMSG") == 0) {
									MENTIONED_MSG mentioned_message;
									sprintf(mentioned_message.mentioner, "%s", parsing_array[0]+1);
									int message_text_index = 0;
									int mention_index = 0;
									for(int array_index = 3; array_index < 32768; array_index++) {
										if(array_index == 3 && parsing_array[array_index] != NULL) {
											message_text_index += sprintf(mentioned_message.message + message_text_index, "%s", parsing_array[array_index]+1);
										} else if(array_index > 3 && parsing_array[array_index] != NULL) {
											if(message_text_index < 400) {
												message_text_index += sprintf(mentioned_message.message + message_text_index, " %s", parsing_array[array_index]);
											} else if(message_text_index >= 400 || strlen(parsing_array[array_index]) > 80) {
												message_text_index += sprintf(mentioned_message.message + message_text_index, "...");
												array_index = 131072;
											};
										};
									};
									CString parsed_array_part(mentioned_message.message);
									mention_index = parsed_array_part.Find(params.nickname);
									if(mention_index != -1) {
										mention_wnd->SendMessage(WM_USER_MENTION, NULL, (LPARAM)&mentioned_message);
									};
									TRACE(mentioned_message.message);
								} else {
									parsed_msg_index += sprintf(parsed_msg_list + parsed_msg_index, "%s", p_msg);
                                };
							} catch(...) {

							};
						};
					};
				};
				if(pong == "") {
					if(strlen(previous_listing) + strlen(parsed_msg_list) < 32768) {
						sp += sprintf(listing + sp, "%s",  parsed_msg_list);
					} else {
						sp = sprintf(listing, "%s",  parsed_msg_list);
					};
					if(msg_history_string2 == "Enabled") {
						if(history_file_stdio.Open(history_file, CFile::modeReadWrite)) {
							history_file_stdio.Write(listing, strlen(listing)*sizeof(char));
							history_file_stdio.Close();
						} else {
							if (history_file_stdio.Open(history_file, CFile::modeReadWrite | CFile::modeCreate)) {
								history_file_stdio.Write(listing, strlen(listing)*sizeof(char));
								history_file_stdio.Close();
							} else {
							};
						};
					};
					AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS)->SetWindowText(listing);
					CEdit* msg_box = (CEdit*)AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS);
					msg_box->SetSel(0, -1);
					msg_box->SetSel(-1);
				};
		} else if(message == WM_SYSCOMMAND && wParam == SC_MINIMIZE) {
			mention_wnd->ShowWindow(SW_HIDE);
		} else if(message == WM_SYSCOMMAND && wParam == SC_RESTORE) {
			mention_wnd->ShowWindow(SW_HIDE);
		};
	return CDialog::WindowProc(message, wParam, lParam);
}


LRESULT MainWindow::MessageOutput(WPARAM wp, LPARAM lp)
{
	
	SetWindowLong((HWND)wp, DWL_MSGRESULT, WM_SOCKET_MESSAGE);
	return 0;

}

void MainWindow::OnFileQuitClicked() 
{
	DestroyWindow();	
}

BOOL MainWindow::DestroyWindow() 
{		
	
	return CDialog::DestroyWindow();
}

void MainWindow::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
		
}

void MainWindow::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	CRect rect;
	
	GetDlgItem(IDC_SOCKMSGS)->MoveWindow(3, 2, cx - 6, cy - 28);
	GetDlgItem(IDC_JOINED_CHANNELS)->MoveWindow(3, cy - 23, 88, 90);
	GetDlgItem(IDC_MSGTEXT)->MoveWindow(93, cy - 23, cx - 163, 20);
	GetDlgItem(IDC_SENDMSG)->MoveWindow(cx - 68, cy - 24, 66, 22);
	CEdit* msg_box = (CEdit*)GetDlgItem(IDC_SOCKMSGS); 	
}

void MainWindow::OnHelpAboutClicked() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();	
}

void MainWindow::OnChangeMsgText() 
{
	char msg_text[1024] = {0};
	GetDlgItem(IDC_MSGTEXT)->GetWindowText(msg_text, 1024);
	CString msg_txt(msg_text);
	if (msg_txt != "" && msg_txt != " ") {
		GetDlgItem(IDC_SENDMSG)->EnableWindow(TRUE);
	} else {
		GetDlgItem(IDC_SENDMSG)->EnableWindow(FALSE);
	};	
}

void MainWindow::OnSendmsg() 
{
	
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	TCHAR language_string[MAX_PATH] = {0};
	CMenu* mainmenu;
	
	WSADATA WSAData;
	char szTemp[80];

	int status = (WSAStartup(MAKEWORD(1,1), &WSAData));

	GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);

	CString language_string_2(language_string);
	
	char msg_text[4096] = {0};
	char socks_msg[32768] = {0};
	GetDlgItem(IDC_SOCKMSGS)->GetWindowText(socks_msg, 32767);
	GetDlgItem(IDC_MSGTEXT)->GetWindowText(msg_text, 4096);
	CString msg_txt(msg_text);
	CArray<CString, CString> spaces_splitter;
	int string_index = 0;
	while(AfxExtractSubString(msg_txt, msg_text, string_index, ' '))
	{
		if(strlen(msg_txt) > 0) {
			spaces_splitter.Add(msg_txt);
		};
		++string_index;
	};
	
	CString first_symbol_in_args;
	CString args;
	CString slash;

	if(spaces_splitter.GetSize() >= 0) {
		exit;
	};

	slash = spaces_splitter[0][0];

	if(spaces_splitter.GetSize() >= 2) {
			first_symbol_in_args = spaces_splitter[1][0];
			for (int i = 1; i > spaces_splitter.GetSize(); i++) {
		  		args += spaces_splitter[i];
				if(i < (spaces_splitter.GetSize() - 1)) {
					args += " ";
				};
			}; 
	} else {
		first_symbol_in_args = "";
		args = "";
	};


	if(spaces_splitter[0] == "/join" && first_symbol_in_args != "#") {
		if(spaces_splitter.GetSize() > 1) {
			char join_msg[1024] = {0};
			sprintf(join_msg, "JOIN #%s\r\n", spaces_splitter[1]);
			sprintf(channel, "#%s", spaces_splitter[1]);
			int status = send(sock, join_msg, strlen(join_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
			CComboBox* joined_chs = (CComboBox*)GetDlgItem(IDC_JOINED_CHANNELS);
			joined_chs->EnableWindow(TRUE);
			joined_chs->AddString(channel);
		} else {
			if(language_string_2 == "Russian") {
				MessageBox("Пожалуйста, укажите аргумент к данной команде.", "Ошибка", MB_OK | MB_ICONSTOP);
			} else {
				MessageBox("Please enter an argument for this command.", "Error", MB_OK | MB_ICONSTOP);
			};
		};
	} else if(spaces_splitter[0] == "/join" && first_symbol_in_args == "#") {
		if(spaces_splitter.GetSize() > 1) {
            char join_msg[1024] = {0};
            sprintf(join_msg, "JOIN %s\r\n", spaces_splitter[1]);
            sprintf(channel, "%s", spaces_splitter[1]);
            int status = send(sock, join_msg, strlen(join_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);;
			CComboBox* joined_chs = (CComboBox*)GetDlgItem(IDC_JOINED_CHANNELS);
			joined_chs->EnableWindow(TRUE);
			joined_chs->AddString(channel);
			joined_chs->SelectString(NULL, channel);
        } else {
			if(language_string_2 == "Russian") {
				MessageBox("Пожалуйста, укажите аргумент к данной команде.", "Ошибка", MB_OK | MB_ICONSTOP);
			} else {
				MessageBox("Please enter an argument for this command.", "Error", MB_OK | MB_ICONSTOP);
			};
		};
	} else if(spaces_splitter[0] == "/part" && first_symbol_in_args != "#") {
        if(spaces_splitter.GetSize() > 1) {
            char part_msg[1024] = {0};
            sprintf(part_msg, "PART #%s\r\n", spaces_splitter[1]);
            sprintf(left_ch, "#%s", spaces_splitter[1]);
            int status = send(sock, part_msg, strlen(part_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
			CComboBox* joined_chs = (CComboBox*)GetDlgItem(IDC_JOINED_CHANNELS);
			int ch_index = 0;
			ch_index = joined_chs->FindString(ch_index, channel);
			if(ch_index != CB_ERR) {
				joined_chs->DeleteString(ch_index);
			};
        };
	} else if(spaces_splitter[0] == "/part" && first_symbol_in_args == "#") {
        if(spaces_splitter.GetSize() > 1) {
            char part_msg[1024] = {0};
            sprintf(part_msg, "PART %s\r\n", spaces_splitter[1]);
            sprintf(left_ch, "%s", spaces_splitter[1]);
            int status = send(sock, part_msg, strlen(part_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
			CComboBox* joined_chs = (CComboBox*)GetDlgItem(IDC_JOINED_CHANNELS);
			int ch_index = 0;
			ch_index = joined_chs->FindString(ch_index, channel);
			if(ch_index != CB_ERR) {
				joined_chs->DeleteString(ch_index);
			};
        };
	} else if(spaces_splitter[0] == "/part") {
		if(spaces_splitter.GetSize() == 1) {
			char part_msg[1024] = {0};
			CComboBox* joined_chs = (CComboBox*)GetDlgItem(IDC_JOINED_CHANNELS);
        	joined_chs->GetLBText(joined_chs->GetCurSel(), left_ch);
			sprintf(part_msg, "PART %s\r\n", left_ch);
        	int status = send(sock, part_msg, strlen(part_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
			int ch_index = 0;
			ch_index = joined_chs->FindString(ch_index, channel);
			if(ch_index != CB_ERR) {
				joined_chs->DeleteString(ch_index);
			};
		};
	} else if(spaces_splitter[0] == "/whois" && first_symbol_in_args != "#") {
        if(spaces_splitter.GetSize() > 1) {
            char whois_msg[1024] = {0};
            sprintf(whois_msg, "WHOIS %s\r\n", spaces_splitter[1]);
            int status = send(sock, whois_msg, strlen(whois_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
        } else {
            if(language_string_2 == "Russian") {
				MessageBox("Пожалуйста, укажите аргумент к данной команде.", "Ошибка", MB_OK | MB_ICONSTOP);
			} else {
				MessageBox("Please enter an argument for this command.", "Error", MB_OK | MB_ICONSTOP);
			};
        };
	} else if(spaces_splitter[0] == "/ping" && first_symbol_in_args != "#") {
        if(spaces_splitter.GetSize() > 1) {
            char ping_msg[1024] = {0};
            sprintf(ping_msg, "PING %s\r\n", spaces_splitter[1]);
            int status = send(sock, ping_msg, strlen(ping_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
        } else {
            if(language_string_2 == "Russian") {
				MessageBox("Пожалуйста, укажите аргумент к данной команде.", "Ошибка", MB_OK | MB_ICONSTOP);
			} else {
				MessageBox("Please enter an argument for this command.", "Error", MB_OK | MB_ICONSTOP);
			};
        };
	} else if(spaces_splitter[0] == "/privmsg") {
		char cmd_msg[1024] = {0};
		int msg_index = 0;
		if(spaces_splitter.GetSize() > 2) {
			msg_index = sprintf(cmd_msg, "PRIVMSG %s", spaces_splitter[1]);
			for (int i = 2; i < spaces_splitter.GetSize(); i++) {
				if(i == spaces_splitter.GetSize() - 1) {
					msg_index += sprintf(cmd_msg + msg_index, " %s\r\n", spaces_splitter[i]);
				} else if (i < spaces_splitter.GetSize() - 1) {
					msg_index += sprintf(cmd_msg + msg_index, " %s", spaces_splitter[i]);
				};
			};
			int status = send(sock, cmd_msg, strlen(cmd_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
		};
	} else if(spaces_splitter[0] == "/nickserv" && first_symbol_in_args != "#") {
		char cmd_msg[1024] = {0};
		int msg_index = 0;
		if(spaces_splitter.GetSize() > 2) {
			msg_index = sprintf(cmd_msg, "NICKSERV", spaces_splitter[1]);
			for (int i = 1; i < spaces_splitter.GetSize(); i++) {
				msg_index += sprintf(cmd_msg + msg_index, " %s", spaces_splitter[i]);
			};
			msg_index += sprintf(cmd_msg + msg_index, "\r\n");
			int status = send(sock, cmd_msg, strlen(cmd_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
		};
	} else if(spaces_splitter[0] == "/nick" && first_symbol_in_args != "#") {
		char cmd_msg[1024] = {0};
		int msg_index = 0;
		if(spaces_splitter.GetSize() >= 2) {
			msg_index = sprintf(cmd_msg, "NICK");	
			for (int i = 1; i < spaces_splitter.GetSize(); i++) {
				msg_index += sprintf(cmd_msg + msg_index, " %s", spaces_splitter[i]);
			};
			msg_index += sprintf(cmd_msg + msg_index, "\r\n");
			int status = send(sock, cmd_msg, strlen(cmd_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
		};
	} else if(spaces_splitter[0] == "/mode" && first_symbol_in_args != "#") {
		char cmd_msg[1024] = {0};
		int msg_index = 0;
		if(spaces_splitter.GetSize() >= 2) {
			msg_index = sprintf(cmd_msg, "MODE");	
			for (int i = 1; i < spaces_splitter.GetSize(); i++) {
				msg_index += sprintf(cmd_msg + msg_index, " %s", spaces_splitter[i]);
			};
			msg_index += sprintf(cmd_msg + msg_index, "\r\n");
			int status = send(sock, cmd_msg, strlen(cmd_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
		};
	} else if(spaces_splitter[0] == "/msg") {
		char cmd_msg[1024] = {0};
		int msg_index = 0;
		if(spaces_splitter.GetSize() > 2) {
			msg_index = sprintf(cmd_msg, "PRIVMSG %s", spaces_splitter[1]);
			for (int i = 2; i < spaces_splitter.GetSize(); i++) {
				if(i == spaces_splitter.GetSize() - 1) {
					msg_index += sprintf(cmd_msg + msg_index, " %s\r\n", spaces_splitter[i]);
				} if (i < spaces_splitter.GetSize() - 1) {
					msg_index += sprintf(cmd_msg + msg_index, " %s", spaces_splitter[i]);
				};
			};
			int status = send(sock, cmd_msg, strlen(cmd_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
		};
	} else if(spaces_splitter[0] == "/quit") {
		char cmd_msg[1024] = {0};
		int msg_index;
		msg_index = sprintf(cmd_msg, "QUIT %s\r\n", params.quit_msg);
		int status = send(sock, cmd_msg, strlen(cmd_msg), 0);
		IRC_STATS irc_stats;
		sended_bytes_count = sended_bytes_count + status;
		irc_stats.sended_bytes = sended_bytes_count;
		irc_stats.recieved_bytes = recieved_bytes_count;
		stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);	
	} else if(slash == "/") {
		if (strlen(spaces_splitter[0]) > 1) {
			char cmd_msg[1024] = {0};
			int msg_index;
			msg_index = sprintf(cmd_msg, "%s", spaces_splitter[0].Right(strlen(spaces_splitter[0]) - 1));
			if(args != "") {
				msg_index += sprintf(cmd_msg + msg_index, " %s\r\n", args);
			} else {
				msg_index += sprintf(cmd_msg + msg_index, "\r\n");
			};
			int status = send(sock, cmd_msg, strlen(cmd_msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
		};
		
	} else {
	   	char msg[1024] = {0};
		int msg_index;
		if(strcmp(channel, "(None)") != 0 && spaces_splitter[0][0] != '/') {
	   		msg_index = sprintf(msg, "PRIVMSG %s", channel);
			msg_index += sprintf(msg + msg_index, " :%s\r\n", msg_text);
			int status = send(sock, msg, strlen(msg), 0);
			IRC_STATS irc_stats;
			sended_bytes_count = sended_bytes_count + status;
			irc_stats.sended_bytes = sended_bytes_count;
			irc_stats.recieved_bytes = recieved_bytes_count;
			stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
		};
	};
	char listing[32768] = {0};
	if(strcmp(channel, "(None)") != 0) {
		sprintf(listing, "%sYou (%s): %s\r\n", socks_msg, channel, msg_text);
	} else {
		sprintf(listing, "%sYou: %s\r\n", socks_msg, msg_text);
	};
	CString listing_2(listing);
	GetDlgItem(IDC_SOCKMSGS)->SetWindowText(listing_2);
	GetDlgItem(IDC_MSGTEXT)->SetWindowText("");
	CEdit* msg_box = (CEdit*)AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS);
	msg_box->SetSel(0, -1);
	msg_box->SetSel(-1);
}

void MainWindow::OnOK() 
{	
	char* msg_text = (char*)malloc(4096);
	GetDlgItem(IDC_MSGTEXT)->GetWindowText(msg_text, 4096);
	if (strcmp(msg_text, "") != 0) {
		MainWindow::OnSendmsg();
	};
	//CDialog::OnOK();
}

void MainWindow::OnCancel() 
{	
	CDialog::OnCancel();
}

void MainWindow::OnViewSettings() 
{
	SettingsDialog setgdlg;
	int settings_modal = setgdlg.DoModal();
	if(settings_modal == IDOK) {
		IRC_STATS irc_stats;
		irc_stats.sended_bytes = sended_bytes_count;
		irc_stats.recieved_bytes = recieved_bytes_count;
		stats_dlg->SendMessage(WM_UPDATING_STATISTICS, NULL, (LPARAM)&irc_stats);
	};
	
}

void MainWindow::OnSelchangeJoinedChannels() 
{
	CComboBox* joined_chs = (CComboBox*)GetDlgItem(IDC_JOINED_CHANNELS);
    joined_chs->GetLBText(joined_chs->GetCurSel(), channel);
	
}

void MainWindow::OnFileStatistics() 
{
	stats_dlg->CenterWindow();
	stats_dlg->ShowWindow(SW_SHOW);
	
}

void MainWindow::OnDestroy() 
{
	CDialog::OnDestroy();
	
	delete stats_dlg;
    delete mention_wnd;
}
