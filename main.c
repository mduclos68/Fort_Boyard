// main.c

#include "taskGenerator.h"
#include "helper.h"
#include "audioMixer.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <alsa/asoundlib.h>

#define SCORE 10



int main()
{    
    // initialize audio and button
    AudioMixer_init();
    Button_init();
    openSoundFiles();

    /*********** First Challenge ***********/
    TaskGenerator1_init();

    // Wait for user to obtain the right score to exit the game
    while (true) {
        if (getSuccess() == SCORE) {
            break;
        }
    }

    // exit first task
    TaskGenerator1_cleanup();

    /*********** Second Challenge ***********/
    TaskGenerator2_init();
    
    // Wait for user to obtain the right score to exit the game
    while (true) {
        if (getSuccess() == SCORE) {
            break;
        }
    }

    // exit second task
    TaskGenerator2_cleanup();
    

    /*********** Third Challenge ***********/
    // Start second task
    TaskGenerator3_init();
    
    // Wait for user to obtain the right score to exit the game
    while (true) {
        if (getSuccess() == 7) {
            break;
        }
    }
    // exit second task
    TaskGenerator3_cleanup();



    // cleanup audio, button and task generator
    closeSoundFiles();
    AudioMixer_cleanup(); 
    Button_cleanup();

    return 0;
}

