
#ifndef SORTINSERTION_h
#define SORTINSERTION_h

#include <iostream>
#include "node.h"
using namespace std;


/****************************************
* INSERTION SORT()
* Parameters: 
* array - an array
* num - the size of array
* --------------------------------------
* This function uses a linked-list to 
* sort an array
****************************************/ 
template <class T>
void sortInsertion(T array[], int num)
{
   Node <T> * sortedList = NULL;

   for (int i = 0; i < num; i++)
   {
      if (i == 0)
      {
         insert(array[i], sortedList);         
      }
      else
      {
         bool isInserted = false;
         Node <T> * p = sortedList;
         while (!isInserted)
         {
            if (array[i] > p->data)
            {
               if (p->pNext == NULL)
               {
                  insert(array[i], p);
                  isInserted = true;
               }
               else if (p->pNext != NULL)
               {
                  if (array[i] < p->pNext->data)
                  {
                     insert(array[i], p);
                     isInserted = true;
                  }
                  else if (array[i] > p->pNext->data)
                     p = p->pNext;
               }
            }
            else if (array[i] <= p->data)
            {
               sortedList = insert(array[i], p, true);
               isInserted = true;
            }
         }
      }
   }

   for (int i = 0; i < num; i++, sortedList = sortedList->pNext)
   {
      array[i] = sortedList->data;
   }

   return;
}



#endif // SORTINSERTION_H