/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include "vector.h"
#include "person.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(Vector <T> vector)
{
   BST <T> bst;
   int i = 0;
   for (i = 0; i < vector.size(); i++)
      bst.insert(vector[i]);

   i = 0;
   for (BSTIterator <T> it = bst.begin(); it != bst.end(); it++, i++)
   {
      vector[i] = *it;
   }
}

#endif // SORT_BINARY_H
