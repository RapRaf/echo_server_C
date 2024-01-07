#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"
#include "application.h"

int failCount = 0;

int isQuit(const char *str)
{
    return strcmp(str, "quit") == 0;
}

int getValidatedInteger(const char *prompt)
{
    int value;
    char input[20];

    while (1)
    {
        printf("%s", prompt);

        // GET INPUT STRING
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline

            if (isQuit(input))
                closeProgram(); // Request to quit

            // CONVERSION STRING TO INTEGER
            if (sscanf(input, "%d", &value) == 1)
            {
                failCount = 0;
                return value;
            }

            failCount += 1;

            if (failCount == 3)
                closeProgram();

            printf("Invalid input. Please enter a valid integer or 'quit'. Still %d tries.\n", 3 - failCount);
        }
        else
        {
            printf("Error reading input.\n");
            closeProgram();
        }
    }
}

char *getValidatedString(const char *prompt)
{
    char input[1024];

    while (1)
    {
        printf("%s", prompt);

        // GET INPUT STRING
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline

            if (isQuit(input))
                closeProgram(); // Request to quit

            if (strlen(input) > 0)
            {
                failCount = 0;
                return strdup(input); // Return a dynamically allocated copy of the string
            }

            failCount += 1;

            if (failCount == 3)
                closeProgram();

            printf("Invalid input. Please enter a non-empty string or 'quit'. Still %d tries.\n", 3 - failCount);
        }
        else
        {
            printf("Error reading input.\n");
            closeProgram();
        }
    }
}