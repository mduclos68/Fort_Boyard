#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#include "button.h"

char CurrentLanguage = "ENGL"

int main(){


}

void languageSelection(){
    printf("Français (Bleu) || English (Red)\n");

    while(true){
        if (rightButton(RED_Select)){
            CurrentLanguage = "ENGL";
            break;
        }
        else if (rightButton(BLUE_Select)) {
            CurrentLanguage = "FREN";
            break;
        }
    } 
}


void difficultySelection(){
    while(true){
        if (rightButton(RED_Select)){
            // easy
            break;
        }
        else if (rightButton(BLUE_Select)) {
            // medium
            break;
        }
        else if (rightButton(BLUE_Select)) {
            // hard
            break;
        }
        else if (rightButton(BLUE_Select)) {
            // hell
            break;
        }
    }
}


void modeSelection(){
    printf("\n");

    while(true){
        if (rightButton(RED_Select)){
            // language selection
            break;
        }
        else if (rightButton(BLUE_Select)) {
            // game selection
            break;
        }
        else if (rightButton(BLUE_Select)) {
            // volume setting
            break;
        }
    }     
}

void inGameSelection(){
    printf("\n");

    while(true){
        if (rightButton(BLUE_Select)) {
            // game difficulty
            break;
        }
        else if (rightButton(BLUE_Select)) {
            // restart
            break;
        }
        else if (rightButton(BLUE_Select)) {
            // exit game
            break;
        }
    }
}