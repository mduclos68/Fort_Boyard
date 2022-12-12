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
    sleepForMs(2000);

    // initialize task generator
    void TaskGenerator_init(void);

    // Wait for user to obtain the right score to exit the game
    while (true) {
        // Quit?
        if (getSuccess() == SCORE) {
            break;
        }
    }

    // Stops the task generator
    void TaskGenerator_cleanup();

    return 0;
}

