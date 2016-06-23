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

typedef enum {
    PAUSE,
    TRIGGER,
    ATTENTE,
    COMPTEUR,
}EtatSonar;

EtatSonar etatSonar = PAUSE;
int SonarActif = 0;

void SonarDemmarre() {
  
    EtatSonar = TRIGGER;
    return;
}


void SonarTicTac() {
  
    EtatSonar = TRIGGER;
    return;
}