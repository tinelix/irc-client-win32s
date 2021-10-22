// cnmandlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ConnectionManagerDialog dialog

class ConnectionManagerDialog : public CDialog
{
// Construction
public:
	ConnectionManagerDialog(CWnd* pParent = NULL);   // standard constructor
	void ConnectionManagerDialog::delsymbs(char *str, int begin, int lng);

// Dialog Data
	//{{AFX_DATA(ConnectionManagerDialog)
	enum { IDD = IDD_CONNMAN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ConnectionManagerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont mainfont;
	// Generated message map functions
	//{{AFX_MSG(ConnectionManagerDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddProfileClicked();
	afx_msg void OnConnectProfileClicked();
	virtual void OnOK();
	afx_msg void OnSelchangeProfilelist();
	afx_msg void ConnectionManagerDialog::OnChangeProfileBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	INT ConnectionManagerDialog::GetCountLines(LPCSTR str);
	void SetConnectionState(BOOL value);
	BOOL IsConnected;
};
