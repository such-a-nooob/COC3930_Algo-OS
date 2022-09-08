/*

Part1: Implement in Java the Dijkstra's algorithm for single source shortest path problem.  Take a directed weighted graph as an input. Show results of all intermediate steps of the algorithm.
Part2: Analyze the complexity of the algorithm.

Name : Muniba Rahman
Faculty no. : 20COB275
Sr no. : A2CO-36

*/

import java.util.*;

//class to represent a node of the linked list
//consisting the DESTINATION VERTEX and the WEIGHT of the source-destination edge
class LNode
{
	int dest;
	int wt;
	LNode(int dest, int wt)
	{
		this.dest = dest;
		this.wt = wt;
	}
}

class Graph
{
	public final int INF = Integer.MAX_VALUE;	//constant for infinity

	int vertices;	// total number of vertices present in the graph
	LinkedList<LNode> g[];	// g represents an ADJACENCY LIST (Array of Linked List of type LNode)

	Graph(int vertices)
	{
		g = new LinkedList[vertices];	// size of the adjacency list (array) is equal to the number of vertices in the graph
		this.vertices = vertices;
		for(int i=0; i<vertices; i++)
		{
			g[i] = new LinkedList<>();	// a linked list is inserted in each index of the array
		}
	}

	// To add a new node to the adjacency list
	void addChild(int src, int dest, int weight)
	{
		LNode temp = new LNode(dest, weight);
		g[src].add(temp);
	}

	// To take input from the user and create an adjacency list 
	void createGraph()
	{
		int source, dest, weight;
		Scanner sc = new Scanner(System.in);
		System.out.println("\nEnter the SOURCE VERTEX, the DESTINATION VERTEX and the WEIGHT of the edge between them\n(Do follow the order|Enter -1 when you're done)\n");
		while(true)
		{
			System.out.println("S --w--> D");
			source = sc.nextInt();
			dest = sc.nextInt();
			weight = sc.nextInt();
			if(source == -1 || dest == -1 || weight == -1)
				break;
			addChild(source, dest, weight);
		}
	}

	// to print the adjacency list
	void printGraph()
	{
		System.out.println("\nAdjacency List of the entered Directed Graph : ");
		for(int i=0; i<vertices; i++)
		{
			System.out.print("Vertex "+i+" -> ");
			for(int j=0; j<g[i].size(); j++)
				System.out.print(g[i].get(j).dest+" ["+g[i].get(j).wt+"] ;  ");
			System.out.println();
		}
	}

	// to find the minimum distance from all the unvisited vertices
	int minimumDistance(int[] d, Boolean[] v)
	{
		int min = INF, minV = -1;
		for(int i=0; i<vertices; i++)
		{
			if(v[i]==false && d[i]<=min)
			{
				min = d[i];
				minV = i;
			}
		}
		return minV;
	}

	//COMPLEXITY O(V^2)
	void dijkstra(int s)
	{
		int dist[] = new int[vertices];	// to store the shortest distances after each iteration
		Boolean visited[] = new Boolean[vertices];
		// distances for all vertices are initialized to infinity and visited to false initially
		for(int i=0; i<vertices; i++)	// COMPLEXITY O(V)
		{
			dist[i] = INF;
			visited[i] = false;
		}

		dist[s] = 0; // distance for source node of the graph is 0
		// COMPLEXITY O(V x (2V + E)) = O(V^2)
		for(int i=0; i<vertices-1; i++)	// COMPLEXITY O(V)
		{
			int min = minimumDistance(dist, visited);	// COMPLEXITY O(V)
			visited[min] = true;
			for(int j=0; j<g[min].size(); j++)	// COMPLEXITY O(E)
			{
				int child = g[min].get(j).dest;
				int prevWT = g[min].get(j).wt;
				if(visited[child]==false && dist[child]>(prevWT + dist[min]))
					dist[child] = prevWT + dist[min];
			}

			System.out.println("\n\nMIN = "+min);
			System.out.println("Shortest distance from Source 0 : Vertex[Weight]");
			for(int p=0; p<vertices; p++) 	// COMPLEXITY O(V)
				System.out.print(p+"["+dist[p]+"]\t");
		}
	}
}

class Lab1
{
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the number of nodes : ");
		int n = sc.nextInt();
		Graph G = new Graph(n);
		G.createGraph();
		G.printGraph();
		G.dijkstra(0);	//taking 0 as a source node 
	}
}
