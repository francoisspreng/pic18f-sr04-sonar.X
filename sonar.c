/*
 * File:   sonar.c
 * Author: François
 *
 * Created on 16. juin 2016, 19:24
 */

#include <xc.h>
#include "sonar.h"
#include "file.h"
#include "test.h"
#include "i2c.h"

typedef enum {
    PAUSE,
    TRIGGER,
    ATTENTE,
    COMPTEUR,
}EtatSonar;

EtatSonar etatSonar = PAUSE;
int SonarActif = 0;
int Compteur = 0;
int Distance;

void sonarDemmarre() {
    if (etatSonar == PAUSE){
    etatSonar = TRIGGER;
    }
}


void SonarTicTac() {
    if (etatSonar == TRIGGER){
        etablitTrigger( SonarActif, 1);
        etatSonar = ATTENTE;
    }
    
    if (etatSonar == ATTENTE){
        etablitTrigger(SonarActif, 0);
        if (etablitEntree(SonarActif)) {
            etatSonar = COMPTEUR;
        }
    }
    
     
    
    if (etatSonar == COMPTEUR){
        if (etablitEntree(SonarActif) == 1 ){
            Compteur++;
        }
        
         
         
        if (etablitEntree(SonarActif) == 0 ){
            Distance = (Compteur * 29)/58;
         
            if (Distance > 255) {
                Distance = 255;
            }
            
            i2cExposeValeur(SonarActif, Distance);
            
            if (SonarActif < 3){
                SonarActif++;
            }
            
            if (SonarActif >= 3){
                SonarActif = 0;
            }
            
            etatSonar = PAUSE;
        }
    }
}    
    
    
    
void etablitTrigger(char SonarActif, char valeurTrigger) {
    switch(SonarActif) {
        case 0:
            PORTBbits.RB0 = valeurTrigger;
            break;
                
        case 1:
            PORTBbits.RB1 = valeurTrigger;
            break;
                
        case 2:
            PORTBbits.RB2 = valeurTrigger;
            break;
                
        case 3:
            PORTBbits.RB3 = valeurTrigger;
            break;
            
    }
}
    
char etablitEntree(char SonarActif) {
    switch(SonarActif) {
        case 0:
            return PORTAbits.RA0;
                
        case 1:
            return PORTAbits.RA1;
                
        case 2:
            return PORTAbits.RA2;
                
        
    }
    return PORTAbits.RA3;
}
    
        
            
    
            
