
#include "node.h"
#include <iostream>
#include <cassert>
using namespace std;

#ifndef LIST_H
#define LIST_H

// forward declaration of the ListIterator class
template <class T>
class ListIterator;

/*****************************************
 * LIST Class
 * ---------------------------------------
 * Stores data using a linked list
 * **************************************/
template <class T>
class List
{
public:
   // defaut constructor
   List() : pHead(NULL), pTail(NULL), numItems(0) { };
   // copy constructor
   List(const List & rhs);
   // deconstructor
   ~List() { if (pHead) freeData(pHead); }

   // assignment operator overload
   List <T> operator =(const List <T> & rhs);

   // is the List empty?
   bool empty() { return numItems == 0; }
   
   // clear the contents of the List
   void clear() { freeData(pHead); numItems = 0; pHead = pTail = NULL; }
   
   // what is the size of the List?
   int size() { return numItems; }
   
   // add an item to the back of the List
   void push_back(const T & data);                 
   
   // add an item to the front of the List
   void push_front(const T & data);
   
   // returns the first item in the List
   T & front() throw (const char *) { if (empty()) { throw "ERROR: unable to access data from an empty list"; }       
                                             else { return pHead->data; } }
   
   // returns the last item in the List
   T & back() throw (const char *) { if (empty()) { throw "ERROR: unable to access data from an empty list"; }       
                                             else { return pTail->data; } }
   
   // inserts an item into the List
   void insert(ListIterator <T> &in, const T & data);   
   
   // removes an item from the List
   void remove(ListIterator <T> &rem) throw (const char *);
   
   // pretty straightfoward
   ListIterator <T> begin() { return ListIterator <T> (this->pHead); }
   ListIterator <T> rbegin() { return ListIterator <T> (this->pTail); }
   ListIterator <T> end() { return ListIterator <T> (NULL); }
   ListIterator <T> rend() { return ListIterator <T> (NULL); }

private:
   Node <T> * pHead;
   Node <T> * pTail;
   int numItems;

};

/*******************************************
 * LIST ITERATOR Class
 * 
 * ****************************************/
template <class T>
class ListIterator
{
public:
   // default constructor
   ListIterator() : p(NULL) {}

   // copy constructor
   ListIterator(const ListIterator & rhs) { this->p = rhs.p; }

   // initialize to direct p to some item
   ListIterator(Node <T> * p) : p(p) {}

   // destructor
   ~ListIterator() { p = NULL; };

   // friend declaration of insert()
   friend void List<T> :: insert(ListIterator <T> &in, const T & data);
   // friend declaration of remove()
   friend void List <T> :: remove(ListIterator <T> &rem);

   // not equals operator
   bool operator != (const ListIterator <T> & rhs) const
   {
      return rhs.p != this->p;
   }

   // is equals operator
   bool operator == (const ListIterator <T> & rhs)
   {
      return (this->p == rhs.p);
   }

   // dereference operator
   T & operator * ()
   {
      return p->data;
   }

   // prefix increment
   ListIterator & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }

   // postfix increment
   ListIterator operator ++ (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pNext;
      return tmp;
   }
   
   // prefix decrement
   ListIterator & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix decrement
   ListIterator & operator -- (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pPrev;
   }
 
   // assignment operator
   ListIterator & operator = (const ListIterator <T> & lhs)
   {
      this->p = lhs.p;
   }
   
private:
   Node <T> * p;
};


/**********************************************
 * COPY CONSTRUCTOR
 * 
 * *******************************************/
template <class T>
List <T> :: List(const List & rhs)
{
   if (rhs.numItems == 0)
   {
      this->pHead = this->pTail = NULL;
      this->numItems = 0;
   }
   else
   {      
      this->pHead = copy(rhs.pHead);

      if (rhs.numItems == 1)
         this->pTail = this->pHead;
      else
      {
         for (Node <T> * p = this->pHead; p; p = p->pNext)
         {
            if (p->pNext == NULL)
            {
               this->pTail = p;
            }
         }
      }
      this->numItems = rhs.numItems;
   }
}

/*******************************************
 * PUSH BACK
 * -----------------------------------------
 * add an item to the back of the List
 * ****************************************/
template <class T>
void List <T> :: push_back(const T & data)
{
   Node <T> * temp; 
   try
   {
      temp = new Node <T> (data);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   if (numItems == 0)
   {
      pTail = temp;
      pHead = temp;
   }
   else
   {
      pTail->pNext = temp;
      temp->pPrev = pTail;
      pTail = temp;
   }

   numItems++;
}

/*******************************************
 * PUSH FRONT
 * -----------------------------------------
 * add an item to the front of the List
 * ****************************************/ 
template <class T>
void List <T> :: push_front(const T & data)
{
   Node <T> * temp; 
   try
   {
      temp = new Node <T> (data);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   if (numItems == 0)
   {
      pTail = temp;
      pHead = temp;
   }
   else
   {
      temp->pNext = pHead;
      pHead->pPrev = temp;
      pHead = temp;
   }

   numItems++;
}



/**********************************************
 * ASSIGNMENT OPERATOR =
 * *******************************************/
template <class T>
List <T> List <T> :: operator =(const List <T> & rhs)
{
   this->clear();
   if (rhs.numItems == 0)
   {
      this->pHead = this->pTail = NULL;
      this->numItems = 0;
   }
   else
   {      
      this->pHead = copy(rhs.pHead);

      if (rhs.numItems == 1)
         this->pTail = this->pHead;
      else
      {
         for (Node <T> * p = this->pHead; p; p = p->pNext)
         {
            if (p->pNext == NULL)
            {
               this->pTail = p;
            }
         }
      }
      this->numItems = rhs.numItems;
   }   
   return *this;
}


/**********************************************
 * INSERT
 * -------------------------------------------
 * Inserts before the pointer.
 * *******************************************/
template <class T>
void List <T> :: insert(ListIterator <T> &in, const T & data)
{   
   // create temp Node ptr
   Node <T> * temp; 
   try
   {
      temp = new Node <T> (data);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   // insert into empty list
   if (pHead == NULL && in != NULL)
   {
      pHead = temp;
      pTail = temp;
   }
   // insert at the end
   else if(in == end()) 
   {
      pTail->pNext = temp;
      temp->pPrev = pTail;
      pTail = temp;
   }
   // insert at beginning or middle
   else 
   {
      temp->pNext = in.p;
      temp->pPrev = in.p->pPrev;
      in.p->pPrev = temp;
      if (in.p == pHead) // insert at beginning
      {
         pHead = temp;
      }
      else
      {
         temp->pPrev->pNext = temp; // insert in middle
      }

   }

   numItems++;
}

/**********************************************
 * REMOVE
 * --------------------------------------------
 * Removes the item pointed to by ListIterator
 * rem.
 * *******************************************/
template <class T>
void List <T> :: remove(ListIterator <T> &rem) throw (const char *)
{
   // check to be sure it's valid
   if (rem == end())
      throw "ERROR: unable to remove from an invalid location in a list";
   // remove from beginning
   if (rem.p == pHead)
   {
      rem.p->pNext->pPrev = NULL;
      pHead = rem.p->pNext;
   }
   // remove from end
   else if (rem.p == pTail)
   {
      rem.p->pPrev->pNext = NULL;
      pTail = rem.p->pPrev;
   }
   // remove from middle
   else
   {
      rem.p->pPrev->pNext = rem.p->pNext;
      rem.p->pNext->pPrev = rem.p->pPrev;
   }

   numItems--;
   // delete the pointer!
   delete rem.p;
}


#endif // LIST_H