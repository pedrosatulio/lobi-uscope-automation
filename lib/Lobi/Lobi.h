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
#define MOTOR_HEAD                            // Choose LED_HEAD or MOTOR_HEAD
//#define DEBUG_PRINTS                        // Show serial prints for debugging (comment to disable)
#define SAMPLING_PERIOD     250             // Sampling period (ms)
#define LCD_I2C_ADDR        0xFF            // LCD module I2C device address
#ifdef LED_HEAD
    #define WHITE_LED_THRS  110             // Maximum PWM value for white LEDs (20mA)
    #define IR_LED_THRS     240             // Maximum PWM value for infrared LEDs (100mA)
    #define I2C_ADDR        0x04            // LED head module I2C address
#endif
#ifdef MOTOR_HEAD
    #define FORWARD         2               // z-axis forward direction
    #define BACKWARD        1               // z-axis backward direction
    #define STOP            0               // z-axis stop
    #define I2C_ADDR        0x05            // Motor head module I2C address
#endif

/******************* ARDUINO PINS *********************/
#define SDA                 A4              // I2C SDA pin (interboard comm)
#define SCL                 A5              // I2C SCL pin (interboard comm)
#ifdef LED_HEAD
    #define WHITE_LED_PIN   5               // D5 (White LED PWM output pin - 980 Hz)
    #define IR_LED_PIN      6               // D6 (Infrared LED PWM output pin - 980 Hz)
    // espaço 1 para encoder seletor
    // espaço 2 para encoder seletor
    // espaço 3 para encoder seletor
    // espaço para encoder fim de curso x1
    // espaço para encoder fim de curso x2
    // espaço para encoder fim de curso y1
    // espaço para encoder fim de curso y2
    // espaço para potenciômetro de velocidade dos motores de passo
    // botão de enable dos controles do motor
    // botão de home x/y
    // botão de home z
#endif
#ifdef MOTOR_HEAD
    #define ZIN1            3               // D3 (z-axis negative DC motor pin)
    #define ZIN2            4               // D4 (z-axis positive DC motor pin)
    #define XIN1            5               // D5 (Step motor pin 5)
    #define XIN2            6               // D6 (Step motor pin 6)
    #define XIN3            7               // D7 (Step motor pin 7)
    #define XIN4            8               // D8 (Step motor pin 8)
    #define YIN1            9               // D9 (Step motor pin 9)
    #define YIN2            10              // D10 (Step motor pin 10)
    #define YIN3            11              // D11 (Step motor pin 11)
    #define YIN4            12              // D12 (Step motor pin 12)
    #define ZNEG            A2              // A2 (z-axis zoom-out button pin) [Digital Mode]
    #define ZPOS            A3              // A3 (z-axis zoom-in button pin) [Digital Mode]
    #define XPOT            A6              // Stepper motor x-axis joystick control [Analog Mode]
    #define YPOT            A7              // Stepper motor y-axis joystick control [Analog Mode]
    // espaço para push button do joystick
    // espaço para encoder do eixo x
    // espaço para encoder do eixo y
    // espaço para encoder do eixo z
#endif


class Lobi
{
    public:
        Lobi();

        #ifdef LED_HEAD
            // USB communication methods
            char    keyboardRx();                       // Reads incoming keyboard control keys from serial
            void    stringRx(char *rxMessage);          // Reads incoming string from serial (automatic features)
        #endif
        #ifdef MOTOR_HEAD
            // Stepper motor methods
            void    xAxisMotorStep(uint8_t state);      // Produces a single step in motor
            void    yAxisMotorStep(uint8_t state);      // Produces a single step in motor

            // DC motor methods
            void    zAxisMotorCtrl(uint8_t state);      // Produces a single step in motor
        #endif

        // I2C communication methods
        void I2CInitialization();                       // Initializes I2C bus
        void I2CWrite(String txMessage);                // Sends data string secondary module
        String I2CRead(char *rxMessage, int curr_addr); // Receives char sent by secondary module

        private:
};

#endif /* LOBI_H */