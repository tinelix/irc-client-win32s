// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include <winsock.h>
#include "..\Tinelix IRC.h"
#include "..\tabs\AppThreadTab.h"
#include "AboutDlg.h"
#include "MainDlg.h"
#include "ConnManDlg.h"

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Global variables

CAppThreadTab *thread_tab;
HINSTANCE wsaWrap;
CString thread_input;

// WSAWrapper DLL functions;

typedef BOOL (WINAPI *EnableAsyncMessages) (HWND);
typedef int (WINAPI *GetWSAError) ();
typedef BOOL (WINAPI *CreateConnection) (char*, int);
typedef BOOL (WINAPI *SendSocketData) (char*);
typedef char* (WINAPI *GetInputBuffer) ();


/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// Loading WSAWrapper library. 
	// Available in https://github.com/tinelix/WSAWrapper (LGPLv2.1+)
	wsaWrap = LoadLibrary("wsawrap.dll");

	if(!wsaWrap) {
		MessageBox("wsawrap.dll loading error", "Error", MB_OK|MB_ICONSTOP);
	}


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

	char* app_name = "Tinelix IRC (Win32s)"; // LoadString is buggy...
	SetWindowText(app_name);

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
	}
	else
	{
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
	CreateConnection WrapCreateConn;
	EnableAsyncMessages EnableAsyncMsgs;

	char app_name[80];
	sprintf(app_name, "Tinelix IRC (Win32s) | %s:%d", address, port); // LoadString is buggy...

	// Running CreateConnection function (#17) in WSAWrapper DLL
	WrapCreateConn = (CreateConnection)GetProcAddress(wsaWrap, MAKEINTRESOURCE(17));
	if(!(*WrapCreateConn)(address, port)) {
		MessageBox("Connection error", address, MB_OK|MB_ICONSTOP);
	} else {
		SetWindowText(app_name);
	}
	// Running EnableAsyncMessages function (#15) in WSAWrapper DLL
	EnableAsyncMsgs = (EnableAsyncMessages)GetProcAddress(wsaWrap, MAKEINTRESOURCE(15));
	EnableAsyncMsgs(m_hWnd);
}

LRESULT CMainDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == 0xAFFF) {
		GetInputBuffer GetInBuff;
		char* sock_buffer;
		// Running GetInputBuffer function (#19) in WSAWrapper DLL
		GetInBuff = (GetInputBuffer)GetProcAddress(wsaWrap, MAKEINTRESOURCE(19));
		sock_buffer = (*GetInBuff)();
		CEdit* thread_input_box = (CEdit*)thread_tab->GetDlgItem(IDC_CHAT_INPUT);
		thread_input += CString(sock_buffer);
		thread_input_box->SetWindowText(thread_input);
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}
