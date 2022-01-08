// parssdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParserSettingsDialog dialog

class ParserSettingsDialog : public CDialog
{
// Construction
public:
	ParserSettingsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ParserSettingsDialog)
	enum { IDD = IDD_PARSER_S };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParserSettingsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont mainfont;
	// Generated message map functions
	//{{AFX_MSG(ParserSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowMsgtime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
