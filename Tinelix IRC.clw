; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConnManDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tinelix IRC.h"

ClassCount=5
Class1=CIRCApplication
Class2=CMainDlg

ResourceCount=9
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
LastObject=CMainDlg

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
Command3=ID_CHANNEL_JOIN
Command4=ID_CHANNEL_LEAVE
Command5=ID_ABOUT
CommandCount=5

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
LastObject=ID_ABOUT

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

