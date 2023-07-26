// appthreadtab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppThreadTab dialog

class CAppThreadTab : public CDialog
{
// Construction
public:
	CAppThreadTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAppThreadTab)
	enum { IDD = IDD_TABTHREAD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppThreadTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CAppThreadTab)
	afx_msg void OnChatSendMsg();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
