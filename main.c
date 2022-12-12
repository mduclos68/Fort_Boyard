// main.c
// Includes the userinterface. Allows the threads the start and wait for user
// to terminate them.

#include "taskGenerator.h"
#include "helper.h"

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
    printf("Tu dois obtenir un score de %d pour réussir cette épreuve. Bonne chance!\n", SCORE);
    Helper_sleepForMs(2000);

    // initialize task generator, audio and button
    AudioMixer_init();
    Button_init();
    TaskGenerator_init();

    // Wait for user to obtain the right score to exit the game
    while (true) {
        // Quit?
        if (getSuccess() == SCORE) {
            break;
        }
    }

    printf("Félicitation, tu as réussi ton épreuve\n");


    // cleanup audio, button and task generator
    AudioMixer_cleanup(); 
    Button_cleanup();
    TaskGenerator_cleanup();

    return 0;
}

