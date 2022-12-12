// helper.h
// Description: Contains helper functions used by multiple modules
#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>


// Helper function that runs a given system command
void sleepForMs(long long delayInMs);

// Helper function that gets the current time in Ms
long long getTimeInMs(void);

#endif