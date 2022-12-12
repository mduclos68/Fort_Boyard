#include "taskGenerator.h"

// define thread variables
static bool stopping = false;
static pthread_t taskThreadId;

// Define pSounds
static wavedata_t redSound, blueSound, greenSound, greySound, yellowSound;

static int success = 0;

#define INIT_TIME_INTERVAL 1500; // 5 seconds
static long long timeInterval = INIT_TIME_INTERVAL; 


static void* TaskGenerator_Thread(void* _arg){

    long long t, t_diff;
    while(!stopping){

        // choose a number for 0-4
        int colour = rand() % 5;

        // Red
        if(colour == RED){
            printf("Rouge\n");
            AudioMixer_queueSound(&redSound);
        }

        // Blue
        else if(colour == BLUE){
            printf("Bleu\n");
            AudioMixer_queueSound(&blueSound);

        }

        // Grey
        else if(colour == GREY){
            printf("Gris\n");
            AudioMixer_queueSound(&greySound);
        }

        // Green
        else if(colour == GREEN){
            printf("Vert\n");
            AudioMixer_queueSound(&greenSound);
        }

        // Yellow
        else{
            printf("Jaune\n");
            AudioMixer_queueSound(&yellowSound);
        }

        // Get time
        t = getTimeInMs();
        t_diff = 0;

        // Wait for button press of run out of time
        while(!isButtonPressed() && (t_diff < timeInterval)){
            t_diff = getTimeInMs() - t;  
        }

        bool goodButton = rightButton(colour);
        bool onTime = (t_diff < timeInterval); 
        
        if(goodButton && onTime){
            // add to success count
            success++;
            printf("---\n");
            Helper_sleepForMs(timeInterval);
            // reduce time interval
            timeInterval = 0.90 * timeInterval;
            
        }
        else{
            if ((!goodButton)){
                printf("MAUVAIS BOUTTON!!!\nTu t'es rendu à %d, recommence!\n", success);
            }
            else{
                printf("TROP LENT!!!\nTu t'es rendu à %d, recommence!\n", success);
            }
            
            success = 0;
            timeInterval = INIT_TIME_INTERVAL;
            
            Helper_sleepForMs(2000);
        }
    }

    return NULL;
}




void TaskGenerator_init(void){

    // Open all sound files
    AudioMixer_readWaveFileIntoMemory(RED_AUDIO, &redSound);
    AudioMixer_readWaveFileIntoMemory(GREEN_AUDIO, &greenSound);
    AudioMixer_readWaveFileIntoMemory(GREY_AUDIO, &greySound);
    AudioMixer_readWaveFileIntoMemory(BLUE_AUDIO, &blueSound);
    AudioMixer_readWaveFileIntoMemory(YELLOW_AUDIO, &yellowSound);
    
    // Launch beatGen thread:
    pthread_create(&taskThreadId, NULL, TaskGenerator_Thread, NULL);
}


void TaskGenerator_cleanup(void){
    stopping = true;

    pthread_join(taskThreadId, NULL);

    // Free all sound files
    AudioMixer_freeWaveFileData(&redSound);
    AudioMixer_freeWaveFileData(&greenSound);
	AudioMixer_freeWaveFileData(&greySound); 
    AudioMixer_freeWaveFileData(&yellowSound);
    AudioMixer_freeWaveFileData(&blueSound);   
}


int getSuccess(void){
    return success;
}
