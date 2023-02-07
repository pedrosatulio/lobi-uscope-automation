// Automation of LOBI's Eclipse TE2000 Inverted Microscope


#include "Lobi.h"
Lobi LobiDevice;                          // Lobi class


// Global variables and flags
uint32_t  samplingTimeOut;                // Timing variable for sampling period


// Main functions
void updateStatus();                      // Update and print loop state


// RTOS Tasks
void xAxisStep(void *parameter);        // x-axis control thread
void yAxisStep(void *parameter);        // y-axis control thread
void zAxisCtrl(void *parameter);        // Focus (z-axis) control thread


void setup()
{
  // Initializing x-axis stepper motor pins
  pinMode(XIN1, OUTPUT);
  pinMode(XIN2, OUTPUT);
  pinMode(XIN3, OUTPUT);
  pinMode(XIN4, OUTPUT);

  // Initializing y-axis stepper motor pins
  pinMode(YIN1, OUTPUT);
  pinMode(YIN2, OUTPUT);
  pinMode(YIN3, OUTPUT);
  pinMode(YIN4, OUTPUT);

  // Initializing z-axis DC motor pins
  pinMode(ZIN1, OUTPUT);
  pinMode(ZIN2, OUTPUT);

  // Initializing joystick pins and zoom pins
  pinMode(XPOT, INPUT);
  pinMode(YPOT, INPUT);
  pinMode(ZNEG, INPUT);
  pinMode(ZPOS, INPUT);

  // Initializing flags and variables
  samplingTimeOut = 0;

  // Initializing RTOS tasks
  xTaskCreate(
    xAxisStep,                          // Function that should be called
    "x-axis step",                      // Name of the task (for debugging)
    128,                                // Stack size (bytes)
    NULL,                               // Parameter to pass
    1,                                  // Task priority
    NULL                                // Task handle
  );

  xTaskCreate(
    yAxisStep,                          // Function that should be called
    "y-axis step",                      // Name of the task (for debugging)
    128,                                // Stack size (bytes)
    NULL,                               // Parameter to pass
    1,                                  // Task priority
    NULL                                // Task handle
  );

  xTaskCreate(
    zAxisCtrl,                          // Function that should be called
    "z-axis ctrl",                      // Name of the task (for debugging)
    128,                                // Stack size (bytes)
    NULL,                               // Parameter to pass
    1,                                  // Task priority
    NULL                                // Task handle
  );
}

void loop()
{
  uint32_t samplingNow = millis();

  if (samplingNow - samplingTimeOut > SAMPLING_PERIOD)
  {
    //

    updateStatus();
    samplingTimeOut = samplingNow;
  }
}


/****************** MAIN FUNCTIONS *******************/
void updateStatus()
{
  #ifdef DEBUG_PRINTS
    //
  #endif
}


/********************* RTOS TASKS ********************/
void xAxisStep(void *parameter)
{
  while (true)
  {
    if (analogRead(XPOT) < 250)
    {
      LobiDevice.xAxisMotorStep(BACKWARD);
    }
    else if (analogRead(XPOT) > 700)
    {
      LobiDevice.xAxisMotorStep(FORWARD);
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void yAxisStep(void *parameter)
{
  while (true)
  {
    if (analogRead(YPOT) < 250)
    {
      LobiDevice.yAxisMotorStep(BACKWARD);
    }
    else if (analogRead(YPOT) > 700)
    {
      LobiDevice.yAxisMotorStep(FORWARD);
    }
  }

  vTaskDelay(50 / portTICK_PERIOD_MS);
}

void zAxisCtrl(void *parameter)
{
  while (true)
  {
    if (digitalRead(ZNEG) == LOW && digitalRead(ZPOS) == HIGH)
    {
      LobiDevice.zAxisMotorCtrl(FORWARD);
    }
    else if (digitalRead(ZNEG) == HIGH && digitalRead(ZPOS) == LOW)
    {
      LobiDevice.zAxisMotorCtrl(BACKWARD);
    }
    else
    {
      LobiDevice.zAxisMotorCtrl(STOP);
    }
    
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}