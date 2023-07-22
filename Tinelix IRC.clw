; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAppThreadTab
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tinelix IRC.h"

ClassCount=5
Class1=CIRCApplication
Class2=CMainDlg

ResourceCount=7
Resource1=IDD_TABCHAT
Resource2=IDR_MAINFRAME
Resource3=IDD_TINELIXIRC_DIALOG
Resource4=IDD_ABOUTBOX
Resource5=IDD_TABTHREAD
Resource6=IDR_MAINMENU (English (U.S.))
Class3=CAboutDlg
Class4=CMainDlgS
Class5=CAppThreadTab
Resource7=IDD_MAINDIALOG

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
Command1=ID_FILE_CONNECT
Command2=ID_FILE_QUIT
Command3=ID_CHANNEL_JOIN
Command4=ID_CHANNEL_LEAVE
Command5=ID_HELP_ABOUT
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
Control1=IDC_CHAT_INPUT,edit,1352728644
Control2=IDC_CHAT_OUTPUT,edit,1350631424
Control3=IDC_CHAT_SEND_MSG,button,1342242816
Control4=IDC_CHAT_MEMBERS,listbox,1352728835

[DLG:IDD_TABTHREAD]
Type=1
Class=CAppThreadTab
ControlCount=3
Control1=IDC_CHAT_INPUT,edit,1352728644
Control2=IDC_CHAT_OUTPUT,edit,1350631424
Control3=IDC_CHAT_SEND_MSG,button,1342242816

[CLS:CMainDlgS]
Type=0
HeaderFile=dialogs\maindlgs.h
ImplementationFile=dialogs\maindlgs.cpp
BaseClass=CDialog
Filter=D
LastObject=CMainDlgS
VirtualFilter=dWC

[DLG:IDD_MAINDIALOG]
Type=1
ControlCount=1
Control1=IDC_MAINDLG_TABS,SysTabControl32,1342177280

[CLS:CAppThreadTab]
Type=0
HeaderFile=tabs\appthreadtab.h
ImplementationFile=tabs\appthreadtab.cpp
BaseClass=CDialog
Filter=D
LastObject=CAppThreadTab

