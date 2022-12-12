/*
* Description: Contains functions to initialize and configure pin control using GPIO
*/

#ifndef _GPIO_H
#define _GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "helper.h"

// Config pin for GPIO
void GPIO_configPin(char* pinNum);

// Configure pin for input
void GPIO_setForInput(int gpioNum);

// Get pin value
int GPIO_getValue(int gpioNum);

#endif