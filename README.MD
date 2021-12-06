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
<p><b>...and then you can run the IRC client.</b>
<h2>Known issues</h2>
<b>1. SSL not supported.</b>
<p>Use the <a href="https://github.com/tinelix/irc-client">Python version (in repo)</a> for this, but it is not compatible with older versions of Windows.
<p><b>2. Program crash when closing the "Profile Settings" window.</b>
<p>The thing is that the CPropertySheet object does not work very well with multiple tabs in those versions where there is a standard interface (with the Start menu, etc.). We are trying to solve this problem, but so far not very unsuccessfully.
<p><b>3. Standard encoding is system dependent.</b>
<p>I haven't figured out how to add this yet, but note that Unicode (UTF-16) is not supported in Win32s.
<p><b>4. <code>PARSER.DLL</code> does not work in Windows 3.1x.</b>
<p>Sorry, but to develop a string handler (parser) inside the main project (without DLL), then I had random crashes due to the array of the <code>char*</code> object. And no matter how much I tried to write the DLL again, it may still not start on Windows 3.1x.
<p>p. s. github codeberg, what a setup, I had sources 0.1.3 and 0.1.4 erased
