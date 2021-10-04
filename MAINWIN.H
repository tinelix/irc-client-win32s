// mainwin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MainWindow dialog

#define WM_SOCKET_MESSAGE 0xAFFF
#define WM_SOCKET_TIMER 1;

class MainWindow : public CDialog
{
// Construction
public:
	struct PARAMETERS 
	{
		char server[256];
		char nickname[80];
		int port;
		HWND hwnd;
	};
	char channel[256];
	BOOL is_connected;
	MainWindow(CWnd* pParent = NULL);	// standard constructor
	void MainWindow::CreateConnectionThread(PARAMETERS params);
	void MainWindow::delsymbs(char *str, int begin, int lng);


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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class ConnectionManagerDialog;
};
