#include<bits/stdc++.h>
using namespace std;
struct Process{
    int id,arrival,burst,priority,ct,tat,wt,remaining;
};

void PrintTable(struct Process p[],int n)
{
    cout<<"\n+-----+------------+----------+------------+--------------+----------+\n";
    cout<<"| PID | Arrival    | Burst    | Completion | Turnaround   | Waiting  |\n";
    cout<<"+-----+------------+----------+------------+--------------+----------+\n";
    for(int i = 0 ;i < n;i++)
    {
        cout<<"| "<<p[i].id<<"  |"<<p[i].arrival<<"         | "<<p[i].burst<<"      | "<<p[i].ct<<"        | "<<p[i].tat<<"          | "<<p[i].wt<<"      |\n";
        cout<<"+-----+------------+----------+------------+--------------+----------+\n";
    }
}

void fcfs(struct Process p[],int n)
{
    sort(p,p+n,[](Process a,Process b){return a.arrival < b.arrival;});
    int time = 0 ;
    for(int i = 0;i<n;i++)
    {
        if(time > p[i].arrival)
        {
            time = time + p[i].burst;
        }
        else{
            time = p[i].arrival + p[i].burst;
        }

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].arrival;
        p[i].wt = p[i].tat - p[i].burst;
    }
    PrintTable(p,n);
}


void sjf_preemptive(struct Process p[], int n)
{
    int currentTime = 0, completed = 0;
    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && p[i].remaining > 0) {
                if (idx == -1 || p[i].remaining < p[idx].remaining ||
                    (p[i].remaining == p[idx].remaining && p[i].arrival < p[idx].arrival)) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].remaining--;
            currentTime++;

            if (p[idx].remaining == 0) {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].arrival;
                p[idx].wt = p[idx].tat - p[idx].burst;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    PrintTable(p, n);
}

void priorityScheduling(struct Process p[], int n) {
    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, min_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].ct == 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time += p[idx].burst;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].arrival;
            p[idx].wt = p[idx].tat - p[idx].burst;
            completed++;
        }
    }
    PrintTable(p, n);
}

void roundRobin(struct Process p[], int n, int tq) {
    int time = 0, completed = 0;
    printf("\nGantt Chart:\n");
    printf("|");
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                int execTime = (p[i].remaining < tq) ? p[i].remaining : tq;
                printf(" P%d (%d-%d) |", p[i].id, time, time + execTime);
                time += execTime;
                p[i].remaining -= execTime;
                if (p[i].remaining == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].arrival;
                    p[i].wt = p[i].tat - p[i].burst;
                    completed++;
                }
            }
        }
    }
    printf("\n");
    PrintTable(p, n);
}

int main()
{
    int choise,qt;
    while(true)
    {
        int n;
        cout<<"Enter the number of the processes:"<<endl;
        cin>>n;
        if(n==0) break;
        struct Process p[n];
        for(int i = 0 ;i< n;i++)
        {
            p[i].id = i+1;
            cout<<"Enter the value of Arrival and Brust Time of having Process id"<<p[i].id<<endl;
            cin>>p[i].arrival>>p[i].burst;
        }

        cout<<"Enter your Choise:"<<endl;
        cout<<"1.FCFS\n2.SJF\n3.Priority\n4.Round Robin"<<endl;
        cin>>choise;
        if(choise == 3)
        {
            cout<<"Enter the Priority of Each Process:"<<endl;
            for(int i = 0 ;i< n;i++)
            {
                cout<<"Enter the Priority of Process:"<<p[i].id<<endl;
                cin>>p[i].priority;
            }
        }

        if(choise == 4)
        {
            cout<<"Enter the Quantum Time:"<<endl;
            cin>>qt;
        }

        switch(choise)
        {
            case 1:
                fcfs(p,n);
                break;
            case 2:
                for(int i = 0 ;i< n;i++)
                {
                    p[i].remaining = p[i].burst;
                }
                sjf_preemptive(p,n);
                break;
            case 3:
                priorityScheduling(p,n);
                break;
            case 4:
                for(int i = 0 ;i< n;i++)
                {
                    p[i].remaining = p[i].burst;
                }
                roundRobin(p,n,qt);
                break;
            default:
                return 0;
        }
    }
}