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
			if(directed == 0)
				g[d].push_back(s);
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
	bool BFS(int source = 0, int key = -1)
	{
		list<int> q;	//Queue for BFS implementation
		bool *visited = new bool[vertices];	//An array to keep track of the visited nodes
		for(int i=0; i<vertices; i++)
			visited[i] = false;	//mark all nodes of the graph - unvisited

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
			if(key != -1)	//if it's searching
				if(node == key)	//check if the visited element matches with the key
					return true;

			for(auto i = g[node].begin(); i != g[node].end(); i++)	//explore the visited node
				if(!visited[*i] && !(contains(q, *i)))	//find elements that are unvisited and are not in the queue
					q.push_back(*i);	//add the elements to the queue
		}
		return false;
	}

	//Depth First Search implementation
	bool DFS(int source, int key = -1)
	{
		list<int> s;	//Stack for DFS implementation
		bool *visited = new bool[vertices];	//An array to keep track of the visited nodes
		for(int i=0; i<vertices; i++)
			visited[i] = false;	//mark all nodes of the graph - unvisited

		s.push_back(source);
		while(!s.empty())
		{
			//printing the stack to show the intermediate steps
			cout<<"\n Stack : ";
			for(auto i = s.begin(); i != s.end(); i++)
				cout<<*i<<"\t";

			int c = 0;	//to count the number of elements pushed into the stack
			int top = s.back();	//fetching the stack top (Stack follows LIFO)
			for(auto i = g[top].begin(); i != g[top].end(); i++)	//explore the top node of the stack
			{
				if(!visited[*i] && !(contains(s, *i)))	//find elements that are unvisited and are not in the stack
				{
					s.push_back(*i);	//add the elements to the stack
					c++;
				}
			}
			if(c == 0)	//if no elements are entered in the stack
			{
				visited[top] = true;	//mark the top node of the stack as visited
				cout<<"\n Node traversed ---> [ "<<top<<" ]";
				if(key != -1)	//if it's searching
					if(top == key)	//check if the visited element matches with the key
						return true;
				s.pop_back();	//pop the visited node out of the stack
			}
		}
		return false;
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

	int repeat;
	do
	{
	int ch;
	cout<<"\n Traversal (0) or Search (1) ?\t";
	cin>>ch;
	if(ch == 1)	//Searching
	{
		int key;
		cout<<"\n Enter the key to be searched :\t";
		cin>>key;
		cout<<"\nBreadth First Search :\n";
		if(G.BFS(0, key))
			cout<<"\n Key "<<key<<" found!";
		else
			cout<<"\n Key "<<key<<" not found!";
		cout<<"\n\nDepth First Search :\n";
		if(G.DFS(0, key))
			cout<<"\n Key "<<key<<" found!";
		else
			cout<<"\n Key "<<key<<" not found!";
	}
	else if(ch == 0)	//Traversal
	{
		int s;
		cout<<"\n Enter the source node : ";
		cin>>s;
		cout<<"\nBreadth First Traversal :\n";
		G.BFS(s);
		cout<<"\n\nDepth First Traversal :\n";
		G.DFS(s);
	}
	else 	//Invalid input
	{
		cout<<"\n Invalid input!";
		exit(0);
	}
	cout<<"\n AGAIN? (Press 0 to Exit)\t";
	cin>>repeat;
	}while(repeat != 0);

	return 0;
}
