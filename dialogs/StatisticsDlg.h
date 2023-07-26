// StatisticsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatisticsDlg dialog

class CStatisticsDlg : public CDialog
{
// Construction

public:
	CStatisticsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatisticsDlg)
	enum { IDD = IDD_STATSDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatisticsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

public:
	void SetStatisticsData(struct NetworkStatistics stats);
	void SetConnectionQuality(int ping_value);
	void SetWSAWrapper(HINSTANCE wrapper);
	// Generated message map functions
	//{{AFX_MSG(CStatisticsDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};