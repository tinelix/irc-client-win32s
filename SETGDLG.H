// setgdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SettingsDialog dialog

class SettingsDialog : public CDialog
{
// Construction
public:
	SettingsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SettingsDialog)
	enum { IDD = IDD_SETTINGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettingsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SettingsDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeMsgFont();
	afx_msg void OnParserSettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CFont mainfont;
	char font_family[128];
	int font_size;
	int font_weight;
	char font_key[160];
	void delsymbs(char *str, int begin, int lng);

private:
	CFont msg_font;

friend class MainWindow;
};
