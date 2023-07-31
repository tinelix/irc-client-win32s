// TextBoxDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextBoxDlg dialog

class CTextBoxDlg : public CDialog
{
// Construction
public:
	CTextBoxDlg(CWnd* pParent = NULL);   // standard constructor
	void SetAction(int _action);

// Dialog Data
	//{{AFX_DATA(CTextBoxDlg)
	enum { IDD = IDD_TEXTDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CreateProfile();
	// Generated message map functions
	//{{AFX_MSG(CTextBoxDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
