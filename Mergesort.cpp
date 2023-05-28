#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;


void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

void mergesort(int a[],int i,int j)
{
	int mid;
	if(i<j)
	{
    	mid=(i+j)/2;
   	 
    	#pragma omp parallel sections
    	{

        	#pragma omp section
        	{
            	mergesort(a,i,mid);   	 
        	}

        	#pragma omp section
        	{
            	mergesort(a,mid+1,j);    
        	}
    	}

    	merge(a,i,mid,mid+1,j);    
	}

}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
	int temp[1000];    
	int i,j,k;
	i=i1;    
	j=i2;    
	k=0;
    
	while(i<=j1 && j<=j2)    
	{
    	if(a[i]<a[j])
    	{
        	temp[k++]=a[i++];
    	}
    	else
    	{
        	temp[k++]=a[j++];
    }    
	}
    
	while(i<=j1)    
	{
    	temp[k++]=a[i++];
	}
   	 
	while(j<=j2)    
	{
    	temp[k++]=a[j++];
	}
   	 
	for(i=i1,j=0;i<=j2;i++,j++)
	{
    	a[i]=temp[j];
	}    
}


int main()
{
	int *a,n,i;
	cout<<"\n enter total no of elements=>";
	cin>>n;
	a= new int[n];

	cout<<"\n enter elements=>";
	for(i=0;i<n;i++)
	{
    	cin>>a[i];
	}
   //	 start=.......
//#pragma omp…..
	mergesort(a, 0, n-1);
//          stop…….
	cout<<"\n sorted array is=>";
	for(i=0;i<n;i++)
	{
    	cout<<"\n"<<a[i];
	}
  	// Cout<<Stop-Start
	return 0;
}



/*


Merge Sort is a popular divide-and-conquer sorting algorithm that follows the following steps:
Divide the unsorted array into two halves: This is done by finding the middle index of the array.
Recursively sort the two halves: Apply Merge Sort on the left and right halves of the array separately until each subarray contains only one element or is empty.
Merge the sorted subarrays: Merge the two sorted subarrays obtained from the previous step to create a single sorted array. This is done by comparing the elements from the two subarrays and placing them in the correct order in a temporary array.
Copy the merged array back to the original array: Copy the elements from the temporary array back to the original array to obtain the sorted result.

Parallel Merge Sort is an extension of the traditional Merge Sort algorithm that leverages parallelism to improve performance on multi-core or multi-processor systems. It divides the sorting task among multiple threads or processes, allowing for concurrent execution and faster sorting times

Algo:
Sort, the array is divided into smaller subarrays, each assigned to a different thread or process.
Recursively sort the subarrays: Each thread or process applies Merge Sort independently on its assigned subarray until each subarray contains only one element or is empty.
Merge the sorted subarrays in parallel: Once the subarrays are sorted individually, a parallel merge operation is performed to combine the subarrays and create a single sorted array.
The merge operation can be implemented using parallelization techniques such as OpenMP or MPI.
Threads or processes work together to merge adjacent subarrays in parallel, reducing the overall merging time.
Repeat the merge operation until a single sorted array is obtained: If there are multiple levels of merging required, the process is repeated recursively until a single sorted array is achieved.


Divide the array among threads: Use the #pragma omp parallel directive to create a parallel region and distribute the sorting task among multiple threads.
Determine the thread's assigned range: Within the parallel region, use OpenMP's #pragma omp for directive to divide the array indices among threads. Each thread will work on its assigned range.
Sort the subarrays independently: Each thread independently sorts its assigned subarray using a sequential sorting algorithm like Merge Sort, Quick Sort, or Insertion Sort. This step is performed in parallel by multiple threads.
Synchronize the threads: Use the #pragma omp barrier directive to ensure that all threads have completed their sorting tasks before proceeding to the merging step. This synchronizes the threads.
Merge the sorted subarrays: Perform parallel merging of subarrays using one of the merging algorithms such as K-way merge or recursive doubling. This step combines the sorted subarrays from different threads into a single sorted array.
Repeat merging until a single sorted array is obtained: If there are multiple levels of merging required, repeat the merging process recursively until a single sorted array is achieved.

Time Complexity:
Best case: O(n log n)

Overall space complexity: O(n)

Educational purposes:
Small-sized arrays: 
Early termination: 
Integration with other algorithms
Sorting.
External sorting
Inversion count
Parallel algorithms
External merging

Code explanation:

The necessary header files are included: iostream, cstdlib, and omp.h.

The mergesort() function is defined to perform the merge sort algorithm. It takes an array a, the starting index i, and the ending index j as parameters.

In the mergesort() function, if the starting index i is less than the ending index j, the function proceeds to divide the array into two halves and recursively calls mergesort() on each half.

The OpenMP directive #pragma omp parallel sections is used to parallelize the recursive calls. The code within the parallel sections block is executed by multiple threads in parallel.

Within the parallel sections block, the first section executes mergesort() on the first half of the array (a[i] to a[mid]), and the second section executes mergesort() on the second half of the array (a[mid+1] to a[j]).

After the recursive calls to mergesort(), the function merge() is called to merge the two sorted halves of the array. It takes the indices i1, j1, i2, j2 as parameters, which define the range of the two halves.

The merge() function merges the two halves by comparing the elements from each half and storing them in a temporary array temp[]. The i and j variables track the current positions in each half, and the k variable tracks the position in the temp[] array.

The merged elements are then copied back to the original array a[].

In the main() function, the user is prompted to enter the total number of elements n and the elements of the array.

The mergesort() function is called with the array a[], starting index 0, and ending index n-1 to perform the parallel merge sort.

After the merge sort is completed, the sorted array is printed.




*/