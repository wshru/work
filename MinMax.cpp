#include <iostream>
//#include <vector>
#include <omp.h>
#include <climits>
using namespace std;
void min_reduction(int arr[], int n) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] < min_value) {
  	min_value = arr[i];
	}
  }
  cout << "Minimum value: " << min_value << endl;
}

void max_reduction(int arr[], int n) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] > max_value) {
  	max_value = arr[i];
	}
  }
  cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(int arr[], int n) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < n; i++) {
	sum += arr[i];
  }
  cout << "Sum: " << sum << endl;
}

void average_reduction(int arr[], int n) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
	sum += arr[i];
  }
  cout << "Average: " << (double)sum / (n-1) << endl;
}

int main() {
    int *arr,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    arr=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
   	 cin>>arr[i];
    }

//   int arr[] = {5, 2, 9, 1, 7, 6, 8, 3, 4};
//   int n = size(arr);

  min_reduction(arr, n);
  max_reduction(arr, n);
  sum_reduction(arr, n);
  average_reduction(arr, n);
}





/*

OpenMP (Open Multi-Processing) is an API (Application Programming Interface) that supports parallel programming in shared-memory systems. It allows developers to write parallel programs using a combination of compiler directives, runtime library routines, and environment variables.
OpenMP is widely used for parallelizing computations in scientific and technical computing domains. It simplifies the process of writing parallel code by introducing pragmas, which are compiler directives that specify how to parallelize specific sections of code. The directives are written as comments in the code and provide hints to the compiler about the parallelism.

#pragma omp parallel: Specifies a parallel region where multiple threads are created to execute the enclosed code block in parallel.
#pragma omp for: Distributes the iterations of a loop among the available threads for parallel execution.
#pragma omp sections: Divides the code block into sections that can be executed in parallel by different threads.
#pragma omp single: Ensures that a particular code block is executed by a single thread only.
#pragma omp critical: Defines a critical section of code that can be executed by only one thread at a time.
#pragma omp barrier: Inserts a synchronization point, ensuring that all threads reach the barrier before any of them proceed.


Parallel reduction is a common technique used in parallel computing to perform a collective computation that combines values from multiple threads or processes into a single result. The goal of parallel reduction is to efficiently compute an aggregate value, such as the sum, product, maximum, minimum, or average, across a large dataset or a set of intermediate values.

Ad: load blancing, improved performance, flexibility, scalibilty

Input: A dataset of elements data and the size of the dataset n.
Output: The minimum (min), maximum (max), sum (sum), and average (average) of the elements in data.
Min Operation:

Initialize min to a large value (e.g., positive infinity).
Divide the dataset data among the available threads.
Each thread finds the minimum element in its assigned portion of the data.
Perform a parallel reduction by comparing the minimum values from each thread and updating min with the smallest value.
The final value of min represents the minimum element in the dataset.
Max Operation:

Initialize max to a small value (e.g., negative infinity).
Divide the dataset data among the available threads.
Each thread finds the maximum element in its assigned portion of the data.
Perform a parallel reduction by comparing the maximum values from each thread and updating max with the largest value.
The final value of max represents the maximum element in the dataset.
Sum Operation:

Initialize sum to zero.
Divide the dataset data among the available threads.
Each thread calculates the sum of its assigned portion of the data.
Perform a parallel reduction by adding the partial sums from each thread to the overall sum.
The final value of sum represents the sum of all elements in the dataset.
Average Operation:

Calculate the sum of the elements using the steps mentioned above.
Divide the sum by the size of the dataset (n) to compute the average (average).

The necessary header files are included: iostream, omp.h, and climits.

The min_reduction() function takes an array arr and its size n as parameters. It uses the OpenMP directive #pragma omp parallel for reduction(min: min_value) to parallelize the loop and perform the reduction operation. The min reduction specifies that the minimum value among the threads' local minimum values should be computed. Within the loop, each thread compares its local minimum value min_value with the element arr[i] and updates min_value if arr[i] is smaller.

The max_reduction() function is similar to min_reduction() but performs a reduction to find the maximum value in the array.

The sum_reduction() function calculates the sum of all elements in the array using the reduction operation #pragma omp parallel for reduction(+: sum). Each thread computes a local sum by adding arr[i] to its local sum, and the final reduction operation adds up all the local sums.

The average_reduction() function calculates the average of all elements in the array using the same reduction operation as sum_reduction(). After calculating the sum, the average is computed by dividing the sum by (n-1).

In the main() function, the user is prompted to enter the total number of elements n and the elements of the array.

The min_reduction(), max_reduction(), sum_reduction(), and average_reduction() functions are called with the array and its size as arguments to perform the respective reduction operations.

The program ends with a return statement.


The line #include <climits> is a preprocessor directive that includes the standard C++ library header file <climits>. This header file provides constants with the limits of integral types.

By including <climits>, you gain access to various constants defined in the header that represent the limits of different integral types, such as INT_MAX and INT_MIN for the maximum and minimum values of int, respectively.



*/
