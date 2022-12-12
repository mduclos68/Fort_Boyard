#include "taskGenerator.h"

// define thread variables
static bool stopping = false;
static bool stoppingSound = false;
static pthread_t task1Id, task2Id, soundId;

// Define pSounds
static wavedata_t redSound, blueSound, greenSound, greySound, yellowSound;
static wavedata_t buzzerSound, dingSound, winSound;

static int success = 0;

#define INIT_TIME_INTERVAL 1500 // 5 seconds
static long long timeInterval = INIT_TIME_INTERVAL; 


int getSuccess(void){
    return success;
}

/*********** First task ***********/

static void* TaskGenerator1_Thread(void* _arg){

    long long t, t_diff;
    while(!stopping){

        // choose a number for 0-4
        int colour = rand() % 5;

        // Colour selection
        if(colour == RED){
            printf("Rouge\n");
            AudioMixer_queueSound(&redSound);
        }
        else if(colour == BLUE){
            printf("Bleu\n");
            AudioMixer_queueSound(&blueSound);
        }
        else if(colour == GREY){
            printf("Gris\n");
            AudioMixer_queueSound(&greySound);
        }
        else if(colour == GREEN){
            printf("Vert\n");
            AudioMixer_queueSound(&greenSound);
        }
        else{
            printf("Jaune\n");
            AudioMixer_queueSound(&yellowSound);
        }


        Helper_sleepForMs(250);

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
            AudioMixer_queueSound(&dingSound);
            Helper_sleepForMs(timeInterval);
            // reduce time interval
            timeInterval = 0.87 * timeInterval;
            
        }
        else{
            if ((!onTime)){
                printf("TROP LENT!!!\nTu t'es rendu à %d, recommence!\n", success);
            }
            else{
                printf("MAUVAIS BOUTTON!!!\nTu t'es rendu à %d, recommence!\n", success);
            }
            
            success = 0;
            timeInterval = INIT_TIME_INTERVAL;
            AudioMixer_queueSound(&buzzerSound);

            Helper_sleepForMs(500);
            printf("Pèse sur un bouton pour recommencer.\n");
            while(true){
                if (isButtonPressed()){
                    break;
                }
            }            
            Helper_sleepForMs(2000);
        }
    }

    AudioMixer_queueSound(&winSound);

    return NULL;
}


void TaskGenerator1_init(void){

    // Open all sound files
    AudioMixer_readWaveFileIntoMemory(RED_AUDIO, &redSound);
    AudioMixer_readWaveFileIntoMemory(GREEN_AUDIO, &greenSound);
    AudioMixer_readWaveFileIntoMemory(GREY_AUDIO, &greySound);
    AudioMixer_readWaveFileIntoMemory(BLUE_AUDIO, &blueSound);
    AudioMixer_readWaveFileIntoMemory(YELLOW_AUDIO, &yellowSound);
    AudioMixer_readWaveFileIntoMemory(BUZZER_AUDIO, &buzzerSound);
    AudioMixer_readWaveFileIntoMemory(WIN_AUDIO, &winSound);
    AudioMixer_readWaveFileIntoMemory(DING_AUDIO, &dingSound);


    
    // Launch beatGen thread:
    pthread_create(&task1Id, NULL, TaskGenerator1_Thread, NULL);
}


void TaskGenerator1_cleanup(void){
    stopping = true;

    pthread_join(task1Id, NULL); 
}


/*********** Second task ***********/
static void* SoundGenerator_Thread(void* _arg){
    while(!stoppingSound){
        // choose a number from 0-4
        int sound = rand() % 5; 

        // sound selection
        if(sound == RED){
            AudioMixer_queueSound(&redSound);
        }
        else if(sound == BLUE){
            AudioMixer_queueSound(&blueSound);
        }
        else if(sound == GREY){
            AudioMixer_queueSound(&greySound);
        }
        else if(sound == GREEN){
            AudioMixer_queueSound(&greenSound);
        }
        else{
            AudioMixer_queueSound(&yellowSound);
        }

        Helper_sleepForMs(1500);
    }

    return NULL;
}


static void SoundGenerator_init(void){
    stoppingSound = false;
    
    // Launch thread:
    pthread_create(&soundId, NULL, SoundGenerator_Thread, NULL);
}


static void SoundGenerator_cleanup(void){
    stoppingSound = true;

    pthread_join(soundId, NULL);  
}


static void* TaskGenerator2_Thread(void* _arg){

    while(!stopping){

        SoundGenerator_init();
        
        // choose a number from 0-4
        int colour = rand() % 5;

        // Colour Selection
        if(colour == RED){
            printf("Rouge\n");
        }
        else if(colour == BLUE){
            printf("Bleu\n");
        }
        else if(colour == GREY){
            printf("Gris\n");
        }
        else if(colour == GREEN){
            printf("Vert\n");
        }
        else{
            printf("Jaune\n");
        }

        // Wait for button press
        while(true){
            if (isButtonPressed()){
                break;
            }
        } 

        bool goodButton = rightButton(colour);
        
        if(goodButton){
            // add to success count
            success++;
            AudioMixer_queueSound(&dingSound);
            Helper_sleepForMs(500);
            printf("---\n");
        }
        else{
            printf("MAUVAIS BOUTTON!!!\nTu t'es rendu à %d, recommence!\n", success);
            
            SoundGenerator_cleanup();

            AudioMixer_queueSound(&buzzerSound);
            success = 0;

            Helper_sleepForMs(500);
            printf("Pèse sur un bouton pour recommencer.\n");
            while(true){
                if (isButtonPressed()){
                    break;
                }
            }            
            Helper_sleepForMs(1000);
            SoundGenerator_init();
        }
    }
    
    SoundGenerator_cleanup();
    AudioMixer_queueSound(&winSound);

    return NULL;
}


void TaskGenerator2_init(void){
    stopping = false;
    success = 0;
    
    // Launch thread:
    pthread_create(&task2Id, NULL, TaskGenerator2_Thread, NULL);
}


void TaskGenerator2_cleanup(void){
    stopping = true;

    pthread_join(task2Id, NULL);
    pthread_join(soundId, NULL);

    // Free all sound files
    AudioMixer_freeWaveFileData(&redSound);
    AudioMixer_freeWaveFileData(&greenSound);
	AudioMixer_freeWaveFileData(&greySound); 
    AudioMixer_freeWaveFileData(&yellowSound);
    AudioMixer_freeWaveFileData(&blueSound);   
}

