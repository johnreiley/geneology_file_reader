/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a Vector: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the Vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Br. Helfrich
************************************************************************/

#ifndef Vector_H
#define Vector_H

#include <cassert>
#include <iostream>
using namespace std;

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (cap) delete [] data; }

   // operator=: copy data from one vector to another
   Vector & operator = (const Vector & rhs)
   {
      this->numItems = rhs.numItems;
      this->cap = rhs.cap;
      //int i = 0;

      try
      {
         delete [] data;
         data = new T[rhs.cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      for (int i = 0; i < this->cap; i++)
      {
         this->data[i] = rhs.data[i];
      }
   }

   //operator[]: returns a value from within the vector
   T & operator [] (int index)
   {
      if (index < 0 || index >= cap)
        throw false;
      return data[index];
   }

   //const operator[]: returns a value from within the vector
   T & operator [] (int index) const
   {
      if (index < 0 || index >= cap)
        throw false;
      return data[index];
   }

   // is the Vector currently empty?
   bool empty() const   { return numItems == 0;        }

   // remove all the items from the Vector
   void clear()         { numItems = 0;                }

   // how many items are currently in the Vector?
   int size() const     { return numItems;             }

   // how many items can the Vector hold?
   int capacity() const { return cap;                  }

   // add an item to the Vector
   void push_back(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
 VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
 VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Vector?
   int cap;           // how many items can I put on the Vector before full?
};

/**************************************************
 * Vector ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
 VectorIterator() : p(NULL) {}

   // copy constructor
 VectorIterator(const VectorIterator & rhs) { this->p = rhs.p; }

   // initialize to direct p to some item
 VectorIterator(T * p) : p(p) {}

   // destructor
 ~VectorIterator() { p = NULL; };

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

  // is equals operator
   bool operator == (const VectorIterator & lhs)
   {
      return (this->p == lhs.p);
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
 VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
 VectorIterator <T> operator++(int postfix)
   {
 VectorIterator tmp(*this);
      p++;
      return tmp;
   }
 
   // assignment operator
 VectorIterator & operator = (const VectorIterator & lhs)
 {
    this->p = lhs.p;
 }
   
  private:
   T * p;
};

/*******************************************
 * Vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T> Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = 0;
      numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/**********************************************
 * Vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Vector to "capacity"
 **********************************************/
template <class T> Vector <T> :: Vector(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the Vector by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}


/***************************************************
 * Vector :: INSERT
 * Insert an item on the end of the Vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{
   // is the capacity zero?
   if (cap == 0)
   {
      // increase capacity to 1
      ++cap;
      
      try
      {
         // reallocate
         data = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // insert value
      data[numItems++] = t;

   }
   // is there any space?
   else if (cap == numItems)
      
   {
      cap *= 2;
      T * temp;

      try
      {
         // create a temp array with new capacity
         temp = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // copy data to temp
      for (int i = 0; i < numItems; i++)
      {
         temp[i] = data[i];
      }

      try
      {
         // expand the capacity
         delete [] data;
         data = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      /*
      // transfer temp back to data
      for (int i = 0; i < numItems; i++)
      {
         data[i] = temp[i];
      }
      */

      // assign temp address to data
      data = temp;

      // add the new item
      data[numItems++] = t;
   }
   else
   {
      // add an item to the end
      data[numItems++] = t;
   }
}


#endif // Vector_H

