#include<iostream>
#include<algorithm>

#define MAX 1000
using namespace std; 

struct Process
{
        int pid; 
        int btime; 
        int priority; 
};

bool comparison(Process a, Process b)
{
    return (a.priority < b.priority);
}

class NPPriority
{
    Process *processList;
    int n;

public:

    NPPriority(int n)
    {
        this->n = n;
        processList = new Process[MAX];
    }

    void inputData()
    {
        cout<<"\nEnter the Process number,  Burst Time and Piority"<<endl; 
        int i; 
        for(i = 0; i<n; i++)
        {
            cin>>processList[i].pid; 
            cin>>processList[i].btime; 
            cin>>processList[i].priority;  
        }
    }

    void avgTime()
    {
        int wt[n], tat[n], total_wt = 0, total_tat = 0;

        wt[0] = 0;
        for (int i = 1; i < n ; i++ )
            wt[i] = processList[i-1].btime + wt[i-1] ;

        for (int i = 0; i < n ; i++)
            tat[i] = processList[i].btime + wt[i];

        cout<<"\n\nGantt Chart"<<endl; 
        for(int i=0; i<n; i++)
            cout<<"|  "<<'P'<< processList[i].pid << "   ";
        cout<<"|\n0\t";
        for(int i=0; i<n; i++)
            cout << tat[i] << "\t"; 

        cout << "\n\nProcesses "<< " Burst time "<< " Waiting time " << " Turn around time"<<endl;

        for (int i=0; i<n; i++)
        {
            total_wt = total_wt + wt[i];
            total_tat = total_tat + tat[i];
            cout << " " << processList[i].pid << "\t\t"<< processList[i].btime << "\t " << wt[i]<< "\t\t " << tat[i] <<endl;
        }

        cout << "\nAverage waiting time = "<< (float)total_wt / (float)n;
        cout << "\nAverage turn around time = "<< (float)total_tat / (float)n;
    }

    void npPriority()
    {
        sort(processList, processList + n, comparison);
        avgTime();
    }
};

struct process
{
    char pid; 
    int btime; 
    int atime; 
    int priority; 
    int restime = 0; 
    int ctime = 0; 
    int wtime = 0; 
}; 

bool btimeSort(process a, process b)
    {
        return a.btime < b.btime;  
    }

    bool atimeSort(process a, process b)
    {
        return a.atime < b.atime;  
    }
    bool prioritySort(process a, process b)
    {
        return a.priority < b.priority;  
    }

class PPriority
{
    process *a;
    process *b;
    process *c;
    int n;
    int k, f, r; 

public:

    PPriority(int n)
    {
        this->n = n;
        a = new process[MAX];
        b = new process[MAX];
        c = new process[MAX];
        k=0;    f=0;    r=0;
    }

    void inputData()
    {
        cout<<"\nEnter the Process number,  Piority,  Arrival Time and  Burst Time"<<endl; 
        for(int i=0; i<n; i++)
        {
            cin>>a[i].pid; 
            cin>>a[i].priority; 
            cin>>a[i].atime; 
            cin>>a[i].btime; 
            a[i].wtime = -a[i].atime+1; 
        }
    }

    void pPriority(int qt = 1)
    {
        int np = n, q; 
        sort(a, a+np,  atimeSort); 
        int ttime = 0, i; 
        int j, tArray[np]; 
        int alltime = 0; 
        bool moveLast = false; 

        for(i = 0; i<np; i++)
            alltime += a[i].btime; 

        alltime += a[0].atime; 
        for(i = 0; ttime <= alltime; )
        {
            j = i; 
            while(a[j].atime <= ttime && j != np)
            {
                b[r] = a[j]; 
                j++; 
                r++; 
            }
            if(r == f)
            {
                c[k].pid = 'i'; 
                c[k].btime = a[j].atime-ttime; 
                c[k].atime = ttime; 
                ttime += c[k].btime; 
                k++; 
                continue; 
            }
            i = j; 
            if(moveLast == true)
                sort(b+f, b+r, prioritySort);  

            j = f; 
            if(b[j].btime > qt)
            {
                c[k] = b[j]; 
                c[k].btime = qt; 
                k++; 
                b[j].btime = b[j].btime-qt; 
                ttime += qt;   
                moveLast = true; 
                for(q = 0; q<np; q++){
                    if(b[j].pid != a[q].pid){
                        a[q].wtime += qt; 
                    }
                }
            }
            else
            {
                c[k] = b[j]; 
                k++; 
                f++; 
                ttime += b[j].btime;   
                moveLast = false; 
                for(q = 0; q<np; q++){
                    if(b[j].pid != a[q].pid){
                        a[q].wtime += b[j].btime; 
                    }
                }
            }
            if(f == r && i >= np)
            break; 
        }
        tArray[i] = ttime; 
        ttime += a[i].btime; 
        for(i = 0; i<k-1; i++){
            if(c[i].pid == c[i+1].pid)
            {
                c[i].btime += c[i+1].btime; 
                for(j = i+1; j<k-1; j++)
                    c[j] = c[j+1]; 
                k--; 
                i--; 
            }
        }
        
        int rtime = 0; 
        for(j = 0; j<np; j++)
        {
            rtime = 0; 
            for(i = 0; i<k; i++)
            {
                if(c[i].pid == a[j].pid)
                {
                    a[j].restime = rtime; 
                    break; 
                }
                rtime += c[i].btime; 
            }
        }

        float averageWaitingTime = 0; 
        float averageResponseTime = 0; 
        float averageTAT = 0; 
        
        cout<<"\nGantt Chart"<<endl; 
        rtime = 0; 
        for (i = 0;  i<k;  i++){
            if(i != k)
                cout<<"|  "<<'P'<< c[i].pid << "   ";  
            rtime += c[i].btime; 
            for(j = 0; j<np; j++){
                if(a[j].pid == c[i].pid)
                    a[j].ctime = rtime; 
            } 
        }
        cout<<"|"<<endl; 
        rtime = 0; 
        for (i = 0;  i<k+1;  i++){
            cout << rtime << "\t"; 
            tArray[i] = rtime; 
            rtime += c[i].btime;  
        }

        cout<<"\n\nPID Priority\tAT\tBT\tTAT\tWT"<<endl; 
        for (i = 0;  i<n && a[i].pid != 'i';  i++)
        {
            if(a[i].pid == '\0')
                break; 
            cout <<'P'<< a[i].pid << "\t";  
            cout << a[i].priority << "\t"; 
            cout << a[i].atime << "\t"; 
            cout << a[i].btime << "\t"; 
            cout << a[i].wtime+a[i].ctime-rtime+a[i].btime << "\t";  
            averageTAT += a[i].wtime+a[i].ctime-rtime+a[i].btime; 
            cout << a[i].wtime+a[i].ctime-rtime << "\t";  
            averageWaitingTime += a[i].wtime+a[i].ctime-rtime; 
            cout <<""<<endl;  
        }

        cout<<"\nAverage Waiting time: "<<(float)averageWaitingTime/(float)n<<endl; 
        cout<<"Average TA time: "<<(float)averageTAT/(float)n<<endl; 

    }
};

class RRobin
{
    int n,btime[10],atime[10],tatime[10],wtime[10],rtime[10],finish[10];
    float twt,ttat,total;   //total waiting Time, total turnaround Time

public:

    RRobin(int n)
    {
        this->n = n;
    }
    
    void  inputData()
    {
        cout<<"Enter the Arrival times in order:\n";
        for(int i=0;i<n;i++)
        cin>>atime[i];
        cout<<"Enter the Burst times in order :\n";
        for(int i=0;i<n;i++)
        cin>>btime[i];
    }

    void  Init()
    {
        total=0;
        twt=0;
        ttat=0;
        for(int i=0; i<n; i++)
     {
            rtime[i]=btime[i];
            finish[i]=0;
            wtime[i]=0;
            tatime[i]=0;
            total+=btime[i];
            }
    }

    void  dispTime()
    {
        cout << "\n\nProcesses "<< " Burst time "<< " Waiting time " << " Turn around time"<<endl;

            for(int i=0;i<n;i++)
            {

                twt+=wtime[i];
                tatime[i]=wtime[i]+btime[i];
                ttat+=tatime[i];
                //cout<<"\nProcess"<<(i+1)<<endl;
                //cout<<"Waiting Time = "<<wtime[i]<<"\t\t"<<"Turnaround Time = "<<tatime[i]<<endl;
                cout << " " << (i+1) << "\t\t"<< btime[i] << "\t " << wtime[i]<< "\t\t " << tatime[i] <<endl;

            }

            cout<<"\nAverage Waiting Time = "<<(float)twt/n<<endl;
            cout<<"Average Turnaround Time = "<<(double)ttat/n<<endl;
        
    }

    void  roundRobin()
    {
        Init();
        int t,j,q,i,dec=0;
        cout<<"Enter the Time quantum:\n";
        cin>>q;
        cout<<"Gantt Chart\n ";
        for(t=0;t<total;)
        {
            for(i=0;i<n;i++)
            {
                if(atime[i]<=t && finish[i]==0)
                {

                    cout<<"("<<t<<")|  P"<<(i+1)<<"  |";
                    if(rtime[i]<q)  {
                        dec=rtime[i];
                    }
                    else {dec=q;}

                    rtime[i]=rtime[i]-dec;
                    if(rtime[i]==0) 
                        finish[i]=1;
                    for(j=0;j<n;j++)
                        if(j!=i && finish[j]==0 && atime[j]<=t)
                            wtime[j]+=dec;
                     t=t+dec;
                }
            }
        }                                                         

        cout<<"("<<total<<")"<<endl;
        dispTime();
    }
};

int main()
{
    int np, choice; 
    cout<<"[NOTE - Lesser the number, higher the priority]\n"<<endl;
    cout<<"1. Non-preemptive Priority Scheduling\n2. Preemptive Priority Scheduling\n3. Round Robin\nEnter your choice: ";
    cin>>choice;
    cout<<"\nEnter number of processes"<<endl; 
    cin>>np; 
    NPPriority npp(np);
    PPriority pp(np);
    RRobin rr(np);
    switch (choice)
    {
    case 1:
        npp.inputData();
        npp.npPriority();
        break;
    case 2:
        pp.inputData(); 
        pp.pPriority();
        break;
    case 3:
        rr.inputData();
        rr.roundRobin(); 
        break;
    default:
        cout<<"\nInvalid choice!"<<endl;
        break;
    }
     
    return 0; 
}