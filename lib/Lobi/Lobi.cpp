/* 
  This class contains LOBI device methods

  Public methods:
    
  
  Private methods:


     Developer:
        MSc. Tulio Pedrosa (tulio.pedrosa@ufpe.br)
        Hardware Engineer
     
     LOBI - Laboratório de Óptica Biomédica e Imagens
     Date: January 14th, 2022

 
*/

#include "Lobi.h"

// x-axis and y-axis stepper sequence
uint8_t xStepperVec[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};      
uint8_t yStepperVec[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};

uint8_t xStepperPos = 0;      // x-axis Stepper motor stepper vector position
uint8_t yStepperPos = 0;      // y-axis Stepper motor stepper vector position

Lobi::Lobi()
{
}

#ifdef LED_HEAD
   char Lobi::keyboardRx()
   {
      if (Serial.available() > 0)
      {
         return Serial.read();
      }
      else
      {
         return '\0';
      }
   }

   void Lobi::stringRx(char *rxMessage)
   {
      //
   }
#endif

#ifdef MOTOR_HEAD
   void Lobi::xAxisMotorStep(uint8_t state)
   {
      digitalWrite(XIN1, xStepperVec[xStepperPos] & 0x01);
      digitalWrite(XIN2, (xStepperVec[xStepperPos] >> 1) & 0x01);
      digitalWrite(XIN3, (xStepperVec[xStepperPos] >> 2) & 0x01);
      digitalWrite(XIN4, (xStepperVec[xStepperPos] >> 3) & 0x01);

      if (state == 2)
      {
         if (xStepperPos == 7)
         {
            xStepperPos = 0;
         }
         else
         {
            xStepperPos++;
         }
      }
      
      if (state == 1)
      {
         if (xStepperPos == 0)
         {
            xStepperPos = 7;
         }
         else
         {
            xStepperPos--;
         }
      }
   }

   void Lobi::yAxisMotorStep(uint8_t state)
   {
      digitalWrite(YIN1, yStepperVec[yStepperPos] & 0x01);
      digitalWrite(YIN2, (yStepperVec[yStepperPos] >> 1) & 0x01);
      digitalWrite(YIN3, (yStepperVec[yStepperPos] >> 2) & 0x01);
      digitalWrite(YIN4, (yStepperVec[yStepperPos] >> 3) & 0x01);

      if (state == 2)
      {
         if (yStepperPos == 7)
         {
            yStepperPos = 0;
         }
         else
         {
            yStepperPos++;
         }
      }
      
      if (state == 1)
      {
         if (yStepperPos == 0)
         {
            yStepperPos = 7;
         }
         else
         {
            yStepperPos--;
         }
      }
   }

   void Lobi::zAxisMotorCtrl(uint8_t state)
   {
      if (state == 2)
      {
         digitalWrite(ZIN1, LOW);
         digitalWrite(ZIN2, HIGH);
      }
      else if (state == 1)
      {
         digitalWrite(ZIN1, HIGH);
         digitalWrite(ZIN2, LOW);
      }
      else
      {
         digitalWrite(ZIN1, LOW);
         digitalWrite(ZIN2, LOW);
      }
   }
#endif