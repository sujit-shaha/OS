#include <stdio.h>

struct Process {
    int pid, arrival, burst, priority, CT, TAT, WT;
};

void sortByPriority(struct Process p[], int n, int currentTime) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].arrival <= currentTime && p[j+1].arrival <= currentTime) {
                if (p[j].priority > p[j + 1].priority) {
                    struct Process temp = p[j];
                    p[j] = p[j+1];
                    p[j + 1] = temp;
                }
            }
        }
    }
}

void priority(struct Process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        sortByPriority(p, n, currentTime);
        
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && p[i].CT == 0) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            currentTime += p[idx].burst;
            p[idx].CT = currentTime;
            p[idx].TAT = p[idx].CT - p[idx].arrival;
            p[idx].WT = p[idx].TAT - p[idx].burst;
            totalTAT += p[idx].TAT;
            totalWT += p[idx].WT;
            completed++;
        }
    }

    printf("\n+-----+------------+----------+----------+------------+--------------+----------+\n");
    printf("| PID | Arrival    | Burst    | Priority | Completion | Turnaround   | Waiting  |\n");
    printf("+-----+------------+----------+----------+------------+--------------+----------+\n");
    
    for (int i = 0; i < n; i++) {
        printf("| %-3d | %-10d | %-8d | %-8d | %-10d | %-12d | %-8d |\n", 
               p[i].pid, p[i].arrival, p[i].burst, p[i].priority, p[i].CT, p[i].TAT, p[i].WT);
    }
    
    printf("+-----+------------+----------+----------+------------+--------------+----------+\n");
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival, Burst, and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].CT = 0;
    }

    priority(p, n);
    return 0;
}