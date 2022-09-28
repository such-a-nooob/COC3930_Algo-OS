/*
Write a program to implement 0/1 knapsack problem. Show all intermediate steps.
Reference: (1) Algorithms by Horowitz and Sahni, and (2) Introduction to Algorithms by Cormen et al.

Name : Muniba Rahman
Faculty no. : 20COB275
Sr no. : A2CO-36

*/

#include<iostream>

using namespace std;

class Knapsack
{
	int KWeight;
	int items;
	int **k;
	int *w, *p;

public:
	Knapsack(int items, int KWeight)
	{
		this->items = items;
		this->KWeight = KWeight;
		w = new int[items+1]{0};
		p = new int[items+1]{0};
		k = new int*[items+1];
		for(int i=0; i<=items; i++)
			k[i] = new int[KWeight+1]{0};
	}

	void getItems()
	{
		cout<<"\n Enter the items and their profits :"<<endl;
		for(int i=1; i<=items; i++)
			cin>>w[i]>>p[i];
	}

	void printResult()
	{
		cout<<"\n MATRIX : "<<endl;
		for(int i=0; i<=items; i++)
		{
			for(int j=0; j<=KWeight; j++)
				cout<<k[i][j]<<" \t ";
			cout<<endl;
		}
		
		cout<<"\n MAXIMUM PROFIT : "<<k[items][KWeight];
		//cout<<"\n ITEM SELECTED : ";

		int x = KWeight;
		int *res = new int[items+1]{0};
		for(int i=items; i>0; i--)
		{
			if(x && (k[i][x] != k[i-1][x]))
			{
				res[i] = 1;
				//cout<<w[i]<<" [ "<<p[i]<<" ] \t";
				x-=w[i];
			}
		}

		cout<<"\n Weights ->  \t ";
		for(int i=1; i<=items; i++)
			cout<<w[i]<<" \t ";

		cout<<"\n Profits ->  \t ";
		for(int i=1; i<=items; i++)
			cout<<p[i]<<" \t ";

		cout<<"\n Selected -> \t ";
		for(int i=1; i<=items; i++)
			cout<<res[i]<<" \t ";
	}

	void maxProfit01()
	{
		/*for(int i=1; i<=items; i++)
		{
			for(int j=1; j<=items-i; j++)
			{
				if(w[j] > w[j+1])
				{
					int t = w[j];
					w[j] = w[j+1];
					w[j+1] = t;
					t = p[j];
					p[j] = p[j+1];
					p[j+1] = t;
				}
			}
		}*/

		for(int i=1; i<=items; i++)
		{
			for(int j=1; j<=KWeight; j++)
			{
				if(j < w[i])
					k[i][j] = k[i-1][j];
				else
					k[i][j] = (k[i-1][j] > k[i-1][j-w[i]] + p[i]) ? k[i-1][j] : k[i-1][j-w[i]] + p[i];
			}
		}

		printResult();
	}
};

int main()
{
	int n, W;
	cout<<"\n Number of items : ";
	cin>>n;
	cout<<" Weight of Knapsack : ";
	cin>>W;
	
	Knapsack K(n, W);
	K.getItems();
	K.maxProfit01();

	return 0;
}