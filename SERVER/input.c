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
                closeProgramWithError();

            printf("Invalid input. Please enter a valid integer or 'quit'. Still %d tries.\n", 3 - failCount);
        }
        else
        {
            printf("Error reading input.\n");
            closeProgramWithError();
        }
    }
}

char *getValidatedString()
{
    char input[32];

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline

            if (isQuit(input))
                closeProgram(); // Request to quit

            printf("Invalid input. Please enter 'quit'.\n");
        }
        else
        {
            printf("Error reading input.\n");
            closeProgramWithError();
        }
    }
}