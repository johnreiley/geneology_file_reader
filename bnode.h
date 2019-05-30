#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>
using namespace std;

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
   // Default Constructor
   BinaryNode() : data(T()), pLeft(NULL), pRight(NULL), pParent(NULL) { };
   // Non-Default Constructor
   BinaryNode(T data) : pLeft(NULL), pRight(NULL), pParent(NULL) { this->data = data; }

   // return size (i.e. number of nodes in tree)
   int size() const
   {
      return 1 +
         (pLeft== NULL? 0 : pLeft->size()) +
         (pRight == NULL ? 0 : pRight->size());
   }
   
   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
};

/************************************************
 * BinaryNode :: ADD LEFT
 * Perameters: 
 * pNode - a new node to be inserted into the 
 *         binary tree
 * ----------------------------------------------
 * Adds a node to the left child of a node in the
 * binary tree.
 * *********************************************/
template <class T>
void BinaryNode <T> :: addLeft (BinaryNode <T> * pNode)
{
   if (pNode == NULL)
      this->pLeft = pNode;
   else
   {
      pNode->pParent = this;
      this->pLeft = pNode;
   }
   
}

/************************************************
 * BinaryNode :: ADD RIGHT
 * Perameters: 
 * pNode - a new node to be inserted into the 
 *         binary tree
 * ----------------------------------------------
 * Adds a node to the right child of a node in 
 * the binary tree.
 * *********************************************/
template <class T>
void BinaryNode <T> :: addRight(BinaryNode <T> * pNode)
{
   if (pNode == NULL)
      this->pRight = pNode;
   else
   {
      pNode->pParent = this;
      this->pRight = pNode;
   }
}


/************************************************
 * BinaryNode :: ADD LEFT
 * 
 * *********************************************/
template <class T>
void BinaryNode <T> :: addLeft (const T & t) throw (const char *)
{
   BinaryNode * newBNode;
   
   try
   {
      // allocate a new node!
      newBNode = new BinaryNode(t);
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   // do the magic
   newBNode->pParent = this;
   this->pLeft = newBNode;
}

/************************************************
 * BinaryNode :: ADD RIGHT
 * 
 * *********************************************/
template <class T>
void BinaryNode <T> :: addRight(const T & t) throw (const char *)
{
   BinaryNode * newBNode;
   
   try
   {
      newBNode = new BinaryNode(t);
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   // do the magic
   newBNode->pParent = this;
   this->pRight = newBNode;
}

// ----- NON-MEMBER FUNCTIONS ----- //

/************************************************
 * DELETE BINARY TREE
 * Parameters: 
 * bNode - the root of the tree to be deleted
 * *********************************************/
template <class T>
void deleteBinaryTree (BinaryNode <T> * &pNode)
{
   if (pNode == NULL)
      return;
   deleteBinaryTree(pNode->pLeft);
   deleteBinaryTree(pNode->pRight);
   delete pNode;
}


/************************************************
 * INSERTION OPERATOR <<
 * ----------------------------------------------
 * Displays the Binary Tree in infix order (LVR)
 * *********************************************/
template <class T>
ostream & operator <<(ostream & out, const BinaryNode <T> * rhs)
{

   if (rhs == NULL)
      return out;
   
   cout << rhs->pLeft;
   out << rhs->data << " ";
   cout << rhs->pRight;

}

#endif // BNODE_H
