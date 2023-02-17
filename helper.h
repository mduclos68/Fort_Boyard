/*
* Description: Contains miscellaneous helper functions used by multiple modules
*/

#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

// Define audio files
#define FREN_RED_AUDIO      "colour-wav-files/Rouge.wav"
#define FREN_BLUE_AUDIO     "colour-wav-files/Bleu.wav"
#define FREN_YELLOW_AUDIO   "colour-wav-files/Jaune.wav"
#define FREN_GREEN_AUDIO    "colour-wav-files/Vert.wav"
#define FREN_GREY_AUDIO     "colour-wav-files/Gris.wav"
#define BUZZER_AUDIO        "colour-wav-files/buzzer.wav"
#define WIN_AUDIO           "colour-wav-files/win.wav"
#define DING_AUDIO          "colour-wav-files/ding.wav"

// Helper function that gets the current time in Ms
long long getTimeInMs(void);

// Helper function that reads from a file specified 
int Helper_readFromFile(char *fileName);

// Helper function that writes to a file specified 
void Helper_writeToFile(char *fileName, char* message);

// Helper function that runs a given system command
void Helper_runCommand(char* command);

// Helper function that sleeps for delayInMs
void Helper_sleepForMs(long long delayInMs);

// open and close all sound files
void openSoundFiles(void);
void closeSoundFiles(void);

#endif