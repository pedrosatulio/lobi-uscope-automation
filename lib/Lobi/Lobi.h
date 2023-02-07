/*
 ************** LOBI class **************

 This class contains LOBI device information and method definitions
 for automation of LOBI's Eclipse TE2000 Inverted Microscope

.
 Implemented methods:
    To select module
        #define LED_HEAD to select microscope dark field control
        #define MOTOR_HEAD to select microscope motor control
    To print debugs in serial
        #define DEBUG_PRINTS
    To change superloop sampling time
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
//#define DEBUG_PRINTS                      // Show serial prints for debugging (comment to disable)
#define SAMPLING_PERIOD     250             // Sampling period (ms)
#define FORWARD             2               // z-axis forward direction
#define BACKWARD            1               // z-axis backward direction
#define STOP                0               // z-axis stop

/******************* ARDUINO PINS *********************/
// espaço para fim de curso x1
// espaço para fim de curso x2
// espaço para fim de curso y1
// espaço para fim de curso y2
// botão de enable dos controles do motor
// botão de home x/y
// botão de home z
#define ZIN1                3               // D3 (z-axis negative DC motor pin)
#define ZIN2                4               // D4 (z-axis positive DC motor pin)
#define XIN1                5               // D5 (Step motor pin 5)
#define XIN2                6               // D6 (Step motor pin 6)
#define XIN3                7               // D7 (Step motor pin 7)
#define XIN4                8               // D8 (Step motor pin 8)
#define YIN1                9               // D9 (Step motor pin 9)
#define YIN2                10              // D10 (Step motor pin 10)
#define YIN3                11              // D11 (Step motor pin 11)
#define YIN4                12              // D12 (Step motor pin 12)
#define ZNEG                A2              // A2 (z-axis zoom-out button pin) [Digital Mode]
#define ZPOS                A3              // A3 (z-axis zoom-in button pin) [Digital Mode]
#define XPOT                A6              // Stepper motor x-axis joystick control [Analog Mode]
#define YPOT                A7              // Stepper motor y-axis joystick control [Analog Mode]
// espaço para push button do joystick
// espaço para encoder do eixo x
// espaço para encoder do eixo y
// espaço para encoder do eixo z


class Lobi
{
    public:
        Lobi();

        // Stepper motor methods
        void    xAxisMotorStep(uint8_t state);      // Produces a single step in motor
        void    yAxisMotorStep(uint8_t state);      // Produces a single step in motor

        // DC motor methods
        void    zAxisMotorCtrl(uint8_t state);      // Produces a single step in motor

        private:
};

#endif /* LOBI_H */