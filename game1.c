#include "taskGenerator.h"


// define thread variables
static bool stopping = false;
static pthread_t gameId;

// Define pSounds
static wavedata_t redSound, blueSound, greenSound, greySound, yellowSound;
static wavedata_t buzzerSound, dingSound, winSound;

static int success = 0;


static void* Game1_Thread(void* _arg){
    
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
            
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");           
        }
    }

    AudioMixer_queueSound(&winSound);
    Helper_sleepForMs(1500);

    return NULL;
}


void Game1_init(void){
    // Launch beatGen thread:
    pthread_create(&gameId, NULL, Game1_Thread, NULL);
}


void Game1_cleanup(void){
    stopping = true;

    pthread_join(gameId, NULL); 
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

