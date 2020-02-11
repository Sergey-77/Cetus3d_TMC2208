
// Needs TMC2208Stepper library by teemuatlut
#include <TMC2208Stepper.h>
// Define pins
#define EN_PIN 2  // LOW: Driver enabled. HIGH: Driver disabled
#define rxPin 3
#define txPin 0
#define input_enable_motors 1
TMC2208Stepper driver = TMC2208Stepper(rxPin, txPin);  // Create driver and use
                                                  // Software Serial for communication
void setDriversInternal_ref(int current_mA){
  driver.push();                // Reset registers
  driver.pdn_disable(true);     // Use PDN/UART pin for communication
  driver.mstep_reg_select(true);
  driver.microsteps(32);
  driver.I_scale_analog(false); // Use internal voltage reference
  driver.rms_current(current_mA);// Set driver current
  driver.toff(5);               // Enable driver in software
  driver.blank_time(24);
  driver.intpol(1);
  driver.TPOWERDOWN(128); // ~2s until driver lowers to hold current
  //driver.hysterisis_start(3);
  //driver.hysterisis_end(2);
  //driver.pwm_lim(12);
  //driver.pwm_reg(8);
  driver.pwm_autograd(1);
  driver.pwm_autoscale(1);
  driver.pwm_freq(1);
  //driver.pwm_grad(14);
  //driver.pwm_ofs(36);
  driver.en_spreadCycle(false);
  driver.GSTAT(0b111); // Clear
}

void setDriversExternal_ref(){
  driver.push();                // Reset registers
  driver.pdn_disable(true);     // Use PDN/UART pin for communication
  driver.mstep_reg_select(true);
  driver.microsteps(32);
  driver.IHOLD_IRUN(0x1F10);
  driver.I_scale_analog(true);
  driver.internal_Rsense(false);
  driver.toff(3);               // Enable driver in software
  driver.blank_time(24);
  driver.intpol(1);
  driver.TPOWERDOWN(128); // ~2s until driver lowers to hold current
  driver.hysterisis_start(3);
  driver.hysterisis_end(3);
  //driver.pwm_lim(12);
  driver.pwm_autograd(1);
  driver.pwm_autoscale(1);
  driver.pwm_freq(0);
  driver.pwm_reg(5);
  driver.pwm_grad(14);
  driver.pwm_ofs(36);
  driver.en_spreadCycle(false);
  driver.GSTAT(0b111); // Clear
}

void setup() {
  pinMode(input_enable_motors, INPUT);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);   // Disable driver in hardware
  driver.beginSerial(9600);
  //setDriversExternal_ref();
  //setDriversInternal_ref(200);// Set driver current 200mA
}

void loop() {
 bool drivers_initialized;
 delay(500);
 if(digitalRead(input_enable_motors) &! drivers_initialized ){
  setDriversExternal_ref();
  //setDriversInternal_ref(200);// Set driver current 200mA
  digitalWrite(EN_PIN, LOW);    // Enable driver in hardware
  drivers_initialized = true;
 }
 else {
  digitalWrite(EN_PIN, HIGH);    // Disable driver in hardware
  drivers_initialized = false;
 }
}
