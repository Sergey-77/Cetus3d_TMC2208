#        Cetus3d_TMC2208

     This is TMC2208 stepstick drivers extension board for Cetus3d mk3 printer.
Original stepper drivers in Cetus3d printer are set for 32 microsteps, so I added Attiny85 to configure trinamic drivers for 32 microsteps. By default current is set by adjusting referense voltage with the potentiometer. It also can be set by Attiny's firmware, but only for same current for all axis in four steppers version. Three steppers version has separate serial connections to drivers, so current can be set for each motor individualy. My printer has stepper motors with 31 ohms coil resistance, so current has to be set low. Can't find any information about cetus motors. I think maximum current should be no more than 400mA. Reference voltage on my printer is set to: x 0.15v, y 0.1v, z 0.2v. I left extruder on original driver since it's not that loud anyway.</br>
     Printed board can be made with tonner transfer method since it's simple one sided design. Attiny was programmed with Arduino IDE. Motor pins on stepsticks were soldered pointing upward to get original connectors to fit. Also jumper needs to be installed on back of trinamic driver to get chip's serial connected to pin #5(PDN).</br>
     After board was installed it was hard to put cover back on. I had to remove spacer on power switch to slide cover back in place. Modified spacer can be installed after cover was installed. Also needs some insulation  between bottom of exension board and cover to prevent short circuit.

![Extension board](/5.jpg)
![Extension board](/3.jpg)
