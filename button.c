#include "button.h"


// Define thread functions and variables
static bool stopping = false;
static pthread_t buttonId;

static bool buttonPressed = false;
static int colourSelected = 0;


// Checks if user selected the right button
bool rightButton(int colourWanted){
    if (colourWanted == colourSelected){
        return true;
    }
    return false;
}


// Checks if a button has been pressed
bool isButtonPressed(void){
    return buttonPressed;
}


// Button thread
static void* buttonThread(void* _arg){
    while(!stopping){

        if (GPIO_getValue(RED_GPIO) == 1){
            colourSelected = RED;
            buttonPressed = true;
        }

        else if (GPIO_getValue(BLUE_GPIO) == 1){
            colourSelected = BLUE;
            buttonPressed = true;
        }

        else if (GPIO_getValue(GREY_GPIO) == 1){
            colourSelected = GREY;
            buttonPressed = true;
        }

        else if (GPIO_getValue(GREEN_GPIO) == 1){
            colourSelected = GREEN;
            buttonPressed = true;
        }

        else if (GPIO_getValue(YELLOW_GPIO) == 1){
            colourSelected = YELLOW;
            buttonPressed = true;
        }

        else{
            buttonPressed = false;
        }

    }
    return NULL;
}


void Button_init(void){
    // Config pins for GPIO
    GPIO_configPin(RED_PIN);
    GPIO_configPin(BLUE_PIN);
    GPIO_configPin(YELLOW_PIN);
    GPIO_configPin(GREEN_PIN);
    GPIO_configPin(GREY_PIN);

    // Configure pin for input
    GPIO_setForInput(RED_GPIO);
    GPIO_setForInput(BLUE_GPIO);
    GPIO_setForInput(YELLOW_GPIO);
    GPIO_setForInput(GREEN_GPIO);
    GPIO_setForInput(GREY_GPIO);

    // Launch button thread:
    pthread_create(&buttonId, NULL, buttonThread, NULL);
}

void Button_cleanup(void){
    stopping = true;
    pthread_join(buttonId, NULL);
}
