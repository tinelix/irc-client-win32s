// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include <winsock.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "..\Tinelix IRC.h"
#include "..\tabs\AppThreadTab.h"
#include "AboutDlg.h"
#include "MainDlg.h"
#include "ConnManDlg.h"
#include "ProgressDlg.h"
#include "StatisticsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_ABOUT, OnMenuHelpAbout)
	ON_COMMAND(ID_FILE_CONNECT, OpenConnectionManager)
	ON_WM_SIZE()
	ON_COMMAND(ID_CONNECTION_STATISTICS, OnConnectionStatistics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Global variables

CAppThreadTab *thread_tab;
HINSTANCE wsaWrap;
HINSTANCE ircParser;
CString thread_input;
BOOL isWin3x;
char* conn_server;
char* app_name;
int new_unread_messages;
char g_address[256];
int g_port;
CProgressDlg progressDlg;
CStatisticsDlg statisticsDlg;

// WSAWrapper DLL functions;

typedef BOOL (WINAPI *EnableAsyncMessages) (HWND);
typedef int (WINAPI *GetWSAError) ();
typedef int (WINAPI *CreateAsyncConnection) (char*, int, int, int, HWND);
typedef BOOL (WINAPI *SendSocketData) (char*);
typedef char* (WINAPI *GetInputBuffer) ();

CreateAsyncConnection WrapCreateConn;
EnableAsyncMessages EnableAsyncMsgs;
SendSocketData SendOutBuff;
GetInputBuffer GetInBuff;
GetWSAError GetWSAErrorFunc;


// Tinelix IRC Parser functions:

typedef char* (WINAPI *ParseIRCPacketFunc) (char*);

ParseIRCPacketFunc ParseIRCPacket;

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	isWin3x = (GetVersion() & 0xFF) == 3;

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// Loading WSAWrapper library. 
	// Available in https://github.com/tinelix/WSAWrapper (LGPLv2.1+)
	wsaWrap = LoadLibrary("wsawrap.dll");
	conn_server = "";

	if(!wsaWrap) {
		MessageBox("wsawrap.dll loading error", "Error", MB_OK|MB_ICONSTOP);
		DestroyWindow();
		return FALSE;
	}

	ircParser = LoadLibrary("ircpars.dll");
	if(!ircParser) {
		MessageBox("ircpars.dll loading error", "Error", MB_OK|MB_ICONSTOP);
	}

	ImportDllFunctions();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	app_name = "Tinelix IRC (Win32s)"; // LoadString is buggy...
	SetWindowText(app_name);
	progressDlg.Create(CProgressDlg::IDD, this);
	statisticsDlg.Create(CStatisticsDlg::IDD, this);
	statisticsDlg.SetWSAWrapper(wsaWrap);

	EnableWindow(TRUE);

	CreateTabs();
	
	return TRUE;
}


void CMainDlg::CreateTabs() {
	CTabCtrl* tabCtrl = (CTabCtrl*)GetDlgItem(IDC_MAINDLG_TABS);
	TC_ITEM tabItem;
	tabItem.mask = TCIF_TEXT;
	char* tab_title = "Thread";
	tabItem.pszText = tab_title;
	tabCtrl->InsertItem(0, &tabItem);
	thread_tab = new CAppThreadTab;
	thread_tab->Create(IDD_TABTHREAD, this);
	tabItem.lParam = (LPARAM)thread_tab;
	thread_tab->SetWindowPos(NULL, 6, 24, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	thread_tab->ShowWindow(SW_SHOW);
	CEdit* thread_input_box = (CEdit*)thread_tab->GetDlgItem(IDC_CHAT_INPUT);
	font.CreateFont(11, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, "Fixedsys");
	thread_input_box->SetFont(&font);

}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg aboutDlg;
		aboutDlg.DoModal();
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

//  If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint() 
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

//  The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CMainDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, 
					  DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
					  UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CMainDlg::OnMenuHelpAbout() 
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CMainDlg::DestroyWindow() 
{
	if(thread_tab != NULL && thread_tab->m_hWnd != NULL ) {
		thread_tab->DestroyWindow();
		delete thread_tab;
	}

	if(wsaWrap != NULL) {
		FreeLibrary(wsaWrap);
	}
	
	return CDialog::DestroyWindow();
}

void CMainDlg::OpenConnectionManager() 
{
	CConnManDlg connman;
	if(connman.DoModal() == IDOK) {
		char* server;
		sprintf(server, "irc.tinelix.ru"); // for example, because profiles not impemented.
		PrepareConnect(server, 6667);
	}
}

void CMainDlg::PrepareConnect(char* address, int port) {
	sprintf(g_address, address);
	g_port = port;
	progressDlg.SetProgress(0);
	sprintf(app_name, "Tinelix IRC (Win32s) | %s:%d", address, port); // LoadString is buggy...
	sprintf(conn_server, "%s:%d", address, port);
	progressDlg.CenterWindow();
	progressDlg.ShowWindow(SW_SHOW);
	int result = (*WrapCreateConn)(address, port, 0, 0xB001, m_hWnd);
	if(result == 0) {
		int error_code = ((*GetWSAErrorFunc)());
		char error_msg[32];
		sprintf(error_msg, "Connection error #%d", error_code);
		MessageBox(error_msg, address, MB_OK|MB_ICONSTOP);
		sprintf(app_name, "Tinelix IRC (Win32s)", address, port); // LoadString is buggy...
	} else if(result == 1) {
		IdentificateConnection();
		EnableAsyncMsgs(m_hWnd);
		SetWindowText(app_name);
	}
}

void CMainDlg::PrepareConnect(int result) {
	if(result == 0) {
		int error_code = ((*GetWSAErrorFunc)());
		char error_msg[32];
		sprintf(error_msg, "Connection error #%d", error_code);
		MessageBox(error_msg, g_address, MB_OK|MB_ICONSTOP);
		sprintf(app_name, "Tinelix IRC (Win32s)"); // LoadString is buggy...
	} else if(result == 1) {
		if(progressDlg.m_hWnd) {
			progressDlg.SetProgress(100);
		}
		IdentificateConnection();
		EnableAsyncMsgs(m_hWnd);
		SetWindowText(app_name);
	}
}

void CMainDlg::ImportDllFunctions() {
	// Running EnableAsyncMessages function (#15) in WSAWrapper DLL
	EnableAsyncMsgs = (EnableAsyncMessages)GetProcAddress(wsaWrap, MAKEINTRESOURCE(15));
	// Running GetWSAError function (#16) in WSAWrapper DLL
	GetWSAErrorFunc = (GetWSAError)GetProcAddress(wsaWrap, MAKEINTRESOURCE(16));
	// Running CreateAsyncConnection function (#18) in WSAWrapper DLL
	WrapCreateConn = (CreateAsyncConnection)GetProcAddress(wsaWrap, MAKEINTRESOURCE(18));
	// Running SendData function (#19) in WSAWrapper DLL
	SendOutBuff = (SendSocketData)GetProcAddress(wsaWrap, MAKEINTRESOURCE(19));
	// Running GetInputBuffer function (#20) in WSAWrapper DLL
	GetInBuff = (GetInputBuffer)GetProcAddress(wsaWrap, MAKEINTRESOURCE(20));

	ParseIRCPacket = (ParseIRCPacketFunc)GetProcAddress(ircParser, MAKEINTRESOURCE(2));

}

void CMainDlg::IdentificateConnection() {
	char* ident_str = "";
	sprintf(ident_str, "USER %s %s %s :Member\r\n",
		"irc_member", "irc_member", "irc_member");
	if(!(*SendOutBuff)(ident_str)) {
		int error_code = ((*GetWSAErrorFunc)());
		char error_msg[32];
		sprintf(error_msg, "Identification error #%d", error_code);
		MessageBox(error_msg, conn_server, MB_OK|MB_ICONSTOP);
		return;
	}
	sprintf(ident_str, "NICK %s\r\n", "irc_member");
	BOOL result = (*SendOutBuff)(ident_str);
	if(progressDlg.m_hWnd) {
		progressDlg.Close();
		EnableWindow(TRUE);
	}
	if(!result) {
		int error_code = ((*GetWSAErrorFunc)());
		char error_msg[32];
		sprintf(error_msg, "Identification error #%d", error_code);
		MessageBox(error_msg, conn_server, MB_OK|MB_ICONSTOP);
		return;
	} else {
		CEdit* thread_output_box = (CEdit*)thread_tab->GetDlgItem(IDC_CHAT_OUTPUT);
		thread_output_box->EnableWindow(TRUE);
		CButton* thread_send_btn = (CButton*)thread_tab->GetDlgItem(IDC_CHAT_SEND_MSG);
		thread_send_btn->EnableWindow(TRUE);
	}
}

void CMainDlg::SendPing(CString ping_hexcode) {	
	CString ping_str = "";
	ping_str.Format("PONG %s\r\n", ping_hexcode);
	struct _timeb until_pong;
	_ftime(&until_pong);
	if((*SendOutBuff)(ping_str.GetBuffer(ping_str.GetLength()))) {
		struct _timeb after_pong;
		_ftime(&after_pong);
		TRACE("Difference: %d ms", after_pong.millitm - until_pong.millitm);
		statisticsDlg.SetConnectionQuality(after_pong.millitm - until_pong.millitm);
	}
}

LRESULT CMainDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == 0xB001) {
		progressDlg.SetProgress(50);
		int result = (*WrapCreateConn)("", 0, 1, 0xB001, m_hWnd);
		PrepareConnect(result);
	} else if(message == 0xAFFF) {
		new_unread_messages += 1;
		char* sock_buffer;
		sock_buffer = (*GetInBuff)();
		CEdit* thread_input_box = (CEdit*)thread_tab->GetDlgItem(IDC_CHAT_INPUT);
		CString sock_buff_str = CString(sock_buffer);
		if(sock_buff_str == "[WSAWrapper] 0xE0001\r\n") {
			MessageBox("Connection closed", conn_server, MB_OK|MB_ICONINFORMATION);
			app_name = "Tinelix IRC (Win32s)";
			conn_server = "";
			SetWindowText(app_name);
		} else if(sock_buff_str.GetLength() > 0) {
			if(sock_buff_str.Left(4) == "PING") {
				SendPing(sock_buff_str.Right(sock_buff_str.GetLength() - 3));
			} else {
				if(ircParser != NULL) {
					CString parsed_str = CString("");
					parsed_str = CString(
						ParseMessage(sock_buff_str.GetBuffer(sock_buff_str.GetLength()))
					);
					thread_input += parsed_str;
					thread_input_box->SetWindowText(thread_input);
				} else {
					thread_input += CString(sock_buffer);
					thread_input_box->SetWindowText(thread_input);
				}
			}
		}
	} else if(message == 0xAFFE) {
		EnableWindow(FALSE);
		char status[48];
		sprintf(status, "Connecting with %s...", conn_server);
		if(progressDlg.m_hWnd) {
			progressDlg.ShowWindow(SW_SHOW);
			progressDlg.SetStatus(CString(status));
		}
	} else if(message == 0xE0001) {
		MessageBox("Connection closed", conn_server, MB_OK|MB_ICONINFORMATION);
		app_name = "Tinelix IRC (Win32s)";
		conn_server = "";
		SetWindowText(app_name);
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}

void CMainDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(isWin3x) {  
		// Setting window title in Win3.x / WinNT3.x 
		// for greater compactness.
		if(nType != SIZE_MINIMIZED) {
			SetWindowText(app_name);
		} else if(strlen(conn_server) > 0) {
			SetWindowText(conn_server);
		}
	}
}

CString CMainDlg::ParseMessage(char* irc_packet) {
	char* parsed_packet = "";
	parsed_packet = (*ParseIRCPacket)(irc_packet);

	return CString(parsed_packet);
};

void CMainDlg::OnConnectionStatistics() 
{
	statisticsDlg.CenterWindow();
	statisticsDlg.ShowWindow(SW_SHOW);
}
