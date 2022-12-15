#include "taskGenerator.h"


// define thread variables
static bool stopping = false;
static pthread_t task1Id, task2Id, task3Id;

// Define pSounds
static wavedata_t redSound, blueSound, greenSound, greySound, yellowSound;
static wavedata_t buzzerSound, dingSound, winSound;
static wavedata_t pSound, pSound1, pSound2, pSound3;

static int success = 0;

#define INIT_TIME_INTERVAL 1500 // 1.5 seconds
static long long timeInterval = INIT_TIME_INTERVAL; 

#define RESTART_TEXT "Pèse sur un bouton pour recommencer.\n"

int getSuccess(void){
    return success;
}


/*********** Helper Functions ***********/
static char* ChooseTextColour(int colour){
    // Colour Selection
    if(colour == RED_Select){
        return TEXT_COLOUR_RED;
    }
    else if(colour == BLUE_Select){
        return TEXT_COLOUR_BLUE;
    }
    else if(colour == GREY_Select){
        return TEXT_COLOUR_GREY;
    }
    else if(colour == GREEN_Select){
        return TEXT_COLOUR_GREEN;
    }
    else{
        return TEXT_COLOUR_YELLOW;
    }
}

static char* ChooseColour(int colour){
    // Colour Selection
    if(colour == RED_Select){
        return RED;
    }
    else if(colour == BLUE_Select){
        return BLUE;
    }
    else if(colour == GREY_Select){
        return GREY;
    }
    else if(colour == GREEN_Select){
        return GREEN;
    }
    else{
        return YELLOW;
    }
}

static void PlayColour(int colour){
    if(colour == RED_Select){
        AudioMixer_queueSound(&redSound);
    }
    else if(colour == BLUE_Select){
        AudioMixer_queueSound(&blueSound);
    }
    else if(colour == GREY_Select){
        AudioMixer_queueSound(&greySound);
    }
    else if(colour == GREEN_Select){
        AudioMixer_queueSound(&greenSound);
    }
    else{
        AudioMixer_queueSound(&yellowSound);
    }
}

void openSoundFiles(void){
    // Open all sound files
    AudioMixer_readWaveFileIntoMemory(RED_AUDIO, &redSound);
    AudioMixer_readWaveFileIntoMemory(GREEN_AUDIO, &greenSound);
    AudioMixer_readWaveFileIntoMemory(GREY_AUDIO, &greySound);
    AudioMixer_readWaveFileIntoMemory(BLUE_AUDIO, &blueSound);
    AudioMixer_readWaveFileIntoMemory(YELLOW_AUDIO, &yellowSound);
    AudioMixer_readWaveFileIntoMemory(BUZZER_AUDIO, &buzzerSound);
    AudioMixer_readWaveFileIntoMemory(WIN_AUDIO, &winSound);
    AudioMixer_readWaveFileIntoMemory(DING_AUDIO, &dingSound);
    AudioMixer_readWaveFileIntoMemory(START_MESSAGE_AUDIO, &pSound);
    AudioMixer_readWaveFileIntoMemory(TASK1_AUDIO, &pSound1);
    AudioMixer_readWaveFileIntoMemory(TASK2_AUDIO, &pSound2);
    AudioMixer_readWaveFileIntoMemory(TASK3_AUDIO, &pSound3);
}

void closeSoundFiles(void){
    // Free all sound files
    AudioMixer_freeWaveFileData(&redSound);
    AudioMixer_freeWaveFileData(&greenSound);
	AudioMixer_freeWaveFileData(&greySound); 
    AudioMixer_freeWaveFileData(&yellowSound);
    AudioMixer_freeWaveFileData(&blueSound); 
    AudioMixer_freeWaveFileData(&buzzerSound);
    AudioMixer_freeWaveFileData(&winSound);
    AudioMixer_freeWaveFileData(&dingSound);
    AudioMixer_freeWaveFileData(&pSound);
    AudioMixer_freeWaveFileData(&pSound1);
    AudioMixer_freeWaveFileData(&pSound2);
    AudioMixer_freeWaveFileData(&pSound3);
}


/*********** First task ***********/

static void* TaskGenerator1_Thread(void* _arg){
    // read opening message
    AudioMixer_queueSound(&pSound);
    Helper_sleepForMs(SPEECH_LENGTH_START);

    // Read first task
    AudioMixer_queueSound(&pSound1);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_1);
    
    long long t, t_diff;
    while(!stopping){

        // choose a number for 0-4
        int colour = rand() % 5;      
        char* COLOUR = ChooseColour(colour);
        char* TEXT_COLOUR = ChooseTextColour(colour);
   
        // Print the colour name in its colour and play the colour sound
        printf("%s%s\033[0m\n", TEXT_COLOUR, COLOUR);
        PlayColour(colour);

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
            AudioMixer_queueSound(&dingSound);
            printf("---\n");
            
            // Wait for time interval
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
            printf("%s", RESTART_TEXT);
            while(true){
                if (isButtonPressed()){
                    break;
                }
            }            
        }
    }

    AudioMixer_queueSound(&winSound);
    Helper_sleepForMs(1500);

    return NULL;
}


void TaskGenerator1_init(void){
    // Launch beatGen thread:
    pthread_create(&task1Id, NULL, TaskGenerator1_Thread, NULL);
}


void TaskGenerator1_cleanup(void){
    stopping = true;

    pthread_join(task1Id, NULL); 
}


/*********** Second task ***********/
/*
static void* SoundGenerator_Thread(void* _arg){
    while(!stoppingSound){
        // choose a number from 0-4
        int colour = rand() % 5; 

        // Play the sound
        PlayColour(colour);

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
*/

static void* TaskGenerator2_Thread(void* _arg){
    // Read second task
    AudioMixer_queueSound(&pSound2);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_2);

    timeInterval = INIT_TIME_INTERVAL;
    long long t, t_diff;

    while(!stopping){
        
        // choose a number from 0-4, choose colours
        int colour = rand() % 5;
        int text_colour = rand() % 5;  
        int sound_colour = rand() % 5;      
        char* COLOUR = ChooseColour(colour);
        char* TEXT_COLOUR = ChooseTextColour(text_colour);
    
        printf("%s%s\033[0m\n", TEXT_COLOUR, COLOUR);
        PlayColour(sound_colour);

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
            AudioMixer_queueSound(&dingSound);
            Helper_sleepForMs(500);
            printf("---\n");

            // reduce time interval
            timeInterval = 0.92 * timeInterval;
        }
        else{
            if ((!onTime)){
                printf("TROP LENT!!!\nTu t'es rendu à %d, recommence!\n", success);
            }
            else{
                printf("MAUVAIS BOUTTON!!!\nTu t'es rendu à %d, recommence!\n", success);
            }

            AudioMixer_queueSound(&buzzerSound);
            success = 0;
            timeInterval = INIT_TIME_INTERVAL;

            Helper_sleepForMs(500);
            printf("%s", RESTART_TEXT);
            while(true){
                if (isButtonPressed()){
                    break;
                }
            }            
            Helper_sleepForMs(1000);
        }
    }
    
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
}


/*********** Third Task ***********/
static void GenerateArray(int *arr){
    for (int i=0; i<10; i++){
        arr[i] = rand() % 4;
    }
}

static void* TaskGenerator3_Thread(void* _arg){
    // Read third task
    AudioMixer_queueSound(&pSound3);
    Helper_sleepForMs(SPEECH_LENGHT_TASK_3);

    int arr[10];
    memset(arr, 0, sizeof arr);

    while(!stopping){
        // choose colours
        GenerateArray(arr);

        // Say all 10 colours
        for (int i=0; i<10; i++){
            PlayColour(arr[i]);
            Helper_sleepForMs(1000);
        }
        
        int i = 0;
        bool goodButton = true;
        while(goodButton && success !=10){
            // Wait for button press
            while(!isButtonPressed()){
            }

            goodButton = rightButton(arr[i]);

            if(goodButton){
                // add to success count
                success++;
                i++;
                AudioMixer_queueSound(&dingSound);
                Helper_sleepForMs(500);
                printf("---\n");

            }
            else{
                printf("MAUVAIS BOUTTON!!!\nTu t'es rendu à %d, recommence!\n", success);

                AudioMixer_queueSound(&buzzerSound);
                success = 0;
                i=0;

                Helper_sleepForMs(500);
                printf("%s", RESTART_TEXT);
                while(true){
                    if (isButtonPressed()){
                        break;
                    }
                }            
                Helper_sleepForMs(1000);
            }
        }

        
    }
    
    AudioMixer_queueSound(&winSound);

    return NULL;
}


void TaskGenerator3_init(void){
    stopping = false;
    success = 0;
    
    // Launch thread:
    pthread_create(&task3Id, NULL, TaskGenerator3_Thread, NULL);
}


void TaskGenerator3_cleanup(void){
    stopping = true;

    pthread_join(task3Id, NULL);
}

