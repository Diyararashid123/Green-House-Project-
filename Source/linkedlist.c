#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"


int controll=1;


void insertFirst(struct LinkedList **first, LinkedList *el) {
if(controll==0)
  *first=NULL;
  el->next = *first;
  *first = el;
  controll=1;
}

int isMember(struct LinkedList **first, LinkedList *el) {
  LinkedList *temp=NULL;

  for (temp = *first; temp != NULL; temp = temp->next) {
    if (el == temp)

      return 1;
  }
  return 0;
}





void removeEl(LinkedList **first, LinkedList *el) {
  
  LinkedList *temp=NULL;
  temp = *first;
    LinkedList *n=NULL;
  n = *first;
  if(n==NULL){
    printf("%s\n","Trying to remove from empty list");
  }
    
  

  if (isMember(first, el) == 1) {

     if (temp->next == NULL && n == el) {
       
    *first = NULL;
       
    return;
  }
   
     if(temp==el) {
   
       temp=temp->next;
      *first=temp;
    
  }
    
      
    while(temp->next != NULL){
       
       n= temp->next;
        if(n==el){
          if(n->next==NULL){
            temp->next=NULL;
            return;
          }
          
          temp->next=n->next;
          n=temp->next;
        }
      temp = n;
      }
    }

 }
  
LinkedList *readSensor(int y,int m,int d, int h, int min, int t,LinkedList **a) {
  LinkedList *temp=NULL;
  temp = (LinkedList *)malloc(sizeof(LinkedList));
    if (temp == NULL) {
  removelast(a);
    temp = (LinkedList *)malloc(sizeof(LinkedList));
    
 
  }
  temp->day=d;
  temp->minute=min;
  temp->hour=h;
  temp->month=m;
  temp->year=y;
  
 temp->temp = t;
  return temp;
}

void printList(LinkedList *first) {
  LinkedList *a=first;

  
if(a==NULL||controll==0){
    printf("%s\n","Trying to print empty list");
  return;
  }
  
  for (a = first; a != NULL; a = a->next)
    
    printf("%i  %i %i\n ", a->hour, a->minute, a->temp);
}



//---------------------------_____________

LinkedList* selectionSort(LinkedList* first)
{
    LinkedList *prev, *current, *beforetest, *test, *temp1=NULL;
  
    prev = current = first;
  if(prev==NULL){
    printf("%s\n","Trying to sort empty list");
    return(NULL);
  }
    // While current is not the last element
    while (current->next) {
  
        beforetest = test = current->next;
  
        // While test is not null
        while (test) {
  
            if (current->day > test->day) {
              
                // If current and test is next to eachother
               if (current->next == test) {
                 
                   //  current is first
                    if (current == first) {

                        // Move test  before current
                        current->next = test->next;
                        test->next = current;
  
                        // Swap current and test pointers
                        temp1 = current;
                        current = test;
                        test = temp1;
  
                        beforetest = test; 
                        first = current; 
                        
                        test = test->next;
                    }
  
                    //  current is not first
                    else { 
                        
                        current->next = test->next;
                        test->next = current;
                        prev->next = test;
  
                        // Swap pointers
                        temp1 = current;
                        current = test;
                        test = temp1;
  
                        beforetest = test;
  
                        test = test->next;
                    }
                }


                 
  
                // If current & test not next to eachother
                else {  
                    //current is first
                    if (current == first) {
  
                        // Swap current->next and test->next
                        temp1 = current->next;
                        current->next = test->next;
                        test->next = temp1;
                        beforetest->next = current;

                            
                     
                        // Swap pointers
                        temp1 = current;
                        current = test;
                        test = temp1;
  
                        beforetest = test;
                        test = test->next;
                        first = current;
                    }  
                      
                    // current is not first element
                    else {  
                        
                        temp1 = current->next;
                        current->next = test->next;
                        test->next = temp1;
                      
                        beforetest->next = current;
                        prev->next = test;
  
                        // Swap pointers 
                        temp1 = current;
                        current = test;
                        test = temp1;
                      
                        beforetest = test;                 
                        test = test->next;
                    }
                }
            }
            else {
                // already in order
                beforetest = test;
                test = test->next;
            }
        }  
        prev = current;
        current = current->next;
    }
  
   return (first);
}
void removelast(LinkedList **first) {
  LinkedList*temp=NULL;
  temp=*first;

          while(temp->next->next != NULL)
            temp = temp->next;
          LinkedList* lastNode = temp->next;
          temp->next = NULL;
          free(lastNode);
}


void Empty(LinkedList *first){
  controll=0;
  if(first!=NULL){
  LinkedList  *current=NULL;
  current=first;
  LinkedList *n = current;
  while(current->next != NULL){
    
    n = current->next;
     free(current);
    current = n;
  }
  free(current);
  
    }
  else
     printf("%s\n","List is already empty");
}
