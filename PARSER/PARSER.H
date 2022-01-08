#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

extern "C" __declspec(dllexport) void ParseMessage(char* line, char* array[], char* output, BOOL debug, char* clock_position);
extern "C" __declspec(dllexport) void ParseNamesMessage(char* line, char* array[], char* owners_array[], 
char* operators_array[], char* members_array[], BOOL debug);
extern "C" __declspec(dllexport) void ShowSettings();
extern "C" __declspec(dllexport) void ShowAboutWindow();
extern "C" __declspec(dllexport) void FreeArray();

char version_number[6];

#endif
