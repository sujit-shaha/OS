#include <stdio.h>

struct Process {
    int pid, arrival, burst, remaining, CT, TAT, WT;
};

void printTable(struct Process p[], int n) {
    
    printf("\n+-----+------------+----------+------------+\n");
    printf("| PID | Arrival    | Burst    | Completion |\n");
    printf("+-----+------------+----------+------------+\n");

    for (int j = 0; j < n; j++) {
        printf("| %-3d | %-10d | %-8d | %-10d |\n",
               p[j].pid, p[j].arrival, p[j].burst, p[j].CT);
    }

    printf("+-----+------------+----------+------------+\n");
}

void printGantt(int gantt[], int time[], int idx) {

    printf("\nGantt Chart:\n");
    printf("-----------------------------------------\n|");
    for (int j = 0; j < idx; j++) {
        printf(" P%d |", gantt[j]);
    }
    printf("\n---------------------------------------\n|");

    for (int j = 0; j < idx; j++) {
        printf("    %d", time[j]);
    }
    printf("\n");
}

void roundRobin(struct Process p[], int n, int TQ) {
    int currTime = 0, completed = 0, i = 0;
    int gantt[100], time[100], idx = 0;

    for (int j = 0; j < n; j++) {
        p[j].remaining = p[j].burst;
    }

    while (completed < n) {
        if (p[i].remaining > 0 && p[i].arrival <= currTime) {
            if (p[i].remaining > TQ) {
                currTime += TQ;
                p[i].remaining -= TQ;
            } else {
                currTime += p[i].remaining;
                p[i].remaining = 0;
                p[i].CT = currTime;
                completed++;
            }

            gantt[idx] = p[i].pid;
            time[idx] = currTime;
            idx++;
        }

        i = (i+1)%n;
    }

    printGantt(gantt, time, idx);
    printTable(p,n);
}

void RR(struct Process p[], int n, int TQ) {
    int currTime = 0, completed = 0;
    int gantt[100], time[100], idx = 0;
    
    int front = 0, rear = 0;
    struct Process readyQueue[100];
    int inQueue[100] = {0};
    
    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        if (p[i].arrival == 0) {
            readyQueue[rear++] = p[i];
            inQueue[i] = 1;
        }
    }
    
    while (completed < n) {
        if (front != rear) {
            struct Process proc = readyQueue[front++];
            
            int execTime = (proc.remaining > TQ) ? TQ : proc.remaining;
            currTime += execTime;
            proc.remaining -= execTime;
            
            gantt[idx] = proc.pid;
            time[idx++] = currTime;

            for (int j = 0; j < n; j++) {
                if (p[j].arrival <= currTime && !inQueue[j] && p[j].remaining > 0) {
                    readyQueue[rear++] = p[j];
                    inQueue[j] = 1;
                }
            }

            // If the process is not completed, add it back to the queue
            if (proc.remaining > 0) {
                readyQueue[rear++] = proc;
            } else {
                proc.CT = currTime;
                completed++;
            }
        } else {
            currTime++; // Idle time if no process is ready
        }
    }

    // Print Completion Time for each process
    printf("Completion Times:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: %d\n", p[i].pid, p[i].CT);
    }
}

int main() {
    int n, TQ;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the Time Quantum: ");
    scanf("%d", &TQ);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    // Sorting processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    RR(p, n, TQ);

    return 0;
}