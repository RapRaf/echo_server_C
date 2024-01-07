#ifndef APPLICATION_H // Include guards to prevent multiple inclusion
#define APPLICATION_H

#include <pthread.h>

extern void closeProgram();

extern void closeProgramWithError();

extern pthread_t thread_close;

#endif
