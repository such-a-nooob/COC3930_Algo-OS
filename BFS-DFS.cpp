/*

Write a program in C++ for Breadth First Search (BFS) and Depth First Search (DFS). You need to show all intermediate steps.
Reference: Introduction to Algorithms by Cormen, Lieserson, and Rivest.

Name : Muniba Rahman
Faculty no. : 20COB275
Sr no. : A2CO-36

*/

#include<iostream>
#include<list>

using namespace std;

class Graph
{
	int vertices;	//to store total number of vertices in the graph
	list<int> *g;	//adjacency list - array of lists 

public:
	//constructor - initialises the 'vertices' and creates an array of lists 'g' 
	Graph(int v)
	{
		vertices = v;
		g = new list<int>[vertices];
	}

	//get edges from the user and create the adjacency list
	void createGraph(int directed)
	{
		int s,d;
		cout<<"\n Enter the edges of the graph :\n(Enter -1 when you're done)\n";
		while(1)
		{
			cout<<"S-->D :\t";
			cin>>s>>d;
			if(s == -1 || d == -1) break;
			g[s].push_back(d);
			g[s].sort();
			if(directed == 0)
			{
				g[d].push_back(s);
				g[d].sort();
			}
		}
	}

	//print the adjacency list
	void printGraph()
	{
		cout<<"\nAdjacency List of the entered Graph :\n";
		for(int i=0; i<vertices; i++)
		{
			cout<<"Vertex "<<i<<" -> ";
			for(auto j=g[i].begin(); j!=g[i].end(); j++)
				cout<< *j << " ; ";
			cout<<"\\0"<<endl;
		}
	}

	//checks if an element is present in the given list 
	bool contains(list<int> l, int x)
	{
		for(auto i = l.begin(); i != l.end(); i++)
			if(*i == x)
				return true;
		return false;
	}

	//Breadth First Search implementation
	void BFS(int source , bool *visited)
	{
		list<int> q;	//Queue for BFS implementation
		
		cout<<"\n --- Source : "<<source;
		q.push_back(source);	
		while(!q.empty())
		{
			//printing the queue to show the intermediate steps
			cout<<"\n Queue : ";
			for(auto i = q.begin(); i != q.end(); i++)
				cout<<*i<<"\t";

			int node = q.front();	//fetching the node entered first (Queue follows FIFO)
			q.pop_front();	//pop the node out of the queue
			visited[node] = true;	//mark the poped node visited
			cout<<"\n Node traversed ---> [ "<<node<<" ]";

			for(auto i = g[node].begin(); i != g[node].end(); i++)	//explore the visited node
				if(!visited[*i] && !(contains(q, *i)))	//find elements that are unvisited and are not in the queue
					q.push_back(*i);	//add the elements to the queue
		}
	}

	//Depth First Search implementation
	void DFS(int source , bool *visited)
	{
		list<int> s;	//Stack for DFS implementation
		
		cout<<"\n --- Source : "<<source;
		s.push_back(source);
		visited[source]=true;
		while(!s.empty())
		{
			//printing the stack to show the intermediate steps
			cout<<"\n Stack : ";
			for(auto i = s.begin(); i != s.end(); i++)
				cout<<*i<<"\t";

			int top = s.back();	//fetching the stack top (Stack follows LIFO)
			s.pop_back();	//pop the visited node out of the stack
			visited[top] = true;	//mark the top node of the stack as visited
			cout<<"\n Node traversed ---> [ "<<top<<" ]";
				
			g[top].reverse();
			for(auto i = g[top].begin(); i != g[top].end(); i++)	//explore the top node of the stack
			{
				if(!visited[*i] && !(contains(s, *i)))	//find elements that are unvisited and are not in the stack
				{
					s.push_back(*i);	//add the elements to the stack
					visited[*i]=true;
				}
			}
		}
	}
};

int main()
{
	int d;
	cout<<"\n Directed (1) or Undirected (0) ?\t";
	cin>>d;
	if(!(d == 1 || d == 0)) 
	{
		cout<<"\n Invalid input!";
		exit(0);
	}

	int n;
	cout<<"\n Enter the total number of vertices in the graph : ";
	cin>>n;

	Graph G(n);
	G.createGraph(d);
	G.printGraph();

	bool *visited = new bool[n];	//An array to keep track of the visited nodes
	
	cout<<"\nBreadth First Traversal :\n";
	for(int i=0; i<n; i++)
		visited[i] = false;	//mark all nodes of the graph - unvisited
	for(int i=0; i<n; i++)
		if(visited[i] == false)
			G.BFS(i,visited);

	cout<<"\n\nDepth First Traversal :\n";
	for(int i=0; i<n; i++)
		visited[i] = false;	//mark all nodes of the graph - unvisited
	for(int i=0; i<n; i++)
		if(visited[i] == false)
			G.DFS(i,visited);

	return 0;
}
