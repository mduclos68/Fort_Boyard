// mainGame.h
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


// Define colours to make it more convienient ot change languages
#define FREN_RED     "Rouge"
#define FREN_GREEN   "Vert"
#define FREN_GREY    "Gris"
#define FREN_YELLOW  "Jaune"
#define FREN_BLUE    "Bleu"
#define ENGL_RED     "Red"
#define ENGL_GREEN   "Grenn"
#define ENGL_GREY    "Grey"
#define ENGL_YELLOW  "Yellow"
#define ENGL_BLUE    "Blue"

// Code to change the text colour
#define TEXT_COLOUR_RED    "\033[91m"
#define TEXT_COLOUR_GREEN  "\033[92m"
#define TEXT_COLOUR_GREY   "\033[37m"
#define TEXT_COLOUR_YELLOW "\033[33;1m"
#define TEXT_COLOUR_BLUE   "\033[94m"

#endif