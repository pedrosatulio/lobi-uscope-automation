// Automation of LOBI's Eclipse TE2000 Inverted Microscope

#include "Lobi.h"


Lobi LobiDevice;                        // Lobi class

// Global variables
uint32_t samplingTimeOut;               // Timing variable for sampling period


// Main functions
bool zAxisDirection();                  // Monitors focus (z-axis) direction switch
void updateStatus();                    // Update and print loop state


// RTOS Tasks
void zAxisStep(void *parameter);        // Focus (z-axis) control thread


void setup()
{
  #ifdef DEBUG_PRINTS
    Serial.begin(9600);
  #endif

  // Initializing stepper motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initializing switch pins and button pins
  pinMode(ZDIR, INPUT_PULLUP);
  pinMode(ZIN, INPUT);

  // Initializing flags and variables
  samplingTimeOut = 0;

  // Initializing RTOS tasks
  xTaskCreate(
    zAxisStep,                          // Function that should be called
    "z-axis step",                      // Name of the task (for debugging)
    128,                                // Stack size (bytes)
    NULL,                               // Parameter to pass
    1,                                  // Task priority
    NULL                                // Task handle
  );

  #ifdef DEBUG_PRINTS
    delay(1000);
    Serial.println("Setup... ok!");
  #endif
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
bool zAxisDirection()
{
  if (digitalRead(ZDIR))
  {
    return POS;
  }
  else
  {
    return NEG;
  }
}

void updateStatus()
{
  #ifdef DEBUG_PRINTS
    //
  #endif
}


/********************* RTOS TASKS ********************/
void zAxisStep(void *parameter)
{
  while (true)
  {
    if (digitalRead(ZIN) == HIGH)
    {
      LobiDevice.motorStep(zAxisDirection());
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}