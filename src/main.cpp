// Automation of LOBI's Eclipse TE2000 Inverted Microscope

#include "Lobi.h"

Lobi LobiDevice;

uint32_t samplingTimeOut;   // Timing variable for sampling period

// Interrupts
void zAxisStep();           // Button interruption for focus (z-axis) stepper motor

// Main functions
void updateStatus();

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

  // Initializing interrupt pins
  pinMode(ZIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ZIN), zAxisStep, RISING);

  // Initializing variables
  samplingTimeOut = 0;

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

void zAxisStep()
{
  LobiDevice.motorStep(POS);
}

void updateStatus()
{
  #ifdef DEBUG_PRINTS
    //
  #endif
}