#ifndef INPUT_H // Include guards to prevent multiple inclusion
#define INPUT_H

extern int getValidatedInteger(const char *prompt);

extern char *getValidatedString(const char *prompt);

extern int isQuit(const char *str);

extern int failCount;

#endif
