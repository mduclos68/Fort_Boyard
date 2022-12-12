// button.h
// checks it a button has been pressed
#ifndef BUTTON_H_
#define BUTTON_H_

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#include "gpio.h"

// Define button GPIO
#define RED_GPIO    30
#define BLUE_GPIO   50
#define YELLOW_GPIO 31
#define GREEN_GPIO  48
#define GREY_GPIO   60

#define RED_PIN    "p9.11"
#define BLUE_PIN   "p9.14"
#define YELLOW_PIN "p9.13"
#define GREEN_PIN  "p9.15"
#define GREY_PIN   "p9.12"

#define RED     0
#define BLUE    1
#define GREY    2
#define GREEN   3
#define YELLOW  4

// Initialize button thread
void Button_init(void);

// Stop button thread
void Button_cleanup(void);


// Checks if the right button has been pressed
bool rightButton(int colourWanted);


// Checks if a button has been pressed
bool isButtonPressed(void);
#endif