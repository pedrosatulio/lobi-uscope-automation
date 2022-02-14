// Automation of LOBI's Eclipse TE2000 Inverted Microscope

#include "Lobi.h"
Lobi LobiDevice;                        // Lobi class


// Global variables and flags
#ifdef LED_HEAD
  //
#endif
#ifdef MOTOR_HEAD
  //
#endif
byte      manualControl;                // Manual control flag (buttons and joystick)
byte      computerizedControl;          // Computerized control flag (keyboard)
uint32_t  samplingTimeOut;              // Timing variable for sampling period

// Main functions
void updateStatus();                    // Update and print loop state


// RTOS Tasks
#ifdef LED_HEAD
  void keyboardControl(void *parameter);  // Control device functionalities from keyboard commands
#endif
#ifdef MOTOR_HEAD
  void xAxisStep(void *parameter);        // x-axis control thread
  void yAxisStep(void *parameter);        // y-axis control thread
  void zAxisCtrl(void *parameter);        // Focus (z-axis) control thread
#endif


void setup()
{
  #ifdef LED_HEAD
    Serial.begin(9600);
  #endif

  #ifdef MOTOR_HEAD
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
    manualControl = false;
    computerizedControl = false;
  #endif

  samplingTimeOut = 0;

  // Initializing RTOS tasks
  #ifdef LED_HEAD
    xTaskCreate(
      keyboardControl,                    // Function that should be called
      "Keyboard command",                 // Name of the task (for debugging)
      128,                                // Stack size (bytes)
      NULL,                               // Parameter to pass
      1,                                  // Task priority
      NULL                                // Task handle
    );

    #ifdef DEBUG_PRINTS
      delay(1000);
      Serial.println("Setup... ok!");
    #endif
  #endif

  #ifdef MOTOR_HEAD
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
void updateStatus()
{
  //

  #ifdef DEBUG_PRINTS
    //
  #endif
}


/********************* RTOS TASKS ********************/
#ifdef LED_HEAD
  void keyboardControl(void *parameter)
  {
    char rxKey;
    char ledFlag = '\0';

    while (true)
    {
      if (ledFlag == '\0')
      {
        rxKey = LobiDevice.keyboardRx();

        if (!manualControl)
        {
          computerizedControl = true;
          LobiDevice.zAxisMotorCtrl(STOP);

          if (rxKey == 'd')
          {
            LobiDevice.xAxisMotorStep(FORWARD);
          }
          else if (rxKey == 'a')
          {
            LobiDevice.xAxisMotorStep(BACKWARD);
          }
          else if (rxKey == 'w')
          {
            LobiDevice.yAxisMotorStep(FORWARD);
          }
          else if (rxKey == 's')
          {
            LobiDevice.yAxisMotorStep(BACKWARD);
          }
          else if (rxKey == '+')
          {
            LobiDevice.zAxisMotorCtrl(FORWARD);
          }
          else if (rxKey == '-')
          {
            LobiDevice.zAxisMotorCtrl(BACKWARD);
          }
          else if (rxKey == 'q')
          {
            ledFlag = 'q';
          }
          else if (rxKey == 'e')
          {
            ledFlag = 'e';
          }
          else
          {
            computerizedControl = false;
          }
        }
      }
      else
      {
        switch (ledFlag)
        {
          case 'q':
            if (Serial.available > 0)
            {
              \\pwm_branco = Serial.parseInt();
            }
            else
            {
              \\pwm_branco = ultimo valor;
            }
            break;
          case 'e':
            if (Serial.available > 0)
            {
              \\pwm_ir = Serial.parseInt();
            }
            else
            {
              \\pwm_ir = ultimo valor;
            }
            break;
        }
      }
      

      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }
#endif

#ifdef MOTOR_HEAD
  void xAxisStep(void *parameter)
  {
    while (true)
    {
      if (!computerizedControl)
      {
        manualControl = true;
        if (analogRead(XPOT) < 250)
        {
          LobiDevice.xAxisMotorStep(BACKWARD);
        }
        else if (analogRead(XPOT) > 700)
        {
          LobiDevice.xAxisMotorStep(FORWARD);
        }
        else
        {
          manualControl = false;
        }
      }

      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }

  void yAxisStep(void *parameter)
  {
    while (true)
    {
      if (!computerizedControl)
      {
        manualControl = true;
        if (analogRead(YPOT) < 250)
        {
          LobiDevice.yAxisMotorStep(BACKWARD);
        }
        else if (analogRead(YPOT) > 700)
        {
          LobiDevice.yAxisMotorStep(FORWARD);
        }
        else
        {
          manualControl = false;
        }
      }

      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }

  void zAxisCtrl(void *parameter)
  {
    while (true)
    {
      if (!computerizedControl)
      {
        manualControl = true;
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
          manualControl = false;
        }
      }

      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }
#endif