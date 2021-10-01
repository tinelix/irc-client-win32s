#include "parser.h"


extern "C" __declspec(dllexport) void ParseMessage(char* line, char* array[], char* output) {
	char msg[32768];
	if (line == NULL || output == NULL) {
		exit;
	};
	char* token;
	char* new_token;
	//OutputDebugString(line);
	int index = 0;
	int string_index = 0;
	char tr[32768];
	char code;
	char digit[32];
	token = strtok(line, " ");
	//new_token = strtok(line, " ");										   
	while(token != NULL) {
		array[index++] = token;
		token = strtok(NULL, " ");
	};
	
	OutputDebugString("Parsing...\r\n");

	for (int i = 0; i < index; i++) {
		if(i < 3 && strlen(array[i]) < 4) {
			sprintf(&code, "%s", array[i]);
		};
		//sprintf(digit, "IsDigit: %d\r\n", isdigit(code));
		//OutputDebugString(digit);
		if(i < 3 && strlen(array[i]) < 4 && isdigit(code) != 0) {
			string_index += sprintf(output + string_index, "Code %s:", array[i]);
		} if (i > index -2) {
			string_index += sprintf(output + string_index, " %s\r\n", array[i]);
		} else {
			if (i >= 3) {
				string_index += sprintf(output + string_index, " %s", array[i]);
			} if (i > 0 && index < 4) { 
				string_index += sprintf(output + string_index, " %s", array[i]);
			} if (index < 4) {
				string_index += sprintf(output + string_index, "%s", array[i]);
			};
		};	
	};


	try {
		output = tr;
	} catch(...) {

	};
	
};

extern "C" __declspec(dllexport) void FreeArray() {

};
