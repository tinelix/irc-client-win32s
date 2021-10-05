// proftabs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ProfileTabs

class ProfileTabs : public CPropertySheet
{
	DECLARE_DYNAMIC(ProfileTabs)

// Construction
public:
	ProfileTabs(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	ProfileTabs(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	char profile_name;
// Operations
public:
	void delsymbs(char *str, int begin, int lng);
	void SetProfileName(char *str);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProfileTabs)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ProfileTabs();

	// Generated message map functions
protected:
	CFont mainfont;
	//{{AFX_MSG(ProfileTabs)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
