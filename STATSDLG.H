// statsdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StatisticsDialog dialog

#define WM_UPDATING_STATISTICS 0xAFFC

class StatisticsDialog : public CDialog
{
// Construction
public:
	StatisticsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(StatisticsDialog)
	enum { IDD = IDD_STATISTICS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StatisticsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StatisticsDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int sended_bytes_count;
	int recieved_bytes_count;
	
	struct IRC_STATS 
	{
		int sended_bytes;
		int recieved_bytes;
	};
	CFont mainfont;
	void StatisticsDialog::delsymbs(char *str, int begin, int lng);
};
