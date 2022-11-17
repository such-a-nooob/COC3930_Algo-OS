/*

Given a set of processes and their max demands and currently allocated resources of each type. Also, given the maximum number of resources of each type in a system. Write a program to implement Bankers algorithm. Further, suppose a process requests resources of each type. Can the request of the process be granted? You need to compute the safe sequence.
Reference: Operating Systems by Silberchaltz and Galvin

Name : Muniba Rahman
Faculty no. : 20COB275
Sr no. : A2CO-36

*/

import java.util.*;

class BankersAlgo 
{
  int need[][], allocate[][], max[][], avail[];
  int np, nr;
  
  BankersAlgo(int np, int nr)
  {
    this.np = np;
    this.nr = nr;
    need= new int[np][nr]; //initializing arrays
    max= new int[np][nr];
    allocate = new int[np][nr];
    avail = new int[nr];
  }
  
  void inputData()
  {  
    Scanner sc = new Scanner(System.in);

    System.out.print("\nEnter the matrices :");
    System.out.println("\nAllocated resources ( "+np+" x "+nr+" )");
    for(int i=0; i<np; i++)
      for(int j=0;j<nr; j++)
        allocate[i][j]=sc.nextInt();  //allocate matrix
      
    System.out.println("\nMaximum need of processes ( "+np+" x "+nr+" )");
    for(int i=0; i<np; i++)
      for(int j =0; j<nr; j++)
        max[i][j]=sc.nextInt(); //max matrix
      
    System.out.println("\nEnter the total available resources : ");
    for (int j=0; j<nr; j++)
      avail[j]=sc.nextInt(); //available processes
  }
  
  int [][] calc_need()
  {
    for(int i=0; i<np; i++)
      for(int j=0; j<nr; j++)  //calculating need matrix
        need[i][j]=max[i][j]-allocate[i][j];
      
    return need;
  }
      
              
  boolean check(int i)
  {
    //checking if all resources for ith process can be allocated
    for (int j=0; j<nr; j++)
      if(avail[j]<need[i][j])
        return false;
      
    return true;
  }
  
  void isSafe()
  {
    calc_need();
    boolean done[] = new boolean[np];
    for(int i=0; i<np; i++)
      done[i] = false;
    int j=0;
     
    System.out.print("\nSafe sequence : ");
    while(j<np)
    { //untill all the processes are allocated
      boolean allocated = false;
      for(int i=0; i<np; i++)
      {
        if(!done[i] && check(i))
        { //trying to allocate
          for (int k=0; k<nr; k++)
            avail[k]=avail[k]-need[i][k]+max[i][k];
        
          System.out.print(i+1+" ");
          allocated = true;
          done[i] = true;
          j++;
        }
      }
      if(!allocated) break;  //no allocation
    }
      
    if(j==np) //if all processes are allocated
      System.out.println("\nSafely Allocated!");
    else
      System.out.println("\nAll processes can not be allocated safely!");   
  }
}
  
class Lab7 
{
  public static void main(String [] args)
  {
    int processes, resources;
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter no. of processes and resources : ");
    processes = sc.nextInt();
    resources = sc.nextInt();

    BankersAlgo B = new BankersAlgo(processes, resources);
    B.inputData();
    B.isSafe();
  }
}
