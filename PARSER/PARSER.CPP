#include "parser.h"
#include <time.h>

extern "C" __declspec(dllexport) void ParseMessage(char* line, char* array[], char* output, BOOL debug, char* clock_position) {
	char msg[32768];
	if (line == NULL || output == NULL) {
		exit;
	};
	if(clock_position == NULL) {
		sprintf(clock_position, "right");
	} else if(strcmp(clock_position, "left") != 0 && strcmp(clock_position, "right") != 0 && strcmp(clock_position, "noshow") != 0) {
		sprintf(clock_position, "right");
	};
	char* token;
	char* new_token;
	//OutputDebugString(line);
	int index = 0;
	int points_index = 0;
	int string_index = 0;
	char tr[32768];
	char code;
	char privmsg_code[32768];
	char join_code[32768];
	char digit[32];
	token = strtok(line, " ");
	array[index] = token;
	//new_token = strtok(line, " ");										   
	while(token != NULL) {
		if(token[0] == ':' && index < 4) {
			array[index++] = token + 1;
		} else {
			array[index++] = token;
		};
		token = strtok(NULL, " ");
	};

	for (int i = 0; i < index; i++) {
		if(i < 2 && strlen(array[i]) < 4) {
			if(strcmp(array[1], "PRIVMSG") == 0) {
				sprintf(privmsg_code, "PRIVMSG"); 
			};
			if(strcmp(array[1], "JOIN") == 0) {
				sprintf(join_code, "Join"); 
			};
			if(isdigit(code) == 0) {
				sprintf(&code, "%s", array[i]);
			};
		};
		char current_time_ch[9];
		time_t current_time = time(NULL);
		strftime(current_time_ch, 9, "%H:%M:%S", localtime(&current_time));
		if (debug == TRUE) {
			OutputDebugString("WORD: [");
			OutputDebugString(array[i]);
			OutputDebugString("]\r\n");
			char index_str[40];
			char length_str[40];
			sprintf(index_str, "INDEX: %d\r\n", i); 
			sprintf(length_str, "LENGTH: %d\r\n", index); 
			OutputDebugString(index_str);
			OutputDebugString(length_str);
			OutputDebugString("\r\n");
		};
		if(i == 0 && strcmp(array[1], "PRIVMSG") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PRIVMSG.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			string_index += sprintf(output + string_index, "%s ", array[i]);
		} else if(i == 2 && strcmp(array[1], "PRIVMSG") == 0) {
			if(array[i][0] != '#') {
				if(strcmp(clock_position, "left") == 0) {
					string_index += sprintf(output + string_index, "(direct, %s):", current_time_ch);
				} else {
					string_index += sprintf(output + string_index, "(direct):");
				};
			} else {
				if(strcmp(clock_position, "left") == 0) {
					string_index += sprintf(output + string_index, "(#%s, %s):", array[i] + 1, current_time_ch);
				} else {
					string_index += sprintf(output + string_index, "(#%s):", array[i] + 1);
				};
			};
		} else if(i == 0 && strcmp(array[1], "JOIN") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is JOIN.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(strcmp(clock_position, "left") == 0) {
				string_index += sprintf(output + string_index, "(%s) %s joined the ", current_time_ch, array[i]);
			} else {
				string_index += sprintf(output + string_index, "%s joined the ", array[i]);
			};
		} else if(i == 0 && strcmp(array[1], "QUIT") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is QUIT.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(strlen(array[i]) < 3) {
				if(strcmp(clock_position, "right") == 0) {
					string_index += sprintf(output + string_index, "%s quited. (%s)\r\n", array[i], current_time_ch);
				} else if(strcmp(clock_position, "left") == 0) {
					string_index += sprintf(output + string_index, "(%s) %s quited.\r\n", current_time_ch, array[i]);
				} else {
					string_index += sprintf(output + string_index, "%s quited.\r\n", array[i]);
				};
			} else {
				if(strcmp(clock_position, "left") == 0) {
					string_index += sprintf(output + string_index, "(%s) %s quited with reason: [", current_time_ch, array[i]);
				} else {
					string_index += sprintf(output + string_index, "%s quited with reason: [", array[i]);
				};
			};
		} else if(i >= 2 && strcmp(array[1], "QUIT") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is QUIT.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(i > index - 2) {
				if(strcmp(clock_position, "right") == 0) {
					string_index += sprintf(output + string_index, "%s]. (%s)\r\n", array[i], current_time_ch);
				} else {
					string_index += sprintf(output + string_index, "%s].\r\n", array[i]);
				}
			} else {
				string_index += sprintf(output + string_index, "%s ", array[i]);
			};
		} else if(i == 0 && strcmp(array[1], "PART") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PART.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(strcmp(clock_position, "left") == 0) {
				string_index += sprintf(output + string_index, "(%s) %s left the ", current_time_ch, array[i]);
			} else {
				string_index += sprintf(output + string_index, "%s left the ", array[i]);
			};
		} else if(i >= 3 && strcmp(array[1], "PART") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PART.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(i > index - 2) {
				if(strcmp(clock_position, "right") == 0) {
					string_index += sprintf(output + string_index, "%s]. (%s)\r\n", array[i], current_time_ch);
				} else {
					string_index += sprintf(output + string_index, "%s].\r\n", array[i]);
				};
			} else {
				string_index += sprintf(output + string_index, "%s ", array[i]);
			};
		} else if(i == 0 && strcmp(array[1], "322") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is LIST (322).");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			
			string_index += sprintf(output + string_index, "%s\r\nTopic: ", array[3]);
		} else if(i >= 6 && strcmp(array[1], "322") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is LIST (322).");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(i > index - 2) {
				string_index += sprintf(output + string_index, "%s\r\nMembers: %d\r\n", array[i], atoi(array[4]));
				string_index += sprintf(output + string_index, "-----------------------------------\r\n", array[i]);
			} else {
				string_index += sprintf(output + string_index, "%s ", array[i]);
			};
		} else if(i == 2 && strcmp(array[1], "PART") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PART.");
				OutputDebugString("\r\n");
			};
			if(index <= 4) {
				if(strcmp(clock_position, "right") == 0) {
					string_index += sprintf(output + string_index, "%s channel. (%s)\r\n", array[i], current_time_ch);
				} else {
					string_index += sprintf(output + string_index, "%s channel.\r\n", array[i]);
				};
			} else {
				string_index += sprintf(output + string_index, "%s channel with reason: [", array[i]);
			};
		} else if(i == 2 && strcmp(array[1], "JOIN") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is JOIN.");
				OutputDebugString("\r\n");
			};
			if(strcmp(clock_position, "right") == 0) {
				string_index += sprintf(output + string_index, "%s channel. (%s)\r\n", array[i], current_time_ch);
			} else {
				string_index += sprintf(output + string_index, "%s channel.\r\n", array[i]);
			};
		} else if(i == 0 && strcmp(array[1], "311") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is WHOIS (311).");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "%s (%s@%s)\r\nReal name: ", array[3], array[4], array[5]);
		} else if(i == 0 && strcmp(array[1], "317") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is WHOIS (317).");
				OutputDebugString("\r\n");
			};
			char login_timeft[48];
			char idle_timeft[12];
			time_t login_time = atoi(array[5]);
			time_t idle_time = atoi(array[4]);
			strftime(login_timeft, 48, "%Y-%m-%d %H:%M:%S", localtime(&login_time));
			strftime(idle_timeft, 12, "%H:%M:%S", localtime(&idle_time));
			string_index += sprintf(output + string_index, "%s idle, last logon time - %s\r\n", idle_timeft, login_timeft);
		} else if(i >= 7 && strcmp(array[1], "311") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is WHOIS (311).");
				OutputDebugString("\r\n");
			};
			if(i > index - 2) {
				string_index += sprintf(output + string_index, "%s\r\n", array[i]);
				string_index += sprintf(output + string_index, "-----------------------------------\r\n", array[i]);
			} else if(i == 7) {
				string_index += sprintf(output + string_index, "%s ", array[i] + 1);
			} else {
				string_index += sprintf(output + string_index, "%s ", array[i]);
			};
		} else if(i >= 4 && strcmp(array[1], "312") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is WHOIS (312).");
				OutputDebugString("\r\n");
			};
			
		} else if(i >= 3 && strcmp(array[1], "317") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is WHOIS (317).");
				OutputDebugString("\r\n");
			};
			
		} else if(i < 3 && strlen(array[i]) < 4 && isdigit(code) != 0 && strcmp(array[1], "372") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is MOTD (372).");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "MOTD:");
		} else if(i < 3 && strlen(array[i]) < 4 && isdigit(code) != 0 && strcmp(array[1], "372") != 0 
			&& strcmp(array[1], "311") != 0 && strcmp(array[1], "312") != 0 && strcmp(array[1], "317") != 0 
			&& strcmp(array[1], "378") != 0 && strcmp(array[1], "318") != 0 && strcmp(array[1], "321") != 0 
			&& strcmp(array[1], "322") != 0 && strcmp(array[1], "323") != 0 && strcmp(array[1], "366") != 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is digit.");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "Code %s:", array[i]);
		} else if (i > index - 2 && strcmp(array[1], "JOIN") != 0 && strcmp(array[1], "QUIT") != 0 
			&& strcmp(array[1], "PART") != 0 && strcmp(array[1], "378") != 0 
			&& strcmp(array[1], "312") != 0 && strcmp(array[1], "317") != 0 
			&& strcmp(array[1], "318") != 0 && strcmp(array[1], "321") != 0 
			&& strcmp(array[1], "322") != 0 && strcmp(array[1], "323") != 0 
			&& strcmp(array[1], "366") != 0) {
			if (debug == TRUE) {
				OutputDebugString("Code isn't digit. (i > index - 2)");
				OutputDebugString("\r\n");
			};
			if(strcmp(array[1], "PRIVMSG") == 0) {
				if(strcmp(clock_position, "right") == 0) {
					string_index += sprintf(output + string_index, " %s (%s)\r\n", array[i], current_time_ch);
				} else {
					string_index += sprintf(output + string_index, " %s\r\n", array[i]);
				};
			} else {
				string_index += sprintf(output + string_index, " %s\r\n", array[i]);
			};

		} else {
			if (i >= 1 && i <= index - 2) {
				if ((strcmp(array[1], "PRIVMSG") == 0) && i == 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"PRIVMSG\") == 0) && i == 3)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if ((strcmp(array[1], "PRIVMSG") == 0) && i >= 4) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"PRIVMSG\") == 0) && i >= 4)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if ((strcmp(array[1], "372") == 0) && i == 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"372\") == 0) && i == 3)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if ((strcmp(array[1], "372") == 0) && i >= 4) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"372\") == 0) && i >= 4)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if (strcmp(array[1], "JOIN") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"JOIN\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "QUIT") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"QUIT\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "PART") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"PART\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "311") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"311\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "312") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"312\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "318") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"318\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "378") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"378\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "321") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"321\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "322") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"322\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "323") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"323\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "366") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"366\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if ((i == 1 && isdigit(code) == 0 && isdigit(code) == 0 && strcmp(array[1], "PRIVMSG") != 0 
					&& strcmp(array[1], "JOIN") != 0 && strcmp(array[1], "QUIT") != 0 && strcmp(array[1], "372") != 0 
					&& strcmp(array[1], "PART") != 0 && strcmp(array[1], "321") != 0 && strcmp(array[1], "322") != 0
					&& strcmp(array[1], "323") != 0 && strcmp(array[1], "366") != 0)) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (i == 1 && isdigit(code) == 0 && strcmp(array[1], \"PRIVMSG\")\r\n"
						"!= 0 && strcmp(array[1], \"JOIN\") != 0 && strcmp(array[1], \"QUIT\") != 0 && strcmp(array[1], \"372\") != 0)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, "%s", array[i]);
				} else if ((i > 1 && isdigit(code) == 0)) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (i > 1 && isdigit(code) == 0 && strcmp(array[1], \"PRIVMSG\") != 0\r\n"
						"&& strcmp(array[1], \"JOIN\") != 0 && strcmp(array[1], \"QUIT\") != 0 && strcmp(array[1], \"372\") != 0)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if (isdigit(code) > 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (isdigit(code) > 0 && i >= 3 && strcmp(array[1], \"372\") != 0)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				};		
			};
		};
	};


	//try {
		//output = tr;
	//} catch(...) {

	//};
	
};

extern "C" __declspec(dllexport) void ParseNamesMessage(char* line, char* array[], char* owners_array[], 
char* operators_array[], char* members_array[], BOOL debug) {					  
	int owners_index = 0;
	int operators_index = 0;
	int members_index = 0;
	for (int index = 5; index < 32768; index++) {
		if(array[index] == "\0" || array[index] == NULL) {
			
		} else if(array[index][0] == ':' && array[index][1] == '~') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if owner): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			owners_array[owners_index++] = array[index] + 2;
		} else if(array[index][0] == ':' && array[index][1] == '@') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if operator): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			operators_array[operators_index++] = array[index] + 2;
		} else if(array[index][0] == '~') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if owner without \":\" mask): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			owners_array[owners_index++] = array[index] + 1;
		} else if(array[index][0] == '@') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if operator without \":\" mask): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			operators_array[operators_index++] = array[index] + 1;
		} else if(array[index][0] == ':') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if member): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			members_array[members_index++] = array[index] + 1;
		} else {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if member without \":\" mask): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			members_array[members_index++] = array[index];
		};
	};
};

extern "C" __declspec(dllexport) void FreeArray() {

};
