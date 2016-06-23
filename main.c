#include <xc.h>
#include <stdio.h>

/**
 * Bits de configuration:
 */
#pragma config FOSC = INTIO67  // Osc. interne, A6 et A7 comme IO.
#pragma config IESO = OFF      // Pas d'osc. au démarrage.
#pragma config FCMEN = OFF     // Pas de monitorage de l'oscillateur.

// Nécessaires pour ICSP / ICD:
#pragma config MCLRE = EXTMCLR // RE3 est actif comme master reset.
#pragma config WDTEN = OFF     // Watchdog inactif.
#pragma config LVP = OFF       / / Single Supply Enable bits off.



void low_priority interrupt interruptionsBassePriorite() {
    
    if (PIR1bits.TMR1IF) {
        TMR1 = 65536 - 464;
        SonarDemmarre();
        PIR1bits.TMR1IF = 0;
    }
    if (PIR2bits.TMR3IF) {
        TMR3 = 65536 - 16000;
        SonarTicTac();
        PIR2bits.TMR3IF = 0;
    }
    if (XXXXIF) {
        // xxxx
        XXXXIF = 0;
    }
    if (XXXXIF) {
        // xxxx
        XXXXIF = 0;
    }
}

/**
 * Initialise la sortie 1 de la EUSART.
 * Si le UP est à 1MHz, le Virtual Terminal dans Proteus
 * doit être configuré comme suit:
 * - 1200 bauds.
 * - Transmission 8 bits.
 * - Bit de stop activé.
 */
void initialiseHardware() {
    // Pour une fréquence de 64MHz
   
    OSCCONbits.IRCF = 7;   // Oscillateur interne à 16MHz
    OSCTUNEbits.PLLEN = 1; // fréquence de sortie multipliée par 4
   
    
    // Configure RA0 à RA3 comme entrées digitales
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 1;
    TRISAbits.RA2 = 1;
    TRISAbits.RA3 = 1;
     // Configure RB0 à RB3 comme sortie digitales
    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0;
    
   
    // Active les tempos TMR1 et TMR3:
    
    T1CONbits.TMR1CS = 0;   // source Fosc/4
    T1CONbits.T1CKPS = 0;   // pas de division de fréquence
    T1CONbits.T1RD16 = 1;   // accès simultané à TMR1H et TMR1L activé
    T1CONbits.TMR1ON = 1;   // temporisateur actif
    
    T3CONbits.TMR3CS = 0;   // source Fosc/4
    T3CONbits.T3CKPS = 0;   // pas de division de fréquence
    T3CONbits.T3RD16 = 1;   // accès simultané à TMR1H et TMR1L activé
    T3CONbits.TMR3ON = 1;   // temporisateur actif
    
    // Active les interruptions:
    PIE1bits.TMR1IE = 1;   // interruption active   
    IPR1bits.TMR1IP = 0;   // priorité basse
    PIR1bits.TMR1IF = 0;   // drapeau bas
    
    PIE2bits.TMR3IE = 1;   // interruption active   
    IPR3bits.TMR3IP = 0;   // priorité basse
    PIR2bits.TMR3IF = 0;   // drapeau bas
}

/**
 * Point d'entrée du programme.
 */
void main(void) {
    initialiseHardware();
    while (1);
}