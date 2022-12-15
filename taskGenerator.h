// button.h
// checks it a button has been pressed
#ifndef TASKGEN_H_
#define TASKGEN_H_

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#include "helper.h"
#include "button.h"
#include "audioMixer.h"

// Define audio files
#define RED_AUDIO      "colour-wav-files/Rouge.wav"
#define BLUE_AUDIO     "colour-wav-files/Bleu.wav"
#define YELLOW_AUDIO   "colour-wav-files/Jaune.wav"
#define GREEN_AUDIO    "colour-wav-files/Vert.wav"
#define GREY_AUDIO     "colour-wav-files/Gris.wav"
#define BUZZER_AUDIO   "colour-wav-files/buzzer.wav"
#define WIN_AUDIO      "colour-wav-files/win.wav"
#define DING_AUDIO     "colour-wav-files/ding.wav"

// Define colours to make it more convienient ot change languages
#define RED     "Rouge"
#define GREEN   "Vert"
#define GREY    "Gris"
#define YELLOW  "Jaune"
#define BLUE    "Bleu"

// Code to change the text colour
#define TEXT_COLOUR_RED    "\033[91m"
#define TEXT_COLOUR_GREEN  "\033[92m"
#define TEXT_COLOUR_GREY   "\033[37m"
#define TEXT_COLOUR_YELLOW "\033[33;1m"
#define TEXT_COLOUR_BLUE   "\033[94m"

void openSoundFiles(void);

void closeSoundFiles(void);

void TaskGenerator1_init(void);

void TaskGenerator1_cleanup(void);

void TaskGenerator2_init(void);

void TaskGenerator2_cleanup(void);

int getSuccess(void);

#endif