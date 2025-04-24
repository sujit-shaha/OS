#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int pid, arrival, burst, priority, ct, tat, wt, remaining;
} Process;

void calculateMetrics(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].arrival;
        p[i].wt = p[i].tat - p[i].burst;
    }
}

void printTable(Process p[], int n) {
    printf("\n%-6s%-10s%-10s%-15s%-15s%-15s\n", "PID", "Arrival", "Burst", "Completion", "Turnaround", "Waiting");
    for (int i = 0; i < n; i++) {
        printf("%-6d%-10d%-10d%-15d%-15d%-15d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].ct, p[i].tat, p[i].wt);
    }
}

void fcfs(Process p[], int n) {
    int time = p[0].arrival;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].arrival > p[j].arrival)
                { Process temp = p[i]; p[i] = p[j]; p[j] = temp; }

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival) time = p[i].arrival;
        time += p[i].burst;
        p[i].ct = time;
    }

    calculateMetrics(p, n);
    printTable(p, n);
}

void sjfNonPreemptive(Process p[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, min_burst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].ct == 0 && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time += p[idx].burst;
            p[idx].ct = time;
            completed++;
        }
    }

    calculateMetrics(p, n);
    printTable(p, n);
}

void sjfPreemptive(Process p[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min_burst) {
                min_burst = p[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) time++;
        else {
            time++;
            p[idx].remaining--;
            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                completed++;
            }
        }
    }

    calculateMetrics(p, n);
    printTable(p, n);
}

void priorityNonPreemptive(Process p[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, min_priority = INT_MAX;

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
            completed++;
        }
    }

    calculateMetrics(p, n);
    printTable(p, n);
}

void priorityPreemptive(Process p[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, min_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }

        if (idx == -1) time++;
        else {
            time++;
            p[idx].remaining--;
            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                completed++;
            }
        }
    }

    calculateMetrics(p, n);
    printTable(p, n);
}

void roundRobin(Process p[], int n, int tq) {
    int time = 0, completed = 0;
    int queue[1000], front = 0, rear = 0;
    bool isQueued[100] = { false };

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && !isQueued[i]) {
                queue[rear++] = i;
                isQueued[i] = true;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int i = queue[front++];
        int execTime = (p[i].remaining < tq) ? p[i].remaining : tq;

        time += execTime;
        p[i].remaining -= execTime;

        for (int j = 0; j < n; j++) {
            if (p[j].arrival <= time && p[j].remaining > 0 && !isQueued[j]) {
                queue[rear++] = j;
                isQueued[j] = true;
            }
        }

        if (p[i].remaining == 0) {
            p[i].ct = time;
            completed++;
        } else {
            queue[rear++] = i;
        }
    }

    calculateMetrics(p, n);
    printTable(p, n);
}

int main() {
    int choice, tq;
    while (1) {
        int n;
        printf("Enter number of processes (Enter 0 to exit): ");
        scanf("%d", &n);
        if (n == 0) break;

        Process p[n];
        for (int i = 0; i < n; i++) {
            p[i].pid = i + 1;
            printf("Enter Arrival and Burst Time for P%d: ", p[i].pid);
            scanf("%d%d", &p[i].arrival, &p[i].burst);
            p[i].remaining = p[i].burst;
        }

        printf("Select Scheduling Algorithm:\n");
        printf("1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\n");
        printf("4. Priority (Non-Preemptive)\n5. Priority (Preemptive)\n6. Round Robin\nChoice: ");
        scanf("%d", &choice);

        if (choice == 4 || choice == 5) {
            for (int i = 0; i < n; i++) {
                printf("Enter Priority for P%d: ", p[i].pid);
                scanf("%d", &p[i].priority);
            }
        }

        if (choice == 6) {
            printf("Enter Time Quantum: ");
            scanf("%d", &tq);
        }

        switch (choice) {
            case 1: fcfs(p, n); break;
            case 2: sjfNonPreemptive(p, n); break;
            case 3: sjfPreemptive(p, n); break;
            case 4: priorityNonPreemptive(p, n); break;
            case 5: priorityPreemptive(p, n); break;
            case 6: roundRobin(p, n, tq); break;
            default: printf("Invalid choice!\n"); break;
        }
    }
    return 0;
}
