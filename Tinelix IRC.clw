; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAppThreadTab
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tinelix IRC.h"

ClassCount=7
Class1=CIRCApplication
Class2=CMainDlg

ResourceCount=11
Resource1=IDD_TABTHREAD
Resource2=IDR_MAINFRAME
Resource3=IDD_TINELIXIRC_DIALOG
Resource4=IDD_ABOUTBOX
Resource5=IDR_MAINMENU (English (U.S.))
Resource6=IDD_TABCHAT
Class3=CAboutDlg
Class4=CAppThreadTab
Resource7=IDD_MAINDIALOG
Resource8=IDD_TEXTDIALOG
Class5=CConnManDlg
Resource9=IDD_CONNMANDIALOG
Class6=CProgressDlg
Resource10=IDD_CONNECTION_PROGRESS
Class7=CStatisticsDlg
Resource11=IDD_STATSDIALOG

[CLS:CIRCApplication]
Type=0
HeaderFile=Tinelix IRC.h
ImplementationFile=Tinelix IRC.cpp
Filter=N

[CLS:CMainDlg]
Type=0
HeaderFile=dialogs\maindlg.h
ImplementationFile=dialogs\maindlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHAT_SEND_MSG

[DLG:IDD_TINELIXIRC_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CMainDlg

[MNU:IDR_MAINMENU (English (U.S.))]
Type=1
Class=CMainDlg
Command1=ID_FILE_CONNECT
Command2=ID_FILE_QUIT
Command3=ID_CONNECTION_STATISTICS
Command4=ID_CHANNEL_JOIN
Command5=ID_CHANNEL_LEAVE
Command6=ID_ABOUT
CommandCount=6

[CLS:CAboutDlg]
Type=0
HeaderFile=dialogs\aboutdlg.h
ImplementationFile=dialogs\aboutdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TABCHAT]
Type=1
ControlCount=4
Control1=IDC_CHAT_INPUT,edit,1352730692
Control2=IDC_CHAT_OUTPUT,edit,1350631424
Control3=IDC_CHAT_SEND_MSG,button,1342242816
Control4=IDC_CHAT_MEMBERS,listbox,1352728835

[DLG:IDD_TABTHREAD]
Type=1
Class=CAppThreadTab
ControlCount=3
Control1=IDC_CHAT_INPUT,edit,1352730692
Control2=IDC_CHAT_OUTPUT,edit,1484849152
Control3=IDC_CHAT_SEND_MSG,button,1476460544

[DLG:IDD_MAINDIALOG]
Type=1
Class=CMainDlg
ControlCount=1
Control1=IDC_MAINDLG_TABS,SysTabControl32,1342177280

[CLS:CAppThreadTab]
Type=0
HeaderFile=tabs\appthreadtab.h
ImplementationFile=tabs\appthreadtab.cpp
BaseClass=CDialog
Filter=D
LastObject=CAppThreadTab
VirtualFilter=dWC

[DLG:IDD_CONNMANDIALOG]
Type=1
Class=CConnManDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PROFILE_LIST,listbox,1352728835
Control4=IDC_CREATE_PROFILE,button,1342242816
Control5=IDC_REMOVE_PROFILE,button,1342242816
Control6=IDC_EDIT_PROFILE,button,1342242816
Control7=IDC_PROFILES_GROUP,button,1342177287

[DLG:IDD_TEXTDIALOG]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDITTEXT,static,1342308352
Control4=IDC_EDITTEXTAREA,edit,1350631552

[CLS:CConnManDlg]
Type=0
HeaderFile=dialogs\ConnManDlg.h
ImplementationFile=dialogs\ConnManDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_CONNECTION_PROGRESS]
Type=1
Class=CProgressDlg
ControlCount=2
Control1=IDC_PROGRESS,msctls_progress32,1350565888
Control2=IDC_STATUS,static,1342308352

[CLS:CProgressDlg]
Type=0
HeaderFile=dialogs\ProgressDlg.h
ImplementationFile=dialogs\ProgressDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CProgressDlg
VirtualFilter=dWC

[DLG:IDD_STATSDIALOG]
Type=1
Class=CStatisticsDlg
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDC_PACKETS_GROUP,button,1342177287
Control3=IDC_PACKETS_SENT_LABEL,static,1342308352
Control4=IDC_PACKETS_SENT_VALUE,static,1342308354
Control5=IDC_PACKETS_READ_LABEL,static,1342308352
Control6=IDC_PACKETS_READ_VALUE,static,1342308354
Control7=IDC_BYTES_SENT_LABEL,static,1342308352
Control8=IDC_BYTES_SENT_VALUE,static,1342308354
Control9=IDC_READ_BYTES_LABEL,static,1342308352
Control10=IDC_BYTES_READ_VALUE,static,1342308354
Control11=IDC_TOTAL_BYTES_LABEL2,static,1342308352
Control12=IDC_TOTAL_BYTES_VALUE,static,1342308354
Control13=IDC_DATA_GROUP,button,1342177287
Control14=IDC_TOTAL_PACKETS_LABEL,static,1342308352
Control15=IDC_TOTAL_PACKETS_VALUE,static,1342308354
Control16=IDC_CONNECTION_GROUP,button,1342177287
Control17=IDC_CONNQUALITY_LABEL,static,1342308352
Control18=IDC_PING_STRENGTH,msctls_progress32,1350565888
Control19=IDC_CONNQUALITY_VALUE,static,1342308354

[CLS:CStatisticsDlg]
Type=0
HeaderFile=dialogs\StatisticsDlg.h
ImplementationFile=dialogs\StatisticsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CStatisticsDlg
VirtualFilter=dWC

