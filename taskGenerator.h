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


void TaskGenerator_init(void);

void TaskGenerator_cleanup(void);

int getSuccess(void);

#endif