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

void SonarDemmarre() {
    if (etatSonar == PAUSE){
    etatSonar = TRIGGER;
    }
}


void SonarTicTac() {
    if (etatSonar == TRIGGER){
        etablitTrigger(char SonarActif, char 1);
        etatSonar = ATTENTE;
    }
    
     if (etatSonar == ATTENTE){
           etablitTrigger(char SonarActif, char 0);
           if (etablitEntree(char SonarActif)) {
               etatSonar = COMPTEUR;
           }
        }
    
     
    
     if (etatSonar == COMPTEUR ){
         if (etablitEntree(char SonarActif) == 1 ){
             Compteur++;
         }
         
         if (etablitEntree(char SonarActif) == 0 ){
             i2cExposeValeur(SonarActif, (Compteur * 29)/58);
             if (SonarActif < 3){
                SonarActif++;
             }
             if (SonarActif >= 3){
                SonarActif = 0;
             }
             etatSonar = PAUSE;
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
                break;
                
            case 1:
                return PORTAbits.RA1;
                break;
                
            case 2:
                return PORTAbits.RA2;
                break;
                
            case 3:
                return PORTAbits.RA3;
                break;
            
        }
    }
}