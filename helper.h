/*
* Description: Contains miscellaneous helper functions used by multiple modules
* Created By: Kaleigh Toering & Laura Flood
* Contributors: Megan Duclos
* Originally Created For: ENSC 351 Assignment 1
* Sources Used: ENSC 351 GPIO guide and Assignment 1
*/

#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>


// Helper function that gets the current time in Ms
long long getTimeInMs(void);

// Helper function that reads from a file specified 
int Helper_readFromFile(char *fileName);

void Helper_writeToFile(char *fileName, char* message);

// Helper function that runs a given system command
void Helper_runCommand(char* command);

// Helper function that runs a given system command
void Helper_sleepForMs(long long delayInMs);

#endif