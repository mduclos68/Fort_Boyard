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

    /*Bienvenue à Fort Boyard. Pour obtenir ton cadeau, tu devras compléter plusieur défis. 
    Ne t'inqiètes pas, je serais présente tout au long de ton aventure pour te soutenir. Comme tu peux voir,
    5 boutons sont à ta disponibilité. Ils te seront nécéssaire tout au long de tes épreuves.
    Ta première épreuve va comme suis: Des couleurs apparaitront sur l'écran une à une. Je nommerais les couleurs
    en même temps qu'elles seront affiché pour t'aider. À mesure qu'une nouvelle couleur apparait, tu dois peser
    sur le bouton de la bonne couleur. Si tu pèses sur le mauvais bouton, le jeu recommenceras du tout début. 
    Tu dois obtenir 10 bons résultats de suite pour passé à l'étape suivante. Je te préviens, plus tu avance 
    dans le jeu, plus la candence augmentera. Bonne chance!
    */
    Helper_sleepForMs(2000); 

    printf("Tu dois obtenir un score de %d pour réussir cette épreuve. Bonne chance!\n", SCORE);
    TaskGenerator1_init();

    /*// Wait for user to obtain the right score to exit the game
    while (true) {
        if (getSuccess() == SCORE) {
            break;
        }
    }
    printf("Félicitation, tu as réussi ton épreuve\n");*/

    // exit first task
    TaskGenerator1_cleanup();


    /*********** Second Challenge ***********/
    /* Félicitation, tu as réussi la première épreuve. La deuxième épreuve s'appelle le chaos des sons. 
    Tu comprendras assez vite pourquoi. La seule chose à savoir pour cette épreuve cest que tu dois peser
    sur le bouton correspondant à la couleur écrite sur l'écran. Les vois ne te seront pas utiles dans cette
    épreuve. Tu dois obtenir 10 bons résultats de suite pour passé à l'étape suivante. Bonne chance!
    */
    Helper_sleepForMs(2000);
    printf("Tu dois obtenir un score de %d pour réussir cette épreuve. Bonne chance!\n", SCORE);

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
    


    /*********** Third Challenge ***********/
    /* Wow, tes oreilles on survécu le chaos. Tu est maintenant rendu à ton épreuve finale.
    Celle-ci testeras ta mémoire. Seulement ceux avec une mémoir d'éléphant peuvent survivre 
    cette épreuve. Écoute bien parce que rien ne seras écrit sur l'écran pour t'aider. Lorsque le jeux
    commenceras, une suite de couleur te seras énoncé, tu devras peser sur les boutons dans le bon ordre
    pour réussir le jeu. Si tu échou, une nouvelle suite de couleur sera énoncé et tu recommenceras 
    le défi. Prépare tes oreilles, le défi commence maintenant. 
    */

    /*Helper_sleepForMs(2000);
    printf("Tu dois obtenir un score de %d pour réussir cette épreuve. Bonne chance!\n", SCORE);

    // Start second task
    TaskGenerator3_init();
    
    // Wait for user to obtain the right score to exit the game
    while (true) {
        if (getSuccess() == SCORE) {
            break;
        }
    }
    printf("Félicitation, tu as réussi ton épreuve\n");
    
    // exit second task
    TaskGenerator3_cleanup();*/



    // cleanup audio, button and task generator
    AudioMixer_cleanup(); 
    Button_cleanup();

    return 0;
}

