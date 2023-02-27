# GreenHouse-Project
## Software part
### 



## Hardware part
### We have used all those wiring diagrams we have already done in labs 2 and 3. Therefore, we have changed how the functions should work and how we should use them to work as we want. We used the following system components for this project: 
### Microchip (Atmel) SAM3X8E – ARM embedded computer platform (Arduino due)  

 #### Keypad (Port I/O)  

 #### Photosensor (A/D)  

 #### Temperature sensor (time)  

#### RC servo motor (PWM)  

 #### Switch (HW-int)  

 #### Display (port I/O)  

 #### LED  

#### 2 Push Buttons 

###These are hardware drivers that was usen in the project:  

#### at91sam3x8.h 

#### system_sam3x.h 

#### This is all we have used, and we have made all the connections according to lab 2 and 3 wiring diagrams on Blackboard. 

Next, the kepay is programmed in such a way that it will be equal to -1, meaning if you do not press the keypad the program understands it and does not go any further and it will wait for a signal to reset, for example when you press the keypad, then when you have pressed a number that is more than -1 it will print out that number on the screen. 
