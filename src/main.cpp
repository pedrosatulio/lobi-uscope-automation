// Automation of LOBI's Eclipse TE2000 Inverted Microscope

#include "Lobi.h"


Lobi LobiDevice;                        // Lobi class

// Global variables and flags
byte zAxisButton;                       // Focus (z-axis) stepper motor control flag (button)
byte zAxisKeyboard;                     // Focus (z-axis) stepper motor control flag (keyboard)
uint32_t samplingTimeOut;               // Timing variable for sampling period


// Main functions
byte zAxisDirection();                  // Monitors focus (z-axis) direction switch
void updateStatus();                    // Update and print loop state


// RTOS Tasks
void keyboardControl(void *parameter);  // Control device functionalities from keyboard commands
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
  zAxisButton = false;
  zAxisKeyboard = false;
  samplingTimeOut = 0;

  // Initializing RTOS tasks
  xTaskCreate(
    keyboardControl,                    // Function that should be called
    "Keyboard command",                 // Name of the task (for debugging)
    128,                                // Stack size (bytes)
    NULL,                               // Parameter to pass
    1,                                  // Task priority
    NULL                                // Task handle
  );
  
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
byte zAxisDirection()
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
  //

  #ifdef DEBUG_PRINTS
    //
  #endif
}


/********************* RTOS TASKS ********************/
void keyboardControl(void *parameter)
{
  byte posStepCompleted = true;
  byte negStepCompleted = true;

  char rxKey;

  while (true)
  {
    rxKey = LobiDevice.keyboardRx();

    if (!zAxisButton)
    {
      zAxisKeyboard = true;

      if (rxKey == 'w' || !posStepCompleted)
      {
        posStepCompleted = LobiDevice.motorStep(POS);
      }
      else if (rxKey == 's' || !negStepCompleted)
      {
        negStepCompleted = LobiDevice.motorStep(NEG);
      }
      else
      {
        zAxisKeyboard = false;
      }
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void zAxisStep(void *parameter)
{
  byte stepCompleted = true;

  while (true)
  {
    if (!zAxisKeyboard)
    {
      zAxisButton = true;
      if (digitalRead(ZIN) == HIGH || !stepCompleted)
      {
        stepCompleted = LobiDevice.motorStep(zAxisDirection());
      }
      else
      {
        zAxisButton = false;
      }
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}