#ifndef GLOBALS_H
#define GLOBALS_H               
                    
#include <windows.h>

static char* AppName = "Tinelix IRC";
static char* BuildDate = "2022-12-04";
static char* DevState = "Alpha";
static char* AppVersion = "0.0.0-alpha_win16";     

/* Global instance handle */
extern HINSTANCE g_hInstance; 

static UINT WM_SOCKMSG = 0xAFFF;


#endif
