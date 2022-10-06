/*

Given a  flow network with a source, s, and a sink, t. 
Write a program to find the maximum flow in a flow network from the source to the sink. 
Show all intermediate steps.

Reference: Introduction to Algorithms by Cormen et al.

Name : Muniba Rahman
Faculty no. : 20COB275
Sr no. : A2CO-36

*/

import java.util.*;

class Graph
{
	public final int INF = Integer.MAX_VALUE;	//constant for infinity
	
	int g[][];
	int vertices;
	int type;

	Graph(int vertices, int type)
	{
		g = new int[vertices][vertices];
		this.vertices = vertices;
		this.type = type;
	}

	void addEdge(int src, int dest, int cap)
	{
		g[src][dest] = cap;
		if(type == 1)	//graph is undirected
			g[dest][src] = cap;
	}

	// To take input from the user and create an adjacency matrix 
	void createGraph()
	{
		int src, dest, cap;
		Scanner sc = new Scanner(System.in);
		System.out.println("\nEnter the EDGES of the graph and their WEIGHT/CAPACITY \n(Do follow the order|Enter -1 when you're done)");
		while(true)
		{
			src = sc.nextInt();
			dest = sc.nextInt();
			cap = sc.nextInt();
			if(src == -1 || dest == -1 || cap == -1)
				break;
			addEdge(src, dest, cap);
		}
	}

	// to print the adjacency matrix
	void printGraph(int[][] g)
	{
		System.out.println("\nAdjacency Matrix : ");
		for(int i=0; i<vertices; i++)
		{
			for(int j=0; j<vertices; j++)
				System.out.print(g[i][j]+"\t");
			System.out.println();
		}
	}

	int c;
	//to print the augmenting path
	void printPath(int[][] g, int[] p, int source, int sink)
	{
		int s = sink, d = p[s];
		System.out.println("\nPath "+(c++));
		while(s!=source)
		{
			System.out.print(s+"  <-- ["+g[d][s]+"] ---  ");
			s = d;
			d = p[s];
		}
		System.out.println(s);
	}

	//to traverse the graph and find a possible path
	Boolean findPath(int[][] g, int source, int sink, int[] parent)
	{
		int[] queue = new int[vertices];
		int front = -1, rear = -1;

		Boolean[] visited = new Boolean[vertices];
		for(int i=0; i<vertices; i++)
			visited[i] = false;

		//Enqueue source
		queue[++rear] = source;
		front++; 
		//set the parent of source to -1 and visited to true
		parent[source] = -1;
		visited[source] = true;
		
		while(front <= rear)	//until the queue is empty 
		{
			//pop the front element
			int popped = queue[front++];
			//find vertices adjacent to popped vertices
			for(int i=0; i<vertices; i++)
			{
				/* such that - 
				   (i) They're not visited yet (not already in queue)
				   (ii) The capacity of the edge to that vertex is NOT 0	*/
				if((!visited[i]) && (g[popped][i] > 0))
				{
					//if sink is found/visited then return true
					if(i == sink)
					{
						parent[i] = popped;
						printPath(g, parent, source, sink);
						return true;
					}

					//enqueue found vertices
					queue[++rear] = i;
	
					//mark them visited and set parent
					visited[i] = true;
					parent[i] = popped;
				}
			}
		}
		return false;
	}

	int fordFulkerson(int source, int sink)
	{
		//copy the original adjacency matrix
		int[][] tempG = new int[vertices][vertices];
		for(int i=0; i<vertices; i++)
			for(int j=0; j<vertices; j++)
					tempG[i][j] = g[i][j];

		//to store the source/ parent of each node of the augmenting path
		int[] parent = new int[vertices];

		int maxFlow = 0;

		while(findPath(tempG, source, sink, parent) == true)	//repeat until sink can not be visited
		{
			int minCap = INF;

			//trace the path from sink to source
			int s = sink, d = parent[s];
			while(s!=source)
			{
				//find the minimum capacity on this path
				minCap = (minCap > tempG[d][s])? tempG[d][s]: minCap;
				s = d;
				d = parent[s];
			}
			System.out.println("Minimum Capacity : "+minCap);

			//add the minimum capacity thus found to the maximum flow
			maxFlow += minCap;

			//trace the path from sink to source
			s = sink;	d = parent[s];
			while(s!=source)
			{
				//subtract minimum capacity from the capacity of each edge on that path
				tempG[d][s] -= minCap;
				//undirected graph
				if(type == 1)	
					tempG[s][d] += minCap;
				s = d;
				d = parent[s];
			}
		}

		return maxFlow;
	}
}

class Lab5
{
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		System.out.println("Directed (0) / Undirected (1) ? ");
		int dir = sc.nextInt();
		System.out.println("Enter the number of nodes : ");
		int n = sc.nextInt();
		Graph G = new Graph(n, dir);
		/*G.addEdge(0,1,11);
		G.addEdge(0,2,12);
		G.addEdge(1,3,12);
		G.addEdge(2,1,1);
		G.addEdge(1,2,2);
		G.addEdge(2,4,11);
		G.addEdge(4,3,7);
		G.addEdge(3,5,19);
		G.addEdge(4,5,4);*/
		G.createGraph();
		G.printGraph(G.g);
		int again;
		do
		{
			System.out.println("\nEnter the source and sink nodes : ");
			int source = sc.nextInt();
			int sink = sc.nextInt();
			G.c=1;
			int maxFlow = G.fordFulkerson(source, sink);
			System.out.println("\nMAXIMUM FLOW : "+ maxFlow);
			System.out.println("\n\nChange source and sink nodes?\n(Press 0 to EXIT)");
			again = sc.nextInt();
		}while(again!=0);
	}
}
