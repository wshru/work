#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void dfs(int start, int* arr, int n, int visited[]) {

    //#pragma omp parallel for ordered
    for(int i = 0; i < n; i++) {
        //#pragma omp ordered
        if( (*(arr + (start*n) + i) == 1) && (!visited[i]) )
        {
            visited[i] = 1;
            cout<<i<<" ";
            dfs(i, (int*)arr, n, visited);
        }
    }
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);

	cout<<"Enter the number of vertices:";
    int n;
    cin>>n;
	
    int arr[n][n] = {0};

    cout<<"Enter the number of edges:";
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

    int visited[n] = {0};

    cout<<"Enter the start vertex: ";
    int start;
    cin>>start;

    clock_t strt = clock();
    
    cout<<start<<" ";
    visited[start] = 1;
	dfs(start, (int *)arr, n, visited);
    
    clock_t stop = clock();

    cout<<"\nTime required : "<<(double)(stop-strt)<<" ms"<<endl;


    return 0;
}


/*

"Parallel Execution"
PS D:\C++> g++ -fopenmp parallel_dfs.cpp
PS D:\C++> ./a out
Enter the number of vertices:7 
Enter the number of edges:6
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
0 1 3 4 2 5 6
Time required : 9 ms

"Serial Execution"
PS D:\C++> g++ parallel_dfs.cpp
PS D:\C++> ./a out
Enter the number of vertices:7
Enter the number of edges:6
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
0 1 3 4 2 5 6
Time required : 12 ms


DFS (Depth-First Search) is a graph traversal algorithm that explores a graph by systematically visiting all the vertices in a depth-first manner. In DFS, the algorithm starts at a given vertex and explores as far as possible along each branch before backtracking.The algorithm starts at the root node (selecting some arbitrary node as the root node in the case of a graph) and explores as far as possible along each branch before backtracking. So the basic idea is to start from the root or any arbitrary node and mark the node and move to the adjacent unmarked node and continue this loop until there is no unmarked adjacent node. Then backtrack and check for other unmarked nodes and traverse them. Finally, print the nodes in the path
Here is the basic idea behind the DFS algorithm:
Start with a source vertex.
Mark the source vertex as visited.
Explore an unvisited neighbor of the current vertex.
If an unvisited neighbor is found, recursively apply steps 2 and 3, making the neighbor the new current vertex.
If no unvisited neighbor is found, backtrack to the previous vertex.
Repeat steps 3 to 5 until all vertices are visited.


Parallelizing the DFS algorithm using OpenMP involves dividing the work among multiple threads to explore different parts of the graph concurrently. Each thread will handle a portion of the graph and contribute to the overall traversal.

Here's a high-level description of the parallel DFS algorithm using OpenMP:

Start with a source vertex and mark it as visited.
Spawn a parallel region using #pragma omp parallel directive.
Within the parallel region, create private variables for each thread, including a private stack or other data structure to track the path.
Each thread enters a loop using #pragma omp while directive and continues until the shared stack is empty.
Inside the loop, each thread pops a vertex from the shared stack using a critical section or atomic operation to ensure mutual exclusion.
If the popped vertex is not visited, mark it as visited and process it.
Each thread explores the unvisited neighbors of its popped vertex and pushes them onto its private stack.
After all threads have finished exploring their respective vertices, combine the private stacks into the shared stack using #pragma omp barrier to synchronize.
Repeat steps 5 to 8 until all vertices are processed.
Exit the parallel region.


Applications:
Graph Traversal 
Maze Solving 
Topological Sorting
Detecting Cycles
Solving Puzzles
Decision Making
Backtracking

 
o(v+e) o(v)


The necessary header files are included: iostream, vector, stack, omp.h, and bits/stdc++.h.

The dfs() function is defined, which performs the depth-first search traversal. It takes the starting vertex, the adjacency matrix arr, the number of vertices n, and the visited array as parameters.

Inside the dfs() function, a parallel loop is commented out using #pragma omp parallel for ordered. This indicates that the loop can be parallelized across multiple threads for concurrent execution. However, in the provided code, the parallel loop is commented out, so the DFS is executed sequentially.

Within the loop, it checks if an adjacent vertex is unvisited (!visited[i]). If so, it marks it as visited, prints the vertex, and recursively calls dfs() for the unvisited vertex.

In the main() function, the user is prompted to enter the number of vertices and edges.

The adjacency matrix arr is initialized with zeros using int arr[n][n] = {0};.

The user is prompted to enter the edges by providing two vertices for each edge. The adjacency matrix is updated accordingly by setting the corresponding elements to 1.

The visited array is initialized with zeros using int visited[n] = {0};.

The user is prompted to enter the starting vertex.

The clock() function is used to measure the execution time.

The starting vertex is printed and marked as visited.

The dfs() function is called with the starting vertex and other parameters.

The clock() function is used again to measure the stop time.

The total execution time is printed.

The program ends with a return statement.


*/