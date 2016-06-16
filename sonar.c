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
unsigned char sonarActif = 0

void demmarre(sonarActif) {
    sonarActif = n;
    EtatSonar = TRIGGER;
    return;
}
