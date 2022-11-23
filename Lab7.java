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
  int need[][], allocate[][], max[][], avail[], availNow[];
  int np, nr;
  
  BankersAlgo(int np, int nr)
  {
    this.np = np;
    this.nr = nr;
    need= new int[np][nr]; //initializing arrays
    max= new int[np][nr];
    allocate = new int[np][nr];
    avail = new int[nr];
    availNow = new int[nr];
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
    for (int i=0; i<nr; i++)
    {
      avail[i]=sc.nextInt(); //available processes
      availNow[i] = avail[i];
    }
  }

  void printTable(int[][] matrix)
  {
    System.out.print("\nProcesses\t");
    for(int i=0; i<nr; i++)
      System.out.print("R"+(i+1)+"\t");
    for(int i=0; i<np; i++)
    {
      System.out.print("\n  P"+(i+1)+"\t\t");
      for(int j=0; j<nr; j++)
        System.out.print(matrix[i][j]+"\t");
    }
  }

  void printData()
  {
    System.out.print("\nCURRENTLY ALLOCATED RESOURCES");
    printTable(allocate);
    System.out.print("\n\nMAXIMUN DEMANDS");
    printTable(max);
  }
  
  void calcNeed()
  {
    for(int i=0; i<np; i++)
      for(int j=0; j<nr; j++)  //calculating need matrix
        need[i][j]=max[i][j]-allocate[i][j];
  }
    
  void calcAvailable()
  {
    for(int i=0; i<nr; i++)
    {
      for(int j=0; j<np; j++)
        availNow[i] = availNow[i] - allocate[j][i];
    }
  }
              
  boolean checkResource(int[] available, int i)
  {
    //checking if all resources for ith process can be allocated
    for (int j=0; j<nr; j++)
      if(available[j]<need[i][j])
        return false;
      
    return true;
  }
  
  void isSafe()
  {
    calcNeed();
    System.out.print("\n\nRESOURCES NEEDED");
    printTable(need);

    calcAvailable();
    System.out.println("\n\nAVAILABLE RESOURCES");
    for(int i=0; i<nr; i++)
      System.out.print("R"+(i+1)+"\t");
    System.out.println();
    for(int i=0; i<nr; i++)
      System.out.print(availNow[i]+"\t");

    boolean done[] = new boolean[np];
    int safeSequence[] = new int[np];
    int ns=0;
    for(int i=0; i<np; i++)
      done[i] = false;
    int f=0;
     
    while(f<np)
    { //untill all the processes are allocated
      boolean allocated = false;
      for(int i=0; i<np; i++)
      {
        if(!done[i] && checkResource(availNow,i))
        { //trying to allocate
          for (int j=0; j<nr; j++)
            availNow[j] = availNow[j] + allocate[i][j];
        
          System.out.println("\n\nResourses allocated to : P"+(i+1));
          System.out.println("Available Resources :");
          for(int k=0; k<nr; k++)
            System.out.print("R"+(k+1)+"\t");
          System.out.println();
          for(int k=0; k<nr; k++)
            System.out.print(availNow[k]+"\t");
          
          safeSequence[ns++] = i+1;
          allocated = true;
          done[i] = true;
          f++;
        }
      }
      if(!allocated) break;  //no allocation
    }
      
    if(f==np) //if all processes are allocated
    {
      System.out.println("\n\nAll processes are SAFELY Allocated!");

      System.out.print("Safe sequence : ");
      int i;
      for(i=0; i<np-1; i++)
        System.out.print("P"+safeSequence[i]+" -> ");
      System.out.println("P"+safeSequence[i]);
    }
    else
      System.out.println("\n\nAll processes CAN NOT be allocated safely!");   
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
    B.printData();
    B.isSafe();
  }
}
