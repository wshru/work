#include<iostream>
#include<vector>
#include<omp.h>
#include<queue>
#include<bits/stdc++.h>
using namespace std;

queue<int>q;

void bfs(int start, int* arr, int n, int visit[])
{
	#pragma omp parallel for ordered
	for(int i=0; i<n; i++)
	{
		#pragma omp ordered
		if( ( *(arr + (n*start) + i)  == 1 ) && (visit[i] == 0) )
		{
			cout<<i<<" ";
			q.push(i);
			visit[i] = 1;
		}
	}

	q.pop();

	if(!q.empty()) bfs(q.front(), (int*)arr, n, visit);
	
}

int main()
{

	//freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

	//cout<<"BFS 0 1 2 3 4 5 6"<<endl;
    cout<<"Enter the number of vertices: ";
    int n;
    cin>>n;

    int arr[n][n] = {0};

    cout<<"Enter the number of edges: ";
    int edges;
    cin>>edges;

    for(int j=0; j<edges; j++)
    {
        int a, b;
        cout<<"Enter the two edges:"<<endl;
        cin>>a>>b;
        arr[a][b] = 1;
		arr[b][a] = 1;
    }

	int visit[n] = {0};

    cout<<"Enter the start vertex: ";
    int start;
    cin>>start;
	
	
	clock_t strt = clock();

	visit[start] = 1;
	cout<<start<<" ";
	q.push(start);

	bfs(start, (int*)arr, n, visit);

    clock_t stop = clock();

	cout<<"\nTime required : "<<(double)(stop-strt)<<" ms"<<endl;

    return 0;
}

/*

"Parallel Execution"
PS D:\C++> g++ -fopenmp parallel_bfs.cpp
PS D:\C++> ./a out
Enter the number of vertices: 7
Enter the number of edges: 6
Enter the two edges:
0 1
Enter the two edges:
0 2
Enter the two edges:
1 3
Enter the two edges:
1 4
Enter the two edges:
2 5
Enter the two edges:
2 6
Enter the start vertex: 0
0 1 2 3 4 5 6
Time required : 3 ms

"Serial Execution"
PS D:\C++> g++ parallel_bfs.cpp
PS D:\C++> ./a out
Enter the number of vertices: 7
Enter the number of edges: 6
Enter the two edges:
0 1
Enter the two edges:
0 2
Enter the two edges:
1 3
Enter the two edges:
1 4
Enter the two edges:
2 5
Enter the two edges:
2 6
Enter the start vertex: 0
0 1 2 3 4 5 6
Time required : 11 ms


BFS stands for Breadth-First Search. It is a graph traversal algorithm that explores all the vertices of a graph in breadth-first order, i.e., visiting all the vertices at the same level before moving on to the next level. BFS starts at a given vertex (often called the source vertex) and systematically explores its adjacent vertices before moving to the next level of vertices.
Here is the basic idea behind the BFS algorithm:
Start with a source vertex and enqueue it into a queue.
Mark the source vertex as visited.
While the queue is not empty, do the following:
Dequeue a vertex from the front of the queue.
Process the dequeued vertex (e.g., print it or perform some operation).
Enqueue all the unvisited neighbors of the dequeued vertex into the queue and mark them as visited.
Repeat steps 3 until the queue is empty.


Algo:
Parallelizing the BFS algorithm using OpenMP involves distributing the work across multiple threads to explore different parts of the graph concurrently. Each thread will handle a portion of the graph and contribute to the overall traversal.
Here's a high-level description of the parallel BFS algorithm using OpenMP:
Start with a source vertex and enqueue it into a shared queue.
Mark the source vertex as visited in a shared visited array or set.
Spawn a parallel region using #pragma omp parallel directive.
Within the parallel region, create private variables for each thread, including a private queue.
Each thread enters a loop using #pragma omp while directive and continues until the shared queue is empty.
Inside the loop, each thread dequeues a vertex from the shared queue using a critical section or atomic operation to ensure mutual exclusion.
If the dequeued vertex is not visited, mark it as visited in the shared visited array or set and process it.
Each thread explores the unvisited neighbors of its dequeued vertex and enqueues them into its private queue.
After all threads have finished exploring their respective vertices, combine the private queues into a shared queue using #pragma omp barrier to synchronize.
Repeat steps 6 to 9 until all vertices are processed.
Exit the parallel region.

Applications:
social n/w analysis
Web spiders
puzzle solving
graph traversal

O(V+E)
O(V)

Code explanation:
The code begins by including the necessary header files, such as iostream, vector, omp.h, queue, and bits/stdc++.h, which provide the required functionality for the program.

The bfs() function is defined to perform the breadth-first search traversal. It takes the starting vertex, adjacency matrix, number of vertices, and an array to keep track of visited vertices as input.

The parallel loop is defined using #pragma omp parallel for ordered. This pragma instructs the OpenMP compiler to parallelize the loop across multiple threads, allowing for concurrent execution of the loop iterations.

Inside the loop, the code checks for adjacent vertices of the current vertex. If an adjacent vertex is found and it has not been visited before (as indicated by visit[i] == 0), it is printed, enqueued in the q queue, and marked as visited by setting visit[i] = 1.

After processing all adjacent vertices, the q.pop() statement removes the front element from the queue, indicating that it has been processed.

If the queue is not empty, the bfs() function is recursively called with the front element of the queue as the new starting vertex. This ensures that all vertices in the connected component are traversed.

In the main() function, the user is prompted to enter the number of vertices (n) and the number of edges (edges).

An adjacency matrix arr of size n x n is created and initialized to all zeros.

The user is then prompted to enter the edges by providing two vertices at a time. For each edge, the corresponding elements in the adjacency matrix (arr[a][b] and arr[b][a]) are set to 1, indicating the existence of an edge between the two vertices.

An array visit of size n is initialized to all zeros. This array is used to keep track of visited vertices during the BFS traversal.

The user is asked to enter the starting vertex (start) for the BFS traversal.

The clock is started using clock() before initiating the BFS traversal. The starting vertex is marked as visited, printed, and enqueued in the q queue.

The bfs() function is called to perform the BFS traversal, passing the starting vertex, adjacency matrix, number of vertices, and the visit array.

After the BFS traversal is completed, the clock is stopped using clock() and the execution time is calculated as the difference between the stop and start times.

The execution time of the BFS traversal is printed


iostream: Provides input and output stream functionality.
vector: Implements dynamic arrays that can resize themselves.
omp.h: Contains OpenMP directives and functions for parallel programming.
queue: Implements a queue data structure for BFS traversal.
bits/stdc++.h: A convenience header that includes commonly used standard library headers.


*/