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

uint8_t stepperPos = 0x01;       // Stepper motor position

Lobi::Lobi()
{
}

void Lobi::motorStep(byte direction)
{
   #ifdef DEBUG_PRINTS
      if (stepperPos == 0x01 || stepperPos == 0x08)
      {
         Serial.println("");
         Serial.println("Starting new step...");
      }
   #endif

   digitalWrite(IN1, stepperPos & 0x01);
   digitalWrite(IN2, (stepperPos >> 1) & 0x01);
   digitalWrite(IN3, (stepperPos >> 2) & 0x01);
   digitalWrite(IN4, (stepperPos >> 3) & 0x01);

   if (direction)
   {
      if (stepperPos == 0x08)
      {
         stepperPos = 0x01;
      }
      else
      {
         stepperPos = stepperPos << 1;
      }
   }
   else
   {
      if (stepperPos == 0x01)
      {
         stepperPos = 0x08;
      }
      else
      {
         stepperPos = stepperPos >> 1;
      }
   }

   #ifdef DEBUG_PRINTS
      Serial.print("Switching stepper motor:\t");
      Serial.print(stepperPos & 0x01);
      Serial.print((stepperPos >> 1) & 0x01);
      Serial.print((stepperPos >> 2) & 0x01);
      Serial.println((stepperPos >> 3) & 0x01);
   
      if (direction)
      {
         if (stepperPos == 0x08)
         {
            Serial.println("Foward step completed.");
            Serial.println("");
         }
      }
      else
      {
         if (stepperPos == 0x01)
         {
            Serial.println("Backward step completed.");
            Serial.println("");
         }
      }
   #endif
}