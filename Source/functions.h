#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


//--------------------------LinkedList----------------------------------------------------------------------



typedef struct LinkedList {
  int temp;
  int second,minute,hour,day,month,year;
  struct LinkedList *next;
} 
LinkedList;


void insertFirst(struct LinkedList **first, LinkedList *el);


int isMember(struct LinkedList **first, LinkedList *el);


void removelast(LinkedList **first);



void removeEl(struct LinkedList **first, LinkedList *el);


LinkedList *readSensor(int y,int m,int d, int h, int min, int t,LinkedList **a);

void printList(LinkedList *first);


LinkedList* selectionSort(struct LinkedList* first);


void Empty(struct LinkedList *first);


//--------------------END OF LinkedList--------------------------------------------------------


//------------------------Project-------------------------------------------------------------
int func();
//keypad function
//returns (0-9)

void Delay();
//A delay using asembly

void set_KeyPad();
//setup for the keaypad

void set_Display();
//setup display

void Init_Display();
//setup display

void Write_Data_2_Display(unsigned char Data);
//write data to display

void Write_Command_2_Display(unsigned char Command);
//write comand to display

unsigned char Read_Status_Display(void);
//check if display is ready

void Init_Temp(void);
//setup tempsensor

void TC0_Handler(void);
//handles interrupts for temp measurement

void Init_Light(void);
//setup lightsensors

void Temp_Mesurement(void);
// setup for Read_Temp

void Movment_Servo(int degree);
//move servo to the degree

void Init_PWM_Servo(void);
//init the servo

void set_tempscreen(void);
//writes all the information of the temperaturescreen exept vallues and the date

void clear_Display();
//clears all the pages we use

void t_ime(void);
//the clock used for everything exept for the fast version of tracking the sun

double Light_Mesurment();
//measure the light with 2 lightsensors

void writeS(char c[]);
//writes the entire char[]

void write_Char(char c);
//writes the char c

void write_Date(void);
//writes the date(YYYY:MM:DD)

void write_Timestamp(int h, int m);
//writes a timestamp (HH:MM)

int Read_Temp(void);
//reads the temp and saves it in an int



void Green_House(void);
//function that tracks the temperature over seven days. 
//Keeps track of the timestamps and vallue for minimum, maximum and average temp of everyday.
//It also sets of an alarm if the temp is outside the allowed limits.

void set_Date(void);
//function that lets us use the keypad to decide the date and time

void menu(void);
//A switchcase that use the keypad to decide an option from the menu 

void set_menu(void);
//creates the graphical ui for the menu

void write_Time(void);
//writes the time HH:MM:SS


void PIOD_Handler(void);
//used for the button interrupts

void Set_Led(int x);
// x=1 means led is set to on, x=0 means led is set to off 


void resetTempscreen(void); 
// used to reset the screen used by sevenDays_temp so that we can use it again


void resetDatescreen(void); 
// used to reset the set_Date screen so that it can be used again


void resetLimitscreen(void);
// used to reset the set_Limits screen so that it can be used again



void set_Buttons(void); 
// enables the two buttons


void Write_Temp(int t); 
// writes an int between 00-99


void fastToggle(int i); 
// toggles fastmode(i=1) and normalmode(i=0)


void Write_light(double l); 
//writes a double






#endif