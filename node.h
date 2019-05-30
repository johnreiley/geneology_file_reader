#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;


/***********************************************
 * NODE Class
 * --------------------------------------------
 * This forms the fundamental building blocks
 * for making lists!
 * ********************************************/
template <class T>
class Node
{
   public:
      T data;
      Node <T> * pNext;
      Node <T> * pPrev;

      Node() : data(T()), pNext(NULL), pPrev(NULL) {}
      Node(T data) : pNext(NULL), pPrev(NULL) { this->data = data; }
      Node(T data, Node <T>* pNext, Node <T>* pPrev) { this->data  = data;
                                                       this->pNext = pNext;
                                                       this->pPrev = pPrev; }
};


/**********************************************
 * COPY()
 * Parameters:
 * pSource - pointer to head of a linked list
 * --------------------------------------------
 * Makes a copy of a linked list
 **********************************************/
template <class T>
Node <T>* copy(Node <T>* pSource) throw (const char*)
{
   Node <T> * pSrc;
   Node <T> * pDestination;
   Node <T> * pDest;
   try
   {
      pDestination = new Node <T> (pSource->data);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   
   pSrc = pSource;
   pDest = pDestination;

   for (pSrc = pSrc->pNext; pSrc; pSrc = pSrc->pNext)
   {
      pDest = insert(pSrc->data, pDest);
   }

   return pDestination;
}

/**********************************************
 * INSERT()
 * Parameters:
 * value - the value to be inserted
 * pNode - a pointer to the Node before the 
 *         new Node
 * front - if true, value is inserted in the 
 *         front of the linked list
 * --------------------------------------------
 * Inserts a value into a linked list.
 **********************************************/
template <class T>
Node <T> * insert(const T & value, Node <T> * &pNode, bool front = false)
             throw (const char*)
{  
   // create the new Node to be inserted with value
   Node <T> * newNode;
   try
   {
      newNode = new Node <T> (value);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   newNode->pNext = newNode->pPrev = NULL;
   
   if (front == true) // put the node at the front
   {  
      newNode->pNext = pNode;
      pNode->pPrev = newNode;
      pNode = newNode;
      return newNode;
   }
   else
   {
      if (pNode == NULL) // means there are no nodes yet
      {
         pNode = newNode;
         return pNode;
      }
      else if ( pNode->pNext == NULL) // put the node at the end
      {
         newNode->pPrev = pNode;
         pNode->pNext = newNode;
         return pNode->pNext;
      }
      else // put the node in the middle
      {
         newNode->pNext = pNode->pNext;
         newNode->pNext->pPrev = newNode;
         newNode->pPrev = pNode;
         pNode->pNext = newNode;
         return pNode->pNext;
      }
   }
}

/**********************************************
 * FIND()
 * Parameters:
 * head - pointer to head of a linked list
 * value - the value being searched for in the
 *         linked list
 * --------------------------------------------
 * Searches for a given value in a linked list.
 **********************************************/
template <class T>
Node <T>* find(Node <T> * head, const T & value)
{
   for (Node <T> * pHead = head; pHead != NULL; pHead = pHead->pNext)
   {
      if (pHead->data == value)
         return pHead;
   }   
   
   return NULL;
}

/**********************************************
 * Extraction Operator
 * --------------------------------------------
 * Displays the contents of a linked list
 **********************************************/
template <class T>
ostream & operator <<(ostream & out, Node <T> * rhs)
{
   for (Node <T> * display = rhs; display; display = display->pNext)
   {
      out << display->data;
      if (display->pNext != NULL)
         out << ", ";
   }
   return out;
}

/**********************************************
 * FREE DATA()
 * --------------------------------------------
 * Clears up memory allocated for the list
 **********************************************/
template <class T>
void freeData(Node <T> * &head)
{
   Node <T> * ptr = head;
   Node <T> * headPtr = head;

   if (head != NULL)
   {
      while (head->pNext != NULL)
      {
         ptr = head->pNext;
         delete head->pNext;
         head = ptr;
      }
      head = headPtr;
      delete head;
      head = NULL;
   }
}


#endif // NODE_H