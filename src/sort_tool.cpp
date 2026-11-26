// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
//  Modify     [2024/9/2 Meng-Chen Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); i++){
      int key = data[i];
      //insert data[i] into sorted sequence data[0:i-1]
      int j = i - 1;
      while (j >= 0 and data[j] > key){
        data[j+1] = data[j];
        j = j - 1; 
      }
      data[j+1] = key;

    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data,int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if(high > low){
      if(flag == 0){
        int q = Partition(data, low, high);//q:the highest index of the low side
        QuickSortSubVector(data, low, q, 0);
        QuickSortSubVector(data, q+1, high, 0);
        
      }
      else if(flag == 1){
        int q =  RandomizedPartition(data, low, high);//q:the highest index of the low side
        QuickSortSubVector(data, low, q, 1);
        QuickSortSubVector(data, q+1, high, 1);
      }
    }
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int mid = low + (high - low) / 2;
    int a = data[low], b = data[mid], c = data[high];
    int pivot = data[low + rand() % (high - low + 1)];
    int i = low - 1;
    int j = high + 1;
    while(true){
        do {j = j - 1;} while (data[j] > pivot);
        do {i = i + 1;} while (data[i] < pivot);
        if (i < j){//swaping
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
        else{
            return j;
        }
    }
}
int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int mid = low + (high - low) / 2;
    int a = data[low], b = data[mid], c = data[high];
    int pivot = std::min(std::max(a,b), std::max(std::min(a,b),c));
    int i = low - 1;
    int j = high + 1;
    while(true){
        do {j = j - 1;} while (data[j] > pivot);
        do {i = i + 1;} while (data[i] < pivot);
        if (i < j){//swaping
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
        else{
            return j;
        }
    }
    
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    if (data.empty()) return;
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (high - low >= 1){
        int middle1 =  (high + low) / 2;
        int middle2 = middle1 + 1;

        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);

    }

    
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIndex = low; // index into left subvector              
    int rightIndex = middle2; // index into right subvector         
    int combinedIndex = 0; // index into temporary working vector
    
    vector< int > combined; // working vector 
    combined.resize(high - low + 1);
    while ( leftIndex <= middle1 && rightIndex <= high )
    {
      // place smaller of two current elements into result
      // and move to next space in vector
      //???
      if(data[leftIndex] <= data[rightIndex]){
         combined[combinedIndex++] = data[leftIndex++];
         
      }
      else{
        combined[combinedIndex++] = data[rightIndex++];
        
      }

    } // end while
  
  if ( leftIndex == middle2 ) // if at end of left vector          
    {                                                               
      // copy in rest of right vector
      //???
      while (rightIndex <= high) {
        combined[combinedIndex++] = data[rightIndex++];
    }
    } // end if                                                     
  else // at end of right vector                                   
    {                                                               
       // copy in rest of left vector
      //???
      while (leftIndex <= middle1) {
        combined[combinedIndex++] = data[leftIndex++];
    }
    } // end else
    for (int i = 0; i < combined.size(); ++i) {
      data[low + i] = combined[i];
}

}

// bottom-up style implementation of merge sort
void SortTool::BottomUpMergeSort(vector<int>& data) 
{
  /*TODO :
    Implement merge sort in bottom-up style, in other words,
    without recursive function calls.
    Hint: 
    1. Divide data to n groups of one data each group
    2. Iteratively merge each pair of 2 neighbor groups into one larger group
    3. Finally we obtain exactly one sorted group
  */
  int n = data.size();
  int groupMem = 1;
  while (groupMem < n ){
    int i = 0;
    while(i + groupMem < n ){ // case 1: a and b both in length groupMem //case 2: a is in length groupMem while b is not //case 3: a.size() <= groupMem (won't go into this loop because a is already sorted)
        int leftIndex = i;
        int midIndex = i + groupMem;
        int rightIndex = std::min(i + 2 * groupMem , n);
        vector<int> a(data.begin()+leftIndex, data.begin()+midIndex);
        vector<int> b(data.begin()+midIndex, data.begin()+rightIndex );
        vector<int> c;
        c.reserve(a.size() + b.size());
        int indexOfa = 0;
        int indexOfb = 0;
        while(indexOfa < a.size() and indexOfb < b.size()){ // a 0 1 2 size 3 
            if (a[indexOfa] <= b[indexOfb]){
                c.push_back(a[indexOfa]);
                indexOfa += 1;
            }
            else{
                c.push_back(b[indexOfb]);
                indexOfb += 1;
            }
        }
        if(indexOfa == a.size()){
           while(indexOfb < b.size()){
            c.push_back(b[indexOfb]);
            indexOfb += 1;
           }
        }
        if(indexOfb == b.size()){
            while(indexOfa < a.size()){
             c.push_back(a[indexOfa]);
             indexOfa += 1;
            }
        }
        for (int j = 0; j < c.size(); j++ ){
            data[i + j] = c[j];
        }
        i = i + groupMem * 2; 
    }
    groupMem = groupMem * 2;
  }
   
}

// Heap sort method, be aware that you are NOT required to implement heap sort in PA1
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
}
