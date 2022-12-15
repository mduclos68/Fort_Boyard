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


int main()
{    
    // initialize audio and button
    AudioMixer_init();
    Button_init();
    openSoundFiles();

    /*********** First Challenge ***********/
    // read opening message
    wavedata_t *pSound;
    AudioMixer_readWaveFileIntoMemory(START_MESSAGE_AUDIO, pSound);
    AudioMixer_queueSound(pSound);
    Helper_sleepForMs(SPEECH_LENGTH_START);
    AudioMixer_freeWaveFileData(pSound);

    // Read first task
    wavedata_t *pSound1;
    AudioMixer_readWaveFileIntoMemory(TASK1_AUDIO, pSound1);
    AudioMixer_queueSound(pSound1);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_1);
    AudioMixer_freeWaveFileData(pSound1);

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
    wavedata_t *pSound2;
    AudioMixer_readWaveFileIntoMemory(TASK2_AUDIO, pSound2);
    AudioMixer_queueSound(pSound2);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_2);
    AudioMixer_freeWaveFileData(pSound2);

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
    wavedata_t *pSound3;
    AudioMixer_readWaveFileIntoMemory(TASK3_AUDIO, pSound3);
    AudioMixer_queueSound(pSound3);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_3);
    AudioMixer_freeWaveFileData(pSound3);

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

