// mainwin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MainWindow dialog

#define WM_SOCKET_MESSAGE 0xAFFF
#define WM_SOCKET_TIMER 1;
#define WM_UPDATING_STATISTICS 0xAFFC
#define WM_USER_MENTION 0xAFFB

#include "statsdlg.h"
#include "mentionw.h"

class MainWindow : public CDialog
{
// Construction
public:
	struct PARAMETERS
	{
		char server[256];
		char nickname[80];
		char realname[80];
		char quit_msg[256];
		int port;
		HWND hwnd;
	};
	struct IRC_STATS
	{
		int sended_bytes;
		int recieved_bytes;
	};
	struct MENTIONED_MSG
	{
		char mentioner[128];
		char message[512];
	};
	PARAMETERS params;
	MENTIONED_MSG mentioned_message;
	char channel[256];
	char left_ch[256];
	char app_version[20];
	char release_date[10];
	char exe_path[MAX_PATH];
	char history_path[MAX_PATH];
	char history_path2[MAX_PATH];
	char history_file[MAX_PATH];
	time_t current_time;
	int sended_bytes_count;
	int recieved_bytes_count;
	CStdioFile history_file_stdio;
	BOOL IsConnected;
	MainWindow(CWnd* pParent = NULL);	// standard constructor
	void MainWindow::CreateConnectionThread(PARAMETERS params);
	void MainWindow::delsymbs(char *str, int begin, int lng);
	void MainWindow::ConnectionFunc(HWND hwnd, struct PARAMETERS params);


// Dialog Data
	//{{AFX_DATA(MainWindow)
	enum { IDD = IDD_MAINWINDOW };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainWindow)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CFont font;
	CFont mainfont;
	StatisticsDialog* stats_dlg;
    MentionWindow* mention_wnd;

	// Generated message map functions
	//{{AFX_MSG(MainWindow)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnConnectClicked();
	afx_msg LRESULT MessageOutput(WPARAM wp, LPARAM lp);
	afx_msg void OnTimer(UINT event);
	afx_msg void OnFileQuitClicked();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHelpAboutClicked();
	afx_msg void OnChangeMsgText();
	afx_msg void OnSendmsg();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnViewSettings();
	afx_msg void OnSelchangeJoinedChannels();
	afx_msg void OnFileStatistics();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class ConnectionManagerDialog;
	friend class SettingsDialog;
	friend class IRCClient;
};
