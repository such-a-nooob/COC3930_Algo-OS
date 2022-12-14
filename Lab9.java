/*

Given the number of frames and a reference string. Write a program
to implement page replacement algorithms e.g. FIFO, LRU, and OPT.

Reference: Operating Systems by Silberchatz and Galvin.

Name : Muniba Rahman
Faculty no. : 20COB275
Sr no. : A3CO-36

*/

import java.util.*;

class PageReplacement
{
	int nf, n;
	Boolean[] pages;
    int pfaults, hits;
    int[] refString;
    
    PageReplacement(int n, int nf)
    {
    	this.n = n;
    	this.nf = nf;	
    	pages = new Boolean[1000];
    	refString = new int[n];
    }

    void inputRefString()
    {
    	Scanner sc = new Scanner(System.in);
    	System.out.println("Enter the reference string :\t");
	    for (int i=0; i<n; i++)
	        refString[i] = sc.nextInt();
	}

	void initialize()
	{
		pfaults = 0;
    	hits = 0;
		for(int i=0; i<1000; i++)
    	    pages[i] = false;
	}

	void prFIFO()
	{
		System.out.println("\n\n---FIFO PAGE REPLACEMENT ALGORITHM---");
		LinkedList<Integer> frames = new LinkedList();
		initialize();
    	for (int i=0; i<n; i++)
	    {
	        System.out.println("\n--> For page : " + refString[i]);
	        if (pages[refString[i]] == true)
	        {
	            System.out.println("HIT!\n " + refString[i] + " already present in memory!");
	            hits++;
	        }
	        else
	        {
	            System.out.println("PAGE FAULT!\n Page " + refString[i] + " not present in memory!" );
	            frames.add(refString[i]);
	            if (frames.size() == nf)
	            {
	                int top = frames.peekFirst();
	                frames.pop();
	                pages[top] = false;
	                System.out.println("Removed page : " + top);
	            }
	            System.out.println("Inserted page : " + refString[i]);
	            pages[refString[i]] = true;
	            pfaults++;
	        }
	    }
	    System.out.println("\nThe total number of hits occurred = " + hits);
	    System.out.println("The total number of page faults occurred = " + pfaults);
	}

	void prOPT()
	{
		System.out.println("\n\n---OPTIMAL PAGE REPLACEMENT ALGORITHM---");
	    LinkedList<Integer> frames = new LinkedList();
	    initialize();
    	for (int i = 0; i < n; i++)
	    {
	        System.out.println("\n--> For page : " + refString[i]);
	        int k;
	        for (k = 0; k < frames.size(); k++)
	        {
	            if (frames.get(k) == refString[i])
	            {
	            	System.out.println("HIT!\n " + refString[i] + " already present in memory!");
	                break;
	            }
	        }
	        if (k == frames.size())
	        {
	            System.out.println("PAGE FAULT!\n Page " + refString[i] + " not present in memory!");
	            if (frames.size() < nf)
	            {
	                frames.add(refString[i]);
	                System.out.println("Inserted page : " + refString[i]);
	            }

	            else
	            {
	                int index = i + 1;
	                int res = -1, farthest = index;
	                for (int l = 0; l < frames.size(); l++)
	                {
	                    int j;
	                    for (j = index; j < n; j++)
	                    {
	                        if (frames.get(l) == refString[j])
	                        {
	                            if (j > farthest)
	                            {
	                                farthest = j;
	                                res = l;
	                            }
	                            break;
	                        }
	                    }
	                    if (j == n)
	                    {
	                        res = l;
	                        break;
	                    }
	                }
	                System.out.println("Removed page : " + frames.get(res));
	                System.out.println("Inserted page : " + refString[i]);
	                frames.remove(res);
	                frames.add(res, refString[i]);
	            }
	            pfaults++;
	        }
	    }
	    System.out.println("\nThe total number of hits occurred = " + (n - pfaults));
		System.out.println("The total number of page faults occurred = " + pfaults);
	}

	void prLRU()
	{
	    System.out.println("\n\n---LRU PAGE REPLACEMENT ALGORITHM---");
	    int[] frames = new int[nf];
	    initialize();
	    for (int i = 0; i < nf; i++)
	    {
	        frames[i] = -1;
	    }
	    
	    int[] time = new int[1000];
	    for (int i = 0; i < 1000; i++)
	    {
	        time[i] = -1;
	    }
	    int index = 0;
	    for (int i = 0; i < n; i++)
	    {
	        System.out.println("\n--> For page : " + refString[i]);
	        if (pages[refString[i]] == true)
	        {
	            System.out.println("HIT!\n " + refString[i] + " already present in memory!");
	            hits++;
	        }
	        else
	        {
	            System.out.println("PAGE FAULT!\n Page " + refString[i] + " not present in memory!");
	            if (frames[nf - 1] == -1)
	                frames[index] = refString[i];
	            else
	            {
	                int lru = 1000;
	                for (int j = 0; j < 1000; j++)
	                {
	                    if (time[j] < lru && time[j] >= 0)
	                    {
	                        lru = time[j];
	                        index = j;
	                    }
	                }
	                for (int j = 0; j < nf; j++)
	                {
	                    if (frames[j] == index)
	                    {
	                        System.out.println("Removed page : " + frames[j]);
	                        pages[frames[j]] = false;
	                        time[frames[j]] = -1;
	                        frames[j] = refString[i];
	                    }
	                }
	            }
	            index = (index + 1) % nf;
	            System.out.println("Inserted page : " + refString[i]);
	            pages[refString[i]] = true;
	            pfaults++;
	        }
	        time[refString[i]] = i;
	    }
	    System.out.println("\nThe total number of hits occurred = " + hits);
	    System.out.println("The total number of page faults occurred = " + pfaults);
	}
};

class Lab9 
{
	public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
	    int nf, n;
	    System.out.println( "Enter no of page frames :\t");
	    nf = sc.nextInt();
	    System.out.println( "Enter the no of pages you want to insert :\t");
	    n = sc.nextInt();
	    PageReplacement P = new PageReplacement(n, nf);
	    P.inputRefString();
	    int again=1;
	    do
	    {
	    System.out.println( "\nReplacement Algorithm?\n 1. FIFO\n 2. OPT\n 3. LRU\n 4. Exit\nYour choice : ");
	    int ch = sc.nextInt();
	    switch(ch)
	    {
	    	case 1 :
		    P.prFIFO();
		    break;
		    case 2:
		    P.prOPT();
		    break;
		    case 3:
		    P.prLRU();
		    break;
		    case 4:
		    again = 0;
		    break;
		    default: System.out.println( "\nInvalid Choice!");
		}
		}while(again==1);
	}
}
