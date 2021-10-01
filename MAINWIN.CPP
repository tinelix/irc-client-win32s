// mainwin.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "mainwin.h"
#include "cnmandlg.h"

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
typedef void (WINAPI *ParseMessage)(char*, char*[], char*);

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
	while(*(str + begin++) = (str + begin + lng)[MAX_PATH]);
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog()
{

	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	CAboutDlg::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings");	// add settings filename

	TCHAR language_string[MAX_PATH] = {0};

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MainWindow::delsymbs(char *str, int begin, int lng)
{
	while(*(str + begin++) = (str + begin + lng)[MAX_PATH]);
};

/////////////////////////////////////////////////////////////////////////////
// MainWindow message handlers

BOOL MainWindow::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	CMenu* pSysMenu;
	pSysMenu = GetSystemMenu(FALSE);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	};
	font.CreateFont(11, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "Fixedsys");
	AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS)->SetFont(&font);
	if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
		SetWindowText("Tinelix IRC Client (Win32s)");
	} else {
		SetWindowText("Tinelix IRC Client");
	};
	char exe_path[MAX_PATH] = {0};
	char dll_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);
	GetModuleFileName(NULL, dll_path, MAX_PATH);  

	MainWindow::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename
	MainWindow::delsymbs(dll_path, strlen(dll_path) - strlen(exe_name) - 1, strlen(dll_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings");	// add settings filename

	strcat(dll_path, "\\parser.dll");

	parserLib = LoadLibrary(dll_path);

	TCHAR language_string[MAX_PATH] = {0};
	
	WSADATA WSAData;
	char szTemp[80];

	int status = (WSAStartup(MAKEWORD(1,1), &WSAData));

	try {
		GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
		CComboBox *language_combo = (CComboBox*)GetDlgItem(IDC_LANGCOMBO1);
		language_combo->SelectString(NULL, language_string);

		CString lng_selitemtext_2(language_string);
		if (lng_selitemtext_2 == "Russian") {
			GetDlgItem(IDC_SENDMSG)->SetWindowText("Отправить");
			if (status == 0) {
				TRACE("Winsock initialed.\r\n");
    		}
    		else {
				MessageBox("Winsock не может быть инициализирован.", "Ошибка", MB_OK|MB_ICONSTOP);
    		};
			MessageBox("Это альфа-версия данной программы. Многие функции на данный момент не реализованы.", "Предупреждение", MB_OK|MB_ICONEXCLAMATION);
			MoveWindow(40, 40, 600, 360);
		} else {
			GetDlgItem(IDC_SENDMSG)->SetWindowText("Send");
			if (status == 0) {
				TRACE("Winsock initialed.\r\n");
    		}
    		else {
				MessageBox("Winsock cannot be initialed.", "Error", MB_OK|MB_ICONSTOP);
    		};
			MessageBox("This is alpha version of program. Many features are not yet implemented.", "Warning", MB_OK|MB_ICONEXCLAMATION);
			MoveWindow(40, 40, 600, 360);
		};
	} 
	catch(...)
	{
		MessageBox("Error reading INI file.", "Error", MB_OK|MB_ICONSTOP);
	};
	
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
	
	CMenu* mainmenu = new CMenu();
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	MainWindow::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings");	// add settings filename

	TCHAR language_string[MAX_PATH] = {0};

	try {
		GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
		CComboBox *language_combo = (CComboBox*)GetDlgItem(IDC_LANGCOMBO1);
		language_combo->SelectString(NULL, language_string);

		CString lng_selitemtext_2(language_string);
		if(lng_selitemtext_2 == "Russian") {
			setlocale(LC_ALL, "Russian");
			if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {  // Win32s
				mainmenu->LoadMenu(IDR_MAINMENU);
				SetMenu(mainmenu);
			} else { // Win32/Win64
				mainmenu->LoadMenu(IDR_RUS_MAINMENU);
				SetMenu(mainmenu);
			};
		} else {
			setlocale(LC_ALL, "English");
			mainmenu->LoadMenu(IDR_MAINMENU);
			SetMenu(mainmenu);
		};
	}
	catch(...) {
	};
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
	connman.DoModal();
	
}

void ConnectionFunc(HWND hwnd, struct MainWindow::PARAMETERS params) 
{
	TCHAR exe_path[MAX_PATH] = {0};
	TCHAR history_path[MAX_PATH] = {0};
	TCHAR* exe_name = "TLX_IRC.EXE"; // EXE filename
	GetModuleFileName(NULL, exe_path, MAX_PATH);
	GetModuleFileName(NULL, history_path, MAX_PATH); 
	MainWindow* mainwin;
	mainwin->delsymbs(history_path, strlen(history_path) - strlen(exe_name) - 1, strlen(history_path) - strlen(exe_name) - 1); // deleting EXE filename
	strcat(history_path, "\\history.txt");	// add settings filename
	char server[256];
	sprintf(server, "%s", params.server);
	char connecting_msgb[100];
	int port = params.port;

	if (server == NULL || server == "")
	{
	  	TRACE("[SERVER_IS_NULL_ERROR] Not specified server address.\n");
		cout << "[SERVER_IS_NULL_ERROR] Not specified server address.\n" << endl << endl;
		exit;
	}; 
	if (port == NULL || port == 0)
	{
		TRACE("[PORT_IS_NULL_ERROR] Not specified server port.\n");
		cout << "[PORT_IS_NULL_ERROR] Not specified server port.\n" << endl << endl;
		exit;
	};

	char* connecting_msg;
	connecting_msg = "Trying connecting to %s:%d...\n";
	TRACE(connecting_msg, &server, port);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN client_param;
	hostent* host;
	if (sock == SOCKET_ERROR) {
		char* error_msg;
		error_msg = "[SOCKET_ERROR] Could not start WinSocket with error code: %d\n"; 
		TRACE0(error_msg, WSAGetLastError());
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
		TRACE("[NOHOST_ERROR] Could not calculate this hostname.\n");
	};
	client_param.sin_port = htons(port);
	connecting_msg = "Connecting...\n";
	TRACE(connecting_msg);
	int status;
	status = connect(sock, (SOCKADDR*)&client_param, sizeof(client_param));
	if (status == SOCKET_ERROR || status == INVALID_SOCKET) {
		char error_msg[100];
		wsprintf(error_msg, "[SOCKET_ERROR] Could not start WinSocket with error code: %d\n", WSAGetLastError()); 
		TRACE0(error_msg, WSAGetLastError());
	};
	char sock_buffer[32768];
	char listing[32768];
	char listing_file[32768];
	char previous_listing[32768];
	char previous_listing_file[32768];

	char window_title[384];
	sprintf(window_title, "Tinelix IRC Client | %s", params.server);

	AfxGetApp()->GetMainWnd()->SetWindowText(window_title);

	int WSAAsync = WSAAsyncSelect(sock, AfxGetApp()->GetMainWnd()->GetSafeHwnd(), WM_SOCKET_MESSAGE, FD_READ | FD_CLOSE);
	if (WSAAsync > 0) {
		char error_msg[100];
		wsprintf(error_msg, "[SOCKET_ERROR] Could not start WinSocket with error code: %d\n", WSAGetLastError());
	};
	char ident_sending[400];
	int ident_sending_parts;
	ident_sending_parts = sprintf(ident_sending, "USER %s ", params.nickname);
	ident_sending_parts += sprintf(ident_sending + ident_sending_parts, "%s ", params.nickname);
	ident_sending_parts += sprintf(ident_sending + ident_sending_parts, "%s :Member\r\n", params.nickname);
	status = send(sock, ident_sending, strlen(ident_sending), 0);
	char nick_sending[400];
	int nick_sending_parts;
	nick_sending_parts = sprintf(nick_sending, "NICK %s\n", params.nickname);
	mainwin = (MainWindow*)hwnd;
	AfxGetMainWnd()->GetDlgItem(IDC_MSGTEXT)->EnableWindow(TRUE);
	status = send(sock, nick_sending, strlen(nick_sending), 0);

}

void MainWindow::CreateConnectionThread(PARAMETERS params) 
{
	HWND hwnd;
	hwnd = m_hWnd;
	char change_font[100];
	ConnectionFunc(hwnd, params);

}


void MainWindow::OnClose() 
{
	WSACleanup();
	if (parserLib == NULL) {
		MessageBox("Не удалось загрузить библотеку \"PARSER.DLL\". Без нее программа может работать некорректно.", "Ошибка", MB_OK); 
		FreeLibrary(parserLib);
	} else {
		//cfunc FreeArray;
		//FreeArray = (cfunc)GetProcAddress((HMODULE)parserLib, "FreeArray");
		//FreeArray();
		TRACE("Quiting...\r\n");
		FreeLibrary(parserLib);
		TRACE("Shutting down library...\r\n");
	};
	SetMenu(NULL);	
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

	MainWindow::delsymbs(exe_path, strlen(exe_path) - strlen(exe_name) - 1, strlen(exe_path) - strlen(exe_name) - 1); // deleting EXE filename

	strcat(exe_path, "\\settings");	// add settings filename
	
	TCHAR language_string[MAX_PATH] = {0};
	//try {
		switch(message) {
			case WM_SOCKET_MESSAGE:
				GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
				CString lng_selitemtext(language_string);
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
					if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
						AfxGetApp()->GetMainWnd()->SetWindowText("Tinelix IRC Client (Win32s)");
					} else {
						AfxGetApp()->GetMainWnd()->SetWindowText("Tinelix IRC Client");
					};
					exit;
				};
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
					exit;
				};
				char listing[32768] = {0};
				char previous_listing[32768] = {0};
				int sp;
				AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS)->GetWindowText(previous_listing, 32767);
				if(previous_listing == NULL) {
				};
				sp = sprintf(listing, "%s\n", previous_listing);
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
						if( GetVersion() & 0x80000000 && (GetVersion() & 0xFF) ==3) {
							parsed_msg_index += sprintf(parsed_msg_list + parsed_msg_index, "%s\r\n", new_line_splitter[i]);
						} else {	
							char* unparsed_msg;
							char** parsing_array;
							unparsed_msg = (char*)malloc(sizeof(char) * 32768);
							parsed_msg = (char*)malloc(sizeof(char) * 32768);
							parsing_array = (char**)malloc(sizeof(char*) * 32768);
							for (int array_index = 0; array_index < sizeof(parsing_array); array_index++) {
								parsing_array[array_index] = (char*)malloc(sizeof(char) * 32768);
							};
							sprintf(unparsed_msg, "%s", new_line_splitter[i]);
							ParseMessage ParseMsg;
							ParseMsg = (ParseMessage)GetProcAddress((HMODULE)parserLib, "ParseMessage");
							try {
								ParseMsg(unparsed_msg, parsing_array, parsed_msg);
								//TRACE("OUTPUT: %s\r\n", parsed_msg);
								parsed_msg_index += sprintf(parsed_msg_list + parsed_msg_index, "%s", parsed_msg);
								
							} catch(...) {

							};
						};
					};
				};
				if(pong == "") {
					sp += sprintf(listing + sp, "%s",  parsed_msg_list);
					AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS)->SetWindowText(listing);
					CEdit* msg_box = (CEdit*)AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS);
					msg_box->SetSel(0, -1);
					msg_box->SetSel(-1);
				};
			break;	
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
	CloseWindow();	
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
	
	GetDlgItem(IDC_SOCKMSGS)->MoveWindow(2, 2, cx - 4, cy - 28);
	GetDlgItem(IDC_MSGTEXT)->MoveWindow(2, cy - 24, cx - 72, 22);
	GetDlgItem(IDC_SENDMSG)->MoveWindow(cx - 68, cy - 24, 66, 22); 	
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
	char msg_text[1024] = {0};
	char socks_msg[32768] = {0};
	GetDlgItem(IDC_SOCKMSGS)->GetWindowText(socks_msg, 32767);
	GetDlgItem(IDC_MSGTEXT)->GetWindowText(msg_text, 1024);
	CString msg_txt(msg_text);
	CArray<CString, CString> spaces_splitter;
	int string_index = 0;
	while(AfxExtractSubString(msg_txt, msg_text, string_index, ' '))
	{
		spaces_splitter.Add(msg_txt);
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
		char join_msg[1024] = {0};
		sprintf(join_msg, "JOIN #%s\r\n", spaces_splitter[1]);
		sprintf(channel, "#%s", spaces_splitter[1]);
		int status = send(sock, join_msg, strlen(join_msg), 0);
	} if(spaces_splitter[0] == "/join" && first_symbol_in_args == "#") {
		char join_msg[1024] = {0};
		sprintf(join_msg, "JOIN %s\r\n", spaces_splitter[1]);
		sprintf(channel, "%s", spaces_splitter[1]);
		int status = send(sock, join_msg, strlen(join_msg), 0);	
	} if(slash == "/") {
		char cmd_msg[1024] = {0};
		int msg_index;
		msg_index = sprintf(cmd_msg, "%s", spaces_splitter[0].Right(strlen(spaces_splitter[0]) - 1));
		if(args != "") {
			msg_index += sprintf(cmd_msg + msg_index, " %s\r\n", args);
		} else {
			msg_index += sprintf(cmd_msg + msg_index, "\r\n");
		};
		int status = send(sock, cmd_msg, strlen(cmd_msg), 0);	
	} else {
	   	char msg[1024] = {0};
		int msg_index;
		if(channel) {
	   		msg_index = sprintf(msg, "PRIVMSG %s ", channel);
			msg_index += sprintf(msg + msg_index, "%s\r\n", msg_text);
			int status = send(sock, msg, strlen(msg), 0);
		};
	};
	char listing[32768];
	sprintf(listing, "%s\r\nYou: %s", socks_msg, msg_text);	
	GetDlgItem(IDC_SOCKMSGS)->SetWindowText(listing);
	GetDlgItem(IDC_MSGTEXT)->SetWindowText("");
	CEdit* msg_box = (CEdit*)AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_SOCKMSGS);
	msg_box->SetSel(0, -1);
	msg_box->SetSel(-1);
}

void MainWindow::OnOK() 
{	
	//CDialog::OnOK();
}

void MainWindow::OnCancel() 
{	
	CDialog::OnCancel();
}
