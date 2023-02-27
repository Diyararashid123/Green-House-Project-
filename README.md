# GreenHouse-Project
## Software part
### The first implementation is a fully functional date and time display on the screen in the dd/mm/yyyy form (I'm using the keypad as input for typing the date and using a 24-hour clock system).The following implementation is recording the temperature over 7 days and then taking the maximum, minimum, and average and displaying it on the screen. The temperatures and the averages for these temperatures were saved in a linked list. Lastly, both the date and time as well as the maximum, minimum, and average temperature were displayed all together on the display simultaneously. Thereafter, in order to make the light sensors point to where the sun is, we put the light sensors on the "servo" and they point towards the sun. However, we also keep count of how many hours the plants get light and darkness. If the plants can't get 16 hours of light and 8 hours of darkness, a lamp lights up if it is dark outside. Afterward, we set limits to the temperature. If we get more/less than what the user writes using the keypad an alarm in the form of a LED will set on. Afterward, we made a "fast mode" that ticks at a faster rate, approximately 30min/sec. 



## Hardware part
### I have used all those wiring diagrams I have already done and you can find the wiring diagram inside the hardware folder. Therefore, I have changed how the functions should work and how I should use them to work as we want. I used the following system components for this project: 

### Microchip (Atmel) SAM3X8E – ARM embedded computer platform (Arduino due)  

 #### Keypad (Port I/O)  

 #### Photosensor (A/D)  

 #### Temperature sensor (time)  

#### RC servo motor (PWM)  

 #### Switch (HW-int)  

 #### Display (port I/O)  

 #### LED  

#### 2 Push Buttons 
