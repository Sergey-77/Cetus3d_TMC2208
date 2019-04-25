// Needs TMC2208Stepper library by teemuatlut
#include <TMC2208Stepper.h>
// Define pins
#define EN_PIN 4  // LOW: Driver enabled. HIGH: Driver disabled
#define rxPin 5
#define txPin_x 3
#define txPin_y 1
#define txPin_z 2
#define input_enable_motors 0

void setDriversInternal_ref(int current_mA, TMC2208Stepper *driver){
  driver->push();                // Reset registers
  driver->pdn_disable(true);     // Use PDN/UART pin for communication
  driver->mstep_reg_select(true);
  driver->microsteps(32);
  driver->I_scale_analog(false); // Use internal voltage reference
  driver->internal_Rsense(false);
  driver->rms_current(current_mA);// Set driver current
  driver->toff(3);               // Enable driver in software
  driver->blank_time(24);
  driver->intpol(1);
  driver->TPOWERDOWN(128); // ~2s until driver lowers to hold current
  driver->hysterisis_start(3);
  driver->hysterisis_end(2);
  driver->pwm_lim(12);
  driver->pwm_reg(5);
  driver->pwm_autograd(1);
  driver->pwm_autoscale(1);
  driver->pwm_freq(1);
  driver->pwm_grad(14);
  driver->pwm_ofs(36);
  driver->en_spreadCycle(false);
  driver->GSTAT(0b111); // Clear
}

void setDriversExternal_ref(TMC2208Stepper *driver){
  driver->push();                // Reset registers
  driver->pdn_disable(true);     // Use PDN/UART pin for communication
  driver->mstep_reg_select(true);
  driver->microsteps(32);
  //driver->IHOLD_IRUN(0x1F10); // Irms = (Vref * 1.768A) / 2.5V = Vref * 0.707
  driver->IHOLD_IRUN(0x1008);   // Irms = Vref * 0.37565
  driver->I_scale_analog(true);
  driver->internal_Rsense(false);
  driver->toff(3);               // Enable driver in software
  driver->blank_time(24);
  driver->intpol(1);
  driver->TPOWERDOWN(128); // ~2s until driver lowers to hold current
  driver->hysterisis_start(3);
  driver->hysterisis_end(3);
  //driver->pwm_lim(12);
  driver->pwm_autograd(1);
  driver->pwm_autoscale(1);
  driver->pwm_freq(1);
  driver->pwm_reg(5);
  driver->pwm_grad(14);
  driver->pwm_ofs(36);
  driver->en_spreadCycle(false);
  driver->GSTAT(0b111); // Clear
}

void setup() {
  pinMode(input_enable_motors, INPUT);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);   // Disable driver in hardware
  TMC2208Stepper driver = TMC2208Stepper(rxPin, txPin_x, false);  // Create driver and use Software Serial for communication
  driver.beginSerial(9600);
  //setDriversInternal_ref(100, &driver);     //Stepper current can be set by Attiny 
  setDriversExternal_ref(&driver);            //or with driver potentiometer
  driver = TMC2208Stepper(rxPin, txPin_y, false);
  driver.beginSerial(9600);
  //setDriversInternal_ref(90, &driver);
  setDriversExternal_ref(&driver);
  driver = TMC2208Stepper(rxPin, txPin_z, false);
  driver.beginSerial(9600);
  //setDriversInternal_ref(150, &driver);
  setDriversExternal_ref(&driver);
}

void loop() {
 delay(500);
 if(digitalRead(input_enable_motors)){
  digitalWrite(EN_PIN, LOW);    // Enable driver in hardware
 }
 else {
  digitalWrite(EN_PIN, HIGH);    // Disable driver in hardware
 }
}
