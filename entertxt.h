// entertxt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EnterTextDlg dialog

class EnterTextDlg : public CDialog
{
// Construction
public:
	EnterTextDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EnterTextDlg)
	enum { IDD = IDD_EDITTEXT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EnterTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont mainfont;
	// Generated message map functions
	//{{AFX_MSG(EnterTextDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void delsymbs(char *str, int begin, int lng);
	void SetSettingProfileState(BOOL value);
	void SetProfileName(char* name);
	BOOL setting_profile;
	char profilename[80];

friend class ProfileMainPage;
};
