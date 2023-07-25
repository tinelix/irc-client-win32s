// MainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

#define WM_SOCKET_READ 0xAFFF;


class CMainDlg : public CDialog
{
// Construction
public:
	BOOL is_connected;

	CMainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_MAINDIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CFont font;
	void CreateTabs();
	void PrepareConnect(LPSTR address, int port);
	void PrepareConnect(int result);
	void ImportDllFunctions();
	void IdentificateConnection();
	void SendPing(CString ping_hexcode);
	CString ParseMessage(char* irc_packet);

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuHelpAbout();
	afx_msg void OpenConnectionManager();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnConnectionStatistics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CConnManDlg;
};
