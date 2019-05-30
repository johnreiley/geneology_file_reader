/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Br. Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,
 *                                   but left BST Iterator class.
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack

// forward declaration for the BST iterator
template <class T>
class BSTIterator;


/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   // constructor
   BST(): root(NULL){};
   
   // copy constructor
   BST(const BST <T> & rhs);    
   
   ~BST();

   int  size() const  { return empty() ? 0 : root->size(); }   // BinaryNode class needs a size function
   
   
   // determine if the tree is empty
   bool empty() const
   {
      if (root == NULL)
         return true;
      else
         return false;
   }

   // remove all the nodes from the tree.  Makes an empty tree.
   void clear()
   {
      // use LRV traversal (delete the bottom-most nodes starting from the left side)
      BSTIterator <T> it = NULL;
      removeLRV(root, it);

      root = NULL;
   }
   // called by the clear function
   void removeLRV(BinaryNode <T> * bNode, BSTIterator <T> & it)
   {
      if (bNode == NULL)
         return;

      removeLRV(bNode->pLeft, it);
      removeLRV(bNode->pRight, it);
      it = bNode;
      remove(it);
   }


   // overloaded assignment operator
   BST & operator = (const BST & rhs) throw (const char *)
   {
      if (rhs.root == NULL)
         this->root = NULL;
      else
         this->root = copyBTree(rhs.root);
      
      return *this;
   }
   // called by the assignment operator
   BinaryNode <T> * copyBTree(const BinaryNode <T> * bNode) throw (const char *)
   {
      if (bNode == NULL)
         return NULL;
      
      BinaryNode <T> * destination;
      try
      {
         destination = new BinaryNode <T> (bNode->data);
      } 
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }

      destination->pLeft = copyBTree(bNode->pLeft);
      if (destination->pLeft != NULL)
         destination->pLeft->pParent = destination;
      
      destination->pRight = copyBTree(bNode->pRight);
      if (destination->pRight != NULL)
         destination->pRight->pParent = destination;

      return destination;
   }

      
   // insert an item
   void insert(const T & t) throw (const char * );

   // remove an item
   void remove(BSTIterator <T> & it);

   // find a given item
   BSTIterator <T> find(const T & t);

   // the usual iterator stuff
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
   
private:

   BinaryNode <T> * root;
};

/*********************************************************
* copy constructor
**********************************************************/
template <class T>
BST<T>::BST(const BST <T> &rhs)
{
   if (rhs.root == NULL)
   {
      //this->clear();
      this->root = NULL;
   }
   else
      this->root = copyBTree(rhs.root);
}

/*****************************************************
* Destructor
*******************************************************/
template <class T>
BST<T>::~BST()
{
   // delete the tree by calling clear
   this->clear();
}


/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return BSTIterator<T>(nodes);   
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return BSTIterator<T>(nodes);
}  

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   // allocate a new BinaryNode with value of t
   BinaryNode <T> * newBNode;
   try
   {
      newBNode = new BinaryNode <T> (t);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   // first check if the tree empty
   if (root == NULL)
   {
      // if it's empty, set root to newNode
      this->root = newBNode;
   }
   else
   {
      // pointer from root
      BinaryNode <T> * pBNode = this->root;
      bool found = false;

      // traverse until insert spot is found
      while (pBNode != NULL && !found)
      {

         // gonna take a left 
         if (t <= pBNode->data)
         {
            if (pBNode->pLeft != NULL)
               pBNode = pBNode->pLeft;
            
            // we've found the spot!
            else 
            {
               found = true;
               pBNode->pLeft = newBNode;
               newBNode->pParent = pBNode;
            }
         }
         // gonna take a right
         else if (t > pBNode->data)
         {
            if (pBNode->pRight != NULL)
               pBNode = pBNode->pRight;
            
            // we've found the spot!
            else
            {
               found = true;
               pBNode->pRight = newBNode;
               newBNode->pParent = pBNode;
            }
         }
      }
   }
}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
   // get the bnode from the iterator
   BinaryNode <T> * temp = it.getNode();
   
   bool isRoot; // tells us if the bnode is the root
   if (temp->pParent == NULL)
      isRoot = true;
   else
      isRoot = false;

   if (temp == NULL)
   {
      return;
   }
   else if (!isRoot) // it has 0, 1 or 2 children and isn't the root
   {      
      bool isLeft; // tells us which side of the parent bnode is on
      if (temp->pParent->pLeft != NULL) 
      {  
         if (temp->pParent->pLeft->data == temp->data)
            isLeft = true; // the bnode is to the left of its parent
      }
      else
         isLeft = false; // the bnode is to the right of its parent

      if (temp->pLeft == NULL && temp->pRight == NULL) 
      {
         // it's a leaf   
         if (isLeft)
            temp->pParent->pLeft = NULL;
         else
            temp->pParent->pRight = NULL;

         delete temp;
         temp = NULL;
      }
      else if (temp->pLeft != NULL && temp->pRight == NULL) 
      {
         // bnode has 1 child on the left
         temp->pLeft->pParent = temp->pParent;
         if (isLeft) // bnode is on left side of parent
            temp->pParent->pLeft = temp->pLeft;
         else // bnode is on right side of parent
            temp->pParent->pRight = temp->pLeft;
         // get rid of that dude!
         delete temp;
         temp = NULL;
      }
      else if (temp->pLeft == NULL && temp->pRight != NULL) 
      {
         // bnode has 1 child on the right
         temp->pRight->pParent = temp->pParent;
         if (isLeft) // bnode is on the left side of parent
            temp->pParent->pLeft = temp->pRight;
         else // bnode is on the right side of parent
            temp->pParent->pRight = temp->pRight;
         // get rid of that dude!
         delete temp;
         temp = NULL;
      }
      else if (temp->pLeft != NULL && temp->pRight != NULL) 
      {
         // bnode has 2 children
         
         // look for the in-order successor
         BinaryNode <T> * succ = temp->pRight;
         while (succ->pLeft != NULL)
         {
            succ = succ->pLeft;
         }
         temp->data = succ->data;

         // create an iterator to point to succ and have it removed
         BSTIterator <T> it;
         it = succ;
         remove(it);
      }
   }
   else if (isRoot) // it's a root
   {
      if (temp->pLeft == NULL && temp->pRight == NULL) 
      {
         // it's a leaf   
         delete temp;
         temp = NULL;
      }
      else if (temp->pLeft != NULL && temp->pRight == NULL) 
      {
         // bnode has 1 child on the left
         temp->pLeft->pParent = NULL;
         root = temp->pLeft;
         // get rid of that dude!
         delete temp;
         temp = NULL;
      }
      else if (temp->pLeft == NULL && temp->pRight != NULL) 
      {
         // bnode has 1 child on the right
         temp->pRight->pParent = NULL;
         root = temp->pRight;
         // get rid of that dude!
         delete temp;
         temp = NULL;
      }
      else if (temp->pLeft != NULL && temp->pRight != NULL) 
      {
         // bnode has 2 children
         
         // look for the in-order successor
         BinaryNode <T> * succ = temp->pRight;
         while (succ->pLeft != NULL)
         {
            succ = succ->pLeft;
         }
         temp->data = succ->data;

         // create an iterator to point to succ and have it removed
         BSTIterator <T> it;
         it = succ;
         remove(it);
      }
   }
}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   BSTIterator <T> it = NULL;

   // first check if the tree empty
   if (root == NULL)
   {
      // if it's empty, return NULL iterator
      return it;
   }
   else
   {
      // pointer from root
      BinaryNode <T> * pBNode = root;
      bool found = false;

      // traverse until insert spot is found
      while (!found)
      {
         // gonna take a left
         if (t < pBNode->data && pBNode->pLeft != NULL)
         {
               pBNode = pBNode->pLeft;
         }
         // gonna take a right
         else if (t > pBNode->data && pBNode->pRight != NULL)
         {
            pBNode = pBNode->pRight;
         }
         else if (t == pBNode->data) // we've found the guy
         {
            // point the iterator it to the spot
            it = pBNode;
            return it;
         }
         else // there's no guy t!
         {
            // return a NULL iterator
            return it;
         }
      }
   }
}


/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()  
   {
      return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(BSTIterator <T> & it);

private:
   
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }
      
   return *this;      
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}


#endif // BST_H
