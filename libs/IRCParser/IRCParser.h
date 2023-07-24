#define EXPORT extern "C" __declspec (dllexport)

EXPORT char* CALLBACK ParseLine(char* original_line);