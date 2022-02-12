// mentionw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MentionWindow dialog

#define WM_USER_MENTION 0xAFFB

class MentionWindow : public CDialog
{
// Construction
public:
	MentionWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MentionWindow)
	enum { IDD = IDD_MENTIONWND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MentionWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont titlefont;
	CFont mainfont;
	// Generated message map functions
	//{{AFX_MSG(MentionWindow)
	afx_msg void OnOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	struct MENTIONED_MSG 
	{
		char mentioner[128];
		char message[512];
	};
};
