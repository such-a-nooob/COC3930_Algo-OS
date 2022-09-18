import java.util.*;

class LNode
{
	int dest;
	int cost;

	LNode(int dest, int cost)
	{
		this.dest = dest;
		this.cost = cost;
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
			g[i] = new LinkedList<>();	// a linked list is inserted at each index of the array
	}

	// To add a new node to the adjacency list
	void addNode(int src, int dest, int cost)
	{
		LNode temp = new LNode(dest, cost);
		g[src].add(temp);
		temp = new LNode(src, cost);
		g[dest].add(temp);
	}

	// To take input from the user and create an adjacency list 
	void createGraph()
	{
		int src, dest, cost;
		Scanner sc = new Scanner(System.in);
		System.out.println("\nEnter the EDGES of the graph and their WEIGHT/COST \n(Do follow the order|Enter -1 when you're done)\n");
		while(true)
		{
			src = sc.nextInt();
			dest = sc.nextInt();
			cost = sc.nextInt();
			if(src == -1 || dest == -1 || cost == -1)
				break;
			addNode(src, dest, cost);
		}
	}

	// to print the adjacency list
	void printGraph()
	{
		System.out.println("\nAdjacency List of the entered Graph : ");
		for(int i=0; i<vertices; i++)
		{
			System.out.print("Vertex "+i+" -> ");
			for(int j=0; j<g[i].size(); j++)
				System.out.print(g[i].get(j).dest+" ["+g[i].get(j).cost+"] ;  ");
			System.out.println("\\0");
		}
	}

	// to find the minimum cost from all the vertices which are not yet included in the MST
	int minCost(int[] costs, Boolean[] included)
	{
		int min = INF, minV = INF;
		for(int i=0; i<vertices; i++)
		{
			if(included[i]==false && costs[i]<=min)
			{	
				if(costs[i] == min)	//if edges with same costs occur
				{
					if(i < minV)	// the edge connecting to a lower order vertex would be preferred
						minV = i;
				}
				else
					minV = i;
				min = costs[i];
			}
		}
		return minV;
	}

	// to print the Minimum Spanning Tree
	void printMST(int[] parent, int[] costs, int root)
	{
		if(parent[root] == -1)
			System.out.println("Root Node : "+root);
		else
			System.out.println("Parent : "+parent[root]+"\t Child : "+root+"\t Cost : "+costs[root]);
		
		for(int i=0; i<vertices; i++)
			if(parent[i] == root)
				printMST(parent, costs, i);
			
	}

	void prims(int root)
	{
		int costs[] = new int[vertices];	// to store the minimum costs associated with the vertices
		Boolean included[] = new Boolean[vertices];	// to check if the vertices are included in MST
		int parent[] = new int[vertices];	// to store the parent of each node in MST

		// costs for all vertices are set to infinity and root to zero
		for(int i=0; i<vertices; i++)
			costs[i] = INF;
		costs[root] = 0;
		
		// MST is empty, mark all vertices as NOT included
		for(int i=0; i<vertices; i++)
			included[i] = false;

		// set the parent node of root to -1
		parent[root] = -1;
		
		for(int i=0; i<vertices; i++)
		{
			int node = minCost(costs, included);	// find the node with minimum cost associated 
			System.out.println(node);
			included[node] = true;	// include that node in MST
			
			for(int j=0; j<g[node].size(); j++)	//explore the node
			{
				int orgCost = g[node].get(j).cost;	// cost of the current edge
				int destNode = g[node].get(j).dest;	
				if(included[destNode] == false && orgCost < costs[destNode])	// if current cost is smaller than previous 
				{
					costs[destNode] = orgCost;	// update the cost
					parent[destNode] = node;	// store the parent of that node to create the MST
				}
			}
		}

		// check if the graph is connected
		Boolean connected = true;
		for(int i=0; i<vertices; i++)
		{
			for(int x=0; x<vertices; x++)
				System.out.print(parent[x]+"\t");
			System.out.println();

			if(costs[i] == INF)
			{
				connected = false;
				break;
			}
		}
		// if graph is connected, print the MST 
		if(connected)
		{
			System.out.println("\nMinimum Spanning Tree of the given graph would be : ");
			printMST(parent, costs, root);
			int t=0;
			for(int i=0; i<vertices; i++)
				t+=costs[i];
			System.out.println("TOTAL COST : "+t);
		}
		// if the graph is disconnected, Prim's Algorithm is not applicable
		else
			System.out.println("\nPrim's Algorithm is not applicable for disconnected graphs!");
	}
}

class Lab3
{
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		System.out.println("\nEnter the number of nodes :\t");
		int n = sc.nextInt();

		Graph G = new Graph(n);
		G.createGraph();
		G.printGraph();
		
		while(true)
		{
			System.out.println("\nEnter the root node :\t");
			int s = sc.nextInt();
			
			G.prims(s);

			System.out.println("\nAgain? (Enter any number)\nPress 0 to EXIT \t");
			int ch = sc.nextInt();
			if(ch == 0) break;
		}
	}
}