/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   John Reiley
* Summary: 
*    The heap allows for efficient sorting of values (n log n)
*
************************************************************************/
#include <vector>
   
using namespace std;

// forward declaration for heap class
template<class T>
class Heap;

/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(vector<T> &data)
{
   // turn the vector into a heap
   Heap <T> toSort(data, data.size());

   // sort the heap!
   toSort.sort();

   data = toSort.getData();
}

/***************************************
 * ------------ HEAP CLASS -------------
 * ************************************/
template<class T>
class Heap
{
public:
   Heap(vector <T> data, int num);
   ~Heap() { };

   void percolateDown(int index);
   void sort();
   void swap(int i1, int i2);

   int getLeftIndex(int i) { return (i * 2); }
   int getRightIndex(int i) { return (getLeftIndex(i) + 1); }
   vector <T> getData() const { return data; }

private:
   vector <T> data;
   int num;

};


/***************************************
 * HEAP : Non-Default Constructor
 * -------------------------------------
 * Heapifies the passed in vector
 * ************************************/
template <class T>
Heap <T> :: Heap(vector<T> data, int num)
{
   this->num = num;

   // copy the vector
   this->data = data;

   // heapify
   for (int r = num / 2; r >= 0; r--) // r represents the last non-leaf node
   {
      // go through every node before the last parent
      percolateDown(r);
   }
}

/***************************************
 * HEAP : PERCOLATE DOWN
 * -------------------------------------
 * moves higher values up and lower
 * values down through the binary tree
 * ************************************/
template<class T>
void Heap <T> :: percolateDown(int index)
{
   // convert to slot index by adding one
   int slotIndex = index + 1;
   int indexLeft  = slotIndex * 2;
   int indexRight = indexLeft + 1; 
   
   // convert left and right slot index to normal index
   indexLeft--;
   indexRight--;

   // swap and percolate if right is larger than parent and is the larger of the children
   if (indexRight <= num - 1 && data[indexRight] > data[indexLeft] && data[indexRight] > data[index])
   {
      swap(index, indexRight);
      percolateDown(indexRight);
   }
   // swap and percolate if left is larger than parent
   else if (indexLeft <= num - 1 && data[indexLeft] > data[index])
   {
      swap(index, indexLeft);
      percolateDown(indexLeft);
   }
}

/***************************************
 * HEAP : SORT
 * -------------------------------------
 * this does the actual heap sort
 * ************************************/
template <class T>
void Heap <T> :: sort()
{
   while (num > 0)
   {
      swap(0, num - 1);
      num--;
      percolateDown(0);
   }
}

/***************************************
 * HEAP : SWAP
 * -------------------------------------
 * swaps the values of the given indexes
 * (i1 and i2)
 * ************************************/
template <class T>
void Heap <T> :: swap(int i1, int i2)
{
   T var1 = data[i1];
   data[i1] = data[i2];
   data[i2] = var1;
}
