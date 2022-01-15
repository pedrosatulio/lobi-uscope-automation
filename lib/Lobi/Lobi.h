/*
 ************** LOBI class **************

 This class contains LOBI device information and method definitions
 for automation of LOBI's Eclipse TE2000 Inverted Microscope

.
 Implemented methods:
    To print debugs in serial
        #define DEBUG_PRINTS
    To change loop sampling time
        #define SAMPLING_PERIOD "<MS_VALUE>"

 Developer:
    MSc. Tulio Pedrosa (tulio.pedrosa@ufpe.br)
    Hardware Engineer
 
 LOBI - Laboratório de Óptica Biomédica e Imagens
 Date: January 14th, 2022

*/

#ifndef LOBI_H
#define LOBI_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

/************* LOBI DEVICE INFORMATION ***************/
#define DEBUG_PRINTS                        // Show serial prints for debugging (comment to disable)
#define SAMPLING_PERIOD 250                 // Sampling period (ms)
#define POS             1                   // Stepper motor foward direction (clockwise)
#define NEG             0                   // Stepper motor backward direction (anticlockwise)

/******************* ARDUINO PINS *********************/
#define LED             3                   // D3 (Green LED test)
#define IN1             4                   // D4 (Step motor pin 1)
#define IN2             5                   // D5 (Step motor pin 2)
#define IN3             6                   // D6 (Step motor pin 3)
#define IN4             7                   // D7 (Step motor pin 4)
#define ZDIR            12                  // D12 (z-axis switch direction button pin)
#define ZIN             13                  // D13 (z-axis trigger button pin)

class Lobi
{
    public:
        Lobi();

        // Stepper motor methods
        byte    motorStep(byte direction);      // Produces a single step in motor

        // Communication methods
        char    keyboardRx();                   // Reads incoming keyboard control keys from serial
        void    stringRx(char *rxMessage);      // Reads incoming string from serial (automatic features)

    private:
};

#endif /* LOBI_H */