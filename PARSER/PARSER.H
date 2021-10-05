#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

extern "C" __declspec(dllexport) void ParseMessage(char* line, char* array[], char* output, BOOL debug);
extern "C" __declspec(dllexport) void FreeArray();

#endif
