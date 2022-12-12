// main.c

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
    // initialize audio and button
    AudioMixer_init();
    Button_init();


    /*********** First Challenge ***********/
    printf("Tu dois obtenir un score de %d pour réussir cette épreuve. Bonne chance!\n", SCORE);
    Helper_sleepForMs(2000);

    // Start first task
    TaskGenerator1_init();

    // Wait for user to obtain the right score to exit the game
    while (true) {
        if (getSuccess() == 1) {
            break;
        }
    }
    printf("Félicitation, tu as réussi ton épreuve\n");

    // exit first task
    TaskGenerator1_cleanup();


    /*********** Second Challenge ***********/
    printf("Tu dois obtenir un score de %d pour réussir cette épreuve. Bonne chance!\n", SCORE);
    Helper_sleepForMs(2000);

    // Start second task
    TaskGenerator2_init();
    
    // Wait for user to obtain the right score to exit the game
    while (true) {
        if (getSuccess() == SCORE) {
            break;
        }
    }
    printf("Félicitation, tu as réussi ton épreuve\n");
    
    // exit second task
    TaskGenerator2_cleanup();
    




    // cleanup audio, button and task generator
    AudioMixer_cleanup(); 
    Button_cleanup();

    return 0;
}

