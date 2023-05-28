#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);


void bubble(int *a, int n)
{
    for(  int i = 0;  i < n;  i++ )
     {  	 
   	 int first = i % 2; 	 

   	 #pragma omp parallel for shared(a,first)
   	 for(  int j = first;  j < n-1;  j += 2  )
   	   {  	 
   		 if(  a[ j ]  >  a[ j+1 ]  )
   		  {  	 
     			 swap(  a[ j ],  a[ j+1 ]  );
   		  }  	 
   		   }  	 
     }
}


void swap(int &a, int &b)
{

    int test;
    test=a;
    a=b;
    b=test;

}

int main()
{

    int *a,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
   	 cin>>a[i];
    }
    
    bubble(a,n);
    
    cout<<"\n sorted array is=>";
    for(int i=0;i<n;i++)
    {
   	 cout<<a[i]<<endl;
    }


return 0;
}




/*
Bubble sort:
Bubble Sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. The algorithm gets its name from the way smaller elements "bubble" to the top of the list.
Here are the steps to perform the Bubble Sort algorithm:

Start with an unsorted list of elements.
Compare the first element with the second element. If the first element is greater than the second element, swap them.
Move to the next pair of elements (second and third), and repeat the comparison and swapping process.
Continue this process until the last two elements of the list are compared and swapped, if necessary.
Repeat steps 2 to 4 for the remaining passes until no more swaps are needed.
The list is now sorted.



In parallel Bubble Sort, the work is divided among multiple threads, allowing them to sort different portions of the array concurrently. Each thread performs its own local Bubble Sort on a subset of the array, reducing the overall execution time
The parallel Bubble Sort algorithm typically follows these steps:
The input array is divided into equal-sized or approximately equal-sized chunks, and each chunk is assigned to a separate thread.
Each thread performs the Bubble Sort algorithm independently on its assigned chunk of the array.
After completing the local sort, the threads synchronize to ensure that all elements are in the correct position within their respective chunks.
The sorted chunks are combined or merged to obtain a globally sorted array.
If the array is not fully sorted, the process is repeated until the array is completely sorted.


Algo:
Start with an unsorted array of elements.

Create a parallel region using the #pragma omp parallel directive to distribute the work among multiple threads.

Within the parallel region, initialize a flag sorted to track whether any swaps were made during a pass.

Continue iterating over the array until no more swaps are needed. Use a while loop with the #pragma omp barrier directive to synchronize the threads at the end of each pass.

Inside the loop, use a #pragma omp for directive to distribute the iterations of the outer loop among the threads. Each thread will independently perform a local Bubble Sort on its assigned chunk of the array.

Compare adjacent elements and swap them if necessary. Ensure that the swapping operation is performed within a #pragma omp critical section to avoid race conditions.

After each pass, set the sorted flag to true if no swaps were made by any thread. Use the #pragma omp barrier directive to synchronize the threads again before updating the sorted flag.

Once the sorting is complete, exit the parallel region.
time complexity of O(n^2) and a space complexity of O(1),

Applications:

Educational Purposes
Small Dataset Sorting
Partially Sorted Data
Online Algorithms: 
Algorithmic Analysis



he bubble() function implements the Bubble Sort algorithm. It takes an integer array a and the number of elements n as parameters.
The outer loop iterates n times, representing the number of passes required to sort the array.
Inside the outer loop, there is a variable first that determines whether the inner loop starts from an even or odd index. This is done to alternate the starting point of comparisons in each pass, which helps in parallelizing the sorting process using OpenMP.
The inner loop performs the comparisons and swaps adjacent elements if they are out of order. The loop starts from the first index and iterates with a step size of 2, ensuring that adjacent elements are compared.
The swap() function is a helper function that swaps the values of two integers using a temporary variable.
void bubble(int *, int):

This function implements the Bubble Sort algorithm using OpenMP for parallelization.
It takes two parameters: an integer pointer a representing the array and an integer n representing the number of elements in the array.
The function uses a nested loop structure to perform the sorting process.
The outer loop iterates n times, representing the number of passes required to sort the array.
Inside the outer loop, the variable first is calculated as i % 2. It determines whether the inner loop starts from an even or odd index. This helps in alternating the starting point of comparisons in each pass, which is important for parallelization using OpenMP.
The inner loop is parallelized using the #pragma omp parallel for directive. It performs the comparisons and swaps adjacent elements if they are out of order.
The loop starts from the first index and iterates with a step size of 2. This ensures that adjacent elements are compared.
The shared(a, first) clause specifies that the variables a and first are shared among the parallel threads.
Inside the inner loop, the elements at indices j and j+1 are compared, and if the element at index j is greater than the element at index j+1, the swap() function is called to swap their values.
After completing the inner loop, the next pass of the outer loop starts until all elements are sorted.
void swap(int &, int &) :

This function is a helper function used by the bubble() function to swap the values of two integers by reference.
It takes two integer references a and b as parameters.
The function uses a temporary variable test to store the value of a.
The value of a is then assigned the value of b, and the value of b is assigned the value stored in test.
As a result, the values of a and b are swapped.



*/

