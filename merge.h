/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   John Reiley 
* Summary: 
*
************************************************************************/
#include <list>
#include <cassert>
   
using namespace std;

template<class T>
int split(list<T> &data, list<T> &subF1, list<T> &subF2);
template<class T>
void merge(list<T> &data, list<T> &subF1, list<T> &subF2);

/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template<class T>
void mergeSort(list<T> &data)
{
   // create two subfiles as lists
   list <T> subF1;
   list <T> subF2;

   int subListNum = 3;
   
   // while loop until there is one sub list
   while (subListNum > 2) 
   {
      // call split to separtate the sublists
      subListNum = split(data, subF1, subF2);

      // call merge to combine the sublists
      merge(data, subF1, subF2);
   }

}

/**************************************************************
 * SPLIT
 * splits the file into 2 files by sublists
 * ***********************************************************/
template<class T>
int split(list<T> &data, list<T> &subF1, list<T> &subF2)
{
   typename list<T> :: iterator it;
   typename list<T> :: iterator itNext;
   int subListNum = 0;
   // determines which subfile to insert to
   bool insertSelect = 1;
   // for loop until end of data
   for (it = itNext = data.begin(); it != data.end(); it++)
   {
      // prevent incrementing a null iterator
      if (itNext != data.end())
         itNext++;

      if (insertSelect) // insert into subF2
         subF1.push_back(*it);
      else // insert into subF1
         subF2.push_back(*it);

      // check for next sublist
      if (*itNext < *it)
      {
         insertSelect = !insertSelect;
         subListNum++;
      }
   }

   return subListNum;
}


/**************************************************************
 * MERGE
 * merges the two files into one
 * ***********************************************************/
template<class T>
void merge(list<T> &data, list<T> &subF1, list<T> &subF2)
{
   typename list<T> :: iterator dataIt = data.begin();
   typename list<T> :: iterator f1It = subF1.begin();
   typename list<T> :: iterator f2It = subF2.begin();
   typename list<T> :: iterator f1ItPrev = subF1.begin();
   typename list<T> :: iterator f2ItPrev = subF2.begin();
   // keeps the previous iterators behind by one
   int count1 = 0;
   int count2 = 0;
   // tells which f-list to copy from
   int copySelect = 0;
   bool isNewSubList = false;

   while (dataIt != data.end())
   {
      // remove everything up to the new sub lists
      if (*f1It < *f1ItPrev && *f2It < *f2ItPrev)
      {
         
         while(f1It != subF1.begin())
         {
            subF1.pop_front();
         }
         count1 = 0;
         f1ItPrev = f1It;
         while(f2It != subF2.begin())
         {
            subF2.pop_front();
         }
         count2 = 0;
         f2ItPrev = f2It;
      }  

      // copy the rest of file A if B is done
      if (f1It == subF1.end())
         copySelect = 2;
      else if (f2It == subF2.end())
         copySelect = 1;

      // copy the rest of sublist from file A if B is at a new sublist
      else if (*f1It < *f1ItPrev && *f2It >= *f2ItPrev)
         copySelect = 2;
      else if (*f2It < *f2ItPrev && *f1It >= *f1ItPrev)
         copySelect = 1;

      // just compare the data of file A and B
      else if (*f1It <= *f2It)
         copySelect = 1;
      else if (*f2It <= *f1It)
         copySelect = 2;

      // copy and incriment the specified fIt
      if (copySelect == 1)
      {
         *dataIt = *f1It; 
         f1It++;
         if (count1 > 0)
            f1ItPrev++;
         count1++;
      }
      else if (copySelect == 2)
      {
         *dataIt = *f2It;
         f2It++;
         if (count2 > 0)
            f2ItPrev++;
         count2++;
      }
      dataIt++;      

   }
   subF1.clear();
   subF2.clear();
}

