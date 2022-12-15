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

#define SCORE 5
#define SPEECH_LENGTH_START  27000
#define SPEECH_LENGHT_TASK_1 27000
#define SPEECH_LENGHT_TASK_2 27000
#define SPEECH_LENGHT_TASK_3 33000

#define START_MESSAGE_AUDIO "colour-wav-files/Message_dentree.wav"
#define TASK1_AUDIO "colour-wav-files/Message_Jeu_1.wav"
#define TASK2_AUDIO "colour-wav-files/Message_Jeu_2.wav"
#define TASK3_AUDIO "colour-wav-files/Message_Jeu_3.wav"

static wavedata_t *pSound;


int main()
{    
    // initialize audio and button
    AudioMixer_init();
    Button_init();
    openSoundFiles();

    /*********** First Challenge ***********/
    // read opening message
    AudioMixer_readWaveFileIntoMemory(START_MESSAGE_AUDIO, pSound);
    AudioMixer_queueSound(pSound);
    Helper_sleepForMs(SPEECH_LENGTH_START);
    AudioMixer_freeWaveFileData(pSound);

    // Read first task
    AudioMixer_readWaveFileIntoMemory(TASK1_AUDIO, pSound);
    AudioMixer_queueSound(pSound);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_1);
    AudioMixer_freeWaveFileData(pSound);

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
    // Read second task
    AudioMixer_readWaveFileIntoMemory(TASK2_AUDIO, pSound);
    AudioMixer_queueSound(pSound);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_2);
    AudioMixer_freeWaveFileData(pSound);

    // Start second task
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
    // Read third task
    AudioMixer_readWaveFileIntoMemory(TASK3_AUDIO, pSound);
    AudioMixer_queueSound(pSound);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_3);
    AudioMixer_freeWaveFileData(pSound);

    /*// Start second task
    TaskGenerator3_init();
    
    // Wait for user to obtain the right score to exit the game
    while (true) {
        if (getSuccess() == SCORE) {
            break;
        }
    }
    // exit second task
    TaskGenerator3_cleanup();*/



    // cleanup audio, button and task generator
    closeSoundFiles();
    AudioMixer_cleanup(); 
    Button_cleanup();

    return 0;
}

