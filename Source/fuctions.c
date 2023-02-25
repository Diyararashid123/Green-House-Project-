#include "at91sam3x8.h"

#include "system_sam3x.h"

#include "functions.h"

#include <time.h>

#include <stdio.h>

#include <string.h>

#define AT91C_PIOD_AIMER (AT91_CAST(AT91_REG *)         0x400E14B0)
#define AT91C_PIOD_DIFSR (AT91_CAST(AT91_REG *)         0x400E1484)
#define AT91C_PIOD_SCDR (AT91_CAST(AT91_REG *)          0x400E148C)
#define AT91C_PIOD_REHLSR (AT91_CAST(AT91_REG *)        0x400E14D4)

int tempratur = 0;
int flag = 0; 
int counter = 0;
int flagL1 = 0;
int flagL2 = 0;
int t_counter = 0;
int day = 28;
int month = 11;
int year = 2000;
int hour = 12;
int minute = 2;
int second = 15;
int d1 = 0;
int newDay = 0;
int newMin = 0;
int cLight = 0;
int fastmode = 0;
int button = 0;
int button2 =0;
int Tmin = 20;
int Tmax = 25;
int Value;
int temp = 0;
int start = 0;
int limit_counter=-1;
int limitx=0;
int outsidelimits=0;
int de_activated=0;

void fastToggle(int i){
if(i==1)
  fastmode=1;
else
  fastmode=0;
}



void set_limits(void) {
  int y=-1;

  switch (limit_counter){
  case 0:
    resetLimitscreen();
    limit_counter++;
   break;
   
  case 1:
  
  
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0xA);
  Write_Command_2_Display(0x40);

  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0xA);
  Write_Command_2_Display(0x24);
  

  char c1[] = "Write the lowest allowed temperature: ";
  writeS(c1);

  Write_Data_2_Display(0x28);
  Write_Data_2_Display(0xA);
  Write_Command_2_Display(0x24);
  
  Delay(5000000);
  int x=0;
  
  x = func() * 10;
  if(x!=-10){
  Write_Data_2_Display(0x10 + x/10);
  Write_Command_2_Display(0xC0);
  limitx=x;
  Delay(5000000);
  limit_counter++;
  }
  break;
  case 2:
   y=func();
   if(y!=-1){
  x = limitx+ y;
  Write_Data_2_Display(0x28);
  Write_Data_2_Display(0xA);
  Write_Command_2_Display(0x24);
  Write_Temp(x);
  Tmin = x;
  x=0;
  limitx=0;
  Delay(5000000);
    limit_counter++;
   }
  break;
  case 3:


  Write_Data_2_Display(0x50);
  Write_Data_2_Display(0xA);
  Write_Command_2_Display(0x24);
  char c2[]= "Write the highest allowed temperature: ";
  writeS(c2);

 
      

    
      Write_Data_2_Display(0x78);
      Write_Data_2_Display(0xA);
      Write_Command_2_Display(0x24);
      x = func() * 10;
      if(x!=-10){
        limitx=x;
      Write_Data_2_Display(0x10 + x/10);
      Write_Command_2_Display(0xC0);
      Delay(5000000);
      limit_counter++;
      }
      break;
  case 4:
    
      Write_Data_2_Display(0x78);
      Write_Data_2_Display(0xA);
      Write_Command_2_Display(0x24); 
      y=func();
      if(y!=-1){
      x = limitx + y;
      limitx=0;
      if(x<Tmin){
        Write_Data_2_Display(0x78);
        Write_Data_2_Display(0xA);
        Write_Command_2_Display(0x24);
        write_Char(' ');
        write_Char(' ');      
      limit_counter=limit_counter-1;
      }
      else{
      Tmax = x;
      Write_Temp(Tmax);
      Delay(5000000);
      limit_counter=5;
      }
      }
  break;
  case 5:
    

  Write_Data_2_Display(0xC8);
  Write_Data_2_Display(0xA);
  Write_Command_2_Display(0x24);
  char c3[] = "Press any key to continue!";
  writeS(c3);
  Delay(5000000);
  
  x = func();
  if (x!=-1){
  limit_counter=-1;
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x5);
  Write_Command_2_Display(0x40);
  }
  break;
  
  default:
    break;
  
  }
}

void Tempcontroll(int x) {
  if((outsidelimits==1)&&(limit_counter==-1)){
   Write_Data_2_Display(0x80);
  Write_Data_2_Display(0xC);
  Write_Command_2_Display(0x40);
  }
  
  if ((x < Tmin || x > Tmax)&&(button==0)&&(limit_counter==-1)) {
    outsidelimits=1;

    
  } else if ((button == 1)&&((x >= Tmin && x <= Tmax))) {
    button = 0;
    outsidelimits=0;
        if(de_activated==0){
          if(limit_counter==-1){
        Write_Data_2_Display(0x00);
        Write_Data_2_Display(0x5);
        Write_Command_2_Display(0x40);
          }else {           
            Write_Data_2_Display(0x00);
            Write_Data_2_Display(0xA);
            Write_Command_2_Display(0x40);          
        }
        }
        de_activated=0;
  }else if(button==1){
        outsidelimits=0;
        if(de_activated==0){
          if(limit_counter==-1){
        Write_Data_2_Display(0x00);
        Write_Data_2_Display(0x5);
        Write_Command_2_Display(0x40);
          }else {           
            Write_Data_2_Display(0x00);
            Write_Data_2_Display(0xA);
            Write_Command_2_Display(0x40);          
        }
        }
        de_activated=1;
  }        
              
}

void PIOD_Handler(void) {
    char c= * AT91C_PIOD_ISR & 66;
  if ((( c & (1 << 1)) == (1 << 1))) {
    if (button == 0) {
      button = 1;
    }

  }
  
  if ((( c & (1 << 6)) == (1 << 6))) {
    if (button2 == 0) {
      button2 = 1;
    }    
  }
}

void set_Buttons(void) { // enables the buttons

  * AT91C_PMC_PCER = (1 << 14);
  * AT91C_PIOD_IFER = (66);
  * AT91C_PIOD_AIMER = (66);
  * AT91C_PIOD_DIFSR = (66);
  * AT91C_PIOD_SCDR = (1670);
  * AT91C_PIOD_IER = (66);
  * AT91C_PIOD_PER = (66);

  * AT91C_PIOD_ODR = (66);
  * AT91C_PIOD_PPUDR = (66);

  * AT91C_PIOD_ISR;
  * AT91C_NVIC_ISER = (1 << 14);

}

void Set_Led(int x) {
  * AT91C_PMC_PCER = (1 << 14);
  * AT91C_PIOD_PER = (1 << 3);
  * AT91C_PIOD_OER = (1 << 3);
  * AT91C_PIOD_PPUDR = (1 << 3);

  if (x == 0)
    *
    AT91C_PIOD_CODR = (1 << 3);

  else
    *
    AT91C_PIOD_SODR = (1 << 3);

}


void set_menu(void) {

  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x5);
  Write_Command_2_Display(0x24);

  char c[] = "1. Select new date";
  char c1[] = "2. Measure temp over 7 days";
  char c2[] = "3. Fast mode";
  char c3[] = "4. Normal mode";
  char c4[] = "5. Track sun";
  char c5[] = "6. Set limits";
  writeS(c);
  Write_Data_2_Display(0x00 + 40);
  Write_Data_2_Display(0x5);
  Write_Command_2_Display(0x24);
  writeS(c1);
  Write_Data_2_Display(0x00 + 80);
  Write_Data_2_Display(0x5);
  Write_Command_2_Display(0x24);
  writeS(c2);
  Write_Data_2_Display(0x00 + 120);
  Write_Data_2_Display(0x5);
  Write_Command_2_Display(0x24);
  writeS(c3);
  Write_Data_2_Display(0x00 + 160);
  Write_Data_2_Display(0x5);
  Write_Command_2_Display(0x24);
  writeS(c4);
  Write_Data_2_Display(0x00 + 200);
  Write_Data_2_Display(0x5);
  Write_Command_2_Display(0x24);
  writeS(c5);
}

void menu(void) {
 
    Delay(300000);
    int a = func();

    switch (a) {
    case 1:
      resetDatescreen();
      set_Date();
      newDay=1;

      break;
    case 2:
  Write_Data_2_Display(0x0);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x40);//view the page

      break;
    case 3:
      fastToggle(1);

      break;
    case 4:
      fastToggle(0);

      break;
    case 5:
      Write_Data_2_Display(0x80);
      Write_Data_2_Display(0x7);
      Write_Command_2_Display(0x40);//view the page

      break;
    case 6:
      limit_counter=0;
      

      break;

    default:
      break;

    

  }

}

void set_Date(void) {
  Write_Data_2_Display(0x80);
  Write_Data_2_Display(0x2);
  Write_Command_2_Display(0x40);

  Write_Data_2_Display(0x80);
  Write_Data_2_Display(0x2);
  Write_Command_2_Display(0x24);

  int pcounter = 0;

  char c[] = "WRITE A  VALID DATE:";
  writeS(c);

  char c2[] = "YYYY/MM/DD";

  Write_Data_2_Display(0x07);
  Write_Data_2_Display(0x3);
  Write_Command_2_Display(0x24);
  writeS(c2);

  Write_Data_2_Display(0x07);
  Write_Data_2_Display(0x3);
  Write_Command_2_Display(0x24);
  int val = 0;
  int ydiv = 1;

  int m1 = 0;
  int dc = 0;
  int q =-1;
  int tsecond, tminute, thour, tday, tmonth, tyear = 0; // Temporary variables 

  while (pcounter < 10){    // we run the while loop 10 times for this function
    Delay(5000000);
    q=-1;
    while(q==-1){
     q = func();
    }
   
    if (q == 11) {  // Place 11 on the keypad is 0 
      q = 0;
    }
    if (pcounter < 4){// if our Pcounter is smaller than 4 (first 4 digits)
      if (q < 10) {//if the value is between 0-9
        pcounter++;// we add +1 every time we run it
        Write_Data_2_Display(0x10 + q);
        Write_Command_2_Display(0xC0);

        val = val + (q * 1000 / ydiv);// So we can print out 4 numbers and it can go maximum 9999.
        ydiv = ydiv * 10;

      }
    } else if (pcounter == 4) {// When we are on the 5th digit, we will print out "/".
      write_Char('/');
      tyear = val;
      val = 0;
      pcounter++;
    } else if (pcounter == 5) {// Here we are on the 6th digit

      if (q < 2) {// the first number of the month can only be 0 and 1
        m1 = q;
        if (q == 1) {// if its 1 then we set val to 10
          val = 10;
        }
        pcounter++;

        Write_Data_2_Display(0x10 + q);
        Write_Command_2_Display(0xC0);
      }

    } else if (pcounter == 6) {// here we are on the 7th digit and its the other part of the month

      if (m1 == 0) {// if we know that it's 0 on the digit 6 then we can only have 1,2,3,4,5,6,7,8,9

        if (q != 0 && q < 10) {// we must have a number between 1-9
          val = val + q;
          pcounter++;

          Write_Data_2_Display(0x10 + q);
          Write_Command_2_Display(0xC0);
        }
      } else {// otherwise it can only be 0 1 2 because  we have maximum 12 and minimum 10
        if (q < 3) {
          pcounter++;
          val = val + q;
          Write_Data_2_Display(0x10 + q);
          Write_Command_2_Display(0xC0);
        }
      }

    } else if (pcounter == 7) {// Here on the 8th digit we print out another / and set month value
      write_Char('/');
      tmonth = val;
      val = 0;
      pcounter++;

    } else if (pcounter == 8) {// Here we have 9th digit and now we input the days 
      if (q < 4) {// first day number can only be 0,1,2,3 
        val = q * 10;
        dc = q;
        pcounter++;

        Write_Data_2_Display(0x10 + q);
        Write_Command_2_Display(0xC0);
      }

    } else {//
      if (dc < 3) {// If we have a the previous that are 0 1 2 
        if ((dc!= 0||q!= 0)  && q < 10) {// so we can have a number 1-9
          val = val + q;
          pcounter++;
          tday = val;
          Write_Data_2_Display(0x10 + q);
          Write_Command_2_Display(0xC0);
        }

      } else {// else if we have 3 then we can only have 0 and 1
        if (q < 2) {
          pcounter++;
          val = val + q;
          tday = val;
          Write_Data_2_Display(0x10 + q);
          Write_Command_2_Display(0xC0);
        }
      }

    }

  }
  pcounter = 0;
  char c4[] = "HH:MM:SS";
  char c3[] = "WRITE A VALID TIME:";
  Write_Data_2_Display(0x48);
  Write_Data_2_Display(0x3);
  Write_Command_2_Display(0x24);
  writeS(c3);

  Write_Data_2_Display(0xA7);
  Write_Data_2_Display(0x3);
  Write_Command_2_Display(0x24);
  writeS(c4);

  Write_Data_2_Display(0xA7);
  Write_Data_2_Display(0x3);
  Write_Command_2_Display(0x24);
  val = 0;
  int qPrev = 0;
  while (pcounter < 8) {// we will run this while loop 8 time because  we have 8 digits 
    Delay(5000000);
    q=-1;
    while(q==-1){
     q = func();
    }
      
    if (q == 11)
      q = 0;
    switch (pcounter) {// we are using switch cases to decide every digit
    case 0:
      if (q < 3) {// Here we can only have 0 1 2 because  we can only have max 2
        pcounter++;
        Write_Data_2_Display(0x10 + q);
        Write_Command_2_Display(0xC0);
        val = q * 10;
      }
      break;
    case 1:
      if (qPrev < 2) {//if previous value were 0 or 1 
        if (q < 10) {// we can have 0-9
          pcounter++;
          Write_Data_2_Display(0x10 + q);
          Write_Command_2_Display(0xC0);
          val = val + q;
        }
      } else {
        if (q < 4) {// otherwise, if we have 2 we can only have 0 1 2 3( 20, 21, 22, 23)
          pcounter++;
          Write_Data_2_Display(0x10 + q);
          Write_Command_2_Display(0xC0);
          val = val + q;
        }
      }

      break;
    case 2:// here we just put colon between them 
      write_Char(':');
      pcounter++;
      thour = val;
      val = 0;
      qPrev = 0;

      break;
    case 3:
      if (q < 7) {// we can have 0-6 on the first digit for minute
        qPrev = q;
        Write_Data_2_Display(0x10 + q);
        Write_Command_2_Display(0xC0);
        val = q * 10;
        pcounter++;
      }
      break;
    case 4:// On the second part of minute so if the first digit is equal to 6
      if (qPrev == 6) {
        if (q == 0) {// Next nuber must be 0
          Write_Data_2_Display(0x10);
          Write_Command_2_Display(0xC0);
          pcounter++;
        }
      } else {// otherwise we can have 0-9
        if (q < 10) {
          pcounter++;
          val = val + q;
          Write_Data_2_Display(0x10 + q);
          Write_Command_2_Display(0xC0);

        }
      }
      break;
    case 5:// here we just put colon between them 
      write_Char(':');
      pcounter++;
      tminute = val;
      val = 0;
      qPrev = 0;
      
      break;
    case 6:// Here we are on the second part and here we can have up to 6 as well(0-6)
      if (q < 7) {
        qPrev = q;
        Write_Data_2_Display(0x10 + q);
        Write_Command_2_Display(0xC0);
        val = q * 10;
        pcounter++;
      }
      break;
    case 7:
      if (qPrev == 6) {// And this is the same as minute if we have 6, the next number will be 0 
        if (q == 0) {
          Write_Data_2_Display(0x10);
          Write_Command_2_Display(0xC0);
          pcounter++;
          tsecond = val;
        }
      } else {// otherwise we can have 0-9
        if (q < 10) {
          pcounter++;
          val = val + q;
          Write_Data_2_Display(0x10 + q);
          Write_Command_2_Display(0xC0);
          tsecond = val;
        }
      }
      break;
    } 
     q=-1;
  } 
  //here we set all our global variables to the values of the Temporary variables
  year = tyear;
  month = tmonth;
  day = tday;
  hour = thour;
  minute = tminute;
  second = tsecond;
  Delay(300000);
          
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x5);
  Write_Command_2_Display(0x40);
} 

void set_tempscreen(void) {

  Write_Data_2_Display(0x28);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);

  char c[] = "MIN:   KL       MAX:   KL       AVG:  ";
  writeS(c);
  Write_Data_2_Display(0x28 + 80);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeS(c);
  Write_Data_2_Display(0x28 + 160);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  writeS(c);
  Write_Data_2_Display(0x18);
  Write_Data_2_Display(0x1);
  Write_Command_2_Display(0x24);
  writeS(c);
  Write_Data_2_Display(0x18 + 80);
  Write_Data_2_Display(0x1);
  Write_Command_2_Display(0x24);
  writeS(c);
  Write_Data_2_Display(0x18 + 160);
  Write_Data_2_Display(0x1);
  Write_Command_2_Display(0x24);
  writeS(c);
  Write_Data_2_Display(0x08);
  Write_Data_2_Display(0x2);
  Write_Command_2_Display(0x24);
  writeS(c);
}

void write_Date(void) {
  int p1 = year / 1000;
  Write_Data_2_Display(0x10 + p1);
  Write_Command_2_Display(0xC0);

  int p2 = year % 1000;
  if (p2 < 100) {
    Write_Data_2_Display(0x10);
    Write_Command_2_Display(0xC0);
  } else {
    p1 = p2 / 100;
    Write_Data_2_Display(0x10 + p1);
    Write_Command_2_Display(0xC0);
  }
  p2 = p2 % 100;
  Write_Temp(p2);
  writeS("/");
  Write_Temp(month);
  writeS("/");
  Write_Temp(day);
}

void write_Time(void) {
  Write_Temp(hour);
  writeS(":");
  Write_Temp(minute);
  writeS(":");
  Write_Temp(second);
}


void Green_House(void) {


        Write_Data_2_Display(0x00);
        Write_Data_2_Display(0x5);
        Write_Command_2_Display(0x40);

  write_Date();
  

  
  Write_Data_2_Display(0xF8);
  Write_Data_2_Display(0xC);
  Write_Command_2_Display(0x24);
  
  char c8[] = "Temperature is outside the limits!";
  writeS(c8);

  LinkedList * first = NULL; //create a linkedlist for the values we read
  LinkedList * a = NULL; //a temporary linkedlist element

  Delay(4000000);
  int di = Read_Temp(); // initiate read temp
  Temp_Mesurement();
  Delay(25);

  flag = 1;
  int maxtemp = 0; // a low vallue for maximum temp
  int mintemp = 100; // a high vallue for minimum temp
  d1=0;
  int sum = 0; //a variable to keep track of the sum
  int avg = 0; // a variable to keep track of the average
  int mincounter = 0; // count the amout of minutes
  newDay = 0; // 1 if its a new day
  newMin = 0; // 1 if its a new minute
  char c7[]="Latest: ";
  
  
  //-----------------------------Light
  Write_Data_2_Display(0x80);
  Write_Data_2_Display(0x7);
  Write_Command_2_Display(0x24);//adress where we write

  char c1[] = "TRACKING THE SUNLIGHT";
  char c2[] = "Hours of sunlight: ";
  char c3[] = "Hours of darkness: ";
  char c4[] = "Hours left of the day: ";
  char c5[] = "Angle of the sun: ";
  writeS(c1); // write c1 to display

  double d = Light_Mesurment();
  Delay(500000);
  newMin = 0;
  double right = 0;
  double left = 0;
  Movment_Servo(0); // set servo to 0 deg
  int servodeg = 0;
  int x=0;
  int minOfLight = 0;
  int h=0;
  int m=0;
  int minLeft = 0;
  int minDarkness = 0;
  int min_LedLight = 0;
  minDarkness = (hour * 60) + minute; // if we start in the middle of the day we count everyting before as darkness
  double sumdegre = 0;

   Init_Light();
   
   
           Write_Data_2_Display(0x0);
        Write_Data_2_Display(0x0);
        Write_Command_2_Display(0x24);
        write_Date(); // function that prints the date on the display 

  while (1) {
    t_ime(); // sync the clock
    set_limits();
    if(limit_counter==-1){
        menu();
     if(button2==1){
      button2=0;
        Write_Data_2_Display(0x00);
        Write_Data_2_Display(0x5);
        Write_Command_2_Display(0x40);
    }
    
    }
    

    Write_Data_2_Display(0x58);
    Write_Data_2_Display(0x2);
    Write_Command_2_Display(0x24); // set adress
    write_Date(); // function that prints the date on the display

    Write_Data_2_Display(0x76);
    Write_Data_2_Display(0x2);
    Write_Command_2_Display(0x24); // set adress
    write_Time(); // function that prints the time on the display

    if (newDay == 1) { // if its a new day
      d1++; //day counter
      if(d1==7){
      d1=0;
      }
   
          servodeg=0;
          Movment_Servo(servodeg);
          newDay = 0;
          minOfLight = 0;
          minDarkness = 0;
      if (d1 < 4) { //first 4 days
        Write_Data_2_Display(0x50 * d1);
        Write_Data_2_Display(0x0);
        Write_Command_2_Display(0x24);
        write_Date(); // function that prints the date on the display               
      } else if (d1 < 7) { //day 5-7
        Write_Data_2_Display(0x40 + 0x50 * (d1 - 4));
        Write_Data_2_Display(0x1);
        Write_Command_2_Display(0x24);
        write_Date(); // function that prints the date on the display 
      }

     
      mintemp = 100;
      maxtemp = 0;
      sum = 0;
      avg = 0;
      mincounter = 0;
    }

    if (flag == 1) { // flag from temp meashurement
      Temp_Mesurement();
      Delay(4000000);
       x = Read_Temp(); //read temp
       Delay(500000);
     

      if (newMin == 1) {
        Tempcontroll(x); //see if temp is alowed
        
        mincounter++;
        sum = sum + x;
        avg = sum / mincounter;
        newMin = 0;

        if (fastmode == 1) { //if we run the code in fast mode
          for (int i = 0; i < 30; i++) {
            a = readSensor(year, month, day, hour, minute, x, &first);
            if (minute < 59) {
              minute++;
              t_ime();
            }
            insertFirst( &first, a); //Insert it first int the LinkedList
          }
          newMin = 0;
        } else { //if not in fastmode
          a = readSensor(year, month, day, hour, minute, x, &first);
          insertFirst( &first, a); //Insert it first int the LinkedList
        }
          
        if (maxtemp < x) { //if its a new max temp for the day
          maxtemp = x;
          h = a -> hour;
           m = a -> minute;
          if (d1 < 3) {
            Write_Data_2_Display(0x42 + 0x50 * d1);
            Write_Data_2_Display(0x0);
            Write_Command_2_Display(0x24);
          } else if (d1 < 6) {
            Write_Data_2_Display(0x32 + 0x50 * (d1 - 3));
            Write_Data_2_Display(0x1);
            Write_Command_2_Display(0x24);
          } else {
            Write_Data_2_Display(0x22);
            Write_Data_2_Display(0x2);
            Write_Command_2_Display(0x24);
          }
          write_Timestamp(h, m);
        }

        if (mintemp > x) { // Print min temp and the timestamp
          mintemp = x;
          if (d1 < 3) {
            Write_Data_2_Display(0x32 + 0x50 * d1);
            Write_Data_2_Display(0x0);
            Write_Command_2_Display(0x24);
          } else if (d1 < 6) {
            Write_Data_2_Display(0x22 + 0x50 * (d1 - 3));
            Write_Data_2_Display(0x1);
            Write_Command_2_Display(0x24);
          } else {
            Write_Data_2_Display(0x12);
            Write_Data_2_Display(0x2);
            Write_Command_2_Display(0x24);
          }
           h = a -> hour;
           m = a -> minute;
          write_Timestamp(h, m);
        }

        if (d1 < 3) {
          Write_Data_2_Display(0x3C + 0x50 * d1);
          Write_Data_2_Display(0x0);
          Write_Command_2_Display(0x24);
          Write_Temp(maxtemp);

          Write_Data_2_Display(0x2C + 0x50 * d1);
          Write_Data_2_Display(0x0);
          Write_Command_2_Display(0x24);
          Write_Temp(mintemp);

          Write_Data_2_Display(0x4C + 0x50 * d1);
          Write_Data_2_Display(0x0);
          Write_Command_2_Display(0x24);
          Write_Temp(avg);
        } else if (d1 < 6) {
          Write_Data_2_Display(0x2C + 0x50 * (d1 - 3));
          Write_Data_2_Display(0x1);
          Write_Command_2_Display(0x24);
          Write_Temp(maxtemp);

          Write_Data_2_Display(0x1C + 0x50 * (d1 - 3));
          Write_Data_2_Display(0x1);
          Write_Command_2_Display(0x24);
          Write_Temp(mintemp);

          Write_Data_2_Display(0x3C + 0x50 * (d1 - 3));
          Write_Data_2_Display(0x1);
          Write_Command_2_Display(0x24);
          Write_Temp(avg);
        } else {
          Write_Data_2_Display(0x1C);
          Write_Data_2_Display(0x2);
          Write_Command_2_Display(0x24);
          Write_Temp(maxtemp);

          Write_Data_2_Display(0x0C);
          Write_Data_2_Display(0x2);
          Write_Command_2_Display(0x24);
          Write_Temp(mintemp);

          Write_Data_2_Display(0x2C);
          Write_Data_2_Display(0x2);
          Write_Command_2_Display(0x24);
          Write_Temp(avg);
        }
          Write_Data_2_Display(0x67);
          Write_Data_2_Display(0x2);
          Write_Command_2_Display(0x24);
          writeS(c7);
          Write_Temp(x);  
      }
    }
     //  if(limit_counter==-1){
       //menu();
       //}
       
    
    Write_Data_2_Display(0xD8);
    Write_Data_2_Display(0x9);
    Write_Command_2_Display(0x24);
    char c6[] = "Date: ";
    writeS(c6); //write c6 to display
    write_Date();

    Write_Data_2_Display(0xEC);
    Write_Data_2_Display(0x9);
    Write_Command_2_Display(0x24);
    char c7[] = "Time: ";
    writeS(c7); // write c7 to display
    write_Time();
    

     
 

    if (cLight < 2) {
      left = Light_Mesurment(); // mesurement of sensonr 1
      Delay(500000);
      right = Light_Mesurment();// meurement of sensor 2
      Delay(500000);
    } else {

      Delay(200000);
      sumdegre = left - right; 
      if(left<1 || right<1)     // if its light   
      if (sumdegre > 0.1 || sumdegre < -0.1) { // if the differsnse betwen the sensors is to big
        if (left > right && servodeg < 180) {
          servodeg = servodeg + 5;
          Movment_Servo(servodeg);
        } else if (servodeg >= 5 && right > left) {
          servodeg = servodeg - 5;
          Movment_Servo(servodeg);
        }
      }
      if(fastmode==0&&newMin==0)
        Init_Light();
      
        t_ime();    

   minLeft = 1440 - (hour * 60) - minute; // minutes left of the day
   
        if (right > 1 && left > 1) { // if its dark
          minDarkness = minDarkness +1+ 29*fastmode;
          if ((minOfLight + minLeft) <= 960) { //if we need to to turn on the light to get 16 hours of light
            Set_Led(1);// led is on
            min_LedLight = min_LedLight +1+ 29*fastmode;
          } else {
            Set_Led(0);// led is off
          }
        } else {
          minOfLight = minOfLight +1+ 29*fastmode;
          Set_Led(0); // led is off
        }

        Write_Data_2_Display(0xF8);
        Write_Data_2_Display(0x7);
        Write_Command_2_Display(0x24);
        writeS(c2);
        Write_Temp(minOfLight / 60);

        Write_Data_2_Display(0x20);
        Write_Data_2_Display(0x8);
        Write_Command_2_Display(0x24);
        writeS(c3);
        Write_Temp(minDarkness / 60);

        Write_Data_2_Display(0x48);
        Write_Data_2_Display(0x8);
        Write_Command_2_Display(0x24);
        writeS(c4);
        Write_Temp(minLeft / 60);

        Write_Data_2_Display(0x70);
        Write_Data_2_Display(0x8);
        Write_Command_2_Display(0x24);
        writeS(c5);
        int temporary = 0;
        int printdeg = servodeg;
        temporary = servodeg / 100;
        if (temporary > 0) {
          write_Char('1');
          printdeg = servodeg % 100;
          Write_Temp(printdeg);
        } else {
          Write_Temp(servodeg);
          write_Char(' ');
        }
        Init_Light();// ready for new measurements
      
    }   
    
    
    
    
    
  }

}

void write_Timestamp(int h, int m) {
  Write_Temp(h); //write hour
  writeS(":");
  Write_Temp(m); //write minute
}

void write_Char(char c) {

  char val = ' ';
  switch (c) {
  case ' ':
    val = 0x00;
    break;
  case '!':
    val = 0x01;
    break;
  case '"':
    val = 0x02;
    break;
  case '#':
    val = 0x03;
    break;
  case '$':
    val = 0x04;
    break;
  case '%':
    val = 0x05;
    break;
  case '&':
    val = 0x06;
    break;
  case '\'':
    val = 0x07;
    break;
  case '(':
    val = 0x08;
    break;
  case ')':
    val = 0x09;
    break;
  case '*':
    val = 0x0A;
    break;
  case '+':
    val = 0x0B;
    break;
  case ',':
    val = 0x0C;
    break;
  case '-':
    val = 0x0D;
    break;
  case '.':
    val = 0x0E;
    break;
  case '/':
    val = 0x0F;
    break;
  case '0':
    val = 0x10;
    break;
  case '1':
    val = 0x11;
    break;
  case '2':
    val = 0x12;
    break;
  case '3':
    val = 0x13;
    break;
  case '4':
    val = 0x14;
    break;
  case '5':
    val = 0x15;
    break;
  case '6':
    val = 0x16;
    break;
  case '7':
    val = 0x17;
    break;
  case '8':
    val = 0x18;
    break;
  case '9':
    val = 0x19;
    break;
  case ':':
    val = 0x1A;
    break;
  case ';':
    val = 0x1B;
    break;
  case '<':
    val = 0x1C;
    break;
  case '=':
    val = 0x1D;
    break;
  case '>':
    val = 0x1E;
    break;
  case '?':
    val = 0x1F;
    break;
  case '@':
    val = 0x20;
    break;
  case 'A':
    val = 0x21;
    break;
  case 'B':
    val = 0x22;
    break;
  case 'C':
    val = 0x23;
    break;
  case 'D':
    val = 0x24;
    break;
  case 'E':
    val = 0x25;
    break;
  case 'F':
    val = 0x26;
    break;
  case 'G':
    val = 0x27;
    break;
  case 'H':
    val = 0x28;
    break;
  case 'I':
    val = 0x29;
    break;
  case 'J':
    val = 0x2A;
    break;
  case 'K':
    val = 0x2B;
    break;
  case 'L':
    val = 0x2C;
    break;
  case 'M':
    val = 0x2D;
    break;
  case 'N':
    val = 0x2E;
    break;
  case 'O':
    val = 0x2F;
    break;
  case 'P':
    val = 0x30;
    break;
  case 'Q':
    val = 0x31;
    break;
  case 'R':
    val = 0x32;
    break;
  case 'S':
    val = 0x33;
    break;
  case 'T':
    val = 0x34;
    break;
  case 'U':
    val = 0x35;
    break;
  case 'V':
    val = 0x36;
    break;
  case 'W':
    val = 0x37;
    break;
  case 'X':
    val = 0x38;
    break;
  case 'Y':
    val = 0x39;
    break;
  case 'Z':
    val = 0x3A;
    break;
  case '[':
    val = 0x3B;
    break;

  case ']':
    val = 0x3D;
    break;
  case '^':
    val = 0x3E;
    break;
  case '_':
    val = 0x3F;
    break;
  case 'a':
    val = 0x41;
    break;
  case 'b':
    val = 0x42;
    break;
  case 'c':
    val = 0x43;
    break;
  case 'd':
    val = 0x44;
    break;
  case 'e':
    val = 0x45;
    break;
  case 'f':
    val = 0x46;
    break;
  case 'g':
    val = 0x47;
    break;
  case 'h':
    val = 0x48;
    break;
  case 'i':
    val = 0x49;
    break;
  case 'j':
    val = 0x4A;
    break;
  case 'k':
    val = 0x4B;
    break;
  case 'l':
    val = 0x4C;
    break;
  case 'm':
    val = 0x4D;
    break;
  case 'n':
    val = 0x4E;
    break;
  case 'o':
    val = 0x4F;
    break;
  case 'p':
    val = 0x50;
    break;
  case 'q':
    val = 0x51;
    break;
  case 'r':
    val = 0x52;
    break;
  case 's':
    val = 0x53;
    break;
  case 't':
    val = 0x54;
    break;
  case 'u':
    val = 0x55;
    break;
  case 'v':
    val = 0x56;
    break;
  case 'w':
    val = 0x57;
    break;
  case 'x':
    val = 0x58;
    break;
  case 'y':
    val = 0x59;
    break;
  case 'z':
    val = 0x5A;
    break;
  case '{':
    val = 0x5B;
    break;
  case '|':
    val = 0x5C;
    break;
  case '}':
    val = 0x5D;
    break;

  default:
    return;
  }
  Write_Data_2_Display(val);
  Write_Command_2_Display(0xC0);

}

void writeS(char c[]) {

  for (int i = 0; i < strlen(c); i++) {
    write_Char(c[i]);
  }
}

void t_ime(void) {

  while (t_counter > 999) {
    t_counter = t_counter - 999;
    second = second + 1 + 60 * fastmode;
 
    if (second > 59) {
      second = 0;
      minute++;
      newMin = 1;
      if (minute > 59) {
        minute = 0;
        hour++;
        if (hour == 24) {
          hour = 0;
          day++;
          newDay = 1;
          switch (month) {
          case 1:
            if (day > 31) {
              day = 1;
              month++;
            }
          case 2:
            if (day > 28) {
              day = 1;
              month++;
            }
          case 3:
            if (day > 31) {
              day = 1;
              month++;
            }
          case 4:
            if (day > 30) {
              day = 0;
              month++;
            }
          case 5:
            if (day > 31) {
              day = 1;
              month++;
            }
          case 6:
            if (day > 30) {
              day = 0;
              month++;
            }
          case 7:
            if (day > 31) {
              day = 1;
              month++;
            }
          case 8:
            if (day > 31) {
              day = 1;
              month++;
            }
          case 9:
            if (day > 30) {
              day = 1;
              month++;
            }
          case 10:
            if (day > 30) {
              day = 1;
              month++;
            }
          case 11:
            if (day > 31) {
              day = 1;
              month++;
            }
          case 12:
            if (day > 31) {
              day = 1;
              month = 1;
              year++;
            }
          }
        }
      }
    }
  }
}

void Write_light(double l) {
  int arr[10];
  int j = 0;
  int z = -1;
  int z2 = -1;
  if (l < 1)
    z = 0;
  if (l < 0.1)
    z2 = 0;

  int t = l * 1000;
  while (t != 0) {
    int k = t % 10;
    arr[j] = k;
    t = t / 10;
    j++;
  }
  if (j > 4)
    j = 4;
  if (z == 0) {
    Write_Data_2_Display(0x10);
    Write_Command_2_Display(0xC0);

    Write_Data_2_Display(0x0E);
    Write_Command_2_Display(0xC0);
  } else {
    Write_Data_2_Display(0x10 + arr[j - 1]);
    Write_Command_2_Display(0xC0);

    Write_Data_2_Display(0x0E);
    Write_Command_2_Display(0xC0);
  }
  if (z2 == 0) {
    Write_Data_2_Display(0x10);
    Write_Command_2_Display(0xC0);
  }
  for (int i = j - 1; i > -1; i--) {
    Write_Data_2_Display(0x10 + arr[i]);
    Write_Command_2_Display(0xC0);
  }
}

void Write_Temp(int t) {
  int p1 = t / 10;
  int p2 = t % 10;

  Write_Data_2_Display(0x10 + p1);
  Write_Command_2_Display(0xC0);
  Write_Data_2_Display(0x10 + p2);
  Write_Command_2_Display(0xC0);
}

void Init_Temp(void) {
  * AT91C_PMC_PCER = 1 << 12; // timer clock PIOB
  * AT91C_PIOB_PER = 1 << 25; // ACTIVING pin
  * AT91C_PMC_PCER = 1 << 27; // Timer clock zero
  * AT91C_TC0_CMR = ( * AT91C_TC0_CMR & 65534); //clock select(TCLK1)
  * AT91C_TC0_CCR = 5; // Channel control register enable and reset TC0 
  * AT91C_TC0_CMR = ( * AT91C_TC0_CMR | (1 << 17));
  * AT91C_TC0_CMR = ( * AT91C_TC0_CMR | (1 << 18));
  * AT91C_PIOB_OER = 1 << 25; // as output
  while (counter < 17) {}
  counter = 0;
  * AT91C_PIOB_ODR = 1 << 25; // as output 
  NVIC_EnableIRQ((IRQn_Type) 27);
  NVIC_SetPriority((IRQn_Type) 37, 1);
  NVIC_ClearPendingIRQ((IRQn_Type) 27);
  * AT91C_TC0_IER = 1 << 6;
}

void Temp_Mesurement(void) {
  * AT91C_PIOB_OER = 1 << 25; // enable puls
  Delay(25);
  * AT91C_PIOB_SODR = 1 << 25;
  * AT91C_PIOB_ODR = 1 << 25; // disable puls
  * AT91C_PIOB_CODR = 1 << 25;
  flag = 0;
  Delay(25);
  * AT91C_TC0_CCR = 1 << 2;
  * AT91C_TC0_IER = 1 << 6;
  * AT91C_TC0_SR;
}

int Read_Temp(void) {
  int Ra = * AT91C_TC0_RA;
  int Rb = * AT91C_TC0_RB;
  int temp = Rb - Ra;
  tempratur = (temp / (42 * 5)) - 273.15;
  return tempratur;
}

void TC0_Handler(void) {
  * AT91C_TC0_IDR = 1 << 6;
  flag = 1;
}

void Init_PWM_Servo(void) {
  * AT91C_PMC_PCER = 1 << 12;
  * AT91C_PMC_PCER1 = 1 << 4;
  * AT91C_PIOB_ABMR = 1 << 17;
  * AT91C_PIOB_PDR = 1 << 17;
  * AT91C_PIOB_PPUDR = 1 << 17;
  * AT91C_PWMC_ENA = 1 << 1;
  * AT91C_PWMC_CH1_CMR = 5 << 0;
  * AT91C_PWMC_CH1_CPRDR = 52500;
  * AT91C_PWMC_CH1_CDTYR = 1800;
}

void Movment_Servo(int deg) {
  * AT91C_PWMC_CH1_CDTYR = 1800 + deg * 25;
}

void Init_Light(void) {
  * AT91C_PMC_PCER1 = 1 << 5;
  * AT91C_ADCC_MR = 1 << 10;
  * AT91C_PMC_PCER1 = 1 << 11;
  * AT91C_PIOA_PER = (1 << 27);
  * AT91C_ADCC_CHER = 1 << 1;
  * AT91C_ADCC_CHER = 1 << 2;
  NVIC_EnableIRQ((IRQn_Type) 37);
  NVIC_SetPriority((IRQn_Type) 37, 3);
  NVIC_ClearPendingIRQ((IRQn_Type) 37);
  flagL1 = 1;
  cLight = 0;
}

double Light_Mesurment() {
  * AT91C_ADCC_CR = 1 << 1; // ADC control register
  * AT91C_ADCC_SR;
  double res = 0;
  while (flagL1 == 0 && flagL2 == 0) {}
  if (flagL1 == 1) {
    flagL1 = 0;
    res = ( * AT91C_ADCC_CDR1) * (3.3 / (0xFFF));
    Delay(500000);
    * AT91C_ADCC_IDR = (1 << 1);
    * AT91C_ADCC_IER = (1 << 2);
  } else if (flagL2 == 1) {
    flagL2 = 0;
    res = ( * AT91C_ADCC_CDR2) * (3.3 / (0xFFF));
    Delay(500000);
    * AT91C_ADCC_IDR = (1 << 2);
    * AT91C_ADCC_IER = (1 << 1);
  }
  return res;
}

void resetTempscreen(void){
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  for (int i = 0; i < 640; i++) {
    Write_Data_2_Display(0x0);
    Write_Command_2_Display(0xC0);
  }
  set_tempscreen();
}

void resetDatescreen(void){
  Write_Data_2_Display(0x80);
  Write_Data_2_Display(0x2);
  Write_Command_2_Display(0x24);
  for (int i = 0; i < 640; i++) {
    Write_Data_2_Display(0x0);
    Write_Command_2_Display(0xC0);
  }
}

void resetLimitscreen(void){
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0xA);
  Write_Command_2_Display(0x24);
  for (int i = 0; i < 640; i++) {
    Write_Data_2_Display(0x0);
    Write_Command_2_Display(0xC0);
  }
}

void ADC_Handler(void) {
  volatile int x = * AT91C_ADCC_SR; // get the one that triggered
  NVIC_ClearPendingIRQ((IRQn_Type) 37);
  if ((x & (1 << 1)) == (1 << 1) && (cLight == 1)) {
    flagL1 = 1;
    * AT91C_ADCC_IDR = (1 << 1);
    * AT91C_ADCC_IDR = (1 << 2);
    cLight = 0;
  } else if ((x & (1 << 2)) == (1 << 2) && (cLight == 0)) {
    flagL2 = 1;
    * AT91C_ADCC_IDR = (1 << 2);
    * AT91C_ADCC_IDR = (1 << 1);
    cLight = 2;
  } else if (cLight == 2) {
    * AT91C_ADCC_IDR = (1 << 2);
    * AT91C_ADCC_IDR = (1 << 1);
    flagL1 = 0;
    flagL2 = 0;
  }
}

void Delay(int v) {
  int i;
  for (i = 0; i < v; i++) {
    __asm("nop");
  }
}

void SysTick_Handler() {
  t_counter++;
  counter++;
}

void set_KeyPad() {
  ( * AT91C_PIOD_PER) = 0x4;
  ( * AT91C_PIOC_PER) = 0x3BC;
  ( * AT91C_PMC_PCER) = (1 << 14);
  ( * AT91C_PMC_PCER) = (1 << 13);
  ( * AT91C_PIOC_PPUDR) = 0x3BC;
  ( * AT91C_PIOC_PPUDR) = 0x4;
  ( * AT91C_PIOC_ODR) = (15 << 2); //2-3-4-5 ROWS
  ( * AT91C_PIOD_OER) = 4; // PIN 27
  ( * AT91C_PIOC_OER) = (7 << 7); // 7-8-9 COLUMNS
  ( * AT91C_PIOC_SODR) = (7 << 7); //Set all Columns pin as high 
  ( * AT91C_PIOD_CODR) = (1 << 2);
}

int func() {
  int value = 0;

  * AT91C_PIOD_OER = (1 << 2);
  * AT91C_PIOC_OER = (7 << 7);
  * AT91C_PIOD_CODR = (1 << 2);
  * AT91C_PIOC_SODR = (7 << 7);
  * AT91C_PIOC_ODR = (15 << 2);
  for (int i = 0; i < 3; i++) {
    * AT91C_PIOC_CODR = (1 << (7 + i));
    for (int j = 0; j < 4; j++) {
      int k = 2 + j;
      if ((( * AT91C_PIOC_PDSR & (1 << k)) == 0)) {
        value = (j * 3) + (i + 1);
        * AT91C_PIOC_ODR = (7 << 7);
        if(value<10||value==11){
          if (value==11)
            value=0;
          return (value);
        }
      }
    }
    * AT91C_PIOC_SODR = (1 << (7 + i));
    if (i == 2){
     // i = -1;
    return -1;
    }
  }
  return value;
}

void set_Display() {
  ( * AT91C_PMC_PCER) = (1 << 13);
  ( * AT91C_PMC_PCER) = (1 << 14);
  ( * AT91C_PIOD_PER) = 0x1; //25  
  ( * AT91C_PIOC_PER) = 0xFF3FC; //34-51
  ( * AT91C_PIOC_PPUDR) = 0xFF3FC; //34-51
  ( * AT91C_PIOD_PPUDR) = 0x1; //25
  ( * AT91C_PIOC_OER) = (1 << 12);
  ( * AT91C_PIOC_OER) = (1 << 13);
  ( * AT91C_PIOD_OER) = 0x1; //25
  ( * AT91C_PIOC_OER) = (1 << 18);
  ( * AT91C_PIOC_OER) = (1 << 19);
  ( * AT91C_PIOC_SODR) = (1 << 18);
  ( * AT91C_PIOC_CODR) = (1 << 19);
}

void Init_Display(void) {
  * AT91C_PIOD_CODR = 1; // clear reset (pin 25)
  Delay(10);
  * AT91C_PIOD_SODR = 1; // set reset (pin 25)
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x40); //Set text home address
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x40);
  Write_Command_2_Display(0x42); //Set graphic home address
  Write_Data_2_Display(0x28);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x41); // Set text area
  Write_Data_2_Display(0x0);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x43); // Set graphic area
  Write_Command_2_Display(0x80); // text mode
  Write_Command_2_Display(0x94); // Text on graphic off 
}

void Write_Data_2_Display(unsigned char Data) {
  while ((Read_Status_Display() & (12)) != 12) {} //Wait until Read_Status_Display returns an OK
  * AT91C_PIOC_OER = 1020;
  * AT91C_PIOC_OER = (1020);
  * AT91C_PIOC_CODR = (1020); //Clear databus
  * AT91C_PIOC_SODR = (Data << 2); //Set Data to databus
  * AT91C_PIOC_CODR = (1 << 13); //DIR as output
  * AT91C_PIOC_CODR = (1 << 12); //Enable output (74chip)
  * AT91C_PIOC_OER = (1020); //Set databus as output
  * AT91C_PIOC_CODR = (1 << 14); //Clear C/D signal High (0 = Data)
  * AT91C_PIOC_CODR = (1 << 15); //Clear chip select display
  * AT91C_PIOC_CODR = (1 << 17); //Clear write display
  Delay(10); //Make a Delay
  * AT91C_PIOC_SODR = (1 << 15); //Set chip enable display
  * AT91C_PIOC_SODR = (1 << 17); //Set write display
  * AT91C_PIOC_SODR = (1 << 12); //Disable output (74chip)
  * AT91C_PIOC_ODR = (1020); //Make databus as input
}

void Write_Command_2_Display(unsigned char Command) {
  while ((Read_Status_Display() & (12)) != 12) {} //Wait until Read_Status_Display returns an OK
  * AT91C_PIOC_OER = (1020);
  * AT91C_PIOC_OER = (63 << 12);
  * AT91C_PIOC_CODR = (1020); //Clear databus
  * AT91C_PIOC_SODR = (Command << 2); //Set Command to databus 
  * AT91C_PIOC_CODR = (1 << 13); //Set 2dir as output (74chip)
  * AT91C_PIOC_CODR = (1 << 12); //Enable output (74chip)
  * AT91C_PIOC_OER = (1020); //Set databus as output
  * AT91C_PIOC_SODR = (1 << 14); //Set C/D signal High (1 = Command)
  * AT91C_PIOC_CODR = (1 << 15); //Clear chip select display
  * AT91C_PIOC_CODR = (1 << 17); //Clear write display
  Delay(10); //Make a Delay
  * AT91C_PIOC_SODR = (1 << 15); //Set chip enable display
  * AT91C_PIOC_SODR = (1 << 17); //Set write display
  * AT91C_PIOC_SODR = (1 << 12); //Disable output (74chip)
  * AT91C_PIOC_ODR = (1020); //Make databus as input
}

unsigned char Read_Status_Display(void) {
  unsigned char temp;
  * AT91C_PIOC_ODR = (1020);
  * AT91C_PIOC_OER = (3 << 12);
  * AT91C_PIOC_OER = (3 << 15);
  * AT91C_PIOC_SODR = (1 << 13); //DIR as input
  * AT91C_PIOC_CODR = (1 << 12); //OE =0
  * AT91C_PIOC_SODR = (1 << 14); //Set CD
  * AT91C_PIOC_CODR = (3 << 15); //Clear CE and RD
  Delay(10);
  temp = * AT91C_PIOC_PDSR & (12); //save datbus input on temp
  * AT91C_PIOC_SODR = (3 << 15); //Set CE and RD
  * AT91C_PIOC_SODR = (1 << 12); //OE =1
  * AT91C_PIOC_CODR = (1 << 13); //DIR as output
  return temp;
}

void clear_Display() {
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  for (int i = 0; i < (4000); i++) {
    Write_Data_2_Display(0x0);
    Write_Command_2_Display(0xC0);
  }
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
}