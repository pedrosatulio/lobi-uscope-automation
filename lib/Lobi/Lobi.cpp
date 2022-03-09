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

// Stepper motor sequence
uint8_t stepperVec[8] = {0x1, 0x3, 0x2, 0x6, 0x4, 0xC, 0x8, 0x9};      

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

   int Lobi::intensityRx()
   {
      if (Serial.available() > 0)
      {
         return Serial.parseInt();
      }
      else
      {
         return -1;
      }
   }
#endif

#ifdef MOTOR_HEAD
   void Lobi::xAxisMotorStep(uint8_t state)
   {
      digitalWrite(XIN1, stepperVec[xStepperPos] & 0x01);
      digitalWrite(XIN2, (stepperVec[xStepperPos] >> 1) & 0x01);
      digitalWrite(XIN3, (stepperVec[xStepperPos] >> 2) & 0x01);
      digitalWrite(XIN4, (stepperVec[xStepperPos] >> 3) & 0x01);

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
      digitalWrite(YIN1, stepperVec[yStepperPos] & 0x01);
      digitalWrite(YIN2, (stepperVec[yStepperPos] >> 1) & 0x01);
      digitalWrite(YIN3, (stepperVec[yStepperPos] >> 2) & 0x01);
      digitalWrite(YIN4, (stepperVec[yStepperPos] >> 3) & 0x01);

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