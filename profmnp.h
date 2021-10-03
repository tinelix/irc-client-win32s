// profmnp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ProfileMainPage dialog

class ProfileMainPage : public CPropertyPage
{
	DECLARE_DYNCREATE(ProfileMainPage)

// Construction
public:
	ProfileMainPage();
	~ProfileMainPage();

// Dialog Data
	//{{AFX_DATA(ProfileMainPage)
	enum { IDD = IDD_PROFMAINPAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(ProfileMainPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont mainfont;
	// Generated message map functions
	//{{AFX_MSG(ProfileMainPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeNicknames();
	afx_msg void OnClose();
	afx_msg void OnChangePassword();
	afx_msg void OnChangeRealname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public: 	
	void delsymbs(char *str, int begin, int lng);
	char profilename[80];
	char currnickname[80];
	char password[20];
	char realname[160];
	void SetProfileName(LPCSTR name);
	void SetCurrentNickname(LPCSTR nick);
	void SetPassword(LPCSTR passw);
	void SetRealname(LPCSTR realn);
	friend class EditTextDlg;

};
