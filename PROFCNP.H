// profcnp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ProfileConnectionPage dialog

class ProfileConnectionPage : public CPropertyPage
{
	DECLARE_DYNCREATE(ProfileConnectionPage)

// Construction
public:
	ProfileConnectionPage();
	~ProfileConnectionPage();

// Dialog Data
	//{{AFX_DATA(ProfileConnectionPage)
	enum { IDD = IDD_PROFCONNPAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(ProfileConnectionPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont mainfont;
	// Generated message map functions
	//{{AFX_MSG(ProfileConnectionPage)
	afx_msg void OnChangeServer();
	afx_msg void OnChangePort();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	char server[80];
	INT port;
	char encoding[160];
	void delsymbs(char *str, int begin, int lng);

friend class EnterTextDlg;

};
