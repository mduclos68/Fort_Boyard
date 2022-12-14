#include "taskGenerator.h"

// define thread variables
static bool stopping = false;
//static bool stoppingSound = false;
static pthread_t task1Id, task2Id, soundId;

// Define pSounds
static wavedata_t redSound, blueSound, greenSound, greySound, yellowSound;
static wavedata_t buzzerSound, dingSound, winSound;

static int success = 0;

#define INIT_TIME_INTERVAL 1500 // 5 seconds
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


/*********** First task ***********/

static void* TaskGenerator1_Thread(void* _arg){

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
            printf("---\n");
            AudioMixer_queueSound(&dingSound);
            
            // Wait for time interval
            Helper_sleepForMs(timeInterval);
            
            // reduce time interval
            timeInterval = 0.87 * timeInterval;
        }
        else{
            Helper_runCommand("clear");

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

    long long t, t_diff;
    while(!stopping){

        //SoundGenerator_init();
        
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
        while(!isButtonPressed() && (t_diff < INIT_TIME_INTERVAL)){
            t_diff = getTimeInMs() - t;  
        }

        bool goodButton = rightButton(colour);
        bool onTime = (t_diff < INIT_TIME_INTERVAL); 

        if(goodButton && onTime){
             // add to success count
            success++;
            AudioMixer_queueSound(&dingSound);
            Helper_sleepForMs(500);
            printf("---\n");
        }
        else{
            if ((!onTime)){
                printf("TROP LENT!!!\nTu t'es rendu à %d, recommence!\n", success);
            }
            else{
                printf("MAUVAIS BOUTTON!!!\nTu t'es rendu à %d, recommence!\n", success);
            }
            
            //SoundGenerator_cleanup();

            AudioMixer_queueSound(&buzzerSound);
            success = 0;

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
    
    //SoundGenerator_cleanup();
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

