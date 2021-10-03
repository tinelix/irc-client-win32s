<h1>Tinelix IRC Client for Win32s</h1>
Tinelix IRC <i>(Internet Relay Chat protocol)</i> client written on Microsoft Visual C++ 2.0 and designed for Windows 3.1x with Win32s.
<h2>Why is it needed?</h2>
1. <b>IRC</b> <i>(Internet Relay Chat)</i> - one of the oldest messaging protocols, that's why it was popular developers in the 90s before the ICQ, AIM and Windows Live Messenger era. Many clients were released that ran on almost any OS, including MS-DOS, Windows 3.1x, Windows 95, Linux and etc. <p><p>2. We want our client to work with older Windows versions as well. And this is a big advantage over current IT commerce, as this IRC client can even be used on older computers.
<h2>Screenshots</h2>
<img src="https://user-images.githubusercontent.com/76806170/134696539-1174cf08-5fad-47e5-a05e-efdbfb9115df.png"></img>
<h2>How to run this program on Windows 3.1x?</h2>
<b>Make sure you have:</b>
<p><p><b>1.</b> configured the Microsoft Windows Network via Network Setup (on Windows 3.1 / 3.11 for Workgroups), because the connection to IRC server is done using the WinSock component.
<p><img src="https://user-images.githubusercontent.com/76806170/134756327-ccf1dbea-7992-4168-9752-53ac4564ccaf.png"></img>
<p><b>2.</b> the Win32s compatibility layer installed. Version 1.25 or 1.30c is recommended.
<p><b>...and then you can run the IRC client<sup>*</sup>.</b>
<h6>* The <code>PARSER.DLL</code> (Tinelix IRC Parser library) does not work the Windows versions listed below:
<br>Windows 3.1x, Windows NT 3.1 / 3.5. But the program can run without this DLL.
  
 
